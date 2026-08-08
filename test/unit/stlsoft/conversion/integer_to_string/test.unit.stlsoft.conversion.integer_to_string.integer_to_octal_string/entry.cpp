/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.integer_to_string.integer_to_octal_string/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/conversion/integer_to_string/integer_to_octal_string`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/conversion/integer_to_string/integer_to_octal_string.hpp>


#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_integer_to_octal_string();

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.integer_to_string.integer_to_octal_string", verbosity))
    {
        XTESTS_RUN_CASE(test_integer_to_octal_string);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {


static void test_integer_to_octal_string()
{
    char buf[32];
    char const* s = stlsoft::integer_to_octal_string(buf, STLSOFT_NUM_ELEMENTS(buf), 8);
    TEST_MS_EQ("10", s);
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
