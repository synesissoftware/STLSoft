/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.error.conversion_error/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/error/conversion_error`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/error/conversion_error.hpp>


#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_conversion_error();

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.error.conversion_error", verbosity))
    {
        XTESTS_RUN_CASE(test_conversion_error);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {


static void test_conversion_error()
{
    stlsoft::conversion_error e("test", 42);
    TEST_INTEGER_EQUAL(42, e.get_error_code());
    TEST_PTR_NE(NULL, e.what());
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
