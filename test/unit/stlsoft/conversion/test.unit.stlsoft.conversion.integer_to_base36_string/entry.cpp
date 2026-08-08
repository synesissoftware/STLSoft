/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.integer_to_base36_string/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::integer_to_base36_string`.
 *
 * Created: 14th February 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */

#ifdef _WIN32
# ifndef NOMINMAX
#  define NOMINMAX
# endif
#endif


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/conversion/integer_to_string/integer_to_base36_string.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <limits>

/* Standard C header files */
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_zero();
    static void test_ones();
#if __cplusplus >= 201103L
    static void test_fibonacci();
#endif
    static void test_limits();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.integer_to_base36_string", verbosity))
    {
        XTESTS_RUN_CASE(test_zero);
        XTESTS_RUN_CASE(test_ones);
#if __cplusplus >= 201103L
        XTESTS_RUN_CASE(test_fibonacci);
#endif
        XTESTS_RUN_CASE(test_limits);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    struct mapping_t
    {
        long long   v;
        char const* s;
    };

#if __cplusplus >= 201103L

    const mapping_t fibonacci_mappings[] =
    {
            {          0,       "0" }

        ,   {          1,       "1" }
        ,   {          2,       "2" }
        ,   {          3,       "3" }
        ,   {          5,       "5" }
        ,   {          8,       "8" }
        ,   {         13,       "d" }
        ,   {         21,       "l" }
        ,   {         34,       "y" }
        ,   {         55,      "1j" }
        ,   {         89,      "2h" }
        ,   {        144,      "40" }
        ,   {        233,      "6h" }
        ,   {        377,      "ah" }
        ,   {        610,      "gy" }
        ,   {        987,      "rf" }
        ,   {       1597,     "18d" }
        ,   {       2584,     "1zs" }
        ,   {       4181,     "385" }
        ,   {       6765,     "57x" }
        ,   {      10946,     "8g2" }
        ,   {      17711,     "dnz" }
        ,   {      28657,     "m41" }
        ,   {      46368,     "zs0" }
        ,   {      75025,    "1lw1" }
        ,   {     121393,    "2lo1" }
        ,   {     196418,    "47k2" }
        ,   {     317811,    "6t83" }
        ,   {     514229,    "b0s5" }

        ,   {         -1,      "-1" }
        ,   {         -2,      "-2" }
        ,   {         -3,      "-3" }
        ,   {         -5,      "-5" }
        ,   {         -8,      "-8" }
        ,   {        -13,      "-d" }
        ,   {        -21,      "-l" }
        ,   {        -34,      "-y" }
        ,   {        -55,     "-1j" }
        ,   {        -89,     "-2h" }
        ,   {       -144,     "-40" }
        ,   {       -233,     "-6h" }
        ,   {       -377,     "-ah" }
        ,   {       -610,     "-gy" }
        ,   {       -987,     "-rf" }
        ,   {      -1597,    "-18d" }
        ,   {      -2584,    "-1zs" }
        ,   {      -4181,    "-385" }
        ,   {      -6765,    "-57x" }
        ,   {     -10946,    "-8g2" }
        ,   {     -17711,    "-dnz" }
        ,   {     -28657,    "-m41" }
        ,   {     -46368,    "-zs0" }
        ,   {     -75025,   "-1lw1" }
        ,   {    -121393,   "-2lo1" }
        ,   {    -196418,   "-47k2" }
        ,   {    -317811,   "-6t83" }
        ,   {    -514229,   "-b0s5" }
    };
#endif


static void test_zero()
{
    {
        char                buf[21];
        size_t              n;
        char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), 0, &n);

        TEST_INT_EQ(1u, n);
        TEST_MS_EQ("0", s);
    }

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

    {
        char                buf[9];
        char const* const   s   =   stlsoft::integer_to_base36_string(buf, 0);

        TEST_MS_EQ("0", s);
    }
#endif
}

static void test_ones()
{
    {
        char                buf[21];
        size_t              n;
        char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), 1, &n);

        TEST_INT_EQ(1u, n);
        TEST_MS_EQ("1", s);
    }

    {
        char                buf[21];
        size_t              n;
        char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), -1, &n);

        TEST_INT_EQ(2u, n);
        TEST_MS_EQ("-1", s);
    }
}

#if __cplusplus >= 201103L

static void test_fibonacci()
{
    for (size_t i = 0; STLSOFT_NUM_ELEMENTS(fibonacci_mappings) != i; ++i)
    {
        mapping_t const& mapping = fibonacci_mappings[i];

        // check values forward (via `std::strtoll()`)
        {
            char*           endptr;
            long long const v = strtoll(mapping.s, &endptr, 36);

            TEST_INT_EQ(mapping.v, v);
        }

        // long long
        if (std::numeric_limits<long long>::min() <= mapping.v &&
            std::numeric_limits<long long>::max() >= mapping.v)
        {
            char                buf[21];
            size_t              n;
            long long const     v   =   static_cast<long long>(mapping.v);
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), v, &n);

            TEST_MS_EQ(mapping.s, s);
        }

        // long
        if (std::numeric_limits<long>::min() <= mapping.v &&
            std::numeric_limits<long>::max() >= mapping.v)
        {
            char                buf[21];
            size_t              n;
            long const          v   =   static_cast<long>(mapping.v);
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), v, &n);

            TEST_MS_EQ(mapping.s, s);
        }

        // short
        if (std::numeric_limits<short>::min() <= mapping.v &&
            std::numeric_limits<short>::max() >= mapping.v)
        {
            char                buf[21];
            size_t              n;
            short const         v   =   static_cast<short>(mapping.v);
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), v, &n);

            TEST_MS_EQ(mapping.s, s);
        }

        // int8_t
        if (std::numeric_limits<int8_t>::min() <= mapping.v &&
            std::numeric_limits<int8_t>::max() >= mapping.v)
        {
            char                buf[21];
            size_t              n;
            int8_t const        v   =   static_cast<int8_t>(mapping.v);
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), v, &n);

            TEST_MS_EQ(mapping.s, s);
        }

        // int16_t
        if (std::numeric_limits<int16_t>::min() <= mapping.v &&
            std::numeric_limits<int16_t>::max() >= mapping.v)
        {
            char                buf[21];
            size_t              n;
            int16_t const       v   =   static_cast<int16_t>(mapping.v);
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), v, &n);

            TEST_MS_EQ(mapping.s, s);
        }

        // int32_t
        if (std::numeric_limits<int32_t>::min() <= mapping.v &&
            std::numeric_limits<int32_t>::max() >= mapping.v)
        {
            char                buf[21];
            size_t              n;
            int32_t const       v   =   static_cast<int32_t>(mapping.v);
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), v, &n);

            TEST_MS_EQ(mapping.s, s);
        }

        // int64_t
        if (std::numeric_limits<int64_t>::min() <= mapping.v &&
            std::numeric_limits<int64_t>::max() >= mapping.v)
        {
            char                buf[21];
            size_t              n;
            int64_t const       v   =   static_cast<int64_t>(mapping.v);
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), v, &n);

            TEST_MS_EQ(mapping.s, s);
        }
    }
}
#endif

static void test_limits()
{
    // int8_t
    {
        typedef int8_t i_t;

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min(), &n);

            TEST_INT_EQ(3u, n);
            TEST_MS_EQ("-3k", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min() + 1, &n);

            TEST_INT_EQ(3u, n);
            TEST_MS_EQ("-3j", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::max(), &n);

            TEST_INT_EQ(2u, n);
            TEST_MS_EQ("3j", s);
        }

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char                buf[4];
            char const* const   s   =   stlsoft::integer_to_base36_string(buf, std::numeric_limits<i_t>::max());

            TEST_MS_EQ("3j", s);
        }
#endif
    }

    // uint8_t
    {
        typedef uint8_t i_t;

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min(), &n);

            TEST_INT_EQ(1u, n);
            TEST_MS_EQ("0", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::max(), &n);

            TEST_INT_EQ(2u, n);
            TEST_MS_EQ("73", s);
        }

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char                buf[3];
            char const* const   s   =   stlsoft::integer_to_base36_string(buf, std::numeric_limits<i_t>::max());

            TEST_MS_EQ("73", s);
        }
#endif
    }

    // int16_t
    {
        typedef int16_t i_t;

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min(), &n);

            TEST_INT_EQ(4u, n);
            TEST_MS_EQ("-pa8", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min() + 1, &n);

            TEST_INT_EQ(4u, n);
            TEST_MS_EQ("-pa7", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::max(), &n);

            TEST_INT_EQ(3u, n);
            TEST_MS_EQ("pa7", s);
        }

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char                buf[5];
            char const* const   s   =   stlsoft::integer_to_base36_string(buf, std::numeric_limits<i_t>::max());

            TEST_MS_EQ("pa7", s);
        }
#endif
    }

    // uint16_t
    {
        typedef uint16_t i_t;

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min(), &n);

            TEST_INT_EQ(1u, n);
            TEST_MS_EQ("0", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::max(), &n);

            TEST_INT_EQ(4u, n);
            TEST_MS_EQ("1ekf", s);
        }

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char                buf[5];
            char const* const   s   =   stlsoft::integer_to_base36_string(buf, std::numeric_limits<i_t>::max());

            TEST_MS_EQ("1ekf", s);
        }
#endif
    }

    // int32_t
    {
        typedef int32_t i_t;

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min(), &n);

            TEST_INT_EQ(7u, n);
            TEST_MS_EQ("-zik0zk", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min() + 1, &n);

            TEST_INT_EQ(7u, n);
            TEST_MS_EQ("-zik0zj", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::max(), &n);

            TEST_INT_EQ(6u, n);
            TEST_MS_EQ("zik0zj", s);
        }

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char                buf[8];
            char const* const   s   =   stlsoft::integer_to_base36_string(buf, std::numeric_limits<i_t>::max());

            TEST_MS_EQ("zik0zj", s);
        }
#endif
    }

    // uint32_t
    {
        typedef uint32_t i_t;

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min(), &n);

            TEST_INT_EQ(1u, n);
            TEST_MS_EQ("0", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::max(), &n);

            TEST_INT_EQ(7u, n);
            TEST_MS_EQ("1z141z3", s);
        }

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char                buf[8];
            char const* const   s   =   stlsoft::integer_to_base36_string(buf, std::numeric_limits<i_t>::max());

            TEST_MS_EQ("1z141z3", s);
        }
#endif
    }

    // int64_t
    {
        typedef int64_t i_t;

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min(), &n);

            TEST_INT_EQ(14u, n);
            TEST_MS_EQ("-1y2p0ij32e8e8", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min() + 1, &n);

            TEST_INT_EQ(14u, n);
            TEST_MS_EQ("-1y2p0ij32e8e7", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::max(), &n);

            TEST_INT_EQ(13u, n);
            TEST_MS_EQ("1y2p0ij32e8e7", s);
        }

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char                buf[15];
            char const* const   s   =   stlsoft::integer_to_base36_string(buf, std::numeric_limits<i_t>::max());

            TEST_MS_EQ("1y2p0ij32e8e7", s);
        }
#endif
    }

    // uint64_t
    {
        typedef uint64_t i_t;

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::min(), &n);

            TEST_INT_EQ(1u, n);
            TEST_MS_EQ("0", s);
        }

        {
            char                buf[21];
            size_t              n;
            char const* const   s   =   stlsoft::integer_to_base36_string(&buf[0], STLSOFT_NUM_ELEMENTS(buf), std::numeric_limits<i_t>::max(), &n);

            TEST_INT_EQ(13u, n);
            TEST_MS_EQ("3w5e11264sgsf", s);
        }

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

        {
            char                buf[14];
            char const* const   s   =   stlsoft::integer_to_base36_string(buf, std::numeric_limits<i_t>::max());

            TEST_MS_EQ("3w5e11264sgsf", s);
        }
#endif
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

