/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.exception.throw_policies/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/exception/throw_policies.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/exception/throw_policies.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_unix_exception_policy_throws(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.exception.throw_policies", verbosity))
    {
        XTESTS_RUN_CASE(test_unix_exception_policy_throws);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_unix_exception_policy_throws()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    try
    {
        unixstl::unix_exception_policy()(ENOENT);
        TEST_FAIL("expected exception");
    }
    catch (unixstl::unixstl_exception const& x)
    {
        TEST_INT_EQ(ENOENT, x.status_code());
    }

    try
    {
        unixstl::unix_exception_policy()("reason", EACCES);
        TEST_FAIL("expected exception");
    }
    catch (unixstl::unixstl_exception const& x)
    {
        TEST_INT_EQ(EACCES, x.status_code());
    }
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
