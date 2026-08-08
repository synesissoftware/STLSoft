/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.shims.attribute.get_top.std.stack/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/shims/attribute/get_top/std/stack`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/shims/attribute/get_top/std/stack.hpp>

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

static void test_get_top_stack();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.shims.attribute.get_top.std.stack", verbosity))
    {
        XTESTS_RUN_CASE(test_get_top_stack);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_get_top_stack()
{
    std::stack<int> s;
    s.push(10);
    s.push(20);
    TEST_INTEGER_EQUAL(20, stlsoft::get_top(s));
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
