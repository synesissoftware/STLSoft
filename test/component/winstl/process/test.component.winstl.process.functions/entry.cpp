/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.process.functions/entry.cpp
 *
 * Purpose: Component-tests for `process/functions`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/process/functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_current_pid(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.process.functions", verbosity))
    {
        XTESTS_RUN_CASE(test_current_pid);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_current_pid(void)
{
    DWORD pid = ::GetCurrentProcessId();
    TEST_UINT_NE(0u, static_cast<unsigned>(pid));
}
