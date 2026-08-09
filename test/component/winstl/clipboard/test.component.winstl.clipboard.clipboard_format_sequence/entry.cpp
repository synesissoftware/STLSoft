/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.clipboard.clipboard_format_sequence/entry.cpp
 *
 * Purpose: Component-tests for `clipboard/clipboard_format_sequence`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/clipboard/clipboard_format_sequence.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_enumerate(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.winstl.clipboard.clipboard_format_sequence", verbosity))
    {
        XTESTS_RUN_CASE(test_enumerate);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_enumerate(void)
{
    /* Does not open clipboard; only compiles sequence type. */
    winstl::clipboard_format_sequence::const_iterator b;
    winstl::clipboard_format_sequence::const_iterator e;
    (void)b; (void)e;
    TEST_PASSED();
}
