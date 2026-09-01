#include <platformstl/filesystem/path_functions.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_path_squeeze_null_buffer(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.path_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_path_squeeze_null_buffer);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_path_squeeze_null_buffer(void)
{
    char const* const input = "abcdef";
    size_t const cch = platformstl::path_squeeze(input, static_cast<char*>(NULL), 0);
    TEST_INT_EQ(7, cch);
}

