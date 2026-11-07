#include <platformstl/system/environment_variable.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_path(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(test_path);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_path(void)
{
#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif
    char const* const path = ::getenv("PATH");
#if defined(_MSC_VER)
# pragma warning(pop)
#endif
    if (NULL != path)
    {
        platformstl::environment_variable_a ev_PATH("PATH");
        TEST_MS_EQ(path, ev_PATH);
    }
}

