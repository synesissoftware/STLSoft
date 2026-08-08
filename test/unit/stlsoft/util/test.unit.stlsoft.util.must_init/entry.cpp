/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.must_init/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/util/must_init`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/util/must_init.hpp>


#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_must_init();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.must_init", verbosity))
    {
        XTESTS_RUN_CASE(test_must_init);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_must_init()
{
    stlsoft::must_init<int> m(7);
    TEST_INTEGER_EQUAL(7, static_cast<int>(m));
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
