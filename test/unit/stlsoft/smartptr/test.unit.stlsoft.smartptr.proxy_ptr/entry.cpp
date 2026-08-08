/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.smartptr.proxy_ptr/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/smartptr/proxy_ptr`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/smartptr/proxy_ptr.hpp>


#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_proxy_ptr();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.smartptr.proxy_ptr", verbosity))
    {
        XTESTS_RUN_CASE(test_proxy_ptr);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_proxy_ptr()
{
    int x = 3;
    stlsoft::proxy_ptr<int> pp(&x);
    TEST_INTEGER_EQUAL(3, *pp);
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
