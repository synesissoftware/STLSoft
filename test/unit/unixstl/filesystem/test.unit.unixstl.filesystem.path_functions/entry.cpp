/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.filesystem.path_functions/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/path_functions.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/filesystem/path_functions.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_aggregate_includes_path_parse(void);
    static void test_aggregate_includes_path_classify(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.path_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_aggregate_includes_path_parse);
        XTESTS_RUN_CASE(test_aggregate_includes_path_classify);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_aggregate_includes_path_parse()
{
    char const path[] = "a/b";

    TEST_PTR_EQ(path + 1, unixstl::find_first_path_name_separator(path));
}

static void test_aggregate_includes_path_classify()
{
    unixstl_C_path_classification_results_m_t results = {};

    int const r = unixstl_C_path_classify_m("file.txt", 8, UNIXSTL_PATH_CLASSIFY_F_NONE, &results);

    TEST_INT_EQ((int)UNIXSTL_C_PathType_Relative, r);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
