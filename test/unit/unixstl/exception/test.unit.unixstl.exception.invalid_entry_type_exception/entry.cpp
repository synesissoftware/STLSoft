/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.exception.invalid_entry_type_exception/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/exception/invalid_entry_type_exception.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/exception/invalid_entry_type_exception.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_invalid_entry_type(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.exception.invalid_entry_type_exception", verbosity))
    {
        XTESTS_RUN_CASE(test_invalid_entry_type);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_invalid_entry_type()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    unixstl::invalid_entry_type_exception x("/entry", EINVAL);

    TEST_INT_EQ(EINVAL, x.status_code());
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
