/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/string/grab_CString_buffer/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::grab_CString_buffer`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
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

    static void TEST_ACQUIRES_AND_RELEASES_BUFFER();
    static void TEST_PRESERVES_original_length_METADATA();
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
        XTESTS_RUN_CASE(TEST_ACQUIRES_AND_RELEASES_BUFFER);
        XTESTS_RUN_CASE(TEST_PRESERVES_original_length_METADATA);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_ACQUIRES_AND_RELEASES_BUFFER()
{
    CString s(_T("hello"));

    {
        mfcstl::grab_CString_buffer grab(s, 5);

        TEST_INT_EQ(5, grab.length());
        TEST_INT_EQ(5, _tcslen(grab.c_str()));

        LPTSTR const p = grab;

        p[0] = _T('w');
        p[1] = _T('o');
        p[2] = _T('r');
        p[3] = _T('l');
        p[4] = _T('d');
        p[5] = _T('\0');
    }

    TEST_MS_EQ(_T("world"), s);
}

static void TEST_PRESERVES_original_length_METADATA()
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
