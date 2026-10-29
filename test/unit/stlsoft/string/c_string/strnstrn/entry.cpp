/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/c_string/strnstrn/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::c_string::strnstrn() and wcsnstrn().
 *
 * Created: 23rd October 2026
 * Updated: 25th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/c_string/strnstrn.h>


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

    static void TEST_c_string_strnstrn_n2_0();
    static void TEST_c_string_strnstrn_n1_0();
    static void TEST_c_string_strnstrn_n2_GT_n1();
    static void TEST_c_string_strnstrn_MATCH_AT_START();
    static void TEST_c_string_strnstrn_MATCH_IN_MIDDLE();
    static void TEST_c_string_strnstrn_MATCH_AT_END();
    static void TEST_c_string_strnstrn_MISS();
    static void TEST_c_string_strnstrn_PARTIAL_THEN_MATCH();
    static void TEST_c_string_strnstrn_REPEATED_FIRST_BYTE();
    static void TEST_c_string_strnstrn_DOES_NOT_READ_PAST_n1();
    static void TEST_c_string_strnstrn_DOES_NOT_READ_PAST_n2();
    static void TEST_c_string_strnstrn_EMBEDDED_NUL();
    static void TEST_c_string_strnstrn_SINGLE_BYTE();
    static void TEST_c_string_strnstrn_FULL_SPAN();
    static void TEST_c_string_wcsnstrn_n2_0();
    static void TEST_c_string_wcsnstrn_n1_0();
    static void TEST_c_string_wcsnstrn_n2_GT_n1();
    static void TEST_c_string_wcsnstrn_MATCH_AT_START();
    static void TEST_c_string_wcsnstrn_MATCH_IN_MIDDLE();
    static void TEST_c_string_wcsnstrn_MATCH_AT_END();
    static void TEST_c_string_wcsnstrn_MISS();
    static void TEST_c_string_wcsnstrn_PARTIAL_THEN_MATCH();
    static void TEST_c_string_wcsnstrn_REPEATED_FIRST_BYTE();
    static void TEST_c_string_wcsnstrn_DOES_NOT_READ_PAST_n1();
    static void TEST_c_string_wcsnstrn_DOES_NOT_READ_PAST_n2();
    static void TEST_c_string_wcsnstrn_EMBEDDED_NUL();
    static void TEST_c_string_wcsnstrn_SINGLE_BYTE();
    static void TEST_c_string_wcsnstrn_FULL_SPAN();

    static wchar_t const* wcsnstrn_both_(wchar_t const* s1, size_t n1, wchar_t const* s2, size_t n2);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string.strnstrn", verbosity))
    {
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_n2_0);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_n1_0);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_n2_GT_n1);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_MATCH_AT_START);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_MISS);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_PARTIAL_THEN_MATCH);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_REPEATED_FIRST_BYTE);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_DOES_NOT_READ_PAST_n1);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_DOES_NOT_READ_PAST_n2);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_SINGLE_BYTE);
        XTESTS_RUN_CASE(TEST_c_string_strnstrn_FULL_SPAN);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_n2_0);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_n1_0);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_n2_GT_n1);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_MATCH_AT_START);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_MISS);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_PARTIAL_THEN_MATCH);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_REPEATED_FIRST_BYTE);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_DOES_NOT_READ_PAST_n1);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_DOES_NOT_READ_PAST_n2);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_SINGLE_BYTE);
        XTESTS_RUN_CASE(TEST_c_string_wcsnstrn_FULL_SPAN);

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

static wchar_t const* wcsnstrn_both_(wchar_t const* s1, size_t n1, wchar_t const* s2, size_t n2)
{
    wchar_t const* const via_str = stlsoft::c_string::strnstrn(s1, n1, s2, n2);
    wchar_t const* const via_wcs = stlsoft::c_string::wcsnstrn(s1, n1, s2, n2);

    TEST_PTR_EQ(via_wcs, via_str);

    return via_wcs;
}

static void TEST_c_string_strnstrn_n2_0()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s, stlsoft::c_string::strnstrn(s, 3, "", 0));
    TEST_PTR_EQ(s, stlsoft::c_string::strnstrn(s, 0, "", 0));
    TEST_PTR_EQ(s, stlsoft::c_string::strnstrn(s, 3, "xyz", 0));
}

static void TEST_c_string_strnstrn_n1_0()
{
    char const s[] = "abc";

    TEST_PTR_NULL(stlsoft::c_string::strnstrn(s, 0, "a", 1));
}

static void TEST_c_string_strnstrn_n2_GT_n1()
{
    TEST_PTR_NULL(stlsoft::c_string::strnstrn("ab", 2, "abc", 3));
    TEST_PTR_NULL(stlsoft::c_string::strnstrn("abcd", 4, "abcde", 5));
}

static void TEST_c_string_strnstrn_MATCH_AT_START()
{
    char const s[] = "abcdef";

    TEST_PTR_EQ(s, stlsoft::c_string::strnstrn(s, 6, "abc", 3));
    TEST_PTR_EQ(s, stlsoft::c_string::strnstrn(s, 3, "abc", 3));
}

static void TEST_c_string_strnstrn_MATCH_IN_MIDDLE()
{
    char const s[] = "xxabcxx";

    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnstrn(s, 7, "abc", 3));
}

static void TEST_c_string_strnstrn_MATCH_AT_END()
{
    char const s[] = "xxabc";

    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnstrn(s, 5, "abc", 3));
    TEST_PTR_NULL(stlsoft::c_string::strnstrn(s, 4, "abc", 3));
}

static void TEST_c_string_strnstrn_MISS()
{
    TEST_PTR_NULL(stlsoft::c_string::strnstrn("abcdef", 6, "zzz", 3));
    TEST_PTR_NULL(stlsoft::c_string::strnstrn("abcdef", 6, "abx", 3));
}

static void TEST_c_string_strnstrn_PARTIAL_THEN_MATCH()
{
    char const s[] = "abXabc";

    TEST_PTR_EQ(s + 3, stlsoft::c_string::strnstrn(s, 6, "abc", 3));
}

static void TEST_c_string_strnstrn_REPEATED_FIRST_BYTE()
{
    char const s[] = "aaab";
    char const t[] = "aaa";

    TEST_PTR_EQ(s + 1, stlsoft::c_string::strnstrn(s, 4, "aab", 3));
    TEST_PTR_EQ(t, stlsoft::c_string::strnstrn(t, 3, "aa", 2));
}

static void TEST_c_string_strnstrn_DOES_NOT_READ_PAST_n1()
{
    char const s[] = "xxabc";

    TEST_PTR_NULL(stlsoft::c_string::strnstrn(s, 4, "abc", 3));
    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnstrn(s, 5, "abc", 3));
}

static void TEST_c_string_strnstrn_DOES_NOT_READ_PAST_n2()
{
    char const hay[] = "abX";
    char const needle[] = { 'a', 'b', 'Y' };

    TEST_PTR_EQ(hay, stlsoft::c_string::strnstrn(hay, 3, needle, 2));
    TEST_PTR_NULL(stlsoft::c_string::strnstrn(hay, 3, needle, 3));
}

static void TEST_c_string_strnstrn_EMBEDDED_NUL()
{
    char const hay[] = { 'a', '\0', 'b', 'x', 'a', '\0', 'b' };
    char const needle[] = { 'a', '\0', 'b' };

    TEST_PTR_EQ(hay, stlsoft::c_string::strnstrn(hay, 7, needle, 3));
    TEST_PTR_EQ(hay + 4, stlsoft::c_string::strnstrn(hay + 1, 6, needle, 3));
}

static void TEST_c_string_strnstrn_SINGLE_BYTE()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 1, stlsoft::c_string::strnstrn(s, 3, "b", 1));
    TEST_PTR_NULL(stlsoft::c_string::strnstrn(s, 3, "z", 1));
}

static void TEST_c_string_strnstrn_FULL_SPAN()
{
    char const s[] = "abcd";

    TEST_PTR_EQ(s, stlsoft::c_string::strnstrn(s, 4, "abcd", 4));
    TEST_PTR_NULL(stlsoft::c_string::strnstrn(s, 4, "abce", 4));
}

static void TEST_c_string_wcsnstrn_n2_0()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s, wcsnstrn_both_(s, 3, L"", 0));
    TEST_PTR_EQ(s, wcsnstrn_both_(s, 0, L"", 0));
    TEST_PTR_EQ(s, wcsnstrn_both_(s, 3, L"xyz", 0));
}

static void TEST_c_string_wcsnstrn_n1_0()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_NULL(wcsnstrn_both_(s, 0, L"a", 1));
}

static void TEST_c_string_wcsnstrn_n2_GT_n1()
{
    TEST_PTR_NULL(wcsnstrn_both_(L"ab", 2, L"abc", 3));
    TEST_PTR_NULL(wcsnstrn_both_(L"abcd", 4, L"abcde", 5));
}

static void TEST_c_string_wcsnstrn_MATCH_AT_START()
{
    wchar_t const s[] = L"abcdef";

    TEST_PTR_EQ(s, wcsnstrn_both_(s, 6, L"abc", 3));
    TEST_PTR_EQ(s, wcsnstrn_both_(s, 3, L"abc", 3));
}

static void TEST_c_string_wcsnstrn_MATCH_IN_MIDDLE()
{
    wchar_t const s[] = L"xxabcxx";

    TEST_PTR_EQ(s + 2, wcsnstrn_both_(s, 7, L"abc", 3));
}

static void TEST_c_string_wcsnstrn_MATCH_AT_END()
{
    wchar_t const s[] = L"xxabc";

    TEST_PTR_EQ(s + 2, wcsnstrn_both_(s, 5, L"abc", 3));
    TEST_PTR_NULL(wcsnstrn_both_(s, 4, L"abc", 3));
}

static void TEST_c_string_wcsnstrn_MISS()
{
    TEST_PTR_NULL(wcsnstrn_both_(L"abcdef", 6, L"zzz", 3));
    TEST_PTR_NULL(wcsnstrn_both_(L"abcdef", 6, L"abx", 3));
}

static void TEST_c_string_wcsnstrn_PARTIAL_THEN_MATCH()
{
    wchar_t const s[] = L"abXabc";

    TEST_PTR_EQ(s + 3, wcsnstrn_both_(s, 6, L"abc", 3));
}

static void TEST_c_string_wcsnstrn_REPEATED_FIRST_BYTE()
{
    wchar_t const s[] = L"aaab";
    wchar_t const t[] = L"aaa";

    TEST_PTR_EQ(s + 1, wcsnstrn_both_(s, 4, L"aab", 3));
    TEST_PTR_EQ(t, wcsnstrn_both_(t, 3, L"aa", 2));
}

static void TEST_c_string_wcsnstrn_DOES_NOT_READ_PAST_n1()
{
    wchar_t const s[] = L"xxabc";

    TEST_PTR_NULL(wcsnstrn_both_(s, 4, L"abc", 3));
    TEST_PTR_EQ(s + 2, wcsnstrn_both_(s, 5, L"abc", 3));
}

static void TEST_c_string_wcsnstrn_DOES_NOT_READ_PAST_n2()
{
    wchar_t const hay[] = L"abX";
    wchar_t const needle[] = { L'a', L'b', L'Y' };

    TEST_PTR_EQ(hay, wcsnstrn_both_(hay, 3, needle, 2));
    TEST_PTR_NULL(wcsnstrn_both_(hay, 3, needle, 3));
}

static void TEST_c_string_wcsnstrn_EMBEDDED_NUL()
{
    wchar_t const hay[] = { L'a', L'\0', L'b', L'x', L'a', L'\0', L'b' };
    wchar_t const needle[] = { L'a', L'\0', L'b' };

    TEST_PTR_EQ(hay, wcsnstrn_both_(hay, 7, needle, 3));
    TEST_PTR_EQ(hay + 4, wcsnstrn_both_(hay + 1, 6, needle, 3));
}

static void TEST_c_string_wcsnstrn_SINGLE_BYTE()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 1, wcsnstrn_both_(s, 3, L"b", 1));
    TEST_PTR_NULL(wcsnstrn_both_(s, 3, L"z", 1));
}

static void TEST_c_string_wcsnstrn_FULL_SPAN()
{
    wchar_t const s[] = L"abcd";

    TEST_PTR_EQ(s, wcsnstrn_both_(s, 4, L"abcd", 4));
    TEST_PTR_NULL(wcsnstrn_both_(s, 4, L"abce", 4));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
