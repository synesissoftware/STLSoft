#!/usr/bin/env python3
"""Regenerate CMakeLists.txt hierarchy for stlsoft unit/component tests."""

from __future__ import annotations

from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TARGETS = [
    ROOT / "test" / "unit" / "stlsoft",
    ROOT / "test" / "component" / "stlsoft",
]

FOOTER = "\n\n# ############################## end of file ############################# #\n"

HEADER = (
    "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
)

# Tests for language- or compiler-specific APIs: (cmake condition, comment).
CONDITIONAL_SUBDIRS: dict[str, tuple[str, str]] = {
    "test.unit.stlsoft.shims.attribute.get_ptr.std.auto_ptr": (
        "CMAKE_CXX_STANDARD LESS 17",
        "std::auto_ptr removed in C++17",
    ),
    "test.unit.stlsoft.shims.logical.is_null.std.auto_ptr": (
        "CMAKE_CXX_STANDARD LESS 17",
        "std::auto_ptr removed in C++17",
    ),
    "test.unit.stlsoft.string.shim_string_vc5_": (
        'CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND MSVC_VERSION LESS 1200',
        "VC5-only string shim",
    ),
    "test.unit.stlsoft.smartptr.scoped_handle.scoped_handle_borland": (
        'CMAKE_CXX_COMPILER_ID STREQUAL "Borland" OR CMAKE_CXX_COMPILER_ID STREQUAL "Embarcadero"',
        "Borland/Embarcadero-only scoped_handle",
    ),
}


def has_content(directory: Path) -> bool:
    if not directory.is_dir():
        return False
    for child in directory.iterdir():
        if child.is_dir() and child.name.startswith("test."):
            return True
        if child.is_dir() and has_content(child):
            return True
    return False


def write_cmake(directory: Path) -> bool:
    if not has_content(directory):
        return False

    subdirs = sorted(
        p for p in directory.iterdir()
        if p.is_dir() and not p.name.startswith(".")
    )

    lines: list[str] = []
    for sub in subdirs:
        if sub.name.startswith("test."):
            entry = f"add_subdirectory({sub.name})"
        elif has_content(sub):
            entry = f"add_subdirectory({sub.name})"
        else:
            continue

        if sub.name in CONDITIONAL_SUBDIRS:
            condition, comment = CONDITIONAL_SUBDIRS[sub.name]
            lines.append(f"if({condition})")
            lines.append(f"\t# {comment}")
            lines.append(f"\t{entry}")
            lines.append("endif()")
        else:
            lines.append(entry)

    if not lines:
        return False

    content = HEADER + "\n".join(lines) + FOOTER
    cmake = directory / "CMakeLists.txt"
    if cmake.exists() and cmake.read_text() == content:
        return False
    cmake.write_text(content)
    return True


def main() -> None:
    updated = 0
    for target in TARGETS:
        if not target.exists():
            continue
        for directory in sorted(target.rglob("*"), key=lambda p: len(p.parts), reverse=True):
            if directory.is_dir() and write_cmake(directory):
                updated += 1
                print(f"updated {directory.relative_to(ROOT)}")
        if write_cmake(target):
            updated += 1
            print(f"updated {target.relative_to(ROOT)}")
    print(f"updated={updated}")


if __name__ == "__main__":
    main()
