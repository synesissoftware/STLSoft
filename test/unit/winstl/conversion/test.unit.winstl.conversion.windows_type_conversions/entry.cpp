/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.conversion.windows_type_conversions/entry.cpp
 *
 * Purpose: Unit-tests for `conversion/windows_type_conversions`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/conversion/windows_type_conversions.hpp>
#include <windows.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_WPARAM2HWND(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.conversion.windows_type_conversions", verbosity))
    {
        XTESTS_RUN_CASE(test_WPARAM2HWND);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_WPARAM2HWND(void)
{
    HWND const hwnd = WPARAM2HWND()(static_cast<WPARAM>(42));
    TEST_PTR_EQ(reinterpret_cast<HWND>(42), hwnd);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
