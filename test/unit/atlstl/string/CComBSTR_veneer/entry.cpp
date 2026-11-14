/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/atlstl/string/CComBSTR_veneer/entry.cpp
 *
 * Purpose: Unit-tests for `atlstl::CComBSTR_veneer`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <atlstl/string/CComBSTR_veneer.hpp>
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

    static void TEST_DEFAULT_CONSTRUCTION();
    static void TEST_COPY_AND_ASSIGNMENT();
    static void TEST_ITERATION();
    static void TEST_INDEXING_AND_SWAP();
    static void TEST_COMPARISON_OPERATORS();
    static void TEST_STRING_ACCESS_SHIMS();
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
        XTESTS_RUN_CASE(TEST_DEFAULT_CONSTRUCTION);
        XTESTS_RUN_CASE(TEST_COPY_AND_ASSIGNMENT);
        XTESTS_RUN_CASE(TEST_ITERATION);
        XTESTS_RUN_CASE(TEST_INDEXING_AND_SWAP);
        XTESTS_RUN_CASE(TEST_COMPARISON_OPERATORS);
        XTESTS_RUN_CASE(TEST_STRING_ACCESS_SHIMS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_DEFAULT_CONSTRUCTION()
{
    atlstl::CComBSTR_veneer const s;

    TEST_BOOLEAN_EQ(1, s.empty());
    TEST_INT_EQ(0u, s.length());
    TEST_INT_EQ(0u, s.size());
    TEST_WS_EQ(L"", s.c_str());
    TEST_WS_EQ(L"", s.data());
}

static void TEST_COPY_AND_ASSIGNMENT()
{
    atlstl::CComBSTR_veneer const s1(L"hello");
    atlstl::CComBSTR_veneer       s2(s1);
    atlstl::CComBSTR_veneer       s3;

    s3 = s1;

    TEST_INT_EQ(5u, s2.length());
    TEST_WS_EQ(L"hello", s2.c_str());
    TEST_WS_EQ(L"hello", s3.c_str());

    atlstl::CComBSTR_veneer s4(LPCOLESTR(L"ab"), LPCOLESTR(L"ab") + 1);

    TEST_INT_EQ(1u, s4.length());
    TEST_WS_EQ(L"a", s4.c_str());
}

static void TEST_ITERATION()
{
    atlstl::CComBSTR_veneer const s(L"xy");

    TEST_INT_EQ(static_cast<ss_ptrdiff_t>(2), s.end() - s.begin());
    TEST_INT_EQ(L'x', s.begin()[0]);
    TEST_INT_EQ(L'y', s.begin()[1]);
}

static void TEST_INDEXING_AND_SWAP()
{
    atlstl::CComBSTR_veneer s1(L"one");
    atlstl::CComBSTR_veneer s2(L"two");

    TEST_INT_EQ(L'o', s1[1]);
    TEST_INT_EQ(L'w', s2[1]);

    s1.swap(s2);

    TEST_WS_EQ(L"two", s1.c_str());
    TEST_WS_EQ(L"one", s2.c_str());
}

static void TEST_COMPARISON_OPERATORS()
{
    atlstl::CComBSTR_veneer const s1(L"match");
    atlstl::CComBSTR_veneer const s2(L"match");
    atlstl::CComBSTR_veneer const s3(L"other");

    TEST_BOOLEAN_EQ(1, s1 == s2);
    TEST_BOOLEAN_EQ(1, s1 != s3);
    TEST_BOOLEAN_EQ(1, s1 == L"match");
    TEST_BOOLEAN_EQ(1, L"match" == s1);
}

static void TEST_STRING_ACCESS_SHIMS()
{
    atlstl::CComBSTR_veneer const s(L"veneer");

    TEST_INT_EQ(6u, stlsoft::c_str_len_w(s));
    TEST_WS_EQ(L"veneer", stlsoft::c_str_ptr_w(s));
    TEST_WS_EQ(L"veneer", stlsoft::c_str_data_w(s));
    TEST_PTR_NE(NULL, stlsoft::c_str_ptr_null_w(s));
    TEST_WS_EQ(L"veneer", stlsoft::c_str_ptr_null_w(s));

    atlstl::CComBSTR_veneer const empty;

    TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_w(empty));
    TEST_WS_EQ(L"", stlsoft::c_str_ptr_w(empty));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
