/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.containers.static_array/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/containers/static_array`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/containers/static_array.hpp>
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

    static void test_static_array_size(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.containers.static_array", verbosity))
    {
        XTESTS_RUN_CASE(test_static_array_size);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_static_array_size()
{
    stlsoft::static_array_1d<int, 5> arr;

    TEST_INTEGER_EQUAL(5, static_cast<int>(arr.size()));
    arr[0] = 99;
    TEST_INTEGER_EQUAL(99, arr[0]);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
