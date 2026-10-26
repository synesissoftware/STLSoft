/* /////////////////////////////////////////////////////////////////////////
 * File:    c_string.strnrchr.C/entry.c
 *
 * Purpose: Unit-tests for stlsoft_C_strnrchr() and stlsoft_C_wcsnrchr().
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

static void TEST_stlsoft_C_strnrchr_n_0(void);
static void TEST_stlsoft_C_strnrchr_MATCH_AT_END(void);
static void TEST_stlsoft_C_strnrchr_MATCH_IN_MIDDLE(void);
static void TEST_stlsoft_C_strnrchr_MATCH_AT_START(void);
static void TEST_stlsoft_C_strnrchr_LAST_OF_SEVERAL(void);
static void TEST_stlsoft_C_strnrchr_MISS(void);
static void TEST_stlsoft_C_strnrchr_DOES_NOT_READ_PAST_n(void);
static void TEST_stlsoft_C_strnrchr_FINDS_EMBEDDED_NUL(void);
static void TEST_stlsoft_C_strnrchr_CONTINUES_PAST_NUL(void);
static void TEST_stlsoft_C_strnrchr_HIGH_BIT(void);
static void TEST_stlsoft_C_wcsnrchr_n_0(void);
static void TEST_stlsoft_C_wcsnrchr_MATCH_AT_END(void);
static void TEST_stlsoft_C_wcsnrchr_MATCH_IN_MIDDLE(void);
static void TEST_stlsoft_C_wcsnrchr_MATCH_AT_START(void);
static void TEST_stlsoft_C_wcsnrchr_LAST_OF_SEVERAL(void);
static void TEST_stlsoft_C_wcsnrchr_MISS(void);
static void TEST_stlsoft_C_wcsnrchr_DOES_NOT_READ_PAST_n(void);
static void TEST_stlsoft_C_wcsnrchr_FINDS_EMBEDDED_NUL(void);
static void TEST_stlsoft_C_wcsnrchr_CONTINUES_PAST_NUL(void);
static void TEST_stlsoft_C_wcsnrchr_HIGH_BIT(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string.strnrchr.C", verbosity))
    {
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnrchr_n_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnrchr_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnrchr_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnrchr_MATCH_AT_START);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnrchr_LAST_OF_SEVERAL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnrchr_MISS);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnrchr_DOES_NOT_READ_PAST_n);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnrchr_FINDS_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnrchr_CONTINUES_PAST_NUL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnrchr_HIGH_BIT);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnrchr_n_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnrchr_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnrchr_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnrchr_MATCH_AT_START);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnrchr_LAST_OF_SEVERAL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnrchr_MISS);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnrchr_DOES_NOT_READ_PAST_n);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnrchr_FINDS_EMBEDDED_NUL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnrchr_CONTINUES_PAST_NUL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnrchr_HIGH_BIT);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_stlsoft_C_strnrchr_n_0(void)
{
    TEST_PTR_NULL(stlsoft_C_strnrchr("abc", 0, 'a'));
    TEST_PTR_NULL(stlsoft_C_strnrchr("", 0, '\0'));
}

static void TEST_stlsoft_C_strnrchr_MATCH_AT_END(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 2, stlsoft_C_strnrchr(s, 3, 'c'));
    TEST_PTR_EQ(s, stlsoft_C_strnrchr(s, 1, 'a'));
}

static void TEST_stlsoft_C_strnrchr_MATCH_IN_MIDDLE(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 1, stlsoft_C_strnrchr(s, 3, 'b'));
}

static void TEST_stlsoft_C_strnrchr_MATCH_AT_START(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s, stlsoft_C_strnrchr(s, 3, 'a'));
}

static void TEST_stlsoft_C_strnrchr_LAST_OF_SEVERAL(void)
{
    char const s[] = "abaca";

    TEST_PTR_EQ(s + 4, stlsoft_C_strnrchr(s, 5, 'a'));
    TEST_PTR_EQ(s + 2, stlsoft_C_strnrchr(s, 4, 'a'));
}

static void TEST_stlsoft_C_strnrchr_MISS(void)
{
    TEST_PTR_NULL(stlsoft_C_strnrchr("abc", 3, 'z'));
    TEST_PTR_NULL(stlsoft_C_strnrchr("abc", 3, 'A'));
}

static void TEST_stlsoft_C_strnrchr_DOES_NOT_READ_PAST_n(void)
{
    char const s[] = "abc";

    TEST_PTR_NULL(stlsoft_C_strnrchr(s, 2, 'c'));
    TEST_PTR_EQ(s + 2, stlsoft_C_strnrchr(s, 3, 'c'));
}

static void TEST_stlsoft_C_strnrchr_FINDS_EMBEDDED_NUL(void)
{
    char const s[] = { 'a', '\0', 'b' };

    TEST_PTR_EQ(s + 1, stlsoft_C_strnrchr(s, 3, '\0'));
}

static void TEST_stlsoft_C_strnrchr_CONTINUES_PAST_NUL(void)
{
    char const s[] = { 'a', '\0', 'b' };

    TEST_PTR_EQ(s, stlsoft_C_strnrchr(s, 3, 'a'));
    TEST_PTR_EQ(s + 2, stlsoft_C_strnrchr(s, 3, 'b'));
    TEST_PTR_NULL(stlsoft_C_strnrchr(s, 1, 'b'));
}

static void TEST_stlsoft_C_strnrchr_HIGH_BIT(void)
{
    unsigned char const s_u[] = { 'a', 0xE9, 'b' };
    char const* const   s = (char const*)s_u;

    TEST_PTR_EQ(s + 1, stlsoft_C_strnrchr(s, 3, s[1]));
    TEST_PTR_EQ(s, stlsoft_C_strnrchr(s, 1, 'a'));
    TEST_PTR_NULL(stlsoft_C_strnrchr(s, 3, 'x'));
}

static void TEST_stlsoft_C_wcsnrchr_n_0(void)
{
    TEST_PTR_NULL(stlsoft_C_wcsnrchr(L"abc", 0, L'a'));
    TEST_PTR_NULL(stlsoft_C_wcsnrchr(L"", 0, L'\0'));
}

static void TEST_stlsoft_C_wcsnrchr_MATCH_AT_END(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnrchr(s, 3, L'c'));
    TEST_PTR_EQ(s, stlsoft_C_wcsnrchr(s, 1, L'a'));
}

static void TEST_stlsoft_C_wcsnrchr_MATCH_IN_MIDDLE(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 1, stlsoft_C_wcsnrchr(s, 3, L'b'));
}

static void TEST_stlsoft_C_wcsnrchr_MATCH_AT_START(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s, stlsoft_C_wcsnrchr(s, 3, L'a'));
}

static void TEST_stlsoft_C_wcsnrchr_LAST_OF_SEVERAL(void)
{
    wchar_t const s[] = L"abaca";

    TEST_PTR_EQ(s + 4, stlsoft_C_wcsnrchr(s, 5, L'a'));
    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnrchr(s, 4, L'a'));
}

static void TEST_stlsoft_C_wcsnrchr_MISS(void)
{
    TEST_PTR_NULL(stlsoft_C_wcsnrchr(L"abc", 3, L'z'));
    TEST_PTR_NULL(stlsoft_C_wcsnrchr(L"abc", 3, L'A'));
}

static void TEST_stlsoft_C_wcsnrchr_DOES_NOT_READ_PAST_n(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_NULL(stlsoft_C_wcsnrchr(s, 2, L'c'));
    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnrchr(s, 3, L'c'));
}

static void TEST_stlsoft_C_wcsnrchr_FINDS_EMBEDDED_NUL(void)
{
    wchar_t const s[] = { L'a', L'\0', L'b' };

    TEST_PTR_EQ(s + 1, stlsoft_C_wcsnrchr(s, 3, L'\0'));
}

static void TEST_stlsoft_C_wcsnrchr_CONTINUES_PAST_NUL(void)
{
    wchar_t const s[] = { L'a', L'\0', L'b' };

    TEST_PTR_EQ(s, stlsoft_C_wcsnrchr(s, 3, L'a'));
    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnrchr(s, 3, L'b'));
    TEST_PTR_NULL(stlsoft_C_wcsnrchr(s, 1, L'b'));
}

static void TEST_stlsoft_C_wcsnrchr_HIGH_BIT(void)
{
    wchar_t const s[] = { L'a', L'\x00E9', L'b' };

    TEST_PTR_EQ(s + 1, stlsoft_C_wcsnrchr(s, 3, s[1]));
    TEST_PTR_EQ(s, stlsoft_C_wcsnrchr(s, 1, L'a'));
    TEST_PTR_NULL(stlsoft_C_wcsnrchr(s, 3, L'x'));
}


/* ///////////////////////////// end of file //////////////////////////// */
