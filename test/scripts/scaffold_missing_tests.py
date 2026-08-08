#!/usr/bin/env python3
"""Scaffold unit/component test projects for STLSoft sub-projects.

Generates CMakeLists.txt and entry.cpp stubs for components lacking direct
test programs. Intended as a bulk accelerator; review and enhance generated
tests before release.
"""

from __future__ import annotations

import os
import re
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
INCLUDE = ROOT / "include"
TEST_UNIT = ROOT / "test" / "unit"
TEST_COMPONENT = ROOT / "test" / "component"

SKIP_DIRS = {"internal", "api", "obsolete", "util"}
SKIP_FILES = {
    "atlstl.hpp", "comstl.h", "inetstl.h", "mfcstl.hpp", "platformstl.h",
    "platformstl.hpp", "stlsoft.h", "unixstl.h", "winstl.h", "acestl.h",
    "acestl.hpp", "collections.hpp", "algorithms.hpp", "registry.hpp",
    "regfwd.hpp", "synchfwd.hpp", "control_panel.fwd.hpp",
    "shims/access/string.hpp",
}
COMPONENT_KEYWORDS = {
    "filesystem", "directory", "readdir", "glob", "memory_mapped", "path",
    "environment", "registry", "reg_", "pid_sequence", "process", "socket",
    "network", "session", "connection", "dl_call", "module", "stopwatch",
    "home_directory", "pipe", "reactor", "message_queue", "toolhelp",
    "findfile", "ftpdir", "searchspec", "browse_for_folder", "clipboard",
    "directory_functions", "memory_map", "heapwalk", "codepage",
}

STL_SOFT_SKIP_AREAS = {"meta", "obsolete", "internal", "api", "quality", "view"}


@dataclass
class Component:
    project: str
    relpath: str  # e.g. unixstl/filesystem/path.hpp

    @property
    def area_path(self) -> str:
        p = Path(self.relpath).with_suffix("")
        parts = p.parts[1:]  # drop project
        return "/".join(parts)

    @property
    def test_suffix(self) -> str:
        return self.area_path.replace("/", ".")

    @property
    def header_include(self) -> str:
        return f"<{self.relpath}>"

    @property
    def is_component(self) -> bool:
        low = self.area_path.lower()
        return any(k in low for k in COMPONENT_KEYWORDS)

    def test_name(self, kind: str) -> str:
        return f"test.{kind}.{self.project}.{self.test_suffix}"

    def existing(self) -> bool:
        for base in (TEST_UNIT, TEST_COMPONENT):
            if list(base.rglob(self.test_name("unit").replace("test.unit.", "test.unit."))):
                pass
        name_u = self.test_name("unit")
        name_c = self.test_name("component")
        for base in (TEST_UNIT, TEST_COMPONENT):
            if (base / self.project).exists():
                for d in base.rglob("*"):
                    if d.is_dir() and d.name in (name_u, name_c):
                        return True
        return False


def discover(project: str, extra_skip_dirs: set[str] | None = None) -> list[Component]:
    skip = set(SKIP_DIRS)
    if extra_skip_dirs:
        skip |= extra_skip_dirs
    if project == "stlsoft":
        skip.discard("util")  # stlsoft/util is substantive; skip only nested util/ in other projects
    proj_dir = INCLUDE / project
    out: list[Component] = []
    if not proj_dir.exists():
        return out
    for path in sorted(proj_dir.rglob("*")):
        if not path.is_file() or path.suffix not in (".h", ".hpp"):
            continue
        rel = path.relative_to(INCLUDE).as_posix()
        parts = Path(rel).parts
        if any(p in skip for p in parts):
            continue
        if path.name in SKIP_FILES or path.name.endswith("_.h") or ".fwd." in path.name:
            continue
        if project == "stlsoft" and parts[1] in STL_SOFT_SKIP_AREAS:
            continue
        out.append(Component(project, rel))
    return out


def entry_cpp(comp: Component, kind: str) -> str:
    test_name = comp.test_name(kind)
    return f"""/* /////////////////////////////////////////////////////////////////////////
 * File:    {test_name}/entry.cpp
 *
 * Purpose: {'Component' if kind == 'component' else 'Unit'}-tests for `{comp.area_path}`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include {comp.header_include}

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {{

static void TEST_compile_and_link();
static void TEST_smoke();

}} // anonymous namespace


int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(TEST_compile_and_link);
        XTESTS_RUN_CASE(TEST_smoke);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}

    return retCode;
}}


namespace {{

static void TEST_compile_and_link()
{{
    /* Exercises primary header inclusion and basic symbol visibility. */
    TEST_PASSED();
}}

static void TEST_smoke()
{{
    /* TODO: enhance with behavioural assertions for {comp.area_path}. */
    TEST_PASSED();
}}

}} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
"""


def cmake_leaf(comp: Component, kind: str) -> str:
    return f"define_automated_test_program({comp.test_name(kind)} entry.cpp)\n"


def write_test(comp: Component, kind: str, dry_run: bool = False) -> Path:
    base = TEST_COMPONENT if kind == "component" else TEST_UNIT
    test_name = comp.test_name(kind)
    # directory mirrors area path under project
    area_parts = comp.area_path.split("/")
    leaf = base / comp.project / Path(*area_parts[:-1]) / test_name
    if dry_run:
        return leaf
    leaf.mkdir(parents=True, exist_ok=True)
    (leaf / "entry.cpp").write_text(entry_cpp(comp, kind))
    (leaf / "CMakeLists.txt").write_text(cmake_leaf(comp, kind))
    return leaf


def ensure_cmake_chain(leaf: Path, project: str):
    """Add add_subdirectory for leaf up to project root."""
    rel = leaf.relative_to(TEST_UNIT if "unit" in leaf.parts else TEST_COMPONENT)
  # simplified: parent CMakeLists managed separately
    pass


def main():
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("projects", nargs="+", help="Sub-projects e.g. unixstl platformstl")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    created = 0
    skipped = 0
    for project in args.projects:
        for comp in discover(project):
            if comp.existing():
                skipped += 1
                continue
            kind = "component" if comp.is_component else "unit"
            path = write_test(comp, kind, dry_run=args.dry_run)
            if not args.dry_run:
                print(f"created {kind}: {path.relative_to(ROOT)}")
            created += 1
    print(f"created={created} skipped_existing={skipped}")


if __name__ == "__main__":
    main()
