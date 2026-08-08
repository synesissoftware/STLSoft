/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.performance.processtimes_counter/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/performance/processtimes_counter.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/performance/processtimes_counter.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_is_processtimes_stopwatch_alias()
{
    unixstl::processtimes_counter pc;

    pc.start();
    volatile unsigned long n = 0;
    for (unsigned i = 0; i != 100000; ++i) { n += i; }
    pc.stop();

    TEST_INT_GE(0, pc.get_user_microseconds());
    STLSOFT_SUPPRESS_UNUSED(n);
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.performance.processtimes_counter", verbosity))
    {
        XTESTS_RUN_CASE(test_is_processtimes_stopwatch_alias);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
