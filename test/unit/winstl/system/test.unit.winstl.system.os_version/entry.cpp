/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.system.os_version/entry.cpp
 *
 * Purpose: Unit-tests for `system/os_version`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/system/os_version.h>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_query(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.system.os_version", verbosity))
    {
        XTESTS_RUN_CASE(test_query);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_query(void)
{
    winstl::os_version obj;
    TEST_UINT_NE(0u, stlsoft::c_str_len(obj));
}
