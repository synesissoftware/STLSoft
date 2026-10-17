/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.DECIMAL_functions.C/entry.c
 *
 * Purpose: Unit-tests for `comstl_C_DECIMAL_compare`.
 *
 * Created: 9th August 2026
 * Updated: 12th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/util/DECIMAL_functions.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>
#include <string.h>

static void test_compare_equal_zero(void);
static void test_compare_same_scale(void);
static void test_compare_different_sign(void);

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

    if (XTESTS_START_RUNNER("test.unit.comstl.util.DECIMAL_functions.C", verbosity))
    {
        XTESTS_RUN_CASE(test_compare_equal_zero);
        XTESTS_RUN_CASE(test_compare_same_scale);
        XTESTS_RUN_CASE(test_compare_different_sign);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

static void test_compare_equal_zero(void)
{
    DECIMAL lhs;
    DECIMAL rhs;

    init_decimal(&lhs, 0, 0, 0, 0, 0);
    init_decimal(&rhs, DECIMAL_NEG, 0, 0, 0, 0);

    TEST_INT_EQ(0, comstl_C_DECIMAL_compare(&lhs, &rhs));
}

static void test_compare_same_scale(void)
{
    DECIMAL lhs;
    DECIMAL rhs;

    init_decimal(&lhs, 0, 2, 0, 0, 100);
    init_decimal(&rhs, 0, 2, 0, 0, 200);

    TEST_INT_LT(0, comstl_C_DECIMAL_compare(&lhs, &rhs));
    TEST_INT_GT(0, comstl_C_DECIMAL_compare(&rhs, &lhs));
}

static void test_compare_different_sign(void)
{
    DECIMAL lhs;
    DECIMAL rhs;

    init_decimal(&lhs, DECIMAL_NEG, 0, 0, 0, 5);
    init_decimal(&rhs, 0, 0, 0, 0, 5);

    TEST_INT_LT(0, comstl_C_DECIMAL_compare(&lhs, &rhs));
    TEST_INT_GT(0, comstl_C_DECIMAL_compare(&rhs, &lhs));
}

/* ///////////////////////////// end of file //////////////////////////// */
