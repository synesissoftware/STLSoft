/* /////////////////////////////////////////////////////////////////////////
 * File:    integer_to_string/main.cpp
 *
 * Purpose: Perf-test for `stlsoft::integer_to_string<>`.
 *
 * Created: 29th October 2016
 * Updated: 30th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/conversion/integer_to_string/integer_to_decimal_string.hpp>
#include <stlsoft/conversion/integer_to_string/integer_to_hexadecimal_string.hpp>
#include <stlsoft/conversion/integer_to_string/integer_to_octal_string.hpp>
#include <stlsoft/conversion/integer_to_string/integer_to_base32_string.hpp>
#include <stlsoft/conversion/integer_to_string/integer_to_base36_string.hpp>
#include <stlsoft/util/integral_printf_traits.hpp>
#include <stlsoft/util/true_typedef.hpp>

#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>

#include "perf_group_gaps.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

STLSOFT_GEN_OPAQUE(h_WARMUPS_tt)
typedef stlsoft::true_typedef<size_t, h_WARMUPS_tt>         Warmups;
STLSOFT_GEN_OPAQUE(h_LOOPS_tt)
typedef stlsoft::true_typedef<size_t, h_LOOPS_tt>           Loops;
STLSOFT_GEN_OPAQUE(h_ITERATIONS_tt)
typedef stlsoft::true_typedef<size_t, h_ITERATIONS_tt>      Iterations;


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

template<
    typename    T_integer
,   typename    T_interval
,   typename    T_stopwatch
>
void
display_result(
    T_interval      numEvents
,   T_stopwatch&    stopwatch
)
{
    auto const      interval_us =   stopwatch.get_nanoseconds();
    double const    rate        =   double(interval_us) / numEvents;
    char const*     unit        =   "ns";
    double          rate_eff    =   rate;

    if (rate_eff > 100000000)
    {
        rate_eff    =   rate / 1000000000;
        unit        =   "s";
    }
    else
    if (rate_eff > 100000)
    {
        rate_eff    =   rate / 1000000;
        unit        =   "ms";
    }
    else
    if (rate_eff > 100)
    {
        rate_eff    =   rate / 1000;
        unit        =   "us";
    }


    fprintf(
            stdout
        ,   "\t\t%-40s\t%12lu\t%12luns\t%8.3f%s\n"
        ,   typeid(T_integer).name()
        ,   static_cast<unsigned long>(numEvents)
        ,   static_cast<unsigned long>(interval_us)
        ,   rate_eff
        ,   unit
        );
}


template<
    typename    T_integer
,   typename    T_stopwatch
>
size_t
execute_printf(
    Warmups             numWarmups
,   Loops               numLoops
,   Iterations          numIterations
,   T_stopwatch&        stopwatch
,   T_integer const&    baseValue
)
{
    size_t total = 0;

    typedef stlsoft::integral_printf_format_traits<T_integer>   ipf_traits_t;

    for (size_t w = numWarmups.base_type_value(); 0 != w; --w)
    {
        stopwatch.start();

        for (size_t i = 0; numLoops.base_type_value() != i; ++i)
        {
            for (size_t j = 0; numIterations.base_type_value() != j; ++j)
            {
                T_integer const     value   =   baseValue + static_cast<T_integer>(j);
                char                sz[21];
                int const           n       =   snprintf(&sz[0], STLSOFT_NUM_ELEMENTS(sz), ipf_traits_t::decimal_format_a(), value);
                char const* const   s       =   &sz[n];

                total += reinterpret_cast<uintptr_t>(s) & 0x0f;
            }
        }

        stopwatch.stop();

        if (1 == w)
        {
            display_result<T_integer>(numLoops.base_type_value() * numIterations.base_type_value(), stopwatch);
        }
    }

    return total;
}

template<
    typename    T_integer
,   typename    T_stopwatch
>
size_t
execute_xtos(
    Warmups             numWarmups
,   Loops               numLoops
,   Iterations          numIterations
,   T_stopwatch&        stopwatch
,   T_integer const&    baseValue
)
{
    size_t total = 0;

    // xtos_traits<T_integer>  converter;

    for (size_t w = numWarmups.base_type_value(); 0 != w; --w)
    {
        stopwatch.start();

        for (size_t i = 0; numLoops.base_type_value() != i; ++i)
        {
            for (size_t j = 0; numIterations.base_type_value() != j; ++j)
            {
                T_integer const     value   =   baseValue + static_cast<T_integer>(j);
                std::string         str     =   std::to_string(value);
                char const* const   s       =   str.c_str();

                total += reinterpret_cast<uintptr_t>(s) & 0x0f;
            }
        }

        stopwatch.stop();

        if (1 == w)
        {
            display_result<T_integer>(numLoops.base_type_value() * numIterations.base_type_value(), stopwatch);
        }
    }

    return total;
}

template<
    typename    T_integer
,   typename    T_stopwatch
>
size_t
execute_dec(
    Warmups             numWarmups
,   Loops               numLoops
,   Iterations          numIterations
,   T_stopwatch&        stopwatch
,   T_integer const&    baseValue
)
{
    size_t total = 0;

    for (size_t w = numWarmups.base_type_value(); 0 != w; --w)
    {
        stopwatch.start();

        for (size_t i = 0; numLoops.base_type_value() != i; ++i)
        {
            for (size_t j = 0; numIterations.base_type_value() != j; ++j)
            {
                T_integer const     value   =   baseValue + static_cast<T_integer>(j);
                char                sz[21];
                char const* const   s = stlsoft::integer_to_decimal_string(&sz[0], STLSOFT_NUM_ELEMENTS(sz), value);

                total += reinterpret_cast<uintptr_t>(s) & 0x0f;
            }
        }

        stopwatch.stop();

        if (1 == w)
        {
            display_result<T_integer>(numLoops.base_type_value() * numIterations.base_type_value(), stopwatch);
        }
    }

    return total;
}

template<
    typename    T_integer
,   typename    T_stopwatch
>
size_t
execute_oct(
    Warmups             numWarmups
,   Loops               numLoops
,   Iterations          numIterations
,   T_stopwatch&        stopwatch
,   T_integer const&    baseValue
)
{
    size_t total = 0;

    for (size_t w = numWarmups.base_type_value(); 0 != w; --w)
    {
        stopwatch.start();

        for (size_t i = 0; numLoops.base_type_value() != i; ++i)
        {
            for (size_t j = 0; numIterations.base_type_value() != j; ++j)
            {
                T_integer const     value   =   baseValue + static_cast<T_integer>(j);
                char                sz[25];
                char const* const   s = stlsoft::integer_to_octal_string(&sz[0], STLSOFT_NUM_ELEMENTS(sz), value);

                total += reinterpret_cast<uintptr_t>(s) & 0x0f;
            }
        }

        stopwatch.stop();

        if (1 == w)
        {
            display_result<T_integer>(numLoops.base_type_value() * numIterations.base_type_value(), stopwatch);
        }
    }

    return total;
}

template<
    typename    T_integer
,   typename    T_stopwatch
>
size_t
execute_hex(
    Warmups             numWarmups
,   Loops               numLoops
,   Iterations          numIterations
,   T_stopwatch&        stopwatch
,   T_integer const&    baseValue
)
{
    size_t total = 0;

    for (size_t w = numWarmups.base_type_value(); 0 != w; --w)
    {
        stopwatch.start();

        for (size_t i = 0; numLoops.base_type_value() != i; ++i)
        {
            for (size_t j = 0; numIterations.base_type_value() != j; ++j)
            {
                T_integer const     value   =   baseValue + static_cast<T_integer>(j);
                char                sz[21];
                char const* const   s = stlsoft::integer_to_hexadecimal_string(&sz[0], STLSOFT_NUM_ELEMENTS(sz), value);

                total += reinterpret_cast<uintptr_t>(s) & 0x0f;
            }
        }

        stopwatch.stop();

        if (1 == w)
        {
            display_result<T_integer>(numLoops.base_type_value() * numIterations.base_type_value(), stopwatch);
        }
    }

    return total;
}

template<
    typename    T_integer
,   typename    T_stopwatch
>
size_t
execute_b32(
    Warmups             numWarmups
,   Loops               numLoops
,   Iterations          numIterations
,   T_stopwatch&        stopwatch
,   T_integer const&    baseValue
)
{
    size_t total = 0;

    for (size_t w = numWarmups.base_type_value(); 0 != w; --w)
    {
        stopwatch.start();

        for (size_t i = 0; numLoops.base_type_value() != i; ++i)
        {
            for (size_t j = 0; numIterations.base_type_value() != j; ++j)
            {
                T_integer const     value   =   baseValue + static_cast<T_integer>(j);
                char                sz[21];
                char const* const   s = stlsoft::integer_to_base32_string(&sz[0], STLSOFT_NUM_ELEMENTS(sz), value);

                total += reinterpret_cast<uintptr_t>(s) & 0x0f;
            }
        }

        stopwatch.stop();

        if (1 == w)
        {
            display_result<T_integer>(numLoops.base_type_value() * numIterations.base_type_value(), stopwatch);
        }
    }

    return total;
}

template<
    typename    T_integer
,   typename    T_stopwatch
>
size_t
execute_b36(
    Warmups             numWarmups
,   Loops               numLoops
,   Iterations          numIterations
,   T_stopwatch&        stopwatch
,   T_integer const&    baseValue
)
{
    size_t total = 0;

    for (size_t w = numWarmups.base_type_value(); 0 != w; --w)
    {
        stopwatch.start();

        for (size_t i = 0; numLoops.base_type_value() != i; ++i)
        {
            for (size_t j = 0; numIterations.base_type_value() != j; ++j)
            {
                T_integer const     value   =   baseValue + static_cast<T_integer>(j);
                char                sz[21];
                char const* const   s = stlsoft::integer_to_base36_string(&sz[0], STLSOFT_NUM_ELEMENTS(sz), value);

                total += reinterpret_cast<uintptr_t>(s) & 0x0f;
            }
        }

        stopwatch.stop();

        if (1 == w)
        {
            display_result<T_integer>(numLoops.base_type_value() * numIterations.base_type_value(), stopwatch);
        }
    }

    return total;
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    STLSOFT_SUPPRESS_UNUSED(argc);
    STLSOFT_SUPPRESS_UNUSED(argv);

    stlsoft::std_chrono_hrc_stopwatch  stopwatch;

    size_t total = 0;

    perf_maybe_emit_groupgaps_banner(stdout);

    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "std::to_string() - base 0");
    fprintf(stdout, "std::to_string() - base 0\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

        total += execute_xtos<unsigned short>(warmups, loops, iterations, stopwatch, 0);
        total += execute_xtos<  signed short>(warmups, loops, iterations, stopwatch, 0);

        total += execute_xtos<unsigned int>(warmups, loops, iterations, stopwatch, 0);
        total += execute_xtos<  signed int>(warmups, loops, iterations, stopwatch, 0);

        total += execute_xtos<unsigned long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_xtos<  signed long>(warmups, loops, iterations, stopwatch, 0);

        total += execute_xtos<unsigned long long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_xtos<  signed long long>(warmups, loops, iterations, stopwatch, 0);
    }

    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "std::to_string() - base max() - N");
    fprintf(stdout, "std::to_string() - base max() - N\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

#define N           (500000)
        total += execute_xtos<unsigned int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);
        total += execute_xtos<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::min() - N);
        total += execute_xtos<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);

        total += execute_xtos<unsigned long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);
        total += execute_xtos<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::min() - N);
        total += execute_xtos<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);

        total += execute_xtos<unsigned long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
        total += execute_xtos<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::min() - N);
        total += execute_xtos<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
#undef N
    }


    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "snprintf() - base 0");
    fprintf(stdout, "snprintf() - base 0\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

        total += execute_printf<unsigned short>(warmups, loops, iterations, stopwatch, 0);
        total += execute_printf<  signed short>(warmups, loops, iterations, stopwatch, 0);

        total += execute_printf<unsigned int>(warmups, loops, iterations, stopwatch, 0);
        total += execute_printf<  signed int>(warmups, loops, iterations, stopwatch, 0);

        total += execute_printf<unsigned long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_printf<  signed long>(warmups, loops, iterations, stopwatch, 0);

        total += execute_printf<unsigned long long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_printf<  signed long long>(warmups, loops, iterations, stopwatch, 0);
    }

    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "snprintf() - base max() - N");
    fprintf(stdout, "snprintf() - base max() - N\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

#define N           (500000)
        total += execute_printf<unsigned int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);
        total += execute_printf<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::min() - N);
        total += execute_printf<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);

        total += execute_printf<unsigned long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);
        total += execute_printf<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::min() - N);
        total += execute_printf<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);

        total += execute_printf<unsigned long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
        total += execute_printf<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::min() - N);
        total += execute_printf<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
#undef N
    }


    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "integer_to_decimal_string() - base 0");
    fprintf(stdout, "integer_to_decimal_string() - base 0\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

        total += execute_dec<unsigned char>(warmups, loops, iterations, stopwatch, 0);
        total += execute_dec<  signed char>(warmups, loops, iterations, stopwatch, 0);

        total += execute_dec<unsigned short>(warmups, loops, iterations, stopwatch, 0);
        total += execute_dec<  signed short>(warmups, loops, iterations, stopwatch, 0);

        total += execute_dec<unsigned int>(warmups, loops, iterations, stopwatch, 0);
        total += execute_dec<  signed int>(warmups, loops, iterations, stopwatch, 0);

        total += execute_dec<unsigned long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_dec<  signed long>(warmups, loops, iterations, stopwatch, 0);

        total += execute_dec<unsigned long long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_dec<  signed long long>(warmups, loops, iterations, stopwatch, 0);
    }

    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "integer_to_decimal_string() - base max() - N");
    fprintf(stdout, "integer_to_decimal_string() - base max() - N\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

#define N           (500000)
        total += execute_dec<unsigned int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);
        total += execute_dec<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::min() - N);
        total += execute_dec<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);

        total += execute_dec<unsigned long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);
        total += execute_dec<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::min() - N);
        total += execute_dec<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);

        total += execute_dec<unsigned long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
        total += execute_dec<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::min() - N);
        total += execute_dec<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
#undef N
    }


    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "integer_to_octal_string() - base 0");
    fprintf(stdout, "integer_to_octal_string() - base 0\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

        total += execute_oct<unsigned char>(warmups, loops, iterations, stopwatch, 0);
        total += execute_oct<  signed char>(warmups, loops, iterations, stopwatch, 0);

        total += execute_oct<unsigned short>(warmups, loops, iterations, stopwatch, 0);
        total += execute_oct<  signed short>(warmups, loops, iterations, stopwatch, 0);

        total += execute_oct<unsigned int>(warmups, loops, iterations, stopwatch, 0);
        total += execute_oct<  signed int>(warmups, loops, iterations, stopwatch, 0);

        total += execute_oct<unsigned long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_oct<  signed long>(warmups, loops, iterations, stopwatch, 0);

        total += execute_oct<unsigned long long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_oct<  signed long long>(warmups, loops, iterations, stopwatch, 0);
    }

    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "integer_to_octal_string() - base max() - N");
    fprintf(stdout, "integer_to_octal_string() - base max() - N\n");


    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

#define N           (500000)
        total += execute_oct<unsigned int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);
        total += execute_oct<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::min() - N);
        total += execute_oct<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);

        total += execute_oct<unsigned long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);
        total += execute_oct<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::min() - N);
        total += execute_oct<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);

        total += execute_oct<unsigned long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
        total += execute_oct<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::min() - N);
        total += execute_oct<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
#undef N
    }

    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "integer_to_hexadecimal_string() - base 0");
    fprintf(stdout, "integer_to_hexadecimal_string() - base 0\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

        total += execute_hex<unsigned char>(warmups, loops, iterations, stopwatch, 0);
        total += execute_hex<  signed char>(warmups, loops, iterations, stopwatch, 0);

        total += execute_hex<unsigned short>(warmups, loops, iterations, stopwatch, 0);
        total += execute_hex<  signed short>(warmups, loops, iterations, stopwatch, 0);

        total += execute_hex<unsigned int>(warmups, loops, iterations, stopwatch, 0);
        total += execute_hex<  signed int>(warmups, loops, iterations, stopwatch, 0);

        total += execute_hex<unsigned long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_hex<  signed long>(warmups, loops, iterations, stopwatch, 0);

        total += execute_hex<unsigned long long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_hex<  signed long long>(warmups, loops, iterations, stopwatch, 0);
    }

    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "integer_to_hexadecimal_string() - base max() - N");
    fprintf(stdout, "integer_to_hexadecimal_string() - base max() - N\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

#define N           (500000)
        total += execute_hex<unsigned int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);
        total += execute_hex<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::min() - N);
        total += execute_hex<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);

        total += execute_hex<unsigned long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);
        total += execute_hex<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::min() - N);
        total += execute_hex<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);

        total += execute_hex<unsigned long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
        total += execute_hex<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::min() - N);
        total += execute_hex<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
#undef N
    }


    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "integer_to_base32_string() - base 0");
    fprintf(stdout, "integer_to_base32_string() - base 0\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

        total += execute_b32<unsigned char>(warmups, loops, iterations, stopwatch, 0);
        total += execute_b32<  signed char>(warmups, loops, iterations, stopwatch, 0);

        total += execute_b32<unsigned short>(warmups, loops, iterations, stopwatch, 0);
        total += execute_b32<  signed short>(warmups, loops, iterations, stopwatch, 0);

        total += execute_b32<unsigned int>(warmups, loops, iterations, stopwatch, 0);
        total += execute_b32<  signed int>(warmups, loops, iterations, stopwatch, 0);

        total += execute_b32<unsigned long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_b32<  signed long>(warmups, loops, iterations, stopwatch, 0);

        total += execute_b32<unsigned long long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_b32<  signed long long>(warmups, loops, iterations, stopwatch, 0);
    }

    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "integer_to_base32_string() - base max() - N");
    fprintf(stdout, "integer_to_base32_string() - base max() - N\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

#define N           (500000)
        total += execute_b32<unsigned int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);
        total += execute_b32<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::min() - N);
        total += execute_b32<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);

        total += execute_b32<unsigned long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);
        total += execute_b32<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::min() - N);
        total += execute_b32<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);

        total += execute_b32<unsigned long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
        total += execute_b32<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::min() - N);
        total += execute_b32<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
#undef N
    }


    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "integer_to_base36_string() - base 0");
    fprintf(stdout, "integer_to_base36_string() - base 0\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

        total += execute_b36<unsigned char>(warmups, loops, iterations, stopwatch, 0);
        total += execute_b36<  signed char>(warmups, loops, iterations, stopwatch, 0);

        total += execute_b36<unsigned short>(warmups, loops, iterations, stopwatch, 0);
        total += execute_b36<  signed short>(warmups, loops, iterations, stopwatch, 0);

        total += execute_b36<unsigned int>(warmups, loops, iterations, stopwatch, 0);
        total += execute_b36<  signed int>(warmups, loops, iterations, stopwatch, 0);

        total += execute_b36<unsigned long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_b36<  signed long>(warmups, loops, iterations, stopwatch, 0);

        total += execute_b36<unsigned long long>(warmups, loops, iterations, stopwatch, 0);
        total += execute_b36<  signed long long>(warmups, loops, iterations, stopwatch, 0);
    }

    /* Gap between API / base-family sections. */
    perf_maybe_emit_group_gap(stdout, "integer_to_base36_string() - base max() - N");
    fprintf(stdout, "integer_to_base36_string() - base max() - N\n");

    {
        Warmups     warmups(4);
        Loops       loops(100);
        Iterations  iterations(1000000);

#define N           (500000)
        total += execute_b36<unsigned int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);
        total += execute_b36<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::min() - N);
        total += execute_b36<  signed int>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned int>::max() - N);

        total += execute_b36<unsigned long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);
        total += execute_b36<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::min() - N);
        total += execute_b36<  signed long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long>::max() - N);

        total += execute_b36<unsigned long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
        total += execute_b36<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::min() - N);
        total += execute_b36<  signed long long>(warmups, loops, iterations, stopwatch, std::numeric_limits<unsigned long long>::max() - N);
#undef N
    }

    return 0 == total;
}


/* ///////////////////////////// end of file //////////////////////////// */

