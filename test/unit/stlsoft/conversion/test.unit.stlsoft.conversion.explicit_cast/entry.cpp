/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.explicit_cast/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/conversion/explicit_cast`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/conversion/explicit_cast.hpp>
#include <string.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_explicit_cast(void);
    static void test_explicit_cast_assignment(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.explicit_cast", verbosity))
    {
        XTESTS_RUN_CASE(test_explicit_cast);
        XTESTS_RUN_CASE(test_explicit_cast_assignment);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_explicit_cast()
{
    stlsoft::explicit_cast<int> c(42);

    TEST_INTEGER_EQUAL(42, static_cast<int>(c));
}

static void test_explicit_cast_assignment()
{
    stlsoft::explicit_cast<int> c(1);
    c = 99;
    TEST_INTEGER_EQUAL(99, static_cast<int>(c));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
