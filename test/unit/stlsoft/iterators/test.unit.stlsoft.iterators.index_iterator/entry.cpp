/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.iterators.index_iterator/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/iterators/index_iterator`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/iterators/index_iterator.hpp>

#include <vector>
#include <string>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_index_iterator();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.iterators.index_iterator", verbosity))
    {
        XTESTS_RUN_CASE(test_index_iterator);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_index_iterator()
{
    int arr[] = { 10, 20, 30 };

    stlsoft::index_iterator<int*> it(&arr[0], 0);

    TEST_INTEGER_EQUAL(10, *it);
    TEST_INTEGER_EQUAL(0, it.index());

    ++it;

    TEST_INTEGER_EQUAL(20, *it);
    TEST_INTEGER_EQUAL(1, it.index());
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
