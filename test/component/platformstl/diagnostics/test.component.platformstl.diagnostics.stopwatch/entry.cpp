/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.platformstl.diagnostics.stopwatch/entry.cpp
 *
 * Purpose: Unit-tests for `platformstl::stopwatch`.
 *
 * Created: 19th November 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <platformstl/diagnostics/stopwatch.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/conversion/sas_to_string.hpp>
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_default_ctor();
    static void test_start_then_stop_immediately();
    static void test_get_epoch_twice();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.platformstl.diagnostics.stopwatch", verbosity))
    {
        XTESTS_RUN_CASE(test_default_ctor);
        XTESTS_RUN_CASE(test_start_then_stop_immediately);
        XTESTS_RUN_CASE(test_get_epoch_twice);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

    using platformstl::stopwatch;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_default_ctor()
{
    stopwatch sw;
}

static void test_start_then_stop_immediately()
{
    stopwatch sw;

    sw.start();
    sw.stop();

    stopwatch::interval_type const  num_s   =   sw.get_seconds();
    stopwatch::interval_type const  num_ms  =   sw.get_milliseconds();
    stopwatch::interval_type const  num_us  =   sw.get_microseconds();
    stopwatch::interval_type const  num_ns  =   sw.get_nanoseconds();

    // in-principle, the elapsed time is 0, but in practice will be a very
    // small number of microseconds, but because of rollover we _might_ get
    // a second

    TEST_INT_LE(1, num_s);
    TEST_INT_LE(1000, num_ms);
    TEST_INT_LE(1000000, num_us);

#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

    // we _know_ that the implementation of `unixstl::stopwatch` has a
    // granularity of us, so ns will be an exact multiple

    TEST_INT_EQ(num_us * 1000, num_ns);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    // we _know_ that the implementation of `winstl::stopwatch` has a
    // granularity of 100ns

    TEST_INT_EQ(num_us, num_ns / 1000);
#endif
}

static void test_get_epoch_twice()
{
    stopwatch::epoch_type e1 = stopwatch::get_epoch();
    stopwatch::epoch_type e2 = stopwatch::get_epoch();

    stopwatch::interval_type const  num_s   =   stopwatch::get_seconds(e1, e2);
    stopwatch::interval_type const  num_ms  =   stopwatch::get_milliseconds(e1, e2);
    stopwatch::interval_type const  num_us  =   stopwatch::get_microseconds(e1, e2);
    stopwatch::interval_type const  num_ns  =   stopwatch::get_nanoseconds(e1, e2);

    // in-principle, the elapsed time is 0, but in practice will be a very
    // small number of microseconds, but because of rollover we _might_ get
    // a second

    TEST_INT_LE(1, num_s);
    TEST_INT_LE(1000, num_ms);
    TEST_INT_LE(1000000, num_us);

#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

    // we _know_ that the implementation of `unixstl::stopwatch` has a
    // granularity of us, so ns will be an exact multiple

    TEST_INT_EQ(num_us * 1000, num_ns);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    // we _know_ that the implementation of `winstl::stopwatch` has a
    // granularity of 100ns

    TEST_INT_EQ(num_us, num_ns / 1000);
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

