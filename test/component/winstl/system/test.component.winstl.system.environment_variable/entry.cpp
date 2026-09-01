/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.system.environment_variable/entry.cpp
 *
 * Purpose: Component-tests for `system/environment_variable`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/system/environment_variable.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_path(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.winstl.system.environment_variable", verbosity))
    {
        XTESTS_RUN_CASE(test_path);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_path(void)
{
    winstl::environment_variable ev("PATH");
    TEST_UINT_NE(0u, ev.length());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
