/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/diagnostics/processtimes_stopwatch/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/diagnostics/processtimes_stopwatch.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/diagnostics/processtimes_stopwatch.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_PROCESS_TIME_INCREASES_WITH_WORK();
    static void TEST_TOTAL_IS_SUM_OF_USER_AND_KERNEL();
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
        XTESTS_RUN_CASE(TEST_PROCESS_TIME_INCREASES_WITH_WORK);
        XTESTS_RUN_CASE(TEST_TOTAL_IS_SUM_OF_USER_AND_KERNEL);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_PROCESS_TIME_INCREASES_WITH_WORK()
{
    unixstl::processtimes_stopwatch sw;

    sw.start();

    volatile unsigned long n = 0;
    for (unsigned i = 0; i != 1000000; ++i)
    {
        n += i;
    }

    sw.stop();

    TEST_INT_GE(0, sw.get_user_microseconds());
    TEST_INT_GE(0, sw.get_kernel_microseconds());
    TEST_INT_GE(0, sw.get_microseconds());
    STLSOFT_SUPPRESS_UNUSED(n);
}

static void TEST_TOTAL_IS_SUM_OF_USER_AND_KERNEL()
{
    unixstl::processtimes_stopwatch sw;

    sw.start();
    volatile unsigned long n = 0;
    for (unsigned i = 0; i != 500000; ++i) { n += i; }
    sw.stop();

    unixstl::processtimes_stopwatch::interval_type const total = sw.get_period_count();
    unixstl::processtimes_stopwatch::interval_type const sum =
        sw.get_user_period_count() + sw.get_kernel_period_count();

    TEST_INT_EQ(sum, total);
    STLSOFT_SUPPRESS_UNUSED(n);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
