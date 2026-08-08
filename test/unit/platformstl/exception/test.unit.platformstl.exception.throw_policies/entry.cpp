#include <platformstl/exception/throw_policies.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_policy_type_exists(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.exception.throw_policies", verbosity))
    {
        XTESTS_RUN_CASE(test_policy_type_exists);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_policy_type_exists(void)
{
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::platform_exception_policy));
    TEST_PASSED();
}
} // anonymous namespace

