/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.system.directory_functions/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/system/directory_functions.h`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/system/directory_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_get_home_directory(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.system.directory_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_get_home_directory);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_get_home_directory()
{
    char buf[PATH_MAX];

    size_t const n = unixstl::get_home_directory(buf, STLSOFT_NUM_ELEMENTS(buf));

    TEST_INT_GT(0u, n);
    TEST_CHAR_EQ('/', buf[0]);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
