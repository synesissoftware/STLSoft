/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.count_hexadecimal_digits/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::count_hexadecimal_digits`.
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

#include <stlsoft/util/count_digits/count_hexadecimal_digits.h>

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

    static void TEST_count_hexadecimal_digits_WITH_uint16();
    static void TEST_count_hexadecimal_digits_WITH_uint32();
    static void TEST_count_hexadecimal_digits_WITH_uint64();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.count_hexadecimal_digits", verbosity))
    {
        XTESTS_RUN_CASE(TEST_count_hexadecimal_digits_WITH_uint16);
        XTESTS_RUN_CASE(TEST_count_hexadecimal_digits_WITH_uint32);
        XTESTS_RUN_CASE(TEST_count_hexadecimal_digits_WITH_uint64);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_count_hexadecimal_digits_WITH_uint16()
{
    typedef stlsoft::ss_uint16_t                            uint_t;

    TEST_INT_EQ(1, stlsoft::count_hexadecimal_digits(uint_t(0)));

    for (uint_t i = 0x1; 0x10 != i; ++i)
    {
        TEST_INT_EQ(1, stlsoft::count_hexadecimal_digits(i));
    }

    for (uint_t i = 0x10; 0x100 != i; ++i)
    {
        TEST_INT_EQ(2, stlsoft::count_hexadecimal_digits(i));
    }

    for (uint_t i = 0x100; 0x1000 != i; ++i)
    {
        TEST_INT_EQ(3, stlsoft::count_hexadecimal_digits(i));
    }

    for (uint_t i = 0x1000; 0xffff != i; ++i)
    {
        TEST_INT_EQ(4, stlsoft::count_hexadecimal_digits(i));
    }
}

static void TEST_count_hexadecimal_digits_WITH_uint32()
{
    typedef stlsoft::ss_uint32_t                            uint_t;

    TEST_INT_EQ(1, stlsoft::count_hexadecimal_digits(uint_t(0)));

    for (uint_t i = 0x1; 0x10 != i; ++i)
    {
        TEST_INT_EQ(1, stlsoft::count_hexadecimal_digits(i));
    }

    for (uint_t i = 0x10; 0x100 != i; ++i)
    {
        TEST_INT_EQ(2, stlsoft::count_hexadecimal_digits(i));
    }

    for (uint_t i = 0x100; 0x1000 != i; ++i)
    {
        TEST_INT_EQ(3, stlsoft::count_hexadecimal_digits(i));
    }

    for (uint_t i = 0x1000; 0x10000 != i; ++i)
    {
        TEST_INT_EQ(4, stlsoft::count_hexadecimal_digits(i));
    }

    for (uint_t i = 0x10000; 0x100000 != i; ++i)
    {
        TEST_INT_EQ(5, stlsoft::count_hexadecimal_digits(i));
    }

    for (uint_t i = 0x100000; 0x1000000 != i; i += 10)
    {
        TEST_INT_EQ(6, stlsoft::count_hexadecimal_digits(i));
    }

    for (uint_t i = 0x1000000; 0x10000000 != i; i += 10)
    {
        TEST_INT_EQ(7, stlsoft::count_hexadecimal_digits(i));
    }

    TEST_INT_EQ(8, stlsoft::count_hexadecimal_digits(uint_t(0x10000000)));
    TEST_INT_EQ(8, stlsoft::count_hexadecimal_digits(uint_t(0xffffffff)));
}

static void TEST_count_hexadecimal_digits_WITH_uint64()
{
    typedef stlsoft::ss_uint64_t                            uint_t;

    TEST_INT_EQ(1, stlsoft::count_hexadecimal_digits(uint_t(0)));

    TEST_INT_EQ(1, stlsoft::count_hexadecimal_digits(uint_t(0x1)));
    TEST_INT_EQ(1, stlsoft::count_hexadecimal_digits(uint_t(0xf)));

    TEST_INT_EQ(2, stlsoft::count_hexadecimal_digits(uint_t(0x10)));
    TEST_INT_EQ(2, stlsoft::count_hexadecimal_digits(uint_t(0xff)));

    TEST_INT_EQ(3, stlsoft::count_hexadecimal_digits(uint_t(0x100)));
    TEST_INT_EQ(3, stlsoft::count_hexadecimal_digits(uint_t(0xfff)));

    TEST_INT_EQ(4, stlsoft::count_hexadecimal_digits(uint_t(0x1000)));
    TEST_INT_EQ(4, stlsoft::count_hexadecimal_digits(uint_t(0xffff)));

    TEST_INT_EQ(5, stlsoft::count_hexadecimal_digits(uint_t(0x10000)));
    TEST_INT_EQ(5, stlsoft::count_hexadecimal_digits(uint_t(0xfffff)));

    TEST_INT_EQ(6, stlsoft::count_hexadecimal_digits(uint_t(0x100000)));
    TEST_INT_EQ(6, stlsoft::count_hexadecimal_digits(uint_t(0xffffff)));

    TEST_INT_EQ(7, stlsoft::count_hexadecimal_digits(uint_t(0x1000000)));
    TEST_INT_EQ(7, stlsoft::count_hexadecimal_digits(uint_t(0xfffffff)));

    TEST_INT_EQ(8, stlsoft::count_hexadecimal_digits(uint_t(0x10000000)));
    TEST_INT_EQ(8, stlsoft::count_hexadecimal_digits(uint_t(0xffffffff)));

    TEST_INT_EQ(9, stlsoft::count_hexadecimal_digits(uint_t(0x100000000)));
    TEST_INT_EQ(9, stlsoft::count_hexadecimal_digits(uint_t(0xfffffffff)));

    TEST_INT_EQ(10, stlsoft::count_hexadecimal_digits(uint_t(0x1000000000)));
    TEST_INT_EQ(10, stlsoft::count_hexadecimal_digits(uint_t(0xffffffffff)));

    TEST_INT_EQ(11, stlsoft::count_hexadecimal_digits(uint_t(0x10000000000)));
    TEST_INT_EQ(11, stlsoft::count_hexadecimal_digits(uint_t(0xfffffffffff)));

    TEST_INT_EQ(12, stlsoft::count_hexadecimal_digits(uint_t(0x100000000000)));
    TEST_INT_EQ(12, stlsoft::count_hexadecimal_digits(uint_t(0xffffffffffff)));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

