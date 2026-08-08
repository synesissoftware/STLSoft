/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.char2str/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/conversion/char2str`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/conversion/char2str.hpp>

#include <string.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_conversion_compile();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.char2str", verbosity))
    {
        XTESTS_RUN_CASE(test_conversion_compile);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_conversion_compile()
{
    TEST_INTEGER_EQUAL(42, 42);
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
