/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.inetstl.exception.throw_policies/entry.cpp
 *
 * Purpose: Unit-tests for `inetstl::throw_internet_exception_policy`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <inetstl/exception/throw_policies.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>

#ifndef STLSOFT_CF_EXCEPTION_SUPPORT
# error This test requires exception support
#endif /* !STLSOFT_CF_EXCEPTION_SUPPORT */

#ifdef INETSTL_OS_IS_UNIX
# include <errno.h>
#endif /* INETSTL_OS_IS_UNIX */


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_throw_status_code();
    static void TEST_throw_reason_and_status_code();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.inetstl.exception.throw_policies", verbosity))
    {
        XTESTS_RUN_CASE_THAT_THROWS(TEST_throw_status_code, inetstl::inetstl_exception);
        XTESTS_RUN_CASE_THAT_THROWS(TEST_throw_reason_and_status_code, inetstl::inetstl_exception);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_throw_status_code()
{
#if defined(INETSTL_OS_IS_UNIX)

    inetstl::throw_internet_exception_policy()(EINVAL);
#elif defined(INETSTL_OS_IS_WINDOWS)

    inetstl::throw_internet_exception_policy()(ERROR_FILE_NOT_FOUND);
#else /* ? platform */

# error Platform not discriminated
#endif /* platform */
}

static void TEST_throw_reason_and_status_code()
{
#if defined(INETSTL_OS_IS_UNIX)

    inetstl::throw_internet_exception_policy()("policy reason", EACCES);
#elif defined(INETSTL_OS_IS_WINDOWS)

    inetstl::throw_internet_exception_policy()("policy reason", ERROR_ACCESS_DENIED);
#else /* ? platform */

# error Platform not discriminated
#endif /* platform */
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
