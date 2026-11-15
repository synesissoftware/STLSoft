/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/shims/access/string/VARIANT/entry.cpp
 *
 * Purpose: Unit-tests for VARIANT string access shims.
 *
 * Created: 9th August 2026
 * Updated: 15th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/shims/access/string/VARIANT.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stlsoft/shims/access/string.hpp>
#include <sstream>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_c_str_ptr_integer_variant();
    static void test_c_str_ptr_bstr_variant();
    static void TEST_STREAM_INSERTION();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(test_c_str_ptr_integer_variant);
        XTESTS_RUN_CASE(test_c_str_ptr_bstr_variant);
        XTESTS_RUN_CASE(TEST_STREAM_INSERTION);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_c_str_ptr_integer_variant()
{
    VARIANT v;

    ::VariantInit(&v);
    v.vt = VT_I4;
    v.lVal = 1234;

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(v));
    TEST_INT_NE(0u, stlsoft::c_str_len(v));

    ::VariantClear(&v);
}

static void test_c_str_ptr_bstr_variant()
{
    VARIANT v;

    ::VariantInit(&v);
    v.vt = VT_BSTR;
    v.bstrVal = ::SysAllocString(L"abc");

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(v));

    ::VariantClear(&v);
}

static void TEST_STREAM_INSERTION()
{
    VARIANT v;

    ::VariantInit(&v);
    v.vt = VT_BSTR;
    v.bstrVal = ::SysAllocString(L"abc");

    {
        std::ostringstream nstm;

        nstm << stlsoft::c_str_ptr_a(v);
        nstm << stlsoft::c_str_ptr_null_a(v);

        TEST_MS_EQ("abcabc", nstm.str().c_str());
    }

    {
        std::wostringstream wstm;

        wstm << stlsoft::c_str_ptr_w(v);
        wstm << stlsoft::c_str_ptr_null_w(v);

        TEST_WS_EQ(L"abcabc", wstm.str().c_str());
    }

    ::VariantClear(&v);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
