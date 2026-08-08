/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.exception.operating_environment_exception/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/exception/operating_environment_exception.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/exception/operating_environment_exception.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_operating_environment()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::operating_environment_exception x("env", ENOENT);

    TEST_INT_EQ(ENOENT, x.status_code());
#endif
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.exception.operating_environment_exception", verbosity))
    {
        XTESTS_RUN_CASE(test_operating_environment);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
