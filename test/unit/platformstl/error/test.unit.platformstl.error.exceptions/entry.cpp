#include <platformstl/error/exceptions.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_obsolete_header_compiles(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.error.exceptions", verbosity))
    {
        XTESTS_RUN_CASE(test_obsolete_header_compiles);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_obsolete_header_compiles(void)
{
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::platform_exception_policy));
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::platformstl_exception));
    TEST_PASSED();
}

