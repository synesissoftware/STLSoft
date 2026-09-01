/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.exception.filesystem_exception/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/exception/filesystem_exception.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/exception/filesystem_exception.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_filesystem_exception(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.exception.filesystem_exception", verbosity))
    {
        XTESTS_RUN_CASE(test_filesystem_exception);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_filesystem_exception()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::filesystem_exception x("/path", ENOENT);

    TEST_INT_EQ(ENOENT, x.status_code());
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
