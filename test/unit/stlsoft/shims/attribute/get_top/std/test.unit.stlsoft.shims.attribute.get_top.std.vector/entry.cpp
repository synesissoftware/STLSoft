/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.shims.attribute.get_top.std.vector/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/shims/attribute/get_top/std/vector`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/shims/attribute/get_top/std/vector.hpp>

#include <stlsoft/shims/access/string.hpp>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_get_top_vector();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.shims.attribute.get_top.std.vector", verbosity))
    {
        XTESTS_RUN_CASE(test_get_top_vector);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_get_top_vector()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    TEST_INTEGER_EQUAL(1, stlsoft::get_top(v));
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
