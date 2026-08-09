#include <platformstl/synch/refcount_policies.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_types_exist(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.refcount_policies", verbosity))
    {
        XTESTS_RUN_CASE(test_types_exist);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_types_exist(void)
{
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::refcount_policy_single_threaded));
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::refcount_policy_multi_threaded));
    TEST_PASSED();
}

