/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.smartptr.scoped_lambda/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/smartptr/scoped_lambda`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/smartptr/scoped_lambda.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_scoped_lambda(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.smartptr.scoped_lambda", verbosity))
    {
        XTESTS_RUN_CASE(test_scoped_lambda);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_scoped_lambda()
{
    int flag = 0;
    {
        stlsoft::scoped_lambda sl([&flag]() { flag = 1; });
    }
    TEST_INTEGER_EQUAL(1, flag);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
