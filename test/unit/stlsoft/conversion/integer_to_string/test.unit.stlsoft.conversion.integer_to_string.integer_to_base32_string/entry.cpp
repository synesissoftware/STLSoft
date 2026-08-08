/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.integer_to_string.integer_to_base32_string/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/conversion/integer_to_string/integer_to_base32_string`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/conversion/integer_to_string/integer_to_base32_string.hpp>

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

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.integer_to_string.integer_to_base32_string", verbosity))
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
