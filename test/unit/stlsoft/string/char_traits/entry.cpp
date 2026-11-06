/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/char_traits/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::char_traits and char_traits_safe.
 *
 * Created: 29th September 2026
 * Updated: 2nd November 2026
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
    static void TEST_assign_n_CHAR();
    static void TEST_assign_n_WCHAR();
    static void TEST_assign_n_0_NEITHER_WRITES_NOR_DEREFERENCES();
    static void TEST_assign_HIGH_VALUES();
    static void TEST_copy_n_CHAR();
    static void TEST_copy_n_WCHAR();
    static void TEST_copy_n_0_NEITHER_WRITES_NOR_DEREFERENCES();
    static void TEST_find_n_0_NEITHER_READS();
    static void TEST_find_MATCH_AND_MISS();
} // anonymous namespace


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
        XTESTS_RUN_CASE(TEST_assign_n_CHAR);
        XTESTS_RUN_CASE(TEST_assign_n_WCHAR);
        XTESTS_RUN_CASE(TEST_assign_n_0_NEITHER_WRITES_NOR_DEREFERENCES);
        XTESTS_RUN_CASE(TEST_assign_HIGH_VALUES);
        XTESTS_RUN_CASE(TEST_copy_n_CHAR);
        XTESTS_RUN_CASE(TEST_copy_n_WCHAR);
        XTESTS_RUN_CASE(TEST_copy_n_0_NEITHER_WRITES_NOR_DEREFERENCES);
        XTESTS_RUN_CASE(TEST_find_n_0_NEITHER_READS);
        XTESTS_RUN_CASE(TEST_find_MATCH_AND_MISS);

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
    TEST_INT_EQ(0, a_traits_t::compare(NULL, "a", 0));
    TEST_INT_EQ(0, a_traits_t::compare("a", NULL, 0));
    TEST_INT_EQ(0, a_traits_t::compare_max("abc", "xyz", 0));

    TEST_INT_EQ(0, w_traits_t::compare(L"abc", L"xyz", 0));
    TEST_INT_EQ(0, w_traits_t::compare(NULL, NULL, 0));
    TEST_INT_EQ(0, w_traits_t::compare(NULL, L"a", 0));
    TEST_INT_EQ(0, w_traits_t::compare(L"a", NULL, 0));
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

static void TEST_assign_n_CHAR()
{
    char buff[6] = { 'X', 'X', 'X', 'X', 'X', 'X' };
    char* const r = a_traits_t::assign(&buff[1], 4, 'a');

    TEST_BOOLEAN_TRUE(&buff[1] == r);
    TEST_CHAR_EQ('X', buff[0]);
    TEST_CHAR_EQ('a', buff[1]);
    TEST_CHAR_EQ('a', buff[2]);
    TEST_CHAR_EQ('a', buff[3]);
    TEST_CHAR_EQ('a', buff[4]);
    TEST_CHAR_EQ('X', buff[5]);
}

static void TEST_assign_n_WCHAR()
{
    wchar_t buff[6] = { L'X', L'X', L'X', L'X', L'X', L'X' };
    wchar_t* const r = w_traits_t::assign(&buff[1], 4, L'a');

    TEST_BOOLEAN_TRUE(&buff[1] == r);
    TEST_CHAR_EQ(L'X', buff[0]);
    TEST_CHAR_EQ(L'a', buff[1]);
    TEST_CHAR_EQ(L'a', buff[2]);
    TEST_CHAR_EQ(L'a', buff[3]);
    TEST_CHAR_EQ(L'a', buff[4]);
    TEST_CHAR_EQ(L'X', buff[5]);
}

static void TEST_assign_n_0_NEITHER_WRITES_NOR_DEREFERENCES()
{
    {
        char buff[2] = { 'X', 'X' };

        TEST_BOOLEAN_TRUE(&buff[0] == a_traits_t::assign(&buff[0], 0, 'a'));
        TEST_CHAR_EQ('X', buff[0]);
        TEST_CHAR_EQ('X', buff[1]);

        TEST_BOOLEAN_TRUE(NULL == a_traits_t::assign(NULL, 0, 'a'));
    }

    {
        wchar_t buff[2] = { L'X', L'X' };

        TEST_BOOLEAN_TRUE(&buff[0] == w_traits_t::assign(&buff[0], 0, L'a'));
        TEST_CHAR_EQ(L'X', buff[0]);
        TEST_CHAR_EQ(L'X', buff[1]);

        TEST_BOOLEAN_TRUE(NULL == w_traits_t::assign(NULL, 0, L'a'));
    }
}

static void TEST_assign_HIGH_VALUES()
{
    /* a byte fill must not sign-extend, and a wide fill must not be
     * truncated to a byte
     */
    char buff[3] = { 'X', 'X', 'X' };
    wchar_t wbuff[3] = { L'X', L'X', L'X' };

    a_traits_t::assign(&buff[1], 1, '\xff');

    TEST_CHAR_EQ('X', buff[0]);
    TEST_CHAR_EQ('\xff', buff[1]);
    TEST_CHAR_EQ('X', buff[2]);

    w_traits_t::assign(&wbuff[1], 1, L'\x0152');

    TEST_CHAR_EQ(L'X', wbuff[0]);
    TEST_CHAR_EQ(L'\x0152', wbuff[1]);
    TEST_CHAR_EQ(L'X', wbuff[2]);
}

static void TEST_copy_n_CHAR()
{
    char const  src[] = { 'a', 'b', 'c', 'd' };
    char        buff[6] = { 'X', 'X', 'X', 'X', 'X', 'X' };
    char* const r = a_traits_t::copy(&buff[1], src, 4);

    TEST_BOOLEAN_TRUE(&buff[1] == r);
    TEST_CHAR_EQ('X', buff[0]);
    TEST_CHAR_EQ('a', buff[1]);
    TEST_CHAR_EQ('b', buff[2]);
    TEST_CHAR_EQ('c', buff[3]);
    TEST_CHAR_EQ('d', buff[4]);
    TEST_CHAR_EQ('X', buff[5]);
}

static void TEST_copy_n_WCHAR()
{
    wchar_t const   src[] = { L'a', L'b', L'c', L'd' };
    wchar_t         buff[6] = { L'X', L'X', L'X', L'X', L'X', L'X' };
    wchar_t* const  r = w_traits_t::copy(&buff[1], src, 4);

    TEST_BOOLEAN_TRUE(&buff[1] == r);
    TEST_CHAR_EQ(L'X', buff[0]);
    TEST_CHAR_EQ(L'a', buff[1]);
    TEST_CHAR_EQ(L'b', buff[2]);
    TEST_CHAR_EQ(L'c', buff[3]);
    TEST_CHAR_EQ(L'd', buff[4]);
    TEST_CHAR_EQ(L'X', buff[5]);
}

static void TEST_copy_n_0_NEITHER_WRITES_NOR_DEREFERENCES()
{
    {
        char const  src[] = { 'a' };
        char        buff[2] = { 'X', 'X' };

        TEST_BOOLEAN_TRUE(&buff[0] == a_traits_t::copy(&buff[0], src, 0));
        TEST_CHAR_EQ('X', buff[0]);
        TEST_CHAR_EQ('X', buff[1]);

        TEST_BOOLEAN_TRUE(&buff[0] == a_traits_t::copy(&buff[0], NULL, 0));
        TEST_BOOLEAN_TRUE(NULL == a_traits_t::copy(NULL, NULL, 0));
    }

    {
        wchar_t const   src[] = { L'a' };
        wchar_t         buff[2] = { L'X', L'X' };

        TEST_BOOLEAN_TRUE(&buff[0] == w_traits_t::copy(&buff[0], src, 0));
        TEST_CHAR_EQ(L'X', buff[0]);
        TEST_CHAR_EQ(L'X', buff[1]);

        TEST_BOOLEAN_TRUE(&buff[0] == w_traits_t::copy(&buff[0], NULL, 0));
        TEST_BOOLEAN_TRUE(NULL == w_traits_t::copy(NULL, NULL, 0));
    }
}

static void TEST_find_n_0_NEITHER_READS()
{
    char const      s[] = "abc";
    wchar_t const   ws[] = L"abc";

    TEST_PTR_NULL(a_traits_t::find(s, 0, 'a'));
    TEST_PTR_NULL(a_traits_t::find(NULL, 0, 'a'));
    TEST_PTR_NULL(w_traits_t::find(ws, 0, L'a'));
    TEST_PTR_NULL(w_traits_t::find(NULL, 0, L'a'));
}

static void TEST_find_MATCH_AND_MISS()
{
    char const          s[] = "abaca";
    wchar_t const       ws[] = L"abaca";
    unsigned char const hi_u[] = { 0xE9, 'b', 'c' };
    char const* const   hi = reinterpret_cast<char const*>(hi_u);
    wchar_t const       whi[] = { L'\x0152', L'b' };

    TEST_PTR_EQ(s, a_traits_t::find(s, 5, 'a'));
    TEST_PTR_EQ(s + 1, a_traits_t::find(s, 5, 'b'));
    TEST_PTR_NULL(a_traits_t::find(s, 5, 'x'));
    TEST_PTR_NULL(a_traits_t::find(s, 2, 'c'));
    TEST_PTR_EQ(hi, a_traits_t::find(hi, 3, hi[0]));

    TEST_PTR_EQ(ws, w_traits_t::find(ws, 5, L'a'));
    TEST_PTR_EQ(ws + 1, w_traits_t::find(ws, 5, L'b'));
    TEST_PTR_NULL(w_traits_t::find(ws, 5, L'x'));
    TEST_PTR_EQ(whi, w_traits_t::find(whi, 2, whi[0]));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

