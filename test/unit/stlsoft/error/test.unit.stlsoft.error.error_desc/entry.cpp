/* Purpose: unit-tests for stlsoft/error/error_desc */
#include <stlsoft/error/error_desc.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
static void test_header_compiles();
int main(int argc, char* argv[]) {
    int retCode = EXIT_SUCCESS; int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.stlsoft.error.error_desc", verbosity)) {
        XTESTS_RUN_CASE(test_header_compiles);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}
static void test_header_compiles() { TEST_BOOLEAN_TRUE(true); }
