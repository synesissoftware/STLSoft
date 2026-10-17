/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.error.excepinfo_functions/entry.cpp
 *
 * Purpose: Unit-tests for EXCEPINFO helper functions.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/error/excepinfo_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_EXCEPINFO_free(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.error.excepinfo_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_EXCEPINFO_free);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_EXCEPINFO_free(void)
{
    EXCEPINFO xi;

    memset(&xi, 0, sizeof(xi));
    xi.bstrSource = ::SysAllocString(L"src");
    xi.bstrDescription = ::SysAllocString(L"desc");
    xi.bstrHelpFile = ::SysAllocString(L"help");

    comstl::EXCEPINFO_free(&xi);

    TEST_PTR_EQ(NULL, xi.bstrSource);
    TEST_PTR_EQ(NULL, xi.bstrDescription);
    TEST_PTR_EQ(NULL, xi.bstrHelpFile);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
