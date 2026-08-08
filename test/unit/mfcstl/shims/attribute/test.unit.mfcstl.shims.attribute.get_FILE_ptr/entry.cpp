/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.shims.attribute.get_FILE_ptr/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::get_FILE_ptr` attribute shims.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <mfcstl/shims/attribute/get_FILE_ptr.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void TEST_unopened_stdio_file();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.shims.attribute.get_FILE_ptr", verbosity))
    {
        XTESTS_RUN_CASE(TEST_unopened_stdio_file);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_unopened_stdio_file()
{
    CStdioFile file;

    TEST_PTR_EQ(NULL, stlsoft::get_FILE_ptr(file));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
