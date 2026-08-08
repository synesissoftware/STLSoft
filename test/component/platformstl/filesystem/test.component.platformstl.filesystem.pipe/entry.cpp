#include <platformstl/filesystem/pipe.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_construct(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.pipe", verbosity))
    {
        XTESTS_RUN_CASE(test_construct);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_construct(void)
{
    platformstl::pipe pipe;
    STLSOFT_SUPPRESS_UNUSED(pipe);
    TEST_PASSED();
}
} // anonymous namespace

