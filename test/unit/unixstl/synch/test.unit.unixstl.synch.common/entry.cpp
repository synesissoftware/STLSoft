/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.synch.common/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/synch/common.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/synch/common.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_common_header_compiles(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.synch.common", verbosity))
    {
        XTESTS_RUN_CASE(test_common_header_compiles);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_common_header_compiles()
{
#ifdef UNIXSTL_USING_PTHREADS
    TEST_BOOLEAN_TRUE(true);
#else
    TEST_PASSED();
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
