#include <platformstl/filesystem/path_buffer.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_default_construct(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.path_buffer", verbosity))
    {
        XTESTS_RUN_CASE(test_default_construct);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_default_construct(void)
{
    platformstl::path_buffer_a buf;
    STLSOFT_SUPPRESS_UNUSED(buf);
    TEST_PASSED();
}
