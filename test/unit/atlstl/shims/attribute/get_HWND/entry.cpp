/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/atlstl/shims/attribute/get_HWND/entry.cpp
 *
 * Purpose: Unit-tests for `atlstl::get_HWND` attribute shim for `CWindow`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <atlstl/shims/attribute/get_HWND.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <atlbase.h>
#include <atlwin.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_NULL_HWND();
    static void TEST_EXPLICIT_HWND_VALUE();
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
        XTESTS_RUN_CASE(TEST_NULL_HWND);
        XTESTS_RUN_CASE(TEST_EXPLICIT_HWND_VALUE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_NULL_HWND()
{
    CWindow w;

    w.m_hWnd = NULL;

    TEST_PTR_EQ(NULL, atlstl::get_HWND(w));
}

static void TEST_EXPLICIT_HWND_VALUE()
{
    CWindow w;

    w.m_hWnd = reinterpret_cast<HWND>(static_cast<uintptr_t>(0x1234));

    TEST_PTR_EQ(w.m_hWnd, atlstl::get_HWND(w));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
