#!/usr/bin/env python3
"""Remove mistaken anonymous-namespace wrappers around post-main test impls."""
from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2] / "test"


def fix_file(path: Path) -> bool:
    text = path.read_text(encoding="utf-8")
    if not re.search(
        r"^static void \w+\(void\);\s*(?://[^\n]*)?\s*\n\s*\nint main",
        text,
        re.M,
    ):
        return False
    if not re.search(
        r"return retCode;\s*\}\s*\n\s*namespace \{\s*\n\s*static void ",
        text,
    ):
        return False

    new = re.sub(
        r"(return retCode;\s*\}\s*\n)\s*namespace \{\s*\n",
        r"\1",
        text,
        count=1,
    )
    new = re.sub(r"\n\} // anonymous namespace(\s*\n)", r"\1", new, count=1)
    if new == text:
        return False
    path.write_text(new, encoding="utf-8")
    return True


def main() -> int:
    fixed = [p for p in ROOT.rglob("entry.cpp") if fix_file(p)]
    print(f"Unwrapped {len(fixed)} file(s)")
    for p in fixed:
        print(f"  {p.relative_to(ROOT.parent)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
