/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/unixstl/filesystem/path_parse_functions/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/path_parse_functions.h`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
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

    static void TEST_FIND_FIRST_SEPARATOR();
    static void TEST_FIND_LAST_SEPARATOR();
    static void TEST_NO_SEPARATOR();
    static void TEST_BOUNDED_SEARCH();
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
        XTESTS_RUN_CASE(TEST_FIND_FIRST_SEPARATOR);
        XTESTS_RUN_CASE(TEST_FIND_LAST_SEPARATOR);
        XTESTS_RUN_CASE(TEST_NO_SEPARATOR);
        XTESTS_RUN_CASE(TEST_BOUNDED_SEARCH);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_FIND_FIRST_SEPARATOR()
{
    char const path[] = "dir/sub/file";

    TEST_PTR_EQ(path + 3, unixstl_C_find_first_path_name_separator_m(path));
    TEST_PTR_EQ(path + 3, unixstl::find_first_path_name_separator(path));
}

static void TEST_FIND_LAST_SEPARATOR()
{
    char const path[] = "dir/sub/file";

    TEST_PTR_EQ(path + 7, unixstl_C_find_last_path_name_separator_m(path));
    TEST_PTR_EQ(path + 7, unixstl::find_last_path_name_separator(path));
}

static void TEST_NO_SEPARATOR()
{
    char const path[] = "fileonly";

    TEST_PTR_EQ(NULL, unixstl_C_find_first_path_name_separator_m(path));
    TEST_PTR_EQ(NULL, unixstl_C_find_last_path_name_separator_m(path));
}

static void TEST_BOUNDED_SEARCH()
{
    char const path[] = "a/b/c";
    size_t const len = 3; /* "a/b" */

    TEST_PTR_EQ(path + 1, unixstl_C_find_first_path_name_separator_len_m(path, len));
    TEST_PTR_EQ(path + 1, unixstl_C_find_last_path_name_separator_len_m(path, len));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
