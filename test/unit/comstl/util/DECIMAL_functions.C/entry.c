/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/util/DECIMAL_functions.C/entry.c
 *
 * Purpose: Unit-tests for `comstl_C_DECIMAL_compare`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/util/DECIMAL_functions.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>
#include <string.h>

static void TEST_COMPARE_EQUAL_ZERO(void);
static void TEST_COMPARE_SAME_SCALE(void);
static void TEST_COMPARE_DIFFERENT_SIGN(void);

static void init_decimal(DECIMAL* dec, BYTE sign, BYTE scale, ULONG hi, ULONG mid, ULONG lo)
{
    memset(dec, 0, sizeof(*dec));
    dec->sign = sign;
    dec->scale = scale;
    dec->Hi32 = hi;
    dec->Mid32 = mid;
    dec->Lo32 = lo;
}

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_COMPARE_EQUAL_ZERO);
        XTESTS_RUN_CASE(TEST_COMPARE_SAME_SCALE);
        XTESTS_RUN_CASE(TEST_COMPARE_DIFFERENT_SIGN);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

static void TEST_COMPARE_EQUAL_ZERO(void)
{
    DECIMAL lhs;
    DECIMAL rhs;

    init_decimal(&lhs, 0, 0, 0, 0, 0);
    init_decimal(&rhs, DECIMAL_NEG, 0, 0, 0, 0);

    TEST_INT_EQ(0, comstl_C_DECIMAL_compare(&lhs, &rhs));
}

static void TEST_COMPARE_SAME_SCALE(void)
{
    DECIMAL lhs;
    DECIMAL rhs;

    init_decimal(&lhs, 0, 2, 0, 0, 100);
    init_decimal(&rhs, 0, 2, 0, 0, 200);

    TEST_INT_LT(0, comstl_C_DECIMAL_compare(&lhs, &rhs));
    TEST_INT_GT(0, comstl_C_DECIMAL_compare(&rhs, &lhs));
}

static void TEST_COMPARE_DIFFERENT_SIGN(void)
{
    DECIMAL lhs;
    DECIMAL rhs;

    init_decimal(&lhs, DECIMAL_NEG, 0, 0, 0, 5);
    init_decimal(&rhs, 0, 0, 0, 0, 5);

    TEST_INT_LT(0, comstl_C_DECIMAL_compare(&lhs, &rhs));
    TEST_INT_GT(0, comstl_C_DECIMAL_compare(&rhs, &lhs));
}

/* ///////////////////////////// end of file //////////////////////////// */
