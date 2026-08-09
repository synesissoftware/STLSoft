/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.filesystem.directory_functions/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/filesystem/directory_functions.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/filesystem/directory_functions.hpp>
#include <unixstl/filesystem/path.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>
#include <stlsoft/stlsoft.h>
#include <sys/stat.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_create_directory_recurse(void);
    static void test_remove_directory_recurse(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.filesystem.directory_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_create_directory_recurse);
        XTESTS_RUN_CASE(test_remove_directory_recurse);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

typedef unixstl::filesystem_traits<char> fs_traits_t;
using xtests::cpp::util::temp_directory;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_create_directory_recurse()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);

    unixstl::path_a sub(td.c_str());
    sub /= "a/b/c";

    TEST_BOOLEAN_TRUE(unixstl::create_directory_recurse(sub.c_str()));

    struct stat st;
    TEST_INT_EQ(0, ::stat(sub.c_str(), &st));
    TEST_BOOLEAN_TRUE(S_ISDIR(st.st_mode));
}

static void test_remove_directory_recurse()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);

    unixstl::path_a sub(td.c_str());
    sub /= "remove-me";

    TEST_BOOLEAN_TRUE(fs_traits_t::create_directory(sub.c_str()));
    TEST_BOOLEAN_TRUE(unixstl::remove_directory_recurse(sub.c_str()));
    TEST_BOOLEAN_FALSE(fs_traits_t::file_exists(sub.c_str()));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
