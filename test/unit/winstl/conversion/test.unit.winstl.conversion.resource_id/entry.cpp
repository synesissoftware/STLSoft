/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.conversion.resource_id/entry.cpp
 *
 * Purpose: Unit-tests for `conversion/resource_id`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/conversion/resource_id.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_make_resource_id(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.conversion.resource_id", verbosity))
    {
        XTESTS_RUN_CASE(test_make_resource_id);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_make_resource_id(void)
{
    winstl::resource_id const rs(MAKEINTRESOURCE(1234));
    TEST_PTR_NE(NULL, rs);
    TEST_INT_EQ(1234, static_cast<int>(reinterpret_cast<UINT_PTR>(rs)));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
