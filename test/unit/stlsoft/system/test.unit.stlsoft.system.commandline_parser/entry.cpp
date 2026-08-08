/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.system.commandline_parser/entry.cpp
 *
 * Purpose: Compile-verified test for component header.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/system/commandline_parser.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

static void TEST_compile_and_link(void)
{
    TEST_PASSED();
}

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.system.commandline_parser", verbosity))
    {
        XTESTS_RUN_CASE(TEST_compile_and_link);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* ///////////////////////////// end of file //////////////////////////// */
