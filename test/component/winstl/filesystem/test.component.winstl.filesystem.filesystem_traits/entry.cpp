/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.filesystem.filesystem_traits/entry.cpp
 *
 * Purpose: Component-tests for `winstl::filesystem_traits`.
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
#include <stlsoft/smartptr/scoped_handle.hpp>
#include <stlsoft/string/simple_string.hpp>

/* Standard C++ header files */
#include <vector>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_FIND_FILE_1();
    static void TEST_FIND_FILE_2();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSE_HELP_OR_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.winstl.filesystem.filesystem_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_FIND_FILE_1);
        XTESTS_RUN_CASE(TEST_FIND_FILE_2);

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
    typedef stlsoft::basic_simple_string<char>              string_m_t;
    typedef stlsoft::basic_simple_string<wchar_t>           string_w_t;
    typedef winstl::filesystem_traits<char>                 filesystem_traits_m_t;
    typedef winstl::filesystem_traits<wchar_t>              filesystem_traits_w_t;


    static string_m_t get_windows_directory()
    {
        char    path[1 + _MAX_PATH];
        size_t  cch = ::GetWindowsDirectoryA(&path[0], STLSOFT_NUM_ELEMENTS(path));

        return string_m_t(path, cch);
    }

#if 0

    static string_m_t get_current_directory()
    {
        char    path[1 + _MAX_PATH];
        size_t  cch = ::GetCurrentDirectoryA(STLSOFT_NUM_ELEMENTS(path), &path[0]);

        return string_m_t(path, cch);
    }
#endif


static void TEST_FIND_FILE_1()
{
    {
        string_m_t  windir  =   get_windows_directory();
        string_m_t  path    =   windir + filesystem_traits_m_t::path_name_separator() + filesystem_traits_m_t::pattern_all();

        filesystem_traits_m_t::find_data_type   data;
        HANDLE                                  hFind   =   filesystem_traits_m_t::find_first_file(path.c_str(), &data);

        if (INVALID_HANDLE_VALUE == hFind)
        {
no_file_found:
            TEST_FAIL("failed to find a file in the Windows directory");
        }
        else
        {
            stlsoft::scoped_handle<HANDLE> scoper_hFind(hFind, filesystem_traits_m_t::find_file_close, INVALID_HANDLE_VALUE);

            for (; filesystem_traits_m_t::is_directory(&data); )
            {
                if (!filesystem_traits_m_t::find_next_file(hFind, &data))
                {
                    goto no_file_found;
                }
            }

            TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_file(&data));
        }
    }
}

static void TEST_FIND_FILE_2()
{
    {
        string_m_t  windir  =   get_windows_directory();
        string_m_t  path    =   windir + filesystem_traits_m_t::path_name_separator() + filesystem_traits_m_t::pattern_all();

        filesystem_traits_m_t::find_data_type   data;
#if WINSTL_WIN32_WINNT >= WINSTL_WIN32_WINNT_NT4

        HANDLE                                  hFind   =   filesystem_traits_m_t::find_first_file_ex(path.c_str(), FindExSearchLimitToDirectories, &data);
#else

        HANDLE                                  hFind   =   filesystem_traits_m_t::find_first_file(path.c_str(), &data);
#endif

        if (INVALID_HANDLE_VALUE == hFind)
        {
no_file_found:
            TEST_FAIL("failed to find a file in the Windows directory");
        }
        else
        {
            stlsoft::scoped_handle<HANDLE> scoper_hFind(hFind, filesystem_traits_m_t::find_file_close, INVALID_HANDLE_VALUE);

            for (; filesystem_traits_m_t::is_file(&data) || filesystem_traits_m_t::is_dots(data.cFileName); )
            {
                if (!filesystem_traits_m_t::find_next_file(hFind, &data))
                {
                    goto no_file_found;
                }
            }

            TEST_BOOLEAN_TRUE(filesystem_traits_m_t::is_directory(&data));
        }
    }
}
} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

