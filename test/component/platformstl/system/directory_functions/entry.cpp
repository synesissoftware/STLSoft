#include <platformstl/system/directory_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void TEST_get_home_directory();

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_get_home_directory);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void TEST_get_home_directory()
{
    char buff[1001];
    size_t const required = platformstl::platformstl_C_get_home_directory_a(static_cast<char*>(NULL), 0);

    if (0 != required)
    {
        size_t const cch = platformstl::platformstl_C_get_home_directory_a(buff, STLSOFT_NUM_ELEMENTS(buff));
        TEST(0u < cch);
        TEST('\0' != buff[0]);
    }
}
