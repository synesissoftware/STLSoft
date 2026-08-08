/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atlstl.shims.attribute.get_HWND/entry.cpp
 *
 * Purpose: Unit-tests for `atlstl::get_HWND` attribute shim for `CWindow`.
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

#include <atlstl/shims/attribute/get_HWND.hpp>

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


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_null_hwnd();
    static void TEST_explicit_hwnd_value();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atlstl.shims.attribute.get_HWND", verbosity))
    {
        XTESTS_RUN_CASE(TEST_null_hwnd);
        XTESTS_RUN_CASE(TEST_explicit_hwnd_value);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_null_hwnd()
{
    CWindow w;

    w.m_hWnd = NULL;

    TEST_PTR_EQ(NULL, atlstl::get_HWND(w));
}

static void TEST_explicit_hwnd_value()
{
    CWindow w;

    w.m_hWnd = reinterpret_cast<HWND>(static_cast<uintptr_t>(0x1234));

    TEST_PTR_EQ(w.m_hWnd, atlstl::get_HWND(w));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
