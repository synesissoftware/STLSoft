/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/filesystem/filesystem_traits/paths/entry.cpp
 *
 * Purpose: Component-tests for resizeable-buffer overloads of
 *          `unixstl::filesystem_traits` (`get_current_directory`,
 *          `get_full_path_name`, `get_short_path_name`).
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

    static void TEST_get_current_directory_RESIZEABLE_auto_buffer();
    static void TEST_get_current_directory_RESIZEABLE_vector();
    static void TEST_get_full_path_name_RESIZEABLE_auto_buffer();
    static void TEST_get_full_path_name_RESIZEABLE_vector();
    static void TEST_get_short_path_name_RESIZEABLE_auto_buffer();
    static void TEST_get_short_path_name_RESIZEABLE_vector();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.filesystem.filesystem_traits.paths", verbosity))
    {
        XTESTS_RUN_CASE(TEST_get_current_directory_RESIZEABLE_auto_buffer);
        XTESTS_RUN_CASE(TEST_get_current_directory_RESIZEABLE_vector);
        XTESTS_RUN_CASE(TEST_get_full_path_name_RESIZEABLE_auto_buffer);
        XTESTS_RUN_CASE(TEST_get_full_path_name_RESIZEABLE_vector);
        XTESTS_RUN_CASE(TEST_get_short_path_name_RESIZEABLE_auto_buffer);
        XTESTS_RUN_CASE(TEST_get_short_path_name_RESIZEABLE_vector);

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
    typedef stlsoft::auto_buffer<char>                      ab_m_t;
    typedef std::vector<char>                               vec_m_t;


    static
    size_t
    capture_fixed(
        size_t (*fn)(char*, size_t)
    ,   vec_m_t&    expected
    )
    {
        expected.resize(1 + traits_m_t::path_max());

        size_t const n = fn(&expected[0], expected.size());

        if (0 != n &&
            n < expected.size())
        {
            expected.resize(n + 1);
            expected[n] = '\0';
        }

        return n;
    }

    static
    size_t
    capture_cwd(
        char*   buffer
    ,   size_t  cchBuffer
    )
    {
        return traits_m_t::get_current_directory(buffer, cchBuffer);
    }

    static
    size_t
    capture_full_dot(
        char*   buffer
    ,   size_t  cchBuffer
    )
    {
        return traits_m_t::get_full_path_name(".", buffer, cchBuffer);
    }

    static
    size_t
    capture_short_dot(
        char*   buffer
    ,   size_t  cchBuffer
    )
    {
        return traits_m_t::get_short_path_name(".", buffer, cchBuffer);
    }


static void TEST_get_current_directory_RESIZEABLE_auto_buffer()
{
    vec_m_t         expected;
    size_t const    expected_len = capture_fixed(capture_cwd, expected);

    TEST_INT_NE(0, expected_len);

    ab_m_t          rb(0);
    size_t const    n = traits_m_t::get_current_directory(rb);

    TEST_INT_EQ(expected_len, n);
    TEST_INT_EQ(expected_len + 1, rb.size());
    TEST_CHAR_EQ('\0', rb[n]);
    TEST_MS_EQ(&expected[0], rb.data());
}

static void TEST_get_current_directory_RESIZEABLE_vector()
{
    vec_m_t         expected;
    size_t const    expected_len = capture_fixed(capture_cwd, expected);

    TEST_INT_NE(0, expected_len);

    vec_m_t         rb;
    size_t const    n = traits_m_t::get_current_directory(rb);

    TEST_INT_EQ(expected_len, n);
    TEST_INT_EQ(expected_len + 1, rb.size());
    TEST_CHAR_EQ('\0', rb[n]);
    TEST_MS_EQ(&expected[0], &rb[0]);
}

static void TEST_get_full_path_name_RESIZEABLE_auto_buffer()
{
    vec_m_t         expected;
    size_t const    expected_len = capture_fixed(capture_full_dot, expected);

    TEST_INT_NE(0, expected_len);

    ab_m_t          rb(0);
    size_t const    n = traits_m_t::get_full_path_name(".", rb);

    TEST_INT_EQ(expected_len, n);
    TEST_INT_EQ(expected_len + 1, rb.size());
    TEST_CHAR_EQ('\0', rb[n]);
    TEST_MS_EQ(&expected[0], rb.data());
}

static void TEST_get_full_path_name_RESIZEABLE_vector()
{
    vec_m_t         expected;
    size_t const    expected_len = capture_fixed(capture_full_dot, expected);

    TEST_INT_NE(0, expected_len);

    vec_m_t         rb;
    size_t const    n = traits_m_t::get_full_path_name(".", rb);

    TEST_INT_EQ(expected_len, n);
    TEST_INT_EQ(expected_len + 1, rb.size());
    TEST_CHAR_EQ('\0', rb[n]);
    TEST_MS_EQ(&expected[0], &rb[0]);
}

static void TEST_get_short_path_name_RESIZEABLE_auto_buffer()
{
    vec_m_t         expected;
    size_t const    expected_len = capture_fixed(capture_short_dot, expected);

    TEST_INT_NE(0, expected_len);

    ab_m_t          rb(0);
    size_t const    n = traits_m_t::get_short_path_name(".", rb);

    TEST_INT_EQ(expected_len, n);
    TEST_INT_EQ(expected_len + 1, rb.size());
    TEST_CHAR_EQ('\0', rb[n]);
    TEST_MS_EQ(&expected[0], rb.data());
}

static void TEST_get_short_path_name_RESIZEABLE_vector()
{
    vec_m_t         expected;
    size_t const    expected_len = capture_fixed(capture_short_dot, expected);

    TEST_INT_NE(0, expected_len);

    vec_m_t         rb;
    size_t const    n = traits_m_t::get_short_path_name(".", rb);

    TEST_INT_EQ(expected_len, n);
    TEST_INT_EQ(expected_len + 1, rb.size());
    TEST_CHAR_EQ('\0', rb[n]);
    TEST_MS_EQ(&expected[0], &rb[0]);
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
