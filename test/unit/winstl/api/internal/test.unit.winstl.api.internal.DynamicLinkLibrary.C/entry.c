/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.api.internal.DynamicLinkLibrary.C/entry.c
 *
 * Created: 25th May 2025
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/api/internal/DynamicLinkLibrary.h>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */

/* Standard C header files */
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_GMFN_INVALID(void);
static void TEST_GMFN_VALID(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.api.internal.C.DynamicLinkLibrary", verbosity))
    {
        XTESTS_RUN_CASE(TEST_GMFN_INVALID);
        XTESTS_RUN_CASE(TEST_GMFN_VALID);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

// #define WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameA   WINSTL_API_EXTERNAL_DynamicLinkLibrary_GetModuleFileNameA
// #define WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameW   WINSTL_API_EXTERNAL_DynamicLinkLibrary_GetModuleFileNameW

static void TEST_GMFN_INVALID(void)
{
    HMODULE hmInvalid = (HMODULE)UINTPTR_MAX;

    /* sufficient buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[10000] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameA(hmInvalid, &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_MOD_NOT_FOUND, GetLastError());
            TEST_INT_EQ(0, n);
            TEST_CHAR_EQ('~', szBuff[n]);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[10000] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameW(hmInvalid, &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_MOD_NOT_FOUND, GetLastError());
            TEST_INT_EQ(0, n);
            TEST_CHAR_EQ(L'~', szBuff[n]);
        }
    }
}

static void TEST_GMFN_VALID(void)
{
    HMODULE hmKernel32 = LoadLibraryA("kernel32.dll");

    DWORD   cch_A = 0;
    DWORD   cch_W = 0;

    /* establish required size(s) */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[10000];
            DWORD const n = GetModuleFileNameA(hmKernel32, &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(17, n);
            TEST_CHAR_EQ('\0', szBuff[n]);
            TEST_CHAR_EQ('L', toupper(szBuff[n - 1]));

            cch_A = n;
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[10000];
            DWORD const n = GetModuleFileNameW(hmKernel32, &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(17, n);
            TEST_CHAR_EQ(L'\0', szBuff[n]);
            TEST_CHAR_EQ(L'L', towupper(szBuff[n - 1]));

            cch_W = n;
        }
    }

    /* 0 buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameA(hmKernel32, &szBuff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(cch_A, n);
            TEST_CHAR_EQ('~', szBuff[0]);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameW(hmKernel32, &szBuff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(cch_W, n);
            TEST_CHAR_EQ(L'~', szBuff[0]);
        }
    }

    /* 1 buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameA(hmKernel32, &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, GetLastError());
            TEST_INT_GE(cch_A, n);
            TEST_CHAR_EQ('\0', szBuff[0]);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameW(hmKernel32, &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, GetLastError());
            TEST_INT_GE(cch_W, n);
            TEST_CHAR_EQ(L'\0', szBuff[0]);
        }
    }

    /* _MAX_PATH buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[_MAX_PATH] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameA(hmKernel32, &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(cch_A, n);
            TEST_CHAR_EQ('\0', szBuff[n]);
            TEST_CHAR_NE('\0', szBuff[0]);
            TEST_CHAR_NE('\0', szBuff[n - 1]);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[_MAX_PATH] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameW(hmKernel32, &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(cch_W, n);
            TEST_CHAR_EQ(L'\0', szBuff[n]);
            TEST_CHAR_NE(L'\0', szBuff[0]);
            TEST_CHAR_NE(L'\0', szBuff[n - 1]);
        }
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

