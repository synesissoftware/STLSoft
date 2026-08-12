#!/usr/bin/env python3
"""Scaffold entry.c peer programs for C API headers lacking C validation.

For each header flagged ``needs_c_test`` by ``audit_c_tests.py``, creates a
sibling ``test.*.C.<leaf>`` directory next to an existing ``entry.cpp`` peer
when one exists, otherwise under ``test/unit/<project>/…``.

Regenerates affected CMakeLists.txt chains via the same hierarchy logic as
``setup_winstl_tests.write_cmake_hierarchy``.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TEST = ROOT / "test"
TEST_UNIT = TEST / "unit"
TEST_COMPONENT = TEST / "component"

sys.path.insert(0, str(Path(__file__).resolve().parent))

from obsolete_headers import is_obsolete_header, resolve_include  # noqa: E402
from audit_c_tests import (  # noqa: E402
    attach_tests,
    discover_c_headers,
    index_tests,
    recommend,
    test_targets_header,
)
from canonical_entry import render_minimal_c  # noqa: E402
from setup_winstl_tests import write_cmake_hierarchy  # noqa: E402

COMPONENT_KEYWORDS = {
    "filesystem", "directory", "readdir", "glob", "memory_mapped", "path",
    "environment", "registry", "reg_", "pid_sequence", "process", "socket",
    "network", "session", "connection", "dl_call", "module", "stopwatch",
    "home_directory", "pipe", "reactor", "message_queue", "toolhelp",
    "findfile", "ftpdir", "searchspec", "browse_for_folder", "clipboard",
    "directory_functions", "memory_map", "heapwalk", "codepage",
}


def pick_cpp_peer(row) -> str | None:
    project = row.project
    pool = [p for p in row.cpp_tests if f"/{project}/" in p.replace("\\", "/")]
    targeted = [
        p
        for p in pool
        if test_targets_header(p, row.include_path, row.area)
    ]
    candidates = targeted or pool
    if not candidates:
        return None

    area_dots = row.area.replace("/", ".")

    def score(p: str) -> tuple:
        name = Path(p).parent.name
        suffix = name.split(f"test.unit.{project}.")[-1]
        suffix = suffix.split(f"test.component.{project}.")[-1]
        exact_area = suffix == f"C.{area_dots.split('/')[-1]}" or suffix == area_dots
        area_in_name = area_dots.replace(".", "_") in name or area_dots in name
        return (
            0 if exact_area else (0 if area_in_name else 1),
            0 if "/unit/" in p else 1,
            len(p),
        )

    return sorted(candidates, key=score)[0]


def infer_kind(area: str, cpp_peer: str | None = None) -> str:
    if cpp_peer and "/component/" in cpp_peer.replace("\\", "/"):
        return "component"
    low = area.lower()
    return "component" if any(k in low for k in COMPONENT_KEYWORDS) else "unit"


def default_test_name(project: str, area: str, cpp_peer: str | None = None) -> str:
    kind = infer_kind(area, cpp_peer)
    parts = area.split("/")
    leaf = parts[-1]
    prefix = ".".join(["test", kind, project, *parts[:-1]])
    return f"{prefix}.C.{leaf}"


def leaf_dir_for_test(test_name: str, project: str, area: str) -> Path:
    kind = "component" if ".component." in test_name else "unit"
    base = TEST_COMPONENT if kind == "component" else TEST_UNIT
    parts = area.split("/")
    return base / project / Path(*parts[:-1]) / test_name


def cmake_from_peer(
    peer_cmake: Path | None, test_name: str, cpp_peer: str | None = None
) -> str:
    lines = [f"define_automated_test_program({test_name} entry.c)"]
    cpp_name = Path(cpp_peer).parent.name if cpp_peer else ""
    if peer_cmake and peer_cmake.exists():
        for line in peer_cmake.read_text(encoding="utf-8").splitlines():
            stripped = line.strip()
            if not stripped or stripped.startswith("define_automated_test_program"):
                continue
            if stripped.startswith("#"):
                continue
            extra = line.rstrip()
            if cpp_name:
                extra = extra.replace(cpp_name, test_name)
            lines.append(extra)
    header = "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
    return header + "\n".join(lines) + "\n"


def scaffold_row(row, *, dry_run: bool, force: bool = False) -> Path | None:
    cpp_peer = pick_cpp_peer(row)
    test_name = default_test_name(row.project, row.area, cpp_peer)
    leaf = leaf_dir_for_test(test_name, row.project, row.area)
    peer_cmake = (ROOT / Path(cpp_peer).parent / "CMakeLists.txt") if cpp_peer else None

    if (leaf / "entry.c").exists() and not force:
        return None

    include = f"<{resolve_include(row.include_path)}>"
    purpose = f"C validation for `{row.area}` (compiles header in a C translation unit)."

    if dry_run:
        print(f"would create {leaf.relative_to(ROOT)}")
        return leaf

    leaf.mkdir(parents=True, exist_ok=True)
    (leaf / "entry.c").write_text(
        render_minimal_c(
            test_name=test_name,
            purpose=purpose,
            primary_include=include,
        ),
        encoding="utf-8",
    )
    (leaf / "CMakeLists.txt").write_text(
        cmake_from_peer(peer_cmake, test_name, cpp_peer),
        encoding="utf-8",
    )
    return leaf


PROJECTS = (
    "acestl",
    "atlstl",
    "comstl",
    "inetstl",
    "mfcstl",
    "platformstl",
    "stlsoft",
    "unixstl",
    "winstl",
)


def regenerate_all_cmake() -> int:
    written = 0
    for project in PROJECTS:
        for base in (TEST_UNIT, TEST_COMPONENT):
            proj = base / project
            if proj.is_dir():
                written += write_cmake_hierarchy(proj)
    return written


def regenerate_cmake(projects: set[str]) -> int:
    written = 0
    for project in sorted(projects):
        for base in (TEST_UNIT, TEST_COMPONENT):
            proj = base / project
            if proj.is_dir():
                written += write_cmake_hierarchy(proj)
    return written


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--force", action="store_true", help="Overwrite existing entry.c")
    ap.add_argument(
        "--regenerate-cmake",
        action="store_true",
        help="Refresh CMakeLists.txt chains for all sub-projects",
    )
    ap.add_argument(
        "--project",
        action="append",
        help="Limit to sub-project(s); default: all with needs_c_test",
    )
    ap.add_argument(
        "--fix-cmake",
        action="store_true",
        help="Rewrite leaf CMakeLists.txt for all C tests (fix copied target names)",
    )
    args = ap.parse_args()

    if args.regenerate_cmake:
        n = regenerate_all_cmake()
        print(f"regenerated CMakeLists for {n} director(ies)")
        return 0

    rows = discover_c_headers()
    by_c, by_cpp, sym_users = index_tests()
    for row in rows:
        attach_tests(row, by_c, by_cpp, sym_users)
        recommend(row)

    if args.fix_cmake:
        fixed = 0
        for entry in sorted(TEST.rglob("test.*.C.*/CMakeLists.txt")):
            test_name = entry.parent.name
            match = next(
                (r for r in rows if default_test_name(r.project, r.area) == test_name),
                None,
            )
            peer = pick_cpp_peer(match) if match else None
            peer_cmake = (ROOT / Path(peer).parent / "CMakeLists.txt") if peer else None
            entry.write_text(
                cmake_from_peer(peer_cmake, test_name, peer), encoding="utf-8"
            )
            fixed += 1
        n = regenerate_all_cmake()
        print(f"fixed {fixed} leaf CMakeLists; regenerated {n} parent CMakeLists")
        return 0

    needs = [r for r in rows if r.recommendation == "needs_c_test"]
    needs = [r for r in needs if not is_obsolete_header(ROOT / "include" / r.include_path)]
    if args.project:
        allowed = set(args.project)
        needs = [r for r in needs if r.project in allowed]

    created: list[Path] = []
    skipped = 0
    for row in needs:
        path = scaffold_row(row, dry_run=args.dry_run, force=args.force)
        if path is None:
            skipped += 1
        else:
            created.append(path)
            if not args.dry_run:
                print(f"created {path.relative_to(ROOT)}")

    if not args.dry_run and created:
        projects: set[str] = set()
        for p in created:
            rel = p.relative_to(TEST)
            projects.add(rel.parts[1])
        n = regenerate_cmake(projects)
        print(f"regenerated CMakeLists for {n} director(ies)")

    print(f"created={len(created)} skipped_existing={skipped}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
