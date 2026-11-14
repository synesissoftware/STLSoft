/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/smartptr/interface_ptr/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::interface_ptr`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/smartptr/interface_ptr.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include "../../helpers/mock_unknown.hpp"
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CONSTRUCTION_AND_Release();
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
        XTESTS_RUN_CASE(TEST_CONSTRUCTION_AND_Release);
        XTESTS_RUN_CASE(TEST_ATTACH_DETACH);

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

static void TEST_CONSTRUCTION_AND_Release()
{
    mock_unknown*                   raw = new mock_unknown();
    comstl::interface_ptr<IUnknown> ptr(raw, false);

    TEST_BOOLEAN_FALSE(ptr.empty());
    TEST_PTR_EQ(raw, ptr.get_interface_ptr());
}

static void TEST_ATTACH_DETACH()
{
    mock_unknown*                   raw = new mock_unknown();
    comstl::interface_ptr<IUnknown> ptr;

    ptr.set(raw, false);
    TEST_PTR_EQ(raw, ptr.get_interface_ptr());

    IUnknown* detached = ptr.detach();
    TEST_PTR_EQ(raw, detached);
    TEST_PTR_EQ(NULL, ptr.get_interface_ptr());

    detached->Release();
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
