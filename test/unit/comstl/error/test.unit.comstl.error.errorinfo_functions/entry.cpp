/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.error.errorinfo_functions/entry.cpp
 *
 * Purpose: Unit-tests for error-info helper functions.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/error/errorinfo_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_set_and_get_error_info(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.error.errorinfo_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_set_and_get_error_info);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_set_and_get_error_info(void)
{
    HRESULT     hr;
    IErrorInfo* pei = NULL;

    hr = comstl::set_error_info(L"unit-test description");
    TEST_BOOLEAN_EQ(1, SUCCEEDED(hr));

    hr = ::GetErrorInfo(0, &pei);
    TEST_BOOLEAN_EQ(1, SUCCEEDED(hr));
    TEST_PTR_NE(NULL, pei);

    if (NULL != pei)
    {
        BSTR description = NULL;

        TEST_INT_EQ((int)S_OK, (int)pei->GetDescription(&description));
        TEST_PTR_NE(NULL, description);
        TEST_INT_EQ(0, ::wcscmp(L"unit-test description", description));

        ::SysFreeString(description);
        pei->Release();
    }

    ::SetErrorInfo(0, NULL);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
