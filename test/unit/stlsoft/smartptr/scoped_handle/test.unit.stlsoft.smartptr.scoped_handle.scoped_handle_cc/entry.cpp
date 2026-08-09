/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.smartptr.scoped_handle.scoped_handle_cc/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/smartptr/scoped_handle/scoped_handle_cc`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/smartptr/scoped_handle/scoped_handle_cc.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_smoke(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.smartptr.scoped_handle.scoped_handle_cc", verbosity))
    {
        XTESTS_RUN_CASE(test_smoke);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_smoke()
{
    TEST_BOOLEAN_TRUE(true);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
