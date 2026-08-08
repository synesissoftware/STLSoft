/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.shims.access.string.cwnd/entry.cpp
 *
 * Purpose: Unit-tests for CWnd string-access shims.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#define MFCSTL_STRING_ACCESS_NO_INCLUDE_AFXCMN

#include <mfcstl/shims/access/string/cwnd.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void TEST_null_hwnd_window();
static void TEST_c_str_ptr_returns_empty_for_null_hwnd();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.shims.access.string.cwnd", verbosity))
    {
        XTESTS_RUN_CASE(TEST_null_hwnd_window);
        XTESTS_RUN_CASE(TEST_c_str_ptr_returns_empty_for_null_hwnd);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_null_hwnd_window()
{
    CWnd w;

    TEST_PTR_EQ(NULL, w.m_hWnd);
    TEST_INT_EQ(0u, stlsoft::c_str_len(w));
    TEST_PTR_EQ(NULL, static_cast<LPCTSTR>(stlsoft::c_str_ptr_null(w)));
}

static void TEST_c_str_ptr_returns_empty_for_null_hwnd()
{
    CWnd w;

    TEST_INT_EQ(0, _tcslen(stlsoft::c_str_ptr(w)));
    TEST_INT_EQ(0, _tcslen(stlsoft::c_str_data(w)));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
