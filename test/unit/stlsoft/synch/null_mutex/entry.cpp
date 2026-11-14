/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/synch/null_mutex/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/synch/null_mutex`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
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


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_null_mutex_LOCK_UNLOCK();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_null_mutex_LOCK_UNLOCK);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_null_mutex_LOCK_UNLOCK()
{
    stlsoft::null_mutex mx;
    mx.lock();
    mx.unlock();
    TEST_BOOLEAN_TRUE(true);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
