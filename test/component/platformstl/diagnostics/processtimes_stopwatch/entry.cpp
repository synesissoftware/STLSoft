#include <platformstl/diagnostics/processtimes_stopwatch.hpp>
#include <platformstl/synch/sleep_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void TEST_START_STOP();

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.diagnostics.processtimes_stopwatch", verbosity))
    {
        XTESTS_RUN_CASE(TEST_START_STOP);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void TEST_START_STOP()
{
    platformstl::processtimes_stopwatch sw;
    sw.start();
    platformstl::micro_sleep(1000);
    sw.stop();
    TEST_BOOLEAN_TRUE(sw.get_seconds() >= 0);
}

