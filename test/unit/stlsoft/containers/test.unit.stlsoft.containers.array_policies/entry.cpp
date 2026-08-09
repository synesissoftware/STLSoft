/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.containers.array_policies/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/containers/array_policies`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/containers/array_policies.hpp>
#include <vector>
#include <string>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_array_policies_default_construct(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.containers.array_policies", verbosity))
    {
        XTESTS_RUN_CASE(test_array_policies_default_construct);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_array_policies_default_construct()
{
    stlsoft::do_construct_n<int> policy;
    int buf[3];

    policy(&buf[0], 3);

    TEST_INTEGER_EQUAL(0, buf[0]);
    TEST_INTEGER_EQUAL(0, buf[2]);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
