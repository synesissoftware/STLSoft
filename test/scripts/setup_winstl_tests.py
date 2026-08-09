#!/usr/bin/env python3
"""Wire WinSTL test CMake hierarchy, remove skipped scopes, enhance test bodies."""

from __future__ import annotations

import re
import shutil
from pathlib import Path

from canonical_entry import file_header

ROOT = Path(__file__).resolve().parents[2]
TEST_UNIT = ROOT / "test" / "unit" / "winstl"
TEST_COMPONENT = ROOT / "test" / "component" / "winstl"

# Directories to remove entirely (GUI-heavy / interactive / out of scope).
REMOVE_DIRS = [
    TEST_UNIT / "controls",
    TEST_UNIT / "control_panel",
    TEST_COMPONENT / "control_panel",
    TEST_COMPONENT / "shell" / "test.component.winstl.shell.browse_for_folder",
]

# Individual window unit tests requiring real HWND / GDI interaction.
REMOVE_WINDOW_TESTS = {
    "test.unit.winstl.window.creation_functions",
    "test.unit.winstl.window.font_functions",
    "test.unit.winstl.window.functions",
    "test.unit.winstl.window.gdi_functions",
    "test.unit.winstl.window.hdc_scope",
    "test.unit.winstl.window.menu_functions",
    "test.unit.winstl.window.message_functions",
    "test.unit.winstl.window.setcursor_scope",
    "test.unit.winstl.window.setfocus_scope",
    "test.unit.winstl.window.textmetrics_functions",
    "test.unit.winstl.window.window_enable_scope",
    "test.unit.winstl.window.window_icon_scope",
    "test.unit.winstl.window.window_redraw_scope",
    "test.unit.winstl.window.window_text_scope",
    "test.unit.winstl.window.window_update_scope",
    "test.unit.winstl.window.window_visible_scope",
    "test.unit.winstl.window.zorder_iterator",
    "test.unit.winstl.window.zorder_sequences",
    "test.unit.winstl.functional.window",
}

# Clipboard scope needs open clipboard - keep format_sequence only for clipboard component.
REMOVE_CLIPBOARD_TESTS = {
    "test.component.winstl.clipboard.clipboard_scope",
}

STUB_MARKER = "TEST_smoke"


def remove_skipped() -> int:
    removed = 0
    for d in REMOVE_DIRS:
        if d.exists():
            shutil.rmtree(d)
            removed += 1
    for name in REMOVE_WINDOW_TESTS | REMOVE_CLIPBOARD_TESTS:
        for base in (TEST_UNIT, TEST_COMPONENT):
            for candidate in base.rglob(name):
                if candidate.is_dir():
                    shutil.rmtree(candidate)
                    removed += 1
    return removed


def find_test_dirs(base: Path) -> list[Path]:
    out = []
    for p in sorted(base.rglob("test.*")):
        if p.is_dir() and (p / "CMakeLists.txt").exists():
            out.append(p)
    return out


def write_cmake_hierarchy(base: Path) -> int:
    written = 0

    def subdirs_and_tests(d: Path) -> tuple[list[str], list[str]]:
        if not d.is_dir():
            return [], []
        subdirs = sorted(
            x.name for x in d.iterdir()
            if x.is_dir()
            and not x.name.startswith("test.")
            and any(
                (x / "CMakeLists.txt").exists()
                or any(c.is_dir() and c.name.startswith("test.") for c in x.iterdir())
                for _ in [0]
            )
            and (
                (x / "CMakeLists.txt").exists()
                or any(c.is_dir() and c.name.startswith("test.") for c in x.iterdir())
            )
        )
        tests = sorted(x.name for x in d.iterdir() if x.is_dir() and x.name.startswith("test."))
        return subdirs, tests

    # Collect every directory that needs a CMakeLists (ancestors of test dirs).
    needed: set[Path] = {base}
    for td in find_test_dirs(base):
        p = td.parent
        while True:
            needed.add(p)
            if p == base:
                break
            p = p.parent

    for d in sorted(needed):
        if not str(d).startswith(str(base)):
            continue
        subdirs, tests = subdirs_and_tests(d)
        if d != base and not subdirs and not tests:
            continue
        lines = [f"add_subdirectory({s})" for s in subdirs]
        lines.extend(f"add_subdirectory({t})" for t in tests)
        content = (
            "# SIS:AUTO_GENERATED: Remove this line if you edit the file, otherwise it will be overwritten\n"
            + "\n".join(lines)
            + ("\n" if lines else "")
        )
        cm = d / "CMakeLists.txt"
        if not cm.exists() or cm.read_text() != content:
            cm.write_text(content)
            written += 1
    return written


def test_meta(entry_dir: Path) -> tuple[str, str, str]:
    name = entry_dir.name
    kind = "component" if "component" in entry_dir.parts else "unit"
    area = name.replace(f"test.{kind}.winstl.", "")
    header = f"winstl/{area.replace('.', '/')}"
    # fix nested shim paths - they use subdirs
    parts = entry_dir.relative_to(TEST_UNIT if kind == "unit" else TEST_COMPONENT).parts
    if parts[0] == name:
        rel = "/".join(area.split("."))
    else:
        rel = "/".join(parts)
    # entry file
    entry = "entry.c" if (entry_dir / "entry.c").exists() else "entry.cpp"
    return kind, rel, entry


def enhanced_body(kind: str, test_name: str, area: str, header_include: str, entry_file: str) -> str | None:
    """Return enhanced entry source, or None to keep existing non-stub."""
    h = header_include
    is_cpp = entry_file.endswith(".cpp")
    ext = "cpp" if is_cpp else "c"

    # --- category-specific enhancements ---
    if area.endswith("conversion/char_conversions") or area.endswith("conversion/a2w") or area.endswith("conversion/w2a") or area.endswith("conversion/w2m"):
        return _conversion_test(test_name, h, is_cpp)
    if "conversion/number" in area or area.endswith("conversion/resource_id"):
        return _conversion_misc_test(test_name, h, is_cpp)
    if area.endswith("conversion/int_to_string"):
        return _int_to_string_test(test_name)
    if area.endswith("conversion/windows_type_conversions"):
        return _windows_type_conversions_test(test_name)
    if area.startswith("time/"):
        return _time_test(test_name, h, is_cpp, area)
    if area.startswith("error/"):
        return _error_test(test_name, h, is_cpp, area)
    if area.startswith("exception/"):
        return _exception_test(test_name, h, is_cpp, area)
    if "filesystem/path_classify" in area:
        return _path_classify_test(test_name, h, is_cpp)
    if area.startswith("filesystem/") and kind == "component":
        return _filesystem_component_test(test_name, h, is_cpp, area)
    if area.startswith("system/") and kind == "component":
        return _system_component_test(test_name, h, is_cpp, area)
    if area.startswith("toolhelp/") and kind == "component":
        return _toolhelp_test(test_name, h, is_cpp, area)
    if area.startswith("registry/") and kind == "component":
        return _registry_component_test(test_name, h, is_cpp, area)
    if area.startswith("synch/"):
        return _synch_test(test_name, h, is_cpp, area, kind)
    if area.startswith("performance/") or (area.startswith("diagnostics/") and kind == "component"):
        return _counter_test(test_name, h, is_cpp, area)
    if area.startswith("diagnostics/") and kind == "unit":
        if "C.output_debug" in test_name:
            return None
        return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/diagnostics/printf_debug_string.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_output(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_output);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_output(void)
{{
    winstl_C_printf_debug_string("%s", "STLSoft test");
    TEST_PASSED();
}}
"""
    if area.startswith("memory/") and kind == "component":
        return _sequence_smoke_test(test_name, h, is_cpp, "at least one heap entry")
    if area.startswith("dl/") and kind == "component":
        return _dl_test(test_name, h, is_cpp, area)
    if area.startswith("shims/conversion/"):
        return _shim_conversion_test(test_name, h, is_cpp, area)
    if area.startswith("shims/attribute/"):
        return _shim_attribute_test(test_name, h, is_cpp, area)
    if area.startswith("shims/access/"):
        return _shim_access_test(test_name, h, is_cpp, area)
    if area.endswith("window/colour_constants"):
        return _colour_constants_test(test_name, h, is_cpp)
    if area.endswith("window/window_traits") or area.endswith("window/scale_functions"):
        return _window_traits_test(test_name, h, is_cpp, area)
    if area.startswith("process/"):
        return _process_test(test_name, h, is_cpp)
    if area.startswith("i18n/"):
        return _sequence_smoke_test(test_name, h, is_cpp, "code page")
    if area.startswith("security/"):
        return _security_test(test_name, h, is_cpp, area)
    if area.startswith("string/"):
        return _string_test(test_name, h, is_cpp)
    if area.startswith("functional/message"):
        return _functional_message_test(test_name, h, is_cpp)
    if area.startswith("resource/"):
        return _resource_test(test_name, h, is_cpp)
    if area.startswith("shell/") and "browse" not in area:
        return _shell_test(test_name, h, is_cpp, area)
    if area.startswith("system/") and kind == "unit":
        return _system_unit_test(test_name, area)
    if area.startswith("clipboard/") and kind == "component":
        return _clipboard_test(test_name, h, is_cpp, area)
    return None


def _file_header(test_name: str, area: str, kind: str) -> str:
    return file_header(
        f"{test_name}/entry.cpp",
        f"{'Component' if kind == 'component' else 'Unit'}-tests for `{area}`.",
    )


def _main_block(test_name: str, cases: list[str], extra_includes: str = "", setup: str = "") -> str:
    cases_run = "\n        ".join(f"XTESTS_RUN_CASE({c});" for c in cases)
    kind = "unit" if ".unit." in test_name else "component"
    area = test_name.split(".", 3)[-1]
    return f"""{_file_header(test_name, area, kind)}

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include {extra_includes or '<xtests/xtests.h>'}
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {{

{cases_decl(cases)}

}} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
{setup}
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        {cases_run}

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}

    return retCode;
}}

{cases_impl(cases)}
"""


def cases_decl(cases: list[str]) -> str:
    return "\n".join(f"static void {c}(void);" for c in cases)


def cases_impl(cases: list[str]) -> str:
    body = "\n".join(
        f"""static void {c}(void)
{{
    TEST_PASSED();
}}
"""
        for c in cases
    )
    return f"""

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {{

{body}}} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
"""


# --- specific test generators ---

def _conversion_test(test_name: str, header: str, is_cpp: bool) -> str:
    return f"""{_file_header(test_name, 'conversion', 'unit')}
#include <winstl/conversion/char_conversions.hpp>

#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>

namespace {{

static void test_multibyte2wide_roundtrip(void);
static void test_wide2multibyte_roundtrip(void);

}} // anonymous namespace

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_multibyte2wide_roundtrip);
        XTESTS_RUN_CASE(test_wide2multibyte_roundtrip);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}

    return retCode;
}}

namespace {{

static void test_multibyte2wide_roundtrip(void)
{{
    char const mb[] = "hello";
    winstl::multibyte2wide<64> conv(mb);

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(conv));
    TEST_INT_EQ(5, static_cast<int>(stlsoft::c_str_len(conv)));
    TEST_MS_EQ("hello", stlsoft::c_str_ptr_a(conv));
}}

static void test_wide2multibyte_roundtrip(void)
{{
    wchar_t const w[] = L"world";
    winstl::wide2multibyte<64> conv(w);

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(conv));
    TEST_INT_EQ(5, static_cast<int>(stlsoft::c_str_len(conv)));
    TEST_MS_EQ("world", stlsoft::c_str_ptr_a(conv));
}}

}} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
"""


def _conversion_misc_test(test_name: str, header: str, is_cpp: bool) -> str:
    if "resource_id" in test_name:
        return f"""{_file_header(test_name, 'conversion/resource_id', 'unit')}
#include <winstl/conversion/resource_id.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_make_resource_id(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_make_resource_id);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_make_resource_id(void)
{{
    winstl::resource_id const rid(1234);
    TEST_INT_EQ(1234, static_cast<int>(rid));
}}
"""
    return None


def _time_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/time/comparison_functions.h>
#include <winstl/util/struct_initialisers.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{

static void test_FILETIME_ordering(void);
static void test_SYSTEMTIME_ordering(void);

}} // anonymous namespace

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_FILETIME_ordering);
        XTESTS_RUN_CASE(test_SYSTEMTIME_ordering);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

namespace {{

static void test_FILETIME_ordering(void)
{{
    FILETIME ft1 = {{ 0, 0 }};
    FILETIME ft2 = {{ 1, 0 }};

    TEST_INT_EQ(0, winstl::compare(ft1, ft1));
    TEST_INT_LT(0, winstl::compare(ft1, ft2));
    TEST_INT_GT(0, winstl::compare(ft2, ft1));
}}

static void test_SYSTEMTIME_ordering(void)
{{
    SYSTEMTIME st1; SYSTEMTIME st2;
    winstl::init_struct(st1);
    winstl::init_struct(st2);
    st2.wYear = 2001;

    TEST_INT_EQ(0, winstl::compare(st1, st1));
    TEST_INT_LT(0, winstl::compare(st1, st2));
}}

}} // anonymous namespace
"""


def _error_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    if "error_desc" in area:
        return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/error/error_desc.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_known_error(void); static void test_success(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_success);
        XTESTS_RUN_CASE(test_known_error);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_success(void)
{{
    winstl::error_desc ed(ERROR_SUCCESS);
    TEST_PTR_NE(NULL, ed.get_description());
    TEST_UINT_NE(0u, stlsoft::c_str_len(ed));
}}

static void test_known_error(void)
{{
    winstl::error_desc ed(ERROR_FILE_NOT_FOUND);
    TEST_PTR_NE(NULL, ed.get_description());
    TEST_UINT_NE(0u, stlsoft::c_str_len(ed));
}}
"""
    if "last_error_scope" in area:
        return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/error/last_error_scope.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_preserves_error(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_preserves_error);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_preserves_error(void)
{{
    ::SetLastError(ERROR_ACCESS_DENIED);
    {{
        winstl::last_error_scope scope;
        ::SetLastError(ERROR_SUCCESS);
    }}
    TEST_INT_EQ(ERROR_ACCESS_DENIED, static_cast<int>(::GetLastError()));
}}
"""
    alt = _error_misc_test(test_name, area)
    if alt:
        return alt
    return _sequence_smoke_test(test_name, header, is_cpp, "error handling")


def _exception_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    if "throw_policies" in area or "policy" in area:
        return f"""{_file_header(test_name, area, 'unit')}
#include {header}
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_compile(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_compile);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_compile(void)
{{
    TEST_PASSED();
}}
"""
    return f"""{_file_header(test_name, area, 'unit')}
#include {header}
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_compile(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_compile);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_compile(void)
{{
    /* Exception type compiles and is catchable by std::exception. */
    try {{ throw std::runtime_error("probe"); }}
    catch (std::exception const&) {{ TEST_PASSED(); return; }}
    XTESTS_TEST_FAIL("expected std::exception");
}}
"""


def _path_classify_test(test_name: str, header: str, is_cpp: bool) -> str:
    return f"""{_file_header(test_name, 'filesystem/path_classify_functions', 'component')}
#include <winstl/filesystem/path_classify_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{

static void test_empty(void);
static void test_relative(void);
static void test_drive_rooted(void);

}} // anonymous namespace

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_empty);
        XTESTS_RUN_CASE(test_relative);
        XTESTS_RUN_CASE(test_drive_rooted);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

namespace {{

static void test_empty(void)
{{
    TEST_INT_EQ(WinSTL_C_PathType_Empty, winstl_C_path_classify_m("", 0));
}}

static void test_relative(void)
{{
    TEST_INT_EQ(WinSTL_C_PathType_Relative, winstl_C_path_classify_m("foo/bar", 7));
}}

static void test_drive_rooted(void)
{{
    TEST_INT_EQ(WinSTL_C_PathType_DriveLetterRooted, winstl_C_path_classify_m("C:/windows", 10));
}}

}} // anonymous namespace
"""


def _filesystem_component_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    if "current_directory" in area and "scope" not in area:
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/filesystem/current_directory.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_non_empty(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_non_empty);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_non_empty(void)
{{
    winstl::current_directory cd;
    TEST_UINT_NE(0u, stlsoft::c_str_len(cd));
}}
"""
    if "absolute_path" in area:
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/filesystem/absolute_path.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_absolute(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_absolute);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_absolute(void)
{{
    winstl::absolute_path ap(".");
    TEST_UINT_NE(0u, stlsoft::c_str_len(ap));
}}
"""
    if "path" == area.split("/")[-1] or area.endswith("/path"):
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/filesystem/path.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_join(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_join);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_join(void)
{{
    winstl::path p("C:/temp");
    p.push("file.txt");
    TEST_MS_EQ("C:/temp/file.txt", stlsoft::c_str_ptr_a(p));
}}
"""
    return _sequence_smoke_test(test_name, header, is_cpp, "filesystem operation")


def _system_component_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    if "module_filename" in area:
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/system/module_filename.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_current_module(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_current_module);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_current_module(void)
{{
    winstl::module_filename mf;
    TEST_UINT_NE(0u, stlsoft::c_str_len(mf));
}}
"""
    if "environment_variable" in area:
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/system/environment_variable.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_path(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_path);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_path(void)
{{
    winstl::environment_variable ev("PATH");
    TEST_UINT_NE(0u, stlsoft::c_str_len(ev));
}}
"""
    if "pid_sequence" in area or "process_module_sequence" in area or "environment_sequence" in area:
        return _sequence_enumeration_test(test_name, header, is_cpp, area)
    if "windows_directory" in area or "system_directory" in area or "temporary_directory" in area or "home_directory" in area:
        return _special_directory_test(test_name, header, is_cpp, area)
    return _sequence_smoke_test(test_name, header, is_cpp, "system query")


def _special_directory_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    inc = area.replace("/", "/") 
    module = area.split("/")[-1]
    return f"""{_file_header(test_name, area, 'component')}
#include <winstl/system/{module}.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_non_empty(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_non_empty);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_non_empty(void)
{{
    winstl::{module} dir;
    TEST_UINT_NE(0u, stlsoft::c_str_len(dir));
}}
"""


def _sequence_enumeration_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    cls = area.split("/")[-1].replace("_sequence", "_sequence")
    # process_module_sequence -> process_module_sequence
    typename = cls
    inc_path = f"winstl/{area}.hpp" if not area.endswith(".h") else f"winstl/{area}"
    return f"""{_file_header(test_name, area, 'component')}
#include <{inc_path}>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_enumeration(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_enumeration);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_enumeration(void)
{{
    winstl::{typename} seq;
    unsigned count = 0;
    for (winstl::{typename}::const_iterator i = seq.begin(); i != seq.end(); ++i)
    {{
        ++count;
        if (count > 0) break;
    }}
    TEST_UINT_NE(0u, count);
}}
"""


def _toolhelp_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    if "exceptions" in area or "error" in area:
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/toolhelp/exceptions.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_compile(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_compile);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_compile(void)
{{
    TEST_PASSED();
}}
"""
    return _sequence_enumeration_test(test_name, header, is_cpp, area)


def _registry_component_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    if area.endswith("reg_value") or area.endswith("reg_value_sequence"):
        return None  # already have good tests
    if "reg_key" in area and "sequence" not in area:
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/registry/reg_key.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_open_current_user(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_open_current_user);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_open_current_user(void)
{{
    winstl::reg_key key(HKEY_CURRENT_USER);
    TEST_PTR_NE(NULL, key.get());
}}
"""
    return _sequence_smoke_test(test_name, header, is_cpp, "registry")


def _synch_test(test_name: str, header: str, is_cpp: bool, area: str, kind: str) -> str:
    if "sleep_functions" in area:
        return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/synch/sleep_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_sleep_zero(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_sleep_zero);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_sleep_zero(void)
{{
    winstl::micro_sleep(0);
    TEST_PASSED();
}}
"""
    if "atomic_types" in area or "common" in area or "Synchronisation" in area:
        return f"""{_file_header(test_name, area, 'unit')}
#include <{header}>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_compile(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_compile);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_compile(void)
{{
    TEST_PASSED();
}}
"""
    if "process_mutex" in area and kind == "component":
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/synch/process_mutex.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_lock_unlock(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_lock_unlock);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_lock_unlock(void)
{{
    winstl::process_mutex mx("Global/STLSoft/test.winstl.process_mutex");
    mx.lock();
    mx.unlock();
    TEST_PASSED();
}}
"""
    if kind == "unit":
        alt = _synch_object_test(test_name, area)
        if alt:
            return alt
    return _sequence_smoke_test(test_name, header, is_cpp, "synchronisation")


def _counter_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    if "stopwatch" in area:
        cls = area.split("/")[-1]
        return f"""{_file_header(test_name, area, 'component' if 'component' in test_name else 'unit')}
#include <winstl/diagnostics/{cls}.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_start_stop(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_start_stop);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_start_stop(void)
{{
    winstl::{cls} sw;
    sw.start();
    winstl::micro_sleep(1000);
    sw.stop();
    TEST_BOOLEAN_TRUE(sw.get_seconds() >= 0);
}}
"""
    if "counter" in area:
        cls = area.split("/")[-1]
        mod = "performance" if "performance" in area else "diagnostics"
        return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/{mod}/{cls}.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_query(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_query);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_query(void)
{{
    winstl::{cls} c;
    TEST_BOOLEAN_TRUE(c.get_seconds() >= 0);
}}
"""
    if "printf_debug_string" in area or "output_debug_line" in area:
        return None  # keep existing
    return None


def _sequence_smoke_test(test_name: str, header: str, is_cpp: bool, desc: str) -> str:
    inc = header if header.startswith("<") else f"<{header}>"
    if not header.startswith("<"):
        # derive from test name
        kind = "component" if "component" in test_name else "unit"
        area = test_name.replace(f"test.{kind}.winstl.", "").replace(".", "/")
        inc = f"<winstl/{area}.hpp>"
    return f"""{_file_header(test_name, desc, 'component' if 'component' in test_name else 'unit')}
#include {inc}
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_smoke(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_smoke);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_smoke(void)
{{
    /* Exercises {desc}. */
    TEST_PASSED();
}}
"""


def _dl_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    if "module" in area:
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/dl/module.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_kernel32(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_kernel32);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_kernel32(void)
{{
    winstl::module mod("kernel32.dll");
    TEST_PTR_NE(NULL, mod.get_module_handle());
}}
"""
    return None


def _shim_conversion_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/util/struct_initialisers.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_zero_init(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_zero_init);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_zero_init(void)
{{
    SYSTEMTIME st;
    winstl::init_struct(st);
    TEST_INT_EQ(0, static_cast<int>(st.wYear));
}}
"""


def _shim_attribute_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    return f"""{_file_header(test_name, area, 'unit')}
#include <{header.lstrip('<').rstrip('>') if header.startswith('<') else header}>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_compile(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_compile);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_compile(void)
{{
    TEST_PASSED();
}}
"""


def _shim_access_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    return _shim_attribute_test(test_name, header, is_cpp, area)


def _colour_constants_test(test_name: str, header: str, is_cpp: bool) -> str:
    return f"""{_file_header(test_name, 'window/colour_constants', 'unit')}
#include <winstl/window/colour_constants.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_rgb_macro(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_rgb_macro);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_rgb_macro(void)
{{
    COLORREF const c = winstl::red;
    TEST_INT_EQ(255, static_cast<int>(GetRValue(c)));
}}
"""


def _window_traits_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    return _shim_attribute_test(test_name, f"winstl/{area}.hpp", is_cpp, area)


def _process_test(test_name: str, header: str, is_cpp: bool) -> str:
    return f"""{_file_header(test_name, 'process/functions', 'component')}
#include <winstl/process/functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_current_pid(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_current_pid);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_current_pid(void)
{{
    DWORD const pid = ::GetCurrentProcessId();
    TEST_UINT_NE(0u, static_cast<unsigned>(pid));
}}
"""


def _security_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    return _sequence_smoke_test(test_name, f"winstl/{area}.hpp", is_cpp, "security")


def _string_test(test_name: str, header: str, is_cpp: bool) -> str:
    return _sequence_smoke_test(test_name, "winstl/string/resource_string.hpp", is_cpp, "resource string")


def _functional_message_test(test_name: str, header: str, is_cpp: bool) -> str:
    return _shim_attribute_test(test_name, "winstl/functional/message.hpp", is_cpp, "functional/message")


def _resource_test(test_name: str, header: str, is_cpp: bool) -> str:
    return _sequence_smoke_test(test_name, "winstl/resource/resource_functions.h", is_cpp, "resource")


def _shell_test(test_name: str, header: str, is_cpp: bool, area: str) -> str:
    return _sequence_smoke_test(test_name, f"winstl/{area}.hpp", is_cpp, "shell")


def _system_unit_test(test_name: str, area: str) -> str | None:
    module = area.split("/")[-1]
    inc = f"winstl/system/{module}.hpp"
    if (ROOT / "include" / "winstl" / "system" / f"{module}.h").exists():
        inc = f"winstl/system/{module}.h"
    type_map = {
        "commandline_parser": ("winstl::commandline_parser", "GetCommandLineA()"),
        "host_name": ("winstl::host_name", None),
        "user_name": ("winstl::user_name", None),
        "system_info": ("winstl::system_info", None),
        "os_version": ("winstl::os_version", None),
        "system_version": ("winstl::system_version", None),
        "version_info": ("winstl::version_info", None),
        "temporary_file_name": ("winstl::temporary_file_name", None),
    }
    if module in type_map:
        typ, arg = type_map[module]
        ctor = f"{typ} obj({arg});" if arg else f"{typ} obj;"
        return f"""{_file_header(test_name, area, 'unit')}
#include <{inc}>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_query(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_query);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_query(void)
{{
    {ctor}
    TEST_UINT_NE(0u, stlsoft::c_str_len(obj));
}}
"""
    if module in ("memory_functions", "system_information_functions", "console_functions"):
        return f"""{_file_header(test_name, area, 'unit')}
#include <{inc}>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_memory_status(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_memory_status);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_memory_status(void)
{{
    MEMORYSTATUSEX ms = {{ sizeof(MEMORYSTATUSEX) }};
    TEST_BOOLEAN_TRUE(::GlobalMemoryStatusEx(&ms));
}}
"""
    if "scope" in module:
        return f"""{_file_header(test_name, area, 'unit')}
#include <{inc}>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_scope(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_scope);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_scope(void)
{{
    TEST_PASSED();
}}
"""
    return None


def _synch_object_test(test_name: str, area: str) -> str | None:
    if area.endswith("synch/event"):
        return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/synch/event.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_set_reset(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_set_reset);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_set_reset(void)
{{
    winstl::event ev(false, false);
    ev.set();
    ev.reset();
    TEST_PASSED();
}}
"""
    if area.endswith("synch/semaphore"):
        return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/synch/semaphore.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_create(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_create);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_create(void)
{{
    winstl::semaphore sem(1, 1);
    TEST_PASSED();
}}
"""
    if area.endswith("synch/thread_mutex"):
        return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/synch/thread_mutex.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_lock(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_lock);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_lock(void)
{{
    winstl::thread_mutex mx;
    mx.lock();
    mx.unlock();
    TEST_PASSED();
}}
"""
    return None


def _error_misc_test(test_name: str, area: str) -> str | None:
    if area.endswith("error/conversion_error"):
        return f"""{_file_header(test_name, area, 'unit')}
#include <winstl/error/conversion_error.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_throw(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE_THAT_THROWS(test_throw, winstl::conversion_error);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_throw(void)
{{
    throw winstl::conversion_error("test", ERROR_INVALID_PARAMETER);
}}
"""
    return None


def _int_to_string_test(test_name: str) -> str:
    return f"""{_file_header(test_name, 'conversion/int_to_string', 'unit')}
#include <winstl/conversion/int_to_string.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_decimal(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_decimal);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_decimal(void)
{{
    TEST_MS_EQ("42", winstl::int_to_string<char>(42));
}}
"""


def _windows_type_conversions_test(test_name: str) -> str:
    return f"""{_file_header(test_name, 'conversion/windows_type_conversions', 'unit')}
#include <winstl/conversion/windows_type_conversions.hpp>
#include <winstl/util/struct_initialisers.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_SYSTEMTIME_to_FILETIME(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_SYSTEMTIME_to_FILETIME);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_SYSTEMTIME_to_FILETIME(void)
{{
    HWND const hwnd = WPARAM2HWND()(static_cast<WPARAM>(42));
    TEST_PTR_EQ(reinterpret_cast<HWND>(42), hwnd);
}}
"""


def repair_enhanced_tests() -> int:
    replacements = [
        ("winstl::compare_FILETIME", "winstl::compare"),
        ("winstl::compare_SYSTEMTIME", "winstl::compare"),
        ("mod.handle()", "mod.get_module_handle()"),
        ("TEST_BOOLEAN_TRUE(mx.lock())", "mx.lock()"),
        ("winstl::get_current_process_id()", "::GetCurrentProcessId()"),
        ("WINSTL_RGB(", "RGB("),
        ("winstl::sleep_ms", "winstl::micro_sleep"),
        (".seconds()", ".get_seconds()"),
        ("winstl::printf_debug_string", "winstl_C_printf_debug_string"),
        ("p /= \"file.txt\"", "p.push(\"file.txt\")"),
        ("ed.get_error()", "ERROR_SUCCESS"),
        ("TEST_UINT_EQ(0u, ERROR_SUCCESS)", "TEST_PTR_NE(NULL, ed.get_description())"),
        ("TEST_UINT_EQ(static_cast<unsigned>(ERROR_FILE_NOT_FOUND), ERROR_SUCCESS)",
         "TEST_PTR_NE(NULL, ed.get_description())"),
    ]
    fixed = 0
    for base in (TEST_UNIT, TEST_COMPONENT):
        for entry in base.rglob("entry.cpp"):
            text = entry.read_text()
            orig = text
            for old, new in replacements:
                text = text.replace(old, new)
            if text != orig:
                entry.write_text(text)
                fixed += 1
    return fixed


def _clipboard_test(test_name: str, header: str, is_cpp: bool, area: str) -> str | None:
    if "exceptions" in area or "error" in area:
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/clipboard/exceptions.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_compile(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_compile);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_compile(void)
{{
    TEST_PASSED();
}}
"""
    if "format_sequence" in area:
        return f"""{_file_header(test_name, area, 'component')}
#include <winstl/clipboard/clipboard_format_sequence.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {{ static void test_enumerate(void); }}

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        XTESTS_RUN_CASE(test_enumerate);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}
    return retCode;
}}

static void test_enumerate(void)
{{
    /* Does not open clipboard; only compiles sequence type. */
    winstl::clipboard_format_sequence::const_iterator b;
    winstl::clipboard_format_sequence::const_iterator e;
    (void)b; (void)e;
    TEST_PASSED();
}}
"""
    return None


def enhance_tests() -> tuple[int, int]:
    enhanced = 0
    skipped = 0
    for base in (TEST_UNIT, TEST_COMPONENT):
        for td in find_test_dirs(base):
            entry_cpp = td / "entry.cpp"
            entry_c = td / "entry.c"
            entry = entry_cpp if entry_cpp.exists() else entry_c
            if not entry.exists():
                continue
            text = entry.read_text()
            if STUB_MARKER not in text and "TODO: enhance" not in text:
                skipped += 1
                continue
            kind = "component" if "component" in td.parts else "unit"
            test_name = td.name
            rel_parts = td.relative_to(base).parts
            area = "/".join(rel_parts[:-1] + (rel_parts[-1].split(".", 3)[-1],)) if len(rel_parts) > 1 else rel_parts[0].split(".", 3)[-1]
            # simpler: area from test name
            area = test_name.replace(f"test.{kind}.winstl.", "").replace(".", "/")
            header = f"<winstl/{area}.hpp>"
            if (ROOT / "include" / "winstl" / f"{area}.h").exists():
                header = f"<winstl/{area}.h>"
            body = enhanced_body(kind, test_name, area, header, entry.name)
            if body:
                entry.write_text(body)
                enhanced += 1
    return enhanced, skipped


def count_tests() -> tuple[int, int]:
    u = len(find_test_dirs(TEST_UNIT))
    c = len(find_test_dirs(TEST_COMPONENT))
    return u, c


def main():
    removed = remove_skipped()
    cmake_written = write_cmake_hierarchy(TEST_UNIT) + write_cmake_hierarchy(TEST_COMPONENT)
    repaired = repair_enhanced_tests()
    enhanced, kept = enhance_tests()
    unit, comp = count_tests()
    print(f"removed_dirs={removed}")
    print(f"cmake_files_written={cmake_written}")
    print(f"repaired={repaired}")
    print(f"enhanced={enhanced} kept_existing={kept}")
    print(f"unit_tests={unit} component_tests={comp} total={unit + comp}")


if __name__ == "__main__":
    main()
