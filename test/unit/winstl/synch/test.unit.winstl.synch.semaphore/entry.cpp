/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.synch.semaphore/entry.cpp
 *
 * Purpose: Unit-tests for `synch/semaphore`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/synch/semaphore.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_create(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.synch.semaphore", verbosity))
    {
        XTESTS_RUN_CASE(test_create);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_create(void)
{
    winstl::semaphore sem(1, 1);
    TEST_PASSED();
}
