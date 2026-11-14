#include <platformstl/synch/refcount_policies.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void TEST_TYPES_EXIST();

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_TYPES_EXIST);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void TEST_TYPES_EXIST()
{
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::refcount_policy_single_threaded));
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::refcount_policy_multi_threaded));
    TEST_PASSED();
}

