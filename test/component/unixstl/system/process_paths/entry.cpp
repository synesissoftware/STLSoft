/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/system/process_paths/entry.cpp
 *
 * Purpose: Component-tests for
 *          `unixstl::system_traits::get_current_process_path()` (multibyte),
 *          including resizeable-buffer overloads.
 *
 * Created: 15th October 2026
 * Updated: 20th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <unixstl/system/system_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/memory/auto_buffer.hpp>
#include <unixstl/filesystem/filesystem_traits.hpp>

/* Standard C++ header files */
#include <string>
#include <vector>

/* Standard C header files */
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#if 0
#elif defined(_WIN32)

# include <windows.h>
#elif defined(__APPLE__)

# include <libproc.h>
# include <mach-o/dyld.h>
# include <unistd.h>
#elif defined(__linux__)

# include <unistd.h>
#elif 0 ||\
      defined(__FreeBSD__) ||\
      defined(__NetBSD__) ||\
      defined(__OpenBSD__) ||\
      0

# include <sys/sysctl.h>
# include <sys/types.h>
#elif defined(__sun)

# include <unistd.h>
#endif

#if !defined(PATH_MAX)
# define PATH_MAX                                           4096
#endif


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_SIZE_QUERY();
    static void TEST_EXACT_FIT();
    static void TEST_EXCESS_SPACE();
    static void TEST_INSUFFICIENT_SPACE();
    static void TEST_ppFile_NULL_ON_SUCCESS();
    static void TEST_ppFile_separator_on_success();
    static void TEST_ppFile_NULL_WHEN_INSUFFICIENT();
    static void TEST_RESIZEABLE_auto_buffer_SUCCESS();
    static void TEST_RESIZEABLE_vector_SUCCESS();
    static void TEST_RESIZEABLE_ppFile_NULL();
    static void TEST_RESIZEABLE_ppFile_separator();
    static void TEST_RESIZEABLE_resize_FAILURE_leaves_rb_untouched();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.system.process_paths", verbosity))
    {
        XTESTS_RUN_CASE(TEST_SIZE_QUERY);
        XTESTS_RUN_CASE(TEST_EXACT_FIT);
        XTESTS_RUN_CASE(TEST_EXCESS_SPACE);
        XTESTS_RUN_CASE(TEST_INSUFFICIENT_SPACE);
        XTESTS_RUN_CASE(TEST_ppFile_NULL_ON_SUCCESS);
        XTESTS_RUN_CASE(TEST_ppFile_separator_on_success);
        XTESTS_RUN_CASE(TEST_ppFile_NULL_WHEN_INSUFFICIENT);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_auto_buffer_SUCCESS);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_vector_SUCCESS);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_ppFile_NULL);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_ppFile_separator);
        XTESTS_RUN_CASE(TEST_RESIZEABLE_resize_FAILURE_leaves_rb_untouched);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

namespace {

typedef unixstl::filesystem_traits<char>                    fs_traits_m_t;
typedef unixstl::system_traits<char>                        traits_m_t;

/** Retrieves the full path of the current executable from the ambient OS
 * API (not via STLSoft).
 *
 * \return 0 on success; -1 on failure.
 */
static
int
get_executable_path_(
    char*   path
,   size_t  size
)
{
    if (NULL == path ||
        0 == size)
    {
        return -1;
    }

#if 0
#elif defined(_WIN32)

    /* Windows / UNIXem: GetModuleFileNameA */
    {
        DWORD const len = ::GetModuleFileNameA(NULL, path, static_cast<DWORD>(size - 1));

        if (0 == len)
        {
            return -1;
        }

        if (len == static_cast<DWORD>(size - 1) &&
            ERROR_INSUFFICIENT_BUFFER == ::GetLastError())
        {
            return -1;
        }

        path[len] = '\0';

        return 0;
    }
#elif defined(__APPLE__)

    /* macOS: prefer proc_pidpath; fallback to _NSGetExecutablePath (+ realpath). */
    {
        pid_t const pid = ::getpid();
        int const   ret = ::proc_pidpath(pid, path, static_cast<uint32_t>(size));

        if (ret <= 0)
        {
            uint32_t len = static_cast<uint32_t>(size);

            if (0 != ::_NSGetExecutablePath(path, &len))
            {
                return -1;
            }

            {
                char* const resolved = ::realpath(path, NULL);

                if (NULL != resolved)
                {
                    ::strncpy(path, resolved, size - 1);
                    path[size - 1] = '\0';
                    ::free(resolved);
                }
            }
        }

        return 0;
    }
#elif defined(__linux__)

    /* Linux: readlink("/proc/self/exe") */
    {
        ssize_t const len = ::readlink("/proc/self/exe", path, size - 1);

        if (-1 == len)
        {
            return -1;
        }

        path[len] = '\0';

        return 0;
    }
#elif 0 || \
      defined(__FreeBSD__) ||\
      defined(__NetBSD__) ||\
      defined(__OpenBSD__) ||\
      0

    /* BSD: sysctl(KERN_PROC_PATHNAME) */
    {
        int     mib[4];
        size_t  len = size - 1;

        mib[0] = CTL_KERN;
        mib[1] = KERN_PROC;
        mib[2] = KERN_PROC_PATHNAME;
        mib[3] = -1;

        if (0 != ::sysctl(mib, 4, path, &len, NULL, 0))
        {
            return -1;
        }

        path[len] = '\0';

        return 0;
    }
#elif defined(__sun)

    /* Solaris: getexecname() + realpath() */
    {
        char const* const exe = ::getexecname();

        if (NULL == exe)
        {
            return -1;
        }

        if (NULL == ::realpath(exe, path))
        {
            return -1;
        }

        return 0;
    }
#else

    STLSOFT_SUPPRESS_UNUSED(path);
    STLSOFT_SUPPRESS_UNUSED(size);

    return -1;
#endif
}

/** Obtains the current process image path from the ambient OS API, without
 * going through STLSoft.
 */
static
std::string
obtain_raw_current_process_path()
{
    char path[PATH_MAX];

    if (0 != get_executable_path_(path, sizeof(path)))
    {
        return std::string();
    }

    return std::string(path);
}

static
char*
invalid_file_pointer()
{
    return reinterpret_cast<char*>(static_cast<size_t>(-1));
}

/** Minimal resizeable buffer whose #resize() always fails. */
struct fail_on_resize_buffer
{
    typedef char                                            value_type;

    std::vector<char>                                       storage;

    size_t size() const
    {
        return storage.size();
    }

    char& operator [](size_t i)
    {
        return storage[i];
    }

    char const& operator [](size_t i) const
    {
        return storage[i];
    }

    bool resize(size_t /* newSize */)
    {
        return false;
    }
};
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_SIZE_QUERY()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    char*               pFile   =   invalid_file_pointer();
    size_t const        cch     =   traits_m_t::get_current_process_path(0, NULL, &pFile);

    TEST_INT_EQ(expected.size() + 1, cch);
    TEST_PTR_NULL(pFile);
}

static void TEST_EXACT_FIT()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                len     =   expected.size();
    stlsoft::auto_buffer<char>  buff(len + 1);
    char*                       pFile   =   invalid_file_pointer();
    size_t const                cch     =   traits_m_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_EQ(len, cch);
    TEST_MS_EQ(expected.c_str(), &buff[0]);
    TEST_CHAR_EQ('\0', buff[len]);
}

static void TEST_EXCESS_SPACE()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                len = expected.size();
    stlsoft::auto_buffer<char>  buff(len + 64);

    ::memset(&buff[0], '~', buff.size());

    char*                       pFile   =   invalid_file_pointer();
    size_t const                cch     =   traits_m_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_EQ(len, cch);
    TEST_MS_EQ(expected.c_str(), &buff[0]);
    TEST_CHAR_EQ('\0', buff[len]);
}

static void TEST_INSUFFICIENT_SPACE()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const len = expected.size();

    /* One character short of an exact fit. */
    {
        size_t const                cchBuff = len;
        stlsoft::auto_buffer<char>  buff(cchBuff);

        ::memset(&buff[0], '~', buff.size());

        char*                       pFile   =   invalid_file_pointer();
        size_t const                cch     =   traits_m_t::get_current_process_path(buff.size(), &buff[0], &pFile);

        TEST_INT_EQ(len + 1, cch);
        TEST_PTR_NULL(pFile);
        TEST_CHAR_EQ('\0', buff[cchBuff - 1]);
        TEST_MS_EQ_N(expected.c_str(), &buff[0], cchBuff - 1);
    }

    /* Single-character buffer: only the terminating NUL. */
    {
        char            buff[1] =   { '~' };
        char*           pFile   =   invalid_file_pointer();
        size_t const    cch     =   traits_m_t::get_current_process_path(STLSOFT_NUM_ELEMENTS(buff), buff, &pFile);

        TEST_INT_EQ(len + 1, cch);
        TEST_PTR_NULL(pFile);
        TEST_CHAR_EQ('\0', buff[0]);
    }
}

static void TEST_ppFile_NULL_ON_SUCCESS()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<char>  buff(expected.size() + 1);
    size_t const                cch = traits_m_t::get_current_process_path(buff.size(), &buff[0], NULL);

    TEST_INT_EQ(expected.size(), cch);
    TEST_MS_EQ(expected.c_str(), &buff[0]);
}

static void TEST_ppFile_separator_on_success()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<char>  buff(expected.size() + 1);
    char*                       pFile   =   invalid_file_pointer();
    size_t const                cch     =   traits_m_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_EQ(expected.size(), cch);
    TEST_MS_EQ(expected.c_str(), &buff[0]);

    char const* const expectedSep = fs_traits_m_t::find_last_path_name_separator(&buff[0]);

    TEST_PTR_EQ(expectedSep, pFile);

    if (NULL != pFile)
    {
        TEST_MS_EQ(expectedSep + 1, pFile + 1);
    }
}

static void TEST_ppFile_NULL_WHEN_INSUFFICIENT()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    size_t const                len = expected.size();
    stlsoft::auto_buffer<char>  buff(len); /* one short */
    char*                       pFile   =   invalid_file_pointer();
    size_t const                cch     =   traits_m_t::get_current_process_path(buff.size(), &buff[0], &pFile);

    TEST_INT_EQ(len + 1, cch);
    TEST_PTR_NULL(pFile);
}

static void TEST_RESIZEABLE_auto_buffer_SUCCESS()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<char>  rb(0);
    size_t const                cch = traits_m_t::get_current_process_path(rb);

    TEST_INT_EQ(expected.size(), cch);
    TEST_INT_GE(expected.size() + 1, rb.size());
    TEST_MS_EQ(expected.c_str(), &rb[0]);
}

static void TEST_RESIZEABLE_vector_SUCCESS()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    std::vector<char>   rb;
    size_t const        cch = traits_m_t::get_current_process_path(rb);

    TEST_INT_EQ(expected.size(), cch);
    TEST_INT_GE(expected.size() + 1, rb.size());
    TEST_MS_EQ(expected.c_str(), &rb[0]);
}

static void TEST_RESIZEABLE_ppFile_NULL()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<char>  rb(0);
    size_t const                cch = traits_m_t::get_current_process_path(rb, NULL);

    TEST_INT_EQ(expected.size(), cch);
    TEST_MS_EQ(expected.c_str(), &rb[0]);
}

static void TEST_RESIZEABLE_ppFile_separator()
{
    std::string const   expected = obtain_raw_current_process_path();

    XTESTS_REQUIRE(TEST_BOOLEAN_TRUE(!expected.empty()));

    stlsoft::auto_buffer<char>  rb(0);
    char*                       pFile   =   invalid_file_pointer();
    size_t const                cch     =   traits_m_t::get_current_process_path(rb, &pFile);

    TEST_INT_EQ(expected.size(), cch);
    TEST_MS_EQ(expected.c_str(), &rb[0]);

    char const* const expectedSep = fs_traits_m_t::find_last_path_name_separator(&rb[0]);

    TEST_PTR_EQ(expectedSep, pFile);

    if (NULL != pFile)
    {
        TEST_MS_EQ(expectedSep + 1, pFile + 1);
    }
}

static void TEST_RESIZEABLE_resize_FAILURE_leaves_rb_untouched()
{
    fail_on_resize_buffer  rb;

    rb.storage.assign(4, 'X');

    size_t const    priorSize   =   rb.size();
    int const       priorErrno  =   errno;

    errno = 0;

    size_t const    cch = traits_m_t::get_current_process_path(rb);

    TEST_INT_EQ(0, cch);
    TEST_INT_EQ(ENOMEM, errno);
    TEST_INT_EQ(priorSize, rb.size());
    TEST_CHAR_EQ('X', rb.storage[0]);
    TEST_CHAR_EQ('X', rb.storage[3]);

    errno = priorErrno;
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

