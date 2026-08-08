/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.system.system_traits/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/system/system_traits.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/system/system_traits.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>
#include <string.h>


namespace {

typedef unixstl::system_traits<char> sys_traits_t;

static void test_get_home_directory()
{
    char buf[PATH_MAX];

    size_t const n = sys_traits_t::get_home_directory(buf, STLSOFT_NUM_ELEMENTS(buf));

    TEST_INT_GT(0u, n);
    TEST_CHAR_EQ('/', buf[0]);
}

static void test_environment_variable_exists()
{
    char buf[4096];

    size_t const n = sys_traits_t::get_environment_variable("PATH", buf, STLSOFT_NUM_ELEMENTS(buf));

    if (0 != n)
    {
        TEST_INT_GT(0, ::strlen(buf));
    }
}

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.system.system_traits", verbosity))
    {
        XTESTS_RUN_CASE(test_get_home_directory);
        XTESTS_RUN_CASE(test_environment_variable_exists);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
