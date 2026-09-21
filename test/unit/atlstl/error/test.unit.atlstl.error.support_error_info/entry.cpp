/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atlstl.error.support_error_info/entry.cpp
 *
 * Purpose: Unit-tests for `atlstl::SupportErrorInfoImpl` and related templates.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <atlstl/error/support_error_info.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <atlbase.h>
#include <objidl.h>
#include <initguid.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_support_error_info_impl1(void);
    static void TEST_support_error_info_impl2(void);
    static void TEST_support_error_info_impl3(void);
    static void TEST_support_error_info_impl4(void);
    static void TEST_support_error_info_impl5(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atlstl.error.support_error_info", verbosity))
    {
        XTESTS_RUN_CASE(TEST_support_error_info_impl1);
        XTESTS_RUN_CASE(TEST_support_error_info_impl2);
        XTESTS_RUN_CASE(TEST_support_error_info_impl3);
        XTESTS_RUN_CASE(TEST_support_error_info_impl4);
        XTESTS_RUN_CASE(TEST_support_error_info_impl5);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_support_error_info_impl1()
{
    support_error_info1 sei;

    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest1));
    TEST_INT_EQ(S_FALSE, sei.InterfaceSupportsErrorInfo(IID_IUnknown));
}

static void TEST_support_error_info_impl2()
{
    support_error_info2 sei;

    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest1));
    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest2));
    TEST_INT_EQ(S_FALSE, sei.InterfaceSupportsErrorInfo(IID_IUnknown));
}

static void TEST_support_error_info_impl3()
{
    support_error_info3 sei;

    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest1));
    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest2));
    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest3));
    TEST_INT_EQ(S_FALSE, sei.InterfaceSupportsErrorInfo(IID_IUnknown));
}

static void TEST_support_error_info_impl4()
{
    support_error_info4 sei;

    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest1));
    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest2));
    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest3));
    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest4));
    TEST_INT_EQ(S_FALSE, sei.InterfaceSupportsErrorInfo(IID_IUnknown));
}

static void TEST_support_error_info_impl5()
{
    support_error_info5 sei;

    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest1));
    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest2));
    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest3));
    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest4));
    TEST_INT_EQ(S_OK, sei.InterfaceSupportsErrorInfo(IID_AtlstlTest5));
    TEST_INT_EQ(S_FALSE, sei.InterfaceSupportsErrorInfo(IID_IUnknown));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
