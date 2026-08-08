#include <platformstl/filesystem/current_directory.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_non_empty(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.current_directory", verbosity))
    {
        XTESTS_RUN_CASE(test_non_empty);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_non_empty(void)
{
    platformstl::current_directory_a cwd;
    TEST(0u != stlsoft::c_str_len(cwd));
}
} // anonymous namespace
