/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.interface_traits/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::IID_traits`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/util/interface_traits.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_iunknown_iid(void);
static void test_idispatch_iid(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.util.interface_traits", verbosity))
    {
        XTESTS_RUN_CASE(test_iunknown_iid);
        XTESTS_RUN_CASE(test_idispatch_iid);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_iunknown_iid(void)
{
    TEST_BOOLEAN_TRUE(IsEqualGUID(comstl::IID_traits<IUnknown>::iid(), IID_IUnknown));
}

static void test_idispatch_iid(void)
{
    TEST_BOOLEAN_TRUE(IsEqualGUID(comstl::IID_traits<IDispatch>::iid(), IID_IDispatch));
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
