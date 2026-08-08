/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.algorithms.unordered/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/algorithms/unordered`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/algorithms/unordered.hpp>

#include <vector>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_find_first_duplicate();

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.algorithms.unordered", verbosity))
    {
        XTESTS_RUN_CASE(test_find_first_duplicate);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {


static void test_find_first_duplicate()
{
    int arr[] = { 1, 2, 3, 2, 4 };
    std::pair<int*, int*> r = stlsoft::find_first_duplicate(&arr[0], &arr[5]);
    TEST_PTR_EQ(&arr[1], r.first);
    TEST_PTR_EQ(&arr[3], r.second);
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
