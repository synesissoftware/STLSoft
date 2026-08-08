#include <platformstl/synch/semaphore.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_create_wait_post(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.semaphore", verbosity))
    {
        XTESTS_RUN_CASE(test_create_wait_post);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_create_wait_post(void)
{
    platformstl::semaphore sem(1);
    sem.lock();
    sem.unlock();
    TEST_PASSED();
}
} // anonymous namespace

