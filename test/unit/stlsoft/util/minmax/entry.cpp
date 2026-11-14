/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/util/minmax/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/util/minmax`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/util/minmax.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_MINIMUM();
    static void TEST_MAXIMUM();
    static void TEST_MINIMUM_THREE();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_MINIMUM);
        XTESTS_RUN_CASE(TEST_MAXIMUM);
        XTESTS_RUN_CASE(TEST_MINIMUM_THREE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_MINIMUM()
{
    TEST_INTEGER_EQUAL(1, stlsoft::minimum(1, 2));
    TEST_INTEGER_EQUAL(1, stlsoft::minimum(2, 1));
}

static void TEST_MAXIMUM()
{
    TEST_INTEGER_EQUAL(2, stlsoft::maximum(1, 2));
    TEST_INTEGER_EQUAL(2, stlsoft::maximum(2, 1));
}

static void TEST_MINIMUM_THREE()
{
    TEST_INTEGER_EQUAL(1, stlsoft::minimum(3, 1, 2));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
