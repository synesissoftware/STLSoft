/* /////////////////////////////////////////////////////////////////////////
 * File:    stopwatch/main.cpp
 *
 * Purpose: Perf-test for stopwatch types.
 *
 * Created: 15th March 2024
 * Updated: 29th September 2026
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

#include <platformstl/diagnostics/stopwatch.hpp>
#include <platformstl/diagnostics/processtimes_stopwatch.hpp>
#include <platformstl/synch/sleep_functions.h>
#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>

#include <iomanip>
#include <iostream>
#include <tuple>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

using stlsoft::ss_size_t;
using stlsoft::ss_uint_t;
typedef platformstl::stopwatch::interval_type               interval_t;


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

/// Evaluates cost of 1-start and N-stop calls
///
/// @tparam T_sw Type of stopwatch type to be evaluated
///
/// @param num_iterations Number of iterations
///
/// @return T.B.C.
template<
    ss_typename_param_k T_sw
>
std::pair<
    interval_t  // total_time_ns
,   ss_size_t   // anchoring_value - this to incline the optimiser to not elide the whole thing
>
test_start_stop_(
    ss_size_t   num_iterations
)
{
    platformstl::stopwatch  sw;
    interval_t              interval        =   0;
    ss_size_t               anchoring_value =   0;

    for (int W = 2; W != 0; --W)
    {
        sw.start();

        {
            T_sw t;

            t.start();

            for (ss_size_t i = 0; i != num_iterations; ++i)
            {
                t.stop();
            }

            anchoring_value += t.get_seconds();
        }

        sw.stop();

        interval = sw.get_nanoseconds();
    }

    return std::make_pair(interval, anchoring_value);
}

/// Evaluates cost of 1-start, 1-stop, N-pause, and N-unpause calls
///
/// @tparam T_sw Type of stopwatch type to be evaluated
///
/// @param num_iterations Number of iterations
///
/// @return T.B.C.
template<
    ss_typename_param_k T_sw
>
std::pair<
    interval_t  // total_time_ns
,   ss_size_t   // anchoring_value - this to incline the optimiser to not elide the whole thing
>
test_pause_unpause_(
    ss_size_t   num_iterations
)
{
    platformstl::stopwatch  sw;
    interval_t              interval        =   0;
    ss_size_t               anchoring_value =   0;

    for (int W = 2; W != 0; --W)
    {
        sw.start();

        {
            T_sw t;

            t.start();

            for (ss_size_t i = 0; i != num_iterations; ++i)
            {
                t.pause();
                t.unpause();
            }

            t.stop();

            anchoring_value += t.get_seconds();
        }

        sw.stop();

        interval = sw.get_nanoseconds();
    }

    return std::make_pair(interval, anchoring_value);
}

/// Evaluates cost of 1-start, 1-stop, N-pause, and N-unpause calls
///
/// @tparam T_sw Type of stopwatch type to be evaluated
///
/// @param num_iterations Number of iterations
/// @param delay_us Pause/unpause delay (in microseconds)
///
/// @return T.B.C.
template<
    ss_typename_param_k T_sw
>
std::tuple<
    interval_t  // total_elapsed_time_ns
,   interval_t  // total_measured_time_ns
,   ss_size_t   // anchoring_value - this to incline the optimiser to not elide the whole thing
>
test_pause_unpause_around_delay_(
    ss_size_t   num_iterations
,   ss_uint_t   delay_us
)
{
    platformstl::stopwatch  sw;
    interval_t              total_elapsed_time_ns   =   0;
    interval_t              total_measured_time_ns  =   0;
    ss_size_t               anchoring_value         =   0;

    for (int W = 2; W != 0; --W)
    {
        sw.start();

        {
            T_sw t;

            t.start();

            for (ss_size_t i = 0; i != num_iterations; ++i)
            {
                t.pause();

                platformstl::micro_sleep(delay_us);

                t.unpause();
            }

            t.stop();

            anchoring_value += t.get_seconds();
            total_measured_time_ns = t.get_nanoseconds();
        }

        sw.stop();

        total_elapsed_time_ns = sw.get_nanoseconds();
    }

    return std::make_tuple(
        total_elapsed_time_ns
    ,   total_measured_time_ns
    ,   anchoring_value
    );
}


void
display_results(
    std::ostream&       stm
,   ss_size_t           num_iterations
,   char const*         type_name
,   std::tuple<
        interval_t  // total_elapsed_time_ns
    ,   interval_t  // total_measured_time_ns
    ,   ss_size_t   // anchoring_value - this to incline the optimiser to not elide the whole thing
    > const&            r
)
{
    stm
        << '\t'
        << type_name
        << '\t'
        << num_iterations
        << '\t'
        << std::setw(12) << std::right << std::get<0>(r)
        << '\t'
        << std::setw(12) << std::setfill(' ') << std::right << std::fixed << std::setprecision(3) << (static_cast<double>(std::get<0>(r)) / num_iterations)
        << '\t'
        << std::get<1>(r)
        << '\t'
        << std::setw(12) << std::setfill(' ') << std::right << std::fixed << std::setprecision(3) << (static_cast<double>(std::get<1>(r)) / num_iterations)
        << '\t'
        << std::get<2>(r)
        << std::endl;
}


void
display_results(
    std::ostream&       stm
,   ss_size_t           num_iterations
,   char const*         type_name
,   std::pair<
        interval_t  // total_time_ns
    ,   ss_size_t   // anchoring_value
    > const&            r
)
{
    stm
        << '\t'
        << type_name
        << '\t'
        << num_iterations
        << '\t'
        << std::setw(12) << std::right << r.first
        << '\t'
        << std::setw(12) << std::setfill(' ') << std::right << std::fixed << std::setprecision(3) << (static_cast<double>(r.first) / num_iterations)
        << '\t'
        << '\t'
        << '\t'
        << r.second
        << std::endl;
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int /* argc */, char* /* argv */[])
{
    ss_size_t const NUM_ITERATIONS  =   1000000;

#define DEFINE_TYPE_AND_NAME(t)                             char const* const type_name = #t; typedef t sw_t

    std::cout
        << '\t'
        << "type"
        << '\t'
        << "#iterations"
        << '\t'
        << "elapsed (ns)"
        << '\t'
        << "elps/iter (ns)"
        << '\t'
        << "measured (ns)"
        << '\t'
        << "msrd/iter (ns)"
        << '\t'
        << "anchor value"
        << std::endl;


    // start-stop
    {
        std::cout << "`start()` - `stop()`(cost):" << std::endl;

        {
            DEFINE_TYPE_AND_NAME(platformstl::stopwatch);

            std::pair<
                interval_t  // total_time_ns
            ,   ss_size_t   // anchoring_value
            > const r = test_start_stop_<sw_t>(NUM_ITERATIONS);

            display_results(std::cout, NUM_ITERATIONS, type_name, r);
        }


        {
            DEFINE_TYPE_AND_NAME(platformstl::processtimes_stopwatch);

            std::pair<
                interval_t  // total_time_ns
            ,   ss_size_t   // anchoring_value
            > const r = test_start_stop_<sw_t>(NUM_ITERATIONS);

            display_results(std::cout, NUM_ITERATIONS, type_name, r);
        }


        {
            DEFINE_TYPE_AND_NAME(stlsoft::std_chrono_hrc_stopwatch);

            std::pair<
                interval_t  // total_time_ns
            ,   ss_size_t   // anchoring_value
            > const r = test_start_stop_<sw_t>(NUM_ITERATIONS);

            display_results(std::cout, NUM_ITERATIONS, type_name, r);
        }
    }

    // pause-unpause
    {
        std::cout << "`pause()` - `unpause()` (cost):" << std::endl;

        {
            DEFINE_TYPE_AND_NAME(platformstl::stopwatch);

            std::pair<
                interval_t  // total_time_ns
            ,   ss_size_t   // anchoring_value
            > const r = test_pause_unpause_<sw_t>(NUM_ITERATIONS);

            display_results(std::cout, NUM_ITERATIONS, type_name, r);
        }


        {
            DEFINE_TYPE_AND_NAME(stlsoft::std_chrono_hrc_stopwatch);

            std::pair<
                interval_t  // total_time_ns
            ,   ss_size_t   // anchoring_value
            > const r = test_pause_unpause_<sw_t>(NUM_ITERATIONS);

            display_results(std::cout, NUM_ITERATIONS, type_name, r);
        }
    }

    // pause-unpause (around delay)
    {
        std::cout << "`pause()` - `unpause()` (around delay; delay=1000us):" << std::endl;

        ss_size_t const num_iterations  =   NUM_ITERATIONS / 10000;
        ss_uint_t const delay_us        =   499 + 0;

        {
            DEFINE_TYPE_AND_NAME(platformstl::stopwatch);

            std::tuple<
                interval_t  // total_elapsed_time_ns
            ,   interval_t  // total_measured_time_ns
            ,   ss_size_t   // anchoring_value - this to incline the optimiser to not elide the whole thing
            > const r = test_pause_unpause_around_delay_<sw_t>(num_iterations, delay_us);

            display_results(std::cout, num_iterations, type_name, r);
        }


        {
            DEFINE_TYPE_AND_NAME(stlsoft::std_chrono_hrc_stopwatch);

            std::tuple<
                interval_t  // total_elapsed_time_ns
            ,   interval_t  // total_measured_time_ns
            ,   ss_size_t   // anchoring_value - this to incline the optimiser to not elide the whole thing
            > const r = test_pause_unpause_around_delay_<sw_t>(num_iterations, delay_us);

            display_results(std::cout, num_iterations, type_name, r);
        }
    }


    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

