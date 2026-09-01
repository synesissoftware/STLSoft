/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.synch.semaphore/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/synch/semaphore.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/synch/semaphore.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_semaphore_wait_post(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.synch.semaphore", verbosity))
    {
        XTESTS_RUN_CASE(test_semaphore_wait_post);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_semaphore_wait_post()
{
    unixstl::semaphore sem(0);

    sem.unlock();

    sem.lock();
    TEST_PASSED();
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
