/* /////////////////////////////////////////////////////////////////////////
 * File:    c_string.strnistrn.C/entry.c
 *
 * Purpose: Unit-tests for stlsoft_C_strnistrn() and stlsoft_C_wcsnistrn().
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

static void TEST_stlsoft_C_strnistrn_n2_0(void);
static void TEST_stlsoft_C_strnistrn_n1_0(void);
static void TEST_stlsoft_C_strnistrn_n2_GT_n1(void);
static void TEST_stlsoft_C_strnistrn_EXACT_MATCH(void);
static void TEST_stlsoft_C_strnistrn_CASE_FOLD_FULL(void);
static void TEST_stlsoft_C_strnistrn_CASE_FOLD_IN_MIDDLE(void);
static void TEST_stlsoft_C_strnistrn_CASE_FOLD_AT_END(void);
static void TEST_stlsoft_C_strnistrn_MATCH_IN_MIDDLE(void);
static void TEST_stlsoft_C_strnistrn_MATCH_AT_END(void);
static void TEST_stlsoft_C_strnistrn_MISS(void);
static void TEST_stlsoft_C_strnistrn_FIRST_CHAR_ONLY_THEN_MATCH(void);
static void TEST_stlsoft_C_strnistrn_DOES_NOT_READ_PAST_n1(void);
static void TEST_stlsoft_C_strnistrn_DOES_NOT_READ_PAST_n2(void);
static void TEST_stlsoft_C_strnistrn_SINGLE_BYTE(void);
static void TEST_stlsoft_C_strnistrn_HIGH_BIT(void);
static void TEST_stlsoft_C_wcsnistrn_n2_0(void);
static void TEST_stlsoft_C_wcsnistrn_n1_0(void);
static void TEST_stlsoft_C_wcsnistrn_n2_GT_n1(void);
static void TEST_stlsoft_C_wcsnistrn_EXACT_MATCH(void);
static void TEST_stlsoft_C_wcsnistrn_CASE_FOLD_FULL(void);
static void TEST_stlsoft_C_wcsnistrn_CASE_FOLD_IN_MIDDLE(void);
static void TEST_stlsoft_C_wcsnistrn_CASE_FOLD_AT_END(void);
static void TEST_stlsoft_C_wcsnistrn_MATCH_IN_MIDDLE(void);
static void TEST_stlsoft_C_wcsnistrn_MATCH_AT_END(void);
static void TEST_stlsoft_C_wcsnistrn_MISS(void);
static void TEST_stlsoft_C_wcsnistrn_FIRST_CHAR_ONLY_THEN_MATCH(void);
static void TEST_stlsoft_C_wcsnistrn_DOES_NOT_READ_PAST_n1(void);
static void TEST_stlsoft_C_wcsnistrn_DOES_NOT_READ_PAST_n2(void);
static void TEST_stlsoft_C_wcsnistrn_SINGLE_BYTE(void);
static void TEST_stlsoft_C_wcsnistrn_HIGH_BIT(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string.strnistrn.C", verbosity))
    {
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_n2_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_n1_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_n2_GT_n1);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_EXACT_MATCH);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_CASE_FOLD_FULL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_CASE_FOLD_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_CASE_FOLD_AT_END);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_MISS);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_FIRST_CHAR_ONLY_THEN_MATCH);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_DOES_NOT_READ_PAST_n1);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_DOES_NOT_READ_PAST_n2);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_SINGLE_BYTE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnistrn_HIGH_BIT);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_n2_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_n1_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_n2_GT_n1);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_EXACT_MATCH);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_CASE_FOLD_FULL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_CASE_FOLD_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_CASE_FOLD_AT_END);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_MISS);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_FIRST_CHAR_ONLY_THEN_MATCH);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_DOES_NOT_READ_PAST_n1);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_DOES_NOT_READ_PAST_n2);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_SINGLE_BYTE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnistrn_HIGH_BIT);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_stlsoft_C_strnistrn_n2_0(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s, stlsoft_C_strnistrn(s, 3, "", 0));
    TEST_PTR_EQ(s, stlsoft_C_strnistrn(s, 0, "xyz", 0));
}

static void TEST_stlsoft_C_strnistrn_n1_0(void)
{
    TEST_PTR_NULL(stlsoft_C_strnistrn("abc", 0, "a", 1));
}

static void TEST_stlsoft_C_strnistrn_n2_GT_n1(void)
{
    TEST_PTR_NULL(stlsoft_C_strnistrn("ab", 2, "abc", 3));
}

static void TEST_stlsoft_C_strnistrn_EXACT_MATCH(void)
{
    char const s[] = "abcdef";

    TEST_PTR_EQ(s, stlsoft_C_strnistrn(s, 6, "abc", 3));
    TEST_PTR_EQ(s, stlsoft_C_strnistrn(s, 3, "abc", 3));
}

static void TEST_stlsoft_C_strnistrn_CASE_FOLD_FULL(void)
{
    char const s[] = "xxAbCxx";

    TEST_PTR_EQ(s + 2, stlsoft_C_strnistrn(s, 7, "aBc", 3));
    TEST_PTR_EQ(s + 2, stlsoft_C_strnistrn(s, 7, "ABC", 3));
}

static void TEST_stlsoft_C_strnistrn_CASE_FOLD_IN_MIDDLE(void)
{
    char const s[] = "aBc";

    TEST_PTR_EQ(s, stlsoft_C_strnistrn(s, 3, "abc", 3));
    TEST_PTR_NULL(stlsoft_C_strnistrn(s, 3, "axc", 3));
}

static void TEST_stlsoft_C_strnistrn_CASE_FOLD_AT_END(void)
{
    char const s[] = "zzAB";

    TEST_PTR_EQ(s + 2, stlsoft_C_strnistrn(s, 4, "ab", 2));
    TEST_PTR_NULL(stlsoft_C_strnistrn(s, 3, "ab", 2));
}

static void TEST_stlsoft_C_strnistrn_MATCH_IN_MIDDLE(void)
{
    char const s[] = "xxabcxx";

    TEST_PTR_EQ(s + 2, stlsoft_C_strnistrn(s, 7, "AbC", 3));
}

static void TEST_stlsoft_C_strnistrn_MATCH_AT_END(void)
{
    char const s[] = "xxabc";

    TEST_PTR_EQ(s + 2, stlsoft_C_strnistrn(s, 5, "ABC", 3));
}

static void TEST_stlsoft_C_strnistrn_MISS(void)
{
    TEST_PTR_NULL(stlsoft_C_strnistrn("abcdef", 6, "zzz", 3));
    TEST_PTR_NULL(stlsoft_C_strnistrn("abcdef", 6, "abx", 3));
    TEST_PTR_NULL(stlsoft_C_strnistrn("aXY", 3, "abc", 3));
}

static void TEST_stlsoft_C_strnistrn_FIRST_CHAR_ONLY_THEN_MATCH(void)
{
    char const s[] = "aXYabc";

    TEST_PTR_EQ(s + 3, stlsoft_C_strnistrn(s, 6, "ABC", 3));
    TEST_PTR_NULL(stlsoft_C_strnistrn("aXY", 3, "ABC", 3));
}

static void TEST_stlsoft_C_strnistrn_DOES_NOT_READ_PAST_n1(void)
{
    char const s[] = "xxabc";

    TEST_PTR_NULL(stlsoft_C_strnistrn(s, 4, "ABC", 3));
    TEST_PTR_EQ(s + 2, stlsoft_C_strnistrn(s, 5, "ABC", 3));
}

static void TEST_stlsoft_C_strnistrn_DOES_NOT_READ_PAST_n2(void)
{
    char const hay[] = "abX";
    char const needle[] = { 'A', 'B', 'Y' };

    TEST_PTR_EQ(hay, stlsoft_C_strnistrn(hay, 3, needle, 2));
    TEST_PTR_NULL(stlsoft_C_strnistrn(hay, 3, needle, 3));
}

static void TEST_stlsoft_C_strnistrn_SINGLE_BYTE(void)
{
    char const s[] = "xxA";

    TEST_PTR_EQ(s + 2, stlsoft_C_strnistrn(s, 3, "a", 1));
    TEST_PTR_NULL(stlsoft_C_strnistrn(s, 2, "a", 1));
}

static void TEST_stlsoft_C_strnistrn_HIGH_BIT(void)
{
    unsigned char const hay_u[] = { 0xE9, 'A', 'b' };
    unsigned char const needle_u[] = { 0xE9, 'a', 'B' };
    unsigned char const other_u[] = { 0xE2, 'a' };
    char const* const   hay = (char const*)hay_u;
    char const* const   needle = (char const*)needle_u;
    char const* const   other = (char const*)other_u;

    TEST_PTR_EQ(hay, stlsoft_C_strnistrn(hay, 3, needle, 3));
    TEST_PTR_NULL(stlsoft_C_strnistrn(hay, 2, other, 2));
}

static void TEST_stlsoft_C_wcsnistrn_n2_0(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s, stlsoft_C_wcsnistrn(s, 3, L"", 0));
    TEST_PTR_EQ(s, stlsoft_C_wcsnistrn(s, 0, L"xyz", 0));
}

static void TEST_stlsoft_C_wcsnistrn_n1_0(void)
{
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(L"abc", 0, L"a", 1));
}

static void TEST_stlsoft_C_wcsnistrn_n2_GT_n1(void)
{
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(L"ab", 2, L"abc", 3));
}

static void TEST_stlsoft_C_wcsnistrn_EXACT_MATCH(void)
{
    wchar_t const s[] = L"abcdef";

    TEST_PTR_EQ(s, stlsoft_C_wcsnistrn(s, 6, L"abc", 3));
    TEST_PTR_EQ(s, stlsoft_C_wcsnistrn(s, 3, L"abc", 3));
}

static void TEST_stlsoft_C_wcsnistrn_CASE_FOLD_FULL(void)
{
    wchar_t const s[] = L"xxAbCxx";

    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnistrn(s, 7, L"aBc", 3));
    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnistrn(s, 7, L"ABC", 3));
}

static void TEST_stlsoft_C_wcsnistrn_CASE_FOLD_IN_MIDDLE(void)
{
    wchar_t const s[] = L"aBc";

    TEST_PTR_EQ(s, stlsoft_C_wcsnistrn(s, 3, L"abc", 3));
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(s, 3, L"axc", 3));
}

static void TEST_stlsoft_C_wcsnistrn_CASE_FOLD_AT_END(void)
{
    wchar_t const s[] = L"zzAB";

    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnistrn(s, 4, L"ab", 2));
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(s, 3, L"ab", 2));
}

static void TEST_stlsoft_C_wcsnistrn_MATCH_IN_MIDDLE(void)
{
    wchar_t const s[] = L"xxabcxx";

    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnistrn(s, 7, L"AbC", 3));
}

static void TEST_stlsoft_C_wcsnistrn_MATCH_AT_END(void)
{
    wchar_t const s[] = L"xxabc";

    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnistrn(s, 5, L"ABC", 3));
}

static void TEST_stlsoft_C_wcsnistrn_MISS(void)
{
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(L"abcdef", 6, L"zzz", 3));
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(L"abcdef", 6, L"abx", 3));
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(L"aXY", 3, L"abc", 3));
}

static void TEST_stlsoft_C_wcsnistrn_FIRST_CHAR_ONLY_THEN_MATCH(void)
{
    wchar_t const s[] = L"aXYabc";

    TEST_PTR_EQ(s + 3, stlsoft_C_wcsnistrn(s, 6, L"ABC", 3));
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(L"aXY", 3, L"ABC", 3));
}

static void TEST_stlsoft_C_wcsnistrn_DOES_NOT_READ_PAST_n1(void)
{
    wchar_t const s[] = L"xxabc";

    TEST_PTR_NULL(stlsoft_C_wcsnistrn(s, 4, L"ABC", 3));
    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnistrn(s, 5, L"ABC", 3));
}

static void TEST_stlsoft_C_wcsnistrn_DOES_NOT_READ_PAST_n2(void)
{
    wchar_t const hay[] = L"abX";
    wchar_t const needle[] = { L'A', L'B', L'Y' };

    TEST_PTR_EQ(hay, stlsoft_C_wcsnistrn(hay, 3, needle, 2));
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(hay, 3, needle, 3));
}

static void TEST_stlsoft_C_wcsnistrn_SINGLE_BYTE(void)
{
    wchar_t const s[] = L"xxA";

    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnistrn(s, 3, L"a", 1));
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(s, 2, L"a", 1));
}

static void TEST_stlsoft_C_wcsnistrn_HIGH_BIT(void)
{
    wchar_t const hay[] = { L'\x00E9', L'A', L'b' };
    wchar_t const needle[] = { L'\x00E9', L'a', L'B' };
    wchar_t const other[] = { L'\x00E2', L'a' };

    TEST_PTR_EQ(hay, stlsoft_C_wcsnistrn(hay, 3, needle, 3));
    TEST_PTR_NULL(stlsoft_C_wcsnistrn(hay, 2, other, 2));
}


/* ///////////////////////////// end of file //////////////////////////// */
