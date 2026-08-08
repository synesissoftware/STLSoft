/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.system.system_traits/entry.cpp
 *
 * Purpose: Unit-tests for `winstl::system_traits`.
 *
 * Created: 22nd May 2025
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/system/system_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/limits/integral_limits.hpp>
#include <stlsoft/memory/auto_buffer.hpp>
#include <stlsoft/smartptr/scoped_handle.hpp>
#include <platformstl/system/environment_variable_scope.hpp>

/* Standard C++ header files */
#include <vector>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_expand_environment_string_EMPTY_INPUT();
    static void TEST_expand_environment_string_NONEXISTING_VARIABLE();
    static void TEST_expand_environment_string_0();
    static void TEST_expand_environment_string_1();

    static void TEST_get_environment_variable();

    static void TEST_get_home_directory();

    static void TEST_get_module_directory();

    static void TEST_get_module_filename();

    static void TEST_get_system_directory();

    static void TEST_get_windows_directory();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSE_HELP_OR_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.system.system_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_expand_environment_string_EMPTY_INPUT);
        XTESTS_RUN_CASE(TEST_expand_environment_string_NONEXISTING_VARIABLE);
        XTESTS_RUN_CASE(TEST_expand_environment_string_0);
        XTESTS_RUN_CASE(TEST_expand_environment_string_1);

        XTESTS_RUN_CASE(TEST_get_environment_variable);

        XTESTS_RUN_CASE(TEST_get_home_directory);

        XTESTS_RUN_CASE(TEST_get_module_directory);

        XTESTS_RUN_CASE(TEST_get_module_filename);

        XTESTS_RUN_CASE(TEST_get_system_directory);

        XTESTS_RUN_CASE(TEST_get_windows_directory);

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
    typedef winstl::system_traits<char>                     system_traits_m_t;
    typedef winstl::system_traits<wchar_t>                  system_traits_w_t;


static void TEST_expand_environment_string_EMPTY_INPUT()
{
    // empty input string
    {
        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[2];
            ss_size_t const r = system_traits_m_t::expand_environment_strings("", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(1, r);
            TEST_MS_EQ("", buff);
        }

        // passing character array (wchar_t)
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[2];
            ss_size_t const r = system_traits_w_t::expand_environment_strings(L"", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(1, r);
            TEST_WS_EQ(L"", buff);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(1);
            ss_size_t const r = system_traits_m_t::expand_environment_strings("", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(1, r);
            TEST_MS_EQ("", buff.data());
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(1);
            ss_size_t const r = system_traits_w_t::expand_environment_strings(L"", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(1, r);
            TEST_WS_EQ(L"", buff.data());
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t         buff(0);
            ss_size_t const r = system_traits_m_t::expand_environment_strings("", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(1, r);
            TEST_MS_EQ("", buff.data());
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_w_t         buff(0);
            ss_size_t const r = system_traits_w_t::expand_environment_strings(L"", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(1, r);
            TEST_WS_EQ(L"", buff.data());
        }
    }
}

static void TEST_expand_environment_string_NONEXISTING_VARIABLE()
{
    {
        platformstl::environment_variable_scope scope_X("NONE", nullptr);

        // insufficient buffer
        {
            // passing character array (char)
            {
                ::SetLastError(ERROR_SUCCESS);

                char            buff[3] = { '~', '~', '~' };
                ss_size_t const r = system_traits_m_t::expand_environment_strings( "%NONE%", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(8, r);
                TEST_MS_EQ("", buff);
            }

            // passing character array (wchar_t)
            {
                ::SetLastError(ERROR_SUCCESS);

                wchar_t         buff[3] = { '~', '~', '~' };
                ss_size_t const r = system_traits_w_t::expand_environment_strings(L"%NONE%", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_WS_EQ(L"", buff);
            }

            // passing resizeable buffer (auto_buffer<char>)
            {
                ::SetLastError(ERROR_SUCCESS);

                ab_m_t          buff(1);
                ss_size_t const r = system_traits_m_t::expand_environment_strings( "%NONE%", buff);

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_MS_EQ("%NONE%", buff.data());
            }

            // passing resizeable buffer (auto_buffer<wchar_t>)
            {
                ::SetLastError(ERROR_SUCCESS);

                ab_w_t          buff(1);
                ss_size_t const r = system_traits_w_t::expand_environment_strings(L"%NONE%", buff);

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_WS_EQ(L"%NONE%", buff.data());
            }

            // passing resizeable buffer (vector<char>)
            {
                ::SetLastError(ERROR_SUCCESS);

                vec_m_t         buff(0);
                ss_size_t const r = system_traits_m_t::expand_environment_strings("%NONE%", buff);

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_MS_EQ("%NONE%", buff.data());
            }

            // passing resizeable buffer (vector<wchar_t>)
            {
                ::SetLastError(ERROR_SUCCESS);

                vec_w_t         buff(0);
                ss_size_t const r = system_traits_w_t::expand_environment_strings(L"%NONE%", buff);

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_WS_EQ(L"%NONE%", buff.data());
            }
        }

        // sufficient buffer
        {
            // passing character array (char)
            {
                ::SetLastError(ERROR_SUCCESS);

                char            buff[8] = { '~', '~', '~', '~', '~', '~', '~', '~' };
                ss_size_t const r = system_traits_m_t::expand_environment_strings( "%NONE%", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_MS_EQ("%NONE%", buff);
            }

            // passing character array (wchar_t)
            {
                ::SetLastError(ERROR_SUCCESS);

                wchar_t         buff[8] = { '~', '~', '~', '~', '~', '~', '~', '~' };
                ss_size_t const r = system_traits_w_t::expand_environment_strings(L"%NONE%", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_WS_EQ(L"%NONE%", buff);
            }

            // passing resizeable buffer (auto_buffer<char>)
            {
                ::SetLastError(ERROR_SUCCESS);

                ab_m_t          buff(8);
                ss_size_t const r = system_traits_m_t::expand_environment_strings( "%NONE%", buff);

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_INT_EQ(8u, buff.size());
                TEST_MS_EQ("%NONE%", buff.data());
            }

            // passing resizeable buffer (auto_buffer<wchar_t>)
            {
                ::SetLastError(ERROR_SUCCESS);

                ab_w_t          buff(8);
                ss_size_t const r = system_traits_w_t::expand_environment_strings(L"%NONE%", buff);

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_INT_EQ(8u, buff.size());
                TEST_WS_EQ(L"%NONE%", buff.data());
            }

            // passing resizeable buffer (vector<char>)
            {
                ::SetLastError(ERROR_SUCCESS);

                vec_m_t         buff(8);
                ss_size_t const r = system_traits_m_t::expand_environment_strings("%NONE%", buff);

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_INT_EQ(8u, buff.size());
                TEST_MS_EQ("%NONE%", buff.data());
            }

            // passing resizeable buffer (vector<wchar_t>)
            {
                ::SetLastError(ERROR_SUCCESS);

                vec_w_t         buff(8);
                ss_size_t const r = system_traits_w_t::expand_environment_strings(L"%NONE%", buff);

                TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
                TEST_INT_EQ(7, r);
                TEST_INT_EQ(8u, buff.size());
                TEST_WS_EQ(L"%NONE%", buff.data());
            }
        }
    }
}

static void TEST_expand_environment_string_0()
{
    {
        platformstl::environment_variable_scope scope_X("X", "x");

        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[3];
            ss_size_t const r = system_traits_m_t::expand_environment_strings("%X%", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(2, r);
            TEST_MS_EQ("x", buff);
        }

        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[3];
            ss_size_t const r = system_traits_w_t::expand_environment_strings(L"%X%", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(2, r);
            TEST_WS_EQ(L"x", buff);
        }
    }
}

static void TEST_expand_environment_string_1()
{
    char const      ms_TempDir[] =  R"(C:\Users\MYUSER\AppData\Local\Temp)";
    wchar_t const   ws_TempDir[] = LR"(C:\Users\MYUSER\AppData\Local\Temp)";

    platformstl::environment_variable_scope scope_MYTEMP("MYTEMP", ms_TempDir);

    // passing character array (char)
    {
        // insufficient
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[35];
            ss_size_t const r = system_traits_m_t::expand_environment_strings( "%MYTEMP%", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(36, r);
            TEST_MS_EQ("", buff);
        }

        // sufficient
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[36];
            ss_size_t const r = system_traits_m_t::expand_environment_strings( "%MYTEMP%", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(35, r);
            TEST_MS_EQ(ms_TempDir, buff);
            TEST_CHAR_EQ('\0', buff[r - 1]);
            TEST_CHAR_NE('\0', buff[r - 2]);
        }
    }

    // passing character array (wchar_t)
    {
        ::SetLastError(ERROR_SUCCESS);

        wchar_t         buff[35];
        ss_size_t const r = system_traits_w_t::expand_environment_strings(L"%MYTEMP%", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

        TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
        TEST_INT_EQ(35, r);
        TEST_WS_EQ(ws_TempDir, buff);
        TEST_CHAR_EQ(L'\0', buff[r - 1]);
        TEST_CHAR_NE(L'\0', buff[r - 2]);
    }

    // passing resizeable buffer (auto_buffer<char>)
    {
        ::SetLastError(ERROR_SUCCESS);

        ab_m_t          buff(1);
        ss_size_t const r = system_traits_m_t::expand_environment_strings( "%MYTEMP%", buff);

        TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
        TEST_INT_EQ(35, r);
        TEST_MS_EQ(ms_TempDir, buff.data());
        TEST_CHAR_EQ('\0', buff[r - 1]);
        TEST_CHAR_NE('\0', buff[r - 2]);
    }

    // passing resizeable buffer (auto_buffer<wchar_t>)
    {
        ::SetLastError(ERROR_SUCCESS);

        ab_w_t          buff(1);
        ss_size_t const r = system_traits_w_t::expand_environment_strings(L"%MYTEMP%", buff);

        TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
        TEST_INT_EQ(35, r);
        TEST_WS_EQ(ws_TempDir, buff.data());
        TEST_CHAR_EQ(L'\0', buff[r - 1]);
        TEST_CHAR_NE(L'\0', buff[r - 2]);
    }

    // passing resizeable buffer (vector<char>)
    {
        ::SetLastError(ERROR_SUCCESS);

        vec_m_t         buff(0);
        ss_size_t const r = system_traits_m_t::expand_environment_strings("%MYTEMP%", buff);

        TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
        TEST_INT_EQ(35, r);
        TEST_MS_EQ(ms_TempDir, buff.data());
    }

    // passing resizeable buffer (vector<wchar_t>)
    {
        ::SetLastError(ERROR_SUCCESS);

        vec_w_t         buff(0);
        ss_size_t const r = system_traits_w_t::expand_environment_strings(L"%MYTEMP%", buff);

        TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
        TEST_INT_EQ(35, r);
        TEST_WS_EQ(ws_TempDir, buff.data());
    }
}

static void TEST_get_environment_variable()
{
    platformstl::environment_variable_scope scope_X("XYZ", "xyz");

    // insufficient memory
    {
        // passing character array (char) - 0
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1] = { '~' };
            ss_size_t const r = system_traits_m_t::get_environment_variable("XYZ", &buff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(4, r);
            TEST_CHAR_EQ('~', buff[0]);
        }

        // passing character array (wchar_t) - 0
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1] = { '~' };
            ss_size_t const r = system_traits_w_t::get_environment_variable(L"XYZ", &buff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(4, r);
            TEST_CHAR_EQ(L'~', buff[0]);
        }

        // passing character array (char) - 1
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1] = { '~' };
            ss_size_t const r = system_traits_m_t::get_environment_variable("XYZ", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_EQ(4, r);
            TEST_CHAR_EQ('\0', buff[0]);
        }

        // passing character array (wchar_t) - 0
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1] = { '~' };
            ss_size_t const r = system_traits_w_t::get_environment_variable(L"XYZ", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_EQ(4, r);
            TEST_CHAR_EQ(L'\0', buff[0]);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(1);
            ss_size_t const n = system_traits_m_t::get_environment_variable("XYZ", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(3, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
            TEST_MS_EQ("xyz", buff.data());
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(1);
            ss_size_t const n = system_traits_w_t::get_environment_variable(L"XYZ", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(3, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
            TEST_WS_EQ(L"xyz", buff.data());
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t          buff(0);
            ss_size_t const n = system_traits_m_t::get_environment_variable("XYZ", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(3, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
            TEST_MS_EQ("xyz", buff.data());
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(0);
            ss_size_t const n = system_traits_w_t::get_environment_variable(L"XYZ", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(3, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
            TEST_WS_EQ(L"xyz", buff.data());
        }
    }

    // sufficient memory
    {
        // passing character array (char) - 4
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[4] = { '~' };
            ss_size_t const r = system_traits_m_t::get_environment_variable("XYZ", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(3, r);
            TEST_CHAR_EQ('\0', buff[r]);
            TEST_MS_EQ("xyz", buff);
        }

        // passing character array (wchar_t) - 4
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[4] = { '~' };
            ss_size_t const r = system_traits_w_t::get_environment_variable(L"XYZ", &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_EQ(3, r);
            TEST_CHAR_EQ(L'\0', buff[r]);
            TEST_WS_EQ(L"xyz", buff);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(4);
            ss_size_t const n = system_traits_m_t::get_environment_variable("XYZ", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(3, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
            TEST_MS_EQ("xyz", buff.data());
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(4);
            ss_size_t const n = system_traits_w_t::get_environment_variable(L"XYZ", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(3, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
            TEST_WS_EQ(L"xyz", buff.data());
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t         buff(4);
            ss_size_t const n = system_traits_m_t::get_environment_variable("XYZ", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(3, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
            TEST_MS_EQ("xyz", buff.data());
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_w_t         buff(4);
            ss_size_t const n = system_traits_w_t::get_environment_variable(L"XYZ", buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(3, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
            TEST_WS_EQ(L"xyz", buff.data());
        }
    }
}

static void TEST_get_home_directory()
{
    // insufficient memory
    {
        // passing character array (char) - 0
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1] = { '~' };
            ss_size_t const n = system_traits_m_t::get_home_directory(&buff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(8, n);
            TEST_CHAR_EQ('~', buff[0]);
        }

        // passing character array (wchar_t) - 0
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1] = { '~' };
            ss_size_t const n = system_traits_w_t::get_home_directory(&buff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(8, n);
            TEST_CHAR_EQ(L'~', buff[0]);
        }

        // passing character array (char) - 1
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1] = { '~' };
            ss_size_t const n = system_traits_m_t::get_home_directory(&buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_GE(8, n);
            TEST_CHAR_EQ('\0', buff[0]);
        }

        // passing character array (wchar_t) - 1
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1] = { '~' };
            ss_size_t const n = system_traits_w_t::get_home_directory(&buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_GE(8, n);
            TEST_CHAR_EQ(L'\0', buff[0]);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(1);
            ss_size_t const n = system_traits_m_t::get_home_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(8, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(1);
            ss_size_t const n = system_traits_w_t::get_home_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(8, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t         buff(0);
            ss_size_t const n = system_traits_m_t::get_home_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(8, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_w_t         buff(0);
            ss_size_t const n = system_traits_w_t::get_home_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(8, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }
    }

    // sufficient memory
    {
    }
}

static void TEST_get_module_directory()
{
    // invalid handle
    {
        HMODULE hmInvalid = reinterpret_cast<HMODULE>(stlsoft::integral_limits<std::uintptr_t>::maximum());

        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[261]; buff[0] = buff[STLSOFT_NUM_ELEMENTS(buff) - 1] = '~';
            ss_size_t const n = system_traits_m_t::get_module_directory(hmInvalid, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_MOD_NOT_FOUND, ::GetLastError());
            TEST_INT_GE(0, n);
            TEST_CHAR_EQ('~', buff[n]);
            TEST_CHAR_EQ('~', buff[STLSOFT_NUM_ELEMENTS(buff) - 1]);
        }

        // passing character array (wchar_t)
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[261]; buff[0] = buff[STLSOFT_NUM_ELEMENTS(buff) - 1] = '~';
            ss_size_t const n = system_traits_w_t::get_module_directory(hmInvalid, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_MOD_NOT_FOUND, ::GetLastError());
            TEST_INT_GE(0, n);
            TEST_CHAR_EQ(L'~', buff[n]);
            TEST_CHAR_EQ(L'~', buff[STLSOFT_NUM_ELEMENTS(buff) - 1]);
        }
    }

    HMODULE                         hmKernel    =   ::LoadLibraryA("kernel32");
    stlsoft::scoped_handle<HMODULE> scoper_Kernel(hmKernel, ::FreeLibrary);

    // insufficient memory
    {
        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1] = { '~' };
            ss_size_t const n = system_traits_m_t::get_module_directory(hmKernel, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_GE(4, n);
            TEST_CHAR_EQ('\0', buff[0]);
        }

        // passing character array (wchar_t)
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1] = { '~' };
            ss_size_t const n = system_traits_w_t::get_module_directory(hmKernel, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_GE(4, n);
            TEST_CHAR_EQ(L'\0', buff[0]);
        }
    }

    // sufficient memory
    {
        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1001];
            ss_size_t const n = system_traits_m_t::get_module_directory(hmKernel, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(13, n);
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing character array (wchar_t)
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1001];
            ss_size_t const n = system_traits_w_t::get_module_directory(hmKernel, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(13, n);
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }
    }
}

static void TEST_get_module_filename()
{
    // invalid handle
    {
        HMODULE hmInvalid = reinterpret_cast<HMODULE>(stlsoft::integral_limits<std::uintptr_t>::maximum());

        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[261]; buff[0] = buff[STLSOFT_NUM_ELEMENTS(buff) - 1] = '~';
            ss_size_t const n = system_traits_m_t::get_module_filename(hmInvalid, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_MOD_NOT_FOUND, ::GetLastError());
            TEST_INT_GE(0, n);
            TEST_CHAR_EQ('~', buff[n]);
            TEST_CHAR_EQ('~', buff[STLSOFT_NUM_ELEMENTS(buff) - 1]);
        }

        // passing character array (wchar_t)
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[261]; buff[0] = buff[STLSOFT_NUM_ELEMENTS(buff) - 1] = '~';
            ss_size_t const n = system_traits_w_t::get_module_filename(hmInvalid, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_MOD_NOT_FOUND, ::GetLastError());
            TEST_INT_GE(0, n);
            TEST_CHAR_EQ(L'~', buff[n]);
            TEST_CHAR_EQ(L'~', buff[STLSOFT_NUM_ELEMENTS(buff) - 1]);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(1); buff[0] = '~';
            ss_size_t const n = system_traits_m_t::get_module_filename(hmInvalid, buff);

            TEST_INT_EQ(ERROR_MOD_NOT_FOUND, ::GetLastError());
            TEST_INT_GE(0, n);
            TEST_INT_EQ(1, buff.size());
            TEST_CHAR_EQ('~', buff[n]);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(1); buff[0] = '~';
            ss_size_t const n = system_traits_w_t::get_module_filename(hmInvalid, buff);

            TEST_INT_EQ(ERROR_MOD_NOT_FOUND, ::GetLastError());
            TEST_INT_GE(0, n);
            TEST_INT_EQ(1, buff.size());
            TEST_CHAR_EQ(L'~', buff[n]);
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t         buff(0);
            ss_size_t const n = system_traits_m_t::get_module_filename(hmInvalid, buff);

            TEST_INT_EQ(ERROR_MOD_NOT_FOUND, ::GetLastError());
            TEST_INT_GE(0, n);
            TEST_INT_EQ(0, buff.size());
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_w_t         buff(0);
            ss_size_t const n = system_traits_w_t::get_module_filename(hmInvalid, buff);

            TEST_INT_EQ(ERROR_MOD_NOT_FOUND, ::GetLastError());
            TEST_INT_GE(0, n);
            TEST_INT_EQ(0, buff.size());
        }
    }

    HMODULE                         hmKernel    =   ::LoadLibraryA("kernel32");
    stlsoft::scoped_handle<HMODULE> scoper_Kernel(hmKernel, ::FreeLibrary);

    // insufficient memory
    {
        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1] = { '~' };
            ss_size_t const n = system_traits_m_t::get_module_filename(hmKernel, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_GE(4, n);
            TEST_CHAR_EQ('\0', buff[0]);
        }

        // passing character array (wchar_t)
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1] = { '~' };
            ss_size_t const n = system_traits_w_t::get_module_filename(hmKernel, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_GE(4, n);
            TEST_CHAR_EQ(L'\0', buff[0]);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(1);
            ss_size_t const n = system_traits_m_t::get_module_filename(hmKernel, buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(15, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(1);
            ss_size_t const n = system_traits_w_t::get_module_filename(hmKernel, buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(15, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t         buff(0);
            ss_size_t const n = system_traits_m_t::get_module_filename(hmKernel, buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(15, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_w_t         buff(0);
            ss_size_t const n = system_traits_w_t::get_module_filename(hmKernel, buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(15, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }
    }

    // sufficient memory
    {
        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1001];
            ss_size_t const n = system_traits_m_t::get_module_filename(hmKernel, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(15, n);
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing character array (wchar_t)
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1001];
            ss_size_t const n = system_traits_w_t::get_module_filename(hmKernel, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(15, n);
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(1001);
            ss_size_t const n = system_traits_m_t::get_module_filename(hmKernel, buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(15, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(1001);
            ss_size_t const n = system_traits_w_t::get_module_filename(hmKernel, buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(15, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t         buff(1001);
            ss_size_t const n = system_traits_m_t::get_module_filename(hmKernel, buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(15, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_w_t         buff(1001);
            ss_size_t const n = system_traits_w_t::get_module_filename(hmKernel, buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(15, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }
    }
}

static void TEST_get_system_directory()
{
    // insufficient memory
    {
        // passing character array (char) - 0
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1] = { '~' };
            ss_size_t const n = system_traits_m_t::get_system_directory(&buff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_CHAR_EQ('~', buff[0]);
        }

        // passing  character array (wchar_t) - 0
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1] = { '~' };
            ss_size_t const n = system_traits_w_t::get_system_directory(&buff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_CHAR_EQ(L'~', buff[0]);
        }

        // passing character array (char) - 1
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1];
            ss_size_t const n = system_traits_m_t::get_system_directory(&buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_CHAR_EQ('\0', buff[0]);
        }

        // passing character array (wchar_t) - 1
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1];
            ss_size_t const n = system_traits_w_t::get_system_directory(&buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_CHAR_EQ(L'\0', buff[0]);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(1);
            ss_size_t const n = system_traits_m_t::get_system_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(1);
            ss_size_t const n = system_traits_w_t::get_system_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t         buff(0);
            ss_size_t const n = system_traits_m_t::get_system_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_w_t         buff(0);
            ss_size_t const n = system_traits_w_t::get_system_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }
    }

    // sufficient memory
    {
        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[265];
            ss_size_t const n = system_traits_m_t::get_system_directory(&buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing character array (wchar_t)
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[265];
            ss_size_t const n = system_traits_w_t::get_system_directory(&buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(265);
            ss_size_t const n = system_traits_m_t::get_system_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_INT_EQ(265, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(265);
            ss_size_t const n = system_traits_w_t::get_system_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_INT_EQ(265, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t          buff(265);
            ss_size_t const n = system_traits_m_t::get_system_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_INT_EQ(265, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_w_t         buff(265);
            ss_size_t const n = system_traits_w_t::get_system_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_INT_EQ(265, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }
    }
}

static void TEST_get_windows_directory()
{
    // insufficient memory
    {
        // passing character array (char) - 0
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1] = { '~' };
            ss_size_t const n = system_traits_m_t::get_windows_directory(&buff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_CHAR_EQ('~', buff[0]);
        }

        // passing character array (wchar_t) - 0
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1] = { '~' };
            ss_size_t const n = system_traits_w_t::get_windows_directory(&buff[0], 0);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_CHAR_EQ(L'~', buff[0]);
        }

        // passing character array (char) - 1
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[1];
            ss_size_t const n = system_traits_m_t::get_windows_directory(&buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_CHAR_EQ('\0', buff[0]);
        }

        // passing character array (wchar_t) - 1
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[1];
            ss_size_t const n = system_traits_w_t::get_windows_directory(&buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_INSUFFICIENT_BUFFER, ::GetLastError());
            TEST_INT_GE(11, n);
            TEST_CHAR_EQ(L'\0', buff[0]);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(1);
            ss_size_t const n = system_traits_m_t::get_windows_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(4, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(1);
            ss_size_t const n = system_traits_w_t::get_windows_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(4, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t         buff(0);
            ss_size_t const n = system_traits_m_t::get_windows_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(4, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_w_t         buff(0);
            ss_size_t const n = system_traits_w_t::get_windows_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(4, n);
            TEST_INT_GT(n, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }
    }

    // sufficient memory
    {
        // passing character array (char)
        {
            ::SetLastError(ERROR_SUCCESS);

            char            buff[265];
            ss_size_t const n = system_traits_m_t::get_windows_directory(&buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(10, n);
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing character array (wchar_t)
        {
            ::SetLastError(ERROR_SUCCESS);

            wchar_t         buff[265];
            ss_size_t const n = system_traits_w_t::get_windows_directory(&buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(10, n);
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }

        // passing resizeable buffer (auto_buffer<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_m_t          buff(265);
            ss_size_t const n = system_traits_m_t::get_windows_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(10, n);
            TEST_INT_EQ(265, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (auto_buffer<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            ab_w_t          buff(265);
            ss_size_t const n = system_traits_w_t::get_windows_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(10, n);
            TEST_INT_EQ(265, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<char>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_m_t         buff(265);
            ss_size_t const n = system_traits_m_t::get_windows_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(10, n);
            TEST_INT_EQ(265, buff.size());
            TEST_CHAR_EQ('\0', buff[n]);
            TEST_CHAR_NE('\0', buff[n - 1]);
        }

        // passing resizeable buffer (vector<wchar_t>)
        {
            ::SetLastError(ERROR_SUCCESS);

            vec_w_t         buff(265);
            ss_size_t const n = system_traits_w_t::get_windows_directory(buff);

            TEST_INT_EQ(ERROR_SUCCESS, ::GetLastError());
            TEST_INT_GE(10, n);
            TEST_INT_EQ(265, buff.size());
            TEST_CHAR_EQ(L'\0', buff[n]);
            TEST_CHAR_NE(L'\0', buff[n - 1]);
        }
    }
}
} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

