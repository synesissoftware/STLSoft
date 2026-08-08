/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.synch.thread_mutex/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/synch/thread_mutex.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/synch/thread_mutex.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


#include <stlsoft/synch/lock_scope.hpp>

static void test_thread_mutex_lock_unlock()
{
    unixstl::thread_mutex mx;

    mx.lock();
    TEST_PASSED();
    mx.unlock();
}

static void test_thread_mutex_try_lock()
{
    unixstl::thread_mutex mx;

    TEST_BOOLEAN_TRUE(mx.try_lock());
    mx.unlock();
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.synch.thread_mutex", verbosity))
    {
        XTESTS_RUN_CASE(test_thread_mutex_lock_unlock);
        XTESTS_RUN_CASE(test_thread_mutex_try_lock);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
