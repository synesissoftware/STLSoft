/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/memory/functions/entry.cpp
 *
 * Purpose: Unit-tests for COM task memory helper functions.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/memory/functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CoTaskMemGetSize();
    static void TEST_CoTaskMemDidAlloc();
    static void TEST_CoTaskMemHeapMinimise();
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
        XTESTS_RUN_CASE(TEST_CoTaskMemGetSize);
        XTESTS_RUN_CASE(TEST_CoTaskMemDidAlloc);
        XTESTS_RUN_CASE(TEST_CoTaskMemHeapMinimise);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CoTaskMemGetSize()
{
    void* pv = ::CoTaskMemAlloc(16);

    TEST_PTR_NE(NULL, pv);
    TEST_INT_EQ(16u, comstl::CoTaskMemGetSize(pv));
    ::CoTaskMemFree(pv);
}

static void TEST_CoTaskMemDidAlloc()
{
    void* pv = ::CoTaskMemAlloc(8);
    int   stack;

    TEST_PTR_NE(NULL, pv);
    TEST_INT_EQ(1, comstl::CoTaskMemDidAlloc(pv));
    TEST_INT_EQ(0, comstl::CoTaskMemDidAlloc(&stack));
    ::CoTaskMemFree(pv);
}

static void TEST_CoTaskMemHeapMinimise()
{
    comstl::CoTaskMemHeapMinimise();
    comstl::CoTaskMemHeapMinimize();
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
