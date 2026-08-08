#include <platformstl/performance/performance_counter.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_query(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.performance.performance_counter", verbosity))
    {
        XTESTS_RUN_CASE(test_query);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_query(void)
{
    platformstl::performance_counter pc;

    pc.start();
    pc.stop();

    TEST_INT_GE(0, pc.get_seconds());
    TEST_INT_GE(0, pc.get_microseconds());
}
} // anonymous namespace
