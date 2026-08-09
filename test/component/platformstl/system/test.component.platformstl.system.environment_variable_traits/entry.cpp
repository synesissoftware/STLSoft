/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.platformstl.system.environment_variable_traits/entry.cpp
 *
 * Purpose: Unit-tests for `platformstl::environment_variable_traits`.
 *
 * Created: 30th December 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <platformstl/system/environment_variable_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

#ifdef PLATFORMSTL_ENVVAR_SET_SUPPORTED

    static void TEST_set_variable();
#endif /* PLATFORMSTL_ENVVAR_SET_SUPPORTED */
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.platformstl.system.environment_variable_traits", verbosity))
    {
#ifdef PLATFORMSTL_ENVVAR_SET_SUPPORTED

        XTESTS_RUN_CASE(TEST_set_variable);
#endif /* PLATFORMSTL_ENVVAR_SET_SUPPORTED */

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

    using platformstl::environment_variable_traits;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

#ifdef PLATFORMSTL_ENVVAR_SET_SUPPORTED

static void TEST_set_variable()
{
    {
        int const r = environment_variable_traits::set_variable("EV_2C4D392B_22CD_4452_9525_382043AD2611", "some-value");

        TEST_INT_EQ(0, r);
    }

    {
        char const* ev_value = environment_variable_traits::get_variable("EV_2C4D392B_22CD_4452_9525_382043AD2611");

        XTESTS_REQUIRE(TEST_PTR_NE(NULL, ev_value));

        TEST_MS_EQ("some-value", ev_value);
    }

    {
        int const r = environment_variable_traits::erase_variable("EV_2C4D392B_22CD_4452_9525_382043AD2611");

        TEST_INT_EQ(0, r);
    }
}
#endif /* PLATFORMSTL_ENVVAR_SET_SUPPORTED */
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

