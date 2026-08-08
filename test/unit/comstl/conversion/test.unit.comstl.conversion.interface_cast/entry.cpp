/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.conversion.interface_cast/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::interface_cast` helpers.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/conversion/interface_cast.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>
#include <stlsoft/smartptr/ref_ptr.hpp>

#include "../../helpers/mock_unknown.hpp"

#include <stdlib.h>

namespace {

using test_comstl::mock_unknown;

static void test_interface_cast_test(void);
static void test_try_interface_cast(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.conversion.interface_cast", verbosity))
    {
        XTESTS_RUN_CASE(test_interface_cast_test);
        XTESTS_RUN_CASE(test_try_interface_cast);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_interface_cast_test(void)
{
    mock_unknown  obj;

    TEST_BOOLEAN_TRUE(comstl::interface_cast_test<IUnknown>(static_cast<IUnknown*>(&obj)));
    TEST_BOOLEAN_FALSE(comstl::interface_cast_test<IDispatch>(static_cast<IUnknown*>(&obj)));
}

static void test_try_interface_cast(void)
{
    mock_unknown  obj;
    stlsoft::ref_ptr<IUnknown>  punk = comstl::try_interface_cast<IUnknown>(static_cast<IUnknown*>(&obj));

    TEST_BOOLEAN_FALSE(punk.empty());
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
