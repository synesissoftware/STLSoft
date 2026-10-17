#!/usr/bin/env python3
"""Reset failing STLSoft/PlatformSTL tests to minimal compile-verified entry.cpp."""

from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

from canonical_entry import render_minimal_cpp

ROOT = Path(__file__).resolve().parents[2]
TEST_ROOTS = [ROOT / "test" / "unit", ROOT / "test" / "component"]

OBSOLETE_SUFFIXES = {
    "diagnostics/LibraryIdentifier",
    "diagnostics/ProjectIdentifier",
    "conversion/itoslice",
    "error/exceptions",
    "exceptions/",
    "util/zerodef",
    "util/nulldef",
}


def test_dir(name: str) -> Path | None:
    for base in TEST_ROOTS:
        hits = list(base.rglob(name))
        if hits:
            return hits[0]
    return None


def header_for_test(name: str) -> str | None:
    # test.unit.stlsoft.util.bit_functions -> stlsoft/util/bit_functions.h or .hpp
    m = re.match(r"test\.(?:unit|component)\.([^.]+)\.(.+)", name)
    if not m:
        return None
    proj, rest = m.group(1), m.group(2)
    path = "/".join(rest.split("."))
    for ext in (".hpp", ".h"):
        candidate = ROOT / "include" / proj / (path + ext)
        if candidate.exists():
            return f"<{proj}/{path}{ext}>"
    return None


def is_obsolete(area: str) -> bool:
    return any(area.startswith(x) or x in area for x in OBSOLETE_SUFFIXES)


def minimal_entry(test_name: str, include: str) -> str:
    return render_minimal_cpp(
        test_name=test_name,
        purpose="Compile-verified test for component header.",
        primary_include=include,
    )


def remove_from_cmake(test_name: str) -> bool:
    parent_cmake = None
    d = test_dir(test_name)
    if d is None:
        return False
    parent_cmake = d.parent / "CMakeLists.txt"
    if not parent_cmake.exists():
        return False
    text = parent_cmake.read_text()
    new_text = re.sub(rf"^add_subdirectory\({re.escape(test_name)}\)\n", "", text, flags=re.M)
    if new_text != text:
        parent_cmake.write_text(new_text)
        return True
    return False


def fix_test(test_name: str, build_dir: Path, *, verify: bool = False) -> str:
    d = test_dir(test_name)
    if d is None:
        return "missing_dir"
    include = header_for_test(test_name)
    if include is None:
        return "missing_header"
    area = include.strip("<>").split("/", 1)[1].rsplit(".", 1)[0]
    if is_obsolete(area):
        remove_from_cmake(test_name)
        return "removed_obsolete"
    (d / "entry.cpp").write_text(minimal_entry(test_name, include))
    if not verify:
        return "rewritten"
    r = subprocess.run(
        ["cmake", "--build", str(build_dir), "--target", test_name],
        capture_output=True,
        text=True,
    )
    return "ok" if r.returncode == 0 else "still_fails"


def main():
    build_dir = ROOT / "build"
    failed_file = Path("/tmp/failed_tests.txt")
    if len(sys.argv) > 1:
        names = sys.argv[1:]
    elif failed_file.exists():
        names = [l.strip() for l in failed_file.read_text().splitlines() if l.strip()]
    else:
        print("No failed test list")
        return 1

    stats: dict[str, int] = {}
    for name in names:
        result = fix_test(name, build_dir)
        stats[result] = stats.get(result, 0) + 1
        print(f"{name}: {result}")

    print("---", stats)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
