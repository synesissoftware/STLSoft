/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atlstl.shims.access.string.CComBSTR/entry.cpp
 *
 * Purpose: Unit-tests for string-access-shims for `CComBSTR`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <atlstl/shims/access/string/CComBSTR.hpp>
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
    static void TEST_empty_string(void);
    static void TEST_non_empty_string(void);
    static void TEST_null_bstr_returns_empty_ptr(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atlstl.shims.access.string.CComBSTR", verbosity))
    {
        XTESTS_RUN_CASE(TEST_calls_possible);
        XTESTS_RUN_CASE(TEST_empty_string);
        XTESTS_RUN_CASE(TEST_non_empty_string);
        XTESTS_RUN_CASE(TEST_null_bstr_returns_empty_ptr);

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
    stlsoft::c_str_data(s);

    stlsoft::c_str_len_w(s);
    stlsoft::c_str_len(s);

    stlsoft::c_str_ptr_w(s);
    stlsoft::c_str_ptr(s);

    stlsoft::c_str_ptr_null_w(s);
    stlsoft::c_str_ptr_null(s);

    TEST_PASSED();
}

static void TEST_empty_string()
{
    CComBSTR const s;

    TEST_INT_EQ(0u, stlsoft::c_str_len_w(s));
    TEST_INT_EQ(0u, stlsoft::c_str_len(s));

    TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_w(s));
    TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null(s));

    TEST_WS_EQ(L"", stlsoft::c_str_ptr_w(s));
    TEST_WS_EQ(L"", stlsoft::c_str_ptr(s));
}

static void TEST_non_empty_string()
{
    wchar_t const* const expected = L"ATL STL";
    CComBSTR const       s(expected);

    TEST_INT_EQ(::wcslen(expected), stlsoft::c_str_len_w(s));
    TEST_INT_EQ(::wcslen(expected), stlsoft::c_str_len(s));

    TEST_WS_EQ(expected, stlsoft::c_str_ptr_w(s));
    TEST_WS_EQ(expected, stlsoft::c_str_ptr(s));

    TEST_WS_EQ(expected, stlsoft::c_str_data_w(s));
    TEST_WS_EQ(expected, stlsoft::c_str_data(s));

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr_null_w(s));
    TEST_WS_EQ(expected, stlsoft::c_str_ptr_null_w(s));
}

static void TEST_null_bstr_returns_empty_ptr()
{
    CComBSTR s;

    s.m_str = NULL;

    TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_w(s));
    TEST_WS_EQ(L"", stlsoft::c_str_ptr_w(s));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
