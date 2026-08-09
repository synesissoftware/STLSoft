/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.stlsoft.system.environment.functions/entry.cpp
 *
 * Purpose: Component-tests for `stlsoft/system/environment/functions`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/system/environment/functions.hpp>
#include <stlsoft/system/environment/functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_environment_variable_exists(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.stlsoft.system.environment.functions", verbosity))
    {
        XTESTS_RUN_CASE(test_environment_variable_exists);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_environment_variable_exists()
{
    TEST_BOOLEAN_TRUE(0 != stlsoft::stlsoft_C_environment_variable_exists_a("PATH"));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
