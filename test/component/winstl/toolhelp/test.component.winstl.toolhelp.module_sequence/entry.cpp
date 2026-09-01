/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.toolhelp.module_sequence/entry.cpp
 *
 * Purpose: Component-tests for `toolhelp/module_sequence`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/toolhelp/module_sequence.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_enumeration(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.winstl.toolhelp.module_sequence", verbosity))
    {
        XTESTS_RUN_CASE(test_enumeration);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_enumeration(void)
{
    winstl::module_sequence seq;
    unsigned count = 0;
    for (winstl::module_sequence::const_iterator i = seq.begin(); i != seq.end(); ++i)
    {
        ++count;
        if (count > 0) break;
    }
    TEST_UINT_NE(0u, count);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
