/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.filesystem.readdir_sequence/entry.cpp
 *
 * Purpose: Component test for `platformstl::readdir_sequence`.
 *
 * Created: sometime in 2010s
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <platformstl/filesystem/readdir_sequence.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

# ifndef _WIN32
#  define PLATFORM_SUPPORTS_SOCKETS_
# endif
#endif


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <platformstl/filesystem/path.hpp>

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>

/* STLSoft header files */
#include <platformstl/filesystem/filesystem_traits.hpp>
#include <stlsoft/smartptr/scoped_handle.hpp>

/* Standard C header files */
#include <stdlib.h>
#ifdef PLATFORM_SUPPORTS_SOCKETS_

# include <sys/socket.h>
# include <sys/un.h>
#endif


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_empty_directory();
    static void test_non_empty_directory();
#ifdef PLATFORM_SUPPORTS_SOCKETS_

    static void TEST_is_socket();
#endif
} // anonymous namespace

/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.readdir_sequence", verbosity))
    {
        XTESTS_RUN_CASE(test_empty_directory);
        XTESTS_RUN_CASE(test_non_empty_directory);
#ifdef PLATFORM_SUPPORTS_SOCKETS_

        XTESTS_RUN_CASE(TEST_is_socket);
#endif

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

namespace {

    typedef platformstl::filesystem_traits<char>            fs_traits_t;
    typedef platformstl::path                               path_t;
    typedef platformstl::readdir_sequence                       readdir_sequence_t;
    using ::xtests::cpp::util::temp_directory;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace {

#ifdef PLATFORMSTL_OS_IS_UNIXx

int
create_uds_socket_and_bind(
    char const* uds_path
)
{
    assert(NULL != uds_path);

    {
        struct sockaddr_un  sa;
        size_t const        len = strlen(uds_path);

        if (len >= STLSOFT_NUM_ELEMENTS(sa.sun_path))
        {
            return EINVAL;
        }
        else
        {
#ifdef UNIXSTL_OS_IS_MACOSX
            sa.sun_len = sizeof(sa);
#endif
            sa.sun_family = AF_UNIX;
            strncpy(sa.sun_path, uds_path, 1 + len);
        }
    }

    return -1;
}
#endif
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_empty_directory()
{
    temp_directory dir(temp_directory::EmptyOnClose | temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);

    readdir_sequence_t rds(dir);

    TEST_BOOLEAN_TRUE(rds.empty());
}

static void test_non_empty_directory()
{
    readdir_sequence_t rds(".");

    TEST_BOOLEAN_FALSE(rds.empty());
}

#ifdef PLATFORM_SUPPORTS_SOCKETS_

static void TEST_is_socket()
{

    path_t  td_path;

    {
        temp_directory  td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);

        path_t          path(td.c_str());
        path_t          sk_path = path / "tmp.sock";

        td_path = td.c_str();

        int sk = socket(AF_UNIX, SOCK_STREAM, 0);

        if (-1 == sk)
        {
            int const e = errno;

            TEST_FAIL_WITH_QUALIFIER("failed to create socket", strerror(e));
        }
        else
        {
            stlsoft::scoped_handle<int> scoper_sk(sk, close);

            struct sockaddr_un sa;

            if (sk_path.length() >= STLSOFT_NUM_ELEMENTS(sa.sun_path))
            {
                TEST_FAIL_WITH_QUALIFIER("socket_path is too long to test", sk_path);
            }
            else
            {
#ifdef UNIXSTL_OS_IS_MACOSX
                sa.sun_len = sizeof(sa);
#endif
                sa.sun_family = AF_UNIX;
                strcpy(sa.sun_path, sk_path.c_str());

                int const r = bind(sk, (struct sockaddr*)&sa, sizeof(sa));

                if (0 != r)
                {
                    int const e = errno;

                    TEST_FAIL_WITH_QUALIFIER("failed to bind socket", strerror(e));
                }
                else
                {
                    stlsoft::scoped_handle<char const*> scoper_file(sk_path.c_str(), unlink);

                    readdir_sequence_t  rds(td.c_str(), readdir_sequence_t::sockets | readdir_sequence_t::fullPath);
                    size_t              n       =   0;
                    path_t              first;

                    for (readdir_sequence_t::const_iterator i = rds.begin(); rds.end() != i; ++i, ++n)
                    {
                        if (first.empty())
                        {
                            first = *i;
                        }
                    }

                    TEST_INT_EQ(1u, n);

                    TEST_MULTIBYTE_STRING_EQUAL(sk_path, first);
                }
            }
        }
    }

    TEST_BOOLEAN_FALSE(fs_traits_t::file_exists(td_path.c_str()));
}
#endif
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

