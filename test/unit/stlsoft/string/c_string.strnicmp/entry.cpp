/* /////////////////////////////////////////////////////////////////////////
 * File:    c_string.strnicmp/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::c_string::strnicmp() and wcsnicmp().
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

namespace
{

    static void TEST_c_string_strnicmp_EQUAL();
    static void TEST_c_string_strnicmp_LESS();
    static void TEST_c_string_strnicmp_GREATER();
    static void TEST_c_string_strnicmp_n_0();
    static void TEST_c_string_strnicmp_STOPS_AT_NUL();
    static void TEST_c_string_strnicmp_IGNORES_BYTE_PAST_n();
    static void TEST_c_string_strnicmp_ASCII_CASE_FOLD();
    static void TEST_c_string_strnicmp_HIGH_BIT();
    static void TEST_c_string_wcsnicmp_EQUAL();
    static void TEST_c_string_wcsnicmp_LESS();
    static void TEST_c_string_wcsnicmp_GREATER();
    static void TEST_c_string_wcsnicmp_n_0();
    static void TEST_c_string_wcsnicmp_STOPS_AT_NUL();
    static void TEST_c_string_wcsnicmp_IGNORES_BYTE_PAST_n();
    static void TEST_c_string_wcsnicmp_ASCII_CASE_FOLD();
    static void TEST_c_string_wcsnicmp_HIGH_BIT();

    static int wcsnicmp_both_(wchar_t const* s1, wchar_t const* s2, size_t n);

} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string.strnicmp", verbosity))
    {
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_EQUAL);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_LESS);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_GREATER);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_n_0);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_STOPS_AT_NUL);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_IGNORES_BYTE_PAST_n);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_ASCII_CASE_FOLD);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_HIGH_BIT);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_EQUAL);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_LESS);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_GREATER);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_n_0);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_STOPS_AT_NUL);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_IGNORES_BYTE_PAST_n);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_ASCII_CASE_FOLD);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_HIGH_BIT);

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

static int wcsnicmp_both_(wchar_t const* s1, wchar_t const* s2, size_t n)
{
    int const via_str = stlsoft::c_string::strnicmp(s1, s2, n);
    int const via_wcs = stlsoft::c_string::wcsnicmp(s1, s2, n);

    TEST_INT_EQ(via_wcs, via_str);

    return via_wcs;
}

static void TEST_c_string_strnicmp_EQUAL()
{
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("abc", "abc", 3));
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("abc", "abc", 10));
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("", "", 1));
}

static void TEST_c_string_strnicmp_LESS()
{
    TEST_INT_LT(0, stlsoft::c_string::strnicmp("abc", "abd", 3));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp("ab", "abc", 3));
}

static void TEST_c_string_strnicmp_GREATER()
{
    TEST_INT_GT(0, stlsoft::c_string::strnicmp("abd", "abc", 3));
    TEST_INT_GT(0, stlsoft::c_string::strnicmp("abc", "ab", 3));
}

static void TEST_c_string_strnicmp_n_0()
{
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("abc", "xyz", 0));
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("", "abc", 0));
}

static void TEST_c_string_strnicmp_STOPS_AT_NUL()
{
    char const s1[] = { 'a', '\0', 'x' };
    char const s2[] = { 'a', '\0', 'y' };

    TEST_INT_EQ(0, stlsoft::c_string::strnicmp(s1, s2, 3));
}

static void TEST_c_string_strnicmp_IGNORES_BYTE_PAST_n()
{
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("abX", "abY", 2));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp("abX", "abY", 3));
}

static void TEST_c_string_strnicmp_ASCII_CASE_FOLD()
{
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("AbC", "aBc", 3));
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("AbC", "aBc", 10));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp("abC", "aBd", 3));
    TEST_INT_GT(0, stlsoft::c_string::strnicmp("B", "a", 1));
}

static void TEST_c_string_strnicmp_HIGH_BIT()
{
    char const same1[] = { (char)0xE9, 'A', '\0' };
    char const same2[] = { (char)0xE9, 'a', '\0' };
    char const later[] = { (char)0xE9, 'B', '\0' };
    char const lo[] = { (char)0xE1, '\0' };
    char const hi[] = { (char)0xE2, '\0' };

    TEST_INT_EQ(0, stlsoft::c_string::strnicmp(same1, same2, 2));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp(same1, later, 2));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp(lo, hi, 1));
    TEST_INT_GT(0, stlsoft::c_string::strnicmp(hi, lo, 1));
}

static void TEST_c_string_wcsnicmp_EQUAL()
{
    TEST_INT_EQ(0, wcsnicmp_both_(L"abc", L"abc", 3));
    TEST_INT_EQ(0, wcsnicmp_both_(L"abc", L"abc", 10));
    TEST_INT_EQ(0, wcsnicmp_both_(L"", L"", 1));
}

static void TEST_c_string_wcsnicmp_LESS()
{
    TEST_INT_LT(0, wcsnicmp_both_(L"abc", L"abd", 3));
    TEST_INT_LT(0, wcsnicmp_both_(L"ab", L"abc", 3));
}

static void TEST_c_string_wcsnicmp_GREATER()
{
    TEST_INT_GT(0, wcsnicmp_both_(L"abd", L"abc", 3));
    TEST_INT_GT(0, wcsnicmp_both_(L"abc", L"ab", 3));
}

static void TEST_c_string_wcsnicmp_n_0()
{
    TEST_INT_EQ(0, wcsnicmp_both_(L"abc", L"xyz", 0));
    TEST_INT_EQ(0, wcsnicmp_both_(L"", L"abc", 0));
}

static void TEST_c_string_wcsnicmp_STOPS_AT_NUL()
{
    wchar_t const s1[] = { L'a', L'\0', L'x' };
    wchar_t const s2[] = { L'a', L'\0', L'y' };

    TEST_INT_EQ(0, wcsnicmp_both_(s1, s2, 3));
}

static void TEST_c_string_wcsnicmp_IGNORES_BYTE_PAST_n()
{
    TEST_INT_EQ(0, wcsnicmp_both_(L"abX", L"abY", 2));
    TEST_INT_LT(0, wcsnicmp_both_(L"abX", L"abY", 3));
}

static void TEST_c_string_wcsnicmp_ASCII_CASE_FOLD()
{
    TEST_INT_EQ(0, wcsnicmp_both_(L"AbC", L"aBc", 3));
    TEST_INT_EQ(0, wcsnicmp_both_(L"AbC", L"aBc", 10));
    TEST_INT_LT(0, wcsnicmp_both_(L"abC", L"aBd", 3));
    TEST_INT_GT(0, wcsnicmp_both_(L"B", L"a", 1));
}

static void TEST_c_string_wcsnicmp_HIGH_BIT()
{
    wchar_t const same1[] = { L'\x00E9', L'A', L'\0' };
    wchar_t const same2[] = { L'\x00E9', L'a', L'\0' };
    wchar_t const later[] = { L'\x00E9', L'B', L'\0' };
    wchar_t const lo[] = { L'\x00E1', L'\0' };
    wchar_t const hi[] = { L'\x00E2', L'\0' };

    TEST_INT_EQ(0, wcsnicmp_both_(same1, same2, 2));
    TEST_INT_LT(0, wcsnicmp_both_(same1, later, 2));
    TEST_INT_LT(0, wcsnicmp_both_(lo, hi, 1));
    TEST_INT_GT(0, wcsnicmp_both_(hi, lo, 1));
}

} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

