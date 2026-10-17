/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.shims.logical.is_empty.arrays/entry.cpp
 *
 * Purpose: Unit-tests for is_empty shims for MFC array classes.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/shims/logical/is_empty/arrays.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_empty_arrays(void);
    static void TEST_non_empty_arrays(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.shims.logical.is_empty.arrays", verbosity))
    {
        XTESTS_RUN_CASE(TEST_empty_arrays);
        XTESTS_RUN_CASE(TEST_non_empty_arrays);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_empty_arrays()
{
    CUIntArray const uar;
    CStringArray const sar;

    TEST_BOOLEAN_TRUE(stlsoft::is_empty(uar));
    TEST_BOOLEAN_TRUE(stlsoft::is_empty(sar));
}

static void TEST_non_empty_arrays()
{
    CUIntArray uar;
    CStringArray sar;

    uar.Add(1);
    sar.Add(_T("x"));

    TEST_BOOLEAN_FALSE(stlsoft::is_empty(uar));
    TEST_BOOLEAN_FALSE(stlsoft::is_empty(sar));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
