/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.byte_format_functions/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::basic_simple_string`.
 *
 * Created: 12th September 2019
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */

// #define STLSOFT_DEBUG
// #define STLSOFT_CONVERSION_BYTE_FORMAT_FUNCTIONS_USE_SPRINTF


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

    static void test_1_21();
    static void test_1_22();
    static void test_1_23();
    static void test_1_24();
    static void test_1_25();
    static void test_1_26();
    static void test_1_27();
    static void test_1_28();
    static void test_1_29();
    static void test_1_30();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.byte_format_functions", verbosity))
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

        XTESTS_RUN_CASE(test_1_21);
        XTESTS_RUN_CASE(test_1_22);
        XTESTS_RUN_CASE(test_1_23);
        XTESTS_RUN_CASE(test_1_24);
        XTESTS_RUN_CASE(test_1_25);
        XTESTS_RUN_CASE(test_1_26);
        XTESTS_RUN_CASE(test_1_27);
        XTESTS_RUN_CASE(test_1_28);
        XTESTS_RUN_CASE(test_1_29);
        XTESTS_RUN_CASE(test_1_30);

#ifdef STLSOFT_USE_XCOVER
        XCOVER_REPORT_FILE_COVERAGE("*stlsoft*/simple_string.hpp", NULL);
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


static void test_1_21()
{
}

static void test_1_22()
{
}

static void test_1_23()
{
}

static void test_1_24()
{
}

static void test_1_25()
{
}

static void test_1_26()
{
}

static void test_1_27()
{
}

static void test_1_28()
{
}

static void test_1_29()
{
}

static void test_1_30()
{
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

