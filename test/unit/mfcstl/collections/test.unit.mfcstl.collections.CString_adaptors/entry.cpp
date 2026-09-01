/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.collections.CString_adaptors/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::CString_cadaptor` and `mfcstl::CString_iadaptor`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
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

    static void TEST_cadaptor_default_empty(void);
    static void TEST_cadaptor_construct_and_assign(void);
    static void TEST_cadaptor_append_and_substr(void);
    static void TEST_iadaptor_wraps_underlying_string(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.collections.CString_adaptors", verbosity))
    {
        XTESTS_RUN_CASE(TEST_cadaptor_default_empty);
        XTESTS_RUN_CASE(TEST_cadaptor_construct_and_assign);
        XTESTS_RUN_CASE(TEST_cadaptor_append_and_substr);
        XTESTS_RUN_CASE(TEST_iadaptor_wraps_underlying_string);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_cadaptor_default_empty()
{
    mfcstl::CString_cadaptor s;

    TEST_BOOLEAN_TRUE(s.empty());
    TEST_INT_EQ(0, s.size());
}

static void TEST_cadaptor_construct_and_assign()
{
    mfcstl::CString_cadaptor s(_T("mfcstl"));

    TEST_INT_EQ(6, s.size());
    TEST_MS_EQ(_T("mfcstl"), s.c_str());

    s = _T("adaptors");

    TEST_INT_EQ(8, s.size());
    TEST_MS_EQ(_T("adaptors"), s.c_str());
}

static void TEST_cadaptor_append_and_substr()
{
    mfcstl::CString_cadaptor s(_T("hello"));

    s.assign(_T("hello world"));

    TEST_MS_EQ(_T("hello world"), s.c_str());

    mfcstl::CString_cadaptor sub(s, 6, 5);

    TEST_MS_EQ(_T("world"), sub.c_str());
}

static void TEST_iadaptor_wraps_underlying_string()
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
