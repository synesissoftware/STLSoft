/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.count_decimal_digits/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::count_decimal_digits`.
 *
 * Created: 18th October 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/util/count_digits/count_decimal_digits.h>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_count_decimal_digits_WITH_uint16();
    static void TEST_count_decimal_digits_WITH_uint32();
    static void TEST_count_decimal_digits_WITH_uint64();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.count_decimal_digits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_count_decimal_digits_WITH_uint16);
        XTESTS_RUN_CASE(TEST_count_decimal_digits_WITH_uint32);
        XTESTS_RUN_CASE(TEST_count_decimal_digits_WITH_uint64);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_count_decimal_digits_WITH_uint16()
{
    typedef stlsoft::ss_uint16_t                            uint_t;

    TEST_INT_EQ(1, stlsoft::count_decimal_digits(uint_t(0)));

    for (uint_t i = 1; 10 != i; ++i)
    {
        TEST_INT_EQ(1, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10; 100 != i; ++i)
    {
        TEST_INT_EQ(2, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 100; 1000 != i; ++i)
    {
        TEST_INT_EQ(3, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 1000; 10000 != i; ++i)
    {
        TEST_INT_EQ(4, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10000; 65535 != i; ++i)
    {
        TEST_INT_EQ(5, stlsoft::count_decimal_digits(i));
    }
}

static void TEST_count_decimal_digits_WITH_uint32()
{
    typedef stlsoft::ss_uint32_t                            uint_t;

    TEST_INT_EQ(1, stlsoft::count_decimal_digits(uint_t(0)));

    for (uint_t i = 1; 10 != i; ++i)
    {
        TEST_INT_EQ(1, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10; 100 != i; ++i)
    {
        TEST_INT_EQ(2, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 100; 1000 != i; ++i)
    {
        TEST_INT_EQ(3, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 1000; 10000 != i; ++i)
    {
        TEST_INT_EQ(4, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10000; 100000 != i; ++i)
    {
        TEST_INT_EQ(5, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 100000; 1000000 != i; ++i)
    {
        TEST_INT_EQ(6, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 1000000; 10000000 != i; ++i)
    {
        TEST_INT_EQ(7, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10000000; 100000000 != i; i += 1000)
    {
        TEST_INT_EQ(8, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 100000000; 1000000000 != i; i += 10000)
    {
        TEST_INT_EQ(9, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 1000000000; 4200000000 != i; i += 100000)
    {
        TEST_INT_EQ(10, stlsoft::count_decimal_digits(i));
    }
}

static void TEST_count_decimal_digits_WITH_uint64()
{
    typedef stlsoft::ss_uint64_t                            uint_t;

    TEST_INT_EQ(1, stlsoft::count_decimal_digits(uint_t(0)));

    for (uint_t i = 1; 10 != i; ++i)
    {
        TEST_INT_EQ(1, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10; 100 != i; ++i)
    {
        TEST_INT_EQ(2, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 100; 1000 != i; ++i)
    {
        TEST_INT_EQ(3, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 1000; 10000 != i; ++i)
    {
        TEST_INT_EQ(4, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10000; 100000 != i; ++i)
    {
        TEST_INT_EQ(5, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 100000; 1000000 != i; ++i)
    {
        TEST_INT_EQ(6, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 1000000; 10000000 != i; ++i)
    {
        TEST_INT_EQ(7, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10000000; 100000000 != i; i += 1000)
    {
        TEST_INT_EQ(8, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 100000000; 1000000000 != i; i += 10000)
    {
        TEST_INT_EQ(9, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 1000000000; 10000000000 != i; i += 100000)
    {
        TEST_INT_EQ(10, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10000000000; 100000000000 != i; i += 1000000)
    {
        TEST_INT_EQ(11, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 100000000000; 1000000000000 != i; i += 10000000)
    {
        TEST_INT_EQ(12, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 1000000000000; 10000000000000 != i; i += 100000000)
    {
        TEST_INT_EQ(13, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10000000000000; 100000000000000 != i; i += 1000000000)
    {
        TEST_INT_EQ(14, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 100000000000000; 1000000000000000 != i; i += 10000000000)
    {
        TEST_INT_EQ(15, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 1000000000000000; 10000000000000000 != i; i += 100000000000)
    {
        TEST_INT_EQ(16, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10000000000000000; 100000000000000000 != i; i += 1000000000000)
    {
        TEST_INT_EQ(17, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 100000000000000000; 1000000000000000000 != i; i += 10000000000000)
    {
        TEST_INT_EQ(18, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 1000000000000000000; 10000000000000000000u != i; i += 100000000000000)
    {
        TEST_INT_EQ(19, stlsoft::count_decimal_digits(i));
    }

    for (uint_t i = 10000000000000000000u; 18000000000000000000u != i; i += 1000000000000000)
    {
        TEST_INT_EQ(20, stlsoft::count_decimal_digits(i));
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

