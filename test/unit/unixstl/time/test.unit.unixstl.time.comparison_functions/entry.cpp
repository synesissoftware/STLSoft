/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.time.comparison_functions/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/time/comparison_functions.h`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/time/comparison_functions.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_equal_timevals(void);
    static void test_lhs_before_rhs(void);
    static void test_lhs_after_rhs(void);
    static void test_microsecond_difference(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.time.comparison_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_equal_timevals);
        XTESTS_RUN_CASE(test_lhs_before_rhs);
        XTESTS_RUN_CASE(test_lhs_after_rhs);
        XTESTS_RUN_CASE(test_microsecond_difference);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_equal_timevals()
{
    struct timeval lhs = { 100, 500 };
    struct timeval rhs = { 100, 500 };

    TEST_INT_EQ(0, unixstl::compare(lhs, rhs));
    TEST_INT_EQ(0, unixstl::compare(&lhs, &rhs));
}

static void test_lhs_before_rhs()
{
    struct timeval lhs = { 100, 0 };
    struct timeval rhs = { 101, 0 };

    TEST_INT_EQ(-1, unixstl::compare(lhs, rhs));
}

static void test_lhs_after_rhs()
{
    struct timeval lhs = { 200, 1000 };
    struct timeval rhs = { 199, 999999 };

    TEST_INT_EQ(+1, unixstl::compare(lhs, rhs));
}

static void test_microsecond_difference()
{
    struct timeval lhs = { 1, 0 };
    struct timeval rhs = { 1, 42 };

    TEST_INT_EQ(-1, unixstl::compare(lhs, rhs));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
