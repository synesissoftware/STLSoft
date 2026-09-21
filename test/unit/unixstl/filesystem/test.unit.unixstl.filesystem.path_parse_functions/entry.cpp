/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.filesystem.path_parse_functions/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/path_parse_functions.h`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/filesystem/path_parse_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_find_first_separator(void);
    static void test_find_last_separator(void);
    static void test_no_separator(void);
    static void test_bounded_search(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.path_parse_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_find_first_separator);
        XTESTS_RUN_CASE(test_find_last_separator);
        XTESTS_RUN_CASE(test_no_separator);
        XTESTS_RUN_CASE(test_bounded_search);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_find_first_separator()
{
    char const path[] = "dir/sub/file";

    TEST_PTR_EQ(path + 3, unixstl_C_find_first_path_name_separator_m(path));
    TEST_PTR_EQ(path + 3, unixstl::find_first_path_name_separator(path));
}

static void test_find_last_separator()
{
    char const path[] = "dir/sub/file";

    TEST_PTR_EQ(path + 7, unixstl_C_find_last_path_name_separator_m(path));
    TEST_PTR_EQ(path + 7, unixstl::find_last_path_name_separator(path));
}

static void test_no_separator()
{
    char const path[] = "fileonly";

    TEST_PTR_EQ(NULL, unixstl_C_find_first_path_name_separator_m(path));
    TEST_PTR_EQ(NULL, unixstl_C_find_last_path_name_separator_m(path));
}

static void test_bounded_search()
{
    char const path[] = "a/b/c";
    size_t const len = 3; /* "a/b" */

    TEST_PTR_EQ(path + 1, unixstl_C_find_first_path_name_separator_len_m(path, len));
    TEST_PTR_EQ(path + 1, unixstl_C_find_last_path_name_separator_len_m(path, len));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
