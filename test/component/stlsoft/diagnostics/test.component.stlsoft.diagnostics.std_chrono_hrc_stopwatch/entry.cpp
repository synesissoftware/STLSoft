/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.stlsoft.diagnostics.std_chrono_hrc_stopwatch/entry.cpp
 *
 * Purpose: Component-tests for `stlsoft/diagnostics/std_chrono_hrc_stopwatch`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>


#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_chrono_stopwatch();

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.stlsoft.diagnostics.std_chrono_hrc_stopwatch", verbosity))
    {
        XTESTS_RUN_CASE(test_chrono_stopwatch);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {


static void test_chrono_stopwatch()
{
    stlsoft::std_chrono_hrc_stopwatch sw;
    sw.start();
    sw.stop();
    TEST_BOOLEAN_TRUE(sw.get_seconds() >= 0);
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
