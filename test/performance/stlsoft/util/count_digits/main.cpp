/* /////////////////////////////////////////////////////////////////////////
 * File:    count_digits/main.cpp
 *
 * Purpose: Perf-test for digit-counting functions.
 *
 * Created: 18th December 2024
 * Updated: 30th September 2026
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

#include <stlsoft/util/count_digits.h>

#if __cplusplus >= 201103L
# include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>
#else
# include <platformstl/diagnostics/stopwatch.hpp>
#endif /* C++11+ */
#include <stlsoft/conversion/number/grouping_functions.hpp>

#include "perf_group_gaps.hpp"

#include <iomanip>
#include <iostream>


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


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

    ss_size_t const NUM_ITERATIONS = 20000000;
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
    char    dest[41];
    size_t  n = stlsoft::format_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3;0", v);

    return std::string(dest, n);
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int /*argc*/, char* /*argv*/[])
{
    perf_maybe_emit_groupgaps_banner(std::cout);

    // count_decimal_digits
    /* Gap between digit-count function families. */
    perf_maybe_emit_group_gap(std::cout, "count_decimal_digits");
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            stlsoft::uint8_t const v = i & 0xff;

            anchor_value += stlsoft::count_decimal_digits(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            stlsoft::uint16_t const v = i & 0xffff;

            anchor_value += stlsoft::count_decimal_digits(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            stlsoft::uint32_t const v = i & 0xffffffff;

            anchor_value += stlsoft::count_decimal_digits(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            stlsoft::uint64_t const v = i;

            anchor_value += stlsoft::count_decimal_digits(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            stlsoft::uint64_t const v = i;

            anchor_value += stlsoft::count_decimal_digits(v << 32);
        }
        sw.stop();

        interval_t const int_uint64_32 = sw.get_nanoseconds();


        if (1 == W)
        {
            std::cout
                << '\t'
                << "count_decimal_digits()"
                << '\t'
                << std::setw(16) << std::right << thousands(int_uint8)
                << '\t'
                << std::setw(16) << std::right << thousands(int_uint16)
                << '\t'
                << std::setw(16) << std::right << thousands(int_uint32)
                << '\t'
                << std::setw(16) << std::right << thousands(int_uint64)
                << '\t'
                << std::setw(16) << std::right << thousands(int_uint64_32)
                << '\t'
                << anchor_value
                << std::endl;
        }
    }


    // count_hexadecimal_digits
    /* Gap between digit-count function families. */
    perf_maybe_emit_group_gap(std::cout, "count_hexadecimal_digits");
    for (int W = 2; 0 != W; --W)
    {
        stopwatch_t sw;

        int anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            stlsoft::uint8_t const v = i & 0xff;

            anchor_value += stlsoft::count_hexadecimal_digits(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            stlsoft::uint16_t const v = i & 0xffff;

            anchor_value += stlsoft::count_hexadecimal_digits(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            stlsoft::uint32_t const v = i & 0xffffffff;

            anchor_value += stlsoft::count_hexadecimal_digits(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            stlsoft::uint64_t const v = i;

            anchor_value += stlsoft::count_hexadecimal_digits(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            stlsoft::uint64_t const v = i;

            anchor_value += stlsoft::count_hexadecimal_digits(v << 32);
        }
        sw.stop();

        interval_t const int_uint64_32 = sw.get_nanoseconds();


        if (1 == W)
        {
            std::cout
                << '\t'
                << "count_hexadecimal_digits()"
                << '\t'
                << std::setw(16) << std::right << thousands(int_uint8)
                << '\t'
                << std::setw(16) << std::right << thousands(int_uint16)
                << '\t'
                << std::setw(16) << std::right << thousands(int_uint32)
                << '\t'
                << std::setw(16) << std::right << thousands(int_uint64)
                << '\t'
                << std::setw(16) << std::right << thousands(int_uint64_32)
                << '\t'
                << anchor_value
                << std::endl;
        }
    }


    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

