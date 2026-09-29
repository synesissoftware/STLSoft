/* /////////////////////////////////////////////////////////////////////////
 * File:    cstring/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::strcmp and stlsoft::strncmp.
 *
 * Created: 29th September 2026
 * Updated: 29th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* string_view's c_str_ptr exists only when this is defined. The string
 * headers precede cstring.hpp so those overloads are visible to the
 * qualified call in the S const& templates.
 */
#define STLSOFT_STRING_VIEW_PROVIDE_c_str
#include <stlsoft/string/simple_string.hpp>
#include <stlsoft/string/string_view.hpp>
#include <stlsoft/std/cstring.hpp>


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

    static void TEST_strcmp_CHAR();
    static void TEST_strcmp_WCHAR();
    static void TEST_strncmp_n_0();
    static void TEST_strncmp_STOPS_AT_NUL();
    static void TEST_strcmp_SHIM_simple_string();
    static void TEST_strcmp_SHIM_string_view();
    static void TEST_strncmp_SHIM();

} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.std.cstring", verbosity))
    {
        XTESTS_RUN_CASE(TEST_strcmp_CHAR);
        XTESTS_RUN_CASE(TEST_strcmp_WCHAR);
        XTESTS_RUN_CASE(TEST_strncmp_n_0);
        XTESTS_RUN_CASE(TEST_strncmp_STOPS_AT_NUL);
        XTESTS_RUN_CASE(TEST_strcmp_SHIM_simple_string);
        XTESTS_RUN_CASE(TEST_strcmp_SHIM_string_view);
        XTESTS_RUN_CASE(TEST_strncmp_SHIM);

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

static void TEST_strcmp_CHAR()
{
    unsigned char const below_u[] = { 0x01, 0 };
    unsigned char const above_u[] = { 0xFF, 0 };
    char const* const   below = reinterpret_cast<char const*>(below_u);
    char const* const   above = reinterpret_cast<char const*>(above_u);

    TEST_INT_EQ(0, stlsoft::strcmp("abc", "abc"));
    TEST_INT_EQ(0, stlsoft::strcmp("", ""));
    TEST_INT_LT(0, stlsoft::strcmp("abc", "abd"));
    TEST_INT_LT(0, stlsoft::strcmp("", "a"));
    TEST_INT_GT(0, stlsoft::strcmp("abd", "abc"));
    TEST_INT_GT(0, stlsoft::strcmp("a", ""));
    TEST_INT_LT(0, stlsoft::strcmp("A", "a"));
    TEST_INT_LT(0, stlsoft::strcmp(below, above));
}

static void TEST_strcmp_WCHAR()
{
    TEST_INT_EQ(0, stlsoft::strcmp(L"abc", L"abc"));
    TEST_INT_EQ(0, stlsoft::strcmp(L"", L""));
    TEST_INT_LT(0, stlsoft::strcmp(L"abc", L"abd"));
    TEST_INT_LT(0, stlsoft::strcmp(L"", L"a"));
    TEST_INT_GT(0, stlsoft::strcmp(L"abd", L"abc"));
    TEST_INT_GT(0, stlsoft::strcmp(L"a", L""));
    TEST_INT_LT(0, stlsoft::strcmp(L"A", L"a"));
}

static void TEST_strncmp_n_0()
{
    TEST_INT_EQ(0, stlsoft::strncmp("abc", "xyz", 0));
    TEST_INT_EQ(0, stlsoft::strncmp("", "abc", 0));
    TEST_INT_EQ(0, stlsoft::strncmp("abX", "abY", 2));
    TEST_INT_LT(0, stlsoft::strncmp("abX", "abY", 3));

    TEST_INT_EQ(0, stlsoft::strncmp(L"abc", L"xyz", 0));
    TEST_INT_EQ(0, stlsoft::strncmp(L"", L"abc", 0));
    TEST_INT_EQ(0, stlsoft::strncmp(L"abX", L"abY", 2));
    TEST_INT_LT(0, stlsoft::strncmp(L"abX", L"abY", 3));
}

static void TEST_strncmp_STOPS_AT_NUL()
{
    char const a1[] = { 'a', '\0', 'x' };
    char const a2[] = { 'a', '\0', 'y' };
    wchar_t const w1[] = { L'a', L'\0', L'x' };
    wchar_t const w2[] = { L'a', L'\0', L'y' };

    TEST_INT_EQ(0, stlsoft::strncmp(a1, a2, 3));
    TEST_INT_EQ(0, stlsoft::strncmp(w1, w2, 3));
}

static void TEST_strcmp_SHIM_simple_string()
{
    stlsoft::simple_string const abc("abc");
    stlsoft::simple_string const abd("abd");
    stlsoft::simple_string const empty;
    stlsoft::simple_wstring const wabc(L"abc");
    stlsoft::simple_wstring const wabd(L"abd");
    stlsoft::simple_wstring const wempty;

    TEST_INT_EQ(0, stlsoft::strcmp(abc, abc));
    TEST_INT_EQ(0, stlsoft::strcmp(empty, empty));
    TEST_INT_LT(0, stlsoft::strcmp(abc, abd));
    TEST_INT_LT(0, stlsoft::strcmp(empty, abc));
    TEST_INT_GT(0, stlsoft::strcmp(abd, abc));

    TEST_INT_EQ(0, stlsoft::strcmp(wabc, wabc));
    TEST_INT_EQ(0, stlsoft::strcmp(wempty, wempty));
    TEST_INT_LT(0, stlsoft::strcmp(wabc, wabd));
    TEST_INT_GT(0, stlsoft::strcmp(wabd, wabc));
}

static void TEST_strcmp_SHIM_string_view()
{
    stlsoft::string_view const abc("abc");
    stlsoft::string_view const abd("abd");
    stlsoft::string_view const empty;
    stlsoft::wstring_view const wabc(L"abc");
    stlsoft::wstring_view const wabd(L"abd");
    stlsoft::wstring_view const wempty;

    TEST_INT_EQ(0, stlsoft::strcmp(abc, abc));
    TEST_INT_EQ(0, stlsoft::strcmp(empty, empty));
    TEST_INT_LT(0, stlsoft::strcmp(abc, abd));
    TEST_INT_LT(0, stlsoft::strcmp(empty, abc));
    TEST_INT_GT(0, stlsoft::strcmp(abd, abc));

    TEST_INT_EQ(0, stlsoft::strcmp(wabc, wabc));
    TEST_INT_EQ(0, stlsoft::strcmp(wempty, wempty));
    TEST_INT_LT(0, stlsoft::strcmp(wabc, wabd));
    TEST_INT_GT(0, stlsoft::strcmp(wabd, wabc));
}

static void TEST_strncmp_SHIM()
{
    char const a1[] = { 'a', '\0', 'x' };
    char const a2[] = { 'a', '\0', 'y' };
    wchar_t const w1[] = { L'a', L'\0', L'x' };
    wchar_t const w2[] = { L'a', L'\0', L'y' };

    stlsoft::simple_string const abX("abX");
    stlsoft::simple_string const abY("abY");
    stlsoft::simple_string const embedded1(a1, 3);
    stlsoft::simple_string const embedded2(a2, 3);
    stlsoft::string_view const v1(a1, 3);
    stlsoft::string_view const v2(a2, 3);

    stlsoft::simple_wstring const wabX(L"abX");
    stlsoft::simple_wstring const wabY(L"abY");
    stlsoft::simple_wstring const wembedded1(w1, 3);
    stlsoft::simple_wstring const wembedded2(w2, 3);
    stlsoft::wstring_view const wv1(w1, 3);
    stlsoft::wstring_view const wv2(w2, 3);

    TEST_INT_EQ(0, stlsoft::strncmp(abX, abY, 0));
    TEST_INT_EQ(0, stlsoft::strncmp(abX, abY, 2));
    TEST_INT_LT(0, stlsoft::strncmp(abX, abY, 3));
    TEST_INT_EQ(0, stlsoft::strncmp(embedded1, embedded2, 3));
    TEST_INT_EQ(0, stlsoft::strncmp(v1, v2, 3));

    TEST_INT_EQ(0, stlsoft::strncmp(wabX, wabY, 0));
    TEST_INT_EQ(0, stlsoft::strncmp(wabX, wabY, 2));
    TEST_INT_LT(0, stlsoft::strncmp(wabX, wabY, 3));
    TEST_INT_EQ(0, stlsoft::strncmp(wembedded1, wembedded2, 3));
    TEST_INT_EQ(0, stlsoft::strncmp(wv1, wv2, 3));
}

} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

