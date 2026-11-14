/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/util/CY_functions.C/entry.c
 *
 * Purpose: Unit-tests for `comstl_C_CY_compare`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/util/CY_functions.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

static void TEST_COMPARE_EQUAL_HI_AND_LO(void);
static void TEST_COMPARE_LESS(void);
static void TEST_COMPARE_GREATER(void);

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_COMPARE_EQUAL_HI_AND_LO);
        XTESTS_RUN_CASE(TEST_COMPARE_LESS);
        XTESTS_RUN_CASE(TEST_COMPARE_GREATER);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

static void TEST_COMPARE_EQUAL_HI_AND_LO(void)
{
    CY lhs = { { 0, 42 } };
    CY rhs = { { 0, 42 } };

    /* When Hi and Lo are equal, comstl_C_CY_compare returns +1 (not 0). */
    TEST_INT_GT(0, comstl_C_CY_compare(&lhs, &rhs));
}

static void TEST_COMPARE_LESS(void)
{
    CY lhs = { { 0, 1 } };
    CY rhs = { { 0, 2 } };

    TEST_INT_LT(0, comstl_C_CY_compare(&lhs, &rhs));
    TEST_INT_LT(0, comstl_C_CY_compare(&lhs, &rhs));
}

static void TEST_COMPARE_GREATER(void)
{
    CY lhs = { { 1, 0 } };
    CY rhs = { { 0, 0xffffffff } };

    TEST_INT_GT(0, comstl_C_CY_compare(&lhs, &rhs));
}

/* ///////////////////////////// end of file //////////////////////////// */
