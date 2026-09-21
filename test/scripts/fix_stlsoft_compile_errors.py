#!/usr/bin/env python3
"""Apply compile-verified fixes to stlsoft test entry.cpp files."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

# area_path -> test body (function implementations)
FIXES: dict[str, str] = {
    "algorithms/pod": """
static void test_pod_copy()
{
    int src[] = { 10, 20, 30 };
    int dest[3] = {};
    stlsoft::pod_copy(&src[0], &src[3], &dest[0]);
    TEST_INTEGER_EQUAL(10, dest[0]);
    TEST_INTEGER_EQUAL(20, dest[1]);
    TEST_INTEGER_EQUAL(30, dest[2]);
}
""",
    "algorithms/unordered": """
static void test_find_first_duplicate()
{
    int arr[] = { 1, 2, 3, 2, 4 };
    std::pair<int*, int*> r = stlsoft::find_first_duplicate(&arr[0], &arr[5]);
    TEST_PTR_EQ(&arr[1], r.first);
    TEST_PTR_EQ(&arr[3], r.second);
}
""",
    "algorithms/std/alt": """
static void test_alt_find()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int* p = stlsoft::find(&arr[0], &arr[5], 3);
    TEST_PTR_EQ(&arr[2], p);
}
""",
    "algorithms/std/ext": """
static void test_ext_for_each_if()
{
    int arr[] = { 1, 2, 3, 4 };
    int sum = 0;
    stlsoft::for_each_if(&arr[0], &arr[4], [&sum](int v) { sum += v; return v; }, [](int v) { return v > 2; });
    TEST_INTEGER_EQUAL(7, sum);
}
""",
    "containers/fixed_array": """
static void test_fixed_array_1d()
{
    stlsoft::fixed_array_1d<int> arr(4, 7);
    TEST_INTEGER_EQUAL(4, static_cast<int>(arr.size()));
    TEST_INTEGER_EQUAL(7, arr[0]);
    arr[2] = 42;
    TEST_INTEGER_EQUAL(42, arr[2]);
}
""",
    "containers/unsorted_map": """
static void test_unsorted_map_push_back()
{
    stlsoft::unsorted_map<int, int> m;
    m.push_back(1, 10);
    m.push_back(2, 20);
    TEST_INTEGER_EQUAL(2, static_cast<int>(m.size()));
    TEST_INTEGER_EQUAL(10, m[0].second);
    TEST_INTEGER_EQUAL(20, m[1].second);
}
""",
    "containers/util/array_policies": """
static void test_do_construction_int_is_false()
{
    TEST_BOOLEAN_FALSE(stlsoft::do_construction<int>::value);
}
""",
    "conversion/ptr_cast": """
static void test_ptr_cast_pointer()
{
    int x = 42;
    int* p = &x;
    int* q = stlsoft::ptr_cast<int*>(p);
    TEST_PTR_EQ(p, q);
    TEST_INTEGER_EQUAL(42, *q);
}
""",
    "conversion/integer_to_string/integer_to_zeropadded_decimal_string": """
static void test_integer_to_zeropadded_decimal_string()
{
    char buf[32];
    ss_size_t numWritten = 0;
    stlsoft::uint32_t const val = 7;
    char const* s = stlsoft::integer_to_zeropadded_decimal_string(buf, STLSOFT_NUM_ELEMENTS(buf), val, 5, &numWritten);
    TEST_MS_EQ("00007", s);
    TEST_INTEGER_EQUAL(5, static_cast<int>(numWritten));
}
""",
    "conversion/string_to_bool": """
static void test_try_parse_to_bool()
{
    bool result = false;
    TEST_BOOLEAN_TRUE(stlsoft::try_parse_to_bool("true", &result));
    TEST_BOOLEAN_TRUE(result);
    result = true;
    TEST_BOOLEAN_TRUE(stlsoft::try_parse_to_bool("false", &result));
    TEST_BOOLEAN_FALSE(result);
}
""",
    "conversion/integer_to_string": """
static void test_integer_to_decimal_string()
{
    char buf[32];
    char const* s = stlsoft::integer_to_decimal_string(buf, STLSOFT_NUM_ELEMENTS(buf), 99);
    TEST_PTR_NE(NULL, s);
    TEST_MS_EQ("99", s);
}
""",
    "conversion/integer_to_string/integer_to_decimal_string": """
static void test_integer_to_decimal_string()
{
    char buf[32];
    char const* s = stlsoft::integer_to_decimal_string(buf, STLSOFT_NUM_ELEMENTS(buf), 12345);
    TEST_MS_EQ("12345", s);
}
""",
    "conversion/integer_to_string/integer_to_hexadecimal_string": """
static void test_integer_to_hexadecimal_string()
{
    char buf[32];
    char const* s = stlsoft::integer_to_hexadecimal_string(buf, STLSOFT_NUM_ELEMENTS(buf), 0xAB);
    TEST_MS_EQ("ab", s);
}
""",
    "conversion/integer_to_string/integer_to_octal_string": """
static void test_integer_to_octal_string()
{
    char buf[32];
    char const* s = stlsoft::integer_to_octal_string(buf, STLSOFT_NUM_ELEMENTS(buf), 8);
    TEST_MS_EQ("10", s);
}
""",
    "conversion/integer_to_string/integer_to_zeropadded_decimal_string": """
static void test_integer_to_zeropadded_decimal_string()
{
    char buf[32];
    char const* s = stlsoft::integer_to_zeropadded_decimal_string(buf, STLSOFT_NUM_ELEMENTS(buf), 7, 5);
    TEST_MS_EQ("00007", s);
}
""",
    "error/conversion_error": """
static void test_conversion_error()
{
    stlsoft::conversion_error e("test", 42);
    TEST_INTEGER_EQUAL(42, e.get_error_code());
    TEST_PTR_NE(NULL, e.what());
}
""",
    "exception/root_exception": """
static void test_root_exception_type()
{
    TEST_INTEGER_EQUAL(sizeof(stlsoft::stlsoft_root_exception), sizeof(stlsoft::stlsoft_root_exception));
}
""",
    "filesystem/path_buffer": """
static void test_path_buffer_assign()
{
    stlsoft::basic_path_buffer<char, std::allocator<char>, 64> pb;
    pb.assign("a/b", 3);
    TEST_MS_EQ("a/b", pb.c_str());
    TEST_INTEGER_EQUAL(3, static_cast<int>(pb.size()));
}
""",
    "diagnostics/std_chrono_hrc_stopwatch": """
static void test_chrono_stopwatch()
{
    stlsoft::std_chrono_hrc_stopwatch sw;
    sw.start();
    sw.stop();
    TEST_BOOLEAN_TRUE(sw.get_seconds() >= 0);
}
""",
    "diagnostics/stopwatch_scope": """
static void test_stopwatch_scope()
{
    stlsoft::std_chrono_hrc_stopwatch sw;
    {
        stlsoft::stopwatch_scope<stlsoft::std_chrono_hrc_stopwatch> scope(sw);
    }
    TEST_BOOLEAN_TRUE(sw.get_seconds() >= 0);
}
""",
    "system/environment/functions": """
static void test_environment_variable_exists()
{
    TEST_BOOLEAN_TRUE(0 != stlsoft::stlsoft_C_environment_variable_exists_a("PATH"));
}
""",
    "filesystem/io_functions": """
static void test_io_functions_roundtrip()
{
    char const* path = "test_stlsoft_io.tmp";
    FILE* fp = fopen(path, "w");
    TEST_PTR_NE(NULL, fp);
    stlsoft::write_string(fp, "line1\\n", 6);
    fclose(fp);
    fp = fopen(path, "r");
    std::string line;
    stlsoft::read_line(fp, line);
    fclose(fp);
    remove(path);
    TEST_MS_EQ("line1", line);
}
""",
}


def area_from_test_dir(test_dir: Path) -> str:
    parts = test_dir.name.split(".")
    return "/".join(parts[3:]) if len(parts) > 3 else ""


def parse_functions(body: str) -> list[str]:
    return re.findall(r"static void (test_\w+)\(\)", body)


def rewrite_entry(test_dir: Path, area: str, body: str) -> None:
    kind = "component" if "component" in test_dir.parts else "unit"
    test_name = test_dir.name
    inc = f"<stlsoft/{area}.hpp>" if not area.endswith(".h") else f"<stlsoft/{area}>"
    extras = []
    if area.startswith(("algorithms/", "containers/", "collections/")):
        extras.append("#include <vector>")
    if area.startswith("filesystem/"):
        extras.extend(["#include <stdio.h>", "#include <string>"])
    if area == "filesystem/path_buffer":
        extras.append("#include <string>")
    if area.startswith("system/environment"):
        extras.append("#include <stlsoft/system/environment/functions.h>")
    extra_block = ("\n" + "\n".join(extras) + "\n") if extras else "\n"
    funcs = parse_functions(body)
    decls = "\n".join(f"static void {f}();" for f in funcs)
    runs = "\n        ".join(f"XTESTS_RUN_CASE({f});" for f in funcs)
    content = f"""/* /////////////////////////////////////////////////////////////////////////
 * File:    {test_name}/entry.cpp
 *
 * Purpose: {'Component' if kind == 'component' else 'Unit'}-tests for `stlsoft/{area}`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include {inc}
{extra_block}
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {{

{decls}

}} // anonymous namespace

int main(int argc, char* argv[])
{{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("{test_name}", verbosity))
    {{
        {runs}

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }}

    return retCode;
}}

namespace {{

{body}

}} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
"""
    (test_dir / "entry.cpp").write_text(content)


def main() -> None:
    fixed = 0
    for area, body in FIXES.items():
        for base in (ROOT / "test/unit/stlsoft", ROOT / "test/component/stlsoft"):
            for test_dir in base.rglob(f"test.*"):
                if not test_dir.is_dir():
                    continue
                if area_from_test_dir(test_dir) == area:
                    rewrite_entry(test_dir, area, body)
                    fixed += 1
                    print(f"fixed {test_dir.relative_to(ROOT)}")
    print(f"fixed={fixed}")


if __name__ == "__main__":
    main()
