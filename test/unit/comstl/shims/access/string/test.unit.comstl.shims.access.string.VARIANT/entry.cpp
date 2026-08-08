/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.shims.access.string.VARIANT/entry.cpp
 *
 * Purpose: Unit-tests for VARIANT string access shims.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/shims/access/string/VARIANT.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>
#include <stlsoft/shims/access/string.hpp>

#include <stdlib.h>

namespace {

static void test_c_str_ptr_integer_variant(void);
static void test_c_str_ptr_bstr_variant(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.shims.access.string.VARIANT", verbosity))
    {
        XTESTS_RUN_CASE(test_c_str_ptr_integer_variant);
        XTESTS_RUN_CASE(test_c_str_ptr_bstr_variant);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_c_str_ptr_integer_variant(void)
{
    VARIANT v;

    ::VariantInit(&v);
    v.vt = VT_I4;
    v.lVal = 1234;

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(v));
    TEST_UINT_NE(0u, stlsoft::c_str_len(v));

    ::VariantClear(&v);
}

static void test_c_str_ptr_bstr_variant(void)
{
    VARIANT v;

    ::VariantInit(&v);
    v.vt = VT_BSTR;
    v.bstrVal = ::SysAllocString(L"abc");

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(v));

    ::VariantClear(&v);
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
