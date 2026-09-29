/* /////////////////////////////////////////////////////////////////////////
 * File:    functionals.string_begins_with/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::string_begins_with.
 *
 * Created: 29th September 2026
 * Updated: 29th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/functionals.hpp>
#include <stlsoft/string/simple_string.hpp>


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

    static void TEST_string_begins_with_MATCH();
    static void TEST_string_begins_with_REJECT();
    static void TEST_string_begins_with_EMPTY_PREFIX();
    static void TEST_string_begins_with_LONGER_PREFIX();
    static void TEST_string_begins_with_CASE_SENSITIVE();
    static void TEST_string_begins_with_WCHAR();

} /* anonymous namespace */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.functionals.string_begins_with", verbosity))
    {
        XTESTS_RUN_CASE(TEST_string_begins_with_MATCH);
        XTESTS_RUN_CASE(TEST_string_begins_with_REJECT);
        XTESTS_RUN_CASE(TEST_string_begins_with_EMPTY_PREFIX);
        XTESTS_RUN_CASE(TEST_string_begins_with_LONGER_PREFIX);
        XTESTS_RUN_CASE(TEST_string_begins_with_CASE_SENSITIVE);
        XTESTS_RUN_CASE(TEST_string_begins_with_WCHAR);

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

static void TEST_string_begins_with_MATCH()
{
    stlsoft::string_begins_with_function<char> const begins = stlsoft::string_begins_with("ab");
    stlsoft::simple_string const abc("abc");
    char const embedded[] = { 'a', '\0', 'x' };
    stlsoft::string_begins_with_function<char> const begins_n(embedded);

    TEST_BOOLEAN_TRUE(begins("abc"));
    TEST_BOOLEAN_TRUE(begins("ab"));
    TEST_BOOLEAN_TRUE(begins("abcd"));
    TEST_BOOLEAN_TRUE(begins(abc));

    TEST_BOOLEAN_TRUE(begins_n("abc"));
    TEST_BOOLEAN_FALSE(begins_n("xbc"));
}

static void TEST_string_begins_with_REJECT()
{
    stlsoft::string_begins_with_function<char> const begins = stlsoft::string_begins_with("abc");
    stlsoft::simple_string const abd("abd");

    TEST_BOOLEAN_FALSE(begins("abd"));
    TEST_BOOLEAN_FALSE(begins("xbc"));
    TEST_BOOLEAN_FALSE(begins("ab"));
    TEST_BOOLEAN_FALSE(begins(""));
    TEST_BOOLEAN_FALSE(begins(abd));
}

static void TEST_string_begins_with_EMPTY_PREFIX()
{
    stlsoft::string_begins_with_function<char> const begins = stlsoft::string_begins_with("");

    TEST_BOOLEAN_TRUE(begins("abc"));
    TEST_BOOLEAN_TRUE(begins(""));
}

static void TEST_string_begins_with_LONGER_PREFIX()
{
    stlsoft::string_begins_with_function<char> const begins = stlsoft::string_begins_with("abcd");

    TEST_BOOLEAN_FALSE(begins("abc"));
    TEST_BOOLEAN_FALSE(begins(""));
    TEST_BOOLEAN_TRUE(begins("abcd"));
    TEST_BOOLEAN_TRUE(begins("abcde"));
}

static void TEST_string_begins_with_CASE_SENSITIVE()
{
    stlsoft::string_begins_with_function<char> const begins = stlsoft::string_begins_with("Ab");

    TEST_BOOLEAN_FALSE(begins("abc"));
    TEST_BOOLEAN_FALSE(begins("aBc"));
    TEST_BOOLEAN_TRUE(begins("Abc"));
    TEST_BOOLEAN_TRUE(begins("Ab"));
}

static void TEST_string_begins_with_WCHAR()
{
    stlsoft::string_begins_with_function<wchar_t> const begins = stlsoft::string_begins_with(L"ab");
    stlsoft::simple_wstring const abc(L"abc");
    wchar_t const embedded[] = { L'a', L'\0', L'x' };
    stlsoft::string_begins_with_function<wchar_t> const begins_n(embedded);
    stlsoft::string_begins_with_function<wchar_t> const begins_abc = stlsoft::string_begins_with(L"abc");
    stlsoft::string_begins_with_function<wchar_t> const begins_empty = stlsoft::string_begins_with(L"");
    stlsoft::string_begins_with_function<wchar_t> const begins_long = stlsoft::string_begins_with(L"abcd");
    stlsoft::string_begins_with_function<wchar_t> const begins_case = stlsoft::string_begins_with(L"Ab");

    TEST_BOOLEAN_TRUE(begins(L"abc"));
    TEST_BOOLEAN_TRUE(begins(L"ab"));
    TEST_BOOLEAN_TRUE(begins(L"abcd"));
    TEST_BOOLEAN_TRUE(begins(abc));

    TEST_BOOLEAN_TRUE(begins_n(L"abc"));
    TEST_BOOLEAN_FALSE(begins_n(L"xbc"));

    TEST_BOOLEAN_FALSE(begins_abc(L"abd"));
    TEST_BOOLEAN_FALSE(begins_abc(L"ab"));
    TEST_BOOLEAN_FALSE(begins_abc(L""));

    TEST_BOOLEAN_TRUE(begins_empty(L"abc"));
    TEST_BOOLEAN_TRUE(begins_empty(L""));

    TEST_BOOLEAN_FALSE(begins_long(L"abc"));
    TEST_BOOLEAN_TRUE(begins_long(L"abcd"));

    TEST_BOOLEAN_FALSE(begins_case(L"abc"));
    TEST_BOOLEAN_TRUE(begins_case(L"Abc"));
}

} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

