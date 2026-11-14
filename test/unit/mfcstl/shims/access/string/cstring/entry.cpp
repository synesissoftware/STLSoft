/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/shims/access/string/cstring/entry.cpp
 *
 * Purpose: Unit-tests for CString string-access shims.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/shims/access/string/cstring.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CALLS_POSSIBLE();
    static void TEST_EMPTY_STRING();
    static void TEST_NON_EMPTY_STRING();
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
        XTESTS_RUN_CASE(TEST_CALLS_POSSIBLE);
        XTESTS_RUN_CASE(TEST_EMPTY_STRING);
        XTESTS_RUN_CASE(TEST_NON_EMPTY_STRING);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CALLS_POSSIBLE()
{
    CString const s(_T("mfcstl"));

    stlsoft::c_str_data(s);
    stlsoft::c_str_len(s);
    stlsoft::c_str_ptr(s);
    stlsoft::c_str_ptr_null(s);

    TEST_PASSED();
}

static void TEST_EMPTY_STRING()
{
    CString const s;

    TEST_INT_EQ(0u, stlsoft::c_str_len(s));
    TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null(s));
    TEST_INT_EQ(0, _tcslen(stlsoft::c_str_ptr(s)));
}

static void TEST_NON_EMPTY_STRING()
{
    CString const s(_T("mfcstl"));

    TEST_INT_EQ(6u, stlsoft::c_str_len(s));
    TEST_MS_EQ(_T("mfcstl"), stlsoft::c_str_ptr(s));
    TEST_MS_EQ(_T("mfcstl"), stlsoft::c_str_data(s));
    TEST_MS_EQ(_T("mfcstl"), stlsoft::c_str_ptr_null(s));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
