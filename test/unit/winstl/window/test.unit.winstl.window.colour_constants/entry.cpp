/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.window.colour_constants/entry.cpp
 *
 * Purpose: Unit-tests for `window/colour_constants`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/window/colour_constants.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_rgb_macro(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.window.colour_constants", verbosity))
    {
        XTESTS_RUN_CASE(test_rgb_macro);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_rgb_macro(void)
{
    COLORREF c = RGB(0x12, 0x34, 0x56);
    TEST_INT_EQ(0x00563412, static_cast<int>(c));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
