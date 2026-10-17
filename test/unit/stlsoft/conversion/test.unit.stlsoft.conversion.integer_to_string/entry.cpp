/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.integer_to_string/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/conversion/integer_to_string`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/conversion/integer_to_string.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_integer_to_decimal_string(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.integer_to_string", verbosity))
    {
        XTESTS_RUN_CASE(test_integer_to_decimal_string);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_integer_to_decimal_string()
{
    char buf[32];
    char const* s = stlsoft::integer_to_decimal_string(buf, STLSOFT_NUM_ELEMENTS(buf), 99);
    TEST_PTR_NE(NULL, s);
    TEST_MS_EQ("99", s);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
