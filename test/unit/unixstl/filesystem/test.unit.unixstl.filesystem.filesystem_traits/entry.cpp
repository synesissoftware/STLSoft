/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.filesystem.filesystem_traits/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/filesystem_traits.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/filesystem_traits.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>
#include <string.h>


namespace {

typedef unixstl::filesystem_traits<char> fs_traits_t;

static unixstl::path_classification_t classify_path(char const* path)
{
    unixstl::path_classification_results_m_t results = {};

    return static_cast<unixstl::path_classification_t>(
        fs_traits_t::path_classify(path, ::strlen(path), UNIXSTL_PATH_CLASSIFY_F_NONE, &results));
}

static void test_path_separators()
{
    TEST_CHAR_EQ('/', fs_traits_t::path_name_separator());
    TEST_CHAR_EQ(':', fs_traits_t::path_separator());
}

static void test_path_is_rooted()
{
    TEST_BOOLEAN_TRUE(fs_traits_t::path_is_rooted(classify_path("/")));
    TEST_BOOLEAN_TRUE(fs_traits_t::path_is_rooted(classify_path("/usr")));
    TEST_BOOLEAN_FALSE(fs_traits_t::path_is_rooted(classify_path("relative")));
}

static void test_starts_with_dots()
{
    TEST_BOOLEAN_TRUE(fs_traits_t::starts_with_dots("."));
    TEST_BOOLEAN_TRUE(fs_traits_t::starts_with_dots(".."));
    TEST_BOOLEAN_FALSE(fs_traits_t::starts_with_dots("file"));
}

static void test_ensure_and_remove_dir_end()
{
    char buf1[8] = "dir";
    fs_traits_t::ensure_dir_end(buf1);
    TEST_CHAR_EQ('/', buf1[3]);
    TEST_CHAR_EQ('\0', buf1[4]);

    char buf2[] = "dir/";
    fs_traits_t::remove_dir_end(buf2);
    TEST_MS_EQ("dir", buf2);
}

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.filesystem_traits", verbosity))
    {
        XTESTS_RUN_CASE(test_path_separators);
        XTESTS_RUN_CASE(test_path_is_rooted);
        XTESTS_RUN_CASE(test_starts_with_dots);
        XTESTS_RUN_CASE(test_ensure_and_remove_dir_end);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
