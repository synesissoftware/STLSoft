/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.shims.conversion.to_DATE.DATE/entry.cpp
 *
 * Purpose: Unit-tests for `shims/conversion/to_DATE/DATE`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/util/struct_initialisers.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_zero_init(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.shims.conversion.to_DATE.DATE", verbosity))
    {
        XTESTS_RUN_CASE(test_zero_init);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_zero_init(void)
{
    SYSTEMTIME st;
    winstl::init_struct(st);
    TEST_INT_EQ(0, static_cast<int>(st.wYear));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
