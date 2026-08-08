/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.exception.unixstl_exception/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/exception/unixstl_exception.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/exception/unixstl_exception.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_status_code_and_message()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::unixstl_exception x(ENOENT);

    TEST_INT_EQ(ENOENT, x.status_code());
    TEST_PTR_NE(NULL, x.what());

    unixstl::unixstl_exception x2("reason", EACCES);
    TEST_INT_EQ(EACCES, x2.status_code());
    TEST_PTR_NE(NULL, x2.what());
#endif
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.exception.unixstl_exception", verbosity))
    {
        XTESTS_RUN_CASE(test_status_code_and_message);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
