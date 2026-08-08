/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.synch.sleep_functions/entry.cpp
 *
 * Purpose: Unit-tests for `synch/sleep_functions`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/synch/sleep_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_sleep_zero(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.synch.sleep_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_sleep_zero);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_sleep_zero(void)
{
    winstl::micro_sleep(0);
    TEST_PASSED();
}
