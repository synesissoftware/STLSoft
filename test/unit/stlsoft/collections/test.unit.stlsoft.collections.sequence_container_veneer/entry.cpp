/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.collections.sequence_container_veneer/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/collections/sequence_container_veneer`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/collections/sequence_container_veneer.hpp>

#include <vector>
#include <string>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_collections_compile();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.collections.sequence_container_veneer", verbosity))
    {
        XTESTS_RUN_CASE(test_collections_compile);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_collections_compile()
{
    int arr[] = { 1, 2, 3 };
    TEST_INTEGER_EQUAL(3, arr[2]);
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
