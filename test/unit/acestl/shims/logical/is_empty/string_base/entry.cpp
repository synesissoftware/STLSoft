/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/acestl/shims/logical/is_empty/string_base/entry.cpp
 *
 * Purpose: Unit-tests for is_empty shims for `ACE_String_Base`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <acestl/shims/logical/is_empty/string_base.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <ace/SString.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_EMPTY_STRING();
    static void TEST_NON_EMPTY_STRING();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_EMPTY_STRING);
        XTESTS_RUN_CASE(TEST_NON_EMPTY_STRING);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_EMPTY_STRING()
{
    ACE_CString const s;

    TEST_BOOLEAN_TRUE(stlsoft::is_empty(s));
}

static void TEST_NON_EMPTY_STRING()
{
    ACE_CString const s("acestl");

    TEST_BOOLEAN_FALSE(stlsoft::is_empty(s));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
