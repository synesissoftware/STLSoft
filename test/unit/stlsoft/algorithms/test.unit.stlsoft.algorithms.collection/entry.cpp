/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.algorithms.collection/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/algorithms/collection`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/algorithms/collection.hpp>

#include <vector>
#include <string>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_collection_algorithms_compile();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.algorithms.collection", verbosity))
    {
        XTESTS_RUN_CASE(test_collection_algorithms_compile);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_collection_algorithms_compile()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    TEST_INTEGER_EQUAL(2, static_cast<int>(v.size()));
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
