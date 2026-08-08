#include <platformstl/filesystem/cwd_stack.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_default_empty(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.cwd_stack", verbosity))
    {
        XTESTS_RUN_CASE(test_default_empty);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_default_empty(void)
{
    platformstl::cwd_stack stack;
    TEST_BOOLEAN_TRUE(stack.empty());
    TEST_INT_EQ(0, stack.size());
}
} // anonymous namespace
