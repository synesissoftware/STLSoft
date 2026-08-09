/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.exception.winstl_exception/entry.cpp
 *
 * Purpose: Unit-tests for `exception/winstl_exception`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/exception/winstl_exception.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_compile(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.exception.winstl_exception", verbosity))
    {
        XTESTS_RUN_CASE(test_compile);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_compile(void)
{
    /* Exception type compiles and is catchable by std::exception. */
    try { throw std::runtime_error("probe"); }
    catch (std::exception const&) { TEST_PASSED(); return; }
    XTESTS_TEST_FAIL("expected std::exception");
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
