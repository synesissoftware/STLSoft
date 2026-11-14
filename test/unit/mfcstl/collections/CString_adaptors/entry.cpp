/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/collections/CString_adaptors/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::CString_cadaptor` and `mfcstl::CString_iadaptor`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/collections/CString_adaptors.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CADAPTOR_DEFAULT_EMPTY();
    static void TEST_CADAPTOR_CONSTRUCT_AND_ASSIGN();
    static void TEST_CADAPTOR_APPEND_AND_SUBSTR();
    static void TEST_IADAPTOR_WRAPS_UNDERLYING_STRING();
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
        XTESTS_RUN_CASE(TEST_CADAPTOR_DEFAULT_EMPTY);
        XTESTS_RUN_CASE(TEST_CADAPTOR_CONSTRUCT_AND_ASSIGN);
        XTESTS_RUN_CASE(TEST_CADAPTOR_APPEND_AND_SUBSTR);
        XTESTS_RUN_CASE(TEST_IADAPTOR_WRAPS_UNDERLYING_STRING);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CADAPTOR_DEFAULT_EMPTY()
{
    mfcstl::CString_cadaptor s;

    TEST_BOOLEAN_TRUE(s.empty());
    TEST_INT_EQ(0, s.size());
}

static void TEST_CADAPTOR_CONSTRUCT_AND_ASSIGN()
{
    mfcstl::CString_cadaptor s(_T("mfcstl"));

    TEST_INT_EQ(6, s.size());
    TEST_MS_EQ(_T("mfcstl"), s.c_str());

    s = _T("adaptors");

    TEST_INT_EQ(8, s.size());
    TEST_MS_EQ(_T("adaptors"), s.c_str());
}

static void TEST_CADAPTOR_APPEND_AND_SUBSTR()
{
    mfcstl::CString_cadaptor s(_T("hello"));

    s.assign(_T("hello world"));

    TEST_MS_EQ(_T("hello world"), s.c_str());

    mfcstl::CString_cadaptor sub(s, 6, 5);

    TEST_MS_EQ(_T("world"), sub.c_str());
}

static void TEST_IADAPTOR_WRAPS_UNDERLYING_STRING()
{
    CString                             raw(_T("instance"));
    mfcstl::CString_iadaptor            sip(raw);

    TEST_INT_EQ(8, sip.size());
    TEST_MS_EQ(_T("instance"), sip.c_str());

    sip = _T("adapted");

    TEST_INT_EQ(7, raw.GetLength());
    TEST_MS_EQ(_T("adapted"), raw);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
