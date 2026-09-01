#include <platformstl/synch/process_mutex.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_lock_unlock(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.synch.process_mutex", verbosity))
    {
        XTESTS_RUN_CASE(test_lock_unlock);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_lock_unlock(void)
{
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
    platformstl::process_mutex mx("Global/STLSoft/test.platformstl.process_mutex");
#else
    platformstl::process_mutex mx;
#endif
    mx.lock();
    mx.unlock();
    TEST_PASSED();
}
