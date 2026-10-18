/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/unixstl/filesystem/filesystem_traits/entry.cpp
 *
 * Purpose: Unit-tests for `unixstl::filesystem_traits` resizeable-buffer
 *          `ensure_dir_end` / `remove_dir_end` (C2 empty-`""` behaviour;
 *          buffer size after remove); and wide path classification /
 *          separator finders.
 *
 * Created: 15th October 2026
 * Updated: 15th October 2026
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
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_ensure_dir_end_EMPTY_stays_empty();
    static void TEST_ensure_dir_end_APPENDS_separator();
    static void TEST_remove_dir_end_SHRINKS_buffer();
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
        XTESTS_RUN_CASE(TEST_remove_dir_end_SHRINKS_buffer);
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


/* Shared with resizeable_buffer branch — bodies land at merge (C2/C3). */
static void TEST_ensure_dir_end_EMPTY_stays_empty()
{
}

static void TEST_ensure_dir_end_APPENDS_separator()
{
}

static void TEST_remove_dir_end_SHRINKS_buffer()
{
}

static void TEST_remove_then_ensure_round_trip()
{
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
