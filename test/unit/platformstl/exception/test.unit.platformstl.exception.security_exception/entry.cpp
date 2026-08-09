/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.platformstl.exception.security_exception/entry.cpp
 *
 * Purpose: Unit-tests for `platformstl/exception/security_exception.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <platformstl/exception/security_exception.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_type_exists(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.exception.security_exception", verbosity))
    {
        XTESTS_RUN_CASE(test_type_exists);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_type_exists(void)
{
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::security_exception));
    TEST_PASSED();
}

