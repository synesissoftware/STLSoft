/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.initialisers/entry.cpp
 *
 * Purpose: Unit-tests for COM/OLE initialiser RAII classes.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/util/initialisers.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_ole_init_nothrow(void);
    static void test_com_init_nothrow(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.util.initialisers", verbosity))
    {
        XTESTS_RUN_CASE(test_ole_init_nothrow);
        XTESTS_RUN_CASE(test_com_init_nothrow);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_ole_init_nothrow(void)
{
    comstl::ole_init_nothrow  init;

    TEST_BOOLEAN_TRUE(init.is_initialised());
    TEST_BOOLEAN_FALSE(!init);
    TEST_INT_EQ((int)S_OK, (int)init.get_HRESULT());
}

static void test_com_init_nothrow(void)
{
    comstl::com_init_nothrow  init;

    TEST_BOOLEAN_TRUE(init.is_initialised());
    TEST_INT_EQ((int)S_OK, (int)init.get_HRESULT());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
