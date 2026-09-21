/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.inetstl.filesystem.filesystem_traits/entry.cpp
 *
 * Purpose: Unit-tests for `inetstl::filesystem_traits`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <inetstl/filesystem/filesystem_traits.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_is_dots(void);
    static void TEST_ensure_dir_end(void);
    static void TEST_has_dir_end(void);
    static void TEST_remove_dir_end(void);
    static void TEST_is_path_rooted(void);
    static void TEST_is_path_absolute(void);
    static void TEST_is_path_name_separator(void);
    static void TEST_path_separators(void);
    static void TEST_pattern_all(void);
    static void TEST_stat_data_attributes(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.inetstl.filesystem.filesystem_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_is_dots);
        XTESTS_RUN_CASE(TEST_ensure_dir_end);
        XTESTS_RUN_CASE(TEST_has_dir_end);
        XTESTS_RUN_CASE(TEST_remove_dir_end);
        XTESTS_RUN_CASE(TEST_is_path_rooted);
        XTESTS_RUN_CASE(TEST_is_path_absolute);
        XTESTS_RUN_CASE(TEST_is_path_name_separator);
        XTESTS_RUN_CASE(TEST_path_separators);
        XTESTS_RUN_CASE(TEST_pattern_all);
        XTESTS_RUN_CASE(TEST_stat_data_attributes);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

typedef inetstl::filesystem_traits<char>                filesystem_traits_m_t;
    typedef inetstl::filesystem_traits<wchar_t>             filesystem_traits_w_t;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_is_dots()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_dots(""));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_dots("a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_dots("."));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_dots(".."));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_dots("./"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_dots("../"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_dots("..."));
    }

    {
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_dots(L""));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_dots(L"a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_dots(L"."));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_dots(L".."));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_dots(L"./"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_dots(L"../"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_dots(L"..."));
    }
}

static void TEST_ensure_dir_end()
{
    {
        char dirname[] = "abc";

        filesystem_traits_m_t::ensure_dir_end(dirname);

        TEST_MS_EQ("abc/", dirname);
    }

    {
        char dirname[] = "abc/";

        filesystem_traits_m_t::ensure_dir_end(dirname);

        TEST_MS_EQ("abc/", dirname);
    }

    {
        char dirname[] = "abc\\def";

        filesystem_traits_m_t::ensure_dir_end(dirname);

        TEST_MS_EQ("abc\\def\\", dirname);
    }

    {
        wchar_t dirname[] = L"abc";

        filesystem_traits_w_t::ensure_dir_end(dirname);

        TEST_WS_EQ(L"abc/", dirname);
    }

    {
        wchar_t dirname[] = L"abc\\def";

        filesystem_traits_w_t::ensure_dir_end(dirname);

        TEST_WS_EQ(L"abc\\def\\", dirname);
    }
}

static void TEST_has_dir_end()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::has_dir_end(""));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::has_dir_end("abc"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::has_dir_end("abc/"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::has_dir_end("abc\\"));
    }

    {
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::has_dir_end(L""));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::has_dir_end(L"abc"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::has_dir_end(L"abc/"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::has_dir_end(L"abc\\"));
    }
}

static void TEST_remove_dir_end()
{
    {
        char dirname[] = "abc/";

        filesystem_traits_m_t::remove_dir_end(dirname);

        TEST_MS_EQ("abc", dirname);
    }

    {
        char dirname[] = "abc";

        filesystem_traits_m_t::remove_dir_end(dirname);

        TEST_MS_EQ("abc", dirname);
    }

    {
        wchar_t dirname[] = L"abc/";

        filesystem_traits_w_t::remove_dir_end(dirname);

        TEST_WS_EQ(L"abc", dirname);
    }
}

static void TEST_is_path_rooted()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_rooted(""));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_rooted("abc"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_rooted("/abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_rooted("\\abc"));
    }

    {
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_path_rooted(L""));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_path_rooted(L"abc"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_path_rooted(L"/abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_path_rooted(L"\\abc"));
    }
}

static void TEST_is_path_absolute()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_absolute("abc"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_absolute("/abc"));
    }

    {
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_path_absolute(L"abc"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_path_absolute(L"/abc"));
    }
}

static void TEST_is_path_name_separator()
{
    {
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_name_separator('/'));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_name_separator('\\'));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_name_separator('a'));
    }

    {
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_path_name_separator(L'/'));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_path_name_separator(L'\\'));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_path_name_separator(L'a'));
    }
}

static void TEST_path_separators()
{
    {
        TEST_CHAR_EQ(';', filesystem_traits_m_t::path_separator());
        TEST_CHAR_EQ('/', filesystem_traits_m_t::path_name_separator());
    }

    {
        TEST_CHAR_EQ(L';', filesystem_traits_w_t::path_separator());
        TEST_CHAR_EQ(L'/', filesystem_traits_w_t::path_name_separator());
    }
}

static void TEST_pattern_all()
{
    TEST_MS_EQ("*", filesystem_traits_m_t::pattern_all());
    TEST_WS_EQ(L"*", filesystem_traits_w_t::pattern_all());
}

static void TEST_stat_data_attributes()
{
    {
        WIN32_FIND_DATAA    fd;

        memset(&fd, 0, sizeof(fd));
        fd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_directory(&fd));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_file(&fd));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_readonly(&fd));
    }

    {
        WIN32_FIND_DATAA    fd;

        memset(&fd, 0, sizeof(fd));
        fd.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_directory(&fd));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_file(&fd));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_readonly(&fd));
    }

    {
        WIN32_FIND_DATAA    fd;

        memset(&fd, 0, sizeof(fd));
        fd.dwFileAttributes = FILE_ATTRIBUTE_READONLY;

        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_file(&fd));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_readonly(&fd));
    }

    {
        WIN32_FIND_DATAW    fd;

        memset(&fd, 0, sizeof(fd));
        fd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_directory(&fd));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_file(&fd));
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
