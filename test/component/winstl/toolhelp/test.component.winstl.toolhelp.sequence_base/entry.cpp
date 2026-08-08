/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.toolhelp.sequence_base/entry.cpp
 *
 * Purpose: Component-tests for `toolhelp/sequence_base`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/toolhelp/sequence_base.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_enumeration(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.toolhelp.sequence_base", verbosity))
    {
        XTESTS_RUN_CASE(test_enumeration);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_enumeration(void)
{
    winstl::sequence_base seq;
    unsigned count = 0;
    for (winstl::sequence_base::const_iterator i = seq.begin(); i != seq.end(); ++i)
    {
        ++count;
        if (count > 0) break;
    }
    TEST_UINT_NE(0u, count);
}
