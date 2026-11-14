/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/shims/logical/is_empty/lists/entry.cpp
 *
 * Purpose: Unit-tests for is_empty shims for MFC list classes.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/shims/logical/is_empty/lists.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_EMPTY_LISTS();
    static void TEST_NON_EMPTY_LISTS();
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
        XTESTS_RUN_CASE(TEST_EMPTY_LISTS);
        XTESTS_RUN_CASE(TEST_NON_EMPTY_LISTS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_EMPTY_LISTS()
{
    CPtrList const pl;
    CObList const ol;

    TEST_BOOLEAN_TRUE(stlsoft::is_empty(pl));
    TEST_BOOLEAN_TRUE(stlsoft::is_empty(ol));
}

static void TEST_NON_EMPTY_LISTS()
{
    CPtrList pl;
    CObList ol;

    pl.AddTail(reinterpret_cast<void*>(1));
    ol.AddTail(static_cast<CObject*>(NULL));

    TEST_BOOLEAN_FALSE(stlsoft::is_empty(pl));
    TEST_BOOLEAN_FALSE(stlsoft::is_empty(ol));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
