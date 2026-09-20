/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.util.struct_initialisers/entry.cpp
 *
 * Purpose: Component test for `winstl::struct_initialisers`.
 *
 * Created: 9th October 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/util/struct_initialisers.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    // no_init_member_type
    static void test_FILETIME();
    static void test_SYSTEM_INFO();
    static void test_SYSTEMTIME();

    // cbSize_member_type
    static void test_CONSOLE_SCREEN_BUFFER_INFOEX();

    // cb_member_type
    static void test_STARTUPINFOW();

    // cBytes_member_type
    static void test_OFSTRUCT();

    // dwLength_member_type
    static void test_MEMORYSTATUS();

    // dwOSVersionInfoSize_member_type
    static void test_OSVERSIONINFOA();
    static void test_OSVERSIONINFOEXA();

    // dwSize_member_type
    static void test_COMMCONFIG();

    // nLength_member_type
    static void test_SECURITY_ATTRIBUTES();

    // uSize_member_type
    static void test_DRAGINFOA();

    // DCBlength
    static void test_DCB();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.util.struct_initialisers", verbosity))
    {
        // no_init_member_type
        XTESTS_RUN_CASE(test_FILETIME);
        XTESTS_RUN_CASE(test_SYSTEM_INFO);
        XTESTS_RUN_CASE(test_SYSTEMTIME);

        // cbSize_member_type
        XTESTS_RUN_CASE(test_CONSOLE_SCREEN_BUFFER_INFOEX);

        // cb_member_type
        XTESTS_RUN_CASE(test_STARTUPINFOW);

        // cBytes_member_type
        XTESTS_RUN_CASE(test_OFSTRUCT);

        // dwLength_member_type
        XTESTS_RUN_CASE(test_MEMORYSTATUS);

        // dwOSVersionInfoSize_member_type
        XTESTS_RUN_CASE(test_OSVERSIONINFOA);
        XTESTS_RUN_CASE(test_OSVERSIONINFOEXA);

        // dwSize_member_type
        XTESTS_RUN_CASE(test_COMMCONFIG);

        // nLength_member_type
        XTESTS_RUN_CASE(test_SECURITY_ATTRIBUTES);

        // uSize_member_type
        XTESTS_RUN_CASE(test_DRAGINFOA);

        // DCBlength
        XTESTS_RUN_CASE(test_DCB);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::ss_size_t;


// no_init_member_type

static void test_FILETIME()
{
    FILETIME ft;

    winstl::init_struct(ft);

    TEST_INT_EQ(0u, ft.dwLowDateTime);
    TEST_INT_EQ(0u, ft.dwHighDateTime);
}

static void test_SYSTEMTIME()
{
    SYSTEMTIME st;

    winstl::init_struct(st);

    TEST_INT_EQ(0u, st.wYear);
    TEST_INT_EQ(0u, st.wMonth);
    TEST_INT_EQ(0u, st.wDayOfWeek);
    TEST_INT_EQ(0u, st.wDay);
    TEST_INT_EQ(0u, st.wHour);
    TEST_INT_EQ(0u, st.wMinute);
    TEST_INT_EQ(0u, st.wSecond);
    TEST_INT_EQ(0u, st.wMilliseconds);
}

static void test_SYSTEM_INFO()
{
    SYSTEM_INFO si;

    winstl::init_struct(si);

    TEST_INT_EQ(0u, si.dwOemId);
    TEST_INT_EQ(0u, si.wProcessorArchitecture);
    TEST_INT_EQ(0u, si.dwPageSize);
    TEST_PTR_EQ(0, si.lpMinimumApplicationAddress);
    TEST_PTR_EQ(0, si.lpMaximumApplicationAddress);
    TEST_INT_EQ(0u, si.dwActiveProcessorMask);
    TEST_INT_EQ(0u, si.dwNumberOfProcessors);
    TEST_INT_EQ(0u, si.dwProcessorType);
    TEST_INT_EQ(0u, si.dwAllocationGranularity);
    TEST_INT_EQ(0u, si.wProcessorLevel);
    TEST_INT_EQ(0u, si.wProcessorRevision);
}


// cbSize_member_type

static void test_CONSOLE_SCREEN_BUFFER_INFOEX()
{
    CONSOLE_SCREEN_BUFFER_INFOEX csbix;

    winstl::init_struct(csbix);

    TEST_INT_EQ(sizeof(csbix), csbix.cbSize);

#if 0
    TEST((COORD { 0, 0 } == csbix.dwSize));
    TEST((COORD { 0, 0 } == csbix.dwCursorPosition));
#endif
    TEST_INT_EQ(0, csbix.wAttributes);
#if 0
    TEST_INT_EQ(0, csbix.srWindow);
    TEST_INT_EQ(0, csbix.dwMaximumWindowSize);
#endif
    TEST_INT_EQ(0, csbix.wPopupAttributes);
    TEST_BOOLEAN_FALSE(csbix.bFullscreenSupported);
    // COLORREF csbix.ColorTable[16];
}


// cb_member_type

static void test_STARTUPINFOW()
{
    STARTUPINFOW si;

    winstl::init_struct(si);

    TEST_INT_EQ(sizeof(si), si.cb);
    TEST_PTR_EQ(NULL, si.lpReserved);
    TEST_PTR_EQ(NULL, si.lpDesktop);
    TEST_PTR_EQ(NULL, si.lpTitle);
    TEST_INT_EQ(0u, si.dwX);
    TEST_INT_EQ(0u, si.dwY);
    TEST_INT_EQ(0u, si.dwXSize);
    TEST_INT_EQ(0u, si.dwYSize);
    TEST_INT_EQ(0u, si.dwXCountChars);
    TEST_INT_EQ(0u, si.dwYCountChars);
    TEST_INT_EQ(0u, si.dwFillAttribute);
    TEST_INT_EQ(0u, si.dwFlags);
    TEST_INT_EQ(0u, si.wShowWindow);
    TEST_INT_EQ(0u, si.cbReserved2);
    TEST_PTR_EQ(NULL, si.lpReserved2);
    TEST_PTR_EQ(NULL, si.hStdInput);
    TEST_PTR_EQ(NULL, si.hStdOutput);
    TEST_PTR_EQ(NULL, si.hStdError);
}


// cBytes_member_type

static void test_OFSTRUCT()
{
    OFSTRUCT ofs;

    winstl::init_struct(ofs);

    TEST_INT_EQ(sizeof(ofs), static_cast<ss_size_t>(ofs.cBytes));
    TEST_INT_EQ(0u, ofs.fFixedDisk);
    TEST_INT_EQ(0u, ofs.nErrCode);
    TEST_INT_EQ(0u, ofs.Reserved1);
    TEST_INT_EQ(0u, ofs.Reserved2);
#if 0
    CHAR szPathName[OFS_MAXPATHNAME];
#endif
}


// dwLength_member_type

static void test_MEMORYSTATUS()
{
    MEMORYSTATUS ms;

    winstl::init_struct(ms);

    TEST_INT_EQ(sizeof(ms), ms.dwLength);
    TEST_INT_EQ(0u, ms.dwMemoryLoad);
    TEST_INT_EQ(0u, ms.dwTotalPhys);
    TEST_INT_EQ(0u, ms.dwAvailPhys);
    TEST_INT_EQ(0u, ms.dwTotalPageFile);
    TEST_INT_EQ(0u, ms.dwAvailPageFile);
    TEST_INT_EQ(0u, ms.dwTotalVirtual);
    TEST_INT_EQ(0u, ms.dwAvailVirtual);
}


// dwOSVersionInfoSize_member_type

static void test_OSVERSIONINFOA()
{
    OSVERSIONINFOA osvi;

    winstl::init_struct(osvi);

    TEST_INT_EQ(sizeof(osvi), osvi.dwOSVersionInfoSize);
    TEST_INT_EQ(0u, osvi.dwMajorVersion);
    TEST_INT_EQ(0u, osvi.dwMinorVersion);
    TEST_INT_EQ(0u, osvi.dwBuildNumber);
    TEST_INT_EQ(0u, osvi.dwPlatformId);
#if 0
    CHAR   szCSDVersion[ 128 ];     // Maintenance string for PSS usage
#endif
}

static void test_OSVERSIONINFOEXA()
{
    OSVERSIONINFOEXA osvix;

    winstl::init_struct(osvix);

    TEST_INT_EQ(sizeof(osvix), osvix.dwOSVersionInfoSize);
    TEST_INT_EQ(0u, osvix.dwMajorVersion);
    TEST_INT_EQ(0u, osvix.dwMinorVersion);
    TEST_INT_EQ(0u, osvix.dwBuildNumber);
    TEST_INT_EQ(0u, osvix.dwPlatformId);
#if 0
    CHAR   szCSDVersion[ 128 ];     // Maintenance string for PSS usage
#endif
    TEST_INT_EQ(0u, osvix.wServicePackMajor);
    TEST_INT_EQ(0u, osvix.wServicePackMinor);
    TEST_INT_EQ(0u, osvix.wSuiteMask);
    TEST_INT_EQ(0u, osvix.wProductType);
    TEST_INT_EQ(0u, osvix.wReserved);
}


// dwSize_member_type

static void test_COMMCONFIG()
{
    // NOTE: this specialisation is questionnable, since COMMCONFIG is a
    // variable-length structure

    COMMCONFIG cc;

    winstl::init_struct(cc);

    TEST_INT_EQ(sizeof(cc), cc.dwSize);
    TEST_INT_EQ(0u, cc.wVersion);
    TEST_INT_EQ(0u, cc.wReserved);
#if 0
    TEST_INT_EQ(0, cc.dcb);
#endif
    TEST_INT_EQ(0u, cc.dwProviderSubType);
    TEST_INT_EQ(0u, cc.dwProviderOffset);
    TEST_INT_EQ(0u, cc.dwProviderSize);
#if 0
    TEST_INT_EQ(0, cc.wcProviderData);
#endif
}


// nLength_member_type

static void test_SECURITY_ATTRIBUTES()
{
    SECURITY_ATTRIBUTES sa;

    winstl::init_struct(sa);

    TEST_INT_EQ(sizeof(sa), sa.nLength);
    TEST_PTR_EQ(NULL, sa.lpSecurityDescriptor);
    TEST_BOOLEAN_FALSE(sa.bInheritHandle);
}


// uSize_member_type

static void test_DRAGINFOA()
{
    DRAGINFOA da;

    winstl::init_struct(da);

    TEST_INT_EQ(sizeof(da), da.uSize);
#if 0
    POINT pt;
#endif
    TEST_BOOLEAN_FALSE(da.fNC);
    TEST_PTR_EQ(NULL, da.lpFileList);
    TEST_INT_EQ(0u, da.grfKeyState);
}


// DCBlength

static void test_DCB()
{
    DCB dcb;

    winstl::init_struct(dcb);

    TEST_INT_EQ(sizeof(dcb), dcb.DCBlength);
    TEST_INT_EQ(0u, dcb.BaudRate);
    TEST_INT_EQ(0u, dcb.fBinary);
    TEST_INT_EQ(0u, dcb.fParity);
    TEST_INT_EQ(0u, dcb.fOutxCtsFlow);
    TEST_INT_EQ(0u, dcb.fOutxDsrFlow);
    TEST_INT_EQ(0u, dcb.fDtrControl);
    TEST_INT_EQ(0u, dcb.fDsrSensitivity);
    TEST_INT_EQ(0u, dcb.fTXContinueOnXoff);
    TEST_INT_EQ(0u, dcb.fOutX);
    TEST_INT_EQ(0u, dcb.fInX);
    TEST_INT_EQ(0u, dcb.fErrorChar);
    TEST_INT_EQ(0u, dcb.fNull);
    TEST_INT_EQ(0u, dcb.fRtsControl);
    TEST_INT_EQ(0u, dcb.fAbortOnError);
    TEST_INT_EQ(0u, dcb.fDummy2);
    TEST_INT_EQ(0u, dcb.wReserved);
    TEST_INT_EQ(0u, dcb.XonLim);
    TEST_INT_EQ(0u, dcb.XoffLim);
    TEST_INT_EQ(0u, dcb.ByteSize);
    TEST_INT_EQ(0u, dcb.Parity);
    TEST_INT_EQ(0u, dcb.StopBits);
    TEST_CHAR_EQ('\0', dcb.XonChar);
    TEST_CHAR_EQ('\0', dcb.XoffChar);
    TEST_CHAR_EQ('\0', dcb.ErrorChar);
    TEST_CHAR_EQ('\0', dcb.EofChar);
    TEST_CHAR_EQ('\0', dcb.EvtChar);
    TEST_INT_EQ(0u, dcb.wReserved1);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

