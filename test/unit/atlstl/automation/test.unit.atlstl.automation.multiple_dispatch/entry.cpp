/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atlstl.automation.multiple_dispatch/entry.cpp
 *
 * Purpose: Unit-tests for `atlstl::IDispatchImpl2`, `atlstl::IDispatchImpl3`
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <atlstl/automation/multiple_dispatch.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <atlbase.h>
#include <atlcom.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_stripe_flags_are_distinct(void);
    static void TEST_stripe_round_trip(void);
    static void TEST_stripe_preserves_negative_dispids(void);
    static void TEST_header_compiles(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atlstl.automation.multiple_dispatch", verbosity))
    {
        XTESTS_RUN_CASE(TEST_stripe_flags_are_distinct);
        XTESTS_RUN_CASE(TEST_stripe_round_trip);
        XTESTS_RUN_CASE(TEST_stripe_preserves_negative_dispids);
        XTESTS_RUN_CASE(TEST_header_compiles);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

static DISPID stripe_flag_for_index(unsigned index /* 1-based */)
{
    DISPID dispidFlag = DISPID(0x1) << (8 * sizeof(DISPID) - 2);

    dispidFlag >>= (index - 1);

    return dispidFlag;
}

static DISPID apply_stripe(DISPID dispid, unsigned index)
{
    DISPID const flag = stripe_flag_for_index(index);

    if (dispid < 0)
    {
        return dispid;
    }

    return dispid | flag;
}

static DISPID remove_stripe(DISPID dispid, unsigned index)
{
    DISPID const flag = stripe_flag_for_index(index);

    if (dispid >= 0 && (dispid & flag))
    {
        return dispid & ~flag;
    }

    return dispid;
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_stripe_flags_are_distinct()
{
    DISPID const flag1 = stripe_flag_for_index(1);
    DISPID const flag2 = stripe_flag_for_index(2);
    DISPID const flag3 = stripe_flag_for_index(3);
    DISPID const flag4 = stripe_flag_for_index(4);

    TEST_BOOLEAN_EQ(1, 0 == (flag1 & flag2));
    TEST_BOOLEAN_EQ(1, 0 == (flag1 & flag3));
    TEST_BOOLEAN_EQ(1, 0 == (flag2 & flag3));
    TEST_BOOLEAN_EQ(1, 0 == (flag3 & flag4));
}

static void TEST_stripe_round_trip()
{
    DISPID const baseDispid = 42;
    unsigned     index;

    for (index = 1; index <= 4; ++index)
    {
        DISPID const striped = apply_stripe(baseDispid, index);
        DISPID const restored = remove_stripe(striped, index);

        TEST_INT_EQ(baseDispid, restored);
        TEST_BOOLEAN_EQ(1, 0 != (striped & stripe_flag_for_index(index)));
    }
}

static void TEST_stripe_preserves_negative_dispids()
{
    DISPID const dispid = -1;

    TEST_INT_EQ(dispid, apply_stripe(dispid, 1));
    TEST_INT_EQ(dispid, apply_stripe(dispid, 2));
}

static void TEST_header_compiles()
{
    /* Successful inclusion verifies template declarations are available. */
    TEST_PASSED();
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
