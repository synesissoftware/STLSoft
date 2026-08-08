/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.stlsoft.diagnostics.stopwatch_scope/entry.cpp
 *
 * Purpose: Component-tests for `stlsoft/diagnostics/stopwatch_scope`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/diagnostics/stopwatch_scope.hpp>
#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>


#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_stopwatch_scope();

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.stlsoft.diagnostics.stopwatch_scope", verbosity))
    {
        XTESTS_RUN_CASE(test_stopwatch_scope);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {


static void test_stopwatch_scope()
{
    stlsoft::std_chrono_hrc_stopwatch sw;
    {
        stlsoft::stopwatch_scope<stlsoft::std_chrono_hrc_stopwatch> scope(sw);
    }
    TEST_BOOLEAN_TRUE(sw.get_seconds() >= 0);
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
