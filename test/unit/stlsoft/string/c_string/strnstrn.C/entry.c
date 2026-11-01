/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/c_string/strnstrn.C/entry.c
 *
 * Purpose: Unit-tests for stlsoft_C_strnstrn() and stlsoft_C_wcsnstrn().
 *
 * Created: 23rd October 2026
 * Updated: 29th October 2026
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

static void TEST_stlsoft_C_strnstrn_n2_0(void);
static void TEST_stlsoft_C_strnstrn_n1_0(void);
static void TEST_stlsoft_C_strnstrn_n2_GT_n1(void);
static void TEST_stlsoft_C_strnstrn_MATCH_AT_START(void);
static void TEST_stlsoft_C_strnstrn_MATCH_IN_MIDDLE(void);
static void TEST_stlsoft_C_strnstrn_MATCH_AT_END(void);
static void TEST_stlsoft_C_strnstrn_MISS(void);
static void TEST_stlsoft_C_strnstrn_PARTIAL_THEN_MATCH(void);
static void TEST_stlsoft_C_strnstrn_REPEATED_FIRST_BYTE(void);
static void TEST_stlsoft_C_strnstrn_DOES_NOT_READ_PAST_n1(void);
static void TEST_stlsoft_C_strnstrn_DOES_NOT_READ_PAST_n2(void);
static void TEST_stlsoft_C_strnstrn_EMBEDDED_NUL(void);
static void TEST_stlsoft_C_strnstrn_SINGLE_BYTE(void);
static void TEST_stlsoft_C_strnstrn_FULL_SPAN(void);
static void TEST_stlsoft_C_wcsnstrn_n2_0(void);
static void TEST_stlsoft_C_wcsnstrn_n1_0(void);
static void TEST_stlsoft_C_wcsnstrn_n2_GT_n1(void);
static void TEST_stlsoft_C_wcsnstrn_MATCH_AT_START(void);
static void TEST_stlsoft_C_wcsnstrn_MATCH_IN_MIDDLE(void);
static void TEST_stlsoft_C_wcsnstrn_MATCH_AT_END(void);
static void TEST_stlsoft_C_wcsnstrn_MISS(void);
static void TEST_stlsoft_C_wcsnstrn_PARTIAL_THEN_MATCH(void);
static void TEST_stlsoft_C_wcsnstrn_REPEATED_FIRST_BYTE(void);
static void TEST_stlsoft_C_wcsnstrn_DOES_NOT_READ_PAST_n1(void);
static void TEST_stlsoft_C_wcsnstrn_DOES_NOT_READ_PAST_n2(void);
static void TEST_stlsoft_C_wcsnstrn_EMBEDDED_NUL(void);
static void TEST_stlsoft_C_wcsnstrn_SINGLE_BYTE(void);
static void TEST_stlsoft_C_wcsnstrn_FULL_SPAN(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string.strnstrn.C", verbosity))
    {
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_n2_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_n1_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_n2_GT_n1);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_MATCH_AT_START);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_MISS);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_PARTIAL_THEN_MATCH);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_REPEATED_FIRST_BYTE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_DOES_NOT_READ_PAST_n1);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_DOES_NOT_READ_PAST_n2);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_SINGLE_BYTE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnstrn_FULL_SPAN);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_n2_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_n1_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_n2_GT_n1);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_MATCH_AT_START);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_MISS);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_PARTIAL_THEN_MATCH);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_REPEATED_FIRST_BYTE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_DOES_NOT_READ_PAST_n1);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_DOES_NOT_READ_PAST_n2);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_SINGLE_BYTE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnstrn_FULL_SPAN);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_stlsoft_C_strnstrn_n2_0(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s, stlsoft_C_strnstrn(s, 3, "", 0));
    TEST_PTR_EQ(s, stlsoft_C_strnstrn(s, 0, "", 0));
    TEST_PTR_EQ(s, stlsoft_C_strnstrn(s, 3, "xyz", 0));
}

static void TEST_stlsoft_C_strnstrn_n1_0(void)
{
    char const s[] = "abc";

    TEST_PTR_NULL(stlsoft_C_strnstrn(s, 0, "a", 1));
}

static void TEST_stlsoft_C_strnstrn_n2_GT_n1(void)
{
    TEST_PTR_NULL(stlsoft_C_strnstrn("ab", 2, "abc", 3));
    TEST_PTR_NULL(stlsoft_C_strnstrn("abcd", 4, "abcde", 5));
}

static void TEST_stlsoft_C_strnstrn_MATCH_AT_START(void)
{
    char const s[] = "abcdef";

    TEST_PTR_EQ(s, stlsoft_C_strnstrn(s, 6, "abc", 3));
    TEST_PTR_EQ(s, stlsoft_C_strnstrn(s, 3, "abc", 3));
}

static void TEST_stlsoft_C_strnstrn_MATCH_IN_MIDDLE(void)
{
    char const s[] = "xxabcxx";

    TEST_PTR_EQ(s + 2, stlsoft_C_strnstrn(s, 7, "abc", 3));
}

static void TEST_stlsoft_C_strnstrn_MATCH_AT_END(void)
{
    char const s[] = "xxabc";

    TEST_PTR_EQ(s + 2, stlsoft_C_strnstrn(s, 5, "abc", 3));
    TEST_PTR_NULL(stlsoft_C_strnstrn(s, 4, "abc", 3));
}

static void TEST_stlsoft_C_strnstrn_MISS(void)
{
    TEST_PTR_NULL(stlsoft_C_strnstrn("abcdef", 6, "zzz", 3));
    TEST_PTR_NULL(stlsoft_C_strnstrn("abcdef", 6, "abx", 3));
}

static void TEST_stlsoft_C_strnstrn_PARTIAL_THEN_MATCH(void)
{
    char const s[] = "abXabc";

    TEST_PTR_EQ(s + 3, stlsoft_C_strnstrn(s, 6, "abc", 3));
}

static void TEST_stlsoft_C_strnstrn_REPEATED_FIRST_BYTE(void)
{
    char const s[] = "aaab";
    char const t[] = "aaa";

    TEST_PTR_EQ(s + 1, stlsoft_C_strnstrn(s, 4, "aab", 3));
    TEST_PTR_EQ(t, stlsoft_C_strnstrn(t, 3, "aa", 2));
}

static void TEST_stlsoft_C_strnstrn_DOES_NOT_READ_PAST_n1(void)
{
    char const s[] = "xxabc";

    TEST_PTR_NULL(stlsoft_C_strnstrn(s, 4, "abc", 3));
    TEST_PTR_EQ(s + 2, stlsoft_C_strnstrn(s, 5, "abc", 3));
}

static void TEST_stlsoft_C_strnstrn_DOES_NOT_READ_PAST_n2(void)
{
    char const hay[] = "abX";
    char const needle[] = { 'a', 'b', 'Y' };

    TEST_PTR_EQ(hay, stlsoft_C_strnstrn(hay, 3, needle, 2));
    TEST_PTR_NULL(stlsoft_C_strnstrn(hay, 3, needle, 3));
}

static void TEST_stlsoft_C_strnstrn_EMBEDDED_NUL(void)
{
    char const hay[] = { 'a', '\0', 'b', 'x', 'a', '\0', 'b' };
    char const needle[] = { 'a', '\0', 'b' };

    TEST_PTR_EQ(hay, stlsoft_C_strnstrn(hay, 7, needle, 3));
    TEST_PTR_EQ(hay + 4, stlsoft_C_strnstrn(hay + 1, 6, needle, 3));
}

static void TEST_stlsoft_C_strnstrn_SINGLE_BYTE(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 1, stlsoft_C_strnstrn(s, 3, "b", 1));
    TEST_PTR_NULL(stlsoft_C_strnstrn(s, 3, "z", 1));
}

static void TEST_stlsoft_C_strnstrn_FULL_SPAN(void)
{
    char const s[] = "abcd";

    TEST_PTR_EQ(s, stlsoft_C_strnstrn(s, 4, "abcd", 4));
    TEST_PTR_NULL(stlsoft_C_strnstrn(s, 4, "abce", 4));
}

static void TEST_stlsoft_C_wcsnstrn_n2_0(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s, stlsoft_C_wcsnstrn(s, 3, L"", 0));
    TEST_PTR_EQ(s, stlsoft_C_wcsnstrn(s, 0, L"", 0));
    TEST_PTR_EQ(s, stlsoft_C_wcsnstrn(s, 3, L"xyz", 0));
}

static void TEST_stlsoft_C_wcsnstrn_n1_0(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_NULL(stlsoft_C_wcsnstrn(s, 0, L"a", 1));
}

static void TEST_stlsoft_C_wcsnstrn_n2_GT_n1(void)
{
    TEST_PTR_NULL(stlsoft_C_wcsnstrn(L"ab", 2, L"abc", 3));
    TEST_PTR_NULL(stlsoft_C_wcsnstrn(L"abcd", 4, L"abcde", 5));
}

static void TEST_stlsoft_C_wcsnstrn_MATCH_AT_START(void)
{
    wchar_t const s[] = L"abcdef";

    TEST_PTR_EQ(s, stlsoft_C_wcsnstrn(s, 6, L"abc", 3));
    TEST_PTR_EQ(s, stlsoft_C_wcsnstrn(s, 3, L"abc", 3));
}

static void TEST_stlsoft_C_wcsnstrn_MATCH_IN_MIDDLE(void)
{
    wchar_t const s[] = L"xxabcxx";

    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnstrn(s, 7, L"abc", 3));
}

static void TEST_stlsoft_C_wcsnstrn_MATCH_AT_END(void)
{
    wchar_t const s[] = L"xxabc";

    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnstrn(s, 5, L"abc", 3));
    TEST_PTR_NULL(stlsoft_C_wcsnstrn(s, 4, L"abc", 3));
}

static void TEST_stlsoft_C_wcsnstrn_MISS(void)
{
    TEST_PTR_NULL(stlsoft_C_wcsnstrn(L"abcdef", 6, L"zzz", 3));
    TEST_PTR_NULL(stlsoft_C_wcsnstrn(L"abcdef", 6, L"abx", 3));
}

static void TEST_stlsoft_C_wcsnstrn_PARTIAL_THEN_MATCH(void)
{
    wchar_t const s[] = L"abXabc";

    TEST_PTR_EQ(s + 3, stlsoft_C_wcsnstrn(s, 6, L"abc", 3));
}

static void TEST_stlsoft_C_wcsnstrn_REPEATED_FIRST_BYTE(void)
{
    wchar_t const s[] = L"aaab";
    wchar_t const t[] = L"aaa";

    TEST_PTR_EQ(s + 1, stlsoft_C_wcsnstrn(s, 4, L"aab", 3));
    TEST_PTR_EQ(t, stlsoft_C_wcsnstrn(t, 3, L"aa", 2));
}

static void TEST_stlsoft_C_wcsnstrn_DOES_NOT_READ_PAST_n1(void)
{
    wchar_t const s[] = L"xxabc";

    TEST_PTR_NULL(stlsoft_C_wcsnstrn(s, 4, L"abc", 3));
    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnstrn(s, 5, L"abc", 3));
}

static void TEST_stlsoft_C_wcsnstrn_DOES_NOT_READ_PAST_n2(void)
{
    wchar_t const hay[] = L"abX";
    wchar_t const needle[] = { L'a', L'b', L'Y' };

    TEST_PTR_EQ(hay, stlsoft_C_wcsnstrn(hay, 3, needle, 2));
    TEST_PTR_NULL(stlsoft_C_wcsnstrn(hay, 3, needle, 3));
}

static void TEST_stlsoft_C_wcsnstrn_EMBEDDED_NUL(void)
{
    wchar_t const hay[] = { L'a', L'\0', L'b', L'x', L'a', L'\0', L'b' };
    wchar_t const needle[] = { L'a', L'\0', L'b' };

    TEST_PTR_EQ(hay, stlsoft_C_wcsnstrn(hay, 7, needle, 3));
    TEST_PTR_EQ(hay + 4, stlsoft_C_wcsnstrn(hay + 1, 6, needle, 3));
}

static void TEST_stlsoft_C_wcsnstrn_SINGLE_BYTE(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 1, stlsoft_C_wcsnstrn(s, 3, L"b", 1));
    TEST_PTR_NULL(stlsoft_C_wcsnstrn(s, 3, L"z", 1));
}

static void TEST_stlsoft_C_wcsnstrn_FULL_SPAN(void)
{
    wchar_t const s[] = L"abcd";

    TEST_PTR_EQ(s, stlsoft_C_wcsnstrn(s, 4, L"abcd", 4));
    TEST_PTR_NULL(stlsoft_C_wcsnstrn(s, 4, L"abce", 4));
}


/* ///////////////////////////// end of file //////////////////////////// */
