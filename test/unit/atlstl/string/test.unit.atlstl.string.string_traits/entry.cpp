/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atlstl.string.string_traits/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::string_traits<CComBSTR>`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <atlstl/string/string_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/string/string_traits.hpp>

/* ATL header files */
#include <atlbase.h>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_empty_string();
    static void TEST_construct();
    static void TEST_assign_inplace();
    static void TEST_begin_and_end();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atlstl.string.string_traits", verbosity))
    {
        HRESULT const hrCoInit = ::CoInitialize(NULL);

        if (SUCCEEDED(hrCoInit))
        {
            XTESTS_RUN_CASE(TEST_empty_string);
            XTESTS_RUN_CASE(TEST_construct);
            XTESTS_RUN_CASE(TEST_assign_inplace);
            XTESTS_RUN_CASE(TEST_begin_and_end);

            ::CoUninitialize();
        }
        else
        {
            XTESTS_TEST_FAIL("CoInitialize() failed");
        }

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_empty_string()
{
    CComBSTR const s = stlsoft::string_traits<CComBSTR>::empty_string();

    TEST_INT_EQ(0, s.Length());
}

static void TEST_construct()
{
    CComBSTR const src(L"abcdef");
    CComBSTR const sub = stlsoft::string_traits<CComBSTR>::construct(src, 2u, 3u);

    TEST_INT_EQ(3, sub.Length());
    TEST_INT_EQ(0, ::wcsncmp(L"cde", sub, 3));
}

static void TEST_assign_inplace()
{
    CComBSTR       dest(L"old");
    CComBSTR const src(L"newer");

    stlsoft::string_traits<CComBSTR>::assign_inplace(dest, src.m_str, src.m_str + src.Length());

    TEST_INT_EQ(4, dest.Length());
    TEST_INT_EQ(0, ::wcscmp(L"newer", dest));
}

static void TEST_begin_and_end()
{
    CComBSTR s(L"ab");

    LPOLESTR const b = stlsoft::string_traits<CComBSTR>::begin(s);
    LPOLESTR const e = stlsoft::string_traits<CComBSTR>::end(s);

    TEST_PTR_NE(NULL, b);
    TEST_INT_EQ(2, e - b);
    TEST_INT_EQ(L'a', b[0]);
    TEST_INT_EQ(L'b', b[1]);
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
