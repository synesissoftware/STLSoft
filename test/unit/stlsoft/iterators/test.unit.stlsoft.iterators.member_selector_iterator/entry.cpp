/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.iterators.member_selector_iterator/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/iterators/member_selector_iterator`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/iterators/member_selector_iterator.hpp>

#include <vector>
#include <string>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_iterator_compile();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.iterators.member_selector_iterator", verbosity))
    {
        XTESTS_RUN_CASE(test_iterator_compile);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_iterator_compile()
{
    std::vector<int> v;
    v.push_back(1);
    TEST_INTEGER_EQUAL(1, v[0]);
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
