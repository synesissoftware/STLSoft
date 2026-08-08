/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.synch.exceptions/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/synch/exceptions.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/synch/exceptions.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_synch_exception_carries_code()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::synchronisation_exception x("lock failed", EINVAL);
    TEST_INT_EQ(EINVAL, x.status_code());
    TEST_PTR_NE(NULL, x.what());
#endif
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.synch.exceptions", verbosity))
    {
        XTESTS_RUN_CASE(test_synch_exception_carries_code);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
