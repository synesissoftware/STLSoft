/* /////////////////////////////////////////////////////////////////////////
 * File:    test.performance.stlsoft.bit_functions/main.cpp
 *
 * Purpose: Perf-test for bit functions.
 *
 * Created: 24th September 2026
 * Updated: 24th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if !defined(__cplusplus) || \
    __cplusplus < 201103L
# error Requires C++11 or later
#endif


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/util/bit_functions.h>

#if __cplusplus >= 201103L
# include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>
#else
# include <platformstl/diagnostics/stopwatch.hpp>
#endif /* C++11+ */
#include <stlsoft/conversion/number/grouping_functions.hpp>

#include <iomanip>
#include <iostream>
#include <string>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

#if __cplusplus >= 201103L

typedef stlsoft::std_chrono_hrc_stopwatch                   stopwatch_t;
#else

typedef platformstl::stopwatch                              stopwatch_t;
#endif /* C++11+ */
typedef stopwatch_t::interval_type                          interval_t;

using stlsoft::ss_size_t;
using stlsoft::ss_uint8_t;
using stlsoft::ss_uint16_t;
using stlsoft::ss_uint32_t;
using stlsoft::ss_uint64_t;


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

    ss_size_t const NUM_ITERATIONS   = 20000000;
    ss_size_t const XOR_RANGE_LEN    = 64;
    int const       FN_COL_WIDTH     = 42;
    int const       METRIC_COL_WIDTH = 16;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

template <ss_typename_param_k T_integer>
std::string
thousands(
    T_integer const& v
)
{
    char            dest[41];
    size_t const    n = stlsoft::format_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3;0", v);

    return std::string(dest, n);
}

void
emit_metric_cell(
    char const* s
)
{
    std::cout
        << '\t'
        << std::setw(METRIC_COL_WIDTH) << std::right << s;
}

void
emit_metric_cell(
    interval_t const& v
)
{
    emit_metric_cell(thousands(v).c_str());
}

void
emit_absent_metric_cell()
{
    emit_metric_cell("-");
}

void
emit_header_row()
{
    std::cout
        << std::setw(FN_COL_WIDTH) << std::left << ""
        ;
    emit_metric_cell("uint8_t");
    emit_metric_cell("uint16_t");
    emit_metric_cell("uint32_t");
    emit_metric_cell("uint64_t");
    emit_metric_cell("int");
    emit_metric_cell("anchor");
    std::cout << std::endl;
}

void
emit_result_row(
    char const*             function_name
,   interval_t const*       uint8_ns
,   interval_t const*       uint16_ns
,   interval_t const*       uint32_ns
,   interval_t const*       uint64_ns
,   interval_t const*       int_ns
,   int                     anchor_value
)
{
    std::cout
        << std::setw(FN_COL_WIDTH) << std::left << function_name
        ;

    if (NULL != uint8_ns)
    {
        emit_metric_cell(*uint8_ns);
    }
    else
    {
        emit_absent_metric_cell();
    }

    if (NULL != uint16_ns)
    {
        emit_metric_cell(*uint16_ns);
    }
    else
    {
        emit_absent_metric_cell();
    }

    if (NULL != uint32_ns)
    {
        emit_metric_cell(*uint32_ns);
    }
    else
    {
        emit_absent_metric_cell();
    }

    if (NULL != uint64_ns)
    {
        emit_metric_cell(*uint64_ns);
    }
    else
    {
        emit_absent_metric_cell();
    }

    if (NULL != int_ns)
    {
        emit_metric_cell(*int_ns);
    }
    else
    {
        emit_absent_metric_cell();
    }

    emit_metric_cell(thousands(anchor_value).c_str());
    std::cout << std::endl;
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int /*argc*/, char* /*argv*/[])
{
    ss_uint8_t  xor8[XOR_RANGE_LEN];
    ss_uint16_t xor16[XOR_RANGE_LEN];
    ss_uint32_t xor32[XOR_RANGE_LEN];
    ss_uint64_t xor64[XOR_RANGE_LEN];

    for (ss_size_t i = 0; XOR_RANGE_LEN != i; ++i)
    {
        xor8[i]  = static_cast<ss_uint8_t>(i * 3u + 1u);
        xor16[i] = static_cast<ss_uint16_t>(i * 7u + 1u);
        xor32[i] = static_cast<ss_uint32_t>(i * 11u + 1u);
        xor64[i] = static_cast<ss_uint64_t>(i * 13u + 1u);
    }

    emit_header_row();


    // count_bits_by_Kernighan_method
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = i;

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = i;

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "count_bits_by_Kernighan_method()"
            ,   NULL
            ,   NULL
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }
    }


    // count_bits_by_8bit_table
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = i;

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = i;

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "count_bits_by_8bit_table()"
            ,   NULL
            ,   NULL
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }
    }


    // count_bits
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = i;

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = i;

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            int const v = static_cast<int>(i);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_int = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "count_bits()"
            ,   NULL
            ,   NULL
            ,   &int_uint32
            ,   &int_uint64
            ,   &int_int
            ,   anchor_value
            );
        }
    }


    // ------------------------------------------------------------------
    // Dense inputs (~i): high popcount — favourable to the table path
    // ------------------------------------------------------------------

    // count_bits_by_Kernighan_method (dense)
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ~ss_uint32_t(i);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ~ss_uint64_t(i);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "count_bits_by_Kernighan_method()/~i"
            ,   NULL
            ,   NULL
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }
    }


    // count_bits_by_8bit_table (dense)
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ~ss_uint32_t(i);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ~ss_uint64_t(i);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "count_bits_by_8bit_table()/~i"
            ,   NULL
            ,   NULL
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }
    }


    // count_bits (dense)
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ~ss_uint32_t(i);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ~ss_uint64_t(i);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            int const v = static_cast<int>(~ss_uint32_t(i));

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_int = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "count_bits()/~i"
            ,   NULL
            ,   NULL
            ,   &int_uint32
            ,   &int_uint64
            ,   &int_int
            ,   anchor_value
            );
        }
    }


    // ------------------------------------------------------------------
    // Max density (all-ones). Source via volatile so inlining cannot
    // constant-fold popcount(~0) to a literal.
    // ------------------------------------------------------------------

    {
        ss_uint32_t volatile ones32 = ~ss_uint32_t(0);
        ss_uint64_t volatile ones64 = ~ss_uint64_t(0);


        // count_bits_by_Kernighan_method (max)
        for (int W = 2; 0 != W; --W)
        {
            stopwatch_t sw;

            int anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint32_t const v = ones32;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
            }
            sw.stop();

            interval_t const int_uint32 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint64_t const v = ones64;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
            }
            sw.stop();

            interval_t const int_uint64 = sw.get_nanoseconds();


            if (1 == W)
            {
                emit_result_row(
                    "count_bits_by_Kernighan_method()/ones"
                ,   NULL
                ,   NULL
                ,   &int_uint32
                ,   &int_uint64
                ,   NULL
                ,   anchor_value
                );
            }
        }


        // count_bits_by_8bit_table (max)
        for (int W = 2; 0 != W; --W)
        {
            stopwatch_t sw;

            int anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint32_t const v = ones32;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_8bit_table(v);
            }
            sw.stop();

            interval_t const int_uint32 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint64_t const v = ones64;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_8bit_table(v);
            }
            sw.stop();

            interval_t const int_uint64 = sw.get_nanoseconds();


            if (1 == W)
            {
                emit_result_row(
                    "count_bits_by_8bit_table()/ones"
                ,   NULL
                ,   NULL
                ,   &int_uint32
                ,   &int_uint64
                ,   NULL
                ,   anchor_value
                );
            }
        }


        // count_bits (max)
        for (int W = 2; 0 != W; --W)
        {
            stopwatch_t sw;

            int anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint32_t const v = ones32;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits(v);
            }
            sw.stop();

            interval_t const int_uint32 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint64_t const v = ones64;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits(v);
            }
            sw.stop();

            interval_t const int_uint64 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                int const v = static_cast<int>(ones32);

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits(v);
            }
            sw.stop();

            interval_t const int_int = sw.get_nanoseconds();


            if (1 == W)
            {
                emit_result_row(
                    "count_bits()/ones"
                ,   NULL
                ,   NULL
                ,   &int_uint32
                ,   &int_uint64
                ,   &int_int
                ,   anchor_value
                );
            }
        }
    }


    // ------------------------------------------------------------------
    // Close-to-max: all-ones with one rotating bit cleared (31 / 63 ones)
    // ------------------------------------------------------------------

    // count_bits_by_Kernighan_method (close-to-max)
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ~ss_uint32_t(0) ^ (ss_uint32_t(1) << (i % 32u));

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ~ss_uint64_t(0) ^ (ss_uint64_t(1) << (i % 64u));

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "count_bits_by_Kernighan_method()/ones^1"
            ,   NULL
            ,   NULL
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }
    }


    // count_bits_by_8bit_table (close-to-max)
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ~ss_uint32_t(0) ^ (ss_uint32_t(1) << (i % 32u));

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ~ss_uint64_t(0) ^ (ss_uint64_t(1) << (i % 64u));

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "count_bits_by_8bit_table()/ones^1"
            ,   NULL
            ,   NULL
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }
    }


    // count_bits (close-to-max)
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ~ss_uint32_t(0) ^ (ss_uint32_t(1) << (i % 32u));

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ~ss_uint64_t(0) ^ (ss_uint64_t(1) << (i % 64u));

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            int const v = static_cast<int>(~ss_uint32_t(0) ^ (ss_uint32_t(1) << (i % 32u)));

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_int = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "count_bits()/ones^1"
            ,   NULL
            ,   NULL
            ,   &int_uint32
            ,   &int_uint64
            ,   &int_int
            ,   anchor_value
            );
        }
    }


    // find_highest_bit
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = static_cast<ss_uint8_t>(i & 0xff);

            anchor_value += stlsoft::find_highest_bit(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = static_cast<ss_uint16_t>(i & 0xffff);

            anchor_value += stlsoft::find_highest_bit(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = i;

            anchor_value += stlsoft::find_highest_bit(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = i;

            anchor_value += stlsoft::find_highest_bit(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "find_highest_bit()"
            ,   &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }
    }


    // calculate_xor_over_range
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_size_t const n = (i % XOR_RANGE_LEN) + 1u;

            anchor_value += stlsoft::calculate_xor_over_range(xor8, n);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_size_t const n = (i % XOR_RANGE_LEN) + 1u;

            anchor_value += stlsoft::calculate_xor_over_range(xor16, n);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_size_t const n = (i % XOR_RANGE_LEN) + 1u;

            anchor_value += stlsoft::calculate_xor_over_range(xor32, n);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_size_t const n = (i % XOR_RANGE_LEN) + 1u;

            anchor_value += stlsoft::calculate_xor_over_range(xor64, n);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (1 == W)
        {
            emit_result_row(
                "calculate_xor_over_range()"
            ,   &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }
    }


    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

