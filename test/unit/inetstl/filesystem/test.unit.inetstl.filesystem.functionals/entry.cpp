/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.inetstl.filesystem.functionals/entry.cpp
 *
 * Purpose: Unit-tests for `inetstl::path_compare`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <inetstl/filesystem/functionals.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_path_compare_equal();
    static void TEST_path_compare_different();
    static void TEST_path_compare_trailing_separators();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.inetstl.filesystem.functionals", verbosity))
    {
        XTESTS_RUN_CASE(TEST_path_compare_equal);
        XTESTS_RUN_CASE(TEST_path_compare_different);
        XTESTS_RUN_CASE(TEST_path_compare_trailing_separators);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    typedef inetstl::path_compare<char>                     path_compare_m_t;
    typedef inetstl::path_compare<wchar_t>                  path_compare_w_t;


static void TEST_path_compare_equal()
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

static void TEST_path_compare_different()
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

static void TEST_path_compare_trailing_separators()
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
