/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.conversion.int_to_string/entry.cpp
 *
 * Purpose: Unit-tests for `conversion/int_to_string`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/conversion/int_to_string.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_decimal(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.conversion.int_to_string", verbosity))
    {
        XTESTS_RUN_CASE(test_decimal);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_decimal(void)
{
    TEST_MS_EQ("42", winstl::int_to_string<char>(42));
}
