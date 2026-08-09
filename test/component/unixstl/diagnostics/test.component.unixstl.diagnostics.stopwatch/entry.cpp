/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.diagnostics.stopwatch/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/diagnostics/stopwatch.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
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

    static void test_static_interval_helpers(void);
    static void test_start_stop_elapsed(void);
    static void test_pause_unpause(void);
    static void test_restart_and_stop_get(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.diagnostics.stopwatch", verbosity))
    {
        XTESTS_RUN_CASE(test_static_interval_helpers);
        XTESTS_RUN_CASE(test_start_stop_elapsed);
        XTESTS_RUN_CASE(test_pause_unpause);
        XTESTS_RUN_CASE(test_restart_and_stop_get);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_static_interval_helpers()
{
    unixstl::stopwatch::epoch_type start = { 10, 0 };
    unixstl::stopwatch::epoch_type end   = { 12, 500000 };

    TEST_INT_EQ(2, unixstl::stopwatch::get_seconds(start, end));
    TEST_INT_EQ(2500, unixstl::stopwatch::get_milliseconds(start, end));
    TEST_INT_EQ(2500000, unixstl::stopwatch::get_microseconds(start, end));
}

static void test_start_stop_elapsed()
{
    unixstl::stopwatch sw;

    sw.start();
    ::usleep(50000);
    sw.stop();

    TEST_INT_GE(0, sw.get_seconds());
    TEST_INT_GE(40000, sw.get_microseconds());
}

static void test_pause_unpause()
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

    TEST_INT_GE(30000, us);
    TEST_INT_LT(90000, us);
}

static void test_restart_and_stop_get()
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
