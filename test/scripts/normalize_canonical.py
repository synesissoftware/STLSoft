#!/usr/bin/env python3
"""Mechanically normalise generated test entry.cpp files to canonical layout.

Targets files created during the 2026 test initiative (default) or any
non-canonical entry when --all is passed. Preserves includes, test bodies,
and main() setup code; reorders into:

  forward declarations (anonymous namespace) -> main() -> implementations
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SCRIPTS = Path(__file__).resolve().parent
sys.path.insert(0, str(SCRIPTS))

from audit_tests import is_canonical  # noqa: E402
from canonical_entry import AUTO_GENERATED_NOTE, render_cpp  # noqa: E402

GENERATED_MARKER = "Created: 9th August 2026"
FUNC_START = re.compile(r"static void (\w+)\s*\([^)]*\)\s*\{")
STATIC_FUNC_START = re.compile(
    r"static\s+(?:inline\s+)?(?:[\w:<>,\s\*&]+\s+)+\s*(\w+)\s*\([^)]*\)\s*\{"
)


def extract_includes(text: str) -> list[str]:
    return re.findall(r"^#include\s+.+$", text, re.MULTILINE)


def extract_purpose(text: str) -> str:
    m = re.search(r"^\s*\*\s*Purpose:\s*(.+)$", text, re.MULTILINE)
    return m.group(1).strip() if m else "Unit-tests for component."


def extract_runner(text: str) -> str | None:
    m = re.search(r'XTESTS_START_RUNNER\("([^"]+)"', text)
    return m.group(1) if m else None


def extract_cases(text: str) -> list[str]:
    main_m = re.search(r"\bmain\s*\(", text)
    if not main_m:
        return []
    after_main = text[main_m.start() :]
    cases = re.findall(r"XTESTS_RUN_CASE\((\w+)\)", after_main)
    cases += re.findall(r"XTESTS_RUN_CASE_THAT_THROWS\((\w+)", after_main)
    return cases


def extract_run_lines(text: str) -> list[str]:
    main_m = re.search(r"\bmain\s*\(", text)
    if not main_m:
        return []
    after_main = text[main_m.start() :]
    return re.findall(
        r"^\s+(XTESTS_RUN_CASE(?:_THAT_THROWS)?\([^;]+;)\s*$",
        after_main,
        re.MULTILINE,
    )


def extract_main_setup(text: str) -> str:
    m = re.search(
        r"int main\s*\([^)]*\)\s*\{(.*?)\s*if\s*\(\s*XTESTS_START_RUNNER",
        text,
        re.DOTALL,
    )
    if not m:
        return ""
    setup_lines: list[str] = []
    for line in m.group(1).splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("//"):
            continue
        if re.match(r"int retCode\s*=", stripped):
            continue
        if re.match(r"int verbosity\s*=", stripped):
            continue
        if "XTESTS_COMMANDLINE_PARSEVERBOSITY" in stripped:
            continue
        setup_lines.append(line.rstrip())
    if not setup_lines:
        return ""
    return "\n".join(setup_lines) + "\n"


def extract_function_bodies(text: str) -> dict[str, str]:
    return _extract_bodies(text, FUNC_START)


def extract_static_function_bodies(text: str) -> dict[str, str]:
    return _extract_bodies(text, STATIC_FUNC_START)


def _extract_bodies(text: str, pattern: re.Pattern[str]) -> dict[str, str]:
    bodies: dict[str, str] = {}
    for m in pattern.finditer(text):
        name = m.group(1)
        if name == "main":
            continue
        start = m.start()
        brace = m.end() - 1
        depth = 0
        for i in range(brace, len(text)):
            ch = text[i]
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth == 0:
                    bodies[name] = text[start : i + 1]
                    break
    return bodies


def _anonymous_namespace_blocks(text: str) -> list[str]:
    blocks: list[str] = []
    for m in re.finditer(r"namespace\s*\{", text):
        i = m.end()
        depth = 1
        start = i
        while i < len(text):
            ch = text[i]
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth == 0:
                    blocks.append(text[start:i])
                    break
            i += 1
    return blocks


def _strip_test_functions(block: str) -> str:
    out = block
    matches = list(FUNC_START.finditer(out))
    for m in reversed(matches):
        start = m.start()
        brace = m.end() - 1
        depth = 0
        for i in range(brace, len(out)):
            ch = out[i]
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
                if depth == 0:
                    out = out[:start] + out[i + 1 :]
                    break
    out = re.sub(r"static void \w+\s*\([^)]*\)\s*;", "", out)
    return out


def _collect_using_typedef_lines(block: str) -> list[str]:
    lines: list[str] = []
    in_typedef = False
    for line in block.splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("//"):
            continue
        if stripped.startswith("using "):
            in_typedef = False
            lines.append(line.rstrip())
        elif stripped.startswith("typedef "):
            lines.append(line.rstrip())
            in_typedef = ";" not in stripped
        elif in_typedef:
            lines.append(line.rstrip())
            if ";" in stripped:
                in_typedef = False
    return lines


def extract_names_block(text: str, *, case_names: set[str] | None = None) -> str:
    """Extract using/typedef declarations and non-test helper functions."""
    cases = case_names or set()
    chunks: list[str] = []
    seen: set[str] = set()
    for block in _anonymous_namespace_blocks(text):
        lines = _collect_using_typedef_lines(_strip_test_functions(block))
        if lines:
            chunk = "\n".join(lines)
            if chunk not in seen:
                seen.add(chunk)
                chunks.append(chunk)
        for name, body in extract_static_function_bodies(block).items():
            if name in cases or name == "main":
                continue
            if body not in seen:
                seen.add(body)
                chunks.append(body)
    return "\n\n".join(chunks)


def ensure_xtests_include(includes: list[str], implementations: str) -> list[str]:
    need_xtests = any(
        tok in implementations
        for tok in ("TEST_UINT_", "TEST_INT_", "TEST_CHAR_", "TEST_PTR_", "TEST_LONG_")
    )
    if not need_xtests:
        return includes
    if any("xtests/xtests.h" in inc for inc in includes):
        return includes
    out = list(includes)
    insert_at = 0
    for i, inc in enumerate(out):
        if "xtests/" in inc:
            insert_at = i
            break
        if "stlsoft" in inc or "stdlib" in inc:
            insert_at = i
    out.insert(insert_at, "#include <xtests/xtests.h>")
    return out


def normalize_text(
    text: str, *, force: bool = False, names_override: str | None = None
) -> str | None:
    if not force and is_canonical(text, is_cpp=True):
        return None

    runner = extract_runner(text)
    if not runner:
        return None

    cases = extract_cases(text)
    if not cases:
        return None

    bodies = extract_function_bodies(text)
    missing = [c for c in cases if c not in bodies]
    if missing:
        return None

    implementations = "\n\n".join(bodies[c] for c in cases)
    includes = ensure_xtests_include(extract_includes(text), implementations)
    setup = extract_main_setup(text)
    purpose = extract_purpose(text)
    run_lines = extract_run_lines(text)
    if names_override is not None:
        names_block = names_override
    else:
        names_block = extract_names_block(text, case_names=set(cases))

    return render_cpp(
        test_name=runner,
        purpose=purpose,
        includes=includes,
        test_functions=cases,
        implementations=implementations,
        setup_before_runner=setup,
        run_lines=run_lines or None,
        names_block=names_block,
        auto_generated=GENERATED_MARKER in text,
    )


def iter_entries() -> list[Path]:
    paths: list[Path] = []
    for base in (ROOT / "test" / "unit", ROOT / "test" / "component"):
        if base.exists():
            paths.extend(sorted(base.rglob("entry.cpp")))
    return paths


def repair_names_from_git(*, dry_run: bool, verbose: bool) -> int:
    """Re-normalise generated tests, restoring using/typedef names from git HEAD."""
    changed = 0
    for path in iter_entries():
        if GENERATED_MARKER not in path.read_text(encoding="utf-8", errors="replace"):
            continue
        rel = path.relative_to(ROOT).as_posix()
        current = path.read_text(encoding="utf-8", errors="replace")
        head = None
        try:
            head = subprocess.check_output(
                ["git", "show", f"HEAD:{rel}"],
                text=True,
                cwd=ROOT,
            )
        except subprocess.CalledProcessError:
            pass
        names = extract_names_block(head, case_names=set(extract_cases(head))) if head else ""
        repaired = normalize_text(current, force=True, names_override=names)
        if not repaired or repaired == current:
            continue
        changed += 1
        if verbose or dry_run:
            print(f"{'would repair' if dry_run else 'repair'}: {rel}")
        if not dry_run:
            path.write_text(repaired, encoding="utf-8")
    print(f"done: {changed} files repaired")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--all",
        action="store_true",
        help="Normalise any non-canonical entry.cpp (default: 9th August 2026 only)",
    )
    parser.add_argument("--dry-run", action="store_true", help="Report only, do not write")
    parser.add_argument("--verbose", "-v", action="store_true")
    parser.add_argument(
        "--repair-names-from-git",
        action="store_true",
        help="Restore using/typedef names stripped by an earlier normalize pass (reads HEAD)",
    )
    args = parser.parse_args()

    if args.repair_names_from_git:
        return repair_names_from_git(dry_run=args.dry_run, verbose=args.verbose)

    changed = 0
    skipped_canonical = 0
    skipped_unhandled = 0

    for path in iter_entries():
        text = path.read_text(encoding="utf-8", errors="replace")
        if not args.all and GENERATED_MARKER not in text:
            continue
        if is_canonical(text, is_cpp=True):
            skipped_canonical += 1
            continue
        new_text = normalize_text(text)
        if new_text is None:
            skipped_unhandled += 1
            if args.verbose:
                print(f"skip (unhandled): {path.relative_to(ROOT)}")
            continue
        if new_text == text:
            skipped_canonical += 1
            continue
        changed += 1
        if args.verbose or args.dry_run:
            print(f"{'would update' if args.dry_run else 'update'}: {path.relative_to(ROOT)}")
        if not args.dry_run:
            path.write_text(new_text, encoding="utf-8")

    print(
        f"done: {changed} updated, {skipped_canonical} already canonical, "
        f"{skipped_unhandled} unhandled"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
