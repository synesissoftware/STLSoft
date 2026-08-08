/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.synch.common/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/synch/common.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/synch/common.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_common_header_compiles()
{
#ifdef UNIXSTL_USING_PTHREADS
    TEST_BOOLEAN_TRUE(true);
#else
    TEST_PASSED();
#endif
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.synch.common", verbosity))
    {
        XTESTS_RUN_CASE(test_common_header_compiles);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
