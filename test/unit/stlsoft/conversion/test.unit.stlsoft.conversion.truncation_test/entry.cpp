/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.truncation_test/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::truncation_test<>`.
 *
 * Created: 7th November 2008
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/conversion/truncation_test.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_12();
    static void test_zero();
    static void test_sign();
    static void test_range_signed();
    static void test_range_unsigned();
    static void test_edge_to_sint8();
    static void test_to_sint8();
    static void test_to_uint8();
    static void test_to_sint16();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.truncation_test", verbosity))
    {
        XTESTS_RUN_CASE(test_12);
        XTESTS_RUN_CASE(test_zero);
        XTESTS_RUN_CASE(test_sign);
        XTESTS_RUN_CASE(test_range_signed);
        XTESTS_RUN_CASE(test_range_unsigned);
        XTESTS_RUN_CASE(test_edge_to_sint8);
        XTESTS_RUN_CASE(test_to_sint8);
        XTESTS_RUN_CASE(test_to_uint8);
        XTESTS_RUN_CASE(test_to_sint16);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::sint8_t;
    using stlsoft::uint8_t;
    using stlsoft::sint16_t;
    using stlsoft::uint16_t;
    using stlsoft::sint32_t;
    using stlsoft::uint32_t;
    using stlsoft::sint64_t;
    using stlsoft::uint64_t;

static void test_12()
{
    // 1a
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint8_t(stlsoft::integral_limits<sint8_t>::minimum())));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint8_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint8_t(stlsoft::integral_limits<sint8_t>::maximum())));

    // 1b
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint16_t(stlsoft::integral_limits<sint16_t>::minimum())));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint16_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint16_t(stlsoft::integral_limits<sint16_t>::maximum())));

    // 1c
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint16_t>(sint64_t(stlsoft::integral_limits<sint64_t>::minimum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint32_t>::minimum())));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::minimum())));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint32_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint32_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint16_t>(sint64_t(stlsoft::integral_limits<sint64_t>::maximum())));


    // 2a
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(uint8_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(uint8_t(stlsoft::integral_limits<uint8_t>::maximum())));

    // 2b
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(uint16_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(uint16_t(stlsoft::integral_limits<sint16_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint16_t>(uint16_t(stlsoft::integral_limits<uint16_t>::maximum())));

    // 2c
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(uint32_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(uint32_t(stlsoft::integral_limits<sint16_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint16_t>(uint32_t(stlsoft::integral_limits<uint16_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint16_t>(uint32_t(stlsoft::integral_limits<uint32_t>::maximum())));


    // 3a
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(sint8_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(sint8_t(stlsoft::integral_limits<sint8_t>::maximum())));

    // 3b
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(sint16_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(sint16_t(stlsoft::integral_limits<sint16_t>::maximum())));

    // 3c
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(sint32_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::maximum())));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(sint32_t(stlsoft::integral_limits<uint16_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<uint16_t>(sint32_t(stlsoft::integral_limits<sint32_t>::maximum())));


    // 4a
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(uint8_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(uint8_t(stlsoft::integral_limits<uint8_t>::maximum())));

    // 4b
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(uint16_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(uint16_t(stlsoft::integral_limits<uint16_t>::maximum())));

    // 4c
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(uint32_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(uint32_t(stlsoft::integral_limits<uint16_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<uint16_t>(uint32_t(stlsoft::integral_limits<uint32_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<uint16_t>(uint64_t(stlsoft::integral_limits<uint64_t>::maximum())));

}

static void test_zero()
{
    // int
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(0));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint8_t>(0));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(0));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(0));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(0));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(0));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(0));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(0));

    // uint64_t
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(uint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint8_t>(uint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(uint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(uint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(uint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(uint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(uint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(uint64_t(0)));

    // sint64_t
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(sint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint8_t>(sint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(sint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(sint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(sint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(sint64_t(0)));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(sint64_t(0)));
}

static void test_sign()
{
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(-10));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<uint8_t>(-10));

    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(-10));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<uint16_t>(-10));

    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(-10));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<uint32_t>(-10));

    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(-10));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<uint32_t>(-10));
}

static void test_range_signed()
{
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(-1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(-10));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(-100));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(stlsoft::integral_limits<sint8_t>::minimum() + 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(stlsoft::integral_limits<sint8_t>::minimum()));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(sint16_t(stlsoft::integral_limits<sint8_t>::minimum()) + 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(sint16_t(stlsoft::integral_limits<sint8_t>::minimum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint8_t>(sint16_t(stlsoft::integral_limits<sint8_t>::minimum()) - 1));

    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(-1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(-10));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(-100));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(-1000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(-10000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(stlsoft::integral_limits<sint16_t>::minimum() + 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(stlsoft::integral_limits<sint16_t>::minimum()));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::minimum()) + 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::minimum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::minimum()) - 1));

    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(-1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(-10));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(-100));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(-1000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(-10000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(-100000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(-1000000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(-10000000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(stlsoft::integral_limits<sint32_t>::minimum() + 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(stlsoft::integral_limits<sint32_t>::minimum()));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(sint64_t(stlsoft::integral_limits<sint32_t>::minimum()) + 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(sint64_t(stlsoft::integral_limits<sint32_t>::minimum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint32_t>(sint64_t(stlsoft::integral_limits<sint32_t>::minimum()) - 1));
}

static void test_range_unsigned()
{
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint8_t>(1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint8_t>(10));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint8_t>(100));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint8_t>(stlsoft::integral_limits<uint8_t>::maximum()));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint8_t>(uint16_t(stlsoft::integral_limits<uint8_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<uint8_t>(uint16_t(stlsoft::integral_limits<uint8_t>::maximum()) + 1));

    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(10));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(100));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(1000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(10000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(stlsoft::integral_limits<uint16_t>::maximum()));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint16_t>(uint32_t(stlsoft::integral_limits<uint16_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<uint16_t>(uint32_t(stlsoft::integral_limits<uint16_t>::maximum()) + 1));

    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(10));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(100));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(1000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(10000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(100000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(1000000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(10000000));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(stlsoft::integral_limits<uint32_t>::maximum()));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<uint32_t>(uint64_t(stlsoft::integral_limits<uint32_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<uint32_t>(uint64_t(stlsoft::integral_limits<uint32_t>::maximum()) + 1));
}

static void test_edge_to_sint8()
{
    // sint8_t
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(stlsoft::integral_limits<sint8_t>::minimum()));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(stlsoft::integral_limits<sint8_t>::minimum() + 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(stlsoft::integral_limits<sint8_t>::maximum() - 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(stlsoft::integral_limits<sint8_t>::maximum()));

    // sint16_t
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint8_t>(sint16_t(stlsoft::integral_limits<sint8_t>::minimum()) - 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(sint16_t(stlsoft::integral_limits<sint8_t>::minimum())));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(sint16_t(stlsoft::integral_limits<sint8_t>::minimum()) + 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(sint16_t(stlsoft::integral_limits<sint8_t>::maximum()) - 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint8_t>(sint16_t(stlsoft::integral_limits<sint8_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint8_t>(sint16_t(stlsoft::integral_limits<sint8_t>::maximum()) + 1));

    // sint32_t
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::minimum()) - 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::minimum())));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::minimum()) + 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::maximum()) - 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint16_t>(sint32_t(stlsoft::integral_limits<sint16_t>::maximum()) + 1));

    // sint64_t
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint32_t>(sint64_t(stlsoft::integral_limits<sint32_t>::minimum()) - 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(sint64_t(stlsoft::integral_limits<sint32_t>::minimum())));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(sint64_t(stlsoft::integral_limits<sint32_t>::minimum()) + 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(sint64_t(stlsoft::integral_limits<sint32_t>::maximum()) - 1));
    TEST_BOOLEAN_TRUE(stlsoft::truncation_test<sint32_t>(sint64_t(stlsoft::integral_limits<sint32_t>::maximum())));
    TEST_BOOLEAN_FALSE(stlsoft::truncation_test<sint32_t>(sint64_t(stlsoft::integral_limits<sint32_t>::maximum()) + 1));

    // uint8_t
    ;
}

static void test_to_sint8()
{
    // All in range
    { for (sint8_t from = stlsoft::integral_limits<sint8_t>::minimum(); ; ++from)
    {
        TEST_BOOLEAN_EQ(true, stlsoft::truncation_test<sint8_t>(from));

        if (stlsoft::integral_limits<sint8_t>::maximum() == from)
        {
            break;
        }
    }}

    // < lower bound
    { for (sint16_t from = stlsoft::integral_limits<sint16_t>::minimum(); from != stlsoft::integral_limits<sint8_t>::minimum(); ++from)
    {
        TEST_BOOLEAN_EQ(false, stlsoft::truncation_test<sint8_t>(from));
    }}

    // > upper bound
    { for (sint16_t from = sint16_t(1 + stlsoft::integral_limits<sint8_t>::maximum()); from != stlsoft::integral_limits<sint16_t>::maximum(); ++from)
    {
        TEST_BOOLEAN_EQ(false, stlsoft::truncation_test<sint8_t>(from));
    }}
}

static void test_to_uint8()
{
    // All in range
    { for (uint8_t from = stlsoft::integral_limits<uint8_t>::minimum(); ; ++from)
    {
        TEST_BOOLEAN_EQ(true, stlsoft::truncation_test<uint8_t>(from));

        if (stlsoft::integral_limits<uint8_t>::maximum() == from)
        {
            break;
        }
    }}

    // < lower bound
    { for (sint16_t from = stlsoft::integral_limits<sint16_t>::minimum(); from != stlsoft::integral_limits<uint8_t>::minimum(); ++from)
    {
        TEST_BOOLEAN_EQ(false, stlsoft::truncation_test<uint8_t>(from));
    }}

    // > upper bound
    { for (sint16_t from = sint16_t(1 + stlsoft::integral_limits<uint8_t>::maximum()); from != stlsoft::integral_limits<sint16_t>::maximum(); ++from)
    {
        TEST_BOOLEAN_EQ(false, stlsoft::truncation_test<uint8_t>(from));
    }}
}

static void test_to_sint16()
{
    // All in range
    { for (sint16_t from = stlsoft::integral_limits<sint16_t>::minimum(); ; ++from)
    {
        TEST_BOOLEAN_EQ(true, stlsoft::truncation_test<sint16_t>(from));

        if (stlsoft::integral_limits<sint16_t>::maximum() == from)
        {
            break;
        }
    }}

    // < lower bound
    { for (sint32_t from = stlsoft::integral_limits<sint32_t>::minimum(); from < stlsoft::integral_limits<sint16_t>::minimum(); from /= 10)
    {
        TEST_BOOLEAN_EQ(false, stlsoft::truncation_test<sint16_t>(from));
    }}

    // > upper bound
    { for (sint32_t from = 1 + sint32_t(stlsoft::integral_limits<sint16_t>::maximum()); from > stlsoft::integral_limits<sint32_t>::maximum(); from *= 10)
    {
        TEST_BOOLEAN_EQ(false, stlsoft::truncation_test<sint16_t>(from));
    }}
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

