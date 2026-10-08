/* /////////////////////////////////////////////////////////////////////////
 * File:    char_traits/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::char_traits and char_traits_safe.
 *
 * Created: 29th September 2026
 * Updated: 29th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/char_traits.hpp>


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

    static void TEST_eq_AND_lt();
    static void TEST_compare_EQUAL();
    static void TEST_compare_LESS();
    static void TEST_compare_GREATER();
    static void TEST_compare_n_0();
    static void TEST_compare_EXACT_n_SEES_BYTE_AFTER_NUL();
    static void TEST_compare_max_STOPS_AT_NUL();
    static void TEST_compare_null_BOTH_NULL();
    static void TEST_compare_null_ONE_NULL();
    static void TEST_compare_HIGH_BIT_UNSIGNED_ORDER();
    static void TEST_char_traits_safe_compare();
    static void TEST_char_traits_safe_compare_NULL();

} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.char_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_eq_AND_lt);
        XTESTS_RUN_CASE(TEST_compare_EQUAL);
        XTESTS_RUN_CASE(TEST_compare_LESS);
        XTESTS_RUN_CASE(TEST_compare_GREATER);
        XTESTS_RUN_CASE(TEST_compare_n_0);
        XTESTS_RUN_CASE(TEST_compare_EXACT_n_SEES_BYTE_AFTER_NUL);
        XTESTS_RUN_CASE(TEST_compare_max_STOPS_AT_NUL);
        XTESTS_RUN_CASE(TEST_compare_null_BOTH_NULL);
        XTESTS_RUN_CASE(TEST_compare_null_ONE_NULL);
        XTESTS_RUN_CASE(TEST_compare_HIGH_BIT_UNSIGNED_ORDER);
        XTESTS_RUN_CASE(TEST_char_traits_safe_compare);
        XTESTS_RUN_CASE(TEST_char_traits_safe_compare_NULL);

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

typedef stlsoft::char_traits<char>                          a_traits_t;
typedef stlsoft::char_traits<wchar_t>                       w_traits_t;
typedef stlsoft::char_traits_safe<char>                     a_safe_t;
typedef stlsoft::char_traits_safe<wchar_t>                  w_safe_t;

static void TEST_eq_AND_lt()
{
    TEST_BOOLEAN_TRUE(a_traits_t::eq('a', 'a'));
    TEST_BOOLEAN_FALSE(a_traits_t::eq('a', 'b'));
    TEST_BOOLEAN_TRUE(a_traits_t::lt('a', 'b'));
    TEST_BOOLEAN_FALSE(a_traits_t::lt('b', 'a'));
    TEST_BOOLEAN_FALSE(a_traits_t::lt('a', 'a'));

    TEST_BOOLEAN_TRUE(w_traits_t::eq(L'a', L'a'));
    TEST_BOOLEAN_FALSE(w_traits_t::eq(L'a', L'b'));
    TEST_BOOLEAN_TRUE(w_traits_t::lt(L'a', L'b'));
    TEST_BOOLEAN_FALSE(w_traits_t::lt(L'b', L'a'));
    TEST_BOOLEAN_FALSE(w_traits_t::lt(L'a', L'a'));
}

static void TEST_compare_EQUAL()
{
    TEST_INT_EQ(0, a_traits_t::compare("abc", "abc", 3));
    TEST_INT_EQ(0, a_traits_t::compare("abcd", "abce", 3));
    TEST_INT_EQ(0, a_traits_t::compare("", "", 1));

    TEST_INT_EQ(0, w_traits_t::compare(L"abc", L"abc", 3));
    TEST_INT_EQ(0, w_traits_t::compare(L"abcd", L"abce", 3));
    TEST_INT_EQ(0, w_traits_t::compare(L"", L"", 1));
}

static void TEST_compare_LESS()
{
    TEST_INT_LT(0, a_traits_t::compare("abc", "abd", 3));
    TEST_INT_LT(0, a_traits_t::compare("ab", "abc", 3));

    TEST_INT_LT(0, w_traits_t::compare(L"abc", L"abd", 3));
    TEST_INT_LT(0, w_traits_t::compare(L"ab", L"abc", 3));
}

static void TEST_compare_GREATER()
{
    TEST_INT_GT(0, a_traits_t::compare("abd", "abc", 3));
    TEST_INT_GT(0, a_traits_t::compare("abc", "ab", 3));

    TEST_INT_GT(0, w_traits_t::compare(L"abd", L"abc", 3));
    TEST_INT_GT(0, w_traits_t::compare(L"abc", L"ab", 3));
}

static void TEST_compare_n_0()
{
    TEST_INT_EQ(0, a_traits_t::compare("abc", "xyz", 0));
    TEST_INT_EQ(0, a_traits_t::compare(NULL, NULL, 0));
    TEST_INT_EQ(0, a_traits_t::compare_max("abc", "xyz", 0));

    TEST_INT_EQ(0, w_traits_t::compare(L"abc", L"xyz", 0));
    TEST_INT_EQ(0, w_traits_t::compare(NULL, NULL, 0));
    TEST_INT_EQ(0, w_traits_t::compare_max(L"abc", L"xyz", 0));
}

static void TEST_compare_EXACT_n_SEES_BYTE_AFTER_NUL()
{
    char const a1[] = { 'a', '\0', 'd' };
    char const a2[] = { 'a', '\0', 'e' };
    wchar_t const w1[] = { L'a', L'\0', L'd' };
    wchar_t const w2[] = { L'a', L'\0', L'e' };

    TEST_INT_LT(0, a_traits_t::compare(a1, a2, 3));
    TEST_INT_LT(0, w_traits_t::compare(w1, w2, 3));
}

static void TEST_compare_max_STOPS_AT_NUL()
{
    char const a1[] = { 'a', '\0', 'd' };
    char const a2[] = { 'a', '\0', 'e' };
    wchar_t const w1[] = { L'a', L'\0', L'd' };
    wchar_t const w2[] = { L'a', L'\0', L'e' };

    TEST_INT_EQ(0, a_traits_t::compare_max(a1, a2, 3));
    TEST_INT_EQ(0, a_traits_t::compare_max("abc", "abc", 3));
    TEST_INT_LT(0, a_traits_t::compare_max("abc", "abd", 3));

    TEST_INT_EQ(0, w_traits_t::compare_max(w1, w2, 3));
    TEST_INT_EQ(0, w_traits_t::compare_max(L"abc", L"abc", 3));
    TEST_INT_LT(0, w_traits_t::compare_max(L"abc", L"abd", 3));
}

static void TEST_compare_null_BOTH_NULL()
{
    TEST_INT_EQ(0, a_traits_t::compare_null(NULL, NULL, 0));
    TEST_INT_EQ(0, a_traits_t::compare_null(NULL, NULL, 4));
    TEST_INT_EQ(0, w_traits_t::compare_null(NULL, NULL, 0));
    TEST_INT_EQ(0, w_traits_t::compare_null(NULL, NULL, 4));
}

static void TEST_compare_null_ONE_NULL()
{
    TEST_INT_EQ(-1, a_traits_t::compare_null(NULL, "a", 0));
    TEST_INT_EQ(-1, a_traits_t::compare_null(NULL, "a", 1));
    TEST_INT_EQ(1, a_traits_t::compare_null("a", NULL, 0));
    TEST_INT_EQ(1, a_traits_t::compare_null("a", NULL, 1));
    TEST_INT_LT(0, a_traits_t::compare_null("abc", "abd", 3));

    TEST_INT_EQ(-1, w_traits_t::compare_null(NULL, L"a", 0));
    TEST_INT_EQ(-1, w_traits_t::compare_null(NULL, L"a", 1));
    TEST_INT_EQ(1, w_traits_t::compare_null(L"a", NULL, 0));
    TEST_INT_EQ(1, w_traits_t::compare_null(L"a", NULL, 1));
    TEST_INT_LT(0, w_traits_t::compare_null(L"abc", L"abd", 3));
}

static void TEST_compare_HIGH_BIT_UNSIGNED_ORDER()
{
    unsigned char const below_u[] = { 0x01 };
    unsigned char const above_u[] = { 0xFF };
    char const* const   s_below = reinterpret_cast<char const*>(below_u);
    char const* const   s_above = reinterpret_cast<char const*>(above_u);
    char const          below = s_below[0];
    char const          above = s_above[0];

    TEST_BOOLEAN_TRUE(a_traits_t::eq(above, above));
    TEST_BOOLEAN_FALSE(a_traits_t::eq(below, above));

    if (below < above)
    {
        TEST_BOOLEAN_TRUE(a_traits_t::lt(below, above));
    }
    else
    {
        TEST_BOOLEAN_FALSE(a_traits_t::lt(below, above));
        TEST_BOOLEAN_TRUE(a_traits_t::lt(above, below));
    }

    TEST_INT_LT(0, a_traits_t::compare(s_below, s_above, 1));
    TEST_INT_GT(0, a_traits_t::compare(s_above, s_below, 1));

    wchar_t const w_small[] = { 0x0001 };
    wchar_t const w_large[] = { 0x00FF };

    TEST_BOOLEAN_TRUE(w_traits_t::lt(w_small[0], w_large[0]));
    TEST_INT_LT(0, w_traits_t::compare(w_small, w_large, 1));
    TEST_INT_GT(0, w_traits_t::compare(w_large, w_small, 1));
}

static void TEST_char_traits_safe_compare()
{
    char const a1[] = { 'a', '\0', 'd' };
    char const a2[] = { 'a', '\0', 'e' };
    wchar_t const w1[] = { L'a', L'\0', L'd' };
    wchar_t const w2[] = { L'a', L'\0', L'e' };

    TEST_INT_EQ(0, a_safe_t::compare("abc", "abc", 3));
    TEST_INT_LT(0, a_safe_t::compare("abc", "abd", 3));
    TEST_INT_LT(0, a_safe_t::compare(a1, a2, 3));
    TEST_INT_EQ(0, a_safe_t::compare_max(a1, a2, 3));

    TEST_INT_EQ(0, w_safe_t::compare(L"abc", L"abc", 3));
    TEST_INT_LT(0, w_safe_t::compare(L"abc", L"abd", 3));
    TEST_INT_LT(0, w_safe_t::compare(w1, w2, 3));
    TEST_INT_EQ(0, w_safe_t::compare_max(w1, w2, 3));
}

static void TEST_char_traits_safe_compare_NULL()
{
    /* A count of 0 compares no characters, so a null pointer and a live
     * pointer are equal. A non-zero count orders a null pointer before a
     * live pointer, and two null pointers compare equal.
     */
    TEST_INT_EQ(0, a_safe_t::compare(NULL, NULL, 0));
    TEST_INT_EQ(0, a_safe_t::compare(NULL, NULL, 4));
    TEST_INT_EQ(0, a_safe_t::compare(NULL, "a", 0));
    TEST_INT_EQ(-1, a_safe_t::compare(NULL, "a", 1));
    TEST_INT_EQ(0, a_safe_t::compare("a", NULL, 0));
    TEST_INT_EQ(1, a_safe_t::compare("a", NULL, 1));

    TEST_INT_EQ(0, w_safe_t::compare(NULL, NULL, 0));
    TEST_INT_EQ(0, w_safe_t::compare(NULL, NULL, 4));
    TEST_INT_EQ(0, w_safe_t::compare(NULL, L"a", 0));
    TEST_INT_EQ(-1, w_safe_t::compare(NULL, L"a", 1));
    TEST_INT_EQ(0, w_safe_t::compare(L"a", NULL, 0));
    TEST_INT_EQ(1, w_safe_t::compare(L"a", NULL, 1));

    TEST_INT_EQ(0, a_safe_t::compare_max(NULL, NULL, 4));
    TEST_INT_EQ(-1, a_safe_t::compare_max(NULL, "a", 1));
    TEST_INT_EQ(1, a_safe_t::compare_max("a", NULL, 1));

    TEST_INT_EQ(0, w_safe_t::compare_max(NULL, NULL, 4));
    TEST_INT_EQ(-1, w_safe_t::compare_max(NULL, L"a", 1));
    TEST_INT_EQ(1, w_safe_t::compare_max(L"a", NULL, 1));
}

} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

