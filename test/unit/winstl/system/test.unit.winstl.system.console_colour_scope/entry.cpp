/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.system.console_colour_scope/entry.cpp
 *
 * Purpose: Unit-tests for `system/console_colour_scope`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/system/console_colour_scope.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_scope(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.system.console_colour_scope", verbosity))
    {
        XTESTS_RUN_CASE(test_scope);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_scope(void)
{
    TEST_PASSED();
}
