#!/usr/bin/env python3
"""Canonical C/C++ automated-test entry layout shared by generator scripts.

``entry.c`` / ``entry.cpp`` are used **only** for unit and component automated
tests (``test.unit.*`` / ``test.component.*``). Scratch and performance
programs keep ``main.c`` / ``main.cpp`` (or other stems such as ``versions.c``).

Exemplar: test/component/platformstl/diagnostics/stopwatch/entry.cpp
"""

from __future__ import annotations

import re
from typing import Iterable

AUTO_GENERATED_DATE = "9th August 2026"
AUTO_GENERATED_NOTE = (
    f"Auto-generated on {AUTO_GENERATED_DATE} (test initiative); "
    "regenerate via test/scripts/ rather than hand-editing layout."
)
HEADER_NOTE_LINE = f" * Note:    {AUTO_GENERATED_NOTE}"


def file_header(
    filepath: str,
    purpose: str,
    *,
    created: str = AUTO_GENERATED_DATE,
    updated: str = AUTO_GENERATED_DATE,
    auto_generated: bool = True,
) -> str:
    note = f"\n{HEADER_NOTE_LINE}" if auto_generated else ""
    return f"""/* /////////////////////////////////////////////////////////////////////////
 * File:    {filepath}
 *
 * Purpose: {purpose}
 *
 * Created: {created}
 * Updated: {updated}{note}
 *
 * ////////////////////////////////////////////////////////////////////// */
"""


def _format_includes(include_lines: Iterable[str]) -> str:
    lines = [ln.strip() for ln in include_lines if ln.strip()]
    if not lines:
        return ""
    return "\n".join(
        ln if ln.startswith("#include") else f"#include {ln}" for ln in lines
    )


def render_cpp(
    *,
    test_name: str,
    purpose: str,
    includes: Iterable[str],
    test_functions: Iterable[str],
    implementations: str,
    setup_before_runner: str = "",
    run_lines: Iterable[str] | None = None,
    names_block: str = "",
    auto_generated: bool = True,
) -> str:
    """Render a canonical C++ entry.cpp.

    ``test_functions`` — names only (e.g. ``test_smoke`` or ``TEST_smoke``).
    ``implementations`` — full ``static void … { … }`` bodies (no wrapping namespace).
    """
    funcs = list(test_functions)
    if not funcs:
        funcs = ["TEST_smoke"]
        if not implementations.strip():
            implementations = """static void TEST_smoke(void)
{
    TEST_PASSED();
}
"""

    decls = "\n".join(f"    static void {fn}(void);" for fn in funcs)
    if run_lines is None:
        runs = "\n".join(f"        XTESTS_RUN_CASE({fn});" for fn in funcs)
    else:
        runs = "\n".join(f"        {line.rstrip().lstrip()}" for line in run_lines)
    include_block = _format_includes(includes)

    setup = f"{setup_before_runner}\n" if setup_before_runner else ""
    names = names_block.strip()
    names_section = ""
    if names:
        names_section = f"""

/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {{

{names}
}} // anonymous namespace
"""

    return f"""{file_header(f"{test_name}/entry.cpp", purpose, auto_generated=auto_generated)}


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

{include_block}


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {{

{decls}
}} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

{setup}    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
{runs}

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}

    return retCode;
}}
{names_section}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {{

{implementations.rstrip()}
}} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
"""


def render_c(
    *,
    test_name: str,
    purpose: str,
    includes: Iterable[str],
    test_functions: Iterable[str],
    implementations: str,
    setup_before_runner: str = "",
    run_lines: Iterable[str] | None = None,
    auto_generated: bool = True,
) -> str:
    """Render a canonical C entry.c (file-scope linkage; exemplar: C.SystemInformation)."""
    funcs = list(test_functions)
    if not funcs:
        funcs = ["TEST_compile_and_link"]
        if not implementations.strip():
            implementations = """static void TEST_compile_and_link(void)
{
    TEST_PASSED();
}
"""
    decls = "\n".join(f"static void {fn}(void);" for fn in funcs)
    if run_lines is None:
        runs = "\n".join(f"        XTESTS_RUN_CASE({fn});" for fn in funcs)
    else:
        runs = "\n".join(f"        {line.rstrip().lstrip()}" for line in run_lines)
    include_block = _format_includes(includes)
    setup = f"{setup_before_runner}\n" if setup_before_runner else ""

    return f"""{file_header(f"{test_name}/entry.c", purpose, auto_generated=auto_generated)}


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

{include_block}


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

{decls}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

{setup}    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
{runs}

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}

    return retCode;
}}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

{implementations.rstrip()}


/* ///////////////////////////// end of file //////////////////////////// */
"""


def render_minimal_c(
    *,
    test_name: str,
    purpose: str,
    primary_include: str,
    auto_generated: bool = True,
) -> str:
    return render_c(
        test_name=test_name,
        purpose=purpose,
        includes=[
            primary_include,
            "<xtests/xtests.h>",
            "<xtests/terse-api.h>",
            "<stlsoft/stlsoft.h>",
            "<stdlib.h>",
        ],
        test_functions=["TEST_compile_and_link"],
        implementations="""static void TEST_compile_and_link(void)
{
    TEST_PASSED();
}
""",
        auto_generated=auto_generated,
    )


def render_minimal_cpp(
    *,
    test_name: str,
    purpose: str,
    primary_include: str,
    auto_generated: bool = True,
) -> str:
    return render_cpp(
        test_name=test_name,
        purpose=purpose,
        includes=[
            primary_include,
            "<xtests/xtests.h>",
            "<xtests/terse-api.h>",
            "<stlsoft/stlsoft.h>",
            "<stdlib.h>",
        ],
        test_functions=["TEST_compile_and_link"],
        implementations="""static void TEST_compile_and_link(void)
{
    TEST_PASSED();
}
""",
        auto_generated=auto_generated,
    )


def forward_decls_from_impl_block(impl_block: str) -> list[str]:
    return re.findall(r"static void (\w+)\s*\(", impl_block)


def wrap_impl_namespace(implementations: str) -> str:
    """Ensure implementations block is raw functions (caller adds namespace)."""
    return implementations.strip() + "\n"
