/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.api.internal.SystemInformation.C/entry.c
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

#include <winstl/api/internal/SystemInformation.h>

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
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_GetEnvironmentVariable(void);
static void TEST_GetSystemDirectory(void);
static void TEST_GetWindowsDirectory(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.api.internal.C.SystemInformation", verbosity))
    {
        XTESTS_RUN_CASE(TEST_GetEnvironmentVariable);
        XTESTS_RUN_CASE(TEST_GetSystemDirectory);
        XTESTS_RUN_CASE(TEST_GetWindowsDirectory);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_GetEnvironmentVariable(void)
{
    SetEnvironmentVariableA("MY_CUSTOM_VARIABLE", "MyCustomVariable");

    /* 0 buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetEnvironmentVariableA( "MY_CUSTOM_VARIABLE", &szBuff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(17, n);
            TEST_CHAR_EQ('~', szBuff[0]);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetEnvironmentVariableW(L"MY_CUSTOM_VARIABLE", &szBuff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(17, n);
            TEST_CHAR_EQ(L'~', szBuff[0]);
        }
    }

    /* 1 buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetEnvironmentVariableA( "MY_CUSTOM_VARIABLE", &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, GetLastError());
            TEST_INT_GE(17, n);
            TEST_CHAR_EQ('\0', szBuff[0]);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetEnvironmentVariableW(L"MY_CUSTOM_VARIABLE", &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));


            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, GetLastError());
            TEST_INT_GE(17, n);
            TEST_CHAR_EQ(L'\0', szBuff[0]);
        }
    }

    /* sufficient buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[101] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetEnvironmentVariableA( "MY_CUSTOM_VARIABLE", &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(16, n);
            TEST_CHAR_NE('\0', szBuff[0]);
            TEST_CHAR_NE('\0', szBuff[n - 1]);
            TEST_CHAR_EQ('\0', szBuff[n]);
            TEST_MS_EQ("MyCustomVariable", szBuff);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[101] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetEnvironmentVariableW(L"MY_CUSTOM_VARIABLE", &szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(16, n);
            TEST_CHAR_NE(L'\0', szBuff[0]);
            TEST_CHAR_NE(L'\0', szBuff[n - 1]);
            TEST_CHAR_EQ(L'\0', szBuff[n]);
            TEST_WS_EQ(L"MyCustomVariable", szBuff);
        }
    }
}

static void TEST_GetSystemDirectory(void)
{
    /* 0 buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetSystemDirectoryA(&szBuff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(19, n);
            TEST_CHAR_EQ('~', szBuff[0]);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetSystemDirectoryW(&szBuff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(19, n);
            TEST_CHAR_EQ(L'~', szBuff[0]);
        }
    }

    /* 1 buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetSystemDirectoryA(&szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, GetLastError());
            TEST_INT_GE(19, n);
            TEST_CHAR_EQ('\0', szBuff[0]);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetSystemDirectoryW(&szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, GetLastError());
            TEST_INT_GE(19, n);
            TEST_CHAR_EQ(L'\0', szBuff[0]);
        }
    }

    /* sufficient buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[10001] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetSystemDirectoryA(&szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(19, n);
            TEST(isalpha(szBuff[0]));
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[10001] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetSystemDirectoryW(&szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(19, n);
            TEST(iswalpha(szBuff[0]));
        }
    }
}

static void TEST_GetWindowsDirectory(void)
{
    /* 0 buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetWindowsDirectoryA(&szBuff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(10, n);
            TEST_CHAR_EQ('~', szBuff[0]);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetWindowsDirectoryW(&szBuff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(10, n);
            TEST_CHAR_EQ(L'~', szBuff[0]);
        }
    }

    /* 1 buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetWindowsDirectoryA(&szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, GetLastError());
            TEST_INT_GE(10, n);
            TEST_CHAR_EQ('\0', szBuff[0]);
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[1] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetWindowsDirectoryW(&szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, GetLastError());
            TEST_INT_GE(10, n);
            TEST_CHAR_EQ(L'\0', szBuff[0]);
        }
    }

    /* sufficient buffer */
    {
        {
            SetLastError(ERROR_SUCCESS);

            CHAR        szBuff[10001] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetWindowsDirectoryA(&szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(10, n);
            TEST(isalpha(szBuff[0]));
        }

        {
            SetLastError(ERROR_SUCCESS);

            WCHAR       szBuff[10001] = { '~' };
            DWORD const n = WINSTL_API_INTERNAL_SystemInformation_GetWindowsDirectoryW(&szBuff[0], STLSOFT_NUM_ELEMENTS(szBuff));

            TEST_INT_EQ(ERROR_SUCCESS, GetLastError());
            TEST_INT_GE(10, n);
            TEST(iswalpha(szBuff[0]));
        }
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

