/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/string/bstr/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::bstr`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/string/bstr.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stlsoft/shims/access/string.hpp>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_DEFAULT_CONSTRUCTION();
    static void TEST_CONSTRUCTION_FROM_STRING();
    static void TEST_ATTACH_DETACH();
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
        XTESTS_RUN_CASE(TEST_DEFAULT_CONSTRUCTION);
        XTESTS_RUN_CASE(TEST_CONSTRUCTION_FROM_STRING);
        XTESTS_RUN_CASE(TEST_ATTACH_DETACH);

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
    comstl::bstr  s;

    TEST_BOOLEAN_TRUE(s.empty());
    TEST_INT_EQ(0u, s.length());
}

static void TEST_CONSTRUCTION_FROM_STRING()
{
    comstl::bstr  s(L"hello");

    TEST_BOOLEAN_FALSE(s.empty());
    TEST_INT_EQ(5u, s.length());
    TEST_INT_EQ(0, ::wcscmp(L"hello", stlsoft::c_str_ptr(s)));
}

static void TEST_ATTACH_DETACH()
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
