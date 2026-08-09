/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.filesystem.absolute_path/entry.cpp
 *
 * Purpose: Component-tests for `filesystem/absolute_path`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/filesystem/absolute_path.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_absolute(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.filesystem.absolute_path", verbosity))
    {
        XTESTS_RUN_CASE(test_absolute);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_absolute(void)
{
    winstl::absolute_path ap(".");

    TEST_UINT_NE(0u, ap.length());
}
