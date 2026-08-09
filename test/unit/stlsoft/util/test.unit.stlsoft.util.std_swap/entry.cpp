/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.std_swap/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/util/std_swap`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/util/std_swap.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_std_swap(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.std_swap", verbosity))
    {
        XTESTS_RUN_CASE(test_std_swap);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_std_swap()
{
    int a = 1;
    int b = 2;
    stlsoft::std_swap(a, b);
    TEST_INTEGER_EQUAL(2, a);
    TEST_INTEGER_EQUAL(1, b);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
