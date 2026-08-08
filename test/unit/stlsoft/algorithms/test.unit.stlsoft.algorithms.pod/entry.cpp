/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.algorithms.pod/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/algorithms/pod`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/algorithms/pod.hpp>

#include <vector>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_pod_copy();

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.algorithms.pod", verbosity))
    {
        XTESTS_RUN_CASE(test_pod_copy);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {


static void test_pod_copy()
{
    int src[] = { 10, 20, 30 };
    int dest[3] = {};
    stlsoft::pod_copy(&src[0], &src[3], &dest[0]);
    TEST_INTEGER_EQUAL(10, dest[0]);
    TEST_INTEGER_EQUAL(20, dest[1]);
    TEST_INTEGER_EQUAL(30, dest[2]);
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
