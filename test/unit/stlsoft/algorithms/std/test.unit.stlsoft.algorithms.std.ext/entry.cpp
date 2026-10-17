/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.algorithms.std.ext/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/algorithms/std/ext`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/algorithms/std/ext.hpp>
#include <vector>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_ext_for_each_if(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.algorithms.std.ext", verbosity))
    {
        XTESTS_RUN_CASE(test_ext_for_each_if);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_ext_for_each_if()
{
    int arr[] = { 1, 2, 3, 4 };
    int sum = 0;
    stlsoft::for_each_if(&arr[0], &arr[4], [&sum](int v) { sum += v; return v; }, [](int v) { return v > 2; });
    TEST_INTEGER_EQUAL(7, sum);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
