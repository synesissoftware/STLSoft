/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/rangelib/invalid_integral_range_policy/entry.cpp
 *
 * Purpose: Unit-tests for `rangelib::invalid_integral_range_policy`.
 *
 * Created: 29th October 2026
 * Updated: 14th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <rangelib/integral_range.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <stdexcept>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_POLICY_SINT32();
    static void TEST_POLICY_UINT32();
#ifdef STLSOFT_CF_64BIT_INT_SUPPORT
    static void TEST_POLICY_SINT64();
    static void TEST_POLICY_UINT64();
#endif /* STLSOFT_CF_64BIT_INT_SUPPORT */
#ifdef STLSOFT_CF_INT_DISTINCT_INT_TYPE
    static void TEST_POLICY_int();
    static void TEST_POLICY_UNSIGNED();
#endif /* STLSOFT_CF_INT_DISTINCT_INT_TYPE */
    static void TEST_RANGE_REJECTS_NON_CLOSING();
    static void TEST_RANGE_ACCEPTS_CLOSING();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.rangelib.invalid_integral_range_policy", verbosity))
    {
        XTESTS_RUN_CASE(TEST_POLICY_SINT32);
        XTESTS_RUN_CASE(TEST_POLICY_UINT32);
#ifdef STLSOFT_CF_64BIT_INT_SUPPORT
        XTESTS_RUN_CASE(TEST_POLICY_SINT64);
        XTESTS_RUN_CASE(TEST_POLICY_UINT64);
#endif /* STLSOFT_CF_64BIT_INT_SUPPORT */
#ifdef STLSOFT_CF_INT_DISTINCT_INT_TYPE
        XTESTS_RUN_CASE(TEST_POLICY_int);
        XTESTS_RUN_CASE(TEST_POLICY_UNSIGNED);
#endif /* STLSOFT_CF_INT_DISTINCT_INT_TYPE */
        XTESTS_RUN_CASE(TEST_RANGE_REJECTS_NON_CLOSING);
        XTESTS_RUN_CASE(TEST_RANGE_ACCEPTS_CLOSING);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

#define EXPECT_MESSAGE_(invoke, expected) \
\
    do \
    { \
        int caught_ = 0; \
\
        try \
        { \
            invoke; \
        } \
        catch (std::out_of_range& x) \
        { \
            caught_ = 1; \
\
            TEST_MS_EQ((expected), x.what()); \
        } \
\
        TEST_INT_EQ(1, caught_); \
    } while (0)

static void TEST_POLICY_SINT32()
{
    rangelib::invalid_integral_range_policy policy;

    EXPECT_MESSAGE_(
        (policy(stlsoft::ss_sint32_t(-100), stlsoft::ss_sint32_t(200), stlsoft::ss_sint32_t(5)))
    ,   "Invalid integral range [-100, 200), 5"
    );

    EXPECT_MESSAGE_(
        (policy(
            stlsoft::ss_sint32_t(-2147483647) - 1
        ,   stlsoft::ss_sint32_t(2147483647)
        ,   stlsoft::ss_sint32_t(-2147483647) - 1
        ))
    ,   "Invalid integral range [-2147483648, 2147483647), -2147483648"
    );
}

static void TEST_POLICY_UINT32()
{
    rangelib::invalid_integral_range_policy policy;

    EXPECT_MESSAGE_(
        (policy(stlsoft::ss_uint32_t(1), stlsoft::ss_uint32_t(2), stlsoft::ss_uint32_t(3)))
    ,   "Invalid integral range [1, 2), 3"
    );

    EXPECT_MESSAGE_(
        (policy(
            stlsoft::ss_uint32_t(0)
        ,   stlsoft::ss_uint32_t(4294967295u)
        ,   stlsoft::ss_uint32_t(4294967295u)
        ))
    ,   "Invalid integral range [0, 4294967295), 4294967295"
    );
}
#ifdef STLSOFT_CF_64BIT_INT_SUPPORT

static void TEST_POLICY_SINT64()
{
    stlsoft::ss_sint64_t const  minimum =   STLSOFT_GEN_SINT64_SUFFIX(-9223372036854775807) - 1;
    stlsoft::ss_sint64_t const  maximum =   STLSOFT_GEN_SINT64_SUFFIX(9223372036854775807);
    rangelib::invalid_integral_range_policy policy;

    EXPECT_MESSAGE_(
        (policy(stlsoft::ss_sint64_t(0), stlsoft::ss_sint64_t(10), stlsoft::ss_sint64_t(3)))
    ,   "Invalid integral range [0, 10), 3"
    );

    EXPECT_MESSAGE_(
        (policy(minimum, maximum, minimum))
    ,   "Invalid integral range [-9223372036854775808, 9223372036854775807), -9223372036854775808"
    );
}

static void TEST_POLICY_UINT64()
{
    stlsoft::ss_uint64_t const  maximum =   STLSOFT_GEN_UINT64_SUFFIX(18446744073709551615);
    rangelib::invalid_integral_range_policy policy;

    EXPECT_MESSAGE_(
        (policy(stlsoft::ss_uint64_t(0), stlsoft::ss_uint64_t(10), stlsoft::ss_uint64_t(3)))
    ,   "Invalid integral range [0, 10), 3"
    );

    EXPECT_MESSAGE_(
        (policy(stlsoft::ss_uint64_t(0), maximum, maximum))
    ,   "Invalid integral range [0, 18446744073709551615), 18446744073709551615"
    );
}
#endif /* STLSOFT_CF_64BIT_INT_SUPPORT */
#ifdef STLSOFT_CF_INT_DISTINCT_INT_TYPE

static void TEST_POLICY_int()
{
    rangelib::invalid_integral_range_policy policy;

    EXPECT_MESSAGE_(
        (policy(int(-100), int(200), int(5)))
    ,   "Invalid integral range [-100, 200), 5"
    );
}

static void TEST_POLICY_UNSIGNED()
{
    rangelib::invalid_integral_range_policy policy;

    EXPECT_MESSAGE_(
        (policy(unsigned(1), unsigned(2), unsigned(3)))
    ,   "Invalid integral range [1, 2), 3"
    );
}
#endif /* STLSOFT_CF_INT_DISTINCT_INT_TYPE */

static void TEST_RANGE_REJECTS_NON_CLOSING()
{
    int caught = 0;

    try
    {
        rangelib::integral_range<stlsoft::ss_sint32_t> r(0, 10, 3);

        STLSOFT_SUPPRESS_UNUSED(r);
    }
    catch (std::out_of_range& x)
    {
        caught = 1;

        TEST_MS_EQ("Invalid integral range [0, 10), 3", x.what());
    }

    TEST_INT_EQ(1, caught);
}

static void TEST_RANGE_ACCEPTS_CLOSING()
{
    rangelib::integral_range<stlsoft::ss_sint32_t> r(-100, 100, 5);

    TEST_INT_EQ(-100, r.current());
}
#undef EXPECT_MESSAGE_
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */


