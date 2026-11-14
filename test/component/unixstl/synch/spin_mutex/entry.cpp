/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/synch/spin_mutex/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/synch/spin_mutex.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/synch/spin_mutex.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <stlsoft/synch/lock_scope.hpp>
#include <stlsoft/synch/lock_scope.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_LOCK_UNLOCK();
    static void TEST_LOCK_SCOPE();
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
        XTESTS_RUN_CASE(TEST_LOCK_UNLOCK);
        XTESTS_RUN_CASE(TEST_LOCK_SCOPE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_LOCK_UNLOCK()
{
    unixstl::spin_mutex mx;

    mx.lock();
    TEST_PASSED();
    mx.unlock();
}

static void TEST_LOCK_SCOPE()
{
    unixstl::spin_mutex mx;
    stlsoft::lock_scope<unixstl::spin_mutex> lock(mx);
    TEST_PASSED();
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
