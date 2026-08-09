/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.synch.process_mutex/entry.cpp
 *
 * Purpose: Component-tests for `synch/process_mutex`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/synch/process_mutex.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_lock_unlock(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.synch.process_mutex", verbosity))
    {
        XTESTS_RUN_CASE(test_lock_unlock);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_lock_unlock(void)
{
    winstl::process_mutex mx("Global/STLSoft/test.winstl.process_mutex");
    mx.lock();
    mx.unlock();
    TEST_PASSED();
}
