/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.diagnostics.threadtimes_stopwatch/entry.cpp
 *
 * Purpose: Component-tests for `diagnostics/threadtimes_stopwatch`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/diagnostics/threadtimes_stopwatch.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_start_stop(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.diagnostics.threadtimes_stopwatch", verbosity))
    {
        XTESTS_RUN_CASE(test_start_stop);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_start_stop(void)
{
    winstl::threadtimes_stopwatch sw;
    sw.start();
    winstl::micro_sleep(1);
    sw.stop();
    TEST_BOOLEAN_TRUE(sw.get_seconds() >= 0.0);
}
