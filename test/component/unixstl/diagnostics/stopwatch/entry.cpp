/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/diagnostics/stopwatch/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/diagnostics/stopwatch.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/diagnostics/stopwatch.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_STATIC_INTERVAL_HELPERS();
    static void TEST_START_STOP_ELAPSED();
    static void TEST_PAUSE_UNPAUSE();
    static void TEST_RESTART_AND_STOP_GET();
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
        XTESTS_RUN_CASE(TEST_STATIC_INTERVAL_HELPERS);
        XTESTS_RUN_CASE(TEST_START_STOP_ELAPSED);
        XTESTS_RUN_CASE(TEST_PAUSE_UNPAUSE);
        XTESTS_RUN_CASE(TEST_RESTART_AND_STOP_GET);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_STATIC_INTERVAL_HELPERS()
{
    unixstl::stopwatch::epoch_type start = { 10, 0 };
    unixstl::stopwatch::epoch_type end   = { 12, 500000 };

    TEST_INT_EQ(2, unixstl::stopwatch::get_seconds(start, end));
    TEST_INT_EQ(2500, unixstl::stopwatch::get_milliseconds(start, end));
    TEST_INT_EQ(2500000, unixstl::stopwatch::get_microseconds(start, end));
}

static void TEST_START_STOP_ELAPSED()
{
    unixstl::stopwatch sw;

    sw.start();
    ::usleep(50000);
    sw.stop();

    TEST_INT_GE(0, sw.get_seconds());
    TEST_INT_GE(40000, sw.get_microseconds());
}

static void TEST_PAUSE_UNPAUSE()
{
    unixstl::stopwatch sw;

    sw.start();
    ::usleep(20000);
    sw.pause();
    ::usleep(50000);
    sw.unpause();
    ::usleep(20000);
    sw.stop();

    unixstl::stopwatch::interval_type const us = sw.get_microseconds();

    /* Active sleeps are 20ms + 20ms. The ceiling is a runaway guard:
     * hosted runners inflate short usleep()s well past 90ms.
     */
    TEST_INT_GE(30000, us);
    TEST_INT_LT(1000000, us);
}

static void TEST_RESTART_AND_STOP_GET()
{
    unixstl::stopwatch sw;

    sw.start();
    ::usleep(10000);
    sw.stop();

    unixstl::stopwatch::interval_type const first = sw.stop_get_microseconds_and_restart();

    TEST_INT_GE(5000, first);

    ::usleep(10000);
    sw.stop();

    TEST_INT_GE(5000, sw.get_microseconds());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
