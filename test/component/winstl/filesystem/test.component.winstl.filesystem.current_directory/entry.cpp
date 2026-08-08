/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.filesystem.current_directory/entry.cpp
 *
 * Purpose: Component-tests for `filesystem/current_directory`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/filesystem/current_directory.hpp>
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
    if (XTESTS_START_RUNNER("test.component.winstl.filesystem.current_directory", verbosity))
    {
        XTESTS_RUN_CASE(test_non_empty);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_non_empty(void)
{
    winstl::current_directory cd;
    TEST_UINT_NE(0u, stlsoft::c_str_len(cd));
}
