/* /////////////////////////////////////////////////////////////////////////
 * File:    test.performance.stlsoft.par_strip/main.cpp
 *
 * Purpose: Perf-test for `stlsoft::par_strip`.
 *
 * Created: 24th September 2026
 * Updated: 26th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/diagnostics/par_strip.hpp>
#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>

#include <iomanip>
#include <iostream>
#include <string>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

typedef stlsoft::std_chrono_hrc_stopwatch                   stopwatch_t;
typedef stopwatch_t::interval_type                          interval_t;

using stlsoft::ss_sint64_t;
using stlsoft::ss_size_t;
using stlsoft::par_strip_direction;

typedef stlsoft::par_strip<10, ss_sint64_t>                 par_strip_10_t;
typedef stlsoft::par_strip<10, double>                      par_strip_f64_t;


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

ss_size_t const NUM_ITERATIONS = 2000000;

} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main()
{
    stopwatch_t    sw;
    char            buffer[64] = { 0 };

    {
        sw.start();

        ss_size_t anchor = 0;

        for (ss_size_t i = 0; i != NUM_ITERATIONS; ++i)
        {
            par_strip_10_t const   ps(-2, +5, par_strip_direction::backward, 100, 100 + static_cast<ss_sint64_t>(i % 1000));
            ss_size_t const        n = ps.write_strip(buffer, sizeof(buffer));

            anchor += n;
            anchor += static_cast<ss_size_t>(static_cast<unsigned char>(buffer[0]));
        }

        sw.stop();

        interval_t const elapsed = sw.get_nanoseconds();

        std::cout
            << "write_strip sint64"
            << '\t'
            << NUM_ITERATIONS
            << '\t'
            << elapsed
            << '\t'
            << std::fixed << std::setprecision(3) << (static_cast<double>(elapsed) / NUM_ITERATIONS)
            << '\t'
            << anchor
            << std::endl;
    }

    {
        sw.start();

        ss_size_t anchor = 0;

        for (ss_size_t i = 0; i != NUM_ITERATIONS; ++i)
        {
            par_strip_f64_t const  ps(-2, +5, par_strip_direction::forward, 100.0, 100.0 + static_cast<double>(i % 1000));
            std::string const      strip = ps.to_strip();

            anchor += strip.size();
        }

        sw.stop();

        interval_t const elapsed = sw.get_nanoseconds();

        std::cout
            << "to_strip double"
            << '\t'
            << NUM_ITERATIONS
            << '\t'
            << elapsed
            << '\t'
            << std::fixed << std::setprecision(3) << (static_cast<double>(elapsed) / NUM_ITERATIONS)
            << '\t'
            << anchor
            << std::endl;
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

