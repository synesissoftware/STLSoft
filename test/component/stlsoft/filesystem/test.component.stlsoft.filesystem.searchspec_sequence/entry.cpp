/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.stlsoft.filesystem.searchspec_sequence/entry.cpp
 *
 * Purpose: Component-tests for `stlsoft/filesystem/searchspec_sequence`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/filesystem/searchspec_sequence.hpp>
#include <stdio.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_filesystem_compile(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.stlsoft.filesystem.searchspec_sequence", verbosity))
    {
        XTESTS_RUN_CASE(test_filesystem_compile);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_filesystem_compile()
{
    TEST_BOOLEAN_TRUE(true);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
