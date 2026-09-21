/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.shims.logical.is_null.std.unique_ptr/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/shims/logical/is_null/std/unique_ptr`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/shims/logical/is_null/std/unique_ptr.hpp>
#include <stlsoft/shims/access/string.hpp>
#include <memory>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_is_null_unique_ptr(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.shims.logical.is_null.std.unique_ptr", verbosity))
    {
        XTESTS_RUN_CASE(test_is_null_unique_ptr);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_is_null_unique_ptr()
{
    std::unique_ptr<int> empty;
    std::unique_ptr<int> nonempty(new int(1));

    TEST_BOOLEAN_TRUE(stlsoft::is_null(empty));
    TEST_BOOLEAN_FALSE(stlsoft::is_null(nonempty));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
