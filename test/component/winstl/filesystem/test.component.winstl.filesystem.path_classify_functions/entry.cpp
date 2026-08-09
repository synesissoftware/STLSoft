/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.filesystem.path_classify_functions/entry.cpp
 *
 * Purpose: Component-tests for `filesystem/path_classify_functions`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/filesystem/path_classify_functions.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace {

static void test_empty(void);
static void test_relative(void);
static void test_drive_rooted(void);

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.filesystem.path_classify_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_empty);
        XTESTS_RUN_CASE(test_relative);
        XTESTS_RUN_CASE(test_drive_rooted);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_empty(void)
{
    TEST_INT_EQ(WinSTL_C_PathType_Empty, winstl_C_path_classify_m("", 0, 0, NULL));
}

static void test_relative(void)
{
    TEST_INT_EQ(WinSTL_C_PathType_Relative, winstl_C_path_classify_m("foo/bar", 7, 0, NULL));
}

static void test_drive_rooted(void)
{
    TEST_INT_EQ(WinSTL_C_PathType_DriveLetterRooted, winstl_C_path_classify_m("C:/windows", 10, 0, NULL));
}

} // anonymous namespace
