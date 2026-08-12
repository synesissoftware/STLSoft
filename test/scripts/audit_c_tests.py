#!/usr/bin/env python3
"""Phase 2.7 — audit C-language API surface vs test coverage (entry.c / entry.cpp).

Emits TESTING-C.md: which headers expose ostensibly C-callable API, whether an
``entry.c`` program validates that surface as C (not C++), and what exists today.

An ``entry.cpp`` that includes the same header does **not** prove C validity —
only a C translation unit can.
"""

from __future__ import annotations

import re
from collections import defaultdict
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

from obsolete_headers import is_obsolete_header  # noqa: E402

ROOT = Path(__file__).resolve().parents[2]
INCLUDE = ROOT / "include"
TEST = ROOT / "test"
OUTPUT = ROOT / "TESTING-C.md"

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

INCLUDE_RE = re.compile(r'#include\s+[<"]([^>"]+)[>"]')
C_SYM_DEF = re.compile(
    r"\b((?:stlsoft|winstl|unixstl|comstl|platformstl|inetstl)_C_\w+)\s*\("
)
C_SYM_USE = re.compile(
    r"\b((?:stlsoft|winstl|unixstl|comstl|platformstl|inetstl)_C_\w+)"
)

# Headers that are implementation detail / included only by other headers.
SKIP_HEADER_SUFFIXES = (
    "/classify_functions_X_.h",
    "/path_functions/classify_functions_X_.h",
    "/winstl_ntddi_.h",
    "/winstl_win32_winnt_.h",
)


@dataclass
class CApiHeader:
    include_path: str
    project: str
    area: str
    reason: str  # functions | api | symbols
    c_symbol_count: int
    sample_symbols: list[str] = field(default_factory=list)
    c_tests: list[str] = field(default_factory=list)
    cpp_tests: list[str] = field(default_factory=list)
    cpp_uses_c_api: bool = False
    recommendation: str = ""
    notes: str = ""


def md_link(display: str, href: str) -> str:
    safe = display.replace("|", "\\|")
    return f"[{safe}]({href})"


def area_from_include(include_path: str) -> str:
    p = Path(include_path)
    if p.suffix:
        p = p.with_suffix("")
    parts = p.parts[1:]  # drop project
    return "/".join(parts)


def is_c_api_candidate(rel: str, text: str) -> tuple[bool, str]:
    if any(rel.endswith(s) or s in rel for s in SKIP_HEADER_SUFFIXES):
        return False, ""
    if "/api/" in rel:
        return True, "api"
    if rel.endswith("_functions.h"):
        return True, "functions"
    syms = C_SYM_DEF.findall(text)
    if syms:
        return True, "symbols"
    return False, ""


def discover_c_headers() -> list[CApiHeader]:
    rows: list[CApiHeader] = []
    for path in sorted(INCLUDE.rglob("*.h")):
        rel = path.relative_to(INCLUDE).as_posix()
        project = rel.split("/")[0]
        if project not in PROJECTS:
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        ok, reason = is_c_api_candidate(rel, text)
        if not ok:
            continue
        if is_obsolete_header(path):
            continue
        syms = sorted(set(C_SYM_DEF.findall(text)))
        rows.append(
            CApiHeader(
                include_path=rel,
                project=project,
                area=area_from_include(rel),
                reason=reason,
                c_symbol_count=len(syms),
                sample_symbols=syms[:3],
            )
        )
    return rows


def index_tests() -> tuple[dict[str, list[str]], dict[str, list[str]], dict[str, set[str]]]:
    by_header_c: dict[str, list[str]] = defaultdict(list)
    by_header_cpp: dict[str, list[str]] = defaultdict(list)
    cpp_c_symbol_users: dict[str, set[str]] = defaultdict(set)

    for entry in sorted(TEST.rglob("entry.c")):
        rel = entry.relative_to(ROOT).as_posix()
        text = entry.read_text(encoding="utf-8", errors="replace")
        for h in INCLUDE_RE.findall(text):
            by_header_c[h].append(rel)

    for entry in sorted(TEST.rglob("entry.cpp")):
        rel = entry.relative_to(ROOT).as_posix()
        text = entry.read_text(encoding="utf-8", errors="replace")
        for h in INCLUDE_RE.findall(text):
            by_header_cpp[h].append(rel)
        for sym in C_SYM_USE.findall(text):
            cpp_c_symbol_users[sym].add(rel)

    return by_header_c, by_header_cpp, cpp_c_symbol_users


def area_matches_test(area: str, test_path: str) -> bool:
    """Heuristic: test directory/name covers the header area."""
    norm = area.replace("/", ".").replace("_", "").lower()
    tp = test_path.replace("/", ".").replace("_", "").lower()
    leaf = norm.split(".")[-1]
    return leaf in tp or norm in tp


def test_targets_header(test_path: str, include_path: str, area: str) -> bool:
    """True when the test program is primarily for this header (not a transitive include)."""
    stem = Path(include_path).stem
    compact = stem.replace("_", "").lower()
    tp = test_path.replace("_", "").lower()
    if compact and compact in tp:
        return True
    area_dots = area.replace("/", ".")
    if f".c.{area_dots}" in test_path.lower() or f".c.{stem.lower()}" in test_path.lower():
        return True
    return area_matches_test(area, test_path) and stem.lower() in test_path.lower()


def c_test_includes_header(test_path: str, include_path: str) -> bool:
    path = ROOT / test_path
    if not path.exists():
        return False
    text = path.read_text(encoding="utf-8", errors="replace")
    return f'"{include_path}"' in text or f"<{include_path}>" in text


def attach_tests(
    row: CApiHeader,
    by_header_c: dict[str, list[str]],
    by_header_cpp: dict[str, list[str]],
    cpp_c_symbol_users: dict[str, set[str]],
) -> None:
    row.c_tests = [
        p for p in by_header_c.get(row.include_path, [])
        if test_targets_header(p, row.include_path, row.area)
        and c_test_includes_header(p, row.include_path)
    ]
    row.cpp_tests = list(by_header_cpp.get(row.include_path, []))

    if not row.cpp_tests:
        seen: set[str] = set()
        for paths in by_header_cpp.values():
            for tp in paths:
                if tp in seen:
                    continue
                if area_matches_test(row.area, tp):
                    row.cpp_tests.append(tp)
                    seen.add(tp)

    users: set[str] = set()
    for sym in row.sample_symbols:
        users |= cpp_c_symbol_users.get(sym, set())
    row.cpp_uses_c_api = bool(users)
    if not row.cpp_uses_c_api and row.cpp_tests:
        for p in row.cpp_tests[:8]:
            path = ROOT / p
            if path.exists() and C_SYM_USE.search(
                path.read_text(encoding="utf-8", errors="replace")
            ):
                row.cpp_uses_c_api = True
                break


def recommend(row: CApiHeader) -> None:
    if row.c_tests:
        row.recommendation = "c_validated"
        row.notes = "Dedicated entry.c validates this header as C."
        return

    if row.reason == "api" and row.c_symbol_count == 0:
        row.recommendation = "api_shim"
        row.notes = (
            "Preprocessor / WinAPI alias shim — not a freestanding C API surface; "
            "indirect coverage or targeted entry.c only when a C TU is required."
        )
        return

    row.recommendation = "needs_c_test"
    if row.cpp_tests:
        row.notes = (
            "entry.cpp exists but compiles as C++; add entry.c to validate C linkage "
            "and C-only constraints."
        )
    else:
        row.notes = "No test coverage; add entry.c to validate this C API surface."


REC_LABELS = {
    "c_validated": "✅ C validated (`entry.c`)",
    "needs_c_test": "🟢 Needs `entry.c` (C validation)",
    "api_shim": "⚪ API shim (indirect)",
}


def render_document(rows: list[CApiHeader]) -> str:
    total = len(rows)
    has_c = sum(1 for r in rows if r.c_tests)
    cpp_without_c = sum(1 for r in rows if r.cpp_tests and not r.c_tests)
    no_test = sum(1 for r in rows if not r.c_tests and not r.cpp_tests)
    needs_c = sum(1 for r in rows if r.recommendation == "needs_c_test")
    api_shim = sum(1 for r in rows if r.recommendation == "api_shim")
    entry_c_count = sum(1 for _ in TEST.rglob("entry.c"))

    lines = [
        "# STLSoft — C-language test coverage (`TESTING-C.md`)",
        "",
        "Auto-generated by `test/scripts/audit_c_tests.py` (Phase 2.7). "
        "**Do not hand-edit** the tables; re-run the script after header or test changes.",
        "",
        "## At a glance",
        "",
        "| Metric | Count |",
        "|--------|------:|",
        f"| C API headers inventoried | {total} |",
        f"| C-validated (`entry.c` targets header) | {has_c} |",
        f"| Missing `entry.c` (C not validated) | {needs_c} |",
        f"| — of which also have `entry.cpp` | {cpp_without_c} |",
        f"| — of which have no test at all | {no_test} |",
        f"| API shim headers (deferred) | {api_shim} |",
        "",
        f"Existing `entry.c` programs in the tree: **{entry_c_count}**.",
        "",
        "## Recommendations",
        "",
        "| Symbol | Meaning |",
        "|--------|---------|",
    ]
    for key, label in REC_LABELS.items():
        lines.append(f"| {label} | `{key}` |")

    lines += [
        "",
        "## Policy",
        "",
        "1. **C validation requires `entry.c`.** If a header is part of the ostensibly "
        "C API (`*_functions.h`, `*_C_*` symbols, C-oriented `api/*` helpers), it must be "
        "compiled in a **C translation unit** to prove it is valid C. An `entry.cpp` "
        "that includes the same header is compiled as C++ and does not satisfy this.",
        "2. **`entry.cpp` is complementary, not substitutive.** C++ tests may exercise "
        "wrappers or call `extern \"C\"` symbols, but they remain a separate concern from "
        "C-language validation.",
        "3. **Dual programs** — where both exist, `entry.c` validates C; `entry.cpp` "
        "validates C++ wrappers and ergonomics.",
        "4. **Generators** — bulk scaffolds emit `entry.cpp` only; use "
        "`canonical_entry.render_c()` when adding C-validation targets from this audit.",
        "",
        "## Rollup by sub-project",
        "",
        "| Project | C API headers | C validated | Needs `entry.c` | Also `entry.cpp` | API shim |",
        "|---------|-------------:|------------:|----------------:|-----------------:|---------:|",
    ]

    for project in PROJECTS:
        subset = [r for r in rows if r.project == project]
        if not subset:
            continue
        lines.append(
            "| {p} | {n} | {c} | {nc} | {cpp} | {sh} |".format(
                p=project,
                n=len(subset),
                c=sum(1 for r in subset if r.c_tests),
                nc=sum(1 for r in subset if r.recommendation == "needs_c_test"),
                cpp=sum(1 for r in subset if r.cpp_tests and not r.c_tests),
                sh=sum(1 for r in subset if r.recommendation == "api_shim"),
            )
        )

    lines += [
        "",
        "## Priority — needs `entry.c` (C not yet validated)",
        "",
        "| Header | Area | `entry.cpp`? | Symbols | Recommendation |",
        "|--------|------|:------------:|--------:|----------------|",
    ]
    priority = [r for r in rows if r.recommendation == "needs_c_test"]
    priority.sort(key=lambda r: (0 if r.cpp_tests else 1, r.project, r.area))
    for r in priority[:40]:
        hdr = md_link(r.include_path, f"include/{r.include_path}")
        lines.append(
            f"| {hdr} | `{r.area}` | {'yes' if r.cpp_tests else '—'} | "
            f"{r.c_symbol_count} | {REC_LABELS[r.recommendation]} |"
        )
    if len(priority) > 40:
        lines.append(f"| … | | | *{len(priority) - 40} more in full table* |")

    lines += [
        "",
        "## Full inventory",
        "",
        "| Header | `entry.c` | `entry.cpp` (info) | Recommendation |",
        "|--------|-----------|-------------------:|----------------|",
    ]

    for r in sorted(rows, key=lambda x: (x.project, x.area)):
        hdr = md_link(r.area, f"include/{r.include_path}")
        c_cell = "✅" if r.c_tests else "—"
        cpp_cell = str(len(r.cpp_tests)) if r.cpp_tests else "—"
        lines.append(
            f"| {hdr} | {c_cell} | {cpp_cell} | {REC_LABELS[r.recommendation]} |"
        )

    lines += [
        "",
        "---",
        "",
        "Regenerate: `python3 test/scripts/audit_c_tests.py`",
        "",
        "See also: [`TESTING.md`](TESTING.md) (full test inventory).",
        "",
    ]
    return "\n".join(lines)


def main() -> int:
    rows = discover_c_headers()
    by_c, by_cpp, sym_users = index_tests()
    for row in rows:
        attach_tests(row, by_c, by_cpp, sym_users)
        recommend(row)

    OUTPUT.write_text(render_document(rows), encoding="utf-8")
    print(f"Wrote {OUTPUT.relative_to(ROOT)} ({len(rows)} C API headers)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
