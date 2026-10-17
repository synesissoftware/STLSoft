#include <platformstl/synch/spin_mutex.hpp>
#include <stlsoft/synch/lock_scope.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_lock_unlock(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.spin_mutex", verbosity))
    {
        XTESTS_RUN_CASE(test_lock_unlock);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_lock_unlock(void)
{
    platformstl::spin_mutex mx;
    mx.lock();
    mx.unlock();
    {
        stlsoft::lock_scope<platformstl::spin_mutex> scope(mx);
    }
    TEST_PASSED();
}

