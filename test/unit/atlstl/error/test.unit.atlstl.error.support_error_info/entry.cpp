/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atlstl.error.support_error_info/entry.cpp
 *
 * Purpose: Unit-tests for `atlstl::SupportErrorInfoImpl` and related templates.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <atlstl/error/support_error_info.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* ATL / COM header files */
#include <atlbase.h>
#include <objidl.h>

/* Standard C header files */
#include <initguid.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * test IIDs
 */

// {A1B2C3D4-E5F6-7890-ABCD-EF1234567890}
DEFINE_GUID(IID_AtlstlTest1, 0xa1b2c3d4, 0xe5f6, 0x7890, 0xab, 0xcd, 0xef, 0x12, 0x34, 0x56, 0x78, 0x90);
// {B2C3D4E5-F6A7-8901-BCDE-F12345678901}
DEFINE_GUID(IID_AtlstlTest2, 0xb2c3d4e5, 0xf6a7, 0x8901, 0xbc, 0xde, 0xf1, 0x23, 0x45, 0x67, 0x89, 0x01);
// {C3D4E5F6-A7B8-9012-CDEF-123456789012}
DEFINE_GUID(IID_AtlstlTest3, 0xc3d4e5f6, 0xa7b8, 0x9012, 0xcd, 0xef, 0x12, 0x34, 0x56, 0x78, 0x90, 0x12);
// {D4E5F6A7-B8C9-0123-DEF0-234567890123}
DEFINE_GUID(IID_AtlstlTest4, 0xd4e5f6a7, 0xb8c9, 0x0123, 0xde, 0xf0, 0x23, 0x45, 0x67, 0x89, 0x01, 0x23);
// {E5F6A7B8-C9D0-1234-EF01-345678901234}
DEFINE_GUID(IID_AtlstlTest5, 0xe5f6a7b8, 0xc9d0, 0x1234, 0xef, 0x01, 0x34, 0x56, 0x78, 0x90, 0x12, 0x34);


/* /////////////////////////////////////////////////////////////////////////
 * test types
 */

namespace {

class support_error_info1
    : public atlstl::SupportErrorInfoImpl<&IID_AtlstlTest1>
{};

class support_error_info2
    : public atlstl::SupportErrorInfoImpl2<&IID_AtlstlTest1, &IID_AtlstlTest2>
{};

class support_error_info3
    : public atlstl::SupportErrorInfoImpl3<&IID_AtlstlTest1, &IID_AtlstlTest2, &IID_AtlstlTest3>
{};

class support_error_info4
    : public atlstl::SupportErrorInfoImpl4<&IID_AtlstlTest1, &IID_AtlstlTest2, &IID_AtlstlTest3, &IID_AtlstlTest4>
{};

class support_error_info5
    : public atlstl::SupportErrorInfoImpl5<&IID_AtlstlTest1, &IID_AtlstlTest2, &IID_AtlstlTest3, &IID_AtlstlTest4, &IID_AtlstlTest5>
{};

} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_support_error_info_impl1();
    static void TEST_support_error_info_impl2();
    static void TEST_support_error_info_impl3();
    static void TEST_support_error_info_impl4();
    static void TEST_support_error_info_impl5();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atlstl.error.support_error_info", verbosity))
    {
        HRESULT const hrCoInit = ::CoInitialize(NULL);

        if (SUCCEEDED(hrCoInit))
        {
            XTESTS_RUN_CASE(TEST_support_error_info_impl1);
            XTESTS_RUN_CASE(TEST_support_error_info_impl2);
            XTESTS_RUN_CASE(TEST_support_error_info_impl3);
            XTESTS_RUN_CASE(TEST_support_error_info_impl4);
            XTESTS_RUN_CASE(TEST_support_error_info_impl5);

            ::CoUninitialize();
        }
        else
        {
            XTESTS_TEST_FAIL("CoInitialize() failed");
        }

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
