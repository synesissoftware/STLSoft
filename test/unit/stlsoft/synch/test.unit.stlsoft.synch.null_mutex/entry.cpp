/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.synch.null_mutex/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/synch/null_mutex`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/synch/null_mutex.hpp>

#include <stlsoft/synch/lock_scope.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_null_mutex_lock_unlock();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.synch.null_mutex", verbosity))
    {
        XTESTS_RUN_CASE(test_null_mutex_lock_unlock);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_null_mutex_lock_unlock()
{
    stlsoft::null_mutex mx;
    mx.lock();
    mx.unlock();
    TEST_BOOLEAN_TRUE(true);
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
