/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.toolhelp.thread_sequence/entry.cpp
 *
 * Purpose: Component-tests for `toolhelp/thread_sequence`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/toolhelp/thread_sequence.hpp>
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
    if (XTESTS_START_RUNNER("test.component.winstl.toolhelp.thread_sequence", verbosity))
    {
        XTESTS_RUN_CASE(test_enumeration);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_enumeration(void)
{
    winstl::thread_sequence seq;
    unsigned count = 0;
    for (winstl::thread_sequence::const_iterator i = seq.begin(); i != seq.end(); ++i)
    {
        ++count;
        if (count > 0) break;
    }
    TEST_UINT_NE(0u, count);
}
