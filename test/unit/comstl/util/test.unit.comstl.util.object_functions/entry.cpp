/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.object_functions/entry.cpp
 *
 * Purpose: Unit-tests for COM object identity helpers.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/util/object_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include "../../helpers/mock_unknown.hpp"
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_get_object_identity_null_args(void);
    static void test_is_same_object(void);
    static void test_is_interface_implemented(void);
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

    if (XTESTS_START_RUNNER("test.unit.comstl.util.object_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_get_object_identity_null_args);
        XTESTS_RUN_CASE(test_is_same_object);
        XTESTS_RUN_CASE(test_is_interface_implemented);

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

static void test_get_object_identity_null_args(void)
{
    mock_unknown    obj;
    LPUNKNOWN       identity = NULL;

    TEST_INT_EQ((int)E_POINTER, (int)comstl_C_get_object_identity(NULL, &identity));
    TEST_INT_EQ((int)E_INVALIDARG, (int)comstl_C_get_object_identity(&obj, NULL));

    TEST_INT_EQ((int)S_OK, (int)comstl_C_get_object_identity(&obj, &identity));
    TEST_PTR_NE(NULL, identity);
    identity->Release();
}

static void test_is_same_object(void)
{
    mock_unknown    obj1;
    mock_unknown    obj2;
  mock_unknown*   p1 = &obj1;
  mock_unknown*   p2 = &obj2;

    TEST_INT_EQ((int)S_OK, (int)comstl_C_is_same_object(p1, p1));
    TEST_INT_EQ((int)S_FALSE, (int)comstl_C_is_same_object(p1, p2));
    TEST_INT_EQ((int)E_POINTER, (int)comstl_C_is_same_object(NULL, p1));
}

static void test_is_interface_implemented(void)
{
    mock_unknown    obj;

    TEST_INT_EQ((int)S_OK, (int)comstl_C_is_interface_implemented(&obj, IID_IUnknown));
    TEST_INT_EQ((int)E_NOINTERFACE, (int)comstl_C_is_interface_implemented(&obj, IID_IDispatch));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
