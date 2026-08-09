/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.system.environment_sequence/entry.cpp
 *
 * Purpose: Component-tests for `system/environment_sequence`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/system/environment_sequence.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_enumeration(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.system.environment_sequence", verbosity))
    {
        XTESTS_RUN_CASE(test_enumeration);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_enumeration(void)
{
    winstl::environment_sequence seq;
    unsigned count = 0;
    for (winstl::environment_sequence::const_iterator i = seq.begin(); i != seq.end(); ++i)
    {
        ++count;
        if (count > 0) break;
    }
    TEST_UINT_NE(0u, count);
}
