/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.synch.sleep_functions/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/synch/sleep_functions.h`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/synch/sleep_functions.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


#include <sys/time.h>

static void test_micro_sleep_returns()
{
    struct timeval start;
    struct timeval end;

    ::gettimeofday(&start, NULL);
    unixstl::micro_sleep(50000);
    ::gettimeofday(&end, NULL);

    long const elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;

    TEST_INT_GE(30, elapsed_ms);
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.synch.sleep_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_micro_sleep_returns);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
