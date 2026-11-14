/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/atlstl/shims/access/string/CWindow/entry.cpp
 *
 * Purpose: Unit-tests for string-access-shims for `CWindow` (NULL HWND).
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <atlstl/shims/access/string/CWindow.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <atlbase.h>
#include <atlwin.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CALLS_POSSIBLE_WITH_NULL_HWND();
    static void TEST_EMPTY_WINDOW_TEXT();
    static void TEST_PROXY_EQUALITY_OPERATORS();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_CALLS_POSSIBLE_WITH_NULL_HWND);
        XTESTS_RUN_CASE(TEST_EMPTY_WINDOW_TEXT);
        XTESTS_RUN_CASE(TEST_PROXY_EQUALITY_OPERATORS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CALLS_POSSIBLE_WITH_NULL_HWND()
{
    CWindow w;

    w.m_hWnd = NULL;

    stlsoft::c_str_len(w);
    stlsoft::c_str_ptr(w);
    stlsoft::c_str_ptr_null(w);
    stlsoft::c_str_data(w);

    TEST_PASSED();
}

static void TEST_EMPTY_WINDOW_TEXT()
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

static void TEST_PROXY_EQUALITY_OPERATORS()
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
