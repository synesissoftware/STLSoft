/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.diagnostics.systemtime_stopwatch/entry.cpp
 *
 * Purpose: Component-tests for `diagnostics/systemtime_stopwatch`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/diagnostics/systemtime_stopwatch.hpp>
#include <winstl/synch/sleep_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_start_stop(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.winstl.diagnostics.systemtime_stopwatch", verbosity))
    {
        XTESTS_RUN_CASE(test_start_stop);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_start_stop(void)
{
    winstl::systemtime_stopwatch sw;
    sw.start();
    winstl::micro_sleep(1);
    sw.stop();
    TEST_BOOLEAN_TRUE(sw.get_seconds() >= 0.0);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
