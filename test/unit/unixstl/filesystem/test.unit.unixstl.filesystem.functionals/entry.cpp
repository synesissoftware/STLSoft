/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.filesystem.functionals/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/functionals.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/functionals.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


typedef unixstl::path_compare<char> path_compare_t;

static void test_path_compare_equal()
{
    path_compare_t cmp;

    TEST_BOOLEAN_TRUE(cmp("a/b", "a/b"));
    TEST_BOOLEAN_FALSE(cmp("a/b", "a/c"));
}

static void test_path_compare_rooted()
{
    path_compare_t cmp;

    TEST_BOOLEAN_TRUE(cmp("/usr/bin", "/usr/bin"));
    TEST_BOOLEAN_FALSE(cmp("/usr/bin", "/usr/lib"));
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.functionals", verbosity))
    {
        XTESTS_RUN_CASE(test_path_compare_equal);
        XTESTS_RUN_CASE(test_path_compare_rooted);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
