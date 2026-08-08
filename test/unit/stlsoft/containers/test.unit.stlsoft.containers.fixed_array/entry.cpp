/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.containers.fixed_array/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/containers/fixed_array`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/containers/fixed_array.hpp>

#include <vector>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_fixed_array_1d();

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.containers.fixed_array", verbosity))
    {
        XTESTS_RUN_CASE(test_fixed_array_1d);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {


static void test_fixed_array_1d()
{
    stlsoft::fixed_array_1d<int> arr(4, 7);
    TEST_INTEGER_EQUAL(4, static_cast<int>(arr.size()));
    TEST_INTEGER_EQUAL(7, arr[0]);
    arr[2] = 42;
    TEST_INTEGER_EQUAL(42, arr[2]);
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
