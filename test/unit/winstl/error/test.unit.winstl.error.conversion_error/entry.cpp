/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.error.conversion_error/entry.cpp
 *
 * Purpose: Unit-tests for `error/conversion_error`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/error/conversion_error.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_throw(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.error.conversion_error", verbosity))
    {
        XTESTS_RUN_CASE_THAT_THROWS(test_throw, winstl::conversion_error);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_throw(void)
{
    throw winstl::conversion_error("test", ERROR_INVALID_PARAMETER);
}
