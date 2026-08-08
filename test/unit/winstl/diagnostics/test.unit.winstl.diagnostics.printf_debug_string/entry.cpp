/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.diagnostics.printf_debug_string/entry.cpp
 *
 * Purpose: Unit-tests for `diagnostics/printf_debug_string`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/diagnostics/printf_debug_string.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_output(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.diagnostics.printf_debug_string", verbosity))
    {
        XTESTS_RUN_CASE(test_output);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_output(void)
{
    winstl_C_printf_debug_string("STLSoft test");
    TEST_PASSED();
}
