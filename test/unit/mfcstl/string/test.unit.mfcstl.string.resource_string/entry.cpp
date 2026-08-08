/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.string.resource_string/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::resource_string`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <mfcstl/string/resource_string.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void TEST_construct_from_cstring();
static void TEST_copy_and_assign();
static void TEST_iteration_and_shims();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.string.resource_string", verbosity))
    {
        XTESTS_RUN_CASE(TEST_construct_from_cstring);
        XTESTS_RUN_CASE(TEST_copy_and_assign);
        XTESTS_RUN_CASE(TEST_iteration_and_shims);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_construct_from_cstring()
{
    CString const src(_T("resource"));
    mfcstl::resource_string const rs(src);

    TEST_INT_EQ(8, rs.size());
    TEST_BOOLEAN_FALSE(rs.empty());
    TEST_MS_EQ(_T("resource"), rs.c_str());
}

static void TEST_copy_and_assign()
{
    mfcstl::resource_string rs1(CString(_T("one")));
    mfcstl::resource_string rs2(rs1);

    TEST_MS_EQ(_T("one"), rs2.c_str());

    rs2 = CString(_T("two"));

    TEST_MS_EQ(_T("two"), rs2.c_str());
    TEST_MS_EQ(_T("two"), rs2.data());
}

static void TEST_iteration_and_shims()
{
    mfcstl::resource_string const rs(CString(_T("abc")));

    TEST_INT_EQ(3, rs.end() - rs.begin());
    TEST_INT_EQ(3u, stlsoft::c_str_len(rs));
    TEST_MS_EQ(_T("abc"), stlsoft::c_str_ptr(rs));
    TEST_PTR_NE(NULL, stlsoft::c_str_ptr_null(rs));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
