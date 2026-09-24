/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.bit_functions/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::bit_functions`.
 *
 * Created: 19th March 2010
 * Updated: 24th September 2026
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

/* Standard C++ header files */

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_count_bits_Kernighan_method_FOR_32();
    static void TEST_count_bits_Kernighan_method_FOR_64();
    static void TEST_count_bits_8bit_table_FOR_32();
    static void TEST_count_bits_8bit_table_FOR_64();
    static void TEST_count_bits_FOR_32();
    static void TEST_count_bits_FOR_64();
    static void TEST_count_bits_FOR_int();
    static void TEST_find_high_bit_FOR_8();
    static void TEST_find_high_bit_FOR_16();
    static void TEST_find_high_bit_FOR_32();
    static void TEST_find_high_bit_FOR_64();
    static void TEST_calculate_xor_over_range_FOR_8_BIT();
    static void TEST_calculate_xor_over_range_FOR_16_BIT();
    static void TEST_calculate_xor_over_range_FOR_32_BIT();
    static void TEST_calculate_xor_over_range_FOR_64_BIT();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.bit_functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_count_bits_Kernighan_method_FOR_32);
        XTESTS_RUN_CASE(TEST_count_bits_Kernighan_method_FOR_64);
        XTESTS_RUN_CASE(TEST_count_bits_8bit_table_FOR_32);
        XTESTS_RUN_CASE(TEST_count_bits_8bit_table_FOR_64);
        XTESTS_RUN_CASE(TEST_count_bits_FOR_32);
        XTESTS_RUN_CASE(TEST_count_bits_FOR_64);
        XTESTS_RUN_CASE(TEST_count_bits_FOR_int);
        XTESTS_RUN_CASE(TEST_find_high_bit_FOR_8);
        XTESTS_RUN_CASE(TEST_find_high_bit_FOR_16);
        XTESTS_RUN_CASE(TEST_find_high_bit_FOR_32);
        XTESTS_RUN_CASE(TEST_find_high_bit_FOR_64);
        XTESTS_RUN_CASE(TEST_calculate_xor_over_range_FOR_8_BIT);
        XTESTS_RUN_CASE(TEST_calculate_xor_over_range_FOR_16_BIT);
        XTESTS_RUN_CASE(TEST_calculate_xor_over_range_FOR_32_BIT);
        XTESTS_RUN_CASE(TEST_calculate_xor_over_range_FOR_64_BIT);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::uint8_t;
    using stlsoft::uint16_t;
    using stlsoft::uint32_t;
    using stlsoft::uint64_t;


static void TEST_count_bits_Kernighan_method_FOR_32()
{
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

    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00001001)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00001010)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00001100)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x01001000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00011000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x00101000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint32_t(0x10001000)));
}

static void TEST_count_bits_Kernighan_method_FOR_64()
{
    TEST_INT_EQ(0u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(0)));
    TEST_INT_EQ(0u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000000))));

    TEST_INT_EQ(64u, stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0xffffffffffffffff))));

    TEST_INT_EQ(32u, stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x3333333333333333))));
    TEST_INT_EQ(32u, stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x5555555555555555))));
    TEST_INT_EQ(32u, stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0xaaaaaaaaaaaaaaaa))));

    TEST_INT_EQ(8u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x00000000000000ff))));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x00000000ff000000))));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x000000ff00000000))));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0xff00000000000000))));

    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000001))));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x0000000100000000))));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x8000000000000000))));

    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x0000000100000001))));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_Kernighan_method(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x8000000000000001))));
}

static void TEST_count_bits_8bit_table_FOR_32()
{
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

    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00001001)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00001010)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00001100)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x01001000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00011000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x00101000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint32_t(0x10001000)));
}

static void TEST_count_bits_8bit_table_FOR_64()
{
    TEST_INT_EQ(0u,  stlsoft::count_bits_by_8bit_table(uint64_t(0)));
    TEST_INT_EQ(0u,  stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000000))));

    TEST_INT_EQ(64u, stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0xffffffffffffffff))));

    TEST_INT_EQ(32u, stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x3333333333333333))));
    TEST_INT_EQ(32u, stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x5555555555555555))));
    TEST_INT_EQ(32u, stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0xaaaaaaaaaaaaaaaa))));

    TEST_INT_EQ(8u,  stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x00000000000000ff))));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x00000000ff000000))));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x000000ff00000000))));
    TEST_INT_EQ(8u,  stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0xff00000000000000))));

    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000001))));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x0000000100000000))));
    TEST_INT_EQ(1u,  stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x8000000000000000))));

    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x0000000100000001))));
    TEST_INT_EQ(2u,  stlsoft::count_bits_by_8bit_table(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x8000000000000001))));
}

static void TEST_count_bits_FOR_32()
{
    TEST_INT_EQ(0u,  stlsoft::count_bits(uint32_t(0)));
    TEST_INT_EQ(32u, stlsoft::count_bits(uint32_t(0xffffffff)));
    TEST_INT_EQ(16u, stlsoft::count_bits(uint32_t(0x55555555)));
    TEST_INT_EQ(1u,  stlsoft::count_bits(uint32_t(0x80000000)));
    TEST_INT_EQ(2u,  stlsoft::count_bits(uint32_t(0x80000001)));
}

static void TEST_count_bits_FOR_64()
{
    TEST_INT_EQ(0u,  stlsoft::count_bits(uint64_t(0)));
    TEST_INT_EQ(64u, stlsoft::count_bits(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0xffffffffffffffff))));
    TEST_INT_EQ(32u, stlsoft::count_bits(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x5555555555555555))));
    TEST_INT_EQ(1u,  stlsoft::count_bits(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x8000000000000000))));
    TEST_INT_EQ(2u,  stlsoft::count_bits(uint64_t(STLSOFT_GEN_UINT64_SUFFIX(0x8000000000000001))));
}

static void TEST_count_bits_FOR_int()
{
    TEST_INT_EQ(0u, stlsoft::count_bits(0));
    TEST_INT_EQ(1u, stlsoft::count_bits(1));
    TEST_INT_EQ(1u, stlsoft::count_bits(2));
    TEST_INT_EQ(2u, stlsoft::count_bits(3));

    /* Negative values are counted via their two's-complement bit pattern. */
    TEST_INT_EQ(sizeof(int) * 8u, stlsoft::count_bits(-1));
    TEST_INT_EQ(1u, stlsoft::count_bits(static_cast<int>(1u << (sizeof(int) * 8u - 1u))));
}

static void TEST_find_high_bit_FOR_8()
{
    TEST_INT_EQ(0u, stlsoft::find_highest_bit(uint8_t(0)));

    TEST_INT_EQ(1u, stlsoft::find_highest_bit(uint8_t(1)));

    TEST_INT_EQ(2u, stlsoft::find_highest_bit(uint8_t(2)));
    TEST_INT_EQ(2u, stlsoft::find_highest_bit(uint8_t(3)));

    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint8_t(4)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint8_t(5)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint8_t(6)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint8_t(7)));

    TEST_INT_EQ(5u, stlsoft::find_highest_bit(uint8_t(0x10)));
    TEST_INT_EQ(5u, stlsoft::find_highest_bit(uint8_t(0x1f)));

    TEST_INT_EQ(8u, stlsoft::find_highest_bit(uint8_t(0x80)));
    TEST_INT_EQ(8u, stlsoft::find_highest_bit(uint8_t(0xff)));
}

static void TEST_find_high_bit_FOR_16()
{
    TEST_INT_EQ(0u, stlsoft::find_highest_bit(uint16_t(0)));

    TEST_INT_EQ(1u, stlsoft::find_highest_bit(uint16_t(1)));

    TEST_INT_EQ(2u, stlsoft::find_highest_bit(uint16_t(2)));
    TEST_INT_EQ(2u, stlsoft::find_highest_bit(uint16_t(3)));

    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint16_t(4)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint16_t(5)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint16_t(6)));
    TEST_INT_EQ(3u, stlsoft::find_highest_bit(uint16_t(7)));

    TEST_INT_EQ(9u, stlsoft::find_highest_bit(uint16_t(0x0100)));
    TEST_INT_EQ(9u, stlsoft::find_highest_bit(uint16_t(0x01ff)));

    TEST_INT_EQ(16u, stlsoft::find_highest_bit(uint16_t(0x8000)));
    TEST_INT_EQ(16u, stlsoft::find_highest_bit(uint16_t(0xffff)));
}

static void TEST_find_high_bit_FOR_32()
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

static void TEST_find_high_bit_FOR_64()
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

static void TEST_calculate_xor_over_range_FOR_8_BIT()
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

static void TEST_calculate_xor_over_range_FOR_16_BIT()
{
    uint16_t const elements[] =
    {
            0x0000

        ,   0x0001
        ,   0x0002
        ,   0x0004
        ,   0x0008

        ,   0x0001
        ,   0x0002
        ,   0x0004
        ,   0x0008

        ,   0x0040
        ,   0x0080
        ,   0x0010
        ,   0x0020

        ,   0x0100
        ,   0x8000
    };

    TEST_INT_EQ(0x0000, stlsoft::calculate_xor_over_range(elements,  0u));
    TEST_INT_EQ(0x0000, stlsoft::calculate_xor_over_range(elements,  1u));
    TEST_INT_EQ(0x0001, stlsoft::calculate_xor_over_range(elements,  2u));
    TEST_INT_EQ(0x0003, stlsoft::calculate_xor_over_range(elements,  3u));
    TEST_INT_EQ(0x0007, stlsoft::calculate_xor_over_range(elements,  4u));
    TEST_INT_EQ(0x000f, stlsoft::calculate_xor_over_range(elements,  5u));
    TEST_INT_EQ(0x000e, stlsoft::calculate_xor_over_range(elements,  6u));
    TEST_INT_EQ(0x000c, stlsoft::calculate_xor_over_range(elements,  7u));
    TEST_INT_EQ(0x0008, stlsoft::calculate_xor_over_range(elements,  8u));
    TEST_INT_EQ(0x0000, stlsoft::calculate_xor_over_range(elements,  9u));
    TEST_INT_EQ(0x0040, stlsoft::calculate_xor_over_range(elements, 10u));
    TEST_INT_EQ(0x00c0, stlsoft::calculate_xor_over_range(elements, 11u));
    TEST_INT_EQ(0x00d0, stlsoft::calculate_xor_over_range(elements, 12u));
    TEST_INT_EQ(0x00f0, stlsoft::calculate_xor_over_range(elements, 13u));
    TEST_INT_EQ(0x01f0, stlsoft::calculate_xor_over_range(elements, 14u));
    TEST_INT_EQ(0x81f0, stlsoft::calculate_xor_over_range(elements, 15u));
}

static void TEST_calculate_xor_over_range_FOR_32_BIT()
{
    uint32_t const elements[] =
    {
            0x00000000u

        ,   0x00000001u
        ,   0x00000002u
        ,   0x00000004u
        ,   0x00000008u

        ,   0x00000001u
        ,   0x00000002u
        ,   0x00000004u
        ,   0x00000008u

        ,   0x00000040u
        ,   0x00000080u
        ,   0x00000010u
        ,   0x00000020u

        ,   0x00000100u
        ,   0x80000000u
    };

    TEST_INT_EQ(0x00000000u, stlsoft::calculate_xor_over_range(elements,  0u));
    TEST_INT_EQ(0x00000000u, stlsoft::calculate_xor_over_range(elements,  1u));
    TEST_INT_EQ(0x00000001u, stlsoft::calculate_xor_over_range(elements,  2u));
    TEST_INT_EQ(0x00000003u, stlsoft::calculate_xor_over_range(elements,  3u));
    TEST_INT_EQ(0x00000007u, stlsoft::calculate_xor_over_range(elements,  4u));
    TEST_INT_EQ(0x0000000fu, stlsoft::calculate_xor_over_range(elements,  5u));
    TEST_INT_EQ(0x0000000eu, stlsoft::calculate_xor_over_range(elements,  6u));
    TEST_INT_EQ(0x0000000cu, stlsoft::calculate_xor_over_range(elements,  7u));
    TEST_INT_EQ(0x00000008u, stlsoft::calculate_xor_over_range(elements,  8u));
    TEST_INT_EQ(0x00000000u, stlsoft::calculate_xor_over_range(elements,  9u));
    TEST_INT_EQ(0x00000040u, stlsoft::calculate_xor_over_range(elements, 10u));
    TEST_INT_EQ(0x000000c0u, stlsoft::calculate_xor_over_range(elements, 11u));
    TEST_INT_EQ(0x000000d0u, stlsoft::calculate_xor_over_range(elements, 12u));
    TEST_INT_EQ(0x000000f0u, stlsoft::calculate_xor_over_range(elements, 13u));
    TEST_INT_EQ(0x000001f0u, stlsoft::calculate_xor_over_range(elements, 14u));
    TEST_INT_EQ(0x800001f0u, stlsoft::calculate_xor_over_range(elements, 15u));
}

static void TEST_calculate_xor_over_range_FOR_64_BIT()
{
    uint64_t const elements[] =
    {
            STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000000)

        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000001)
        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000002)
        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000004)
        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000008)

        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000001)
        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000002)
        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000004)
        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000008)

        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000040)
        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000080)
        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000010)
        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000020)

        ,   STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000100)
        ,   STLSOFT_GEN_UINT64_SUFFIX(0x8000000000000000)
    };

    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000000), stlsoft::calculate_xor_over_range(elements,  0u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000000), stlsoft::calculate_xor_over_range(elements,  1u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000001), stlsoft::calculate_xor_over_range(elements,  2u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000003), stlsoft::calculate_xor_over_range(elements,  3u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000007), stlsoft::calculate_xor_over_range(elements,  4u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x000000000000000f), stlsoft::calculate_xor_over_range(elements,  5u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x000000000000000e), stlsoft::calculate_xor_over_range(elements,  6u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x000000000000000c), stlsoft::calculate_xor_over_range(elements,  7u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000008), stlsoft::calculate_xor_over_range(elements,  8u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000000), stlsoft::calculate_xor_over_range(elements,  9u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x0000000000000040), stlsoft::calculate_xor_over_range(elements, 10u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x00000000000000c0), stlsoft::calculate_xor_over_range(elements, 11u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x00000000000000d0), stlsoft::calculate_xor_over_range(elements, 12u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x00000000000000f0), stlsoft::calculate_xor_over_range(elements, 13u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x00000000000001f0), stlsoft::calculate_xor_over_range(elements, 14u));
    TEST_INT_EQ(STLSOFT_GEN_UINT64_SUFFIX(0x80000000000001f0), stlsoft::calculate_xor_over_range(elements, 15u));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

