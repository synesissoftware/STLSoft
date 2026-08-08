#include <platformstl/synch/refcount_policies/refcount_policy_multi_threaded.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <thread>

namespace { static void test_increment_decrement(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.refcount_policies.refcount_policy_multi_threaded", verbosity))
    {
        XTESTS_RUN_CASE(test_increment_decrement);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_increment_decrement(void)
{
    platformstl::refcount_policy_multi_threaded policy;
    platformstl::atomic_int_t rc = 0;
    policy.addref(rc);
    policy.addref(rc);
    TEST_INT_EQ(2, rc);
    policy.release(rc);
    TEST_INT_EQ(1, rc);
    policy.release(rc);
    TEST_INT_EQ(0, rc);
}
} // anonymous namespace

