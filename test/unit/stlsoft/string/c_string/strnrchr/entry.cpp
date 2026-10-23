/* /////////////////////////////////////////////////////////////////////////
 * File:    c_string.strnrchr/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::c_string::strnrchr() and wcsnrchr().
 *
 * Created: 23rd October 2026
 * Updated: 23rd October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/c_string/strnrchr.h>


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

    static void TEST_c_string_strnrchr_n_0();
    static void TEST_c_string_strnrchr_MATCH_AT_END();
    static void TEST_c_string_strnrchr_MATCH_IN_MIDDLE();
    static void TEST_c_string_strnrchr_MATCH_AT_START();
    static void TEST_c_string_strnrchr_LAST_OF_SEVERAL();
    static void TEST_c_string_strnrchr_MISS();
    static void TEST_c_string_strnrchr_DOES_NOT_READ_PAST_n();
    static void TEST_c_string_strnrchr_FINDS_EMBEDDED_NUL();
    static void TEST_c_string_strnrchr_CONTINUES_PAST_NUL();
    static void TEST_c_string_strnrchr_HIGH_BIT();
    static void TEST_c_string_wcsnrchr_n_0();
    static void TEST_c_string_wcsnrchr_MATCH_AT_END();
    static void TEST_c_string_wcsnrchr_MATCH_IN_MIDDLE();
    static void TEST_c_string_wcsnrchr_MATCH_AT_START();
    static void TEST_c_string_wcsnrchr_LAST_OF_SEVERAL();
    static void TEST_c_string_wcsnrchr_MISS();
    static void TEST_c_string_wcsnrchr_DOES_NOT_READ_PAST_n();
    static void TEST_c_string_wcsnrchr_FINDS_EMBEDDED_NUL();
    static void TEST_c_string_wcsnrchr_CONTINUES_PAST_NUL();
    static void TEST_c_string_wcsnrchr_HIGH_BIT();

    static wchar_t const* wcsnrchr_both_(wchar_t const* s, size_t n, int ch);

} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string.strnrchr", verbosity))
    {
        XTESTS_RUN_CASE(TEST_c_string_strnrchr_n_0);
        XTESTS_RUN_CASE(TEST_c_string_strnrchr_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_c_string_strnrchr_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_c_string_strnrchr_MATCH_AT_START);
        XTESTS_RUN_CASE(TEST_c_string_strnrchr_LAST_OF_SEVERAL);
        XTESTS_RUN_CASE(TEST_c_string_strnrchr_MISS);
        XTESTS_RUN_CASE(TEST_c_string_strnrchr_DOES_NOT_READ_PAST_n);
        XTESTS_RUN_CASE(TEST_c_string_strnrchr_FINDS_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_c_string_strnrchr_CONTINUES_PAST_NUL);
        XTESTS_RUN_CASE(TEST_c_string_strnrchr_HIGH_BIT);
        XTESTS_RUN_CASE(TEST_c_string_wcsnrchr_n_0);
        XTESTS_RUN_CASE(TEST_c_string_wcsnrchr_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_c_string_wcsnrchr_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_c_string_wcsnrchr_MATCH_AT_START);
        XTESTS_RUN_CASE(TEST_c_string_wcsnrchr_LAST_OF_SEVERAL);
        XTESTS_RUN_CASE(TEST_c_string_wcsnrchr_MISS);
        XTESTS_RUN_CASE(TEST_c_string_wcsnrchr_DOES_NOT_READ_PAST_n);
        XTESTS_RUN_CASE(TEST_c_string_wcsnrchr_FINDS_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_c_string_wcsnrchr_CONTINUES_PAST_NUL);
        XTESTS_RUN_CASE(TEST_c_string_wcsnrchr_HIGH_BIT);

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

static wchar_t const* wcsnrchr_both_(wchar_t const* s, size_t n, int ch)
{
    wchar_t const* const via_str = stlsoft::c_string::strnrchr(s, n, ch);
    wchar_t const* const via_wcs = stlsoft::c_string::wcsnrchr(s, n, ch);

    TEST_PTR_EQ(via_wcs, via_str);

    return via_wcs;
}

static void TEST_c_string_strnrchr_n_0()
{
    TEST_PTR_NULL(stlsoft::c_string::strnrchr("abc", 0, 'a'));
    TEST_PTR_NULL(stlsoft::c_string::strnrchr("", 0, '\0'));
}

static void TEST_c_string_strnrchr_MATCH_AT_END()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnrchr(s, 3, 'c'));
    TEST_PTR_EQ(s, stlsoft::c_string::strnrchr(s, 1, 'a'));
}

static void TEST_c_string_strnrchr_MATCH_IN_MIDDLE()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 1, stlsoft::c_string::strnrchr(s, 3, 'b'));
}

static void TEST_c_string_strnrchr_MATCH_AT_START()
{
    char const s[] = "abc";

    TEST_PTR_EQ(s, stlsoft::c_string::strnrchr(s, 3, 'a'));
}

static void TEST_c_string_strnrchr_LAST_OF_SEVERAL()
{
    char const s[] = "abaca";

    TEST_PTR_EQ(s + 4, stlsoft::c_string::strnrchr(s, 5, 'a'));
    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnrchr(s, 4, 'a'));
}

static void TEST_c_string_strnrchr_MISS()
{
    TEST_PTR_NULL(stlsoft::c_string::strnrchr("abc", 3, 'z'));
    TEST_PTR_NULL(stlsoft::c_string::strnrchr("abc", 3, 'A'));
}

static void TEST_c_string_strnrchr_DOES_NOT_READ_PAST_n()
{
    char const s[] = "abc";

    TEST_PTR_NULL(stlsoft::c_string::strnrchr(s, 2, 'c'));
    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnrchr(s, 3, 'c'));
}

static void TEST_c_string_strnrchr_FINDS_EMBEDDED_NUL()
{
    char const s[] = { 'a', '\0', 'b' };

    TEST_PTR_EQ(s + 1, stlsoft::c_string::strnrchr(s, 3, '\0'));
}

static void TEST_c_string_strnrchr_CONTINUES_PAST_NUL()
{
    char const s[] = { 'a', '\0', 'b' };

    TEST_PTR_EQ(s, stlsoft::c_string::strnrchr(s, 3, 'a'));
    TEST_PTR_EQ(s + 2, stlsoft::c_string::strnrchr(s, 3, 'b'));
    TEST_PTR_NULL(stlsoft::c_string::strnrchr(s, 1, 'b'));
}

static void TEST_c_string_strnrchr_HIGH_BIT()
{
    unsigned char const s_u[] = { 'a', 0xE9, 'b' };
    char const* const   s = reinterpret_cast<char const*>(s_u);

    TEST_PTR_EQ(s + 1, stlsoft::c_string::strnrchr(s, 3, s[1]));
    TEST_PTR_EQ(s, stlsoft::c_string::strnrchr(s, 1, 'a'));
    TEST_PTR_NULL(stlsoft::c_string::strnrchr(s, 3, 'x'));
}

static void TEST_c_string_wcsnrchr_n_0()
{
    TEST_PTR_NULL(wcsnrchr_both_(L"abc", 0, L'a'));
    TEST_PTR_NULL(wcsnrchr_both_(L"", 0, L'\0'));
}

static void TEST_c_string_wcsnrchr_MATCH_AT_END()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 2, wcsnrchr_both_(s, 3, L'c'));
    TEST_PTR_EQ(s, wcsnrchr_both_(s, 1, L'a'));
}

static void TEST_c_string_wcsnrchr_MATCH_IN_MIDDLE()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 1, wcsnrchr_both_(s, 3, L'b'));
}

static void TEST_c_string_wcsnrchr_MATCH_AT_START()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s, wcsnrchr_both_(s, 3, L'a'));
}

static void TEST_c_string_wcsnrchr_LAST_OF_SEVERAL()
{
    wchar_t const s[] = L"abaca";

    TEST_PTR_EQ(s + 4, wcsnrchr_both_(s, 5, L'a'));
    TEST_PTR_EQ(s + 2, wcsnrchr_both_(s, 4, L'a'));
}

static void TEST_c_string_wcsnrchr_MISS()
{
    TEST_PTR_NULL(wcsnrchr_both_(L"abc", 3, L'z'));
    TEST_PTR_NULL(wcsnrchr_both_(L"abc", 3, L'A'));
}

static void TEST_c_string_wcsnrchr_DOES_NOT_READ_PAST_n()
{
    wchar_t const s[] = L"abc";

    TEST_PTR_NULL(wcsnrchr_both_(s, 2, L'c'));
    TEST_PTR_EQ(s + 2, wcsnrchr_both_(s, 3, L'c'));
}

static void TEST_c_string_wcsnrchr_FINDS_EMBEDDED_NUL()
{
    wchar_t const s[] = { L'a', L'\0', L'b' };

    TEST_PTR_EQ(s + 1, wcsnrchr_both_(s, 3, L'\0'));
}

static void TEST_c_string_wcsnrchr_CONTINUES_PAST_NUL()
{
    wchar_t const s[] = { L'a', L'\0', L'b' };

    TEST_PTR_EQ(s, wcsnrchr_both_(s, 3, L'a'));
    TEST_PTR_EQ(s + 2, wcsnrchr_both_(s, 3, L'b'));
    TEST_PTR_NULL(wcsnrchr_both_(s, 1, L'b'));
}

static void TEST_c_string_wcsnrchr_HIGH_BIT()
{
    wchar_t const s[] = { L'a', L'\x00E9', L'b' };

    TEST_PTR_EQ(s + 1, wcsnrchr_both_(s, 3, s[1]));
    TEST_PTR_EQ(s, wcsnrchr_both_(s, 1, L'a'));
    TEST_PTR_NULL(wcsnrchr_both_(s, 3, L'x'));
}

} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */
