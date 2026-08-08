/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.iterator.push_inserter/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/iterator/push_inserter`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/iterator/push_inserter.hpp>

#include <vector>
#include <string>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_push_inserter();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.iterator.push_inserter", verbosity))
    {
        XTESTS_RUN_CASE(test_push_inserter);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_push_inserter()
{
    std::vector<int> v;
    std::back_insert_iterator<std::vector<int> > bi(v);
    *bi = 1;
    ++bi;
    *bi = 2;
    TEST_INTEGER_EQUAL(2, static_cast<int>(v.size()));
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
