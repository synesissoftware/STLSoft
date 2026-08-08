/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.algorithms.bounded/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/algorithms/bounded`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/algorithms/bounded.hpp>

#include <vector>
#include <string>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_copy_n();
static void test_replace_n();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.algorithms.bounded", verbosity))
    {
        XTESTS_RUN_CASE(test_copy_n);
        XTESTS_RUN_CASE(test_replace_n);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_copy_n()
{
    int const src[] = { 1, 2, 3, 4, 5 };
    int       dest[5] = {};

    stlsoft::copy_n(&src[0], 3, &dest[0]);

    TEST_INTEGER_EQUAL(1, dest[0]);
    TEST_INTEGER_EQUAL(2, dest[1]);
    TEST_INTEGER_EQUAL(3, dest[2]);
}

static void test_replace_n()
{
    int src[] = { 1, 2, 1, 3, 1 };

    stlsoft::replace_n(&src[0], 5, 1, 9);

    TEST_INTEGER_EQUAL(9, src[0]);
    TEST_INTEGER_EQUAL(2, src[1]);
    TEST_INTEGER_EQUAL(9, src[2]);
    TEST_INTEGER_EQUAL(3, src[3]);
    TEST_INTEGER_EQUAL(9, src[4]);
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
