/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/shims/access/string/VARIANT/entry.cpp
 *
 * Purpose: Unit-tests for VARIANT string access shims.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
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
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_c_str_ptr_INTEGER_VARIANT();
    static void TEST_c_str_ptr_BSTR_VARIANT();
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
        XTESTS_RUN_CASE(TEST_c_str_ptr_INTEGER_VARIANT);
        XTESTS_RUN_CASE(TEST_c_str_ptr_BSTR_VARIANT);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_c_str_ptr_INTEGER_VARIANT()
{
    VARIANT v;

    ::VariantInit(&v);
    v.vt = VT_I4;
    v.lVal = 1234;

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(v));
    TEST_INT_NE(0u, stlsoft::c_str_len(v));

    ::VariantClear(&v);
}

static void TEST_c_str_ptr_BSTR_VARIANT()
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
