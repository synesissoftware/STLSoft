/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.error.last_error_scope/entry.cpp
 *
 * Purpose: Unit-tests for `error/last_error_scope`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/error/last_error_scope.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_preserves_error(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.error.last_error_scope", verbosity))
    {
        XTESTS_RUN_CASE(test_preserves_error);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_preserves_error(void)
{
    ::SetLastError(ERROR_ACCESS_DENIED);
    {
        winstl::last_error_scope scope;
        ::SetLastError(ERROR_SUCCESS);
    }
    TEST_INT_EQ(ERROR_ACCESS_DENIED, static_cast<int>(::GetLastError()));
}
