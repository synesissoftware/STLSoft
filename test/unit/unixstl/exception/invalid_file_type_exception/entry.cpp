/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/unixstl/exception/invalid_file_type_exception/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/exception/invalid_file_type_exception.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/exception/invalid_file_type_exception.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_INVALID_FILE_TYPE();
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
        XTESTS_RUN_CASE(TEST_INVALID_FILE_TYPE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_INVALID_FILE_TYPE()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::invalid_file_type_exception x("/file", EINVAL);

    TEST_INT_EQ(EINVAL, x.status_code());
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
