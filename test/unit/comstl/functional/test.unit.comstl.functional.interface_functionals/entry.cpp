/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.functional.interface_functionals/entry.cpp
 *
 * Purpose: Unit-tests for COM interface functionals.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/functional/interface_functionals.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include "../../helpers/mock_unknown.hpp"

#include <stdlib.h>

namespace {

using test_comstl::mock_unknown;

static void test_interface_addref_release(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.functional.interface_functionals", verbosity))
    {
        XTESTS_RUN_CASE(test_interface_addref_release);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_interface_addref_release(void)
{
    comstl::interface_addref<IUnknown>  addref_fn;
    comstl::interface_release<IUnknown> release_fn;
    mock_unknown*                       p = new mock_unknown();

    addref_fn(p);
    TEST_UINT_EQ(2u, p->m_ref);

    release_fn(p);
    TEST_UINT_EQ(1u, p->m_ref);

    release_fn(NULL);
    addref_fn(NULL);

    p->Release();
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
