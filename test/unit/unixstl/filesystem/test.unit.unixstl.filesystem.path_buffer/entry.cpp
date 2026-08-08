/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.filesystem.path_buffer/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/path_buffer.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/path_buffer.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>
#include <string.h>


namespace {

static void test_default_constructed_empty()
{
    unixstl::path_buffer_a buf;

    TEST_INT_EQ(0, buf.size());
    TEST_MS_EQ("", buf.c_str());
}

static void test_assign_and_clear()
{
    unixstl::path_buffer_a buf;

    buf.assign("hello/world", ::strlen("hello/world"));
    TEST_MS_EQ("hello/world", buf.c_str());

    buf.assign("", 0);
    TEST_INT_EQ(0, buf.size());
}

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.path_buffer", verbosity))
    {
        XTESTS_RUN_CASE(test_default_constructed_empty);
        XTESTS_RUN_CASE(test_assign_and_clear);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
