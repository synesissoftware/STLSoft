/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/conversion/byte_format_functions/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::format_bytes()`.
 *
 * Created: 12th September 2019
 * Updated: 2nd November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */

// #define STLSOFT_DEBUG
// #define STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF   // defined by CMake for test.unit.stlsoft.conversion.byte_format_functions.sprintf


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/conversion/byte_format_functions.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xCover header files */
#ifdef STLSOFT_USE_XCOVER
# include <xcover/xcover.h>
#endif /* STLSOFT_USE_XCOVER */

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

    static void test_format_bytes_1_byte_1_grouping();
    static void test_format_bytes_1_byte_2_grouping();
    static void test_format_bytes_1_byte_4_grouping();
    static void test_format_bytes_1_byte_8_grouping();
    static void test_format_bytes_1_byte_16_grouping();

    static void test_format_bytes_5_byte_1_grouping();
    static void test_format_bytes_5_byte_2_grouping();
    static void test_format_bytes_5_byte_4_grouping();
    static void test_format_bytes_5_byte_8_grouping();
    static void test_format_bytes_5_byte_16_grouping();

    static void test_format_bytes_ZERO_BYTES();
    static void test_format_bytes_ALL_NIBBLES();
    static void test_format_bytes_32_bytes_1_grouping();
    static void test_format_bytes_32_bytes_2_grouping();
    static void test_format_bytes_32_bytes_4_grouping();
    static void test_format_bytes_32_bytes_8_grouping();
    static void test_format_bytes_32_bytes_16_grouping();
    static void test_format_bytes_32_bytes_32_grouping();
    static void test_format_bytes_3_bytes_32_grouping();
    static void test_format_bytes_33_bytes_32_grouping();
    static void test_format_bytes_0_grouping_DEFAULTS_TO_4();
    static void test_format_bytes_NULL_group_separator();
    static void test_format_bytes_EMPTY_group_separator();
    static void test_format_bytes_MULTI_CHAR_separators();
    static void test_format_bytes_lines_PARTIAL_LAST_LINE();
    static void test_format_bytes_lines_EXACT_LINES();
    static void test_format_bytes_lines_ONE_GROUP_PER_LINE();
    static void test_format_bytes_lines_MORE_GROUPS_PER_LINE_THAN_GROUPS();
    static void test_format_bytes_lines_NONPOSITIVE_groupsPerLine();
    static void test_format_bytes_lines_32_BYTE_GROUPS();
    static void test_format_bytes_BUFFER_EXACT_PLUS_NUL();
    static void test_format_bytes_BUFFER_EXACT_NO_NUL();
    static void test_format_bytes_BUFFER_TOO_SMALL_RETURNS_REQUIRED_SIZE();
    static void test_format_bytes_NULL_BUFFER_QUERIES_REQUIRED_SIZE();

#ifndef STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF
    static void test_format_hex_impl_uint8_CASE();
    static void test_format_hex_impl_uint16_CASE_AND_ORDER();
    static void test_format_hex_impl_uint32_CASE_AND_ORDER();
    static void test_format_hex_impl_uint64_CASE_AND_ORDER();
    static void test_format_hex_impl_uint128_CASE_AND_ORDER();
    static void test_format_hex_impl_uint256_CASE_AND_ORDER();
#endif /* !STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF */
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

#ifdef STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF
    char const* const runnerName = "test.unit.stlsoft.conversion.byte_format_functions.sprintf";
#else /* ? STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF */
    char const* const runnerName = "test.unit.stlsoft.conversion.byte_format_functions";
#endif /* STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF */

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(runnerName, verbosity))
    {
#ifdef STLSOFT_USE_XCOVER
        xcover::init();
#endif /* STLSOFT_USE_XCOVER */

        XTESTS_RUN_CASE(test_format_bytes_1_byte_1_grouping);
        XTESTS_RUN_CASE(test_format_bytes_1_byte_2_grouping);
        XTESTS_RUN_CASE(test_format_bytes_1_byte_4_grouping);
        XTESTS_RUN_CASE(test_format_bytes_1_byte_8_grouping);
        XTESTS_RUN_CASE(test_format_bytes_1_byte_16_grouping);

        XTESTS_RUN_CASE(test_format_bytes_5_byte_1_grouping);
        XTESTS_RUN_CASE(test_format_bytes_5_byte_2_grouping);
        XTESTS_RUN_CASE(test_format_bytes_5_byte_4_grouping);
        XTESTS_RUN_CASE(test_format_bytes_5_byte_8_grouping);
        XTESTS_RUN_CASE(test_format_bytes_5_byte_16_grouping);

        XTESTS_RUN_CASE(test_format_bytes_ZERO_BYTES);
        XTESTS_RUN_CASE(test_format_bytes_ALL_NIBBLES);
        XTESTS_RUN_CASE(test_format_bytes_32_bytes_1_grouping);
        XTESTS_RUN_CASE(test_format_bytes_32_bytes_2_grouping);
        XTESTS_RUN_CASE(test_format_bytes_32_bytes_4_grouping);
        XTESTS_RUN_CASE(test_format_bytes_32_bytes_8_grouping);
        XTESTS_RUN_CASE(test_format_bytes_32_bytes_16_grouping);
        XTESTS_RUN_CASE(test_format_bytes_32_bytes_32_grouping);
        XTESTS_RUN_CASE(test_format_bytes_3_bytes_32_grouping);
        XTESTS_RUN_CASE(test_format_bytes_33_bytes_32_grouping);
        XTESTS_RUN_CASE(test_format_bytes_0_grouping_DEFAULTS_TO_4);
        XTESTS_RUN_CASE(test_format_bytes_NULL_group_separator);
        XTESTS_RUN_CASE(test_format_bytes_EMPTY_group_separator);
        XTESTS_RUN_CASE(test_format_bytes_MULTI_CHAR_separators);
        XTESTS_RUN_CASE(test_format_bytes_lines_PARTIAL_LAST_LINE);
        XTESTS_RUN_CASE(test_format_bytes_lines_EXACT_LINES);
        XTESTS_RUN_CASE(test_format_bytes_lines_ONE_GROUP_PER_LINE);
        XTESTS_RUN_CASE(test_format_bytes_lines_MORE_GROUPS_PER_LINE_THAN_GROUPS);
        XTESTS_RUN_CASE(test_format_bytes_lines_NONPOSITIVE_groupsPerLine);
        XTESTS_RUN_CASE(test_format_bytes_lines_32_BYTE_GROUPS);
        XTESTS_RUN_CASE(test_format_bytes_BUFFER_EXACT_PLUS_NUL);
        XTESTS_RUN_CASE(test_format_bytes_BUFFER_EXACT_NO_NUL);
        XTESTS_RUN_CASE(test_format_bytes_BUFFER_TOO_SMALL_RETURNS_REQUIRED_SIZE);
        XTESTS_RUN_CASE(test_format_bytes_NULL_BUFFER_QUERIES_REQUIRED_SIZE);

#ifndef STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF
        XTESTS_RUN_CASE(test_format_hex_impl_uint8_CASE);
        XTESTS_RUN_CASE(test_format_hex_impl_uint16_CASE_AND_ORDER);
        XTESTS_RUN_CASE(test_format_hex_impl_uint32_CASE_AND_ORDER);
        XTESTS_RUN_CASE(test_format_hex_impl_uint64_CASE_AND_ORDER);
        XTESTS_RUN_CASE(test_format_hex_impl_uint128_CASE_AND_ORDER);
        XTESTS_RUN_CASE(test_format_hex_impl_uint256_CASE_AND_ORDER);
#endif /* !STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF */

#ifdef STLSOFT_USE_XCOVER
        XCOVER_REPORT_FILE_COVERAGE("*stlsoft*/byte_format_functions.hpp", NULL);
#endif /* STLSOFT_USE_XCOVER */

        XTESTS_PRINT_RESULTS();

#ifdef STLSOFT_USE_XCOVER
        xcover::uninit();
#endif /* STLSOFT_USE_XCOVER */

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

#define FORMAT_BYTES_EXPECT_(bytes_, grouping_, group_sep_, groups_per_line_, line_sep_, expected_) \
    \
    do \
    { \
        char                sz_[1001]; \
        std::size_t const   n_ = stlsoft::format_bytes( \
                                    &(bytes_)[0], sizeof(bytes_) \
                                ,   &sz_[0], STLSOFT_NUM_ELEMENTS(sz_) \
                                ,   (grouping_) \
                                ,   (group_sep_) \
                                ,   (groups_per_line_) \
                                ,   (line_sep_) \
                                ); \
        \
        TEST_INT_EQ(static_cast<int>(sizeof(expected_) - 1), static_cast<int>(n_)); \
        TEST_MS_EQ_N((expected_), sz_, static_cast<int>(n_)); \
    } while (0)

static void test_format_bytes_1_byte_1_grouping()
{
    char                    sz[1001];
    stlsoft::byte_t const   bytes[] =   { 0x01 };
    std::size_t const       n       =   stlsoft::format_bytes(
                                                &bytes[0], sizeof(bytes)
                                            ,   &sz[0], STLSOFT_NUM_ELEMENTS(sz)
                                            ,   1
                                            ,   "#"
                                            );

    TEST_MS_EQ_N("01", sz, static_cast<int>(n));
}

static void test_format_bytes_1_byte_2_grouping()
{
    char                    sz[1001];
    stlsoft::byte_t const   bytes[] =   { 0x01 };
    std::size_t const       n       =   stlsoft::format_bytes(
                                                &bytes[0], sizeof(bytes)
                                            ,   &sz[0], STLSOFT_NUM_ELEMENTS(sz)
                                            ,   2
                                            ,   "#"
                                            );

    TEST_MS_EQ_N("0001", sz, static_cast<int>(n));
}

static void test_format_bytes_1_byte_4_grouping()
{
    char                    sz[1001];
    stlsoft::byte_t const   bytes[] =   { 0x01 };
    std::size_t const       n       =   stlsoft::format_bytes(
                                                &bytes[0], sizeof(bytes)
                                            ,   &sz[0], STLSOFT_NUM_ELEMENTS(sz)
                                            ,   4
                                            ,   "#"
                                            );

    TEST_MS_EQ_N("00000001", sz, static_cast<int>(n));
}

static void test_format_bytes_1_byte_8_grouping()
{
    char                    sz[1001];
    stlsoft::byte_t const   bytes[] =   { 0x01 };
    std::size_t const       n       =   stlsoft::format_bytes(
                                                &bytes[0], sizeof(bytes)
                                            ,   &sz[0], STLSOFT_NUM_ELEMENTS(sz)
                                            ,   8
                                            ,   "#"
                                            );

    TEST_MS_EQ_N("0000000000000001", sz, static_cast<int>(n));
}

static void test_format_bytes_1_byte_16_grouping()
{
    char                    sz[1001];
    stlsoft::byte_t const   bytes[] =   { 0x01 };
    std::size_t const       n       =   stlsoft::format_bytes(
                                                &bytes[0], sizeof(bytes)
                                            ,   &sz[0], STLSOFT_NUM_ELEMENTS(sz)
                                            ,   16
                                            ,   "#"
                                            );

    TEST_MS_EQ_N("00000000000000000000000000000001", sz, static_cast<int>(n));
}

static void test_format_bytes_5_byte_1_grouping()
{
    char                    sz[1001];
    stlsoft::byte_t const   bytes[] =   { 0x01, 0x02, 0x03, 0x04, 0x05 };
    std::size_t const       n       =   stlsoft::format_bytes(
                                                &bytes[0], sizeof(bytes)
                                            ,   &sz[0], STLSOFT_NUM_ELEMENTS(sz)
                                            ,   1
                                            ,   " "
                                            );

    TEST_MS_EQ_N("01 02 03 04 05", sz, static_cast<int>(n));
}

static void test_format_bytes_5_byte_2_grouping()
{
    char                    sz[1001];
    stlsoft::byte_t const   bytes[] =   { 0x01, 0x02, 0x03, 0x04, 0x05 };
    std::size_t const       n       =   stlsoft::format_bytes(
                                                &bytes[0], sizeof(bytes)
                                            ,   &sz[0], STLSOFT_NUM_ELEMENTS(sz)
                                            ,   2
                                            ,   " "
                                            );

    TEST_MS_EQ_N("0201 0403 0005", sz, static_cast<int>(n));
}

static void test_format_bytes_5_byte_4_grouping()
{
    char                    sz[1001];
    stlsoft::byte_t const   bytes[] =   { 0x01, 0x02, 0x03, 0x04, 0x05 };
    std::size_t const       n       =   stlsoft::format_bytes(
                                                &bytes[0], sizeof(bytes)
                                            ,   &sz[0], STLSOFT_NUM_ELEMENTS(sz)
                                            ,   4
                                            ,   " "
                                            );

    TEST_MS_EQ_N("04030201 00000005", sz, static_cast<int>(n));
}

static void test_format_bytes_5_byte_8_grouping()
{
    char                    sz[1001];
    stlsoft::byte_t const   bytes[] =   { 0x01, 0x02, 0x03, 0x04, 0x05 };
    std::size_t const       n       =   stlsoft::format_bytes(
                                                &bytes[0], sizeof(bytes)
                                            ,   &sz[0], STLSOFT_NUM_ELEMENTS(sz)
                                            ,   8
                                            ,   " "
                                            );

    TEST_MS_EQ_N("0000000504030201", sz, static_cast<int>(n));
}

static void test_format_bytes_5_byte_16_grouping()
{
    char                    sz[1001];
    stlsoft::byte_t const   bytes[] =   { 0x01, 0x02, 0x03, 0x04, 0x05 };
    std::size_t const       n       =   stlsoft::format_bytes(
                                                &bytes[0], sizeof(bytes)
                                            ,   &sz[0], STLSOFT_NUM_ELEMENTS(sz)
                                            ,   16
                                            ,   " "
                                            );

    TEST_MS_EQ_N("00000000000000000000000504030201", sz, static_cast<int>(n));
}

static void test_format_bytes_ZERO_BYTES()
{
    char                    sz[8];
    stlsoft::byte_t const   bytes[] = { 0x01 };

    sz[0] = 'X';

    TEST_INT_EQ(0, static_cast<int>(stlsoft::format_bytes(&bytes[0], 0, &sz[0], STLSOFT_NUM_ELEMENTS(sz), 1, " ")));
    TEST_CHAR_EQ('\0', sz[0]);
    TEST_INT_EQ(0, static_cast<int>(stlsoft::format_bytes(&bytes[0], 0, NULL, 0, 1, " ")));
}

static void test_format_bytes_ALL_NIBBLES()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x80, 0xff };

    FORMAT_BYTES_EXPECT_(bytes, 1, "", -1, "\n",
        "0123456789abcdef80ff");
}

static void test_format_bytes_32_bytes_1_grouping()
{
    stlsoft::byte_t const   bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };

    FORMAT_BYTES_EXPECT_(bytes, 1, " ", -1, "\n",
        "00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f");
}

static void test_format_bytes_32_bytes_2_grouping()
{
    stlsoft::byte_t const   bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };

    FORMAT_BYTES_EXPECT_(bytes, 2, " ", -1, "\n",
        "0100 0302 0504 0706 0908 0b0a 0d0c 0f0e 1110 1312 1514 1716 1918 1b1a 1d1c 1f1e");
}

static void test_format_bytes_32_bytes_4_grouping()
{
    stlsoft::byte_t const   bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };

    FORMAT_BYTES_EXPECT_(bytes, 4, " ", -1, "\n",
        "03020100 07060504 0b0a0908 0f0e0d0c 13121110 17161514 1b1a1918 1f1e1d1c");
}

static void test_format_bytes_32_bytes_8_grouping()
{
    stlsoft::byte_t const   bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };

    FORMAT_BYTES_EXPECT_(bytes, 8, " ", -1, "\n",
        "0706050403020100 0f0e0d0c0b0a0908 1716151413121110 1f1e1d1c1b1a1918");
}

static void test_format_bytes_32_bytes_16_grouping()
{
    stlsoft::byte_t const   bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };

    FORMAT_BYTES_EXPECT_(bytes, 16, " ", -1, "\n",
        "0f0e0d0c0b0a09080706050403020100 1f1e1d1c1b1a19181716151413121110");
}

static void test_format_bytes_32_bytes_32_grouping()
{
    stlsoft::byte_t const   bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };

    FORMAT_BYTES_EXPECT_(bytes, 32, " ", -1, "\n",
        "1f1e1d1c1b1a191817161514131211100f0e0d0c0b0a09080706050403020100");
}

static void test_format_bytes_3_bytes_32_grouping()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03 };

    FORMAT_BYTES_EXPECT_(bytes, 32, " ", -1, "\n",
        "0000000000000000000000000000000000000000000000000000000000030201");
}

static void test_format_bytes_33_bytes_32_grouping()
{
    stlsoft::byte_t const   bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20 };

    FORMAT_BYTES_EXPECT_(bytes, 32, " ", -1, "\n",
        "1f1e1d1c1b1a191817161514131211100f0e0d0c0b0a09080706050403020100 0000000000000000000000000000000000000000000000000000000000000020");
}

static void test_format_bytes_0_grouping_DEFAULTS_TO_4()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    FORMAT_BYTES_EXPECT_(bytes, 0, " ", -1, "\n",
        "04030201 08070605");
}

static void test_format_bytes_NULL_group_separator()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03, 0x04 };

    FORMAT_BYTES_EXPECT_(bytes, 1, NULL, -1, "\n",
        "01020304");
}

static void test_format_bytes_EMPTY_group_separator()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03, 0x04 };

    FORMAT_BYTES_EXPECT_(bytes, 2, "", -1, "\n",
        "02010403");
}

static void test_format_bytes_MULTI_CHAR_separators()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    FORMAT_BYTES_EXPECT_(bytes, 1, "::", 3, "||",
        "01::02::03||04::05::06||07::08");
}

static void test_format_bytes_lines_PARTIAL_LAST_LINE()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    FORMAT_BYTES_EXPECT_(bytes, 1, " ", 3, "\n",
        "01 02 03\n04 05 06\n07 08");
}

static void test_format_bytes_lines_EXACT_LINES()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    FORMAT_BYTES_EXPECT_(bytes, 1, " ", 4, "\n",
        "01 02 03 04\n05 06 07 08");
}

static void test_format_bytes_lines_ONE_GROUP_PER_LINE()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    FORMAT_BYTES_EXPECT_(bytes, 2, " ", 1, "\r\n",
        "0201\r\n0403\r\n0605\r\n0807");
}

static void test_format_bytes_lines_MORE_GROUPS_PER_LINE_THAN_GROUPS()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    FORMAT_BYTES_EXPECT_(bytes, 1, " ", 100, "\n",
        "01 02 03 04 05 06 07 08");
}

static void test_format_bytes_lines_NONPOSITIVE_groupsPerLine()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    FORMAT_BYTES_EXPECT_(bytes, 1, " ", 0, "\n",
        "01 02 03 04 05 06 07 08");

    stlsoft::byte_t const   bytes2[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

    FORMAT_BYTES_EXPECT_(bytes2, 1, " ", -1, "\n",
        "01 02 03 04 05 06 07 08");
}

static void test_format_bytes_lines_32_BYTE_GROUPS()
{
    stlsoft::byte_t const   bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f };

    FORMAT_BYTES_EXPECT_(bytes, 32, " ", 1, "\n",
        "1f1e1d1c1b1a191817161514131211100f0e0d0c0b0a09080706050403020100\n3f3e3d3c3b3a393837363534333231302f2e2d2c2b2a29282726252423222120");
}

static void test_format_bytes_BUFFER_EXACT_PLUS_NUL()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03 };
    char                    sz[9];
    std::size_t const       n = stlsoft::format_bytes(&bytes[0], sizeof(bytes), &sz[0], STLSOFT_NUM_ELEMENTS(sz), 1, " ");

    TEST_INT_EQ(8, static_cast<int>(n));
    TEST_MS_EQ_N("01 02 03", sz, 8);
    TEST_CHAR_EQ('\0', sz[8]);
}

static void test_format_bytes_BUFFER_EXACT_NO_NUL()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03 };
    char                    sz[8];
    std::size_t const       n = stlsoft::format_bytes(&bytes[0], sizeof(bytes), &sz[0], STLSOFT_NUM_ELEMENTS(sz), 1, " ");

    TEST_INT_EQ(8, static_cast<int>(n));
    TEST_MS_EQ_N("01 02 03", sz, 8);
}

static void test_format_bytes_BUFFER_TOO_SMALL_RETURNS_REQUIRED_SIZE()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03 };
    char                    sz[7];
    std::size_t const       n = stlsoft::format_bytes(&bytes[0], sizeof(bytes), &sz[0], STLSOFT_NUM_ELEMENTS(sz), 1, " ");

    TEST_INT_EQ(8, static_cast<int>(n));

    {
        char                sz2[8];
        std::size_t const   n2 = stlsoft::format_bytes(&bytes[0], sizeof(bytes), &sz2[0], STLSOFT_NUM_ELEMENTS(sz2), 1, " ");

        TEST_INT_EQ(static_cast<int>(n), static_cast<int>(n2));
        TEST_MS_EQ_N("01 02 03", sz2, static_cast<int>(n2));
    }
}

static void test_format_bytes_NULL_BUFFER_QUERIES_REQUIRED_SIZE()
{
    stlsoft::byte_t const   bytes[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

    TEST_INT_EQ(14, static_cast<int>(stlsoft::format_bytes(&bytes[0], sizeof(bytes), NULL, 0, 1, " ")));
    TEST_INT_EQ(17, static_cast<int>(stlsoft::format_bytes(&bytes[0], sizeof(bytes), NULL, 0, 4, " ")));
    TEST_INT_EQ(14, static_cast<int>(stlsoft::format_bytes(&bytes[0], sizeof(bytes), NULL, 0, 2, " ")));
}

#ifndef STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF

# define FORMAT_HEX_EXPECT_(fn_, num_chars_, bytes_, upper_, high_first_, expected_) \
    \
    do \
    { \
        char        sz_[(num_chars_) + 1]; \
        std::size_t i_; \
        \
        for (i_ = 0; i_ != STLSOFT_NUM_ELEMENTS(sz_); ++i_) \
        { \
            sz_[i_] = '#'; \
        } \
        \
        fn_(&sz_[0], &(bytes_)[0], (upper_), (high_first_)); \
        \
        TEST_MS_EQ_N((expected_), sz_, (num_chars_)); \
        TEST_CHAR_EQ('#', sz_[num_chars_]); \
    } while (0)

namespace impl_ = ::stlsoft::conversion::format::impl;

static void test_format_hex_impl_uint8_CASE()
{
    stlsoft::byte_t const bytes[] = { 0xab };
    char sz[3] = { '#', '#', '#' };

    impl_::format_hex_uint8(&sz[0], &bytes[0], false);
    TEST_MS_EQ_N("ab", sz, 2);
    TEST_CHAR_EQ('#', sz[2]);

    impl_::format_hex_uint8(&sz[0], &bytes[0], true);
    TEST_MS_EQ_N("AB", sz, 2);
    TEST_CHAR_EQ('#', sz[2]);
}

static void test_format_hex_impl_uint16_CASE_AND_ORDER()
{
    stlsoft::byte_t const bytes[] = { 0x12, 0xab };

    FORMAT_HEX_EXPECT_(impl_::format_hex_uint16, 4, bytes, false, false,
        "ab12");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint16, 4, bytes, false, true,
        "12ab");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint16, 4, bytes, true, false,
        "AB12");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint16, 4, bytes, true, true,
        "12AB");
}

static void test_format_hex_impl_uint32_CASE_AND_ORDER()
{
    stlsoft::byte_t const bytes[] = { 0x01, 0x23, 0xab, 0xcd };

    FORMAT_HEX_EXPECT_(impl_::format_hex_uint32, 8, bytes, false, false,
        "cdab2301");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint32, 8, bytes, false, true,
        "0123abcd");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint32, 8, bytes, true, false,
        "CDAB2301");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint32, 8, bytes, true, true,
        "0123ABCD");
}

static void test_format_hex_impl_uint64_CASE_AND_ORDER()
{
    stlsoft::byte_t const bytes[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };

    FORMAT_HEX_EXPECT_(impl_::format_hex_uint64, 16, bytes, false, false,
        "efcdab8967452301");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint64, 16, bytes, false, true,
        "0123456789abcdef");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint64, 16, bytes, true, false,
        "EFCDAB8967452301");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint64, 16, bytes, true, true,
        "0123456789ABCDEF");
}

static void test_format_hex_impl_uint128_CASE_AND_ORDER()
{
    stlsoft::byte_t const bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

    FORMAT_HEX_EXPECT_(impl_::format_hex_uint128, 32, bytes, false, false,
        "0f0e0d0c0b0a09080706050403020100");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint128, 32, bytes, false, true,
        "000102030405060708090a0b0c0d0e0f");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint128, 32, bytes, true, false,
        "0F0E0D0C0B0A09080706050403020100");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint128, 32, bytes, true, true,
        "000102030405060708090A0B0C0D0E0F");
}

static void test_format_hex_impl_uint256_CASE_AND_ORDER()
{
    stlsoft::byte_t const bytes[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };

    FORMAT_HEX_EXPECT_(impl_::format_hex_uint256, 64, bytes, false, false,
        "1f1e1d1c1b1a191817161514131211100f0e0d0c0b0a09080706050403020100");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint256, 64, bytes, false, true,
        "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint256, 64, bytes, true, false,
        "1F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100");
    FORMAT_HEX_EXPECT_(impl_::format_hex_uint256, 64, bytes, true, true,
        "000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F");
}

# undef FORMAT_HEX_EXPECT_

#endif /* !STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF */

#undef FORMAT_BYTES_EXPECT_
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

