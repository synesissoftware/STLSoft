/* /////////////////////////////////////////////////////////////////////////
 * File:    c_string.strnistrn/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::c_string::strnistrn() and wcsnistrn().
 *
 * Created: 23rd October 2026
 * Updated: 23rd October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/c_string/strnistrn.h>


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

    static void TEST_c_string_strnistrn_n2_0();
    static void TEST_c_string_strnistrn_n1_0();
    static void TEST_c_string_strnistrn_n2_GT_n1();
    static void TEST_c_string_strnistrn_EXACT_MATCH();
    static void TEST_c_string_strnistrn_CASE_FOLD_FULL();
    static void TEST_c_string_strnistrn_CASE_FOLD_IN_MIDDLE();
    static void TEST_c_string_strnistrn_CASE_FOLD_AT_END();
    static void TEST_c_string_strnistrn_MATCH_IN_MIDDLE();
    static void TEST_c_string_strnistrn_MATCH_AT_END();
    static void TEST_c_string_strnistrn_MISS();
    static void TEST_c_string_strnistrn_FIRST_CHAR_ONLY_THEN_MATCH();
    static void TEST_c_string_strnistrn_DOES_NOT_READ_PAST_n1();
    static void TEST_c_string_strnistrn_DOES_NOT_READ_PAST_n2();
    static void TEST_c_string_strnistrn_SINGLE_BYTE();
    static void TEST_c_string_strnistrn_HIGH_BIT();
    static void TEST_c_string_wcsnistrn_n2_0();
    static void TEST_c_string_wcsnistrn_n1_0();
    static void TEST_c_string_wcsnistrn_n2_GT_n1();
    static void TEST_c_string_wcsnistrn_EXACT_MATCH();
    static void TEST_c_string_wcsnistrn_CASE_FOLD_FULL();
    static void TEST_c_string_wcsnistrn_CASE_FOLD_IN_MIDDLE();
    static void TEST_c_string_wcsnistrn_CASE_FOLD_AT_END();
    static void TEST_c_string_wcsnistrn_MATCH_IN_MIDDLE();
    static void TEST_c_string_wcsnistrn_MATCH_AT_END();
    static void TEST_c_string_wcsnistrn_MISS();
    static void TEST_c_string_wcsnistrn_FIRST_CHAR_ONLY_THEN_MATCH();
    static void TEST_c_string_wcsnistrn_DOES_NOT_READ_PAST_n1();
    static void TEST_c_string_wcsnistrn_DOES_NOT_READ_PAST_n2();
    static void TEST_c_string_wcsnistrn_SINGLE_BYTE();
    static void TEST_c_string_wcsnistrn_HIGH_BIT();

    static wchar_t const* wcsnistrn_both_(wchar_t const* s1, size_t n1, wchar_t const* s2, size_t n2);

} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string.strnistrn", verbosity))
    {
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_n2_0);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_n1_0);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_n2_GT_n1);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_EXACT_MATCH);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_CASE_FOLD_FULL);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_CASE_FOLD_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_CASE_FOLD_AT_END);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_MISS);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_FIRST_CHAR_ONLY_THEN_MATCH);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_DOES_NOT_READ_PAST_n1);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_DOES_NOT_READ_PAST_n2);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_SINGLE_BYTE);
        XTESTS_RUN_CASE(TEST_c_string_strnistrn_HIGH_BIT);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_n2_0);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_n1_0);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_n2_GT_n1);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_EXACT_MATCH);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_CASE_FOLD_FULL);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_CASE_FOLD_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_CASE_FOLD_AT_END);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_MISS);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_FIRST_CHAR_ONLY_THEN_MATCH);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_DOES_NOT_READ_PAST_n1);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_DOES_NOT_READ_PAST_n2);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_SINGLE_BYTE);
        XTESTS_RUN_CASE(TEST_c_string_wcsnistrn_HIGH_BIT);

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

static wchar_t const* wcsnistrn_both_(wchar_t const* s1, size_t n1, wchar_t const* s2, size_t n2)
{
    wchar_t const* const via_str = stlsoft::c_string::strnistrn(s1, n1, s2, n2);
    wchar_t const* const via_wcs = stlsoft::c_string::wcsnistrn(s1, n1, s2, n2);

    TEST_PTR_EQ(via_wcs, via_str);

    return via_wcs;
}

static void TEST_c_string_strnistrn_n2_0()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s, stlsoft::c_string::strnistrn(s, 3, "", 0));
    TEST_PTR_EQ(s, stlsoft::c_string::strnistrn(s, 0, "xyz", 0));
}

static void TEST_c_string_strnistrn_n1_0()
{
    TEST_PTR_NULL(stlsoft::c_string::strnistrn("abc", 0, "a", 1));
}

static void TEST_c_string_strnistrn_n2_GT_n1()
{
    TEST_PTR_NULL(stlsoft::c_string::strnistrn("ab", 2, "abc", 3));
}

static void TEST_c_string_strnistrn_EXACT_MATCH()
{
    char const s[] = "abcdef";

    TEST_PTR_EQ(s, stlsoft::c_string::strnistrn(s, 6, "abc", 3));
    TEST_PTR_EQ(s, stlsoft::c_string::strnistrn(s, 3, "abc", 3));
}

static void TEST_c_string_strnistrn_CASE_FOLD_FULL()
{
    char const s[] = "xxAbCxx";

    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnistrn(s, 7, "aBc", 3));
    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnistrn(s, 7, "ABC", 3));
}

static void TEST_c_string_strnistrn_CASE_FOLD_IN_MIDDLE()
{
    char const s[] = "aBc";

    TEST_PTR_EQ(s, stlsoft::c_string::strnistrn(s, 3, "abc", 3));
    TEST_PTR_NULL(stlsoft::c_string::strnistrn(s, 3, "axc", 3));
}

static void TEST_c_string_strnistrn_CASE_FOLD_AT_END()
{
    char const s[] = "zzAB";

    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnistrn(s, 4, "ab", 2));
    TEST_PTR_NULL(stlsoft::c_string::strnistrn(s, 3, "ab", 2));
}

static void TEST_c_string_strnistrn_MATCH_IN_MIDDLE()
{
    char const s[] = "xxabcxx";

    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnistrn(s, 7, "AbC", 3));
}

static void TEST_c_string_strnistrn_MATCH_AT_END()
{
    char const s[] = "xxabc";

    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnistrn(s, 5, "ABC", 3));
}

static void TEST_c_string_strnistrn_MISS()
{
    TEST_PTR_NULL(stlsoft::c_string::strnistrn("abcdef", 6, "zzz", 3));
    TEST_PTR_NULL(stlsoft::c_string::strnistrn("abcdef", 6, "abx", 3));
    TEST_PTR_NULL(stlsoft::c_string::strnistrn("aXY", 3, "abc", 3));
}

static void TEST_c_string_strnistrn_FIRST_CHAR_ONLY_THEN_MATCH()
{
    char const s[] = "aXYabc";

    TEST_PTR_EQ(s + 3, stlsoft::c_string::strnistrn(s, 6, "ABC", 3));
    TEST_PTR_NULL(stlsoft::c_string::strnistrn("aXY", 3, "ABC", 3));
}

static void TEST_c_string_strnistrn_DOES_NOT_READ_PAST_n1()
{
    char const s[] = "xxabc";

    TEST_PTR_NULL(stlsoft::c_string::strnistrn(s, 4, "ABC", 3));
    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnistrn(s, 5, "ABC", 3));
}

static void TEST_c_string_strnistrn_DOES_NOT_READ_PAST_n2()
{
    char const hay[] = "abX";
    char const needle[] = { 'A', 'B', 'Y' };

    TEST_PTR_EQ(hay, stlsoft::c_string::strnistrn(hay, 3, needle, 2));
    TEST_PTR_NULL(stlsoft::c_string::strnistrn(hay, 3, needle, 3));
}

static void TEST_c_string_strnistrn_SINGLE_BYTE()
{
    char const s[] = "xxA";

    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnistrn(s, 3, "a", 1));
    TEST_PTR_NULL(stlsoft::c_string::strnistrn(s, 2, "a", 1));
}

static void TEST_c_string_strnistrn_HIGH_BIT()
{
    char const hay[] = { (char)0xE9, 'A', 'b' };
    char const needle[] = { (char)0xE9, 'a', 'B' };
    char const other[] = { (char)0xE2, 'a' };

    TEST_PTR_EQ(hay, stlsoft::c_string::strnistrn(hay, 3, needle, 3));
    TEST_PTR_NULL(stlsoft::c_string::strnistrn(hay, 2, other, 2));
}

static void TEST_c_string_wcsnistrn_n2_0()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s, wcsnistrn_both_(s, 3, L"", 0));
    TEST_PTR_EQ(s, wcsnistrn_both_(s, 0, L"xyz", 0));
}

static void TEST_c_string_wcsnistrn_n1_0()
{
    TEST_PTR_NULL(wcsnistrn_both_(L"abc", 0, L"a", 1));
}

static void TEST_c_string_wcsnistrn_n2_GT_n1()
{
    TEST_PTR_NULL(wcsnistrn_both_(L"ab", 2, L"abc", 3));
}

static void TEST_c_string_wcsnistrn_EXACT_MATCH()
{
    wchar_t const s[] = L"abcdef";

    TEST_PTR_EQ(s, wcsnistrn_both_(s, 6, L"abc", 3));
    TEST_PTR_EQ(s, wcsnistrn_both_(s, 3, L"abc", 3));
}

static void TEST_c_string_wcsnistrn_CASE_FOLD_FULL()
{
    wchar_t const s[] = L"xxAbCxx";

    TEST_PTR_EQ(s + 2, wcsnistrn_both_(s, 7, L"aBc", 3));
    TEST_PTR_EQ(s + 2, wcsnistrn_both_(s, 7, L"ABC", 3));
}

static void TEST_c_string_wcsnistrn_CASE_FOLD_IN_MIDDLE()
{
    wchar_t const s[] = L"aBc";

    TEST_PTR_EQ(s, wcsnistrn_both_(s, 3, L"abc", 3));
    TEST_PTR_NULL(wcsnistrn_both_(s, 3, L"axc", 3));
}

static void TEST_c_string_wcsnistrn_CASE_FOLD_AT_END()
{
    wchar_t const s[] = L"zzAB";

    TEST_PTR_EQ(s + 2, wcsnistrn_both_(s, 4, L"ab", 2));
    TEST_PTR_NULL(wcsnistrn_both_(s, 3, L"ab", 2));
}

static void TEST_c_string_wcsnistrn_MATCH_IN_MIDDLE()
{
    wchar_t const s[] = L"xxabcxx";

    TEST_PTR_EQ(s + 2, wcsnistrn_both_(s, 7, L"AbC", 3));
}

static void TEST_c_string_wcsnistrn_MATCH_AT_END()
{
    wchar_t const s[] = L"xxabc";

    TEST_PTR_EQ(s + 2, wcsnistrn_both_(s, 5, L"ABC", 3));
}

static void TEST_c_string_wcsnistrn_MISS()
{
    TEST_PTR_NULL(wcsnistrn_both_(L"abcdef", 6, L"zzz", 3));
    TEST_PTR_NULL(wcsnistrn_both_(L"abcdef", 6, L"abx", 3));
    TEST_PTR_NULL(wcsnistrn_both_(L"aXY", 3, L"abc", 3));
}

static void TEST_c_string_wcsnistrn_FIRST_CHAR_ONLY_THEN_MATCH()
{
    wchar_t const s[] = L"aXYabc";

    TEST_PTR_EQ(s + 3, wcsnistrn_both_(s, 6, L"ABC", 3));
    TEST_PTR_NULL(wcsnistrn_both_(L"aXY", 3, L"ABC", 3));
}

static void TEST_c_string_wcsnistrn_DOES_NOT_READ_PAST_n1()
{
    wchar_t const s[] = L"xxabc";

    TEST_PTR_NULL(wcsnistrn_both_(s, 4, L"ABC", 3));
    TEST_PTR_EQ(s + 2, wcsnistrn_both_(s, 5, L"ABC", 3));
}

static void TEST_c_string_wcsnistrn_DOES_NOT_READ_PAST_n2()
{
    wchar_t const hay[] = L"abX";
    wchar_t const needle[] = { L'A', L'B', L'Y' };

    TEST_PTR_EQ(hay, wcsnistrn_both_(hay, 3, needle, 2));
    TEST_PTR_NULL(wcsnistrn_both_(hay, 3, needle, 3));
}

static void TEST_c_string_wcsnistrn_SINGLE_BYTE()
{
    wchar_t const s[] = L"xxA";

    TEST_PTR_EQ(s + 2, wcsnistrn_both_(s, 3, L"a", 1));
    TEST_PTR_NULL(wcsnistrn_both_(s, 2, L"a", 1));
}

static void TEST_c_string_wcsnistrn_HIGH_BIT()
{
    wchar_t const hay[] = { L'\x00E9', L'A', L'b' };
    wchar_t const needle[] = { L'\x00E9', L'a', L'B' };
    wchar_t const other[] = { L'\x00E2', L'a' };

    TEST_PTR_EQ(hay, wcsnistrn_both_(hay, 3, needle, 3));
    TEST_PTR_NULL(wcsnistrn_both_(hay, 2, other, 2));
}

} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */
