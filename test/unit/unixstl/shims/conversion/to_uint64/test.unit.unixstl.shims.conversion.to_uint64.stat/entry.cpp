/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.shims.conversion.to_uint64.stat/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/shims/conversion/to_uint64/stat.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <sys/stat.h>
#include <unixstl/shims/conversion/to_uint64/stat.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_to_uint64_from_stat(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.shims.conversion.to_uint64.stat", verbosity))
    {
        XTESTS_RUN_CASE(test_to_uint64_from_stat);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_to_uint64_from_stat()
{
    struct stat st = {};
    st.st_size = 12345;

    stlsoft::ss_uint64_t const v = stlsoft::to_uint64(st);

    TEST_BOOLEAN_TRUE(stlsoft::ss_uint64_t(12345) == v);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
