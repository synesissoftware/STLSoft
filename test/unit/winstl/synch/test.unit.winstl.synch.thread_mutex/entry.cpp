/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.synch.thread_mutex/entry.cpp
 *
 * Purpose: Unit-tests for `synch/thread_mutex`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/synch/thread_mutex.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_lock(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.synch.thread_mutex", verbosity))
    {
        XTESTS_RUN_CASE(test_lock);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_lock(void)
{
    winstl::thread_mutex mx;
    mx.lock();
    mx.unlock();
    TEST_PASSED();
}
