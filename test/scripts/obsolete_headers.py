"""Detect STLSoft obsolete shim headers (FILE_DEPRECATED + #error)."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
INCLUDE = ROOT / "include"

_DEP = re.compile(r"STLSOFT:FILE_DEPRECATED")
_ERR = re.compile(r"#\s*error\s+This file is now obsolete")
_FWD = re.compile(r'#\s*include\s+[<"]([^>"]+)[>"]')


def is_obsolete_header(path: Path) -> bool:
    if path.suffix not in (".h", ".hpp"):
        return False
    text = path.read_text(encoding="utf-8", errors="replace")
    return bool(_DEP.search(text) and _ERR.search(text))


def forward_target(path: Path) -> str | None:
    """First forwarded include from an obsolete shim, if any."""
    text = path.read_text(encoding="utf-8", errors="replace")
    if not is_obsolete_header(path):
        return None
    m = _FWD.search(text)
    return m.group(1) if m else None


def resolve_include(include_path: str) -> str:
    """Map obsolete shim path to its forward target when known."""
    path = INCLUDE / include_path
    if not path.is_file():
        return include_path
    fwd = forward_target(path)
    return fwd if fwd else include_path


def obsolete_paths() -> set[str]:
    out: set[str] = set()
    for h in INCLUDE.rglob("*"):
        if h.is_file() and is_obsolete_header(h):
            out.add(h.relative_to(INCLUDE).as_posix())
    return out
