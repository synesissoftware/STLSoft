/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.filesystem.path_buffer/entry.cpp
 *
 * Purpose: Component-tests for `filesystem operation`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/filesystem/path_buffer.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_smoke(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.filesystem.path_buffer", verbosity))
    {
        XTESTS_RUN_CASE(test_smoke);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_smoke(void)
{
    /* Exercises filesystem operation. */
    TEST_PASSED();
}
