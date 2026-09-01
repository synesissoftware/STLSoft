#include <platformstl/system/home_directory.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_non_empty(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.system.home_directory", verbosity))
    {
        XTESTS_RUN_CASE(test_non_empty);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_non_empty(void)
{
    platformstl::home_directory dir;
    TEST(0u != stlsoft::c_str_len(dir));
}

