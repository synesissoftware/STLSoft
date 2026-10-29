/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/c_string/strnpbrkn/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::c_string::strnpbrkn() and wcsnpbrkn().
 *
 * Created: 23rd October 2026
 * Updated: 25th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/c_string/strnpbrkn.h>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <xtests/terse-api.h>
#include <xtests/xtests.h>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void TEST_c_string_strnpbrkn_cchStr_0();
    static void TEST_c_string_strnpbrkn_cchCharSet_0();
    static void TEST_c_string_strnpbrkn_MATCH_AT_START_FIRST_IN_SET();
    static void TEST_c_string_strnpbrkn_MATCH_AT_START_LAST_IN_SET();
    static void TEST_c_string_strnpbrkn_MATCH_IN_MIDDLE();
    static void TEST_c_string_strnpbrkn_MATCH_AT_END();
    static void TEST_c_string_strnpbrkn_FIRST_OF_SEVERAL();
    static void TEST_c_string_strnpbrkn_MISS();
    static void TEST_c_string_strnpbrkn_DOES_NOT_READ_PAST_cchStr();
    static void TEST_c_string_strnpbrkn_DOES_NOT_READ_PAST_cchCharSet();
    static void TEST_c_string_strnpbrkn_EMBEDDED_NUL_IN_STRING();
    static void TEST_c_string_strnpbrkn_NUL_IN_SET();
    static void TEST_c_string_strnpbrkn_SINGLE_BYTE_SET();
    static void TEST_c_string_strnpbrkn_SET_LONGER_THAN_STRING();
    static void TEST_c_string_wcsnpbrkn_cchStr_0();
    static void TEST_c_string_wcsnpbrkn_cchCharSet_0();
    static void TEST_c_string_wcsnpbrkn_MATCH_AT_START_FIRST_IN_SET();
    static void TEST_c_string_wcsnpbrkn_MATCH_AT_START_LAST_IN_SET();
    static void TEST_c_string_wcsnpbrkn_MATCH_IN_MIDDLE();
    static void TEST_c_string_wcsnpbrkn_MATCH_AT_END();
    static void TEST_c_string_wcsnpbrkn_FIRST_OF_SEVERAL();
    static void TEST_c_string_wcsnpbrkn_MISS();
    static void TEST_c_string_wcsnpbrkn_DOES_NOT_READ_PAST_cchStr();
    static void TEST_c_string_wcsnpbrkn_DOES_NOT_READ_PAST_cchCharSet();
    static void TEST_c_string_wcsnpbrkn_EMBEDDED_NUL_IN_STRING();
    static void TEST_c_string_wcsnpbrkn_NUL_IN_SET();
    static void TEST_c_string_wcsnpbrkn_SINGLE_BYTE_SET();
    static void TEST_c_string_wcsnpbrkn_SET_LONGER_THAN_STRING();

    static wchar_t const* wcsnpbrkn_both_(wchar_t const* str, size_t cchStr, wchar_t const* charSet, size_t cchCharSet);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string.strnpbrkn", verbosity))
    {
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_cchStr_0);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_cchCharSet_0);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_MATCH_AT_START_FIRST_IN_SET);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_MATCH_AT_START_LAST_IN_SET);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_FIRST_OF_SEVERAL);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_MISS);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_DOES_NOT_READ_PAST_cchStr);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_DOES_NOT_READ_PAST_cchCharSet);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_EMBEDDED_NUL_IN_STRING);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_NUL_IN_SET);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_SINGLE_BYTE_SET);
        XTESTS_RUN_CASE(TEST_c_string_strnpbrkn_SET_LONGER_THAN_STRING);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_cchStr_0);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_cchCharSet_0);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_MATCH_AT_START_FIRST_IN_SET);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_MATCH_AT_START_LAST_IN_SET);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_FIRST_OF_SEVERAL);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_MISS);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_DOES_NOT_READ_PAST_cchStr);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_DOES_NOT_READ_PAST_cchCharSet);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_EMBEDDED_NUL_IN_STRING);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_NUL_IN_SET);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_SINGLE_BYTE_SET);
        XTESTS_RUN_CASE(TEST_c_string_wcsnpbrkn_SET_LONGER_THAN_STRING);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{

static wchar_t const* wcsnpbrkn_both_(wchar_t const* str, size_t cchStr, wchar_t const* charSet, size_t cchCharSet)
{
    wchar_t const* const via_str = stlsoft::c_string::strnpbrkn(str, cchStr, charSet, cchCharSet);
    wchar_t const* const via_wcs = stlsoft::c_string::wcsnpbrkn(str, cchStr, charSet, cchCharSet);

    TEST_PTR_EQ(via_wcs, via_str);

    return via_wcs;
}

static void TEST_c_string_strnpbrkn_cchStr_0()
{
    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn("abc", 0, "a", 1));
    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn("", 0, "", 0));
}

static void TEST_c_string_strnpbrkn_cchCharSet_0()
{
    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn("abc", 3, "xyz", 0));
    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn("abc", 3, "", 0));
}

static void TEST_c_string_strnpbrkn_MATCH_AT_START_FIRST_IN_SET()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s, stlsoft::c_string::strnpbrkn(s, 3, "ax", 2));
}

static void TEST_c_string_strnpbrkn_MATCH_AT_START_LAST_IN_SET()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s, stlsoft::c_string::strnpbrkn(s, 3, "xya", 3));
}

static void TEST_c_string_strnpbrkn_MATCH_IN_MIDDLE()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 1, stlsoft::c_string::strnpbrkn(s, 3, "xb", 2));
}

static void TEST_c_string_strnpbrkn_MATCH_AT_END()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnpbrkn(s, 3, "zc", 2));
}

static void TEST_c_string_strnpbrkn_FIRST_OF_SEVERAL()
{
    char const s[] = "bXa";

    TEST_PTR_EQ(s + 1, stlsoft::c_string::strnpbrkn(s, 3, "aX", 2));
}

static void TEST_c_string_strnpbrkn_MISS()
{
    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn("abc", 3, "xyz", 3));
}

static void TEST_c_string_strnpbrkn_DOES_NOT_READ_PAST_cchStr()
{
    char const s[] = "abcZ";

    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn(s, 3, "Z", 1));
    TEST_PTR_EQ(s + 3, stlsoft::c_string::strnpbrkn(s, 4, "Z", 1));
}

static void TEST_c_string_strnpbrkn_DOES_NOT_READ_PAST_cchCharSet()
{
    char const str[] = "Zzz";
    char const set[] = { 'x', 'y', 'Z' };

    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn(str, 3, set, 2));
    TEST_PTR_EQ(str, stlsoft::c_string::strnpbrkn(str, 3, set, 3));
}

static void TEST_c_string_strnpbrkn_EMBEDDED_NUL_IN_STRING()
{
    char const str[] = { 'a', '\0', 'b' };
    char const set[] = { 'b' };

    TEST_PTR_EQ(str + 2, stlsoft::c_string::strnpbrkn(str, 3, set, 1));
    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn(str, 2, set, 1));
}

static void TEST_c_string_strnpbrkn_NUL_IN_SET()
{
    char const str[] = { 'a', '\0', 'b' };
    char const set[] = { 'x', '\0', 'q' };

    TEST_PTR_EQ(str + 1, stlsoft::c_string::strnpbrkn(str, 3, set, 3));
    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn(str, 3, set, 1));
}

static void TEST_c_string_strnpbrkn_SINGLE_BYTE_SET()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 1, stlsoft::c_string::strnpbrkn(s, 3, "b", 1));
    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn(s, 3, "z", 1));
}

static void TEST_c_string_strnpbrkn_SET_LONGER_THAN_STRING()
{
    char const s[] = "b";

    TEST_PTR_EQ(s, stlsoft::c_string::strnpbrkn(s, 1, "xyzb", 4));
    TEST_PTR_NULL(stlsoft::c_string::strnpbrkn(s, 1, "xyza", 4));
}

static void TEST_c_string_wcsnpbrkn_cchStr_0()
{
    TEST_PTR_NULL(wcsnpbrkn_both_(L"abc", 0, L"a", 1));
    TEST_PTR_NULL(wcsnpbrkn_both_(L"", 0, L"", 0));
}

static void TEST_c_string_wcsnpbrkn_cchCharSet_0()
{
    TEST_PTR_NULL(wcsnpbrkn_both_(L"abc", 3, L"xyz", 0));
    TEST_PTR_NULL(wcsnpbrkn_both_(L"abc", 3, L"", 0));
}

static void TEST_c_string_wcsnpbrkn_MATCH_AT_START_FIRST_IN_SET()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s, wcsnpbrkn_both_(s, 3, L"ax", 2));
}

static void TEST_c_string_wcsnpbrkn_MATCH_AT_START_LAST_IN_SET()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s, wcsnpbrkn_both_(s, 3, L"xya", 3));
}

static void TEST_c_string_wcsnpbrkn_MATCH_IN_MIDDLE()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 1, wcsnpbrkn_both_(s, 3, L"xb", 2));
}

static void TEST_c_string_wcsnpbrkn_MATCH_AT_END()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 2, wcsnpbrkn_both_(s, 3, L"zc", 2));
}

static void TEST_c_string_wcsnpbrkn_FIRST_OF_SEVERAL()
{
    wchar_t const s[] = L"bXa";

    TEST_PTR_EQ(s + 1, wcsnpbrkn_both_(s, 3, L"aX", 2));
}

static void TEST_c_string_wcsnpbrkn_MISS()
{
    TEST_PTR_NULL(wcsnpbrkn_both_(L"abc", 3, L"xyz", 3));
}

static void TEST_c_string_wcsnpbrkn_DOES_NOT_READ_PAST_cchStr()
{
    wchar_t const s[] = L"abcZ";

    TEST_PTR_NULL(wcsnpbrkn_both_(s, 3, L"Z", 1));
    TEST_PTR_EQ(s + 3, wcsnpbrkn_both_(s, 4, L"Z", 1));
}

static void TEST_c_string_wcsnpbrkn_DOES_NOT_READ_PAST_cchCharSet()
{
    wchar_t const str[] = L"Zzz";
    wchar_t const set[] = { L'x', L'y', L'Z' };

    TEST_PTR_NULL(wcsnpbrkn_both_(str, 3, set, 2));
    TEST_PTR_EQ(str, wcsnpbrkn_both_(str, 3, set, 3));
}

static void TEST_c_string_wcsnpbrkn_EMBEDDED_NUL_IN_STRING()
{
    wchar_t const str[] = { L'a', L'\0', L'b' };
    wchar_t const set[] = { L'b' };

    TEST_PTR_EQ(str + 2, wcsnpbrkn_both_(str, 3, set, 1));
    TEST_PTR_NULL(wcsnpbrkn_both_(str, 2, set, 1));
}

static void TEST_c_string_wcsnpbrkn_NUL_IN_SET()
{
    wchar_t const str[] = { L'a', L'\0', L'b' };
    wchar_t const set[] = { L'x', L'\0', L'q' };

    TEST_PTR_EQ(str + 1, wcsnpbrkn_both_(str, 3, set, 3));
    TEST_PTR_NULL(wcsnpbrkn_both_(str, 3, set, 1));
}

static void TEST_c_string_wcsnpbrkn_SINGLE_BYTE_SET()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 1, wcsnpbrkn_both_(s, 3, L"b", 1));
    TEST_PTR_NULL(wcsnpbrkn_both_(s, 3, L"z", 1));
}

static void TEST_c_string_wcsnpbrkn_SET_LONGER_THAN_STRING()
{
    wchar_t const s[] = L"b";

    TEST_PTR_EQ(s, wcsnpbrkn_both_(s, 1, L"xyzb", 4));
    TEST_PTR_NULL(wcsnpbrkn_both_(s, 1, L"xyza", 4));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
