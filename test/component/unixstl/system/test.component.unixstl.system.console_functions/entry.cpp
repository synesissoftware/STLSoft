/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.system.console_functions/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/system/console_functions.h`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/system/console_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_get_console_width(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.system.console_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_get_console_width);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_get_console_width()
{
    int const w = unixstl::get_console_width();

    if (w >= 0)
    {
        TEST_INT_GT(0, w);
    }
    else
    {
        /* No controlling terminal in this environment. */
        TEST_PASSED();
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
