/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.performance.highperformance_counter/entry.cpp
 *
 * Purpose: Unit-tests for `performance/highperformance_counter`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/performance/highperformance_counter.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_query(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.performance.highperformance_counter", verbosity))
    {
        XTESTS_RUN_CASE(test_query);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_query(void)
{
    winstl::highperformance_counter c;
    TEST_BOOLEAN_TRUE(c.get_seconds() >= 0.0);
}
