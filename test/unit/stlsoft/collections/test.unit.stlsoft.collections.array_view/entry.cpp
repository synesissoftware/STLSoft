/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.collections.array_view/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/collections/array_view`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/collections/array_view.hpp>

#include <vector>
#include <string>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_array_view();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.collections.array_view", verbosity))
    {
        XTESTS_RUN_CASE(test_array_view);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_array_view()
{
    int arr[] = { 1, 2, 3 };
    stlsoft::array_view<int> view(arr, 3);
    TEST_INTEGER_EQUAL(3, static_cast<int>(view.size()));
    TEST_INTEGER_EQUAL(2, view[1]);
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
