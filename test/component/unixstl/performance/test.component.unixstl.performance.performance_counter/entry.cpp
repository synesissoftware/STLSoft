/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.performance.performance_counter/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/performance/performance_counter.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/performance/performance_counter.hpp>
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

    static void test_is_stopwatch_alias(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.performance.performance_counter", verbosity))
    {
        XTESTS_RUN_CASE(test_is_stopwatch_alias);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_is_stopwatch_alias()
{
    unixstl::performance_counter pc;

    pc.start();
    ::usleep(10000);
    pc.stop();

    TEST_INT_GE(0, pc.get_microseconds());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
