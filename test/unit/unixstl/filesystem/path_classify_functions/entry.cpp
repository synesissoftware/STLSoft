/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/unixstl/filesystem/path_classify_functions/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/path_classify_functions.h`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/filesystem/path_classify_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_EMPTY_PATH();
    static void TEST_RELATIVE_PATH();
    static void TEST_SLASH_ROOTED();
    static void TEST_HOME_ROOTED_WITH_FLAG();
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
        XTESTS_RUN_CASE(TEST_EMPTY_PATH);
        XTESTS_RUN_CASE(TEST_RELATIVE_PATH);
        XTESTS_RUN_CASE(TEST_SLASH_ROOTED);
        XTESTS_RUN_CASE(TEST_HOME_ROOTED_WITH_FLAG);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_EMPTY_PATH()
{
    unixstl_C_path_classification_results_m_t results = {};

    int const r = unixstl_C_path_classify_m("", 0, UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ((int)UNIXSTL_C_PathType_Empty, r);
}

static void TEST_RELATIVE_PATH()
{
    unixstl_C_path_classification_results_m_t results = {};

    char const path[] = "dir/file.txt";
    int const r = unixstl_C_path_classify_m(path, strlen(path), UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ((int)UNIXSTL_C_PathType_Relative, r);
    TEST_INT_GE(1u, results.numDirectoryParts);
}

static void TEST_SLASH_ROOTED()
{
    unixstl_C_path_classification_results_m_t results = {};

    char const path[] = "/usr/bin";
    int const r = unixstl_C_path_classify_m(path, strlen(path), UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ((int)UNIXSTL_C_PathType_SlashRooted, r);
}

static void TEST_HOME_ROOTED_WITH_FLAG()
{
    unixstl_C_path_classification_results_m_t results = {};

    char const path[] = "~/projects";
    int const r = unixstl_C_path_classify_m(path, strlen(path), UNIXSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME, &results);

    TEST_INT_EQ((int)UNIXSTL_C_PathType_HomeRooted, r);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
