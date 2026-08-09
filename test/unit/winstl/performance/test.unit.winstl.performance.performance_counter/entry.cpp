/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.performance.performance_counter/entry.cpp
 *
 * Purpose: Unit-tests for `performance/performance_counter`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/performance/performance_counter.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_query(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.performance.performance_counter", verbosity))
    {
        XTESTS_RUN_CASE(test_query);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_query(void)
{
    winstl::performance_counter c;

    c.start();
    c.stop();

    TEST_INT_GE(0, c.get_seconds());
    TEST_INT_GE(0, c.get_microseconds());
}
