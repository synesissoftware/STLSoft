/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/winstl/error/last_error_scope/entry.cpp
 *
 * Purpose: Unit-tests for `error/last_error_scope`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/error/last_error_scope.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_PRESERVES_ERROR();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_PRESERVES_ERROR);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_PRESERVES_ERROR()
{
    ::SetLastError(ERROR_ACCESS_DENIED);
    {
        winstl::last_error_scope scope;
        ::SetLastError(ERROR_SUCCESS);
    }
    TEST_INT_EQ(ERROR_ACCESS_DENIED, static_cast<int>(::GetLastError()));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
