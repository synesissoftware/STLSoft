/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.collections.array_proxy/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/collections/array_proxy`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/collections/array_proxy.hpp>
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

    static void test_array_proxy(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.collections.array_proxy", verbosity))
    {
        XTESTS_RUN_CASE(test_array_proxy);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_array_proxy()
{
    int arr[] = { 5, 6, 7 };
    stlsoft::array_proxy<int> proxy(arr, 3);
    TEST_INTEGER_EQUAL(6, proxy[1]);
    proxy[1] = 99;
    TEST_INTEGER_EQUAL(99, arr[1]);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
