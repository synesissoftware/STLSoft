/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/shims/attribute/get_FILE_ptr/get_FILE_ptr/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/shims/attribute/get_FILE_ptr`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/shims/attribute/get_FILE_ptr.hpp>
#include <stlsoft/shims/access/string.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_GET__FILE__PTR_NULL();
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
        XTESTS_RUN_CASE(TEST_GET__FILE__PTR_NULL);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_GET__FILE__PTR_NULL()
{
    FILE* fp = NULL;
    TEST_PTR_EQ(NULL, stlsoft::get_FILE_ptr(fp));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
