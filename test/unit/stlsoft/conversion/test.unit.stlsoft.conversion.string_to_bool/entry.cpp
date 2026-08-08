/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.string_to_bool/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/conversion/string_to_bool`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/conversion/string_to_bool.hpp>


#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_try_parse_to_bool();

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.string_to_bool", verbosity))
    {
        XTESTS_RUN_CASE(test_try_parse_to_bool);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {


static void test_try_parse_to_bool()
{
    bool result = false;
    TEST_BOOLEAN_TRUE(stlsoft::try_parse_to_bool("true", &result));
    TEST_BOOLEAN_TRUE(result);
    result = true;
    TEST_BOOLEAN_TRUE(stlsoft::try_parse_to_bool("false", &result));
    TEST_BOOLEAN_FALSE(result);
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
