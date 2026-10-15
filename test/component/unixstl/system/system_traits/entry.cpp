/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/system/system_traits/entry.cpp
 *
 * Purpose: Component-tests for resizeable-buffer overloads of
 *          `unixstl::system_traits` (`get_home_directory`,
 *          `get_environment_variable`).
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


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_get_environment_variable_MISSING();
    static void TEST_get_environment_variable_RESIZEABLE_auto_buffer();
    static void TEST_get_environment_variable_RESIZEABLE_vector();
    static void TEST_get_home_directory_RESIZEABLE_auto_buffer();
    static void TEST_get_home_directory_RESIZEABLE_vector();
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
        XTESTS_RUN_CASE(TEST_get_home_directory_RESIZEABLE_auto_buffer);
        XTESTS_RUN_CASE(TEST_get_home_directory_RESIZEABLE_vector);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    typedef unixstl::system_traits<char>                    traits_m_t;
    typedef stlsoft::auto_buffer<char>                      ab_m_t;
    typedef std::vector<char>                               vec_m_t;

    static char const s_missing_name[] =
        "STLSOFT_TEST_ENV_ABSENT_9F3C2B1A_7E4D_4A6F_9C08_1D2E3F4A5B6C";

    static char const s_present_name[] =
        "STLSOFT_TEST_ENV_PRESENT_9F3C2B1A_7E4D_4A6F_9C08_1D2E3F4A5B6C";

    static char const s_present_value[] = "resizeable-buffer-value";


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

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
