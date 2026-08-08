/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.diagnostics.processtimes_stopwatch/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/diagnostics/processtimes_stopwatch.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/diagnostics/processtimes_stopwatch.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_process_time_increases_with_work()
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

static void test_total_is_sum_of_user_and_kernel()
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


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.diagnostics.processtimes_stopwatch", verbosity))
    {
        XTESTS_RUN_CASE(test_process_time_increases_with_work);
        XTESTS_RUN_CASE(test_total_is_sum_of_user_and_kernel);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
