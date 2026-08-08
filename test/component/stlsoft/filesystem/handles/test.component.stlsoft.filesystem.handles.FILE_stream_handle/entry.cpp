/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.stlsoft.filesystem.handles.FILE_stream_handle/entry.cpp
 *
 * Purpose: Component-tests for `stlsoft/filesystem/handles/FILE_stream_handle`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/filesystem/handles/FILE_stream_handle.hpp>

#include <stdio.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_filesystem_compile();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.stlsoft.filesystem.handles.FILE_stream_handle", verbosity))
    {
        XTESTS_RUN_CASE(test_filesystem_compile);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_filesystem_compile()
{
    TEST_BOOLEAN_TRUE(true);
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
