/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.acestl.shims.logical.is_empty.string_base/entry.cpp
 *
 * Purpose: Unit-tests for is_empty shims for `ACE_String_Base`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
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

    static void TEST_empty_string(void);
    static void TEST_non_empty_string(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.acestl.shims.logical.is_empty.string_base", verbosity))
    {
        XTESTS_RUN_CASE(TEST_empty_string);
        XTESTS_RUN_CASE(TEST_non_empty_string);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_empty_string()
{
    ACE_CString const s;

    TEST_BOOLEAN_TRUE(stlsoft::is_empty(s));
    TEST_BOOLEAN_TRUE(stlsoft::is_empty(s, stlsoft::is_empty_type()));
}

static void TEST_non_empty_string()
{
    ACE_CString const s("acestl");

    TEST_BOOLEAN_FALSE(stlsoft::is_empty(s));
    TEST_BOOLEAN_FALSE(stlsoft::is_empty(s, stlsoft::is_empty_type()));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
