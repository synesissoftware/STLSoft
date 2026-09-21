/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.system.console_functions/entry.cpp
 *
 * Purpose: Unit-tests for `system/console_functions`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/system/console_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_memory_status(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.system.console_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_memory_status);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_memory_status(void)
{
    MEMORYSTATUSEX ms = { sizeof(MEMORYSTATUSEX) };
    TEST_BOOLEAN_TRUE(::GlobalMemoryStatusEx(&ms));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
