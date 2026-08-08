/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.containers.unsorted_map/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/containers/unsorted_map`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/containers/unsorted_map.hpp>

#include <vector>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_unsorted_map_push_back();

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.containers.unsorted_map", verbosity))
    {
        XTESTS_RUN_CASE(test_unsorted_map_push_back);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {


static void test_unsorted_map_push_back()
{
    stlsoft::unsorted_map<int, int> m;
    m.push_back(1, 10);
    m.push_back(2, 20);
    TEST_INTEGER_EQUAL(2, static_cast<int>(m.size()));
    TEST_INTEGER_EQUAL(10, m[0].second);
    TEST_INTEGER_EQUAL(20, m[1].second);
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
