/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/shims/access/string/string/entry.cpp
 *
 * Purpose: Unit-tests for the MFCSTL string-access shim umbrella header.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/shims/access/string.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_UMBRELLA_INCLUDES_COMPILE();
    static void TEST_CSTRING_SHIMS_VIA_UMBRELLA();
    static void TEST_CWND_SHIMS_VIA_UMBRELLA();
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
        XTESTS_RUN_CASE(TEST_UMBRELLA_INCLUDES_COMPILE);
        XTESTS_RUN_CASE(TEST_CSTRING_SHIMS_VIA_UMBRELLA);
        XTESTS_RUN_CASE(TEST_CWND_SHIMS_VIA_UMBRELLA);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_UMBRELLA_INCLUDES_COMPILE()
{
    CString const s(_T("umbrella"));
    CWnd const    w;

    stlsoft::c_str_len(s);
    stlsoft::c_str_len(w);

    TEST_PASSED();
}

static void TEST_CSTRING_SHIMS_VIA_UMBRELLA()
{
    CString const s(_T("mfcstl"));

    TEST_INT_EQ(6u, stlsoft::c_str_len(s));
    TEST_MS_EQ(_T("mfcstl"), stlsoft::c_str_ptr(s));
}

static void TEST_CWND_SHIMS_VIA_UMBRELLA()
{
    CWnd w;

    TEST_INT_EQ(0u, stlsoft::c_str_len(w));
    TEST_PTR_EQ(NULL, static_cast<LPCTSTR>(stlsoft::c_str_ptr_null(w)));
    TEST_INT_EQ(0, _tcslen(stlsoft::c_str_ptr(w)));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
