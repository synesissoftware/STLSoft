/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/shims/access/string/cwnd/entry.cpp
 *
 * Purpose: Unit-tests for CWnd string-access shims.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/shims/access/string/cwnd.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_NULL_HWND_WINDOW();
    static void TEST_c_str_ptr_RETURNS_EMPTY_FOR_NULL_HWND();
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
        XTESTS_RUN_CASE(TEST_NULL_HWND_WINDOW);
        XTESTS_RUN_CASE(TEST_c_str_ptr_RETURNS_EMPTY_FOR_NULL_HWND);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_NULL_HWND_WINDOW()
{
    CWnd w;

    TEST_PTR_EQ(NULL, w.m_hWnd);
    TEST_INT_EQ(0u, stlsoft::c_str_len(w));
    TEST_PTR_EQ(NULL, static_cast<LPCTSTR>(stlsoft::c_str_ptr_null(w)));
}

static void TEST_c_str_ptr_RETURNS_EMPTY_FOR_NULL_HWND()
{
    CWnd w;

    TEST_INT_EQ(0, _tcslen(stlsoft::c_str_ptr(w)));
    TEST_INT_EQ(0, _tcslen(stlsoft::c_str_data(w)));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
