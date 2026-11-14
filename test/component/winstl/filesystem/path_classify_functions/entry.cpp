/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/winstl/filesystem/path_classify_functions/entry.cpp
 *
 * Purpose: Component-tests for `filesystem/path_classify_functions`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/filesystem/path_classify_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_EMPTY();
    static void TEST_RELATIVE();
    static void TEST_DRIVE_ROOTED();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_EMPTY);
        XTESTS_RUN_CASE(TEST_RELATIVE);
        XTESTS_RUN_CASE(TEST_DRIVE_ROOTED);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_EMPTY()
{
    TEST_INT_EQ(static_cast<int>(WinSTL_C_PathType_Empty), static_cast<int>(winstl_C_path_classify_m("", 0, 0, NULL)));
}

static void TEST_RELATIVE()
{
    TEST_INT_EQ(static_cast<int>(WinSTL_C_PathType_Relative), static_cast<int>(winstl_C_path_classify_m("foo/bar", 7, 0, NULL)));
}

static void TEST_DRIVE_ROOTED()
{
    TEST_INT_EQ(static_cast<int>(WinSTL_C_PathType_DriveLetterRooted), static_cast<int>(winstl_C_path_classify_m("C:/windows", 10, 0, NULL)));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
