#include <platformstl/synch/thread_mutex.hpp>
#include <stlsoft/synch/lock_scope.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {

    static void TEST_LOCK_UNLOCK();
    static void TEST_LOCK_SCOPE();
}

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_LOCK_UNLOCK);
        XTESTS_RUN_CASE(TEST_LOCK_SCOPE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void TEST_LOCK_UNLOCK()
{
    platformstl::thread_mutex mx;
    mx.lock();
    mx.unlock();
    TEST_PASSED();
}

static void TEST_LOCK_SCOPE()
{
    platformstl::thread_mutex mx;
    stlsoft::lock_scope<platformstl::thread_mutex> scope(mx);
    TEST_PASSED();
}
} // anonymous namespace

