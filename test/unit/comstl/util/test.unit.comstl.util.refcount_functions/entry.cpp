/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.refcount_functions/entry.cpp
 *
 * Purpose: Unit-tests for COM reference-count helpers.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/util/refcount_functions.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include "../../helpers/mock_unknown.hpp"

#include <stdlib.h>

namespace {

using test_comstl::mock_unknown;

static void test_addref_release(void);
static void test_safe_addref_release(void);
static void test_release_set_null(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.util.refcount_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_addref_release);
        XTESTS_RUN_CASE(test_safe_addref_release);
        XTESTS_RUN_CASE(test_release_set_null);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_addref_release(void)
{
    mock_unknown*   p = new mock_unknown();

    TEST_UINT_EQ(2u, p->AddRef());
    comstl__release(p);
    TEST_UINT_EQ(1u, p->m_ref);
    p->Release();
}

static void test_safe_addref_release(void)
{
    mock_unknown*   p = new mock_unknown();

    comstl__safe_addref(NULL);
    comstl__safe_release(NULL);

    comstl__safe_addref(p);
    TEST_UINT_EQ(2u, p->m_ref);
    comstl__safe_release(p);
    p->Release();
}

static void test_release_set_null(void)
{
    mock_unknown*   p = new mock_unknown();

    comstl::release_set_null(p);
    TEST_PTR_EQ(NULL, p);

    comstl::release_set_null(p);
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
