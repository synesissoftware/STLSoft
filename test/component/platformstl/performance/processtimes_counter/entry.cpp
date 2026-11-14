#include <platformstl/performance/processtimes_counter.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void TEST_QUERY();

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.performance.processtimes_counter", verbosity))
    {
        XTESTS_RUN_CASE(TEST_QUERY);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void TEST_QUERY()
{
    platformstl::processtimes_counter pc;

    pc.start();
    pc.stop();
    TEST_BOOLEAN_TRUE(pc.get_seconds() >= 0);
}

