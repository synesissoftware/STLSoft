/* /////////////////////////////////////////////////////////////////////////
 * File:    c_string.strnpbrkn.C/entry.c
 *
 * Purpose: Unit-tests for stlsoft_C_strnpbrkn() and stlsoft_C_wcsnpbrkn().
 *
 * Created: 23rd October 2026
 * Updated: 23rd October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/c_string/strnpbrkn.h>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <xtests/terse-api.h>
#include <xtests/xtests.h>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_stlsoft_C_strnpbrkn_cchStr_0(void);
static void TEST_stlsoft_C_strnpbrkn_cchCharSet_0(void);
static void TEST_stlsoft_C_strnpbrkn_MATCH_AT_START_FIRST_IN_SET(void);
static void TEST_stlsoft_C_strnpbrkn_MATCH_AT_START_LAST_IN_SET(void);
static void TEST_stlsoft_C_strnpbrkn_MATCH_IN_MIDDLE(void);
static void TEST_stlsoft_C_strnpbrkn_MATCH_AT_END(void);
static void TEST_stlsoft_C_strnpbrkn_FIRST_OF_SEVERAL(void);
static void TEST_stlsoft_C_strnpbrkn_MISS(void);
static void TEST_stlsoft_C_strnpbrkn_DOES_NOT_READ_PAST_cchStr(void);
static void TEST_stlsoft_C_strnpbrkn_DOES_NOT_READ_PAST_cchCharSet(void);
static void TEST_stlsoft_C_strnpbrkn_EMBEDDED_NUL_IN_STRING(void);
static void TEST_stlsoft_C_strnpbrkn_NUL_IN_SET(void);
static void TEST_stlsoft_C_strnpbrkn_SINGLE_BYTE_SET(void);
static void TEST_stlsoft_C_strnpbrkn_SET_LONGER_THAN_STRING(void);
static void TEST_stlsoft_C_wcsnpbrkn_cchStr_0(void);
static void TEST_stlsoft_C_wcsnpbrkn_cchCharSet_0(void);
static void TEST_stlsoft_C_wcsnpbrkn_MATCH_AT_START_FIRST_IN_SET(void);
static void TEST_stlsoft_C_wcsnpbrkn_MATCH_AT_START_LAST_IN_SET(void);
static void TEST_stlsoft_C_wcsnpbrkn_MATCH_IN_MIDDLE(void);
static void TEST_stlsoft_C_wcsnpbrkn_MATCH_AT_END(void);
static void TEST_stlsoft_C_wcsnpbrkn_FIRST_OF_SEVERAL(void);
static void TEST_stlsoft_C_wcsnpbrkn_MISS(void);
static void TEST_stlsoft_C_wcsnpbrkn_DOES_NOT_READ_PAST_cchStr(void);
static void TEST_stlsoft_C_wcsnpbrkn_DOES_NOT_READ_PAST_cchCharSet(void);
static void TEST_stlsoft_C_wcsnpbrkn_EMBEDDED_NUL_IN_STRING(void);
static void TEST_stlsoft_C_wcsnpbrkn_NUL_IN_SET(void);
static void TEST_stlsoft_C_wcsnpbrkn_SINGLE_BYTE_SET(void);
static void TEST_stlsoft_C_wcsnpbrkn_SET_LONGER_THAN_STRING(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.c_string.strnpbrkn.C", verbosity))
    {
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_cchStr_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_cchCharSet_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_MATCH_AT_START_FIRST_IN_SET);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_MATCH_AT_START_LAST_IN_SET);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_FIRST_OF_SEVERAL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_MISS);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_DOES_NOT_READ_PAST_cchStr);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_DOES_NOT_READ_PAST_cchCharSet);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_EMBEDDED_NUL_IN_STRING);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_NUL_IN_SET);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_SINGLE_BYTE_SET);
        XTESTS_RUN_CASE(TEST_stlsoft_C_strnpbrkn_SET_LONGER_THAN_STRING);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_cchStr_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_cchCharSet_0);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_MATCH_AT_START_FIRST_IN_SET);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_MATCH_AT_START_LAST_IN_SET);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_MATCH_IN_MIDDLE);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_MATCH_AT_END);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_FIRST_OF_SEVERAL);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_MISS);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_DOES_NOT_READ_PAST_cchStr);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_DOES_NOT_READ_PAST_cchCharSet);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_EMBEDDED_NUL_IN_STRING);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_NUL_IN_SET);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_SINGLE_BYTE_SET);
        XTESTS_RUN_CASE(TEST_stlsoft_C_wcsnpbrkn_SET_LONGER_THAN_STRING);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_stlsoft_C_strnpbrkn_cchStr_0(void)
{
    TEST_PTR_NULL(stlsoft_C_strnpbrkn("abc", 0, "a", 1));
    TEST_PTR_NULL(stlsoft_C_strnpbrkn("", 0, "", 0));
}

static void TEST_stlsoft_C_strnpbrkn_cchCharSet_0(void)
{
    TEST_PTR_NULL(stlsoft_C_strnpbrkn("abc", 3, "xyz", 0));
    TEST_PTR_NULL(stlsoft_C_strnpbrkn("abc", 3, "", 0));
}

static void TEST_stlsoft_C_strnpbrkn_MATCH_AT_START_FIRST_IN_SET(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s, stlsoft_C_strnpbrkn(s, 3, "ax", 2));
}

static void TEST_stlsoft_C_strnpbrkn_MATCH_AT_START_LAST_IN_SET(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s, stlsoft_C_strnpbrkn(s, 3, "xya", 3));
}

static void TEST_stlsoft_C_strnpbrkn_MATCH_IN_MIDDLE(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 1, stlsoft_C_strnpbrkn(s, 3, "xb", 2));
}

static void TEST_stlsoft_C_strnpbrkn_MATCH_AT_END(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 2, stlsoft_C_strnpbrkn(s, 3, "zc", 2));
}

static void TEST_stlsoft_C_strnpbrkn_FIRST_OF_SEVERAL(void)
{
    char const s[] = "bXa";

    TEST_PTR_EQ(s + 1, stlsoft_C_strnpbrkn(s, 3, "aX", 2));
}

static void TEST_stlsoft_C_strnpbrkn_MISS(void)
{
    TEST_PTR_NULL(stlsoft_C_strnpbrkn("abc", 3, "xyz", 3));
}

static void TEST_stlsoft_C_strnpbrkn_DOES_NOT_READ_PAST_cchStr(void)
{
    char const s[] = "abcZ";

    TEST_PTR_NULL(stlsoft_C_strnpbrkn(s, 3, "Z", 1));
    TEST_PTR_EQ(s + 3, stlsoft_C_strnpbrkn(s, 4, "Z", 1));
}

static void TEST_stlsoft_C_strnpbrkn_DOES_NOT_READ_PAST_cchCharSet(void)
{
    char const str[] = "Zzz";
    char const set[] = { 'x', 'y', 'Z' };

    TEST_PTR_NULL(stlsoft_C_strnpbrkn(str, 3, set, 2));
    TEST_PTR_EQ(str, stlsoft_C_strnpbrkn(str, 3, set, 3));
}

static void TEST_stlsoft_C_strnpbrkn_EMBEDDED_NUL_IN_STRING(void)
{
    char const str[] = { 'a', '\0', 'b' };
    char const set[] = { 'b' };

    TEST_PTR_EQ(str + 2, stlsoft_C_strnpbrkn(str, 3, set, 1));
    TEST_PTR_NULL(stlsoft_C_strnpbrkn(str, 2, set, 1));
}

static void TEST_stlsoft_C_strnpbrkn_NUL_IN_SET(void)
{
    char const str[] = { 'a', '\0', 'b' };
    char const set[] = { 'x', '\0', 'q' };

    TEST_PTR_EQ(str + 1, stlsoft_C_strnpbrkn(str, 3, set, 3));
    TEST_PTR_NULL(stlsoft_C_strnpbrkn(str, 3, set, 1));
}

static void TEST_stlsoft_C_strnpbrkn_SINGLE_BYTE_SET(void)
{
    char const s[] = "abc";

    TEST_PTR_EQ(s + 1, stlsoft_C_strnpbrkn(s, 3, "b", 1));
    TEST_PTR_NULL(stlsoft_C_strnpbrkn(s, 3, "z", 1));
}

static void TEST_stlsoft_C_strnpbrkn_SET_LONGER_THAN_STRING(void)
{
    char const s[] = "b";

    TEST_PTR_EQ(s, stlsoft_C_strnpbrkn(s, 1, "xyzb", 4));
    TEST_PTR_NULL(stlsoft_C_strnpbrkn(s, 1, "xyza", 4));
}

static void TEST_stlsoft_C_wcsnpbrkn_cchStr_0(void)
{
    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(L"abc", 0, L"a", 1));
    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(L"", 0, L"", 0));
}

static void TEST_stlsoft_C_wcsnpbrkn_cchCharSet_0(void)
{
    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(L"abc", 3, L"xyz", 0));
    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(L"abc", 3, L"", 0));
}

static void TEST_stlsoft_C_wcsnpbrkn_MATCH_AT_START_FIRST_IN_SET(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s, stlsoft_C_wcsnpbrkn(s, 3, L"ax", 2));
}

static void TEST_stlsoft_C_wcsnpbrkn_MATCH_AT_START_LAST_IN_SET(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s, stlsoft_C_wcsnpbrkn(s, 3, L"xya", 3));
}

static void TEST_stlsoft_C_wcsnpbrkn_MATCH_IN_MIDDLE(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 1, stlsoft_C_wcsnpbrkn(s, 3, L"xb", 2));
}

static void TEST_stlsoft_C_wcsnpbrkn_MATCH_AT_END(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 2, stlsoft_C_wcsnpbrkn(s, 3, L"zc", 2));
}

static void TEST_stlsoft_C_wcsnpbrkn_FIRST_OF_SEVERAL(void)
{
    wchar_t const s[] = L"bXa";

    TEST_PTR_EQ(s + 1, stlsoft_C_wcsnpbrkn(s, 3, L"aX", 2));
}

static void TEST_stlsoft_C_wcsnpbrkn_MISS(void)
{
    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(L"abc", 3, L"xyz", 3));
}

static void TEST_stlsoft_C_wcsnpbrkn_DOES_NOT_READ_PAST_cchStr(void)
{
    wchar_t const s[] = L"abcZ";

    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(s, 3, L"Z", 1));
    TEST_PTR_EQ(s + 3, stlsoft_C_wcsnpbrkn(s, 4, L"Z", 1));
}

static void TEST_stlsoft_C_wcsnpbrkn_DOES_NOT_READ_PAST_cchCharSet(void)
{
    wchar_t const str[] = L"Zzz";
    wchar_t const set[] = { L'x', L'y', L'Z' };

    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(str, 3, set, 2));
    TEST_PTR_EQ(str, stlsoft_C_wcsnpbrkn(str, 3, set, 3));
}

static void TEST_stlsoft_C_wcsnpbrkn_EMBEDDED_NUL_IN_STRING(void)
{
    wchar_t const str[] = { L'a', L'\0', L'b' };
    wchar_t const set[] = { L'b' };

    TEST_PTR_EQ(str + 2, stlsoft_C_wcsnpbrkn(str, 3, set, 1));
    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(str, 2, set, 1));
}

static void TEST_stlsoft_C_wcsnpbrkn_NUL_IN_SET(void)
{
    wchar_t const str[] = { L'a', L'\0', L'b' };
    wchar_t const set[] = { L'x', L'\0', L'q' };

    TEST_PTR_EQ(str + 1, stlsoft_C_wcsnpbrkn(str, 3, set, 3));
    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(str, 3, set, 1));
}

static void TEST_stlsoft_C_wcsnpbrkn_SINGLE_BYTE_SET(void)
{
    wchar_t const s[] = L"abc";

    TEST_PTR_EQ(s + 1, stlsoft_C_wcsnpbrkn(s, 3, L"b", 1));
    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(s, 3, L"z", 1));
}

static void TEST_stlsoft_C_wcsnpbrkn_SET_LONGER_THAN_STRING(void)
{
    wchar_t const s[] = L"b";

    TEST_PTR_EQ(s, stlsoft_C_wcsnpbrkn(s, 1, L"xyzb", 4));
    TEST_PTR_NULL(stlsoft_C_wcsnpbrkn(s, 1, L"xyza", 4));
}


/* ///////////////////////////// end of file //////////////////////////// */
