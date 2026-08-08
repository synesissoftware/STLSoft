/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.synch.spin_mutex_policies/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/synch/spin_mutex_policies.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/synch/spin_mutex_policies.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_default_policy_type_exists()
{
    STLSOFT_SUPPRESS_UNUSED(typeid(unixstl::yield_on_N_spin_mutex_policy<1000>));
    TEST_PASSED();
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.synch.spin_mutex_policies", verbosity))
    {
        XTESTS_RUN_CASE(test_default_policy_type_exists);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
