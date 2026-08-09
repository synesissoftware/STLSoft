/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.dl.dl_call/entry.cpp
 *
 * Purpose: Component test for `winstl::dl_call`.
 *
 * Created: 9th October 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* ///////////////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/dl/dl_call.hpp>

/* ///////////////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <winstl/system/system_directory.hpp>
#include <winstl/util/struct_comparers.hpp>

/* Standard C++ header files */
#if __cplusplus >= 201103L
# include <atomic>
#endif
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    // 0 parameters
    static void test_Kernel32_GetTickCount();
    static void test_Kernel32_GetTickCount64();

    // 1 parameter
    static void test_Kernel32_GetSystemInfo();

    // 2 parameters
    static void test_Kernel32_GetSystemDirectory();

    // 3 parameters
    static void test_GetSystemTimeAdjustmentPrecise();

    // 4 parameters
    static void test_SystemParametersInfo();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.winstl.dl.dl_call", verbosity))
    {
        XTESTS_RUN_CASE(test_Kernel32_GetTickCount);
        XTESTS_RUN_CASE(test_Kernel32_GetTickCount64);

        XTESTS_RUN_CASE(test_Kernel32_GetSystemInfo);

        XTESTS_RUN_CASE(test_Kernel32_GetSystemDirectory);

        XTESTS_RUN_CASE(test_GetSystemTimeAdjustmentPrecise);

        XTESTS_RUN_CASE(test_SystemParametersInfo);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    inline
    void
    full_fence()
    {
#if __cplusplus >= 201103L

        std::atomic_thread_fence(std::memory_order_seq_cst);
#else

# if 0
# elif defined(_WIN32_WINNT) && \
       _WIN32_WINNT > 0x0502

        ::MemoryBarrier();
# else

        /* no barrier implementation */
# endif
#endif
    }

static void test_Kernel32_GetTickCount()
{
    try
    {
        DWORD const tc_before = ::GetTickCount();

        full_fence();

        DWORD const tc_dl = winstl::dl_call<DWORD>("Kernel32.dll", WINSTL_DL_CALL_WINx_STDCALL_LITERAL("GetTickCount"));

        full_fence();

        DWORD const tc_after = ::GetTickCount();

        TEST_INT_GE(tc_before, tc_dl);
        TEST_INT_LE(tc_after, tc_dl);
    }
    catch (winstl::missing_entry_point_exception& x)
    {
        TEST_FAIL_WITH_QUALIFIER("failed to load function", x.what());
    }
}

static void test_Kernel32_GetTickCount64()
{
    try
    {
        ULONGLONG const tc_before = ::GetTickCount64();

        full_fence();

        ULONGLONG const tc_dl = winstl::dl_call<ULONGLONG>("Kernel32.dll", WINSTL_DL_CALL_WINx_STDCALL_LITERAL("GetTickCount64"));

        full_fence();

        ULONGLONG const tc_after = ::GetTickCount64();

        TEST_INT_GE(tc_before, tc_dl);
        TEST_INT_LE(tc_after, tc_dl);
    }
    catch (winstl::missing_entry_point_exception& x)
    {
        TEST_FAIL_WITH_QUALIFIER("failed to load function", x.what());
    }
}

static void test_Kernel32_GetSystemInfo()
{
    try
    {
        SYSTEM_INFO s1;
        SYSTEM_INFO s2;

        ::GetSystemInfo(&s1);

        winstl::dl_call<void>("Kernel32.dll", WINSTL_DL_CALL_WINx_STDCALL_LITERAL("GetSystemInfo"), &s2);

        TEST_BOOLEAN_TRUE(winstl::equal_struct(s1, s2));
    }
    catch (winstl::missing_entry_point_exception& x)
    {
        TEST_FAIL_WITH_QUALIFIER("failed to load function", x.what());
    }
}

static void test_Kernel32_GetSystemDirectory()
{
    try
    {
        winstl::system_directory    d1;
        CHAR                        d2[_MAX_PATH];

        winstl::dl_call<UINT>(
            "Kernel32.dll"
        ,   WINSTL_DL_CALL_WINx_STDCALL_LITERAL("GetSystemDirectoryA")
        ,   &d2[0]
        ,   static_cast<UINT>(STLSOFT_NUM_ELEMENTS(d2))
        );

        TEST_MS_EQ(d1, d2);
    }
    catch (winstl::missing_entry_point_exception& x)
    {
        TEST_FAIL_WITH_QUALIFIER("failed to load function", x.what());
    }
}

static void test_GetSystemTimeAdjustmentPrecise()
{
    try
    {
        DWORD64 timeAdjustment;
        DWORD64 timeIncrement;
        BOOL    timeAdjustmentDisabled;

        BOOL const r = winstl::dl_call<BOOL>(
            "api-ms-win-core-version-l1-1-0.dll"
        ,   WINSTL_DL_CALL_WINx_STDCALL_LITERAL("GetSystemTimeAdjustmentPrecise")
        ,   &timeAdjustment
        ,   &timeIncrement
        ,   &timeAdjustmentDisabled
        );

        TEST_BOOLEAN_TRUE(r);
    }
    catch (winstl::missing_entry_point_exception& x)
    {
        TEST_FAIL_WITH_QUALIFIER("failed to load function", x.what());
    }
    catch (winstl::winstl_exception& /* x */)
    {}
}

static void test_SystemParametersInfo()
{
    try
    {
        RECT    rc = { -1, -1, -1, -1 };

        BOOL const r = winstl::dl_call<BOOL>(
            "User32.dll"
        ,   WINSTL_DL_CALL_WINx_STDCALL_LITERAL("SystemParametersInfoA")
        ,   SPI_GETWORKAREA
        ,   0
        ,   &rc
        ,   0
        );

        if (r)
        {
            TEST(rc.bottom != -1 || rc.top != -1 || rc.left != -1 || rc.right != -1);
        }
    }
    catch (winstl::missing_entry_point_exception& x)
    {
        TEST_FAIL_WITH_QUALIFIER("failed to load function", x.what());
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

