/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/system/system_traits/entry.cpp
 *
 * Purpose: Component-tests for `unixstl::system_traits` — ANSI
 *          resizeable-buffer overloads (`get_home_directory`,
 *          `get_environment_variable`) and wide home / environment APIs.
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

#include <unixstl/system/system_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <platformstl/system/environment_variable_scope.hpp>
#include <stlsoft/memory/auto_buffer.hpp>
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <vector>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_get_environment_variable_MISSING();
    static void TEST_get_environment_variable_RESIZEABLE_auto_buffer();
    static void TEST_get_environment_variable_RESIZEABLE_vector();
    static void TEST_get_environment_variable_w();
    static void TEST_get_home_directory_RESIZEABLE_auto_buffer();
    static void TEST_get_home_directory_RESIZEABLE_vector();
    static void TEST_get_home_directory_w();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.system.system_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_get_environment_variable_MISSING);
        XTESTS_RUN_CASE(TEST_get_environment_variable_RESIZEABLE_auto_buffer);
        XTESTS_RUN_CASE(TEST_get_environment_variable_RESIZEABLE_vector);
        XTESTS_RUN_CASE(TEST_get_environment_variable_w);
        XTESTS_RUN_CASE(TEST_get_home_directory_RESIZEABLE_auto_buffer);
        XTESTS_RUN_CASE(TEST_get_home_directory_RESIZEABLE_vector);
        XTESTS_RUN_CASE(TEST_get_home_directory_w);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    typedef stlsoft::auto_buffer<char>                      ab_m_t;
    typedef stlsoft::auto_buffer<wchar_t>                   ab_w_t;
    typedef unixstl::system_traits<char>                    traits_m_t;
    typedef unixstl::system_traits<wchar_t>                 traits_w_t;
    typedef std::vector<char>                               vec_m_t;
    typedef std::vector<wchar_t>                            vec_w_t;

    static char const s_missing_name[] =
        "STLSOFT_TEST_ENV_ABSENT_9F3C2B1A_7E4D_4A6F_9C08_1D2E3F4A5B6C";

    static char const s_present_name[] =
        "STLSOFT_TEST_ENV_PRESENT_9F3C2B1A_7E4D_4A6F_9C08_1D2E3F4A5B6C";

    static char const s_present_value[] = "resizeable-buffer-value";

    static wchar_t const s_wide_missing_name_w[] =
        L"UNIXSTL_SYSTEM_TRAITS_W_TEST_MISSING_9F3C2B1A_7E4D_4A6F_9C08_1D2E3F4A5B6C";

    static char const s_wide_present_name[] =
        "UNIXSTL_SYSTEM_TRAITS_W_TEST_9F3C2B1A_7E4D_4A6F_9C08_1D2E3F4A5B6C";

    static wchar_t const s_wide_present_name_w[] =
        L"UNIXSTL_SYSTEM_TRAITS_W_TEST_9F3C2B1A_7E4D_4A6F_9C08_1D2E3F4A5B6C";

    static char const s_wide_present_value[] = "wide-env-value";

    static wchar_t const s_wide_present_value_w[] = L"wide-env-value";


static void TEST_get_environment_variable_MISSING()
{
    {
        ab_m_t          rb(0);
        size_t const    n = traits_m_t::get_environment_variable(s_missing_name, rb);

        TEST_INT_EQ(0, n);
        TEST_INT_EQ(0, rb.size());
    }

    {
        vec_m_t         rb;
        size_t const    n = traits_m_t::get_environment_variable(s_missing_name, rb);

        TEST_INT_EQ(0, n);
        TEST_INT_EQ(0, rb.size());
    }

    {
        ab_m_t          rb(3);
        rb[0] = 'a';
        rb[1] = 'b';
        rb[2] = 'c';

        size_t const    n = traits_m_t::get_environment_variable(s_missing_name, rb);

        TEST_INT_EQ(0, n);
        TEST_INT_EQ(3, rb.size());
        TEST_CHAR_EQ('a', rb[0]);
        TEST_CHAR_EQ('b', rb[1]);
        TEST_CHAR_EQ('c', rb[2]);
    }
}

static void TEST_get_environment_variable_RESIZEABLE_auto_buffer()
{
    platformstl::environment_variable_scope const scope(
        s_present_name
    ,   s_present_value
    );

    size_t const        expected_len = ::strlen(s_present_value);
    ab_m_t              rb(0);
    size_t const        n = traits_m_t::get_environment_variable(s_present_name, rb);

    TEST_INT_EQ(expected_len, n);
    TEST_INT_EQ(expected_len + 1, rb.size());
    TEST_CHAR_EQ('\0', rb[n]);
    TEST_MS_EQ(s_present_value, rb.data());
}

static void TEST_get_environment_variable_RESIZEABLE_vector()
{
    platformstl::environment_variable_scope const scope(
        s_present_name
    ,   s_present_value
    );

    size_t const        expected_len = ::strlen(s_present_value);
    vec_m_t             rb;
    size_t const        n = traits_m_t::get_environment_variable(s_present_name, rb);

    TEST_INT_EQ(expected_len, n);
    TEST_INT_EQ(expected_len + 1, rb.size());
    TEST_CHAR_EQ('\0', rb[n]);
    TEST_MS_EQ(s_present_value, &rb[0]);
}

static void TEST_get_environment_variable_w()
{
    platformstl::environment_variable_scope const scope(
        s_wide_present_name
    ,   s_wide_present_value
    );

    size_t const cch_probe = traits_w_t::get_environment_variable(
                                 s_wide_present_name_w
                             ,   static_cast<wchar_t*>(NULL)
                             ,   0
                             );

    TEST_INT_EQ(::strlen(s_wide_present_value), cch_probe);

    wchar_t buff[64];
    size_t const cch = traits_w_t::get_environment_variable(
                           s_wide_present_name_w
                       ,   buff
                       ,   STLSOFT_NUM_ELEMENTS(buff)
                       );

    TEST_INT_EQ(cch_probe, cch);
    TEST_WS_EQ(s_wide_present_value_w, buff);

    {
        vec_w_t rb;

        size_t const n = traits_w_t::get_environment_variable(
                             s_wide_present_name_w
                         ,   rb
                         );

        TEST_INT_EQ(cch_probe, n);
        TEST_INT_EQ(cch_probe, rb.size());
        TEST_INT_EQ(0, ::wcsncmp(s_wide_present_value_w, rb.data(), cch_probe));
    }

    TEST_INT_EQ(
        0
    ,   traits_w_t::get_environment_variable(
            s_wide_missing_name_w
        ,   buff
        ,   STLSOFT_NUM_ELEMENTS(buff)
        )
    );
}

static void TEST_get_home_directory_RESIZEABLE_auto_buffer()
{
    char const* const home = ::getenv("HOME");

    if (NULL == home)
    {
        ab_m_t          rb(0);
        size_t const    n = traits_m_t::get_home_directory(rb);

        TEST_INT_EQ(0, n);
        TEST_INT_EQ(0, rb.size());

        return;
    }

    size_t const        expected_len = ::strlen(home);
    ab_m_t              rb(0);
    size_t const        n = traits_m_t::get_home_directory(rb);

    TEST_INT_EQ(expected_len, n);
    TEST_INT_EQ(expected_len + 1, rb.size());
    TEST_CHAR_EQ('\0', rb[n]);
    TEST_MS_EQ(home, rb.data());
}

static void TEST_get_home_directory_RESIZEABLE_vector()
{
    char const* const home = ::getenv("HOME");

    if (NULL == home)
    {
        vec_m_t         rb;
        size_t const    n = traits_m_t::get_home_directory(rb);

        TEST_INT_EQ(0, n);
        TEST_INT_EQ(0, rb.size());

        return;
    }

    size_t const        expected_len = ::strlen(home);
    vec_m_t             rb;
    size_t const        n = traits_m_t::get_home_directory(rb);

    TEST_INT_EQ(expected_len, n);
    TEST_INT_EQ(expected_len + 1, rb.size());
    TEST_CHAR_EQ('\0', rb[n]);
    TEST_MS_EQ(home, &rb[0]);
}

static void TEST_get_home_directory_w()
{
    size_t const required_m = traits_m_t::get_home_directory(static_cast<char*>(NULL), 0);
    size_t const required_w = traits_w_t::get_home_directory(static_cast<wchar_t*>(NULL), 0);

    if (0 == required_m)
    {
        TEST_INT_EQ(0, required_w);
        return;
    }

    TEST_INT_EQ(required_m, required_w);

    ab_m_t buff_m(required_m);
    ab_w_t buff_w(required_w);

    size_t const cch_m = traits_m_t::get_home_directory(&buff_m[0], buff_m.size());
    size_t const cch_w = traits_w_t::get_home_directory(&buff_w[0], buff_w.size());

    TEST_INT_EQ(required_m - 1, cch_m);
    TEST_INT_EQ(required_w - 1, cch_w);
    TEST_INT_EQ(cch_m, cch_w);

    {
        ab_w_t expected(cch_m + 1);

        TEST_INT_NE(static_cast<size_t>(-1), ::mbstowcs(&expected[0], buff_m.data(), expected.size()));
        TEST_WS_EQ(expected.data(), buff_w.data());
    }

    {
        vec_w_t rb;

        size_t const n = traits_w_t::get_home_directory(rb);

        TEST_INT_EQ(cch_w, n);
        TEST_INT_EQ(required_w, rb.size());
        TEST_WS_EQ(buff_w.data(), rb.data());
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

