/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.iterators.null_output_iterator/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/iterators/null_output_iterator`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/iterators/null_output_iterator.hpp>
#include <vector>
#include <string>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_null_output_iterator(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.iterators.null_output_iterator", verbosity))
    {
        XTESTS_RUN_CASE(test_null_output_iterator);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_null_output_iterator()
{
    stlsoft::null_output_iterator<int> it;
    *it = 42;
    ++it;
    TEST_BOOLEAN_TRUE(true);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
