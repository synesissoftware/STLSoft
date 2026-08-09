/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.string.grab_CString_buffer/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::grab_CString_buffer`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/string/grab_CString_buffer.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_acquires_and_releases_buffer(void);
    static void TEST_preserves_original_length_metadata(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.string.grab_CString_buffer", verbosity))
    {
        XTESTS_RUN_CASE(TEST_acquires_and_releases_buffer);
        XTESTS_RUN_CASE(TEST_preserves_original_length_metadata);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_acquires_and_releases_buffer()
{
    CString s(_T("hello"));

    {
        mfcstl::grab_CString_buffer grab(s, 5);

        TEST_INT_EQ(5, grab.length());
        TEST_INT_EQ(5, _tcslen(grab.c_str()));

        _tcscpy(grab, _T("world"));
    }

    TEST_MS_EQ(_T("world"), s);
}

static void TEST_preserves_original_length_metadata()
{
    CString s(_T("abc"));

    {
        mfcstl::grab_CString_buffer grab(s, 8);

        TEST_INT_EQ(3, grab.original_length());
        TEST_INT_EQ(8, grab.length());
    }

    TEST_INT_EQ(3, s.GetLength());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
