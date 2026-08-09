/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.system.environment_variable/entry.cpp
 *
 * Purpose: Component-tests for `system/environment_variable`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/system/environment_variable.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_path(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.system.environment_variable", verbosity))
    {
        XTESTS_RUN_CASE(test_path);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_path(void)
{
    winstl::environment_variable ev("PATH");
    TEST_UINT_NE(0u, ev.length());
}
