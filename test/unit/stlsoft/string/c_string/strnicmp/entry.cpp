/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/c_string.strnicmp/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::c_string::strnicmp() and wcsnicmp().
 *
 * Created: 29th September 2026
 * Updated: 25th October 2026
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
    static void TEST_c_string_strnicmp_n_1();
    static void TEST_c_string_strnicmp_STOPS_AT_NUL();
    static void TEST_c_string_strnicmp_NUL_AT_START();
    static void TEST_c_string_strnicmp_IGNORES_BYTE_PAST_n();
    static void TEST_c_string_strnicmp_DIFFER_AT_LAST();
    static void TEST_c_string_strnicmp_ASCII_CASE_FOLD();
    static void TEST_c_string_strnicmp_CASE_THEN_DIFFER();
    static void TEST_c_string_strnicmp_NON_LETTER();
    static void TEST_c_string_strnicmp_HIGH_BIT();
    static void TEST_c_string_wcsnicmp_EQUAL();
    static void TEST_c_string_wcsnicmp_LESS();
    static void TEST_c_string_wcsnicmp_GREATER();
    static void TEST_c_string_wcsnicmp_n_0();
    static void TEST_c_string_wcsnicmp_n_1();
    static void TEST_c_string_wcsnicmp_STOPS_AT_NUL();
    static void TEST_c_string_wcsnicmp_NUL_AT_START();
    static void TEST_c_string_wcsnicmp_IGNORES_BYTE_PAST_n();
    static void TEST_c_string_wcsnicmp_DIFFER_AT_LAST();
    static void TEST_c_string_wcsnicmp_ASCII_CASE_FOLD();
    static void TEST_c_string_wcsnicmp_CASE_THEN_DIFFER();
    static void TEST_c_string_wcsnicmp_NON_LETTER();
    static void TEST_c_string_wcsnicmp_HIGH_BIT();

    static int wcsnicmp_both_(wchar_t const* s1, wchar_t const* s2, size_t n);
} // anonymous namespace


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
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_n_1);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_STOPS_AT_NUL);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_NUL_AT_START);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_IGNORES_BYTE_PAST_n);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_DIFFER_AT_LAST);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_ASCII_CASE_FOLD);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_CASE_THEN_DIFFER);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_NON_LETTER);
        XTESTS_RUN_CASE(TEST_c_string_strnicmp_HIGH_BIT);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_EQUAL);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_LESS);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_GREATER);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_n_0);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_n_1);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_STOPS_AT_NUL);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_NUL_AT_START);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_IGNORES_BYTE_PAST_n);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_DIFFER_AT_LAST);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_ASCII_CASE_FOLD);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_CASE_THEN_DIFFER);
        XTESTS_RUN_CASE(TEST_c_string_wcsnicmp_NON_LETTER);
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

static void TEST_c_string_strnicmp_n_1()
{
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("aX", "Ay", 1));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp("A", "b", 1));
    TEST_INT_GT(0, stlsoft::c_string::strnicmp("b", "A", 1));
}

static void TEST_c_string_strnicmp_STOPS_AT_NUL()
{
    char const s1[] = { 'a', '\0', 'x' };
    char const s2[] = { 'a', '\0', 'y' };

    TEST_INT_EQ(0, stlsoft::c_string::strnicmp(s1, s2, 3));
}

static void TEST_c_string_strnicmp_NUL_AT_START()
{
    char const both[] = { '\0', 'x' };
    char const only[] = { '\0', 'y' };

    TEST_INT_EQ(0, stlsoft::c_string::strnicmp(both, only, 2));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp(both, "a", 1));
    TEST_INT_GT(0, stlsoft::c_string::strnicmp("a", only, 1));
}

static void TEST_c_string_strnicmp_IGNORES_BYTE_PAST_n()
{
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("abX", "abY", 2));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp("abX", "abY", 3));
}

static void TEST_c_string_strnicmp_DIFFER_AT_LAST()
{
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("abcd", "abce", 3));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp("abcd", "abce", 4));
    TEST_INT_GT(0, stlsoft::c_string::strnicmp("abce", "abcd", 4));
}

static void TEST_c_string_strnicmp_ASCII_CASE_FOLD()
{
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("AbC", "aBc", 3));
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("AbC", "aBc", 10));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp("abC", "aBd", 3));
    TEST_INT_GT(0, stlsoft::c_string::strnicmp("B", "a", 1));
}

static void TEST_c_string_strnicmp_CASE_THEN_DIFFER()
{
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("abcX", "ABCx", 4));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp("abcX", "ABCY", 4));
    TEST_INT_GT(0, stlsoft::c_string::strnicmp("ABCY", "abcX", 4));
}

static void TEST_c_string_strnicmp_NON_LETTER()
{
    TEST_INT_EQ(0, stlsoft::c_string::strnicmp("a1!", "A1!", 3));
    TEST_INT_LT(0, stlsoft::c_string::strnicmp("a1!", "A1?", 3));
    TEST_INT_GT(0, stlsoft::c_string::strnicmp("A1?", "a1!", 3));
}

static void TEST_c_string_strnicmp_HIGH_BIT()
{
    unsigned char const same1_u[] = { 0xE9, 'A', 0 };
    unsigned char const same2_u[] = { 0xE9, 'a', 0 };
    unsigned char const later_u[] = { 0xE9, 'B', 0 };
    unsigned char const lo_u[] = { 0xE1, 0 };
    unsigned char const hi_u[] = { 0xE2, 0 };
    char const* const   same1 = reinterpret_cast<char const*>(same1_u);
    char const* const   same2 = reinterpret_cast<char const*>(same2_u);
    char const* const   later = reinterpret_cast<char const*>(later_u);
    char const* const   lo = reinterpret_cast<char const*>(lo_u);
    char const* const   hi = reinterpret_cast<char const*>(hi_u);

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

static void TEST_c_string_wcsnicmp_n_1()
{
    TEST_INT_EQ(0, wcsnicmp_both_(L"aX", L"Ay", 1));
    TEST_INT_LT(0, wcsnicmp_both_(L"A", L"b", 1));
    TEST_INT_GT(0, wcsnicmp_both_(L"b", L"A", 1));
}

static void TEST_c_string_wcsnicmp_STOPS_AT_NUL()
{
    wchar_t const s1[] = { L'a', L'\0', L'x' };
    wchar_t const s2[] = { L'a', L'\0', L'y' };

    TEST_INT_EQ(0, wcsnicmp_both_(s1, s2, 3));
}

static void TEST_c_string_wcsnicmp_NUL_AT_START()
{
    wchar_t const both[] = { L'\0', L'x' };
    wchar_t const only[] = { L'\0', L'y' };

    TEST_INT_EQ(0, wcsnicmp_both_(both, only, 2));
    TEST_INT_LT(0, wcsnicmp_both_(both, L"a", 1));
    TEST_INT_GT(0, wcsnicmp_both_(L"a", only, 1));
}

static void TEST_c_string_wcsnicmp_IGNORES_BYTE_PAST_n()
{
    TEST_INT_EQ(0, wcsnicmp_both_(L"abX", L"abY", 2));
    TEST_INT_LT(0, wcsnicmp_both_(L"abX", L"abY", 3));
}

static void TEST_c_string_wcsnicmp_DIFFER_AT_LAST()
{
    TEST_INT_EQ(0, wcsnicmp_both_(L"abcd", L"abce", 3));
    TEST_INT_LT(0, wcsnicmp_both_(L"abcd", L"abce", 4));
    TEST_INT_GT(0, wcsnicmp_both_(L"abce", L"abcd", 4));
}

static void TEST_c_string_wcsnicmp_ASCII_CASE_FOLD()
{
    TEST_INT_EQ(0, wcsnicmp_both_(L"AbC", L"aBc", 3));
    TEST_INT_EQ(0, wcsnicmp_both_(L"AbC", L"aBc", 10));
    TEST_INT_LT(0, wcsnicmp_both_(L"abC", L"aBd", 3));
    TEST_INT_GT(0, wcsnicmp_both_(L"B", L"a", 1));
}

static void TEST_c_string_wcsnicmp_CASE_THEN_DIFFER()
{
    TEST_INT_EQ(0, wcsnicmp_both_(L"abcX", L"ABCx", 4));
    TEST_INT_LT(0, wcsnicmp_both_(L"abcX", L"ABCY", 4));
    TEST_INT_GT(0, wcsnicmp_both_(L"ABCY", L"abcX", 4));
}

static void TEST_c_string_wcsnicmp_NON_LETTER()
{
    TEST_INT_EQ(0, wcsnicmp_both_(L"a1!", L"A1!", 3));
    TEST_INT_LT(0, wcsnicmp_both_(L"a1!", L"A1?", 3));
    TEST_INT_GT(0, wcsnicmp_both_(L"A1?", L"a1!", 3));
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
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

