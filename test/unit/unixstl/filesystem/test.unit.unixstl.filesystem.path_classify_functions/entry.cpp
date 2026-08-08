/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.filesystem.path_classify_functions/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/path_classify_functions.h`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/path_classify_functions.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_empty_path()
{
    unixstl_C_path_classification_results_m_t results = {};

    int const r = unixstl_C_path_classify_m("", 0, UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ((int)UNIXSTL_C_PathType_Empty, r);
}

static void test_relative_path()
{
    unixstl_C_path_classification_results_m_t results = {};

    char const path[] = "dir/file.txt";
    int const r = unixstl_C_path_classify_m(path, strlen(path), UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ((int)UNIXSTL_C_PathType_Relative, r);
    TEST_INT_GE(1u, results.numDirectoryParts);
}

static void test_slash_rooted()
{
    unixstl_C_path_classification_results_m_t results = {};

    char const path[] = "/usr/bin";
    int const r = unixstl_C_path_classify_m(path, strlen(path), UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ((int)UNIXSTL_C_PathType_SlashRooted, r);
}

static void test_home_rooted_with_flag()
{
    unixstl_C_path_classification_results_m_t results = {};

    char const path[] = "~/projects";
    int const r = unixstl_C_path_classify_m(path, strlen(path), UNIXSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME, &results);

    TEST_INT_EQ((int)UNIXSTL_C_PathType_HomeRooted, r);
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.path_classify_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_empty_path);
        XTESTS_RUN_CASE(test_relative_path);
        XTESTS_RUN_CASE(test_slash_rooted);
        XTESTS_RUN_CASE(test_home_rooted_with_flag);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
