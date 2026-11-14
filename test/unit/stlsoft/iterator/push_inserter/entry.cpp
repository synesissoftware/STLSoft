/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/iterator/push_inserter/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/iterator/push_inserter`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
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


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_PUSH_INSERTER();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_PUSH_INSERTER);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_PUSH_INSERTER()
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
