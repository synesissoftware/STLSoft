/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.filesystem.filesystem_traits/entry.cpp
 *
 * Purpose: Unit-tests for `winstl::filesystem_traits`.
 *
 * Created: 31st December 2008
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/filesystem/filesystem_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/memory/auto_buffer.hpp>

/* Standard C++ header files */
#include <vector>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_basename_is_dots(); // => `basename_is_dots()` => `basename_is_dots()`
    static void TEST_starts_with_dots();

    static void TEST_ensure_dir_end_1(); // TODO: rename to `dirname_ensure_pns()`
    static void TEST_ensure_dir_end_4(); // TODO: rename to `dirname_ensure_pns()`

    static void TEST_has_dir_end_1();
    static void TEST_has_dir_end_2();

    static void TEST_remove_dir_end_1();
    static void TEST_remove_dir_end_3();

    static void TEST_find_last_path_name_separator();
    static void TEST_find_next_path_name_separator();

    static void TEST_path_is_rooted_1();
    static void TEST_path_is_rooted_2();
    //static void TEST_path_is_rooted_3();
    static void TEST_path_is_absolute_1();
    static void TEST_path_is_absolute_2();
    static void TEST_path_is_UNC_1();
    static void TEST_path_is_UNC_2();

    static void TEST_is_path_name_separator();
    static void TEST_is_root_designator();
    static void TEST_path_separator();
    static void TEST_path_name_separator();
    static void TEST_path_max();
    static void TEST_pattern_all();
    static void TEST_patterns_all();

    static void TEST_pathComparisonIsCaseSensitive();

    static void TEST_str_fs_compare();
    static void TEST_str_fs_n_compare();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSE_HELP_OR_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.filesystem.filesystem_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_basename_is_dots);
        XTESTS_RUN_CASE(TEST_starts_with_dots);

        XTESTS_RUN_CASE(TEST_ensure_dir_end_1);
        XTESTS_RUN_CASE(TEST_ensure_dir_end_4);

        XTESTS_RUN_CASE(TEST_has_dir_end_1);
        XTESTS_RUN_CASE(TEST_has_dir_end_2);

        XTESTS_RUN_CASE(TEST_remove_dir_end_1);
        XTESTS_RUN_CASE(TEST_remove_dir_end_3);

        XTESTS_RUN_CASE(TEST_path_is_absolute_1);
        XTESTS_RUN_CASE(TEST_path_is_absolute_2);

        XTESTS_RUN_CASE(TEST_find_last_path_name_separator);
        XTESTS_RUN_CASE(TEST_find_next_path_name_separator);

        XTESTS_RUN_CASE(TEST_path_is_rooted_1);
        XTESTS_RUN_CASE(TEST_path_is_rooted_2);

        XTESTS_RUN_CASE(TEST_path_is_UNC_1);
        XTESTS_RUN_CASE(TEST_path_is_UNC_2);

        XTESTS_RUN_CASE(TEST_is_path_name_separator);
        XTESTS_RUN_CASE(TEST_is_root_designator);
        XTESTS_RUN_CASE(TEST_path_separator);
        XTESTS_RUN_CASE(TEST_path_name_separator);
        XTESTS_RUN_CASE(TEST_path_max);
        XTESTS_RUN_CASE(TEST_pattern_all);
        XTESTS_RUN_CASE(TEST_patterns_all);

        XTESTS_RUN_CASE(TEST_pathComparisonIsCaseSensitive);

        XTESTS_RUN_CASE(TEST_str_fs_compare);
        XTESTS_RUN_CASE(TEST_str_fs_n_compare);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::ss_size_t;
    typedef std::vector<char>                               vec_m_t;
    typedef std::vector<wchar_t>                            vec_w_t;
    typedef stlsoft::auto_buffer<char>                      ab_m_t;
    typedef stlsoft::auto_buffer<wchar_t>                   ab_w_t;
    typedef winstl::filesystem_traits<char>                 filesystem_traits_m_t;
    typedef winstl::filesystem_traits<wchar_t>              filesystem_traits_w_t;


static void TEST_basename_is_dots()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::basename_is_dots(""));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::basename_is_dots("a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::basename_is_dots("."));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::basename_is_dots(".."));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::basename_is_dots("./"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::basename_is_dots("../"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::basename_is_dots("./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::basename_is_dots("../abc"));
    }

    {
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::basename_is_dots(L""));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::basename_is_dots(L"a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::basename_is_dots(L"."));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::basename_is_dots(L".."));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::basename_is_dots(L"./"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::basename_is_dots(L"../"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::basename_is_dots(L"./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::basename_is_dots(L"../abc"));
    }
}

static void TEST_starts_with_dots()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::starts_with_dots(""));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::starts_with_dots("a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::starts_with_dots("a."));

        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::starts_with_dots("."));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::starts_with_dots("./"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::starts_with_dots(".a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::starts_with_dots("./a"));

        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::starts_with_dots(".."));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::starts_with_dots("../"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::starts_with_dots("..a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::starts_with_dots("../a"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::starts_with_dots("..."));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::starts_with_dots(".../"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::starts_with_dots("...."));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::starts_with_dots("..../"));
    }

    {
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::starts_with_dots(L""));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::starts_with_dots(L"a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::starts_with_dots(L"a."));

        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::starts_with_dots(L"."));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::starts_with_dots(L"./"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::starts_with_dots(L".a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::starts_with_dots(L"./a"));

        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::starts_with_dots(L".."));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::starts_with_dots(L"../"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::starts_with_dots(L"..a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::starts_with_dots(L"../a"));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::starts_with_dots(L"..."));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::starts_with_dots(L".../"));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::starts_with_dots(L"...."));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::starts_with_dots(L"..../"));
    }
}

static void TEST_ensure_dir_end_1()
{
    // empty string
    {
        // passing character array (char)
        {
            char        dirname[] = "\0";
            char*       r = filesystem_traits_m_t::ensure_dir_end(dirname);

            TEST_MS_EQ("", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

        // passing character array (wchar_t)
        {
            wchar_t     dirname[] = L"\0";
            wchar_t*    r = filesystem_traits_w_t::ensure_dir_end(dirname);

            TEST_WS_EQ(L"", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t          buff = { '\0' };
            ss_size_t const r = filesystem_traits_m_t::ensure_dir_end(buff);

            TEST_MS_EQ("", buff.data());
            TEST_INT_EQ(0, r);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t          buff = { '\0' };
            ss_size_t const r = filesystem_traits_w_t::ensure_dir_end(buff);

            TEST_WS_EQ(L"", buff.data());
            TEST_INT_EQ(0, r);
        }
#endif

        // passing resizeable buffer (vector<char>)
        {
            {
                vec_m_t         buff(0);
                ss_size_t const r = filesystem_traits_m_t::ensure_dir_end(buff);

                TEST_MS_EQ("", buff.data());
                TEST_INT_EQ(0, r);
            }

            {
                vec_m_t         buff(1);
                ss_size_t const r = filesystem_traits_m_t::ensure_dir_end(buff);

                TEST_MS_EQ("", buff.data());
                TEST_INT_EQ(0, r);
            }
        }

        // passing resizeable buffer (vector<char>)
        {
            {
                vec_w_t         buff(0);
                ss_size_t const r = filesystem_traits_w_t::ensure_dir_end(buff);

                TEST_WS_EQ(L"", buff.data());
                TEST_INT_EQ(0, r);
            }

            {
                vec_w_t         buff(1);
                ss_size_t const r = filesystem_traits_w_t::ensure_dir_end(buff);

                TEST_WS_EQ(L"", buff.data());
                TEST_INT_EQ(0, r);
            }
        }
    }

    // needs a slash
    {
        // passing character array (char)
        {
            char        dirname[] = "abc\0";
            char*       r = filesystem_traits_m_t::ensure_dir_end(dirname);

            TEST_MS_EQ("abc\\", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

        // passing character array (wchar_t)
        {
            wchar_t     dirname[] = L"abc\0";
            wchar_t*    r = filesystem_traits_w_t::ensure_dir_end(dirname);

            TEST_WS_EQ(L"abc\\", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t          buff = { 'a', 'b', 'c', '\0' };
            ss_size_t const r = filesystem_traits_m_t::ensure_dir_end(buff);

            TEST_MS_EQ("abc\\", buff.data());
            TEST_INT_EQ(4, r);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t          buff = { 'a', 'b', 'c', '\0' };
            ss_size_t const r = filesystem_traits_w_t::ensure_dir_end(buff);

            TEST_WS_EQ(L"abc\\", buff.data());
            TEST_INT_EQ(4, r);
        }

        // passing resizeable buffer (vector<char>)
        {
            vec_m_t         buff = { 'a', 'b', 'c', '\0' };
            ss_size_t const r = filesystem_traits_m_t::ensure_dir_end(buff);

            TEST_MS_EQ("abc\\", buff.data());
            TEST_INT_EQ(4, r);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            vec_w_t         buff = { 'a', 'b', 'c', '\0' };
            ss_size_t const r = filesystem_traits_w_t::ensure_dir_end(buff);

            TEST_WS_EQ(L"abc\\", buff.data());
            TEST_INT_EQ(4, r);
        }
#endif
    }

    // does not need a slash
    {
        // passing character array (char)
        {
            char        dirname[] = "abc\\";
            char*       r = filesystem_traits_m_t::ensure_dir_end(dirname);

            TEST_MS_EQ("abc\\", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

        // passing character array (wchar_t)
        {
            wchar_t     dirname[] = L"abc\\";
            wchar_t*    r = filesystem_traits_w_t::ensure_dir_end(dirname);

            TEST_WS_EQ(L"abc\\", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t          buff = { 'a', 'b', 'c', '\\', '\0' };
            ss_size_t const r = filesystem_traits_m_t::ensure_dir_end(buff);

            TEST_MS_EQ("abc\\", buff.data());
            TEST_INT_EQ(4, r);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t          buff = { 'a', 'b', 'c', '\\', '\0' };
            ss_size_t const r = filesystem_traits_w_t::ensure_dir_end(buff);

            TEST_WS_EQ(L"abc\\", buff.data());
            TEST_INT_EQ(4, r);
        }

        // passing resizeable buffer (vector<char>)
        {
            vec_m_t         buff = { 'a', 'b', 'c', '\\', '\0' };
            ss_size_t const r = filesystem_traits_m_t::ensure_dir_end(buff);

            TEST_MS_EQ("abc\\", buff.data());
            TEST_INT_EQ(4, r);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            vec_w_t         buff = { 'a', 'b', 'c', '\\', '\0' };
            ss_size_t const r = filesystem_traits_w_t::ensure_dir_end(buff);

            TEST_WS_EQ(L"abc\\", buff.data());
            TEST_INT_EQ(4, r);
        }
#endif
    }

    // has excess slash
    {
        // passing character array (char)
        {
            char        dirname[] = "abc\\\\";
            char*       r = filesystem_traits_m_t::ensure_dir_end(dirname);

            TEST_MS_EQ("abc\\\\", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

        // passing character array (wchar_t)
        {
            wchar_t     dirname[] = L"abc\\\\";
            wchar_t*    r = filesystem_traits_w_t::ensure_dir_end(dirname);

            TEST_WS_EQ(L"abc\\\\", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t          buff = { 'a', 'b', 'c', '\\', '\\', '\0' };
            ss_size_t const r = filesystem_traits_m_t::ensure_dir_end(buff);

            TEST_MS_EQ("abc\\\\", buff.data());
            TEST_INT_EQ(5, r);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t          buff = { 'a', 'b', 'c', '\\', '\\', '\0' };
            ss_size_t const r = filesystem_traits_w_t::ensure_dir_end(buff);

            TEST_WS_EQ(L"abc\\\\", buff.data());
            TEST_INT_EQ(5, r);
        }

        // passing resizeable buffer (vector<char>)
        {
            vec_m_t         buff = { 'a', 'b', 'c', '\\', '\\', '\0' };
            ss_size_t const r = filesystem_traits_m_t::ensure_dir_end(buff);

            TEST_MS_EQ("abc\\\\", buff.data());
            TEST_INT_EQ(5, r);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            vec_w_t         buff = { 'a', 'b', 'c', '\\', '\\', '\0' };
            ss_size_t const r = filesystem_traits_w_t::ensure_dir_end(buff);

            TEST_WS_EQ(L"abc\\\\", buff.data());
            TEST_INT_EQ(5, r);
        }
#endif
    }
}

static void TEST_ensure_dir_end_4()
{
}

static void TEST_has_dir_end_1()
{
    // empty string
    {
        // passing character array (char)
        {
            char    dirname[] = "\0";

            TEST_BOOLEAN_FALSE(filesystem_traits_m_t::has_dir_end(dirname));
        }

        // passing character array (wchar_t)
        {
            wchar_t dirname[] = L"\0";

            TEST_BOOLEAN_FALSE(filesystem_traits_w_t::has_dir_end(dirname));
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t  buff = { '\0' };

            TEST_BOOLEAN_FALSE(filesystem_traits_m_t::has_dir_end(buff));
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t  buff = { '\0' };

            TEST_BOOLEAN_FALSE(filesystem_traits_w_t::has_dir_end(buff));
        }
#endif

        // passing resizeable buffer (vector<char>)
        {
            {
                vec_m_t buff(0);

                TEST_BOOLEAN_FALSE(filesystem_traits_m_t::has_dir_end(buff));
            }

            {
                vec_m_t buff(1);

                TEST_BOOLEAN_FALSE(filesystem_traits_m_t::has_dir_end(buff));
            }
        }

        // passing resizeable buffer (vector<char>)
        {
            {
                vec_w_t buff(0);

                TEST_BOOLEAN_FALSE(filesystem_traits_w_t::has_dir_end(buff));
            }

            {
                vec_w_t buff(1);

                TEST_BOOLEAN_FALSE(filesystem_traits_w_t::has_dir_end(buff));
            }
        }
    }

    // needs a slash
    {
        // passing character array (char)
        {
            char    dirname[] = "abc\0";

            TEST_BOOLEAN_FALSE(filesystem_traits_m_t::has_dir_end(dirname));
        }

        // passing character array (wchar_t)
        {
            wchar_t dirname[] = L"abc\0";

            TEST_BOOLEAN_FALSE(filesystem_traits_w_t::has_dir_end(dirname));
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t  buff = { 'a', 'b', 'c', '\0' };

            TEST_BOOLEAN_FALSE(filesystem_traits_m_t::has_dir_end(buff));
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t  buff = { 'a', 'b', 'c', '\0' };

            TEST_BOOLEAN_FALSE(filesystem_traits_w_t::has_dir_end(buff));
        }

        // passing resizeable buffer (vector<char>)
        {
            vec_m_t buff = { 'a', 'b', 'c', '\0' };

            TEST_BOOLEAN_FALSE(filesystem_traits_m_t::has_dir_end(buff));
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            vec_w_t buff = { 'a', 'b', 'c', '\0' };

            TEST_BOOLEAN_FALSE(filesystem_traits_w_t::has_dir_end(buff));
        }
#endif
    }

    // does not need a slash
    {
        // passing character array (char)
        {
            char    dirname[] = "abc\\";

            TEST_BOOLEAN_TRUE(filesystem_traits_m_t::has_dir_end(dirname));
        }

        // passing character array (wchar_t)
        {
            wchar_t dirname[] = L"abc\\";

            TEST_BOOLEAN_TRUE(filesystem_traits_w_t::has_dir_end(dirname));
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t  buff = { 'a', 'b', 'c', '\\', '\0' };

            TEST_BOOLEAN_TRUE(filesystem_traits_m_t::has_dir_end(buff));
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t  buff = { 'a', 'b', 'c', '\\', '\0' };

            TEST_BOOLEAN_TRUE(filesystem_traits_w_t::has_dir_end(buff));
        }

        // passing resizeable buffer (vector<char>)
        {
            vec_m_t buff = { 'a', 'b', 'c', '\\', '\0' };

            TEST_BOOLEAN_TRUE(filesystem_traits_m_t::has_dir_end(buff));
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            vec_w_t buff = { 'a', 'b', 'c', '\\', '\0' };

            TEST_BOOLEAN_TRUE(filesystem_traits_w_t::has_dir_end(buff));
        }
#endif
    }

    // has excess slash
    {
        // passing character array (char)
        {
            char    dirname[] = "abc\\\\";

            TEST_BOOLEAN_TRUE(filesystem_traits_m_t::has_dir_end(dirname));
        }

        // passing character array (wchar_t)
        {
            wchar_t dirname[] = L"abc\\\\";

            TEST_BOOLEAN_TRUE(filesystem_traits_w_t::has_dir_end(dirname));
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t  buff = { 'a', 'b', 'c', '\\', '\\', '\0' };

            TEST_BOOLEAN_TRUE(filesystem_traits_m_t::has_dir_end(buff));
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t  buff = { 'a', 'b', 'c', '\\', '\\', '\0' };

            TEST_BOOLEAN_TRUE(filesystem_traits_w_t::has_dir_end(buff));
        }

        // passing resizeable buffer (vector<char>)
        {
            vec_m_t buff = { 'a', 'b', 'c', '\\', '\\', '\0' };

            TEST_BOOLEAN_TRUE(filesystem_traits_m_t::has_dir_end(buff));
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            vec_w_t buff = { 'a', 'b', 'c', '\\', '\\', '\0' };

            TEST_BOOLEAN_TRUE(filesystem_traits_w_t::has_dir_end(buff));
        }
#endif
    }
}

static void TEST_has_dir_end_2()
{
}

static void TEST_remove_dir_end_1()
{
    // empty string
    {
        // passing character array (char)
        {
            char        dirname[] = "\0";
            char*       r = filesystem_traits_m_t::remove_dir_end(dirname);

            TEST_MS_EQ("", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

        // passing character array (wchar_t)
        {
            wchar_t     dirname[] = L"\0";
            wchar_t*    r = filesystem_traits_w_t::remove_dir_end(dirname);

            TEST_WS_EQ(L"", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t          buff = { '\0' };
            ss_size_t const r = filesystem_traits_m_t::remove_dir_end(buff);

            TEST_MS_EQ("", buff.data());
            TEST_INT_EQ(0, r);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t          buff = { '\0' };
            ss_size_t const r = filesystem_traits_w_t::remove_dir_end(buff);

            TEST_WS_EQ(L"", buff.data());
            TEST_INT_EQ(0, r);
        }
#endif

        // passing resizeable buffer (vector<char>)
        {
            {
                vec_m_t         buff(0);
                ss_size_t const r = filesystem_traits_m_t::remove_dir_end(buff);

                TEST_MS_EQ("", buff.data());
                TEST_INT_EQ(0, r);
            }

            {
                vec_m_t         buff(1);
                ss_size_t const r = filesystem_traits_m_t::remove_dir_end(buff);

                TEST_MS_EQ("", buff.data());
                TEST_INT_EQ(0, r);
            }
        }

        // passing resizeable buffer (vector<char>)
        {
            {
                vec_w_t         buff(0);
                ss_size_t const r = filesystem_traits_w_t::remove_dir_end(buff);

                TEST_WS_EQ(L"", buff.data());
                TEST_INT_EQ(0, r);
            }

            {
                vec_w_t         buff(1);
                ss_size_t const r = filesystem_traits_w_t::remove_dir_end(buff);

                TEST_WS_EQ(L"", buff.data());
                TEST_INT_EQ(0, r);
            }
        }
    }

    // needs a slash
    {
        // passing character array (char)
        {
            char        dirname[] = "abc\0";
            char*       r = filesystem_traits_m_t::remove_dir_end(dirname);

            TEST_MS_EQ("abc", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

        // passing character array (wchar_t)
        {
            wchar_t     dirname[] = L"abc\0";
            wchar_t*    r = filesystem_traits_w_t::remove_dir_end(dirname);

            TEST_WS_EQ(L"abc", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t          buff = { 'a', 'b', 'c', '\0' };
            ss_size_t const r = filesystem_traits_m_t::remove_dir_end(buff);

            TEST_MS_EQ("abc", buff.data());
            TEST_INT_EQ(3, r);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t          buff = { 'a', 'b', 'c', '\0' };
            ss_size_t const r = filesystem_traits_w_t::remove_dir_end(buff);

            TEST_WS_EQ(L"abc", buff.data());
            TEST_INT_EQ(3, r);
        }

        // passing resizeable buffer (vector<char>)
        {
            vec_m_t         buff = { 'a', 'b', 'c', '\0' };
            ss_size_t const r = filesystem_traits_m_t::remove_dir_end(buff);

            TEST_MS_EQ("abc", buff.data());
            TEST_INT_EQ(3, r);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            vec_w_t         buff = { 'a', 'b', 'c', '\0' };
            ss_size_t const r = filesystem_traits_w_t::remove_dir_end(buff);

            TEST_WS_EQ(L"abc", buff.data());
            TEST_INT_EQ(3, r);
        }
#endif
    }

    // does not need a slash
    {
        // passing character array (char)
        {
            char        dirname[] = "abc\\";
            char*       r = filesystem_traits_m_t::remove_dir_end(dirname);

            TEST_MS_EQ("abc", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

        // passing character array (wchar_t)
        {
            wchar_t     dirname[] = L"abc\\";
            wchar_t*    r = filesystem_traits_w_t::remove_dir_end(dirname);

            TEST_WS_EQ(L"abc", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t          buff = { 'a', 'b', 'c', '\\', '\0' };
            ss_size_t const r = filesystem_traits_m_t::remove_dir_end(buff);

            TEST_MS_EQ("abc", buff.data());
            TEST_INT_EQ(3, r);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t          buff = { 'a', 'b', 'c', '\\', '\0' };
            ss_size_t const r = filesystem_traits_w_t::remove_dir_end(buff);

            TEST_WS_EQ(L"abc", buff.data());
            TEST_INT_EQ(3, r);
        }

        // passing resizeable buffer (vector<char>)
        {
            vec_m_t         buff = { 'a', 'b', 'c', '\\', '\0' };
            ss_size_t const r = filesystem_traits_m_t::remove_dir_end(buff);

            TEST_MS_EQ("abc", buff.data());
            TEST_INT_EQ(3, r);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            vec_w_t         buff = { 'a', 'b', 'c', '\\', '\0' };
            ss_size_t const r = filesystem_traits_w_t::remove_dir_end(buff);

            TEST_WS_EQ(L"abc", buff.data());
            TEST_INT_EQ(3, r);
        }
#endif
    }

    // has excess slash
    {
        // passing character array (char)
        {
            char        dirname[] = "abc\\\\";
            char*       r = filesystem_traits_m_t::remove_dir_end(dirname);

            TEST_MS_EQ("abc", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

        // passing character array (wchar_t)
        {
            wchar_t     dirname[] = L"abc\\\\";
            wchar_t*    r = filesystem_traits_w_t::remove_dir_end(dirname);

            TEST_WS_EQ(L"abc", dirname);
            TEST_PTR_EQ(dirname + 0, r);
        }

#if __cplusplus >= 201103L

        // passing resizeable buffer (auto_buffer<char>)
        {
            ab_m_t          buff = { 'a', 'b', 'c', '\\', '\\', '\0' };
            ss_size_t const r = filesystem_traits_m_t::remove_dir_end(buff);

            TEST_MS_EQ("abc", buff.data());
            TEST_INT_EQ(3, r);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ab_w_t          buff = { 'a', 'b', 'c', '\\', '\\', '\0' };
            ss_size_t const r = filesystem_traits_w_t::remove_dir_end(buff);

            TEST_WS_EQ(L"abc", buff.data());
            TEST_INT_EQ(3, r);
        }

        // passing resizeable buffer (vector<char>)
        {
            vec_m_t         buff = { 'a', 'b', 'c', '\\', '\\', '\0' };
            ss_size_t const r = filesystem_traits_m_t::remove_dir_end(buff);

            TEST_MS_EQ("abc", buff.data());
            TEST_INT_EQ(3, r);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            vec_w_t         buff = { 'a', 'b', 'c', '\\', '\\', '\0' };
            ss_size_t const r = filesystem_traits_w_t::remove_dir_end(buff);

            TEST_WS_EQ(L"abc", buff.data());
            TEST_INT_EQ(3, r);
        }
#endif
    }
}

static void TEST_remove_dir_end_3()
{

}

static void TEST_path_is_absolute_1()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute(""));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("."));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute(".."));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("./"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("../"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("../abc"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/./a"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\.\\a"));

        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("H:\\"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("H:\\a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("H:\\./a"));

        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share\\a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share\\./a"));
    }

    {
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L""));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"."));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L".."));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"./"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"../"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"../abc"));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/./a"));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\.\\a"));

        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"H:\\"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"H:\\a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"H:\\./a"));

        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share\\a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share\\./a"));
    }
}

static void TEST_path_is_absolute_2()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute(".", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute(".", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("..", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("..", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("..", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("./", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("./", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("./", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("../", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("../", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("../", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("../", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("../abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("../abc"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/a", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/./a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/./a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("/./a", 4));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\a", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\.\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\.\\a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\.\\a", 4));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("H:\\", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("H:\\", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("H:\\", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("H:\\", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("H:\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("H:\\a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("H:\\a", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("H:\\a", 3));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("H:\\./a"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share", 1));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share\\a", 1));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share\\a", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share\\a", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share\\./a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share\\./a", 1));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share\\./a", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_absolute("\\\\svr\\share\\./a", 3));
    }

    {
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L".", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L".", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"..", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"..", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"..", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"./", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"./", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"./", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"../", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"../", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"../", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"../", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"../abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"../abc"));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/a", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/./a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/./a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"/./a", 4));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\a", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\.\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\.\\a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\.\\a", 4));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"H:\\", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"H:\\", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"H:\\", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"H:\\", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"H:\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"H:\\a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"H:\\a", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"H:\\a", 3));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"H:\\./a"));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share", 1));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share\\a", 1));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share\\a", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share\\a", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share\\./a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share\\./a", 1));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share\\./a", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::path_is_absolute(L"\\\\svr\\share\\./a", 3));
    }
}

static void TEST_find_last_path_name_separator()
{
    {
        TEST_PTR_EQ(NULL, filesystem_traits_m_t::find_last_path_name_separator(""));
        TEST_PTR_EQ(NULL, filesystem_traits_m_t::find_last_path_name_separator("abc"));
        TEST_PTR_EQ(NULL, filesystem_traits_m_t::find_last_path_name_separator("abc_"));

        {
            char const input[] = "\\";

            TEST_PTR_EQ(input + 0, filesystem_traits_m_t::find_last_path_name_separator(input));
        }

        {
            char const input[] = "/";

            TEST_PTR_EQ(input + 0, filesystem_traits_m_t::find_last_path_name_separator(input));
        }

        {
            char const input[] = "\\abc";

            TEST_PTR_EQ(input + 0, filesystem_traits_m_t::find_last_path_name_separator(input));
        }

        {
            char const input[] = "/abc";

            TEST_PTR_EQ(input + 0, filesystem_traits_m_t::find_last_path_name_separator(input));
        }

        {
            char const input[] = "abc\\";

            TEST_PTR_EQ(input + 3, filesystem_traits_m_t::find_last_path_name_separator(input));
        }

        {
            char const input[] = "abc/";

            TEST_PTR_EQ(input + 3, filesystem_traits_m_t::find_last_path_name_separator(input));
        }

        {
            char const input[] = "abc/def\\";

            TEST_PTR_EQ(input + 7, filesystem_traits_m_t::find_last_path_name_separator(input));
        }

        {
            char const input[] = "abc\\def/";

            TEST_PTR_EQ(input + 7, filesystem_traits_m_t::find_last_path_name_separator(input));
        }

        {
            char const input[] = "abc/def\\ghi";

            TEST_PTR_EQ(input + 7, filesystem_traits_m_t::find_last_path_name_separator(input));
        }

        {
            char const input[] = "abc\\def/ghi";

            TEST_PTR_EQ(input + 7, filesystem_traits_m_t::find_last_path_name_separator(input));
        }
    }

    {
        TEST_PTR_EQ(NULL, filesystem_traits_w_t::find_last_path_name_separator(L""));
        TEST_PTR_EQ(NULL, filesystem_traits_w_t::find_last_path_name_separator(L"abc"));
        TEST_PTR_EQ(NULL, filesystem_traits_w_t::find_last_path_name_separator(L"abc_"));

        {
            wchar_t const input[] = L"\\";

            TEST_PTR_EQ(input + 0, filesystem_traits_w_t::find_last_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"/";

            TEST_PTR_EQ(input + 0, filesystem_traits_w_t::find_last_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"\\abc";

            TEST_PTR_EQ(input + 0, filesystem_traits_w_t::find_last_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"/abc";

            TEST_PTR_EQ(input + 0, filesystem_traits_w_t::find_last_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc\\";

            TEST_PTR_EQ(input + 3, filesystem_traits_w_t::find_last_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc/";

            TEST_PTR_EQ(input + 3, filesystem_traits_w_t::find_last_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc/def\\";

            TEST_PTR_EQ(input + 7, filesystem_traits_w_t::find_last_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc\\def/";

            TEST_PTR_EQ(input + 7, filesystem_traits_w_t::find_last_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc/def\\ghi";

            TEST_PTR_EQ(input + 7, filesystem_traits_w_t::find_last_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc\\def/ghi";

            TEST_PTR_EQ(input + 7, filesystem_traits_w_t::find_last_path_name_separator(input));
        }
    }
}

static void TEST_find_next_path_name_separator()
{
    {
        TEST_PTR_EQ(NULL, filesystem_traits_m_t::find_next_path_name_separator(""));
        TEST_PTR_EQ(NULL, filesystem_traits_m_t::find_next_path_name_separator("abc"));
        TEST_PTR_EQ(NULL, filesystem_traits_m_t::find_next_path_name_separator("abc_"));

        {
            char const input[] = "\\";

            TEST_PTR_EQ(input + 0, filesystem_traits_m_t::find_next_path_name_separator(input));
        }

        {
            char const input[] = "/";

            TEST_PTR_EQ(input + 0, filesystem_traits_m_t::find_next_path_name_separator(input));
        }

        {
            char const input[] = "\\abc";

            TEST_PTR_EQ(input + 0, filesystem_traits_m_t::find_next_path_name_separator(input));
        }

        {
            char const input[] = "/abc";

            TEST_PTR_EQ(input + 0, filesystem_traits_m_t::find_next_path_name_separator(input));
        }

        {
            char const input[] = "abc\\";

            TEST_PTR_EQ(input + 3, filesystem_traits_m_t::find_next_path_name_separator(input));
        }

        {
            char const input[] = "abc/";

            TEST_PTR_EQ(input + 3, filesystem_traits_m_t::find_next_path_name_separator(input));
        }

        {
            char const input[] = "abc/def\\";

            TEST_PTR_EQ(input + 3, filesystem_traits_m_t::find_next_path_name_separator(input));
        }

        {
            char const input[] = "abc\\def/";

            TEST_PTR_EQ(input + 3, filesystem_traits_m_t::find_next_path_name_separator(input));
        }

        {
            char const input[] = "abc/def\\ghi";

            TEST_PTR_EQ(input + 3, filesystem_traits_m_t::find_next_path_name_separator(input));
        }

        {
            char const input[] = "abc\\def/ghi";

            TEST_PTR_EQ(input + 3, filesystem_traits_m_t::find_next_path_name_separator(input));
        }
    }

    {
        TEST_PTR_EQ(NULL, filesystem_traits_w_t::find_next_path_name_separator(L""));
        TEST_PTR_EQ(NULL, filesystem_traits_w_t::find_next_path_name_separator(L"abc"));
        TEST_PTR_EQ(NULL, filesystem_traits_w_t::find_next_path_name_separator(L"abc_"));

        {
            wchar_t const input[] = L"\\";

            TEST_PTR_EQ(input + 0, filesystem_traits_w_t::find_next_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"/";

            TEST_PTR_EQ(input + 0, filesystem_traits_w_t::find_next_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"\\abc";

            TEST_PTR_EQ(input + 0, filesystem_traits_w_t::find_next_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"/abc";

            TEST_PTR_EQ(input + 0, filesystem_traits_w_t::find_next_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc\\";

            TEST_PTR_EQ(input + 3, filesystem_traits_w_t::find_next_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc/";

            TEST_PTR_EQ(input + 3, filesystem_traits_w_t::find_next_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc/def\\";

            TEST_PTR_EQ(input + 3, filesystem_traits_w_t::find_next_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc\\def/";

            TEST_PTR_EQ(input + 3, filesystem_traits_w_t::find_next_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc/def\\ghi";

            TEST_PTR_EQ(input + 3, filesystem_traits_w_t::find_next_path_name_separator(input));
        }

        {
            wchar_t const input[] = L"abc\\def/ghi";

            TEST_PTR_EQ(input + 3, filesystem_traits_w_t::find_next_path_name_separator(input));
        }
    }
}

static void TEST_path_is_rooted_1()
{
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted(""));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("a"));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("."));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted(".."));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("./"));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("../"));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("./abc"));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("../abc"));

    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("/"));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("/a"));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("/./a"));

    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\"));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\a"));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\.\\a"));

    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("H:\\"));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("H:\\a"));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("H:\\./a"));

    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share"));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share\\a"));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share\\./a"));
}

static void TEST_path_is_rooted_2()
{
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("a", 0));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("a", 1));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted(".", 0));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted(".", 1));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("..", 0));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("..", 1));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("..", 2));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("./", 0));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("./", 1));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("./", 2));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("../", 0));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("../", 1));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("../", 2));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("../", 3));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("./abc"));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("./abc"));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("../abc"));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("../abc"));

    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("/", 0));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("/", 1));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("/a", 0));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("/a", 1));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("/a", 2));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("/./a", 0));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("/./a", 1));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("/./a", 4));

    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("\\", 0));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\", 1));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("\\a", 0));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\a", 1));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\a", 2));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("\\.\\a", 0));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\.\\a", 1));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\.\\a", 4));

    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("H:\\", 0));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("H:\\", 1));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("H:\\", 2));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("H:\\", 3));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("H:\\a", 0));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("H:\\a", 1));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("H:\\a", 2));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("H:\\a", 3));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("H:\\./a"));

    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share", 0));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share", 1));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share", 2));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share", 3));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share\\a", 0));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share\\a", 1));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share\\a", 2));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share\\a", 3));
    TEST_BOOLEAN_FALSE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share\\./a", 0));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share\\./a", 1));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share\\./a", 2));
    TEST_BOOLEAN_TRUE(filesystem_traits_m_t::path_is_rooted("\\\\svr\\share\\./a", 3));
}

static void TEST_path_is_UNC_1()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC(""));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("."));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC(".."));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("./"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("../"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("../abc"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/./a"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\.\\a"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\a"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\./a"));

        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share\\a"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share\\./a"));
    }
}

static void TEST_path_is_UNC_2()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC(".", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC(".", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("..", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("..", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("..", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("./", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("./", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("./", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("../", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("../", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("../", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("../", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("./abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("../abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("../abc"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/a", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/./a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/./a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("/./a", 4));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\a", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\.\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\.\\a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\.\\a", 4));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\a", 1));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\a", 2));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\a", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("H:\\./a"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share", 1));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share\\a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share\\a", 1));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share\\a", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share\\a", 3));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share\\./a", 0));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share\\./a", 1));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share\\./a", 2));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_UNC("\\\\svr\\share\\./a", 3));
    }
}

static void TEST_is_path_name_separator()
{
    {
        for (int ch = '\0'; 256 != ch; ++ch)
        {
            switch (ch)
            {
            case '/':
            case '\\':

                TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_path_name_separator(char(ch)));
                break;
            default:

                TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_path_name_separator(char(ch)));
                break;
            }
        }
    }

    {
        for (int ch = L'\0'; 256 != ch; ++ch)
        {
            switch (ch)
            {
            case L'/':
            case L'\\':

                TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_path_name_separator(wchar_t(ch)));
                break;
            default:

                TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_path_name_separator(wchar_t(ch)));
                break;
            }
        }
    }
}

static void TEST_is_root_designator()
{
    {
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_root_designator(""));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_root_designator("abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_root_designator("abc/def"));

        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_root_designator("/"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_root_designator("\\"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_root_designator("C:"));

        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_root_designator("C:/"));
        TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_root_designator("C:\\"));

        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_root_designator("C:/abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_m_t::is_root_designator("C:\\abc"));
    }

    {
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_root_designator(L""));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_root_designator(L"abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_root_designator(L"abc/def"));

        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_root_designator(L"/"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_root_designator(L"\\"));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_root_designator(L"C:"));

        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_root_designator(L"C:/"));
        TEST_BOOLEAN_TRUE(filesystem_traits_w_t::is_root_designator(L"C:\\"));

        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_root_designator(L"C:/abc"));
        TEST_BOOLEAN_FALSE(filesystem_traits_w_t::is_root_designator(L"C:\\abc"));
    }
}

static void TEST_path_separator()
{
    {
        TEST_CHAR_EQ(';', filesystem_traits_m_t::path_separator());
    }

    {
        TEST_CHAR_EQ(L';', filesystem_traits_w_t::path_separator());
    }
}

static void TEST_path_name_separator()
{
    {
        TEST_CHAR_EQ('\\', filesystem_traits_m_t::path_name_separator());
    }

    {
        TEST_CHAR_EQ(L'\\', filesystem_traits_w_t::path_name_separator());
    }
}

static void TEST_path_max()
{
    {
        TEST_INT_EQ(_MAX_PATH, filesystem_traits_m_t::path_max());
    }

    {
        TEST_INT_EQ(32771, filesystem_traits_w_t::path_max());
    }
}

static void TEST_pattern_all()
{
    {
        TEST_MS_EQ("*.*", filesystem_traits_m_t::pattern_all());
    }

    {
        TEST_WS_EQ(L"*.*", filesystem_traits_w_t::pattern_all());
    }
}

static void TEST_patterns_all()
{
    {
        {
            auto const pa = filesystem_traits_m_t::patterns_all();

            TEST_MS_EQ("*.*", pa[0]);
            TEST_PTR_EQ(NULL, pa[1]);
        }

        {
            auto const pa = filesystem_traits_w_t::patterns_all();

            TEST_WS_EQ(L"*.*", pa[0]);
            TEST_PTR_EQ(NULL, pa[1]);
        }
    }

    {
        {
            ss_size_t   n;
            auto const  pa = filesystem_traits_m_t::patterns_all(&n);

            TEST_INT_EQ(1, n);
            TEST_MS_EQ("*.*", pa[0]);
            TEST_PTR_EQ(NULL, pa[1]);
        }

        {
            ss_size_t   n;
            auto const  pa = filesystem_traits_w_t::patterns_all(&n);

            TEST_INT_EQ(1, n);
            TEST_WS_EQ(L"*.*", pa[0]);
            TEST_PTR_EQ(NULL, pa[1]);
        }
    }
}

static void TEST_pathComparisonIsCaseSensitive()
{
    TEST_ENUM_EQ(0, filesystem_traits_m_t::pathComparisonIsCaseSensitive);
}

static void TEST_str_fs_compare()
{
    // char
    {
        // case agnostic
        {
            TEST_INT_EQ(0, filesystem_traits_m_t::str_fs_compare("", ""));

        }

        // same case
        {
            TEST_INT_EQ(0, filesystem_traits_m_t::str_fs_compare("abc", "abc"));
            TEST_INT_LT(0, filesystem_traits_m_t::str_fs_compare("abc", "abd"));
            TEST_INT_GT(0, filesystem_traits_m_t::str_fs_compare("abd", "abc"));

            TEST_INT_EQ(0, filesystem_traits_m_t::str_fs_compare("C:\\dir\\file.ext", "C:\\dir\\file.ext"));
        }

        // mixed case
        {
            TEST_INT_EQ(0, filesystem_traits_m_t::str_fs_compare("abc", "ABc"));
            TEST_INT_LT(0, filesystem_traits_m_t::str_fs_compare("aBC", "abD"));
            TEST_INT_GT(0, filesystem_traits_m_t::str_fs_compare("aBD", "Abc"));

            TEST_INT_EQ(0, filesystem_traits_m_t::str_fs_compare("C:\\DIR\\FILE.EXT", "c:\\dir\\file.ext"));
        }
    }

    {
        // case agnostic
        {
            TEST_INT_EQ(0, filesystem_traits_w_t::str_fs_compare(L"", L""));

        }

        // same case
        {
            TEST_INT_EQ(0, filesystem_traits_w_t::str_fs_compare(L"abc", L"abc"));
            TEST_INT_LT(0, filesystem_traits_w_t::str_fs_compare(L"abc", L"abd"));
            TEST_INT_GT(0, filesystem_traits_w_t::str_fs_compare(L"abd", L"abc"));

            TEST_INT_EQ(0, filesystem_traits_w_t::str_fs_compare(L"C:\\dir\\file.ext", L"C:\\dir\\file.ext"));
        }

        // mixed case
        {
            TEST_INT_EQ(0, filesystem_traits_w_t::str_fs_compare(L"abc", L"ABc"));
            TEST_INT_LT(0, filesystem_traits_w_t::str_fs_compare(L"aBC", L"abD"));
            TEST_INT_GT(0, filesystem_traits_w_t::str_fs_compare(L"aBD", L"Abc"));

            TEST_INT_EQ(0, filesystem_traits_w_t::str_fs_compare(L"C:\\DIR\\FILE.EXT", L"c:\\dir\\file.ext"));
        }
    }
}

static void TEST_str_fs_n_compare()
{

}
} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

