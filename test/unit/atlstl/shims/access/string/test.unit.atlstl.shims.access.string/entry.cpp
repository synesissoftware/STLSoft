/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atlstl.shims.access.string/entry.cpp
 *
 * Purpose: Unit-tests for the primary string-access-shim include
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <atlstl/shims/access/string.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <atlbase.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_calls_possible(void);
    static void TEST_empty_ccombstr(void);
    static void TEST_non_empty_ccombstr(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atlstl.shims.access.string", verbosity))
    {
        XTESTS_RUN_CASE(TEST_calls_possible);
        XTESTS_RUN_CASE(TEST_empty_ccombstr);
        XTESTS_RUN_CASE(TEST_non_empty_ccombstr);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_calls_possible()
{
    CComBSTR const s(L"atlstl");

    stlsoft::c_str_data_w(s);
    stlsoft::c_str_len_w(s);
    stlsoft::c_str_ptr_w(s);
    stlsoft::c_str_ptr_null_w(s);

    TEST_PASSED();
}

static void TEST_empty_ccombstr()
{
    CComBSTR const s;

    TEST_INT_EQ(0u, stlsoft::c_str_len_w(s));
    TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_w(s));
    TEST_WS_EQ(L"", stlsoft::c_str_ptr_w(s));
}

static void TEST_non_empty_ccombstr()
{
    wchar_t const* const expected = L"ATL STL";
    CComBSTR const       s(expected);

    TEST_INT_EQ(::wcslen(expected), stlsoft::c_str_len_w(s));
    TEST_WS_EQ(expected, stlsoft::c_str_ptr_w(s));
    TEST_WS_EQ(expected, stlsoft::c_str_data_w(s));
    TEST_PTR_NE(NULL, stlsoft::c_str_ptr_null_w(s));
    TEST_WS_EQ(expected, stlsoft::c_str_ptr_null_w(s));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
