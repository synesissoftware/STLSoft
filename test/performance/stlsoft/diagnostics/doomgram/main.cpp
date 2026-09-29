/* /////////////////////////////////////////////////////////////////////////
 * File:    doomgram/main.cpp
 *
 * Purpose: Perf-test for `stlsoft::doomgram<>`.
 *
 * Created: 11th December 2024
 * Updated: 29th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/diagnostics/doomgram.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* STLSoft header files */

#if __cplusplus >= 201103L
# include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>
#else
# include <platformstl/diagnostics/stopwatch.hpp>
#endif /* C++11+ */

/* Standard header files */

#include <functional>
#if __cplusplus >= 201103L
# include <list>
#endif
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

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

typedef std::vector<interval_t>                             intervals_t;
typedef std::vector<std::string>                            names_t;

using stlsoft::ss_size_t;

using stlsoft::doomgram;


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

    ss_size_t const NUM_ITERATIONS = 2000000000;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

template<
    ss_typename_param_k T_hg
>
std::pair<
    interval_t  // total_time_ns
,   ss_size_t   // anchoring_value - this to incline the optimiser to not elide the whole thing
>
test_(
    ss_size_t                   num_iterations
,   std::function<void (
        T_hg&       hg1
    ,   T_hg&       hg2
    )>                          init_fn
,   std::function<ss_size_t (
        ss_size_t   iteration
    ,   T_hg&       hg1
    ,   T_hg&       hg2
    )>                          timed_fn
)
{
    stopwatch_t sw;
    interval_t  interval        =   0;
    ss_size_t   anchoring_value =   0;

    for (int W = 2; W != 0; --W)
    {
        T_hg hg1;
        T_hg hg2;

        if (init_fn)
        {
            init_fn(hg1, hg2);
        }

        sw.start();

        for (ss_size_t i = 0; i != num_iterations; ++i)
        {
            anchoring_value += timed_fn(i, hg1, hg2);
        }

        sw.stop();

        interval = sw.get_nanoseconds();
    }

    return std::make_pair(interval, anchoring_value);
}

void
display_results(
    std::ostream&       stm
,   ss_size_t           num_iterations
,   char const*         ordering_label
,   char const*         test_name
,   std::pair<
        interval_t  // total_time_ns
    ,   ss_size_t   // anchoring_value
    > const&            r
)
{
    stm
        << '\t'
        << ordering_label << ": " << test_name
        << '\t'
        << num_iterations
        << '\t'
        << std::setw(12) << std::right << r.first
        << '\t'
        << std::setw(12) << std::setfill(' ') << std::right << std::fixed << std::setprecision(3) << (static_cast<double>(r.first) / num_iterations)
        << '\t'
        << std::setw(20) << std::right << r.second
        << std::endl;
}

template<
    ss_typename_param_k T_hg
>
std::pair<
    intervals_t // intervals
,   names_t     // names
>
run_tests(
)
{
    char const* const ordering_label = typeid(T_hg).name();

    intervals_t intervals;
    names_t     names;

    // ctor default
    {
        char const* const   TEST_NAME   =   "ctor (default)";

        std::pair<
            interval_t  // total_time_ns
        ,   ss_size_t   // anchoring_value
        > const r = test_<T_hg>(
            NUM_ITERATIONS
        ,   nullptr
        ,   [](ss_size_t iteration, T_hg& /*hg1*/, T_hg& /*hg2*/) {

            T_hg dg;

            return iteration;
        });

        display_results(std::cout, NUM_ITERATIONS, ordering_label, TEST_NAME, r);

        intervals.push_back(r.first);
        names.push_back(TEST_NAME);
    }

    // push (ns) (%100000)
    {
        char const* const   TEST_NAME   =   "push (ns) (%100000)";

        std::pair<
            interval_t  // total_time_ns
        ,   ss_size_t   // anchoring_value
        > const r = test_<T_hg>(
            NUM_ITERATIONS
        ,   nullptr
        ,   [](ss_size_t iteration, T_hg& /*hg1*/, T_hg& /*hg2*/) {

            T_hg dg;

            dg.push_event_time_ns(iteration % 100000);

            return iteration
                    + dg.event_count()
                    + dg.total_event_time_ns_raw()
                    + dg.num_events_in_1ns()
                    + dg.num_events_in_10ns()
                    + dg.num_events_in_100ns()
                    + dg.num_events_in_1us()
                    + dg.num_events_in_10us()
                    + dg.num_events_in_100us()
                    + dg.num_events_in_1ms()
                    + dg.num_events_in_10ms()
                    + dg.num_events_in_100ms()
                    + dg.num_events_in_1s()
                    + dg.num_events_in_10s()
                    + dg.num_events_ge_100s()
                    ;
        });

        display_results(std::cout, NUM_ITERATIONS, ordering_label, TEST_NAME, r);

        intervals.push_back(r.first);
        names.push_back(TEST_NAME);
    }

    // push (ns)
    {
        char const* const   TEST_NAME   =   "push (ns)";

        std::pair<
            interval_t  // total_time_ns
        ,   ss_size_t   // anchoring_value
        > const r = test_<T_hg>(
            NUM_ITERATIONS
        ,   nullptr
        ,   [](ss_size_t iteration, T_hg& /*hg1*/, T_hg& /*hg2*/) {

            T_hg dg;

            dg.push_event_time_ns(iteration);

            return iteration
                    + dg.event_count()
                    + dg.total_event_time_ns_raw()
                    + dg.num_events_in_1ns()
                    + dg.num_events_in_10ns()
                    + dg.num_events_in_100ns()
                    + dg.num_events_in_1us()
                    + dg.num_events_in_10us()
                    + dg.num_events_in_100us()
                    + dg.num_events_in_1ms()
                    + dg.num_events_in_10ms()
                    + dg.num_events_in_100ms()
                    + dg.num_events_in_1s()
                    + dg.num_events_in_10s()
                    + dg.num_events_ge_100s()
                    ;
        });

        display_results(std::cout, NUM_ITERATIONS, ordering_label, TEST_NAME, r);

        intervals.push_back(r.first);
        names.push_back(TEST_NAME);
    }

    // push (us)
    {
        char const* const   TEST_NAME   =   "push (us)";

        std::pair<
            interval_t  // total_time_ns
        ,   ss_size_t   // anchoring_value
        > const r = test_<T_hg>(
            NUM_ITERATIONS
        ,   nullptr
        ,   [](ss_size_t iteration, T_hg& /*hg1*/, T_hg& /*hg2*/) {

            T_hg dg;

            dg.push_event_time_us(iteration);

            return iteration
                    + dg.event_count()
                    + dg.total_event_time_ns_raw()
                    + dg.num_events_in_1ns()
                    + dg.num_events_in_10ns()
                    + dg.num_events_in_100ns()
                    + dg.num_events_in_1us()
                    + dg.num_events_in_10us()
                    + dg.num_events_in_100us()
                    + dg.num_events_in_1ms()
                    + dg.num_events_in_10ms()
                    + dg.num_events_in_100ms()
                    + dg.num_events_in_1s()
                    + dg.num_events_in_10s()
                    + dg.num_events_ge_100s()
                    ;
        });

        display_results(std::cout, NUM_ITERATIONS, ordering_label, TEST_NAME, r);

        intervals.push_back(r.first);
        names.push_back(TEST_NAME);
    }

    // push (ms)
    {
        char const* const   TEST_NAME   =   "push (ms)";

        std::pair<
            interval_t  // total_time_ns
        ,   ss_size_t   // anchoring_value
        > const r = test_<T_hg>(
            NUM_ITERATIONS
        ,   nullptr
        ,   [](ss_size_t iteration, T_hg& /*hg1*/, T_hg& /*hg2*/) {

            T_hg dg;

            dg.push_event_time_ms(iteration);

            return iteration
                    + dg.event_count()
                    + dg.total_event_time_ns_raw()
                    + dg.num_events_in_1ns()
                    + dg.num_events_in_10ns()
                    + dg.num_events_in_100ns()
                    + dg.num_events_in_1us()
                    + dg.num_events_in_10us()
                    + dg.num_events_in_100us()
                    + dg.num_events_in_1ms()
                    + dg.num_events_in_10ms()
                    + dg.num_events_in_100ms()
                    + dg.num_events_in_1s()
                    + dg.num_events_in_10s()
                    + dg.num_events_ge_100s()
                    ;
        });

        display_results(std::cout, NUM_ITERATIONS, ordering_label, TEST_NAME, r);

        intervals.push_back(r.first);
        names.push_back(TEST_NAME);
    }

    // push (s)
    {
        char const* const   TEST_NAME   =   "push (s)";

        std::pair<
            interval_t  // total_time_ns
        ,   ss_size_t   // anchoring_value
        > const r = test_<T_hg>(
            NUM_ITERATIONS
        ,   nullptr
        ,   [](ss_size_t iteration, T_hg& /*hg1*/, T_hg& /*hg2*/) {

            T_hg dg;

            dg.push_event_time_s(iteration);

            return iteration
                    + dg.event_count()
                    + dg.total_event_time_ns_raw()
                    + dg.num_events_in_1ns()
                    + dg.num_events_in_10ns()
                    + dg.num_events_in_100ns()
                    + dg.num_events_in_1us()
                    + dg.num_events_in_10us()
                    + dg.num_events_in_100us()
                    + dg.num_events_in_1ms()
                    + dg.num_events_in_10ms()
                    + dg.num_events_in_100ms()
                    + dg.num_events_in_1s()
                    + dg.num_events_in_10s()
                    + dg.num_events_ge_100s()
                    ;
        });

        display_results(std::cout, NUM_ITERATIONS, ordering_label, TEST_NAME, r);

        intervals.push_back(r.first);
        names.push_back(TEST_NAME);
    }

    return std::make_pair(intervals, names);
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int /* argc */, char* /* argv */[])
{
    // pipe to expand: `test.performance.stlsoft.doomgram | expand -t 8,64,80,96,112,128,160`

    std::cout << std::endl;
    intervals_t const intervals_o = run_tests<doomgram>().first;

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

