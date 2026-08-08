/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.synch.atomic_types/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/synch/atomic_types.h`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/synch/atomic_types.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


#include <stlsoft/meta/is_integral_type.hpp>

static void test_atomic_int_type_is_integral()
{
    static_assert(stlsoft::is_integral_type<unixstl::atomic_int_t>::value, "atomic_int_t must be integral");
    TEST_PASSED();
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.synch.atomic_types", verbosity))
    {
        XTESTS_RUN_CASE(test_atomic_int_type_is_integral);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
