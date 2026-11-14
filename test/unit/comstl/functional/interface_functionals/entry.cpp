/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/functional/interface_functionals/entry.cpp
 *
 * Purpose: Unit-tests for COM interface functionals.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/functional/interface_functionals.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include "../../helpers/mock_unknown.hpp"
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_INTERFACE_AddRef_Release();
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
        XTESTS_RUN_CASE(TEST_INTERFACE_AddRef_Release);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

using test_comstl::mock_unknown;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_INTERFACE_AddRef_Release()
{
    comstl::interface_addref<IUnknown>  addref_fn;
    comstl::interface_release<IUnknown> release_fn;
    mock_unknown*                       p = new mock_unknown();

    addref_fn(p);
    TEST_INT_EQ(2u, p->m_ref);

    release_fn(p);
    TEST_INT_EQ(1u, p->m_ref);

    release_fn(NULL);
    addref_fn(NULL);

    p->Release();
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
