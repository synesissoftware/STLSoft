/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/shims/attribute/get_synch_handle/entry.cpp
 *
 * Purpose: Unit-tests for `winstl::get_synch_handle` attribute shims for MFC types.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/shims/attribute/get_synch_handle.hpp>
#include <afxwin.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_EVENT_HANDLE();
    static void TEST_MUTEX_HANDLE();
    static void TEST_SEMAPHORE_HANDLE();
    static void TEST_WINTHREAD_NULL_HANDLE();
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
        XTESTS_RUN_CASE(TEST_EVENT_HANDLE);
        XTESTS_RUN_CASE(TEST_MUTEX_HANDLE);
        XTESTS_RUN_CASE(TEST_SEMAPHORE_HANDLE);
        XTESTS_RUN_CASE(TEST_WINTHREAD_NULL_HANDLE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_EVENT_HANDLE()
{
    CEvent ev(FALSE, FALSE);

    TEST_PTR_NE(NULL, winstl::get_synch_handle(ev));
    TEST_PTR_EQ(static_cast<HANDLE>(ev), winstl::get_synch_handle(ev));
}

static void TEST_MUTEX_HANDLE()
{
    CMutex mx(FALSE);

    TEST_PTR_NE(NULL, winstl::get_synch_handle(mx));
    TEST_PTR_EQ(static_cast<HANDLE>(mx), winstl::get_synch_handle(mx));
}

static void TEST_SEMAPHORE_HANDLE()
{
    CSemaphore sem(1, 1);

    TEST_PTR_NE(NULL, winstl::get_synch_handle(sem));
    TEST_PTR_EQ(static_cast<HANDLE>(sem), winstl::get_synch_handle(sem));
}

static void TEST_WINTHREAD_NULL_HANDLE()
{
    CWinThread th;

    TEST_PTR_EQ(NULL, winstl::get_synch_handle(th));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
