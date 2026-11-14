/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/inetstl/filesystem/functionals/entry.cpp
 *
 * Purpose: Unit-tests for `inetstl::path_compare`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <inetstl/filesystem/functionals.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_PATH_COMPARE_EQUAL();
    static void TEST_PATH_COMPARE_DIFFERENT();
    static void TEST_PATH_COMPARE_TRAILING_SEPARATORS();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_PATH_COMPARE_EQUAL);
        XTESTS_RUN_CASE(TEST_PATH_COMPARE_DIFFERENT);
        XTESTS_RUN_CASE(TEST_PATH_COMPARE_TRAILING_SEPARATORS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

typedef inetstl::path_compare<char>                     path_compare_m_t;
    typedef inetstl::path_compare<wchar_t>                  path_compare_w_t;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_PATH_COMPARE_EQUAL()
{
    {
        path_compare_m_t    cmp;

        TEST_BOOLEAN_TRUE(cmp("/pub/docs", "/pub/docs"));
        TEST_BOOLEAN_TRUE(cmp("readme.txt", "readme.txt"));
    }

    {
        path_compare_w_t    cmp;

        TEST_BOOLEAN_TRUE(cmp(L"/pub/docs", L"/pub/docs"));
        TEST_BOOLEAN_TRUE(cmp(L"readme.txt", L"readme.txt"));
    }
}

static void TEST_PATH_COMPARE_DIFFERENT()
{
    {
        path_compare_m_t    cmp;

        TEST_BOOLEAN_FALSE(cmp("/pub/docs", "/pub/other"));
        TEST_BOOLEAN_FALSE(cmp("readme.txt", "readme.doc"));
    }

    {
        path_compare_w_t    cmp;

        TEST_BOOLEAN_FALSE(cmp(L"/pub/docs", L"/pub/other"));
        TEST_BOOLEAN_FALSE(cmp(L"readme.txt", L"readme.doc"));
    }
}

static void TEST_PATH_COMPARE_TRAILING_SEPARATORS()
{
    {
        path_compare_m_t    cmp;

        TEST_BOOLEAN_TRUE(cmp("/pub/docs/", "/pub/docs"));
        TEST_BOOLEAN_TRUE(cmp("/pub/docs", "/pub/docs/"));
        TEST_BOOLEAN_TRUE(cmp("/pub/docs/", "/pub/docs/"));
    }

    {
        path_compare_w_t    cmp;

        TEST_BOOLEAN_TRUE(cmp(L"/pub/docs/", L"/pub/docs"));
        TEST_BOOLEAN_TRUE(cmp(L"/pub/docs", L"/pub/docs/"));
        TEST_BOOLEAN_TRUE(cmp(L"/pub/docs/", L"/pub/docs/"));
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
