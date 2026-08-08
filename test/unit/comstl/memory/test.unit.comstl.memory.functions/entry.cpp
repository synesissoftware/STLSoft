/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.memory.functions/entry.cpp
 *
 * Purpose: Unit-tests for COM task memory helper functions.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/memory/functions.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_CoTaskMemGetSize(void);
static void test_CoTaskMemDidAlloc(void);
static void test_CoTaskMemHeapMinimise(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.memory.functions", verbosity))
    {
        XTESTS_RUN_CASE(test_CoTaskMemGetSize);
        XTESTS_RUN_CASE(test_CoTaskMemDidAlloc);
        XTESTS_RUN_CASE(test_CoTaskMemHeapMinimise);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_CoTaskMemGetSize(void)
{
    void* pv = ::CoTaskMemAlloc(16);

    TEST_PTR_NE(NULL, pv);
    TEST_UINT_EQ(16u, comstl::CoTaskMemGetSize(pv));
    ::CoTaskMemFree(pv);
}

static void test_CoTaskMemDidAlloc(void)
{
    void* pv = ::CoTaskMemAlloc(8);
    int   stack;

    TEST_PTR_NE(NULL, pv);
    TEST_INT_EQ(1, comstl::CoTaskMemDidAlloc(pv));
    TEST_INT_EQ(0, comstl::CoTaskMemDidAlloc(&stack));
    ::CoTaskMemFree(pv);
}

static void test_CoTaskMemHeapMinimise(void)
{
    comstl::CoTaskMemHeapMinimise();
    comstl::CoTaskMemHeapMinimize();
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
