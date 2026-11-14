/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/system/home_directory/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/system/home_directory.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/system/home_directory.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_HOME_DIRECTORY_NON_EMPTY();
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
        XTESTS_RUN_CASE(TEST_HOME_DIRECTORY_NON_EMPTY);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_HOME_DIRECTORY_NON_EMPTY()
{
    unixstl::home_directory_a home;

    TEST_INT_GT(0, home.length());
    TEST_CHAR_EQ('/', home.c_str()[0]);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
