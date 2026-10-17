/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.inetstl.exception.throw_policies/entry.cpp
 *
 * Purpose: Unit-tests for `inetstl::throw_internet_exception_policy`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <inetstl/exception/throw_policies.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_throw_status_code(void);
    static void TEST_throw_reason_and_status_code(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
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
