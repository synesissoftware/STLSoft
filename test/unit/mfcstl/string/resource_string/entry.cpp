/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/string/resource_string/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::resource_string`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/string/resource_string.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CONSTRUCT_FROM_CString();
    static void TEST_COPY_AND_ASSIGN();
    static void TEST_ITERATION_AND_SHIMS();
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
        XTESTS_RUN_CASE(TEST_CONSTRUCT_FROM_CString);
        XTESTS_RUN_CASE(TEST_COPY_AND_ASSIGN);
        XTESTS_RUN_CASE(TEST_ITERATION_AND_SHIMS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CONSTRUCT_FROM_CString()
{
    CString const src(_T("resource"));
    mfcstl::resource_string const rs(src);

    TEST_INT_EQ(8, rs.size());
    TEST_BOOLEAN_FALSE(rs.empty());
    TEST_MS_EQ(_T("resource"), rs.c_str());
}

static void TEST_COPY_AND_ASSIGN()
{
    mfcstl::resource_string rs1(CString(_T("one")));
    mfcstl::resource_string rs2(rs1);

    TEST_MS_EQ(_T("one"), rs2.c_str());

    rs2 = CString(_T("two"));

    TEST_MS_EQ(_T("two"), rs2.c_str());
    TEST_MS_EQ(_T("two"), rs2.data());
}

static void TEST_ITERATION_AND_SHIMS()
{
    mfcstl::resource_string const rs(CString(_T("abc")));

    TEST_INT_EQ(3, rs.end() - rs.begin());
    TEST_INT_EQ(3u, stlsoft::c_str_len(rs));
    TEST_MS_EQ(_T("abc"), stlsoft::c_str_ptr(rs));
    TEST_PTR_NE(NULL, stlsoft::c_str_ptr_null(rs));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
