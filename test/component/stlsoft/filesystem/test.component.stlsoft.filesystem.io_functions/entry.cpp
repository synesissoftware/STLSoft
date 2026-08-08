/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.stlsoft.filesystem.io_functions/entry.cpp
 *
 * Purpose: Component-tests for `stlsoft/filesystem/io_functions`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/filesystem/io_functions.hpp>

#include <stdio.h>
#include <string>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_io_functions_roundtrip();

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.stlsoft.filesystem.io_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_io_functions_roundtrip);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {


static void test_io_functions_roundtrip()
{
    char const* path = "test_stlsoft_io.tmp";
    FILE* fp = fopen(path, "w");
    TEST_PTR_NE(NULL, fp);
    stlsoft::write_string(fp, "line1\n", 6);
    fclose(fp);
    fp = fopen(path, "r");
    std::string line;
    stlsoft::read_line(fp, line);
    fclose(fp);
    remove(path);
    TEST_MS_EQ("line1", line);
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
