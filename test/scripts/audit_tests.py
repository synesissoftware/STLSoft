#!/usr/bin/env python3
"""Audit unit/component test programs and emit TESTING.md inventory tables.

Phase 0 of the test-quality initiative: classify every test/entry.* file by
structure, provenance, and assertion depth. Does not modify test sources.
"""

from __future__ import annotations

import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TEST_ROOT = ROOT / "test"
OUTPUT = ROOT / "TESTING.md"

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

INCLUDE_ROOT = {p: f"include/{p}/" for p in PROJECTS}
UNIT_ROOT = {p: f"test/unit/{p}/" for p in PROJECTS}
COMP_ROOT = {p: f"test/component/{p}/" for p in PROJECTS}
HEADER_PREFIX = {p: f"{p}/" for p in PROJECTS}

INCLUDE_RE = re.compile(
    r'#include\s+[<"]((?:acestl|atlstl|comstl|inetstl|mfcstl|platformstl|stlsoft|unixstl|winstl)/[^>"]+)[>"]'
)
PURPOSE_RE = re.compile(r"^\s*\*\s*Purpose:\s*(.+)$", re.MULTILINE)
CREATED_RE = re.compile(r"^\s*\*\s*Created:\s*(.+)$", re.MULTILINE)
AUTO_GEN_NOTE = "Auto-generated on 9th August 2026"

VANILLA_PURPOSE_MARKERS = (
    "Compile-verified test",
    "Compile-verified test for component header",
)

ASSERTION_MACROS = (
    "TEST_INTEGER_EQUAL",
    "TEST_INT_EQ",
    "TEST_INT_NE",
    "TEST_INT_GE",
    "TEST_INT_LE",
    "TEST_INT_GT",
    "TEST_INT_LT",
    "TEST_UINT_EQ",
    "TEST_MS_EQ",
    "TEST_MULTIBYTE_STRING_EQUAL",
    "TEST_WIDE_STRING_EQUAL",
    "TEST_CHAR_EQ",
    "TEST_BOOLEAN_TRUE",
    "TEST_BOOLEAN_FALSE",
    "TEST_FAIL",
    "TEST_FAIL_WITH_QUALIFIER",
    "TEST_ERROR_EQ",
    "TEST_PTR_EQ",
    "TEST_PTR_NE",
)

SKIP_INCLUDES = {
    "stlsoft/stlsoft.h",
    "platformstl/platformstl.h",
    "unixstl/unixstl.h",
    "winstl/winstl.h",
    "comstl/comstl.h",
    "inetstl/inetstl.h",
    "acestl/acestl.hpp",
    "atlstl/atlstl.hpp",
    "mfcstl/mfcstl.hpp",
}


@dataclass
class AuditRow:
    rel_path: str
    project: str
    kind: str  # unit | component
    headers: list[str] = field(default_factory=list)
    provenance: str = "old"  # old | new | modified
    vanilla_purpose: bool = False
    sectioned: bool = False
    canonical: bool = False
    substance: str = "unknown"  # substantive | placeholder | partial | smoke
    test_cases: int = 0
    purpose: str = ""


def md_link(display: str, href: str) -> str:
    """Markdown link; pipe characters in display are escaped for table cells."""
    safe = display.replace("|", "\\|")
    return f"[{safe}]({href})"


def elide_prefix(path: str, prefix: str) -> str:
    return path[len(prefix) :] if path.startswith(prefix) else path


def test_path_cell(rel_path: str, project: str, kind: str) -> str:
    if project in PROJECTS:
        root = UNIT_ROOT[project] if kind == "unit" else COMP_ROOT[project]
    elif kind == "unit" and rel_path.startswith("test/unit/"):
        # e.g. test/unit/test.unit.versions/entry.cpp
        root = rel_path.rsplit("/", 1)[0] + "/"
    elif kind == "component" and rel_path.startswith("test/component/"):
        root = rel_path.rsplit("/", 1)[0] + "/"
    else:
        return md_link(rel_path, rel_path)
    display = elide_prefix(rel_path, root)
    return md_link(display, rel_path)


def header_href(header: str) -> str:
    return f"include/{header}"


def header_display(header: str, project: str) -> str:
    prefix = HEADER_PREFIX.get(project, "")
    return elide_prefix(header, prefix) if prefix else header


def format_header_cell(headers: list[str], project: str) -> str:
    if not headers:
        return "—"
    primary = headers[0]
    display = header_display(primary, project)
    cell = md_link(display, header_href(primary))
    if len(headers) == 1:
        return cell
    return f"{cell} (+{len(headers) - 1})"


def git_merge_base() -> str | None:
    for ref in ("origin/master", "origin/main", "master", "main"):
        try:
            subprocess.run(
                ["git", "rev-parse", "--verify", ref],
                cwd=ROOT,
                capture_output=True,
                check=True,
            )
            out = subprocess.run(
                ["git", "merge-base", "HEAD", ref],
                cwd=ROOT,
                capture_output=True,
                text=True,
                check=True,
            )
            return out.stdout.strip() or None
        except subprocess.CalledProcessError:
            continue
    try:
        out = subprocess.run(
            ["git", "rev-list", "--max-parents=0", "HEAD"],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=True,
        )
        return out.stdout.strip().splitlines()[0]
    except subprocess.CalledProcessError:
        return None


def git_name_status(base: str) -> dict[str, str]:
    out = subprocess.run(
        [
            "git",
            "diff",
            "--name-status",
            base,
            "--",
            "test/unit",
            "test/component",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
        check=True,
    )
    status: dict[str, str] = {}
    for line in out.stdout.splitlines():
        if not line.strip():
            continue
        parts = line.split("\t")
        if len(parts) != 2:
            continue
        code, path = parts
        if path.endswith("/entry.cpp") or path.endswith("/entry.c"):
            status[path] = code
    return status


def discover_entries() -> list[Path]:
    entries: list[Path] = []
    for base in (TEST_ROOT / "unit", TEST_ROOT / "component"):
        if not base.exists():
            continue
        for path in sorted(base.rglob("entry.cpp")):
            entries.append(path)
        for path in sorted(base.rglob("entry.c")):
            entries.append(path)
    # Top-level unit test (versions)
    versions = TEST_ROOT / "unit" / "test.unit.versions" / "entry.cpp"
    if versions.exists() and versions not in entries:
        entries.append(versions)
    return entries


def extract_headers(text: str) -> list[str]:
    found: list[str] = []
    for m in INCLUDE_RE.finditer(text):
        inc = m.group(1)
        if inc in SKIP_INCLUDES:
            continue
        if inc not in found:
            found.append(inc)
    return found


def extract_purpose(text: str) -> str:
    m = PURPOSE_RE.search(text)
    return m.group(1).strip() if m else ""


def is_vanilla_purpose(purpose: str) -> bool:
    if not purpose:
        return True
    for marker in VANILLA_PURPOSE_MARKERS:
        if marker in purpose:
            return True
    # Scaffold boilerplate: Unit-tests for `area/path` with no API detail
    if re.match(r"^(Unit|Component)-tests for `[^`]+`\.$", purpose):
        return True
    if purpose == "Unit-tests for versions":
        return False
    return False


def count_test_cases(text: str) -> int:
    return len(re.findall(r"\bXTESTS_RUN_CASE\s*\(", text))


def classify_substance(text: str) -> str:
    has_compile_only = "TEST_compile_and_link" in text
    assertion_hits = sum(text.count(m) for m in ASSERTION_MACROS)
    passed_hits = text.count("TEST_PASSED()")

    if has_compile_only and assertion_hits == 0:
        return "placeholder"
    if assertion_hits == 0 and passed_hits > 0:
        return "placeholder"
    if assertion_hits <= 2 and count_test_cases(text) <= 1:
        return "smoke"
    if has_compile_only and assertion_hits > 0:
        return "partial"
    if passed_hits > 0 and assertion_hits <= passed_hits:
        return "smoke"
    return "substantive"


def is_sectioned(text: str) -> bool:
    section_markers = text.count("/* /////////////////////////////////////////////////////////////////////////")
    has_includes_section = bool(
        re.search(r"\* includes\s*\*/", text) or re.search(r"\* includes\n", text)
    )
    has_forward = "forward declarations" in text.lower()
    has_main_section = "main()" in text or "* main" in text.lower()
    return section_markers >= 3 and has_includes_section and has_forward and has_main_section


def is_canonical(text: str, is_cpp: bool) -> bool:
    if not is_sectioned(text):
        return False

    # forward declarations before main
    fwd = re.search(r"forward declarations", text, re.IGNORECASE)
    main = re.search(r"\bmain\s*\(", text)
    if not fwd or not main or fwd.start() > main.start():
        return False

    # implementations after main's closing brace (heuristic: test function implementations section)
    impl = re.search(
        r"(test function implementations|test functions|names)\s*\n\s*\*/",
        text,
        re.IGNORECASE,
    )
    if impl and impl.start() < main.start():
        return False

    # main should precede at least one static test function definition body
    after_main = text[main.start() :]
    if "XTESTS_END_RUNNER" not in after_main:
        return False

    # C++ exemplar uses anonymous namespace for forward decls; C uses file scope
    if is_cpp:
        between = text[fwd.start() : main.start()]
        if "namespace" not in between and "static void" not in between:
            # allow free functions declared static at file scope in some tests
            if "static void" not in text[fwd.start() : main.start() + 200]:
                return False

    return True


def parse_project_and_kind(rel: str) -> tuple[str, str]:
    parts = Path(rel).parts
    # test/unit/<project>/... or test/component/<project>/...
    if len(parts) >= 3 and parts[0] == "test" and parts[1] in ("unit", "component"):
        return parts[2], parts[1]
    if parts[-2] == "test.unit.versions":
        return "stlsoft", "unit"
    return "unknown", "unknown"


def audit_file(path: Path, git_status: dict[str, str]) -> AuditRow:
    rel = path.relative_to(ROOT).as_posix()
    project, kind = parse_project_and_kind(rel)
    text = path.read_text(encoding="utf-8", errors="replace")
    is_cpp = path.suffix == ".cpp"

    purpose = extract_purpose(text)
    row = AuditRow(
        rel_path=rel,
        project=project,
        kind=kind,
        headers=extract_headers(text),
        purpose=purpose,
        vanilla_purpose=is_vanilla_purpose(purpose),
        sectioned=is_sectioned(text),
        canonical=is_canonical(text, is_cpp),
        substance=classify_substance(text),
        test_cases=count_test_cases(text),
    )

    code = git_status.get(rel)
    if code == "A":
        row.provenance = "new"
    elif code == "M":
        row.provenance = "modified"
    else:
        row.provenance = "old"

    return row


def bool_emoji(value: bool) -> str:
    return "✅" if value else "⬜"


def provenance_emoji(row: AuditRow) -> str:
    if row.provenance == "new":
        return "📋" if row.vanilla_purpose else "🆕"
    if row.provenance == "modified":
        return "✏️"
    return "📎"


def substance_emoji(value: str) -> str:
    return {
        "substantive": "🟢",
        "smoke": "🟡",
        "partial": "🟠",
        "placeholder": "🔴",
    }.get(value, value)


def render_legend() -> str:
    return """## Legend

Per-file inventory tables use the following symbols:

| Symbol | Column | Meaning |
|--------|--------|---------|
| 🆕 | Prov | New test (this initiative) |
| 📋 | Prov | New test with vanilla `Purpose:` (needs upgrade) |
| ✏️ | Prov | Modified pre-existing test |
| 📎 | Prov | Unchanged since merge-base |
| ✅ | Sect / Canon | Yes — sectioned layout or canonical structure |
| ⬜ | Sect / Canon | No — not sectioned or not canonical |
| 🟢 | Subst | Substantive — multiple behavioural assertions |
| 🟡 | Subst | Smoke — minimal bootstrap coverage |
| 🟠 | Subst | Partial — compile-only plus some assertions |
| 🔴 | Subst | Placeholder — `TEST_compile_and_link()` / `TEST_PASSED()` only |

**Column key:** Prov = provenance; Sect = sectioned; Canon = canonical structure; Subst = substance; # = test-case count.

"""


def render_project_roots(project: str, all_rows: list[AuditRow], *, section_rows: list[AuditRow] | None = None) -> str:
    project_rows = section_rows if section_rows is not None else [r for r in all_rows if r.project == project]
    if not project_rows:
        return ""

    lines: list[str] = []
    if project in PROJECTS:
        lines.append(f"- **Includes**: `{INCLUDE_ROOT[project]}`")
        if any(r.kind == "unit" for r in project_rows):
            lines.append(f"- **Unit tests**: `{UNIT_ROOT[project]}`")
        if any(r.kind == "component" for r in project_rows):
            lines.append(f"- **Component tests**: `{COMP_ROOT[project]}`")
    else:
        unit_paths = sorted({r.rel_path.rsplit("/", 1)[0] + "/" for r in project_rows if r.kind == "unit"})
        comp_paths = sorted(
            {r.rel_path.rsplit("/", 1)[0] + "/" for r in project_rows if r.kind == "component"}
        )
        for p in unit_paths:
            lines.append(f"- **Unit tests**: `{p}`")
        for p in comp_paths:
            lines.append(f"- **Component tests**: `{p}`")
    lines.append("")
    return "\n".join(lines)


def render_table(rows: list[AuditRow], project: str) -> str:
    if not rows:
        return "_No test programs in this category._\n\n"

    lines = [
        "| Path | Header(s) | Prov | Sect | Canon | Subst | # |",
        "|------|-----------|:----:|:----:|:-----:|:-----:|--:|",
    ]
    for r in rows:
        lines.append(
            "| "
            + " | ".join(
                [
                    test_path_cell(r.rel_path, project, r.kind),
                    format_header_cell(r.headers, project),
                    provenance_emoji(r),
                    bool_emoji(r.sectioned),
                    bool_emoji(r.canonical),
                    substance_emoji(r.substance),
                    str(r.test_cases),
                ]
            )
            + " |"
        )
    lines.append("")
    return "\n".join(lines)


def summarise(rows: list[AuditRow]) -> str:
    n = len(rows)
    if n == 0:
        return ""
    counts = {
        "new": sum(1 for r in rows if r.provenance == "new"),
        "modified": sum(1 for r in rows if r.provenance == "modified"),
        "old": sum(1 for r in rows if r.provenance == "old"),
        "placeholder": sum(1 for r in rows if r.substance == "placeholder"),
        "smoke": sum(1 for r in rows if r.substance == "smoke"),
        "substantive": sum(1 for r in rows if r.substance == "substantive"),
        "canonical": sum(1 for r in rows if r.canonical),
        "sectioned": sum(1 for r in rows if r.sectioned),
    }
    return (
        f"**{n}** programs — "
        f"new: {counts['new']}, modified: {counts['modified']}, old: {counts['old']}; "
        f"substantive: {counts['substantive']}, smoke: {counts['smoke']}, placeholder: {counts['placeholder']}; "
        f"sectioned: {counts['sectioned']}, canonical: {counts['canonical']}.\n\n"
    )


def render_exclusions() -> str:
    return """## Excluded and deferred components

Components intentionally **not** covered by automated unit/component tests in this tree (or deferred to component/GUI/manual testing):

### ATLSTL (`test/unit/atlstl/DEFERRED.md`)

| Component / area | Reason |
|------------------|--------|
| `util/module_scope.hpp` | Requires full ATL module object map, `HINSTANCE`, type library — component-level infrastructure |
| `window/*` (`about_dialog`, `enhanced_window`, `window`) | GUI/HWND-heavy; manual or component GUI tests |
| `automation/multiple_dispatch.hpp` (full runtime) | Dispid striping unit-tested; `GetIDsOfNames()` / `Invoke()` routing needs MIDL type library |

### COMSTL (`test/unit/comstl/SKIPPED.md`)

| Component | Reason |
|-----------|--------|
| `speech/sapi_util.hpp` | Windows SAPI runtime + headers |
| `typelib/functions.hpp`, `typelib/TypeInfo_resource_scope.hpp` | Requires `.tlb` / registered type library |
| `util/thread_marshal.hpp` | Cross-apartment marshaling + proxy/stub |
| `conversion/method_cast.hpp` | Live `IDispatch` with callable DISPIDs |
| `collections/collection_sequence.hpp` | Custom `IEnumXXXX` protocol |
| Obsolete shims (`interface/interface_cast.hpp`, `interface/interface_traits.hpp`) | Superseded by `conversion/` / `util/` headers (tested) |
| Policy-only / aggregate headers | No standalone runtime surface |

### WinSTL

| Area | Reason |
|------|--------|
| Controls, window scopes, `browse_for_folder`, interactive GUI | Not automatable as unit tests; excluded from bulk generation |
| Some registry/clipboard sequences | Covered where mockable; interactive shell UI excluded |

### INETSTL

| Area | Reason |
|------|--------|
| WinInet FTP / directory sequences | External network + WinInet dependency; excluded from Unix CI scope |

### STLSoft

| Area | Reason |
|------|--------|
| `meta/`, `obsolete/`, `internal/`, vestigial `api/` | Meta-programming, legacy, or internal implementation headers |
| `quality/` | Non-product test harness headers |

### ACESTL

| Area | Reason |
|------|--------|
| Entire sub-project | Gated on `HAS_ACE`; built only when ACE is available |

"""


def render_philosophy() -> str:
    return """## Testing philosophy

STLSoft uses the [xTests](https://github.com/synesissoftware/xTests) framework. Each test program is a standalone executable with one `entry.cpp` or `entry.c` per CMake target.

### Unit tests (`test/unit/`)

- **Goal**: Verify a single header (or small API surface) in isolation.
- **Scope**: Prefer deterministic, in-process checks — no external services, no GUI, no cross-process coupling unless unavoidable.
- **Naming**: `test.unit.<subproject>.<area>.<component>/` (mirrors include path where practical).
- **Acceptable depth**: From a single focused smoke case up to exhaustive assertion suites; **not** acceptable as a long-term state: compile-only `TEST_compile_and_link()` / lone `TEST_PASSED()` with no behavioural checks.

### Component tests (`test/component/`)

- **Goal**: Exercise integration across headers, OS facilities, or runtime resources (filesystem, sockets, environment, timing, etc.).
- **Scope**: May create temp files, bind local sockets, read environment variables, or depend on platform behaviour; still non-interactive and CI-friendly.
- **Naming**: `test.component.<subproject>.<area>.<component>/`.
- **Platform gating**: Some targets build only on Windows, only on Unix, or only when optional dependencies (e.g. ACE) are present.

### Quality tiers (this inventory)

| Symbol | Tier |
|--------|------|
| 🟢 | **Substantive** — multiple behavioural assertions exercising real API semantics |
| 🟡 | **Smoke** — one or two cases with minimal assertions; acceptable bootstrap, not the end state |
| 🟠 | **Partial** — mix of compile-only checks and some behavioural assertions |
| 🔴 | **Placeholder** — `TEST_compile_and_link()` and/or `TEST_PASSED()` only; **must be upgraded** (Phases 2–3) |
| ✅ | **Canonical** — sectioned file layout: includes → forward declarations → `main()` → implementations |

"""


def render_rollup(rows: list[AuditRow]) -> str:
    lines = [
        "## Summary by sub-project\n",
        "| Sub-project | Unit | Component | Total | New | Modified | Placeholder | Canonical |",
        "|-------------|-----:|----------:|------:|----:|---------:|------------:|----------:|",
    ]
    for project in PROJECTS:
        subset = [r for r in rows if r.project == project]
        unit_n = sum(1 for r in subset if r.kind == "unit")
        comp_n = sum(1 for r in subset if r.kind == "component")
        lines.append(
            "| "
            + " | ".join(
                [
                    project.upper(),
                    str(unit_n),
                    str(comp_n),
                    str(len(subset)),
                    str(sum(1 for r in subset if r.provenance == "new")),
                    str(sum(1 for r in subset if r.provenance == "modified")),
                    str(sum(1 for r in subset if r.substance == "placeholder")),
                    str(sum(1 for r in subset if r.canonical)),
                ]
            )
            + " |"
        )
    misc = [r for r in rows if r.project not in PROJECTS]
    if misc:
        lines.append(
            "| "
            + " | ".join(
                [
                    "OTHER",
                    str(sum(1 for r in misc if r.kind == "unit")),
                    str(sum(1 for r in misc if r.kind == "component")),
                    str(len(misc)),
                    str(sum(1 for r in misc if r.provenance == "new")),
                    str(sum(1 for r in misc if r.provenance == "modified")),
                    str(sum(1 for r in misc if r.substance == "placeholder")),
                    str(sum(1 for r in misc if r.canonical)),
                ]
            )
            + " |"
        )
    total_row = [
        "**TOTAL**",
        str(sum(1 for r in rows if r.kind == "unit")),
        str(sum(1 for r in rows if r.kind == "component")),
        str(len(rows)),
        str(sum(1 for r in rows if r.provenance == "new")),
        str(sum(1 for r in rows if r.provenance == "modified")),
        str(sum(1 for r in rows if r.substance == "placeholder")),
        str(sum(1 for r in rows if r.canonical)),
    ]
    lines.append("| " + " | ".join(total_row) + " |")
    lines.append("")
    return "\n".join(lines)


def render_intro(total: int, base: str | None) -> str:
    return f"""# STLSoft — Test inventory (`TESTING.md`)

Auto-generated by `test/scripts/audit_tests.py` (Phase 0 audit). **Do not hand-edit** the per-file tables; re-run the script after test changes.

## At a glance

| Metric | Count |
|--------|------:|
| Total test programs (`entry.cpp` / `entry.c`) | {total} |
| Git merge-base for provenance | `{base or "unknown"}` |

See [Legend](#legend) for per-file table symbols.

**Canonical structure** follows `test/component/platformstl/diagnostics/stopwatch/entry.cpp` (C++) and `test/unit/winstl/api/internal/C.SystemInformation/entry.c` (C): sectioned includes, forward declarations, `main()`, then implementations.

## Canonical exemplars

- **C++**: `test/component/platformstl/diagnostics/test.component.platformstl.diagnostics.stopwatch/entry.cpp`
- **C**: `test/unit/winstl/api/internal/test.unit.winstl.api.internal.C.SystemInformation/entry.c`

New auto-generated tests should carry a header note: `{AUTO_GEN_NOTE}` (Phase 1+).

## Maintenance scripts (`test/scripts/`)

The scripts under [`test/scripts/`](test/scripts/) are **part of the repository** — commit them alongside `TESTING.md`. They support inventory regeneration, scaffolding, and bulk test normalisation:

| Script | Role |
|--------|------|
| [`audit_tests.py`](test/scripts/audit_tests.py) | Regenerate this inventory (`TESTING.md`) |
| [`scaffold_missing_tests.py`](test/scripts/scaffold_missing_tests.py) | Scaffold missing unit/component test programs |
| [`enhance_stlsoft_tests.py`](test/scripts/enhance_stlsoft_tests.py) | STLSoft-specific test enhancement |
| [`generate_unixstl_tests.py`](test/scripts/generate_unixstl_tests.py) | UnixSTL bulk generation |
| [`generate_platformstl_tests.py`](test/scripts/generate_platformstl_tests.py) | PlatformSTL bulk generation |
| [`setup_winstl_tests.py`](test/scripts/setup_winstl_tests.py) | WinSTL test setup |
| [`fix_failed_tests.py`](test/scripts/fix_failed_tests.py) | Post-run failure fixes |
| [`fix_stlsoft_compile_errors.py`](test/scripts/fix_stlsoft_compile_errors.py) | Compile-error remediation |
| [`update_stlsoft_cmake.py`](test/scripts/update_stlsoft_cmake.py) | CMake list maintenance |

"""


def build_document(rows: list[AuditRow], base: str | None) -> str:
    parts = [
        render_intro(len(rows), base),
        render_legend(),
        render_philosophy(),
        render_rollup(rows),
        render_exclusions(),
    ]

    parts.append("## Per-sub-project inventory\n\n")

    for project in PROJECTS:
        parts.append(f"### {project.upper()}\n\n")
        parts.append(render_project_roots(project, rows))
        for kind in ("unit", "component"):
            subset = [r for r in rows if r.project == project and r.kind == kind]
            title = "Unit tests" if kind == "unit" else "Component tests"
            parts.append(f"#### {title}\n\n")
            parts.append(summarise(subset))
            parts.append(render_table(subset, project))

    # Miscellaneous (e.g. test.unit.versions)
    misc = [r for r in rows if r.project not in PROJECTS]
    if misc:
        parts.append("### Other\n\n")
        parts.append(render_project_roots("other", rows, section_rows=misc))
        parts.append(summarise(misc))
        parts.append(render_table(misc, "other"))

    parts.append(
        "---\n\n"
        "Regenerate: `python3 test/scripts/audit_tests.py`\n"
    )
    return "\n".join(parts)


def main() -> int:
    base = git_merge_base()
    git_status = git_name_status(base) if base else {}

    entries = discover_entries()
    rows = [audit_file(p, git_status) for p in entries]

    doc = build_document(rows, base)
    OUTPUT.write_text(doc, encoding="utf-8")

    # Brief stdout summary
    total = len(rows)
    placeholder = sum(1 for r in rows if r.substance == "placeholder")
    print(f"Wrote {OUTPUT} ({total} programs, {placeholder} placeholders)", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
