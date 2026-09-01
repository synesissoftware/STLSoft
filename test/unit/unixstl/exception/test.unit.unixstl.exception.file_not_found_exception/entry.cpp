/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.exception.file_not_found_exception/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/exception/file_not_found_exception.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/exception/file_not_found_exception.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_file_not_found(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.exception.file_not_found_exception", verbosity))
    {
        XTESTS_RUN_CASE(test_file_not_found);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_file_not_found()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::file_not_found_exception x("/no/such/file", ENOENT);

    TEST_INT_EQ(ENOENT, x.status_code());
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
