/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.bit_functions/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::bit_functions`.
 *
 * Created: 19th March 2010
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/util/bit_functions.h>

/* /////////////////////////////////////
 * general includes
 */


/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <platformstl/diagnostics/stopwatch.hpp>

/* Standard C++ header files */

/* Standard C header files */
#include <assert.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_count_bits_Kernighan();
    static void test_count_bits_8bit_table();
    static void test_find_high_bit_32();
    static void test_find_high_bit_64();
    static void test_calculate_xor_over_range_8_bit();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.bit_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_count_bits_Kernighan);
        XTESTS_RUN_CASE(test_count_bits_8bit_table);
        XTESTS_RUN_CASE(test_find_high_bit_32);
        XTESTS_RUN_CASE(test_find_high_bit_64);
        XTESTS_RUN_CASE(test_calculate_xor_over_range_8_bit);

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

    using platformstl::stopwatch;

static void test_count_bits_Kernighan()
{
    stopwatch sw;

    sw.start();

    TEST_INT_EQ(0u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0)));
    TEST_INT_EQ(0u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00000000)));

    TEST_INT_EQ(32u, stlsoft::count_bits_by_Kernighan_method(uint32_t(0xffffffff)));

    TEST_INT_EQ(16u, stlsoft::count_bits_by_Kernighan_method(uint32_t(0x33333333)));
    TEST_INT_EQ(16u, stlsoft::count_bits_by_Kernighan_method(uint32_t(0x55555555)));
    TEST_INT_EQ(16u, stlsoft::count_bits_by_Kernighan_method(uint32_t(0x66666666)));
    TEST_INT_EQ(16u, stlsoft::count_bits_by_Kernighan_method(uint32_t(0x99999999)));
    TEST_INT_EQ(16u, stlsoft::count_bits_by_Kernighan_method(uint32_t(0xaaaaaaaa)));
    TEST_INT_EQ(16u, stlsoft::count_bits_by_Kernighan_method(uint32_t(0xcccccccc)));

    TEST_INT_EQ(8u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x000000ff)));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x0000ff00)));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00ff0000)));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0xff000000)));

    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00000001)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00000010)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00000100)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00001000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00010000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00100000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x01000000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x10000000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00000002)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00000020)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00000200)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00002000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00020000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00200000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x02000000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x20000000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00000002)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00000020)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00000200)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00002000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00020000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00200000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x02000000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x20000000)));

    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00001001)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00001010)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00001100)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x01001000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00011000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00101000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x01001000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x10001000)));

    sw.stop();

    fprintf(stdout, "t: %luns\n", static_cast<unsigned long>(sw.get_nanoseconds()));
}

static void test_count_bits_8bit_table()
{
    stopwatch sw;

    sw.start();

    TEST_INT_EQ(0u,  stlsoft::count_bits_by_8bit_table(uint32_t(0)));
    TEST_INT_EQ(0u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00000000)));

    TEST_INT_EQ(32u, stlsoft::count_bits_by_8bit_table(uint32_t(0xffffffff)));

    TEST_INT_EQ(16u, stlsoft::count_bits_by_8bit_table(uint32_t(0x33333333)));
    TEST_INT_EQ(16u, stlsoft::count_bits_by_8bit_table(uint32_t(0x55555555)));
    TEST_INT_EQ(16u, stlsoft::count_bits_by_8bit_table(uint32_t(0x66666666)));
    TEST_INT_EQ(16u, stlsoft::count_bits_by_8bit_table(uint32_t(0x99999999)));
    TEST_INT_EQ(16u, stlsoft::count_bits_by_8bit_table(uint32_t(0xaaaaaaaa)));
    TEST_INT_EQ(16u, stlsoft::count_bits_by_8bit_table(uint32_t(0xcccccccc)));

    TEST_INT_EQ(8u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x000000ff)));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x0000ff00)));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00ff0000)));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_8bit_table(uint32_t(0xff000000)));

    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00000001)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00000010)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00000100)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00001000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00010000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00100000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x01000000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x10000000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00000002)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00000020)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00000200)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00002000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00020000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00200000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x02000000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x20000000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00000002)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00000020)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00000200)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00002000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00020000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00200000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x02000000)));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x20000000)));

    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00001001)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00001010)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00001100)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x01001000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00011000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00101000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x01001000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x10001000)));

    sw.stop();

    fprintf(stdout, "t: %luns\n", static_cast<unsigned long>(sw.get_nanoseconds()));
}

static void test_find_high_bit_32()
{
    TEST_INT_EQ(0u, stlsoft::find_highest_bit(uint32_t(0)));

    TEST_INT_EQ(1u, stlsoft::find_highest_bit(uint32_t(1)));

    TEST_INT_EQ(2u, stlsoft::find_highest_bit(uint32_t(2)));
    TEST_INT_EQ(2u, stlsoft::find_highest_bit(uint32_t(3)));

    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint32_t(4)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint32_t(5)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint32_t(6)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint32_t(7)));

    TEST_INT_EQ(25u, stlsoft::find_highest_bit(uint32_t(0x01000000)));
    TEST_INT_EQ(25u, stlsoft::find_highest_bit(uint32_t(0x01f00000)));
    TEST_INT_EQ(25u, stlsoft::find_highest_bit(uint32_t(0x010f0000)));
    TEST_INT_EQ(25u, stlsoft::find_highest_bit(uint32_t(0x0100ffff)));

    TEST_INT_EQ(32u, stlsoft::find_highest_bit(uint32_t(0x80000000)));
}

static void test_find_high_bit_64()
{
    TEST_INT_EQ(0u, stlsoft::find_highest_bit(uint64_t(0)));

    TEST_INT_EQ(1u, stlsoft::find_highest_bit(uint64_t(1)));

    TEST_INT_EQ(2u, stlsoft::find_highest_bit(uint64_t(2)));
    TEST_INT_EQ(2u, stlsoft::find_highest_bit(uint64_t(3)));

    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint64_t(4)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint64_t(5)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint64_t(6)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint64_t(7)));

    TEST_INT_EQ(25u, stlsoft::find_highest_bit(uint64_t(0x01000000)));
    TEST_INT_EQ(25u, stlsoft::find_highest_bit(uint64_t(0x01f00000)));
    TEST_INT_EQ(25u, stlsoft::find_highest_bit(uint64_t(0x010f0000)));
    TEST_INT_EQ(25u, stlsoft::find_highest_bit(uint64_t(0x0100ffff)));

    TEST_INT_EQ(32u, stlsoft::find_highest_bit(uint64_t(0x80000000)));

    TEST_INT_EQ(33u, stlsoft::find_highest_bit(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x100000000))));
    TEST_INT_EQ(33u, stlsoft::find_highest_bit(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x13c3c3c3c))));

    TEST_INT_EQ(41u, stlsoft::find_highest_bit(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x10000000000))));
    TEST_INT_EQ(41u, stlsoft::find_highest_bit(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x13c3c3c3c3c))));

    TEST_INT_EQ(45u, stlsoft::find_highest_bit(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x100000000000))));
    TEST_INT_EQ(45u, stlsoft::find_highest_bit(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x1c3c3c3c3c3c))));
}

static void test_calculate_xor_over_range_8_bit()
{
    uint8_t const elements[] =
    {
            0x00

        ,   0x01
        ,   0x02
        ,   0x04
        ,   0x08

        ,   0x01
        ,   0x02
        ,   0x04
        ,   0x08

        ,   0x40
        ,   0x80
        ,   0x10
        ,   0x20
    };

    TEST_INT_EQ(0x00, stlsoft::calculate_xor_over_range(elements,  0u));

    TEST_INT_EQ(0x00, stlsoft::calculate_xor_over_range(elements,  1u));

    TEST_INT_EQ(0x01, stlsoft::calculate_xor_over_range(elements,  2u));
    TEST_INT_EQ(0x03, stlsoft::calculate_xor_over_range(elements,  3u));
    TEST_INT_EQ(0x07, stlsoft::calculate_xor_over_range(elements,  4u));
    TEST_INT_EQ(0x0f, stlsoft::calculate_xor_over_range(elements,  5u));

    TEST_INT_EQ(0x0e, stlsoft::calculate_xor_over_range(elements,  6u));
    TEST_INT_EQ(0x0c, stlsoft::calculate_xor_over_range(elements,  7u));
    TEST_INT_EQ(0x08, stlsoft::calculate_xor_over_range(elements,  8u));
    TEST_INT_EQ(0x00, stlsoft::calculate_xor_over_range(elements,  9u));

    TEST_INT_EQ(0x40, stlsoft::calculate_xor_over_range(elements, 10u));
    TEST_INT_EQ(0xc0, stlsoft::calculate_xor_over_range(elements, 11u));
    TEST_INT_EQ(0xd0, stlsoft::calculate_xor_over_range(elements, 12u));
    TEST_INT_EQ(0xf0, stlsoft::calculate_xor_over_range(elements, 13u));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
