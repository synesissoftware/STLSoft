/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/synch/atomic_functions/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/synch/atomic_functions.h`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/synch/atomic_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_atomic_increment_DECREMENT();
    static void TEST_atomic_exchange();
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
        XTESTS_RUN_CASE(TEST_atomic_increment_DECREMENT);
        XTESTS_RUN_CASE(TEST_atomic_exchange);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_atomic_increment_DECREMENT()
{
    unixstl::atomic_int_t n = 0;

    unixstl::atomic_increment(&n);
    TEST_INT_EQ(1, n);

    unixstl::atomic_decrement(&n);
    TEST_INT_EQ(0, n);
}

static void TEST_atomic_exchange()
{
    unixstl::atomic_int_t n = 5;

    TEST_INT_EQ(5, unixstl::atomic_exchange(&n, 9));
    TEST_INT_EQ(9, n);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
