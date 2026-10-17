/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.system.version_info/entry.cpp
 *
 * Purpose: Unit-tests for `system/version_info`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/system/version_info.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_query(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.system.version_info", verbosity))
    {
        XTESTS_RUN_CASE(test_query);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_query(void)
{
    winstl::version_info const vi("kernel32.dll");

    TEST_UINT_NE(0u, vi.Length());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
