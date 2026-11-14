#include <platformstl/filesystem/path_functions.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void TEST_path_squeeze_NULL_BUFFER();

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_path_squeeze_NULL_BUFFER);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void TEST_path_squeeze_NULL_BUFFER()
{
    char const* const input = "abcdef";
    size_t const cch = platformstl::path_squeeze(input, static_cast<char*>(NULL), 0);
    TEST_INT_EQ(7, cch);
}

