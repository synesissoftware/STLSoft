/* /////////////////////////////////////////////////////////////////////////
 * File:    c_string_traits/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::c_string_traits compare functions.
 *
 * Created: 29th September 2026
 * Updated: 29th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/c_string_traits.hpp>


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

    static void TEST_str_compare_CHAR();
    static void TEST_str_compare_WCHAR();
    static void TEST_str_n_compare_n_0();
    static void TEST_str_n_compare_STOPS_AT_NUL();
    static void TEST_str_n_compare_IGNORES_BYTE_PAST_n();
    static void TEST_str_compare_no_case_ASCII();
    static void TEST_str_n_compare_no_case_ASCII();

} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_str_compare_CHAR);
        XTESTS_RUN_CASE(TEST_str_compare_WCHAR);
        XTESTS_RUN_CASE(TEST_str_n_compare_n_0);
        XTESTS_RUN_CASE(TEST_str_n_compare_STOPS_AT_NUL);
        XTESTS_RUN_CASE(TEST_str_n_compare_IGNORES_BYTE_PAST_n);
        XTESTS_RUN_CASE(TEST_str_compare_no_case_ASCII);
        XTESTS_RUN_CASE(TEST_str_n_compare_no_case_ASCII);

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

typedef stlsoft::c_string_traits<char>                      a_traits_t;
typedef stlsoft::c_string_traits<wchar_t>                   w_traits_t;

static void TEST_str_compare_CHAR()
{
    TEST_INT_EQ(0, a_traits_t::str_compare("abc", "abc"));
    TEST_INT_EQ(0, a_traits_t::str_compare("", ""));
    TEST_INT_LT(0, a_traits_t::str_compare("abc", "abd"));
    TEST_INT_LT(0, a_traits_t::str_compare("", "a"));
    TEST_INT_GT(0, a_traits_t::str_compare("abd", "abc"));
    TEST_INT_GT(0, a_traits_t::str_compare("abc", "ab"));
    TEST_INT_LT(0, a_traits_t::str_compare("A", "a"));
    TEST_INT_NE(0, a_traits_t::str_compare("AbC", "aBc"));
}

static void TEST_str_compare_WCHAR()
{
    TEST_INT_EQ(0, w_traits_t::str_compare(L"abc", L"abc"));
    TEST_INT_EQ(0, w_traits_t::str_compare(L"", L""));
    TEST_INT_LT(0, w_traits_t::str_compare(L"abc", L"abd"));
    TEST_INT_LT(0, w_traits_t::str_compare(L"", L"a"));
    TEST_INT_GT(0, w_traits_t::str_compare(L"abd", L"abc"));
    TEST_INT_GT(0, w_traits_t::str_compare(L"abc", L"ab"));
    TEST_INT_LT(0, w_traits_t::str_compare(L"A", L"a"));
    TEST_INT_NE(0, w_traits_t::str_compare(L"AbC", L"aBc"));
}

static void TEST_str_n_compare_n_0()
{
    TEST_INT_EQ(0, a_traits_t::str_n_compare("abc", "xyz", 0));
    TEST_INT_EQ(0, a_traits_t::str_n_compare("", "abc", 0));
    TEST_INT_EQ(0, w_traits_t::str_n_compare(L"abc", L"xyz", 0));
    TEST_INT_EQ(0, w_traits_t::str_n_compare(L"", L"abc", 0));
}

static void TEST_str_n_compare_STOPS_AT_NUL()
{
    char const a1[] = { 'a', '\0', 'x' };
    char const a2[] = { 'a', '\0', 'y' };
    wchar_t const w1[] = { L'a', L'\0', L'x' };
    wchar_t const w2[] = { L'a', L'\0', L'y' };

    TEST_INT_EQ(0, a_traits_t::str_n_compare(a1, a2, 3));
    TEST_INT_EQ(0, w_traits_t::str_n_compare(w1, w2, 3));
}

static void TEST_str_n_compare_IGNORES_BYTE_PAST_n()
{
    TEST_INT_EQ(0, a_traits_t::str_n_compare("abX", "abY", 2));
    TEST_INT_LT(0, a_traits_t::str_n_compare("abX", "abY", 3));
    TEST_INT_EQ(0, w_traits_t::str_n_compare(L"abX", L"abY", 2));
    TEST_INT_LT(0, w_traits_t::str_n_compare(L"abX", L"abY", 3));
}

static void TEST_str_compare_no_case_ASCII()
{
    TEST_INT_EQ(0, a_traits_t::str_compare_no_case("AbC", "aBc"));
    TEST_INT_EQ(0, a_traits_t::str_compare_no_case("", ""));
    TEST_INT_LT(0, a_traits_t::str_compare_no_case("abC", "aBd"));
    TEST_INT_GT(0, a_traits_t::str_compare_no_case("B", "a"));
    TEST_INT_EQ(0, w_traits_t::str_compare_no_case(L"AbC", L"aBc"));
    TEST_INT_EQ(0, w_traits_t::str_compare_no_case(L"", L""));
    TEST_INT_LT(0, w_traits_t::str_compare_no_case(L"abC", L"aBd"));
    TEST_INT_GT(0, w_traits_t::str_compare_no_case(L"B", L"a"));
}

static void TEST_str_n_compare_no_case_ASCII()
{
    char const a1[] = { 'A', '\0', 'x' };
    char const a2[] = { 'a', '\0', 'y' };
    wchar_t const w1[] = { L'A', L'\0', L'x' };
    wchar_t const w2[] = { L'a', L'\0', L'y' };

    TEST_INT_EQ(0, a_traits_t::str_n_compare_no_case("abc", "XYZ", 0));
    TEST_INT_EQ(0, a_traits_t::str_n_compare_no_case("AbC", "aBc", 3));
    TEST_INT_EQ(0, a_traits_t::str_n_compare_no_case("abX", "ABY", 2));
    TEST_INT_LT(0, a_traits_t::str_n_compare_no_case("abC", "aBd", 3));
    TEST_INT_EQ(0, a_traits_t::str_n_compare_no_case(a1, a2, 3));

    TEST_INT_EQ(0, w_traits_t::str_n_compare_no_case(L"abc", L"XYZ", 0));
    TEST_INT_EQ(0, w_traits_t::str_n_compare_no_case(L"AbC", L"aBc", 3));
    TEST_INT_EQ(0, w_traits_t::str_n_compare_no_case(L"abX", L"ABY", 2));
    TEST_INT_LT(0, w_traits_t::str_n_compare_no_case(L"abC", L"aBd", 3));
    TEST_INT_EQ(0, w_traits_t::str_n_compare_no_case(w1, w2, 3));
}

} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

