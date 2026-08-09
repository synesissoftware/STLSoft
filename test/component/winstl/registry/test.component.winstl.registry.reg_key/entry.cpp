/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.registry.reg_key/entry.cpp
 *
 * Purpose: Component-tests for `registry/reg_key`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/registry/reg_key.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_open_current_user(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.registry.reg_key", verbosity))
    {
        XTESTS_RUN_CASE(test_open_current_user);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_open_current_user(void)
{
    winstl::reg_key key(HKEY_CURRENT_USER);
    TEST_PTR_NE(NULL, key.get());
}
