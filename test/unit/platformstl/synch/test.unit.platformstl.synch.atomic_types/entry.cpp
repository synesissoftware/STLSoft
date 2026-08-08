#include <platformstl/synch/atomic_types.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_compile(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.atomic_types", verbosity))
    {
        XTESTS_RUN_CASE(test_compile);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_compile(void)
{
    platformstl::atomic_int_t n = 0;
    STLSOFT_SUPPRESS_UNUSED(n);
    TEST_PASSED();
}
} // anonymous namespace

