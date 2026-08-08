/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.filesystem.current_directory/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/filesystem/current_directory.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/current_directory.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_get_current_directory()
{
    unixstl::current_directory_a cwd;

    TEST_INT_GT(0, cwd.length());
    TEST_PTR_NE(NULL, cwd.c_str());
    TEST_CHAR_EQ('\0', cwd.c_str()[cwd.length()]);
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.filesystem.current_directory", verbosity))
    {
        XTESTS_RUN_CASE(test_get_current_directory);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
