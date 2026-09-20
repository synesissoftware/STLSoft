/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.diagnostics.doomgram/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::doomgram`.
 *
 * Created: 13th May 2013
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* ///////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/diagnostics/doomgram.hpp>
#include <stlsoft/diagnostics/gram_utils.hpp>

/* ///////////////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <numeric>
#include <stdexcept>
#include <string>
#if __cplusplus >= 201103L
# include <type_traits>
#endif

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_doomgram_DEFAULT_CONSTRUCT();
    static void TEST_doomgram_SINGLE_TIMING_EVENT();
    static void TEST_doomgram_ZERO_TIME_EVENTS();
    static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_1();
    static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_2();
    static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_3();
    static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_4();
    static void TEST_doomgram_SEVERAL_DISTINCT_TIMINGS();
    static void TEST_doomgram_SEVERAL_INTERSECTING_TIMINGS();
    static void TEST_doomgram_MANY_CUMULATIVE_TIMINGS();
    static void TEST_doomgram_OVERFLOW_BY_SECONDS();
    static void TEST_doomgram_OVERFLOW_BY_MICROSECONDS();

    static void TEST_calc_doom_1();

    static void TEST_UNSIGNED_OVERFLOW();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.diagnostics.doomgram", verbosity))
    {
        XTESTS_RUN_CASE(TEST_doomgram_DEFAULT_CONSTRUCT);
        XTESTS_RUN_CASE(TEST_doomgram_SINGLE_TIMING_EVENT);
        XTESTS_RUN_CASE(TEST_doomgram_ZERO_TIME_EVENTS);
        XTESTS_RUN_CASE(TEST_doomgram_UNIFORM_SPREAD_TIMINGS_1);
        XTESTS_RUN_CASE(TEST_doomgram_UNIFORM_SPREAD_TIMINGS_2);
        XTESTS_RUN_CASE(TEST_doomgram_UNIFORM_SPREAD_TIMINGS_3);
        XTESTS_RUN_CASE(TEST_doomgram_UNIFORM_SPREAD_TIMINGS_4);
        XTESTS_RUN_CASE(TEST_doomgram_SEVERAL_DISTINCT_TIMINGS);
        XTESTS_RUN_CASE(TEST_doomgram_SEVERAL_INTERSECTING_TIMINGS);
        XTESTS_RUN_CASE(TEST_doomgram_MANY_CUMULATIVE_TIMINGS);
        XTESTS_RUN_CASE(TEST_doomgram_OVERFLOW_BY_SECONDS);
        XTESTS_RUN_CASE(TEST_doomgram_OVERFLOW_BY_MICROSECONDS);

        XTESTS_RUN_CASE(TEST_calc_doom_1);

        XTESTS_RUN_CASE(TEST_UNSIGNED_OVERFLOW);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {


static void TEST_doomgram_DEFAULT_CONSTRUCT()
{
    stlsoft::doomgram       dg;
    stlsoft::ss_uint64_t    total_event_time_ns;
    stlsoft::ss_uint64_t    min_event_time_ns;
    stlsoft::ss_uint64_t    max_event_time_ns;

    TEST_BOOLEAN_FALSE(dg.has_overflowed());

    TEST_INT_EQ(0, dg.event_count());
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(ss_nullptr_k));
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(&total_event_time_ns));
    TEST_INT_EQ(0u, total_event_time_ns);
    TEST_INT_EQ(0u, dg.total_event_time_ns_raw());
    TEST_BOOLEAN_FALSE(dg.try_get_min_event_time_ns(&min_event_time_ns));
    TEST_BOOLEAN_FALSE(dg.try_get_max_event_time_ns(&max_event_time_ns));
    TEST_INT_EQ(0, dg.num_events_in_1ns());
    TEST_INT_EQ(0, dg.num_events_in_10ns());
    TEST_INT_EQ(0, dg.num_events_in_100ns());
    TEST_INT_EQ(0, dg.num_events_in_1us());
    TEST_INT_EQ(0, dg.num_events_in_10us());
    TEST_INT_EQ(0, dg.num_events_in_100us());
    TEST_INT_EQ(0, dg.num_events_in_1ms());
    TEST_INT_EQ(0, dg.num_events_in_10ms());
    TEST_INT_EQ(0, dg.num_events_in_100ms());
    TEST_INT_EQ(0, dg.num_events_in_1s());
    TEST_INT_EQ(0, dg.num_events_in_10s());
    TEST_INT_EQ(0, dg.num_events_ge_100s());

    {
        char    strip[12];

        stlsoft::gram_to_strip(dg, &strip);

        TEST_MS_EQ_N("____________", strip, 12);
    }
}

static void TEST_doomgram_SINGLE_TIMING_EVENT()
{
    stlsoft::doomgram       dg;
    stlsoft::ss_uint64_t    total_event_time_ns;
    stlsoft::ss_uint64_t    min_event_time_ns;
    stlsoft::ss_uint64_t    max_event_time_ns;

    dg.push_event_time_ms(13);

    TEST_BOOLEAN_FALSE(dg.has_overflowed());

    TEST_INT_EQ(1, dg.event_count());
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(ss_nullptr_k));
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(&total_event_time_ns));
    TEST_INT_EQ(13000000u, total_event_time_ns);
    TEST_INT_EQ(13000000u, dg.total_event_time_ns_raw());
    TEST_BOOLEAN_TRUE(dg.try_get_min_event_time_ns(&min_event_time_ns));
    TEST_INT_EQ(13000000, min_event_time_ns);
    TEST_BOOLEAN_TRUE(dg.try_get_max_event_time_ns(&max_event_time_ns));
    TEST_INT_EQ(13000000u, max_event_time_ns);
    TEST_INT_EQ(0, dg.num_events_in_1ns());
    TEST_INT_EQ(0, dg.num_events_in_10ns());
    TEST_INT_EQ(0, dg.num_events_in_100ns());
    TEST_INT_EQ(0, dg.num_events_in_1us());
    TEST_INT_EQ(0, dg.num_events_in_10us());
    TEST_INT_EQ(0, dg.num_events_in_100us());
    TEST_INT_EQ(0, dg.num_events_in_1ms());
    TEST_INT_EQ(1, dg.num_events_in_10ms());
    TEST_INT_EQ(0, dg.num_events_in_100ms());
    TEST_INT_EQ(0, dg.num_events_in_1s());
    TEST_INT_EQ(0, dg.num_events_in_10s());
    TEST_INT_EQ(0, dg.num_events_ge_100s());

    {
        char    strip[12];

        stlsoft::gram_to_strip(dg, &strip);

        TEST_MS_EQ_N("_______a____", strip, 12);
    }
}

static void TEST_doomgram_ZERO_TIME_EVENTS()
{
    stlsoft::doomgram       dg;
    stlsoft::ss_uint64_t    total_event_time_ns;
    stlsoft::ss_uint64_t    min_event_time_ns;
    stlsoft::ss_uint64_t    max_event_time_ns;

    dg.push_event_time_ns(0);
    dg.push_event_time_us(0);
    dg.push_event_time_ms(0);
    dg.push_event_time_s(0);

    TEST_BOOLEAN_FALSE(dg.has_overflowed());

    TEST_INT_EQ(4, dg.event_count());
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(ss_nullptr_k));
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(&total_event_time_ns));
    TEST_INT_EQ(0u, total_event_time_ns);
    TEST_INT_EQ(0u, dg.total_event_time_ns_raw());
    TEST_BOOLEAN_TRUE(dg.try_get_min_event_time_ns(&min_event_time_ns));
    TEST_INT_EQ(0, min_event_time_ns);
    TEST_BOOLEAN_TRUE(dg.try_get_max_event_time_ns(&max_event_time_ns));
    TEST_INT_EQ(0u, max_event_time_ns);
    TEST_INT_EQ(0, dg.num_events_in_1ns());
    TEST_INT_EQ(0, dg.num_events_in_10ns());
    TEST_INT_EQ(0, dg.num_events_in_100ns());
    TEST_INT_EQ(0, dg.num_events_in_1us());
    TEST_INT_EQ(0, dg.num_events_in_10us());
    TEST_INT_EQ(0, dg.num_events_in_100us());
    TEST_INT_EQ(0, dg.num_events_in_1ms());
    TEST_INT_EQ(0, dg.num_events_in_10ms());
    TEST_INT_EQ(0, dg.num_events_in_100ms());
    TEST_INT_EQ(0, dg.num_events_in_1s());
    TEST_INT_EQ(0, dg.num_events_in_10s());
    TEST_INT_EQ(0, dg.num_events_ge_100s());

    {
        char    strip[12];

        stlsoft::gram_to_strip(dg, &strip);

        TEST_MS_EQ_N("____________", strip, 12);
    }
}

static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_1()
{
    stlsoft::doomgram       dg;
    stlsoft::ss_uint64_t    total_event_time_ns;
    stlsoft::ss_uint64_t    min_event_time_ns;
    stlsoft::ss_uint64_t    max_event_time_ns;

    dg.push_event_time_ns(  9);
    dg.push_event_time_ns( 80);
    dg.push_event_time_ns(700);
    dg.push_event_time_us(  6);
    dg.push_event_time_us( 50);
    dg.push_event_time_us(400);
    dg.push_event_time_ms(  3);
    dg.push_event_time_ms( 20);
    dg.push_event_time_ms(100);
    dg.push_event_time_s(   9);
    dg.push_event_time_s(  80);
    dg.push_event_time_s( 700);

    TEST_BOOLEAN_FALSE(dg.has_overflowed());

    TEST_INT_EQ(12, dg.event_count());
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(ss_nullptr_k));
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(&total_event_time_ns));
    TEST_INT_EQ(789123456789u, total_event_time_ns);
    TEST_INT_EQ(789123456789u, dg.total_event_time_ns_raw());
    TEST_BOOLEAN_TRUE(dg.try_get_min_event_time_ns(&min_event_time_ns));
    TEST_INT_EQ(9, min_event_time_ns);
    TEST_BOOLEAN_TRUE(dg.try_get_max_event_time_ns(&max_event_time_ns));
    TEST_INT_EQ(700000000000u, max_event_time_ns);
    TEST_INT_EQ(1, dg.num_events_in_1ns());
    TEST_INT_EQ(1, dg.num_events_in_10ns());
    TEST_INT_EQ(1, dg.num_events_in_100ns());
    TEST_INT_EQ(1, dg.num_events_in_1us());
    TEST_INT_EQ(1, dg.num_events_in_10us());
    TEST_INT_EQ(1, dg.num_events_in_100us());
    TEST_INT_EQ(1, dg.num_events_in_1ms());
    TEST_INT_EQ(1, dg.num_events_in_10ms());
    TEST_INT_EQ(1, dg.num_events_in_100ms());
    TEST_INT_EQ(1, dg.num_events_in_1s());
    TEST_INT_EQ(1, dg.num_events_in_10s());
    TEST_INT_EQ(1, dg.num_events_ge_100s());

    {
        char    strip[12];

        stlsoft::gram_to_strip(dg, &strip);

        TEST_MS_EQ_N("aaaaaaaaaaaa", strip, 12);
    }
}

static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_2()
{
    stlsoft::doomgram       dg;
    stlsoft::ss_uint64_t    total_event_time_ns;
    stlsoft::ss_uint64_t    min_event_time_ns;
    stlsoft::ss_uint64_t    max_event_time_ns;

    dg.push_event_time_ns(     9);
    dg.push_event_time_ns(    80);
    dg.push_event_time_ns(   700);
    dg.push_event_time_ns(  6000);
    dg.push_event_time_ns( 50000);
    dg.push_event_time_ns(400000);
    dg.push_event_time_ms(     3);
    dg.push_event_time_ms(    20);
    dg.push_event_time_ms(   100);
    dg.push_event_time_ms(  9000);
    dg.push_event_time_ms( 80000);
    dg.push_event_time_ms(700000);

    TEST_BOOLEAN_FALSE(dg.has_overflowed());

    TEST_INT_EQ(12, dg.event_count());
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(ss_nullptr_k));
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(&total_event_time_ns));
    TEST_INT_EQ(789123456789u, total_event_time_ns);
    TEST_INT_EQ(789123456789u, dg.total_event_time_ns_raw());
    TEST_BOOLEAN_TRUE(dg.try_get_min_event_time_ns(&min_event_time_ns));
    TEST_INT_EQ(9, min_event_time_ns);
    TEST_BOOLEAN_TRUE(dg.try_get_max_event_time_ns(&max_event_time_ns));
    TEST_INT_EQ(700000000000u, max_event_time_ns);
    TEST_INT_EQ(1, dg.num_events_in_1ns());
    TEST_INT_EQ(1, dg.num_events_in_10ns());
    TEST_INT_EQ(1, dg.num_events_in_100ns());
    TEST_INT_EQ(1, dg.num_events_in_1us());
    TEST_INT_EQ(1, dg.num_events_in_10us());
    TEST_INT_EQ(1, dg.num_events_in_100us());
    TEST_INT_EQ(1, dg.num_events_in_1ms());
    TEST_INT_EQ(1, dg.num_events_in_10ms());
    TEST_INT_EQ(1, dg.num_events_in_100ms());
    TEST_INT_EQ(1, dg.num_events_in_1s());
    TEST_INT_EQ(1, dg.num_events_in_10s());
    TEST_INT_EQ(1, dg.num_events_ge_100s());

    {
        char    strip[12];

        stlsoft::gram_to_strip(dg, &strip);

        TEST_MS_EQ_N("aaaaaaaaaaaa", strip, 12);
    }
}

static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_3()
{
    stlsoft::doomgram       dg;
    stlsoft::ss_uint64_t    total_event_time_ns;
    stlsoft::ss_uint64_t    min_event_time_ns;
    stlsoft::ss_uint64_t    max_event_time_ns;

    dg.push_event_time_ns(           9);
    dg.push_event_time_ns(          80);
    dg.push_event_time_ns(         700);
    dg.push_event_time_ns(        6000);
    dg.push_event_time_ns(       50000);
    dg.push_event_time_ns(      400000);
    dg.push_event_time_ns(     3000000);
    dg.push_event_time_ns(    20000000);
    dg.push_event_time_ns(   100000000);
    dg.push_event_time_ns(  9000000000);
    dg.push_event_time_ns( 80000000000);
    dg.push_event_time_ns(700000000000);

    TEST_BOOLEAN_FALSE(dg.has_overflowed());

    TEST_INT_EQ(12, dg.event_count());
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(ss_nullptr_k));
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(&total_event_time_ns));
    TEST_INT_EQ(789123456789u, total_event_time_ns);
    TEST_INT_EQ(789123456789u, dg.total_event_time_ns_raw());
    TEST_BOOLEAN_TRUE(dg.try_get_min_event_time_ns(&min_event_time_ns));
    TEST_INT_EQ(9, min_event_time_ns);
    TEST_BOOLEAN_TRUE(dg.try_get_max_event_time_ns(&max_event_time_ns));
    TEST_INT_EQ(700000000000u, max_event_time_ns);
    TEST_INT_EQ(1, dg.num_events_in_1ns());
    TEST_INT_EQ(1, dg.num_events_in_10ns());
    TEST_INT_EQ(1, dg.num_events_in_100ns());
    TEST_INT_EQ(1, dg.num_events_in_1us());
    TEST_INT_EQ(1, dg.num_events_in_10us());
    TEST_INT_EQ(1, dg.num_events_in_100us());
    TEST_INT_EQ(1, dg.num_events_in_1ms());
    TEST_INT_EQ(1, dg.num_events_in_10ms());
    TEST_INT_EQ(1, dg.num_events_in_100ms());
    TEST_INT_EQ(1, dg.num_events_in_1s());
    TEST_INT_EQ(1, dg.num_events_in_10s());
    TEST_INT_EQ(1, dg.num_events_ge_100s());

    {
        char    strip[12];

        stlsoft::gram_to_strip(dg, &strip);

        TEST_MS_EQ_N("aaaaaaaaaaaa", strip, 12);
    }
}

static void TEST_doomgram_UNIFORM_SPREAD_TIMINGS_4()
{
    stlsoft::doomgram       dg;
    stlsoft::ss_uint64_t    total_event_time_ns;
    stlsoft::ss_uint64_t    min_event_time_ns;
    stlsoft::ss_uint64_t    max_event_time_ns;

    dg.push_event_time_us(        6);
    dg.push_event_time_us(       50);
    dg.push_event_time_us(      400);
    dg.push_event_time_us(     3000);
    dg.push_event_time_us(    20000);
    dg.push_event_time_us(   100000);
    dg.push_event_time_us(  9000000);
    dg.push_event_time_us( 80000000);
    dg.push_event_time_us(700000000);

    TEST_BOOLEAN_FALSE(dg.has_overflowed());

    TEST_INT_EQ(9, dg.event_count());
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(ss_nullptr_k));
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(&total_event_time_ns));
    TEST_INT_EQ(789123456000u, total_event_time_ns);
    TEST_INT_EQ(789123456000u, dg.total_event_time_ns_raw());
    TEST_BOOLEAN_TRUE(dg.try_get_min_event_time_ns(&min_event_time_ns));
    TEST_INT_EQ(6000, min_event_time_ns);
    TEST_BOOLEAN_TRUE(dg.try_get_max_event_time_ns(&max_event_time_ns));
    TEST_INT_EQ(700000000000u, max_event_time_ns);
    TEST_INT_EQ(0, dg.num_events_in_1ns());
    TEST_INT_EQ(0, dg.num_events_in_10ns());
    TEST_INT_EQ(0, dg.num_events_in_100ns());
    TEST_INT_EQ(1, dg.num_events_in_1us());
    TEST_INT_EQ(1, dg.num_events_in_10us());
    TEST_INT_EQ(1, dg.num_events_in_100us());
    TEST_INT_EQ(1, dg.num_events_in_1ms());
    TEST_INT_EQ(1, dg.num_events_in_10ms());
    TEST_INT_EQ(1, dg.num_events_in_100ms());
    TEST_INT_EQ(1, dg.num_events_in_1s());
    TEST_INT_EQ(1, dg.num_events_in_10s());
    TEST_INT_EQ(1, dg.num_events_ge_100s());

    {
        char    strip[12];

        stlsoft::gram_to_strip(dg, &strip);

        TEST_MS_EQ_N("___aaaaaaaaa", strip, 12);
    }
}

static void TEST_doomgram_SEVERAL_DISTINCT_TIMINGS()
{
    stlsoft::doomgram       dg;
    stlsoft::ss_uint64_t    total_event_time_ns;
    stlsoft::ss_uint64_t    min_event_time_ns;
    stlsoft::ss_uint64_t    max_event_time_ns;

    dg.push_event_time_ns(23);
    dg.push_event_time_ns(10);
    dg.push_event_time_us(7);
    dg.push_event_time_us(7);
    dg.push_event_time_us(89);
    dg.push_event_time_ms(248);
    dg.push_event_time_s(5);
    dg.push_event_time_s(309);

    TEST_BOOLEAN_FALSE(dg.has_overflowed());

    TEST_INT_EQ(8, dg.event_count());
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(ss_nullptr_k));
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(&total_event_time_ns));
    TEST_INT_EQ(314248103033u, total_event_time_ns);
    TEST_INT_EQ(314248103033u, dg.total_event_time_ns_raw());
    TEST_BOOLEAN_TRUE(dg.try_get_min_event_time_ns(&min_event_time_ns));
    TEST_INT_EQ(10, min_event_time_ns);
    TEST_BOOLEAN_TRUE(dg.try_get_max_event_time_ns(&max_event_time_ns));
    TEST_INT_EQ(309000000000u, max_event_time_ns);
    TEST_INT_EQ(0, dg.num_events_in_1ns());
    TEST_INT_EQ(2, dg.num_events_in_10ns());
    TEST_INT_EQ(0, dg.num_events_in_100ns());
    TEST_INT_EQ(2, dg.num_events_in_1us());
    TEST_INT_EQ(1, dg.num_events_in_10us());
    TEST_INT_EQ(0, dg.num_events_in_100us());
    TEST_INT_EQ(0, dg.num_events_in_1ms());
    TEST_INT_EQ(0, dg.num_events_in_10ms());
    TEST_INT_EQ(1, dg.num_events_in_100ms());
    TEST_INT_EQ(1, dg.num_events_in_1s());
    TEST_INT_EQ(0, dg.num_events_in_10s());
    TEST_INT_EQ(1, dg.num_events_ge_100s());

    {
        char    strip[12];

        stlsoft::gram_to_strip(dg, &strip);

        TEST_MS_EQ_N("_a_aa___aa_a", strip, 12);
    }
}

static void TEST_doomgram_SEVERAL_INTERSECTING_TIMINGS()
{
    stlsoft::doomgram       dg;
    stlsoft::ss_uint64_t    total_event_time_ns;
    stlsoft::ss_uint64_t    min_event_time_ns;
    stlsoft::ss_uint64_t    max_event_time_ns;

    dg.push_event_time_ns(11);
    dg.push_event_time_ns(19);
    dg.push_event_time_ns(19);
    dg.push_event_time_us(7);
    dg.push_event_time_us(7);
    dg.push_event_time_us(89);
    dg.push_event_time_ms(248);
    dg.push_event_time_ms(4321);
    dg.push_event_time_s(5);
    dg.push_event_time_s(309);

    TEST_BOOLEAN_FALSE(dg.has_overflowed());

    TEST_INT_EQ(10, dg.event_count());
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(ss_nullptr_k));
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(&total_event_time_ns));
    TEST_INT_EQ(318569103049u, total_event_time_ns);
    TEST_INT_EQ(318569103049u, dg.total_event_time_ns_raw());
    TEST_BOOLEAN_TRUE(dg.try_get_min_event_time_ns(&min_event_time_ns));
    TEST_INT_EQ(11, min_event_time_ns);
    TEST_BOOLEAN_TRUE(dg.try_get_max_event_time_ns(&max_event_time_ns));
    TEST_INT_EQ(309000000000u, max_event_time_ns);
    TEST_INT_EQ(0, dg.num_events_in_1ns());
    TEST_INT_EQ(3, dg.num_events_in_10ns());
    TEST_INT_EQ(0, dg.num_events_in_100ns());
    TEST_INT_EQ(2, dg.num_events_in_1us());
    TEST_INT_EQ(1, dg.num_events_in_10us());
    TEST_INT_EQ(0, dg.num_events_in_100us());
    TEST_INT_EQ(0, dg.num_events_in_1ms());
    TEST_INT_EQ(0, dg.num_events_in_10ms());
    TEST_INT_EQ(1, dg.num_events_in_100ms());
    TEST_INT_EQ(2, dg.num_events_in_1s());
    TEST_INT_EQ(0, dg.num_events_in_10s());
    TEST_INT_EQ(1, dg.num_events_ge_100s());

    {
        char    strip[12];

        stlsoft::gram_to_strip(dg, &strip);

        TEST_MS_EQ_N("_a_aa___aa_a", strip, 12);
    }
}

static void TEST_doomgram_MANY_CUMULATIVE_TIMINGS()
{
    stlsoft::doomgram       dg;
    stlsoft::ss_uint64_t    total_event_time_ns;
    stlsoft::ss_uint64_t    min_event_time_ns;
    stlsoft::ss_uint64_t    max_event_time_ns;

    { for (int i = 0; 10000 != i; ++i)
    {
        dg.push_event_time_ns(1);
    }}

    { for (int i = 0; 1000 != i; ++i)
    {
        dg.push_event_time_us(1);
    }}

    { for (int i = 0; 100 != i; ++i)
    {
        dg.push_event_time_ms(1);
    }}

    { for (int i = 0; 10 != i; ++i)
    {
        dg.push_event_time_s(1);
    }}

    TEST_BOOLEAN_FALSE(dg.has_overflowed());

    TEST_INT_EQ(11110, dg.event_count());
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(ss_nullptr_k));
    TEST_BOOLEAN_TRUE(dg.try_get_total_event_time_ns(&total_event_time_ns));
    TEST_INT_EQ(10101010000u, total_event_time_ns);
    TEST_INT_EQ(10101010000u, dg.total_event_time_ns_raw());
    TEST_BOOLEAN_TRUE(dg.try_get_min_event_time_ns(&min_event_time_ns));
    TEST_INT_EQ(1, min_event_time_ns);
    TEST_BOOLEAN_TRUE(dg.try_get_max_event_time_ns(&max_event_time_ns));
    TEST_INT_EQ(1000000000u, max_event_time_ns);
    TEST_INT_EQ(10000, dg.num_events_in_1ns());
    TEST_INT_EQ(0, dg.num_events_in_10ns());
    TEST_INT_EQ(0, dg.num_events_in_100ns());
    TEST_INT_EQ(1000, dg.num_events_in_1us());
    TEST_INT_EQ(0, dg.num_events_in_10us());
    TEST_INT_EQ(0, dg.num_events_in_100us());
    TEST_INT_EQ(100, dg.num_events_in_1ms());
    TEST_INT_EQ(0, dg.num_events_in_10ms());
    TEST_INT_EQ(0, dg.num_events_in_100ms());
    TEST_INT_EQ(10, dg.num_events_in_1s());
    TEST_INT_EQ(0, dg.num_events_in_10s());
    TEST_INT_EQ(0, dg.num_events_ge_100s());

    {
        char    strip[12];

        stlsoft::gram_to_strip(dg, &strip);

        TEST_MS_EQ_N("e__d__c__b__", strip, 12);
    }
}

static void TEST_doomgram_OVERFLOW_BY_SECONDS()
{
    stlsoft::doomgram   dg;

    // uint64 max:
    //
    // 18,446,744,073,709,551,615 ns
    //     18,446,744,073,709,551 µs
    //         18,446,744,073,709 ms
    //             18,446,744,073  s

    // 18446744073 max

    // add in max # seconds
    {
        bool r = dg.push_event_time_s(18446744073);

        TEST_BOOLEAN_TRUE(r);
    }

    // add in 0 more
    {
        bool r = dg.push_event_time_s(0);

        TEST_BOOLEAN_TRUE(r);
    }

    // add in 1 more to overflow
    {
        bool r = dg.push_event_time_s(1);

        TEST_BOOLEAN_FALSE(r);
    }
}

static void TEST_doomgram_OVERFLOW_BY_MICROSECONDS()
{
    stlsoft::doomgram   dg;

    // uint64 max:
    //
    // 18,446,744,073,709,551,615 ns
    //     18,446,744,073,709,551 µs
    //         18,446,744,073,709 ms
    //             18,446,744,073  s

    // 18446744073 max

    // add in max-1 # microseconds
    {
        bool r = dg.push_event_time_us(18446744073709550);

        TEST_BOOLEAN_TRUE(r);
    }

    // add in 1 more to max
    {
        bool r = dg.push_event_time_us(1);

        TEST_BOOLEAN_TRUE(r);
    }

    // add in 0 more
    {
        bool r = dg.push_event_time_us(0);

        TEST_BOOLEAN_TRUE(r);
    }

    // add in 1 more to overflow
    {
        bool r = dg.push_event_time_us(1);

        TEST_BOOLEAN_FALSE(r);
    }
}

static void TEST_calc_doom_1()
{
    {
        TEST_INT_EQ(0u, stlsoft::calc_doom(0));
    }

    {
        for (unsigned i = 1; i != 10; ++i)
        {
            TEST_INT_EQ(1u, stlsoft::calc_doom(i));
        }
    }

    {
        for (unsigned i = 10; i != 100; ++i)
        {
            TEST_INT_EQ(2u, stlsoft::calc_doom(i));
        }
    }

    {
        for (unsigned i = 100; i != 1000; ++i)
        {
            TEST_INT_EQ(3u, stlsoft::calc_doom(i));
        }
    }

    {
        TEST_INT_EQ(4u, stlsoft::calc_doom(1000));
        TEST_INT_EQ(4u, stlsoft::calc_doom(9999));
    }

    {
        TEST_INT_EQ(5u, stlsoft::calc_doom(10000));
        TEST_INT_EQ(5u, stlsoft::calc_doom(99999));
    }

    {
        TEST_INT_EQ(6u, stlsoft::calc_doom(100000));
        TEST_INT_EQ(6u, stlsoft::calc_doom(999999));
    }

    {
        TEST_INT_EQ(7u, stlsoft::calc_doom(1000000));
        TEST_INT_EQ(7u, stlsoft::calc_doom(9999999));
    }

    {
        TEST_INT_EQ(8u, stlsoft::calc_doom(10000000));
        TEST_INT_EQ(8u, stlsoft::calc_doom(99999999));
    }

    {
        TEST_INT_EQ(9u, stlsoft::calc_doom(100000000));
        TEST_INT_EQ(9u, stlsoft::calc_doom(999999999));
    }

    {
        TEST_INT_EQ(10u, stlsoft::calc_doom(1000000000));
        TEST_INT_EQ(10u, stlsoft::calc_doom(9999999999));
    }
}

static void TEST_UNSIGNED_OVERFLOW()
{
    using stlsoft::ss_uint8_t;
    using stlsoft::ss_uint64_t;

    {
        ss_uint64_t  a   =   0x8000000000000000;
        ss_uint64_t  b   =   0x8000000000000001;
        ss_uint64_t  c   =   a + b;

        TEST_INT_EQ(1, c);
    }

    {
        for (unsigned i = 0; i != 256; ++i)
        {
            for (unsigned j = 0; j != 256; ++j)
            {
                ss_uint8_t  a   =   static_cast<ss_uint8_t>(i);
                ss_uint8_t  b   =   static_cast<ss_uint8_t>(j);
                ss_uint8_t  c   =   a + b;

                unsigned    s   =   i + j;

                if (s > 255)
                {
                    TEST_INT_LT(a, c);
                    TEST_INT_LT(b, c);
                }
            }
        }
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

