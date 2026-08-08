/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atlstl.shims.access.string.CWindow/entry.cpp
 *
 * Purpose: Unit-tests for string-access-shims for `CWindow` (NULL HWND).
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#define STLSOFT_MINIMUM_SAS_INCLUDES


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <atlstl/shims/access/string/CWindow.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* ATL header files */
#include <atlbase.h>
#include <atlwin.h>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_calls_possible_with_null_hwnd();
    static void TEST_empty_window_text();
    static void TEST_proxy_equality_operators();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atlstl.shims.access.string.CWindow", verbosity))
    {
        XTESTS_RUN_CASE(TEST_calls_possible_with_null_hwnd);
        XTESTS_RUN_CASE(TEST_empty_window_text);
        XTESTS_RUN_CASE(TEST_proxy_equality_operators);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_calls_possible_with_null_hwnd()
{
    CWindow w;

    w.m_hWnd = NULL;

    stlsoft::c_str_len(w);
    stlsoft::c_str_ptr(w);
    stlsoft::c_str_ptr_null(w);
    stlsoft::c_str_data(w);

    TEST_PASSED();
}

static void TEST_empty_window_text()
{
    CWindow w;

    w.m_hWnd = NULL;

    TEST_INT_EQ(0u, stlsoft::c_str_len(w));
    TEST_PTR_EQ(NULL, static_cast<LPCTSTR>(stlsoft::c_str_ptr_null(w)));

#if defined(UNICODE)
    TEST_WS_EQ(L"", static_cast<LPCTSTR>(stlsoft::c_str_ptr(w)));
    TEST_WS_EQ(L"", static_cast<LPCTSTR>(stlsoft::c_str_data(w)));
#else /* ? UNICODE */
    TEST_MS_EQ("", static_cast<LPCTSTR>(stlsoft::c_str_ptr(w)));
    TEST_MS_EQ("", static_cast<LPCTSTR>(stlsoft::c_str_data(w)));
#endif /* UNICODE */
}

static void TEST_proxy_equality_operators()
{
    CWindow w;

    w.m_hWnd = NULL;

    atlstl::c_str_ptr_null_CWindow_proxy const nullProxy(w);

    TEST_BOOLEAN_EQ(1, NULL == nullProxy);
    TEST_BOOLEAN_EQ(1, nullProxy == NULL);
    TEST_BOOLEAN_EQ(1, NULL != static_cast<LPCTSTR>(stlsoft::c_str_ptr(w)));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
