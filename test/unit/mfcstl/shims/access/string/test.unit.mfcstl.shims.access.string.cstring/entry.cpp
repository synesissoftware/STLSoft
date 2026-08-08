/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.shims.access.string.cstring/entry.cpp
 *
 * Purpose: Unit-tests for CString string-access shims.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <mfcstl/shims/access/string/cstring.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>
#include <string.h>


namespace {

static void TEST_calls_possible();
static void TEST_empty_string();
static void TEST_non_empty_string();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.shims.access.string.cstring", verbosity))
    {
        XTESTS_RUN_CASE(TEST_calls_possible);
        XTESTS_RUN_CASE(TEST_empty_string);
        XTESTS_RUN_CASE(TEST_non_empty_string);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_calls_possible()
{
    CString const s(_T("mfcstl"));

    stlsoft::c_str_data(s);
    stlsoft::c_str_len(s);
    stlsoft::c_str_ptr(s);
    stlsoft::c_str_ptr_null(s);

    TEST_PASSED();
}

static void TEST_empty_string()
{
    CString const s;

    TEST_INT_EQ(0u, stlsoft::c_str_len(s));
    TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null(s));
    TEST_INT_EQ(0, _tcslen(stlsoft::c_str_ptr(s)));
}

static void TEST_non_empty_string()
{
    CString const s(_T("mfcstl"));

    TEST_INT_EQ(6u, stlsoft::c_str_len(s));
    TEST_MS_EQ(_T("mfcstl"), stlsoft::c_str_ptr(s));
    TEST_MS_EQ(_T("mfcstl"), stlsoft::c_str_data(s));
    TEST_MS_EQ(_T("mfcstl"), stlsoft::c_str_ptr_null(s));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
