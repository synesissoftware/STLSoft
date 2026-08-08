/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.synch.event/entry.cpp
 *
 * Purpose: Unit-tests for `synch/event`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/synch/event.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_set_reset(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.synch.event", verbosity))
    {
        XTESTS_RUN_CASE(test_set_reset);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_set_reset(void)
{
    winstl::event ev(false, false);
    ev.set();
    ev.reset();
    TEST_PASSED();
}
