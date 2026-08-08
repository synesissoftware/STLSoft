/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.functional.function_pointer_adaptors/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/functional/function_pointer_adaptors`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/functional/function_pointer_adaptors.hpp>

#include <vector>
#include <string>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_functional_compile();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.functional.function_pointer_adaptors", verbosity))
    {
        XTESTS_RUN_CASE(test_functional_compile);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_functional_compile()
{
    TEST_BOOLEAN_TRUE(true);
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
