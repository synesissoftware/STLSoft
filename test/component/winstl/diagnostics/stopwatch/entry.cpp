/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/winstl/diagnostics/stopwatch/entry.cpp
 *
 * Purpose: Component-tests for `diagnostics/stopwatch`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/diagnostics/stopwatch.hpp>
#include <winstl/synch/sleep_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_START_STOP();
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
        XTESTS_RUN_CASE(TEST_START_STOP);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_START_STOP()
{
    winstl::stopwatch sw;
    sw.start();
    winstl::micro_sleep(1);
    sw.stop();
    TEST_BOOLEAN_TRUE(sw.get_seconds() >= 0.0);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
