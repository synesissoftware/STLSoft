#include <platformstl/synch/thread_mutex.hpp>
#include <stlsoft/synch/lock_scope.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_lock_unlock(void); static void test_lock_scope(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.thread_mutex", verbosity))
    {
        XTESTS_RUN_CASE(test_lock_unlock);
        XTESTS_RUN_CASE(test_lock_scope);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_lock_unlock(void)
{
    platformstl::thread_mutex mx;
    mx.lock();
    mx.unlock();
    TEST_PASSED();
}

static void test_lock_scope(void)
{
    platformstl::thread_mutex mx;
    stlsoft::lock_scope<platformstl::thread_mutex> scope(mx);
    TEST_PASSED();
}
} // anonymous namespace

