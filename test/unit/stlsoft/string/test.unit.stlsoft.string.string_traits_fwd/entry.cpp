/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.string.string_traits_fwd/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/string/string_traits_fwd`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/string/string_traits_fwd.hpp>

#include <string.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_string_compile();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.string_traits_fwd", verbosity))
    {
        XTESTS_RUN_CASE(test_string_compile);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_string_compile()
{
    char s[] = "test";
    TEST_MS_EQ("test", s);
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
