#!/usr/bin/env python3
"""Remove test programs that target obsolete STLSoft shim headers.

Obsolete headers are marked STLSOFT:FILE_DEPRECATED and #error on current
_STLSOFT_VER. Tests should target precise headers only; this script removes
programs listed in REMOVE_TESTS when canonical coverage already exists.
"""

from __future__ import annotations

import re
import shutil
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from obsolete_headers import is_obsolete_header, obsolete_paths  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
TEST = ROOT / "test"

# Test leaf directories (relative to repo root) to delete.
REMOVE_TESTS = [
    # stlsoft — obsolete shim or duplicate of exception/ / util/ / algorithms/
    "test/unit/stlsoft/containers/test.unit.stlsoft.containers.array_policies",
    "test/unit/stlsoft/error/test.unit.stlsoft.error.exceptions",
    "test/unit/stlsoft/error/test.unit.stlsoft.error.os_exception",
    "test/unit/stlsoft/error/test.unit.stlsoft.error.project_exception",
    "test/unit/stlsoft/error/test.unit.stlsoft.error.throw_policies",
    "test/unit/stlsoft/exceptions/test.unit.stlsoft.exceptions.active_end_iterator_exhaustion",
    "test/unit/stlsoft/exceptions/test.unit.stlsoft.exceptions.contract_violation",
    "test/unit/stlsoft/exceptions/test.unit.stlsoft.exceptions.external_iterator_invalidation",
    "test/unit/stlsoft/exceptions/test.unit.stlsoft.exceptions.iteration_interruption",
    "test/unit/stlsoft/exceptions/test.unit.stlsoft.exceptions.unrecoverable",
    "test/component/stlsoft/filesystem/test.component.stlsoft.filesystem.read_line",
    "test/unit/stlsoft/function_adaptors/test.unit.stlsoft.function_adaptors.ref2ptr",
    "test/unit/stlsoft/functional/test.unit.stlsoft.functional.access_predicates",
    "test/unit/stlsoft/memory/test.unit.stlsoft.memory.allocator_features",
    "test/unit/stlsoft/memory/test.unit.stlsoft.memory.allocator_selector",
    "test/unit/stlsoft/util/std/test.unit.stlsoft.util.std.algorithm",
    "test/unit/stlsoft/synch/test.unit.stlsoft.synch.spin_policies",
    "test/unit/stlsoft/util/test.unit.stlsoft.util.count_digits",
    # winstl — obsolete umbrella, duplicate error/ path, or wrong C shim path
    "test/unit/winstl/error/test.unit.winstl.error.exceptions",
    "test/unit/winstl/synch/error/test.unit.winstl.synch.error.exceptions",
    "test/unit/winstl/synch/test.unit.winstl.synch.functions",
    "test/unit/winstl/shell/test.unit.winstl.shell.C.memory_functions",
    "test/unit/winstl/time/test.unit.winstl.time.C.format_functions",
    "test/component/winstl/clipboard/test.component.winstl.clipboard.exceptions",
    "test/component/winstl/registry/test.component.winstl.registry.exceptions",
    "test/component/winstl/toolhelp/test.component.winstl.toolhelp.exceptions",
    "test/unit/platformstl/error/test.unit.platformstl.error.exceptions",
    "test/unit/stlsoft/collections/test.unit.stlsoft.collections.associative_mapped_type_detector",
    # Wrong extension / duplicate — header is .h; C validation exists
    "test/unit/stlsoft/conversion/test.unit.stlsoft.conversion.itoslice",
]


def strip_subdir(cmake: Path, name: str) -> bool:
    if not cmake.exists():
        return False
    lines = cmake.read_text(encoding="utf-8").splitlines(keepends=True)
    needle = f"add_subdirectory({name})"
    new = [ln for ln in lines if needle not in ln]
    if new == lines:
        return False
    cmake.write_text("".join(new), encoding="utf-8")
    return True


def main() -> int:
    removed = 0
    for rel in REMOVE_TESTS:
        d = ROOT / rel
        if d.is_dir():
            shutil.rmtree(d)
            removed += 1
            print(f"removed {rel}")
            strip_subdir(d.parent / "CMakeLists.txt", d.name)

    for empty, parent_sub in (
        (TEST / "unit" / "stlsoft" / "exceptions", "exceptions"),
        (TEST / "unit" / "winstl" / "synch" / "error", "error"),
    ):
        if empty.is_dir() and not any(empty.iterdir()):
            shutil.rmtree(empty)
            strip_subdir(empty.parent / "CMakeLists.txt", parent_sub)
            print(f"removed empty {empty.relative_to(ROOT)}/")

    obsolete = obsolete_paths()
    inc_re = re.compile(r'#include\s+[<"]([^>"]+)[>"]')
    remaining = []
    for entry in list(TEST.rglob("entry.cpp")) + list(TEST.rglob("entry.c")):
        for inc in inc_re.findall(entry.read_text(encoding="utf-8", errors="replace")):
            if inc in obsolete:
                remaining.append((entry.relative_to(ROOT).as_posix(), inc))
    if remaining:
        print("\nWARNING: tests still including obsolete headers:")
        for e, inc in sorted(remaining):
            print(f"  {e} -> {inc}")
    else:
        print("\nNo remaining entry.cpp/entry.c files include obsolete shim headers.")

    print(f"\nremoved {removed} test director(ies)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
