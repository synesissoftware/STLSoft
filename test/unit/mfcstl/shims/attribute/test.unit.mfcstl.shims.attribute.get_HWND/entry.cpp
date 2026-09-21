/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.shims.attribute.get_HWND/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::get_HWND` attribute shims.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/shims/attribute/get_HWND.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_null_hwnd_reference(void);
    static void TEST_null_hwnd_pointer(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.shims.attribute.get_HWND", verbosity))
    {
        XTESTS_RUN_CASE(TEST_null_hwnd_reference);
        XTESTS_RUN_CASE(TEST_null_hwnd_pointer);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_null_hwnd_reference()
{
    CWnd w;

    TEST_PTR_EQ(NULL, mfcstl::get_HWND(w));
}

static void TEST_null_hwnd_pointer()
{
    CWnd w;

    TEST_PTR_EQ(NULL, mfcstl::get_HWND(&w));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
