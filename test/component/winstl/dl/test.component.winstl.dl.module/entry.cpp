/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.dl.module/entry.cpp
 *
 * Purpose: Component-tests for `dl/module`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/dl/module.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_kernel32(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.dl.module", verbosity))
    {
        XTESTS_RUN_CASE(test_kernel32);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_kernel32(void)
{
    winstl::module mod("kernel32.dll");
    TEST_PTR_NE(NULL, mod.get_module_handle());
}
