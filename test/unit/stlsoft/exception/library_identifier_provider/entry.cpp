/* Purpose: unit-tests for stlsoft/exception/library_identifier_provider */
#include <stlsoft/exception/library_identifier_provider.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
static void TEST_HEADER_COMPILES();
int main(int argc, char* argv[]) {
    int retCode = EXIT_SUCCESS; int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER(__FILE__, verbosity)) {
        XTESTS_RUN_CASE(TEST_HEADER_COMPILES);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}
static void TEST_HEADER_COMPILES() { TEST_BOOLEAN_TRUE(true); }
