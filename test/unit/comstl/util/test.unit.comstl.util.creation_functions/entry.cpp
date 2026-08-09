/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.creation_functions/entry.cpp
 *
 * Purpose: Unit-tests for COM instance creation helpers.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/util/creation_functions.hpp>
#include <comstl/util/initialisers.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_co_create_instance_filesystem_object(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.util.creation_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_co_create_instance_filesystem_object);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_co_create_instance_filesystem_object(void)
{
    IDispatch*  pdisp = NULL;
    HRESULT     hr    = comstl::co_create_instance(L"Scripting.FileSystemObject", &pdisp);

    TEST_BOOLEAN_EQ(1, SUCCEEDED(hr));
    TEST_PTR_NE(NULL, pdisp);

    if (NULL != pdisp)
    {
        pdisp->Release();
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
