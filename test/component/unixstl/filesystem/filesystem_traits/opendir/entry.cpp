/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/filesystem/filesystem_traits/opendir/entry.cpp)
 *
 * Purpose: Component-tests for `unixstl::filesystem_traits`, in respect of
 *          the directory-enumeration functions `open_dir()`, `read_dir()`,
 *          `rewind_dir()`, and `close_dir()`.
 *
 * Created: 8th October 2026
 * Updated: 8th October 2026
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

#include <platformstl/filesystem/path.hpp>

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>
#include <xtests/util/temp_file.hpp>

/* Standard C++ header files */
#include <algorithm>
#include <string>
#include <vector>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_open_dir_NONEXISTENT_directory();
    static void TEST_read_dir_EMPTY_directory();
    static void TEST_read_dir_NON_EMPTY_directory();
    static void TEST_rewind_dir_AFTER_EXHAUSTION();
    static void TEST_rewind_dir_AFTER_PARTIAL_READ();
    static void TEST_rewind_dir_BEFORE_ANY_READ();
    static void TEST_rewind_dir_EMPTY_directory();
    static void TEST_rewind_dir_MULTIPLE_times();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.filesystem.filesystem_traits.opendir", verbosity))
    {
        XTESTS_RUN_CASE(TEST_open_dir_NONEXISTENT_directory);
        XTESTS_RUN_CASE(TEST_read_dir_EMPTY_directory);
        XTESTS_RUN_CASE(TEST_read_dir_NON_EMPTY_directory);
        XTESTS_RUN_CASE(TEST_rewind_dir_AFTER_EXHAUSTION);
        XTESTS_RUN_CASE(TEST_rewind_dir_AFTER_PARTIAL_READ);
        XTESTS_RUN_CASE(TEST_rewind_dir_BEFORE_ANY_READ);
        XTESTS_RUN_CASE(TEST_rewind_dir_EMPTY_directory);
        XTESTS_RUN_CASE(TEST_rewind_dir_MULTIPLE_times);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

namespace {

    typedef unixstl::filesystem_traits<char>                fs_traits_t;
    typedef platformstl::path                               path_t;
    typedef std::vector<std::string>                        names_t;
    using ::xtests::cpp::util::temp_directory;
    using ::xtests::cpp::util::temp_file;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace {

    /* Three temporary files, created in a given (temporary) directory,
     * and deleted on destruction. Must be declared after, so destroyed
     * before, the `temp_directory` in which they are created.
     */
    class three_files
    {
    public:
        explicit
        three_files(
            char const* dir
        )
            : m_f0(temp_file::DeleteOnClose | temp_file::CloseOnOpen, dir)
            , m_f1(temp_file::DeleteOnClose | temp_file::CloseOnOpen, dir)
            , m_f2(temp_file::DeleteOnClose | temp_file::CloseOnOpen, dir)
        {}

    public:
        /* The names (i.e. without directory) of the files, sorted */
        names_t
        names() const
        {
            names_t result;

            result.push_back(leaf_name(m_f0.c_str()));
            result.push_back(leaf_name(m_f1.c_str()));
            result.push_back(leaf_name(m_f2.c_str()));

            std::sort(result.begin(), result.end());

            return result;
        }

    private:
        static
        std::string
        leaf_name(
            char const* path
        )
        {
            char const* const sep = ::strrchr(path, '/');

            return (NULL == sep) ? path : (sep + 1);
        }

    private:
        temp_file   m_f0;
        temp_file   m_f1;
        temp_file   m_f2;
    };

    /* Reads up to `max` entries from `h` into `names`; returns the number
     * of entries read
     */
    static
    size_t
    read_entries(
        DIR*    h
    ,   names_t& names
    ,   size_t  max
    )
    {
        size_t n = 0;

        for (struct dirent const* de; n < max && NULL != (de = fs_traits_t::read_dir(h)); ++n)
        {
            names.push_back(de->d_name);
        }

        return n;
    }

    /* Reads all remaining entries from `h` into `names`; returns the number
     * of entries read
     */
    static
    size_t
    read_all_entries(
        DIR*    h
    ,   names_t& names
    )
    {
        return read_entries(h, names, ~size_t(0));
    }

    /* Removes the entries "." and ".." and sorts, so that sequences can be
     * compared irrespective of the (unspecified) order of enumeration
     */
    static
    names_t
    normalise(
        names_t names
    )
    {
        names_t result;

        for (names_t::const_iterator i = names.begin(); names.end() != i; ++i)
        {
            if ("." != *i && ".." != *i)
            {
                result.push_back(*i);
            }
        }

        std::sort(result.begin(), result.end());

        return result;
    }

} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_open_dir_NONEXISTENT_directory()
{
    temp_directory  td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);
    path_t const    path = path_t(td.c_str()) / "does-not-exist";

    DIR* const h = fs_traits_t::open_dir(path.c_str());

    TEST_BOOLEAN_TRUE(NULL == h);

    if (NULL != h)
    {
        fs_traits_t::close_dir(h);
    }
}

static void TEST_read_dir_EMPTY_directory()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);

    DIR* const h = fs_traits_t::open_dir(td.c_str());

    if (NULL == h)
    {
        TEST_FAIL("failed to open directory");
    }
    else
    {
        names_t names;

        read_all_entries(h, names);

        TEST_INT_EQ(0u, normalise(names).size());

        TEST_BOOLEAN_TRUE(NULL == fs_traits_t::read_dir(h));

        fs_traits_t::close_dir(h);
    }
}

static void TEST_read_dir_NON_EMPTY_directory()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);

    three_files files(td.c_str());

    DIR* const h = fs_traits_t::open_dir(td.c_str());

    if (NULL == h)
    {
        TEST_FAIL("failed to open directory");
    }
    else
    {
        names_t names;

        read_all_entries(h, names);

        TEST_BOOLEAN_TRUE(files.names() == normalise(names));

        fs_traits_t::close_dir(h);
    }
}

static void TEST_rewind_dir_BEFORE_ANY_READ()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);

    three_files files(td.c_str());

    DIR* const h = fs_traits_t::open_dir(td.c_str());

    if (NULL == h)
    {
        TEST_FAIL("failed to open directory");
    }
    else
    {
        names_t names;

        fs_traits_t::rewind_dir(h);

        read_all_entries(h, names);

        TEST_BOOLEAN_TRUE(files.names() == normalise(names));

        fs_traits_t::close_dir(h);
    }
}

static void TEST_rewind_dir_AFTER_PARTIAL_READ()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);

    three_files files(td.c_str());

    DIR* const h = fs_traits_t::open_dir(td.c_str());

    if (NULL == h)
    {
        TEST_FAIL("failed to open directory");
    }
    else
    {
        names_t first_pass;
        names_t second_pass;

        // Read the first two entries (of "." + ".." + 3 files, in some order)

        TEST_INT_EQ(2u, read_entries(h, first_pass, 2));

        fs_traits_t::rewind_dir(h);

        read_all_entries(h, second_pass);

        // After the rewind, *all* entries are returned, including those
        // that had been read before the rewind

        TEST_INT_EQ(5u, second_pass.size());
        TEST_BOOLEAN_TRUE(files.names() == normalise(second_pass));

        fs_traits_t::close_dir(h);
    }
}

static void TEST_rewind_dir_AFTER_EXHAUSTION()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);

    three_files files(td.c_str());

    DIR* const h = fs_traits_t::open_dir(td.c_str());

    if (NULL == h)
    {
        TEST_FAIL("failed to open directory");
    }
    else
    {
        names_t first_pass;
        names_t second_pass;

        read_all_entries(h, first_pass);

        TEST_BOOLEAN_TRUE(NULL == fs_traits_t::read_dir(h));

        fs_traits_t::rewind_dir(h);

        read_all_entries(h, second_pass);

        TEST_BOOLEAN_TRUE(files.names() == normalise(first_pass));
        TEST_BOOLEAN_TRUE(files.names() == normalise(second_pass));
        TEST_INT_EQ(first_pass.size(), second_pass.size());

        fs_traits_t::close_dir(h);
    }
}

static void TEST_rewind_dir_EMPTY_directory()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);

    DIR* const h = fs_traits_t::open_dir(td.c_str());

    if (NULL == h)
    {
        TEST_FAIL("failed to open directory");
    }
    else
    {
        names_t names;

        read_all_entries(h, names);

        fs_traits_t::rewind_dir(h);

        names_t names_after;

        read_all_entries(h, names_after);

        TEST_INT_EQ(0u, normalise(names_after).size());
        TEST_INT_EQ(names.size(), names_after.size());

        fs_traits_t::close_dir(h);
    }
}

static void TEST_rewind_dir_MULTIPLE_times()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);

    three_files files(td.c_str());

    DIR* const h = fs_traits_t::open_dir(td.c_str());

    if (NULL == h)
    {
        TEST_FAIL("failed to open directory");
    }
    else
    {
        for (int pass = 0; pass != 3; ++pass)
        {
            names_t names;

            read_all_entries(h, names);

            TEST_BOOLEAN_TRUE(files.names() == normalise(names));

            fs_traits_t::rewind_dir(h);
        }

        fs_traits_t::close_dir(h);
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

