/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/unixstl/filesystem/filesystem_traits/entry.cpp
 *
 * Purpose: Unit-tests for `unixstl::filesystem_traits` resizeable-buffer
 *          `ensure_dir_end` / `remove_dir_end` (C2 empty-`""` behaviour;
 *          buffer size after remove; G3 strip-all trailing separators);
 *          and wide path classification / separator finders.
 *
 * Created: 15th October 2026
 * Updated: 19th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <unixstl/filesystem/filesystem_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/memory/auto_buffer.hpp>
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <vector>

/* Standard C header files */
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_ensure_dir_end_EMPTY_stays_empty();
    static void TEST_ensure_dir_end_APPENDS_separator();
    static void TEST_ensure_dir_end_RESIZE_FAILURE_sets_ENOMEM();
    static void TEST_remove_dir_end_SHRINKS_buffer();
    static void TEST_remove_dir_end_STRIPS_ALL_trailing_separators();
    static void TEST_remove_then_ensure_round_trip();

    static void TEST_find_path_name_separators_w();
    static void TEST_path_classification_w();
    static void TEST_path_classification_m_matches_w();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.filesystem_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_ensure_dir_end_EMPTY_stays_empty);
        XTESTS_RUN_CASE(TEST_ensure_dir_end_APPENDS_separator);
        XTESTS_RUN_CASE(TEST_ensure_dir_end_RESIZE_FAILURE_sets_ENOMEM);
        XTESTS_RUN_CASE(TEST_remove_dir_end_SHRINKS_buffer);
        XTESTS_RUN_CASE(TEST_remove_dir_end_STRIPS_ALL_trailing_separators);
        XTESTS_RUN_CASE(TEST_remove_then_ensure_round_trip);

        XTESTS_RUN_CASE(TEST_find_path_name_separators_w);
        XTESTS_RUN_CASE(TEST_path_classification_w);
        XTESTS_RUN_CASE(TEST_path_classification_m_matches_w);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    typedef unixstl::filesystem_traits<char>                traits_m_t;
    typedef unixstl::filesystem_traits<wchar_t>             traits_w_t;
    typedef stlsoft::auto_buffer<char>                      ab_m_t;
    typedef std::vector<char>                               vec_m_t;

    /* Resizeable-buffer model whose resize() always fails — used to lock
     * C5 OOM reporting without exhausting the process heap.
     */
    struct fail_resize_buffer
    {
        typedef char                                        value_type;
        typedef size_t                                      size_type;

        std::vector<char>                                   storage;

        size_type
        size() const
        {
            return storage.size();
        }

        bool
        empty() const
        {
            return storage.empty();
        }

        char&
        operator [](size_type i)
        {
            return storage[i];
        }

        char const&
        operator [](size_type i) const
        {
            return storage[i];
        }

        bool
        resize(size_type /* n */)
        {
            return false;
        }
    };


static void TEST_ensure_dir_end_EMPTY_stays_empty()
{
    {
        char        dirname[] = "\0";
        char*       r = traits_m_t::ensure_dir_end(dirname);

        TEST_MS_EQ("", dirname);
        TEST_PTR_EQ(dirname + 0, r);
    }

#if __cplusplus >= 201103L

    {
        ab_m_t          buff = { '\0' };
        size_t const    r = traits_m_t::ensure_dir_end(buff);

        TEST_MS_EQ("", buff.data());
        TEST_INT_EQ(0, r);
        TEST_INT_EQ(1, buff.size());
    }
#endif

    {
        vec_m_t         buff(0);
        size_t const    r = traits_m_t::ensure_dir_end(buff);

        TEST_MS_EQ("", buff.data());
        TEST_INT_EQ(0, r);
        TEST_INT_EQ(0, buff.size());
    }

    {
        vec_m_t         buff(1, '\0');
        size_t const    r = traits_m_t::ensure_dir_end(buff);

        TEST_MS_EQ("", buff.data());
        TEST_INT_EQ(0, r);
        TEST_INT_EQ(1, buff.size());
    }
}

static void TEST_ensure_dir_end_APPENDS_separator()
{
#if __cplusplus >= 201103L

    {
        ab_m_t          buff = { 'a', 'b', 'c', '\0' };
        size_t const    r = traits_m_t::ensure_dir_end(buff);

        TEST_MS_EQ("abc/", buff.data());
        TEST_INT_EQ(4, r);
        TEST_INT_EQ(5, buff.size());
    }
#endif

    {
        vec_m_t         buff;
        buff.push_back('a');
        buff.push_back('b');
        buff.push_back('c');
        buff.push_back('\0');

        size_t const    r = traits_m_t::ensure_dir_end(buff);

        TEST_MS_EQ("abc/", buff.data());
        TEST_INT_EQ(4, r);
        TEST_INT_EQ(5, buff.size());
    }
}

static void TEST_ensure_dir_end_RESIZE_FAILURE_sets_ENOMEM()
{
    fail_resize_buffer  rb;

    rb.storage.push_back('a');
    rb.storage.push_back('b');
    rb.storage.push_back('c');
    rb.storage.push_back('\0');

    traits_m_t::set_last_error(0);

    size_t const        n = traits_m_t::ensure_dir_end(rb);

    TEST_INT_EQ(0, n);
    TEST_INT_EQ(4, rb.size());
    TEST_INT_EQ(ENOMEM, traits_m_t::get_last_error());
}

static void TEST_remove_dir_end_SHRINKS_buffer()
{
#if __cplusplus >= 201103L

    {
        ab_m_t          buff = { 'a', 'b', 'c', '/', '\0' };
        size_t const    r = traits_m_t::remove_dir_end(buff);

        TEST_MS_EQ("abc", buff.data());
        TEST_INT_EQ(3, r);
        TEST_INT_EQ(4, buff.size());
    }
#endif

    {
        vec_m_t         buff;
        buff.push_back('a');
        buff.push_back('b');
        buff.push_back('c');
        buff.push_back('/');
        buff.push_back('\0');

        size_t const    r = traits_m_t::remove_dir_end(buff);

        TEST_MS_EQ("abc", buff.data());
        TEST_INT_EQ(3, r);
        TEST_INT_EQ(4, buff.size());
    }
}

static void TEST_remove_dir_end_STRIPS_ALL_trailing_separators()
{
    {
        char        dirname[] = "abc///";
        char*       r = traits_m_t::remove_dir_end(dirname);

        TEST_MS_EQ("abc", dirname);
        TEST_PTR_EQ(dirname + 0, r);
    }

#if __cplusplus >= 201103L

    {
        ab_m_t          buff = { 'a', 'b', 'c', '/', '/', '/', '\0' };
        size_t const    r = traits_m_t::remove_dir_end(buff);

        TEST_MS_EQ("abc", buff.data());
        TEST_INT_EQ(3, r);
        TEST_INT_EQ(4, buff.size());
    }
#endif

    {
        vec_m_t         buff;
        buff.push_back('a');
        buff.push_back('b');
        buff.push_back('c');
        buff.push_back('/');
        buff.push_back('/');
        buff.push_back('/');
        buff.push_back('\0');

        size_t const    r = traits_m_t::remove_dir_end(buff);

        TEST_MS_EQ("abc", buff.data());
        TEST_INT_EQ(3, r);
        TEST_INT_EQ(4, buff.size());
    }
}

static void TEST_remove_then_ensure_round_trip()
{
    vec_m_t         buff;
    buff.push_back('a');
    buff.push_back('b');
    buff.push_back('c');
    buff.push_back('/');
    buff.push_back('\0');

    size_t const    n_remove = traits_m_t::remove_dir_end(buff);

    TEST_INT_EQ(3, n_remove);
    TEST_INT_EQ(4, buff.size());
    TEST_MS_EQ("abc", buff.data());

    size_t const    n_ensure = traits_m_t::ensure_dir_end(buff);

    TEST_INT_EQ(4, n_ensure);
    TEST_INT_EQ(5, buff.size());
    TEST_MS_EQ("abc/", buff.data());
}

static void TEST_find_path_name_separators_w()
{
    {
        wchar_t const* const path = L"/usr/local/bin";
        wchar_t const* const last = traits_w_t::find_last_path_name_separator(path);
        wchar_t const* const next = traits_w_t::find_next_path_name_separator(path);

        TEST_PTR_NE(NULL, last);
        TEST_PTR_NE(NULL, next);
        TEST_PTR_EQ(path + 0, next);
        TEST_PTR_EQ(path + 10, last);
        TEST_PTR_EQ(last, traits_w_t::find_last_path_name_separator(path, ::wcslen(path)));
        TEST_PTR_EQ(next, traits_w_t::find_next_path_name_separator(path, ::wcslen(path)));
    }

    {
        wchar_t const* const path = L"relative";

        TEST_PTR_EQ(NULL, traits_w_t::find_last_path_name_separator(path));
        TEST_PTR_EQ(NULL, traits_w_t::find_next_path_name_separator(path));
        TEST_PTR_EQ(NULL, traits_w_t::find_last_path_name_separator(path, 0));
        TEST_PTR_EQ(NULL, traits_w_t::find_next_path_name_separator(path, 0));
    }
}

static void TEST_path_classification_w()
{
    TEST_BOOLEAN_TRUE(traits_w_t::is_path_rooted(L"/"));
    TEST_BOOLEAN_TRUE(traits_w_t::is_path_rooted(L"/tmp"));
    TEST_BOOLEAN_FALSE(traits_w_t::is_path_rooted(L"tmp"));
    TEST_BOOLEAN_FALSE(traits_w_t::is_path_rooted(L"", 0));

    TEST_BOOLEAN_TRUE(traits_w_t::is_path_absolute(L"/tmp"));
    TEST_BOOLEAN_FALSE(traits_w_t::is_path_absolute(L"tmp"));
    TEST_BOOLEAN_FALSE(traits_w_t::is_path_absolute(L"", 0));

    TEST_BOOLEAN_FALSE(traits_w_t::is_path_UNC(L"/tmp"));
    TEST_BOOLEAN_FALSE(traits_w_t::is_path_UNC(L"\\\\server\\share"));
    TEST_BOOLEAN_FALSE(traits_w_t::is_path_UNC(L"/tmp", 4));
}

static void TEST_path_classification_m_matches_w()
{
    char const* const paths_m[] =
    {
        "/",
        "/tmp",
        "tmp",
        "a/b",
        "",
    };
    wchar_t const* const paths_w[] =
    {
        L"/",
        L"/tmp",
        L"tmp",
        L"a/b",
        L"",
    };

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(paths_m); ++i)
    {
        size_t const len_m = ::strlen(paths_m[i]);
        size_t const len_w = ::wcslen(paths_w[i]);

        TEST_BOOLEAN_EQ(
            traits_m_t::is_path_rooted(paths_m[i])
        ,   traits_w_t::is_path_rooted(paths_w[i])
        );
        TEST_BOOLEAN_EQ(
            traits_m_t::is_path_rooted(paths_m[i], len_m)
        ,   traits_w_t::is_path_rooted(paths_w[i], len_w)
        );
        TEST_BOOLEAN_EQ(
            traits_m_t::is_path_absolute(paths_m[i])
        ,   traits_w_t::is_path_absolute(paths_w[i])
        );
        TEST_BOOLEAN_EQ(
            traits_m_t::is_path_absolute(paths_m[i], len_m)
        ,   traits_w_t::is_path_absolute(paths_w[i], len_w)
        );
        TEST_BOOLEAN_EQ(
            traits_m_t::is_path_UNC(paths_m[i])
        ,   traits_w_t::is_path_UNC(paths_w[i])
        );
    }}
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
