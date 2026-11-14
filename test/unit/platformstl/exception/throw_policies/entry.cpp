#include <platformstl/exception/throw_policies.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void TEST_POLICY_TYPE_EXISTS();

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_POLICY_TYPE_EXISTS);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void TEST_POLICY_TYPE_EXISTS()
{
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::platform_exception_policy));
    TEST_PASSED();
}

