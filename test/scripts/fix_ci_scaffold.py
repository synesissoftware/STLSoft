#!/usr/bin/env python3
"""Mechanical fixes for CI scaffold errors in generated test entry.cpp files."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TEST_ROOTS = [ROOT / "test" / "unit", ROOT / "test" / "component"]

INCLUDE_REPLACEMENTS = {
    "winstl/clipboard/exceptions.hpp": "winstl/clipboard/error/exceptions.hpp",
    "winstl/registry/defs.hpp": "winstl/registry/util/defs.hpp",
    "winstl/registry/exceptions.hpp": "winstl/registry/error/exceptions.hpp",
    "winstl/registry/shared_handles.hpp": "winstl/registry/util/shared_handles.hpp",
    "winstl/toolhelp/exceptions.hpp": "winstl/toolhelp/error/exceptions.hpp",
    "winstl/resource/resource_functions.hpp": "winstl/resource/resource_functions.h",
    "winstl/security/functions.hpp": "winstl/security/functions.h",
    "winstl/shell/memory/functions.hpp": "winstl/shell/memory/functions.h",
    "winstl/shell/memory_functions.hpp": "winstl/shell/memory_functions.h",
    "winstl/window/scale_functions.hpp": "winstl/window/scale_functions.h",
}


def iter_entries() -> list[Path]:
    files: list[Path] = []
    for base in TEST_ROOTS:
        files.extend(base.rglob("entry.cpp"))
    return sorted(files)


def fix_double_angle(text: str) -> str:
    return re.sub(r"#include\s+<<([^>]+)>>", r"#include <\1>", text)


def fix_include_paths(text: str) -> str:
    for old, new in INCLUDE_REPLACEMENTS.items():
        text = text.replace(f"<{old}>", f"<{new}>")
    return text


def ensure_xtests_h(text: str) -> str:
    if "TEST_UINT_NE" not in text and "TEST_UINT_EQ" not in text:
        return text
    if "#include <xtests/xtests.h>" in text:
        return text
    if "#include <xtests/terse-api.h>" in text:
        return text.replace(
            "#include <xtests/terse-api.h>",
            "#include <xtests/xtests.h>\n#include <xtests/terse-api.h>",
            1,
        )
    return text


def ensure_sleep_functions(text: str) -> str:
    if "winstl::micro_sleep" not in text:
        return text
    inc = "#include <winstl/synch/sleep_functions.h>"
    if inc in text:
        return text
    # After first winstl include
    m = re.search(r"(#include <winstl/[^>]+>\n)", text)
    if m:
        pos = m.end()
        return text[:pos] + inc + "\n" + text[pos:]
    return text


def fix_single_line_anon_fwd(text: str) -> str:
    """namespace { static void foo(void); } -> static void foo(void);"""
    return re.sub(
        r"namespace\s*\{\s*static\s+void\s+(\w+)\(void\);\s*\}",
        r"static void \1(void);",
        text,
    )


def wrap_post_main_impls_in_anon_namespace(text: str) -> str:
    """If forward decls are in anon namespace but impls are at file scope, wrap impls."""
    if not re.search(
        r"namespace \{\s*\n\s*static void (?:test_|TEST_)",
        text,
    ):
        return text
    if re.search(r"^static void (?:test_|TEST_)\w+\(void\);\s*\n\s*\nint main", text, re.M):
        return text

    # Already has implementation section inside anonymous namespace after main.
    if re.search(
        r"return retCode;\s*\}\s*\n\s*namespace\s*\{[\s\S]*static void (?:test_|TEST_)",
        text,
    ):
        return text

    m_main_end = re.search(r"(return retCode;\s*\}\s*\n)", text)
    if not m_main_end:
        return text

    tail = text[m_main_end.end() :]
    if not re.match(r"\s*static void (?:test_|TEST_)", tail):
        return text

    # Only wrap when forward declarations used anonymous namespace.
    if not re.search(
        r"namespace\s*\{[\s\S]*?static void (?:test_|TEST_)[\s\S]*?\}\s*//\s*anonymous namespace",
        text[: m_main_end.start()],
    ):
        return text

    end_marker = "/* ///////////////////////////// end of file //////////////////////////// */"
    end_idx = tail.find(end_marker)
    body = tail[:end_idx] if end_idx != -1 else tail
    suffix = tail[end_idx:] if end_idx != -1 else ""

    body_stripped = body.rstrip()
    if body_stripped.startswith("namespace {"):
        return text

    wrapped = "\nnamespace {\n\n" + body_stripped + "\n\n} // anonymous namespace\n\n" + suffix
    return text[: m_main_end.end()] + wrapped


def fix_unistd_platform(text: str, path: Path) -> str:
    if "unistd.h" not in text:
        return text
    if "#if defined(_WIN32)" in text or "#ifndef _WIN32" in text:
        return text
    text = text.replace(
        "#include <unistd.h>\n",
        "#ifndef _WIN32\n#include <unistd.h>\n#endif\n",
    )
    return text


def fix_inetstl_is_bool_t(text: str, path: Path) -> str:
    if "network.connection" not in str(path):
        return text
    return text.replace("    is_bool_t const r =", "    stlsoft::ss_bool_t const r =")


def fix_lsa_unicode_string(text: str, path: Path) -> str:
    if "LSA_UNICODE_STRING" not in str(path):
        return text
    if "ntsecapi.h" in text:
        return text
    needle = "#include <winstl/shims/access/string/LSA_UNICODE_STRING.hpp>"
    return text.replace(
        needle,
        "#include <ntsecapi.h>\n" + needle,
    )


def fix_com_enumerator_sequence(text: str, path: Path) -> str:
    if "enumerator_sequence" not in str(path):
        return text
    if "#include <objbase.h>" in text or "#include <windows.h>" in text:
        return text
    insert = "#include <objbase.h>\n"
    return text.replace(
        "#include <comstl/collections/enumerator_sequence.hpp>\n",
        "#include <comstl/collections/enumerator_sequence.hpp>\n" + insert,
    )


def process_file(path: Path) -> bool:
    original = path.read_text(encoding="utf-8")
    text = original
    text = fix_double_angle(text)
    text = fix_include_paths(text)
    text = ensure_xtests_h(text)
    text = ensure_sleep_functions(text)
    text = fix_single_line_anon_fwd(text)
    text = wrap_post_main_impls_in_anon_namespace(text)
    text = fix_unistd_platform(text, path)
    text = fix_inetstl_is_bool_t(text, path)
    text = fix_lsa_unicode_string(text, path)
    text = fix_com_enumerator_sequence(text, path)
    if text != original:
        path.write_text(text, encoding="utf-8")
        return True
    return False


def main() -> int:
    changed = [p for p in iter_entries() if process_file(p)]
    print(f"Updated {len(changed)} entry.cpp file(s)")
    for p in changed:
        print(f"  {p.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
