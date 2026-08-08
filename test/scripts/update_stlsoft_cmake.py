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
            lines.append(f"add_subdirectory({sub.name})")
        elif has_content(sub):
            lines.append(f"add_subdirectory({sub.name})")

    if not lines:
        return False

    content = "\n".join(lines) + FOOTER
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
