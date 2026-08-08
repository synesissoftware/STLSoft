/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.string.bstr/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::bstr`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/string/bstr.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>
#include <stlsoft/shims/access/string.hpp>

#include <stdlib.h>
#include <string.h>

namespace {

static void test_default_construction(void);
static void test_construction_from_string(void);
static void test_attach_detach(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.string.bstr", verbosity))
    {
        XTESTS_RUN_CASE(test_default_construction);
        XTESTS_RUN_CASE(test_construction_from_string);
        XTESTS_RUN_CASE(test_attach_detach);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_default_construction(void)
{
    comstl::bstr  s;

    TEST_BOOLEAN_TRUE(s.empty());
    TEST_UINT_EQ(0u, s.length());
}

static void test_construction_from_string(void)
{
    comstl::bstr  s(L"hello");

    TEST_BOOLEAN_FALSE(s.empty());
    TEST_UINT_EQ(5u, s.length());
    TEST_INT_EQ(0, ::wcscmp(L"hello", stlsoft::c_str_ptr(s)));
}

static void test_attach_detach(void)
{
    BSTR          raw = ::SysAllocString(L"raw");
    comstl::bstr  s;

    s.attach(raw);
    TEST_PTR_EQ(raw, s.get());

    BSTR detached = s.detach();
    TEST_PTR_EQ(raw, detached);
    TEST_PTR_EQ(NULL, s.get());

    ::SysFreeString(detached);
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
