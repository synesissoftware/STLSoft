/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.time.conversion_functions/entry.cpp
 *
 * Purpose: Unit-tests for `time/conversion_functions`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/time/comparison_functions.h>
#include <winstl/util/struct_initialisers.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_FILETIME_ordering(void);
    static void test_SYSTEMTIME_ordering(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.time.conversion_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_FILETIME_ordering);
        XTESTS_RUN_CASE(test_SYSTEMTIME_ordering);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_FILETIME_ordering(void)
{
    FILETIME ft1 = { 0, 0 };
    FILETIME ft2 = { 1, 0 };

    TEST_INT_EQ(0, winstl::compare(ft1, ft1));
    TEST_INT_LT(0, winstl::compare(ft1, ft2));
    TEST_INT_GT(0, winstl::compare(ft2, ft1));
}

static void test_SYSTEMTIME_ordering(void)
{
    SYSTEMTIME st1; SYSTEMTIME st2;
    winstl::init_struct(st1);
    winstl::init_struct(st2);
    st2.wYear = 2001;

    TEST_INT_EQ(0, winstl::compare(st1, st1));
    TEST_INT_LT(0, winstl::compare(st1, st2));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
