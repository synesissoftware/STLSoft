/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.shims.logical.is_empty/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/shims/logical/is_empty`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/shims/logical/is_empty.hpp>

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

static void test_is_empty_vector();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.shims.logical.is_empty", verbosity))
    {
        XTESTS_RUN_CASE(test_is_empty_vector);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_is_empty_vector()
{
    std::vector<int> empty;
    std::vector<int> nonempty(1);
    TEST_BOOLEAN_TRUE(stlsoft::is_empty(empty));
    TEST_BOOLEAN_FALSE(stlsoft::is_empty(nonempty));
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
