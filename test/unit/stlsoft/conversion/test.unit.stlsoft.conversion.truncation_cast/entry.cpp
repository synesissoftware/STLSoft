/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.truncation_cast/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/conversion/truncation_cast`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/conversion/truncation_cast.hpp>
#include <string.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_truncation_cast_in_range(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.truncation_cast", verbosity))
    {
        XTESTS_RUN_CASE(test_truncation_cast_in_range);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_truncation_cast_in_range()
{
    int const v = stlsoft::truncation_cast<int>(42L);
    TEST_INTEGER_EQUAL(42, v);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
