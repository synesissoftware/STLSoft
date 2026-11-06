/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/unixstl/system/system_traits/entry.cpp
 *
 * Purpose: Unit-tests for `unixstl::system_traits` wide `path_str_*`.
 *          Environment-dependent coverage lives in
 *          `test/component/unixstl/system/system_traits`.
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

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_path_str_compare_w();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.system.system_traits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_path_str_compare_w);

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
    typedef unixstl::system_traits<wchar_t>                 traits_w_t;


static void TEST_path_str_compare_w()
{
    TEST_INT_EQ(0, traits_w_t::path_str_compare(L"/a/b", L"/a/b"));
    TEST_INT_NE(0, traits_w_t::path_str_compare(L"/a/b", L"/a/c"));
    TEST_INT_EQ(0, traits_w_t::path_str_n_compare(L"/a/b", L"/a/c", 3));
    TEST_INT_NE(0, traits_w_t::path_str_n_compare(L"/a/b", L"/a/c", 4));

    TEST_BOOLEAN_EQ(
        traits_m_t::path_str_compare("/tmp/x", "/tmp/y") < 0
    ,   traits_w_t::path_str_compare(L"/tmp/x", L"/tmp/y") < 0
    );
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
