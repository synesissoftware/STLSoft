/* /////////////////////////////////////////////////////////////////////////
 * File:    c_string.strnicmp.C/entry.c
 *
 * Purpose: Unit-tests for stlsoft_C_strnicmp() and stlsoft_C_wcsnicmp().
 *
 * Created: 29th September 2026
 * Updated: 29th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/c_string/strnicmp.h>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <xtests/terse-api.h>
#include <xtests/xtests.h>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_stlsoft_C_strnicmp_EQUAL(void);
static void TEST_stlsoft_C_strnicmp_LESS(void);
static void TEST_stlsoft_C_strnicmp_GREATER(void);
static void TEST_stlsoft_C_strnicmp_n_0(void);
static void TEST_stlsoft_C_strnicmp_STOPS_AT_NUL(void);
static void TEST_stlsoft_C_strnicmp_IGNORES_BYTE_PAST_n(void);
static void TEST_stlsoft_C_strnicmp_ASCII_CASE_FOLD(void);
static void TEST_stlsoft_C_strnicmp_HIGH_BIT(void);
static void TEST_stlsoft_C_wcsnicmp_EQUAL(void);
static void TEST_stlsoft_C_wcsnicmp_LESS(void);
static void TEST_stlsoft_C_wcsnicmp_GREATER(void);
static void TEST_stlsoft_C_wcsnicmp_n_0(void);
static void TEST_stlsoft_C_wcsnicmp_STOPS_AT_NUL(void);
static void TEST_stlsoft_C_wcsnicmp_IGNORES_BYTE_PAST_n(void);
static void TEST_stlsoft_C_wcsnicmp_ASCII_CASE_FOLD(void);
static void TEST_stlsoft_C_wcsnicmp_HIGH_BIT(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string.strnicmp.C", verbosity))
    {
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnicmp_EQUAL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnicmp_LESS);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnicmp_GREATER);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnicmp_n_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnicmp_STOPS_AT_NUL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnicmp_IGNORES_BYTE_PAST_n);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnicmp_ASCII_CASE_FOLD);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnicmp_HIGH_BIT);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnicmp_EQUAL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnicmp_LESS);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnicmp_GREATER);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnicmp_n_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnicmp_STOPS_AT_NUL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnicmp_IGNORES_BYTE_PAST_n);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnicmp_ASCII_CASE_FOLD);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnicmp_HIGH_BIT);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_stlsoft_C_strnicmp_EQUAL(void)
{
    TEST_INT_EQ(0, stlsoft_C_strnicmp("abc", "abc", 3));
    TEST_INT_EQ(0, stlsoft_C_strnicmp("abc", "abc", 10));
    TEST_INT_EQ(0, stlsoft_C_strnicmp("", "", 1));
}

static void TEST_stlsoft_C_strnicmp_LESS(void)
{
    TEST_INT_LT(0, stlsoft_C_strnicmp("abc", "abd", 3));
    TEST_INT_LT(0, stlsoft_C_strnicmp("ab", "abc", 3));
}

static void TEST_stlsoft_C_strnicmp_GREATER(void)
{
    TEST_INT_GT(0, stlsoft_C_strnicmp("abd", "abc", 3));
    TEST_INT_GT(0, stlsoft_C_strnicmp("abc", "ab", 3));
}

static void TEST_stlsoft_C_strnicmp_n_0(void)
{
    TEST_INT_EQ(0, stlsoft_C_strnicmp("abc", "xyz", 0));
    TEST_INT_EQ(0, stlsoft_C_strnicmp("", "abc", 0));
}

static void TEST_stlsoft_C_strnicmp_STOPS_AT_NUL(void)
{
    char const s1[] = { 'a', '\0', 'x' };
    char const s2[] = { 'a', '\0', 'y' };

    TEST_INT_EQ(0, stlsoft_C_strnicmp(s1, s2, 3));
}

static void TEST_stlsoft_C_strnicmp_IGNORES_BYTE_PAST_n(void)
{
    TEST_INT_EQ(0, stlsoft_C_strnicmp("abX", "abY", 2));
    TEST_INT_LT(0, stlsoft_C_strnicmp("abX", "abY", 3));
}

static void TEST_stlsoft_C_strnicmp_ASCII_CASE_FOLD(void)
{
    TEST_INT_EQ(0, stlsoft_C_strnicmp("AbC", "aBc", 3));
    TEST_INT_EQ(0, stlsoft_C_strnicmp("AbC", "aBc", 10));
    TEST_INT_LT(0, stlsoft_C_strnicmp("abC", "aBd", 3));
    TEST_INT_GT(0, stlsoft_C_strnicmp("B", "a", 1));
}

static void TEST_stlsoft_C_strnicmp_HIGH_BIT(void)
{
    char const same1[] = { (char)0xE9, 'A', '\0' };
    char const same2[] = { (char)0xE9, 'a', '\0' };
    char const later[] = { (char)0xE9, 'B', '\0' };
    char const lo[] = { (char)0xE1, '\0' };
    char const hi[] = { (char)0xE2, '\0' };

    TEST_INT_EQ(0, stlsoft_C_strnicmp(same1, same2, 2));
    TEST_INT_LT(0, stlsoft_C_strnicmp(same1, later, 2));
    TEST_INT_LT(0, stlsoft_C_strnicmp(lo, hi, 1));
    TEST_INT_GT(0, stlsoft_C_strnicmp(hi, lo, 1));
}

static void TEST_stlsoft_C_wcsnicmp_EQUAL(void)
{
    TEST_INT_EQ(0, stlsoft_C_wcsnicmp(L"abc", L"abc", 3));
    TEST_INT_EQ(0, stlsoft_C_wcsnicmp(L"abc", L"abc", 10));
    TEST_INT_EQ(0, stlsoft_C_wcsnicmp(L"", L"", 1));
}

static void TEST_stlsoft_C_wcsnicmp_LESS(void)
{
    TEST_INT_LT(0, stlsoft_C_wcsnicmp(L"abc", L"abd", 3));
    TEST_INT_LT(0, stlsoft_C_wcsnicmp(L"ab", L"abc", 3));
}

static void TEST_stlsoft_C_wcsnicmp_GREATER(void)
{
    TEST_INT_GT(0, stlsoft_C_wcsnicmp(L"abd", L"abc", 3));
    TEST_INT_GT(0, stlsoft_C_wcsnicmp(L"abc", L"ab", 3));
}

static void TEST_stlsoft_C_wcsnicmp_n_0(void)
{
    TEST_INT_EQ(0, stlsoft_C_wcsnicmp(L"abc", L"xyz", 0));
    TEST_INT_EQ(0, stlsoft_C_wcsnicmp(L"", L"abc", 0));
}

static void TEST_stlsoft_C_wcsnicmp_STOPS_AT_NUL(void)
{
    wchar_t const s1[] = { L'a', L'\0', L'x' };
    wchar_t const s2[] = { L'a', L'\0', L'y' };

    TEST_INT_EQ(0, stlsoft_C_wcsnicmp(s1, s2, 3));
}

static void TEST_stlsoft_C_wcsnicmp_IGNORES_BYTE_PAST_n(void)
{
    TEST_INT_EQ(0, stlsoft_C_wcsnicmp(L"abX", L"abY", 2));
    TEST_INT_LT(0, stlsoft_C_wcsnicmp(L"abX", L"abY", 3));
}

static void TEST_stlsoft_C_wcsnicmp_ASCII_CASE_FOLD(void)
{
    TEST_INT_EQ(0, stlsoft_C_wcsnicmp(L"AbC", L"aBc", 3));
    TEST_INT_EQ(0, stlsoft_C_wcsnicmp(L"AbC", L"aBc", 10));
    TEST_INT_LT(0, stlsoft_C_wcsnicmp(L"abC", L"aBd", 3));
    TEST_INT_GT(0, stlsoft_C_wcsnicmp(L"B", L"a", 1));
}

static void TEST_stlsoft_C_wcsnicmp_HIGH_BIT(void)
{
    wchar_t const same1[] = { L'\x00E9', L'A', L'\0' };
    wchar_t const same2[] = { L'\x00E9', L'a', L'\0' };
    wchar_t const later[] = { L'\x00E9', L'B', L'\0' };
    wchar_t const lo[] = { L'\x00E1', L'\0' };
    wchar_t const hi[] = { L'\x00E2', L'\0' };

    TEST_INT_EQ(0, stlsoft_C_wcsnicmp(same1, same2, 2));
    TEST_INT_LT(0, stlsoft_C_wcsnicmp(same1, later, 2));
    TEST_INT_LT(0, stlsoft_C_wcsnicmp(lo, hi, 1));
    TEST_INT_GT(0, stlsoft_C_wcsnicmp(hi, lo, 1));
}


/* ///////////////////////////// end of file //////////////////////////// */

