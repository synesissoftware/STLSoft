/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.filesystem.file_path_buffer/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/file_path_buffer.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/file_path_buffer.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>
#include <string.h>

#include <stlsoft/internal/warnings/push/suppress_deprecation_.h>


namespace {

static void test_file_path_buffer()
{
    unixstl::file_path_buffer_a buf;

    ::strcpy(buf.data(), "/tmp/example.txt");
    TEST_MS_EQ("/tmp/example.txt", buf.c_str());
    TEST_INT_GT(0, buf.size());
}

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.file_path_buffer", verbosity))
    {
        XTESTS_RUN_CASE(test_file_path_buffer);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
