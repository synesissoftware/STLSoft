/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.shims.access.string/entry.cpp
 *
 * Purpose: Unit-tests for the MFCSTL string-access shim umbrella header.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <mfcstl/shims/access/string.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void TEST_umbrella_includes_compile();
static void TEST_cstring_shims_via_umbrella();
static void TEST_cwnd_shims_via_umbrella();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.shims.access.string", verbosity))
    {
        XTESTS_RUN_CASE(TEST_umbrella_includes_compile);
        XTESTS_RUN_CASE(TEST_cstring_shims_via_umbrella);
        XTESTS_RUN_CASE(TEST_cwnd_shims_via_umbrella);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_umbrella_includes_compile()
{
    CString const s(_T("umbrella"));
    CWnd const    w;

    stlsoft::c_str_len(s);
    stlsoft::c_str_len(w);

    TEST_PASSED();
}

static void TEST_cstring_shims_via_umbrella()
{
    CString const s(_T("mfcstl"));

    TEST_INT_EQ(6u, stlsoft::c_str_len(s));
    TEST_MS_EQ(_T("mfcstl"), stlsoft::c_str_ptr(s));
}

static void TEST_cwnd_shims_via_umbrella()
{
    CWnd w;

    TEST_INT_EQ(0u, stlsoft::c_str_len(w));
    TEST_PTR_EQ(NULL, static_cast<LPCTSTR>(stlsoft::c_str_ptr_null(w)));
    TEST_INT_EQ(0, _tcslen(stlsoft::c_str_ptr(w)));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
