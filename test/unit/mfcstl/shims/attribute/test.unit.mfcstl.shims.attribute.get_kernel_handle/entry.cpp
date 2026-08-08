/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.shims.attribute.get_kernel_handle/entry.cpp
 *
 * Purpose: Unit-tests for `winstl::get_kernel_handle` attribute shims for MFC types.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <mfcstl/shims/attribute/get_kernel_handle.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void TEST_event_handle();
static void TEST_mutex_handle();
static void TEST_semaphore_handle();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.shims.attribute.get_kernel_handle", verbosity))
    {
        XTESTS_RUN_CASE(TEST_event_handle);
        XTESTS_RUN_CASE(TEST_mutex_handle);
        XTESTS_RUN_CASE(TEST_semaphore_handle);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_event_handle()
{
    CEvent ev(FALSE, FALSE);

    TEST_PTR_NE(NULL, winstl::get_kernel_handle(ev));
    TEST_PTR_EQ(static_cast<HANDLE>(ev), winstl::get_kernel_handle(ev));
}

static void TEST_mutex_handle()
{
    CMutex mx(FALSE);

    TEST_PTR_NE(NULL, winstl::get_kernel_handle(mx));
    TEST_PTR_EQ(static_cast<HANDLE>(mx), winstl::get_kernel_handle(mx));
}

static void TEST_semaphore_handle()
{
    CSemaphore sem(1, 1);

    TEST_PTR_NE(NULL, winstl::get_kernel_handle(sem));
    TEST_PTR_EQ(static_cast<HANDLE>(sem), winstl::get_kernel_handle(sem));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
