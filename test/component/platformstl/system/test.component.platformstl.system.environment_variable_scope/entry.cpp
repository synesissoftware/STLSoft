/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.platformstl.system.environment_variable_scope/entry.cpp
 *
 * Purpose: Unit-tests for `platformstl::environment_variable_scope`.
 *
 * Created: 26th April 2025
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <platformstl/system/environment_variable_scope.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <platformstl/system/environment_variable.hpp>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_PATH();
    static void TEST_NON_EXISTING_NAME();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.platformstl.system.environment_variable_scope", verbosity))
    {
        XTESTS_RUN_CASE(TEST_PATH);
        XTESTS_RUN_CASE(TEST_NON_EXISTING_NAME);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

    using platformstl::environment_variable;
    using platformstl::environment_variable_scope;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_PATH()
{
    environment_variable const  ev_PATH_0("PATH");

    {
        environment_variable_scope const    evs_PATH_1("PATH", "nothing-else");
        environment_variable const          ev_PATH_1("PATH");

        TEST_MS_EQ("nothing-else", ev_PATH_1);
    }

    environment_variable const  ev_PATH_0_b("PATH");

    TEST_MS_EQ(ev_PATH_0, ev_PATH_0_b);
}

static void TEST_NON_EXISTING_NAME()
{
    static char const s_name[] = "non_existent_name_AF15995B_C8C1_4772_BFD8_9A3DE85DFBEC";

    environment_variable const  ev_PATH_0(s_name);

    TEST_INT_EQ(0, ev_PATH_0.size());

    {
        environment_variable_scope const    evs_PATH_1(s_name, "something");
        environment_variable const          ev_PATH_1(s_name);

        TEST_MS_EQ("something", ev_PATH_1);
    }

    environment_variable const  ev_PATH_0_b(s_name);

    TEST_INT_EQ(0, ev_PATH_0_b.size());

    TEST_MS_EQ(ev_PATH_0, ev_PATH_0_b);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

