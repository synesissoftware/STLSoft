/* /////////////////////////////////////////////////////////////////////////
 * File:    BSTR_functions/entry.cpp
 *
 * Purpose: Unit-tests for comstl BSTR comparison.
 *
 * Created: 29th September 2026
 * Updated: 29th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <comstl/string/bstr.hpp>


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

    static void TEST_comstl_C_BSTR_compare_EMPTY();
    static void TEST_comstl_C_BSTR_compare_EMBEDDED_NUL();
    static void TEST_comstl_C_BSTR_compare_PREFIX_LENGTH();
    static void TEST_BSTR_compare_MATCHES_comstl_C_BSTR_compare();
    static void TEST_bstr_equal();
    static void TEST_comstl__bstr_compare_MATCHES_comstl_C_BSTR_compare();

} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.string.BSTR_functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_comstl_C_BSTR_compare_EMPTY);
        XTESTS_RUN_CASE(TEST_comstl_C_BSTR_compare_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_comstl_C_BSTR_compare_PREFIX_LENGTH);
        XTESTS_RUN_CASE(TEST_BSTR_compare_MATCHES_comstl_C_BSTR_compare);
        XTESTS_RUN_CASE(TEST_bstr_equal);
        XTESTS_RUN_CASE(TEST_comstl__bstr_compare_MATCHES_comstl_C_BSTR_compare);

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

static void expect_match_(BSTR s1, BSTR s2, int sign)
{
    int const cpp = comstl::BSTR_compare(s1, s2);
    int const c = comstl::comstl_C_BSTR_compare(s1, s2);

    TEST_INT_EQ(c, cpp);

    if (sign < 0)
    {
        TEST_INT_LT(0, cpp);
    }
    else if (sign > 0)
    {
        TEST_INT_GT(0, cpp);
    }
    else
    {
        TEST_INT_EQ(0, cpp);
    }
}

static void TEST_comstl_C_BSTR_compare_EMPTY()
{
    BSTR const empty = comstl::comstl_C_BSTR_create_w(L"");
    BSTR const a = comstl::comstl_C_BSTR_create_w(L"a");

    TEST_PTR_NE(NULL, empty);
    TEST_INT_EQ(0u, SysStringLen(empty));

    TEST_INT_EQ(0, comstl::BSTR_compare(empty, empty));
    TEST_INT_EQ(-1, comstl::BSTR_compare(NULL, empty));
    TEST_INT_EQ(1, comstl::BSTR_compare(empty, NULL));
    TEST_INT_LT(0, comstl::BSTR_compare(empty, a));
    TEST_INT_GT(0, comstl::BSTR_compare(a, empty));

    comstl::comstl_C_BSTR_destroy(empty);
    comstl::comstl_C_BSTR_destroy(a);
}

static void TEST_comstl_C_BSTR_compare_EMBEDDED_NUL()
{
    wchar_t const ax[] = { L'a', L'\0', L'x' };
    wchar_t const ay[] = { L'a', L'\0', L'y' };
    wchar_t const bx[] = { L'b', L'\0', L'x' };
    BSTR const s_ax = comstl::comstl_C_BSTR_create_len_w(ax, 3);
    BSTR const s_ay = comstl::comstl_C_BSTR_create_len_w(ay, 3);
    BSTR const s_bx = comstl::comstl_C_BSTR_create_len_w(bx, 3);

    TEST_INT_EQ(3u, SysStringLen(s_ax));
    TEST_INT_EQ(0, comstl::BSTR_compare(s_ax, s_ay));
    TEST_INT_GT(0, comstl::BSTR_compare(s_bx, s_ax));

    comstl::comstl_C_BSTR_destroy(s_ax);
    comstl::comstl_C_BSTR_destroy(s_ay);
    comstl::comstl_C_BSTR_destroy(s_bx);
}

static void TEST_comstl_C_BSTR_compare_PREFIX_LENGTH()
{
    wchar_t const abc[] = L"abc";
    BSTR const ab = comstl::comstl_C_BSTR_create_len_w(abc, 2);
    BSTR const ab_full = comstl::comstl_C_BSTR_create_w(L"ab");
    BSTR const abc_full = comstl::comstl_C_BSTR_create_w(L"abc");

    TEST_INT_EQ(2u, SysStringLen(ab));
    TEST_INT_EQ(0, comstl::BSTR_compare(ab, ab_full));
    TEST_INT_LT(0, comstl::BSTR_compare(ab, abc_full));
    TEST_INT_GT(0, comstl::BSTR_compare(abc_full, ab));

    comstl::comstl_C_BSTR_destroy(ab);
    comstl::comstl_C_BSTR_destroy(ab_full);
    comstl::comstl_C_BSTR_destroy(abc_full);
}

static void TEST_BSTR_compare_MATCHES_comstl_C_BSTR_compare()
{
    wchar_t const ax[] = { L'a', L'\0', L'x' };
    wchar_t const ay[] = { L'a', L'\0', L'y' };
    BSTR const empty = comstl::comstl_C_BSTR_create_w(L"");
    BSTR const abc = comstl::comstl_C_BSTR_create_w(L"abc");
    BSTR const def = comstl::comstl_C_BSTR_create_w(L"def");
    BSTR const ab = comstl::comstl_C_BSTR_create_len_w(L"abc", 2);
    BSTR const s_ax = comstl::comstl_C_BSTR_create_len_w(ax, 3);
    BSTR const s_ay = comstl::comstl_C_BSTR_create_len_w(ay, 3);

    expect_match_(NULL, NULL, 0);
    expect_match_(NULL, abc, -1);
    expect_match_(abc, NULL, +1);
    expect_match_(abc, abc, 0);
    expect_match_(abc, def, -1);
    expect_match_(def, abc, +1);
    expect_match_(empty, empty, 0);
    expect_match_(empty, abc, -1);
    expect_match_(ab, abc, -1);
    expect_match_(s_ax, s_ay, 0);

    comstl::comstl_C_BSTR_destroy(empty);
    comstl::comstl_C_BSTR_destroy(abc);
    comstl::comstl_C_BSTR_destroy(def);
    comstl::comstl_C_BSTR_destroy(ab);
    comstl::comstl_C_BSTR_destroy(s_ax);
    comstl::comstl_C_BSTR_destroy(s_ay);
}

static void TEST_bstr_equal()
{
    comstl::bstr const abc(L"abc");
    comstl::bstr const abc2(L"abc");
    comstl::bstr const abd(L"abd");
    comstl::bstr const empty;
    BSTR const raw = comstl::comstl_C_BSTR_create_w(L"abc");

    TEST_BOOLEAN_TRUE(abc.equal(abc));
    TEST_BOOLEAN_TRUE(abc.equal(abc2));
    TEST_BOOLEAN_FALSE(abc.equal(abd));
    TEST_BOOLEAN_TRUE(empty.equal(empty));
    TEST_BOOLEAN_FALSE(empty.equal(abc));
    TEST_BOOLEAN_TRUE(abc.equal(raw));
    TEST_BOOLEAN_FALSE(abc.equal(static_cast<BSTR>(NULL)));

    comstl::comstl_C_BSTR_destroy(raw);
}

static void TEST_comstl__bstr_compare_MATCHES_comstl_C_BSTR_compare()
{
    BSTR const abc = comstl::comstl_C_BSTR_create_w(L"abc");
    BSTR const def = comstl::comstl_C_BSTR_create_w(L"def");

    /* One call of the deprecated name, with the warning suppressed. */
#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif
#if defined(__clang__) || defined(__GNUC__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

    int const compared = comstl::comstl__bstr_compare(abc, def);

#if defined(__clang__) || defined(__GNUC__)
# pragma GCC diagnostic pop
#endif
#if defined(_MSC_VER)
# pragma warning(pop)
#endif

    TEST_INT_EQ(comstl::comstl_C_BSTR_compare(abc, def), compared);
    TEST_INT_LT(0, compared);

    comstl::comstl_C_BSTR_destroy(abc);
    comstl::comstl_C_BSTR_destroy(def);
}

} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

