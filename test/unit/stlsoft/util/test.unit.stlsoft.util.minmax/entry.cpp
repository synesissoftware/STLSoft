/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.minmax/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/util/minmax`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/util/minmax.hpp>


#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_minimum();
static void test_maximum();
static void test_minimum_three();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.minmax", verbosity))
    {
        XTESTS_RUN_CASE(test_minimum);
        XTESTS_RUN_CASE(test_maximum);
        XTESTS_RUN_CASE(test_minimum_three);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_minimum()
{
    TEST_INTEGER_EQUAL(1, stlsoft::minimum(1, 2));
    TEST_INTEGER_EQUAL(1, stlsoft::minimum(2, 1));
}

static void test_maximum()
{
    TEST_INTEGER_EQUAL(2, stlsoft::maximum(1, 2));
    TEST_INTEGER_EQUAL(2, stlsoft::maximum(2, 1));
}

static void test_minimum_three()
{
    TEST_INTEGER_EQUAL(1, stlsoft::minimum(3, 1, 2));
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
