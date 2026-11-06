/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.diagnostics.par_strip/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::par_strip`.
 *
 * Created: 24th September 2026
 * Updated: 26th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* ///////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/diagnostics/par_strip.hpp>

/* ///////////////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_par_strip_ACCESSORS();
    static void TEST_par_strip_STRIP_LENGTH();
    static void TEST_par_strip_AT_PAR_WHEN_EQUAL();
    static void TEST_par_strip_AT_PAR_WHEN_BELOW_MIN_OOM();
    static void TEST_par_strip_EXAMPLE_1_BACKWARD();
    static void TEST_par_strip_EXAMPLE_1_FORWARD();
    static void TEST_par_strip_EXAMPLE_2_BACKWARD_S91();
    static void TEST_par_strip_EXAMPLE_2_FORWARD_S91();
    static void TEST_par_strip_S89_BACKWARD();
    static void TEST_par_strip_EXACT_POWER_ROOM_0_FORWARD();
    static void TEST_par_strip_EXACT_POWER_ROOM_0_BACKWARD();
    static void TEST_par_strip_CLAMP_TO_MAX_OOM_BACKWARD();
    static void TEST_par_strip_BASE_2_FORWARD();
    static void TEST_par_strip_DOUBLE_EXAMPLE_1_BACKWARD();
    static void TEST_par_strip_SPECTRUM_BASE_10();
    static void TEST_par_strip_SPECTRUM_OTHER_BASES();
    static void TEST_par_strip_SOFT_CLAMP_AT_MAX_OOM();
    static void TEST_par_strip_EXCEED_MAX_OOM();
    static void TEST_par_strip_SPECTRUM_DOUBLE();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.diagnostics.par_strip", verbosity))
    {
        XTESTS_RUN_CASE(TEST_par_strip_ACCESSORS);
        XTESTS_RUN_CASE(TEST_par_strip_STRIP_LENGTH);
        XTESTS_RUN_CASE(TEST_par_strip_AT_PAR_WHEN_EQUAL);
        XTESTS_RUN_CASE(TEST_par_strip_AT_PAR_WHEN_BELOW_MIN_OOM);
        XTESTS_RUN_CASE(TEST_par_strip_EXAMPLE_1_BACKWARD);
        XTESTS_RUN_CASE(TEST_par_strip_EXAMPLE_1_FORWARD);
        XTESTS_RUN_CASE(TEST_par_strip_EXAMPLE_2_BACKWARD_S91);
        XTESTS_RUN_CASE(TEST_par_strip_EXAMPLE_2_FORWARD_S91);
        XTESTS_RUN_CASE(TEST_par_strip_S89_BACKWARD);
        XTESTS_RUN_CASE(TEST_par_strip_EXACT_POWER_ROOM_0_FORWARD);
        XTESTS_RUN_CASE(TEST_par_strip_EXACT_POWER_ROOM_0_BACKWARD);
        XTESTS_RUN_CASE(TEST_par_strip_CLAMP_TO_MAX_OOM_BACKWARD);
        XTESTS_RUN_CASE(TEST_par_strip_BASE_2_FORWARD);
        XTESTS_RUN_CASE(TEST_par_strip_DOUBLE_EXAMPLE_1_BACKWARD);
        XTESTS_RUN_CASE(TEST_par_strip_SPECTRUM_BASE_10);
        XTESTS_RUN_CASE(TEST_par_strip_SPECTRUM_OTHER_BASES);
        XTESTS_RUN_CASE(TEST_par_strip_SOFT_CLAMP_AT_MAX_OOM);
        XTESTS_RUN_CASE(TEST_par_strip_EXCEED_MAX_OOM);
        XTESTS_RUN_CASE(TEST_par_strip_SPECTRUM_DOUBLE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

typedef stlsoft::par_strip<10, stlsoft::ss_sint64_t>       par_strip_10_t;
typedef stlsoft::par_strip<16, stlsoft::ss_sint64_t>       par_strip_16_t;
typedef stlsoft::par_strip<2, stlsoft::ss_sint64_t>        par_strip_2_t;
typedef stlsoft::par_strip<8, stlsoft::ss_sint64_t>        par_strip_8_t;
typedef stlsoft::par_strip<10, double>                     par_strip_f64_t;

using stlsoft::par_strip_direction;


static void expect_strip_(char const* expected, std::string const& actual)
{
    TEST_MS_EQ_N(expected, actual.c_str(), actual.size());
    TEST_MS_EQ(expected, actual);
}

static void TEST_par_strip_ACCESSORS()
{
    par_strip_10_t const ps(
        -2
    ,   +5
    ,   par_strip_direction::backward
    ,   100
    ,   110
    );

    TEST_INT_EQ(-2, ps.min_oom());
    TEST_INT_EQ(+5, ps.max_oom());
    TEST_INT_EQ(static_cast<int>(par_strip_direction::backward), static_cast<int>(ps.direction()));
    TEST_INT_EQ(100, ps.reference());
    TEST_INT_EQ(110, ps.sample());
    TEST_INT_EQ(10, ps.base);
}

static void TEST_par_strip_STRIP_LENGTH()
{
    par_strip_10_t const wide(-2, +5, par_strip_direction::forward, 100, 100);
    par_strip_10_t const narrow(-1, +5, par_strip_direction::forward, 100, 100);

    TEST_INT_EQ(17, wide.strip_length());
    TEST_INT_EQ(15, narrow.strip_length());
}

static void TEST_par_strip_AT_PAR_WHEN_EQUAL()
{
    {
        par_strip_10_t const ps(0, +1, par_strip_direction::backward, 100, 100);

        expect_strip_("--|--", ps.to_strip());
    }

    {
        par_strip_10_t const ps(0, +2, par_strip_direction::backward, 100, 100);

        expect_strip_("---|---", ps.to_strip());
    }

    {
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 100);

        expect_strip_("--------|--------", ps.to_strip());
    }

    {
        par_strip_10_t const ps(-10, +10, par_strip_direction::backward, 100, 100);

        expect_strip_("---------------------|---------------------", ps.to_strip());
    }
}

static void TEST_par_strip_AT_PAR_WHEN_BELOW_MIN_OOM()
{
    // -1:+5
    {
        {
            // |101 - 100| / 100 = 0.01 = 10^-2, which is below Min-oom -1.
            par_strip_10_t const ps(-1, +5, par_strip_direction::forward, 100, 101);

            TEST_INT_EQ(15, ps.strip_length());
            expect_strip_("-------|-------", ps.to_strip());
        }

        {
            par_strip_10_t const ps(-1, +5, par_strip_direction::forward, 100, 91);

            TEST_INT_EQ(15, ps.strip_length());
            expect_strip_("-------|-------", ps.to_strip());
        }
    }

    // +1:+5
    {
        {
            par_strip_10_t const ps(+1, +5, par_strip_direction::forward, 100, 101);

            TEST_INT_EQ(11, ps.strip_length());
            expect_strip_("-----|-----", ps.to_strip());
        }

        {
            par_strip_10_t const ps(+1, +5, par_strip_direction::forward, 100, 91);

            TEST_INT_EQ(11, ps.strip_length());
            expect_strip_("-----|-----", ps.to_strip());
        }
    }
}

static void TEST_par_strip_EXAMPLE_1_BACKWARD()
{
    {
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 109);

        expect_strip_("-------+|--------", ps.to_strip());
    }

    {
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 111);

        expect_strip_("------+-|--------", ps.to_strip());
    }

    {
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 110);

        expect_strip_("------+-|--------", ps.to_strip());
    }
}

static void TEST_par_strip_EXAMPLE_1_FORWARD()
{
    par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 100, 110);

    expect_strip_("--------|-+------", ps.to_strip());
}

static void TEST_par_strip_EXAMPLE_2_BACKWARD_S91()
{
    par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 91);

    expect_strip_("--------|+-------", ps.to_strip());
}

static void TEST_par_strip_EXAMPLE_2_FORWARD_S91()
{
    par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 100, 91);

    expect_strip_("-------+|--------", ps.to_strip());
}

static void TEST_par_strip_S89_BACKWARD()
{
    // |89 - 100| / 100 = 0.11, ROOM = -1. Backward and S < R => right.
    par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 89);

    expect_strip_("--------|-+------", ps.to_strip());
}

static void TEST_par_strip_EXACT_POWER_ROOM_0_FORWARD()
{
    par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 100, 200);

    expect_strip_("--------|--+-----", ps.to_strip());
}

static void TEST_par_strip_EXACT_POWER_ROOM_0_BACKWARD()
{
    // |200 - 100| / 100 = 10^0, ROOM = 0.
    par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 200);

    expect_strip_("-----+--|--------", ps.to_strip());
}

static void TEST_par_strip_CLAMP_TO_MAX_OOM_BACKWARD()
{
    // |100000100 - 100| / 100 = 10^6, ROOM = 6, clamped to Max-oom +5.
    par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 100000100);

    expect_strip_("+-------|--------", ps.to_strip());
}

static void TEST_par_strip_BASE_2_FORWARD()
{
    // |12 - 8| / 8 = 1/2 = 2^-1, adjacent to the pipe on the right.
    par_strip_2_t const ps(-1, +2, par_strip_direction::forward, 8, 12);

    TEST_INT_EQ(9, ps.strip_length());
    TEST_INT_EQ(2, ps.base);
    expect_strip_("----|+---", ps.to_strip());
}

static void TEST_par_strip_DOUBLE_EXAMPLE_1_BACKWARD()
{
    par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 110.0);

    expect_strip_("------+-|--------", ps.to_strip());
}

static void TEST_par_strip_SPECTRUM_BASE_10()
{
    {
        // at par; f64_room=None; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 100);

        expect_strip_("--------|--------", ps.to_strip());
    }
    {
        // at par fwd; f64_room=None; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 100, 100);

        expect_strip_("--------|--------", ps.to_strip());
    }
    {
        // S=0 room 0; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 0);

        expect_strip_("--------|--+-----", ps.to_strip());
    }
    {
        // below min_oom; f64_room=-2; exceeds_max=False
        par_strip_10_t const ps(-1, +5, par_strip_direction::backward, 100, 101);

        expect_strip_("-------|-------", ps.to_strip());
    }
    {
        // below raised min_oom; f64_room=-1; exceeds_max=False
        par_strip_10_t const ps(+1, +5, par_strip_direction::backward, 100, 110);

        expect_strip_("-----|-----", ps.to_strip());
    }
    {
        // room -2 above; f64_room=-2; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 101);

        expect_strip_("-------+|--------", ps.to_strip());
    }
    {
        // room -2 below; f64_room=-2; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 99);

        expect_strip_("--------|+-------", ps.to_strip());
    }
    {
        // room -1 above; f64_room=-1; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 110);

        expect_strip_("------+-|--------", ps.to_strip());
    }
    {
        // room -1 below; f64_room=-1; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 90);

        expect_strip_("--------|-+------", ps.to_strip());
    }
    {
        // room 0 above; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 200);

        expect_strip_("-----+--|--------", ps.to_strip());
    }
    {
        // room 1 above; f64_room=1; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 1100);

        expect_strip_("----+---|--------", ps.to_strip());
    }
    {
        // room 2 above; f64_room=2; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 10100);

        expect_strip_("---+----|--------", ps.to_strip());
    }
    {
        // room 3 above; f64_room=2; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 100100);

        expect_strip_("--+-----|--------", ps.to_strip());
    }
    {
        // room 4 above; f64_room=4; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 1000100);

        expect_strip_("-+------|--------", ps.to_strip());
    }
    {
        // room 5 above; f64_room=5; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 10000100);

        expect_strip_("+-------|--------", ps.to_strip());
    }
    {
        // fwd room -1; f64_room=-1; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 100, 110);

        expect_strip_("--------|-+------", ps.to_strip());
    }
    {
        // fwd room -2; f64_room=-2; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 100, 91);

        expect_strip_("-------+|--------", ps.to_strip());
    }
    {
        // fwd room 0; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 100, 200);

        expect_strip_("--------|--+-----", ps.to_strip());
    }
    {
        // boundary 109; f64_room=-2; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 109);

        expect_strip_("-------+|--------", ps.to_strip());
    }
    {
        // boundary 89; f64_room=-1; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 89);

        expect_strip_("--------|-+------", ps.to_strip());
    }
    {
        // at par R=1; f64_room=None; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1, 1);

        expect_strip_("--------|--------", ps.to_strip());
    }
    {
        // S=0 R=1; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1, 0);

        expect_strip_("--------|--+-----", ps.to_strip());
    }
    {
        // room ~0 R=1; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1, 2);

        expect_strip_("-----+--|--------", ps.to_strip());
    }
    {
        // at par R=1000; f64_room=None; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000, 1000);

        expect_strip_("--------|--------", ps.to_strip());
    }
    {
        // S=0 R=1000; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000, 0);

        expect_strip_("--------|--+-----", ps.to_strip());
    }
    {
        // room ~0 R=1000; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000, 2000);

        expect_strip_("-----+--|--------", ps.to_strip());
    }
    {
        // room ~-1 R=1000; f64_room=-1; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000, 1100);

        expect_strip_("------+-|--------", ps.to_strip());
    }
    {
        // at par R=1000000; f64_room=None; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000, 1000000);

        expect_strip_("--------|--------", ps.to_strip());
    }
    {
        // S=0 R=1000000; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000, 0);

        expect_strip_("--------|--+-----", ps.to_strip());
    }
    {
        // room ~0 R=1000000; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000, 2000000);

        expect_strip_("-----+--|--------", ps.to_strip());
    }
    {
        // room ~-1 R=1000000; f64_room=-1; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000, 1100000);

        expect_strip_("------+-|--------", ps.to_strip());
    }
    {
        // at par R=1000000000000; f64_room=None; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000000000LL, 1000000000000LL);

        expect_strip_("--------|--------", ps.to_strip());
    }
    {
        // S=0 R=1000000000000; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000000000LL, 0);

        expect_strip_("--------|--+-----", ps.to_strip());
    }
    {
        // room ~0 R=1000000000000; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000000000LL, 2000000000000LL);

        expect_strip_("-----+--|--------", ps.to_strip());
    }
    {
        // room ~-1 R=1000000000000; f64_room=-1; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000000000LL, 1100000000000LL);

        expect_strip_("------+-|--------", ps.to_strip());
    }
    {
        // at par R=1000000000000000; f64_room=None; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000000000000LL, 1000000000000000LL);

        expect_strip_("--------|--------", ps.to_strip());
    }
    {
        // S=0 R=1000000000000000; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000000000000LL, 0);

        expect_strip_("--------|--+-----", ps.to_strip());
    }
    {
        // room ~0 R=1000000000000000; f64_room=0; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000000000000LL, 2000000000000000LL);

        expect_strip_("-----+--|--------", ps.to_strip());
    }
    {
        // room ~-1 R=1000000000000000; f64_room=-1; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000000000000LL, 1100000000000000LL);

        expect_strip_("------+-|--------", ps.to_strip());
    }
}

static void TEST_par_strip_SPECTRUM_OTHER_BASES()
{
    {
        // spec base2; f64_room=-1; exceeds_max=False
        par_strip_2_t const ps(-1, +2, par_strip_direction::forward, 8, 12);

        expect_strip_("----|+---", ps.to_strip());
    }
    {
        // base2 room 0; f64_room=0; exceeds_max=False
        par_strip_2_t const ps(-4, +4, par_strip_direction::backward, 64, 128);

        expect_strip_("----+----|---------", ps.to_strip());
    }
    {
        // base2 fractional; f64_room=-2; exceeds_max=False
        par_strip_2_t const ps(-4, +4, par_strip_direction::backward, 64, 80);

        expect_strip_("------+--|---------", ps.to_strip());
    }
    {
        // base2 S=0; f64_room=0; exceeds_max=False
        par_strip_2_t const ps(-4, +4, par_strip_direction::forward, 1024, 0);

        expect_strip_("----+----|---------", ps.to_strip());
    }
    {
        // base8; f64_room=-1; exceeds_max=False
        par_strip_8_t const ps(-3, +3, par_strip_direction::backward, 512, 576);

        expect_strip_("----+--|-------", ps.to_strip());
    }
    {
        // base8 room 1; f64_room=0; exceeds_max=False
        par_strip_8_t const ps(-3, +3, par_strip_direction::backward, 512, 4096);

        expect_strip_("---+---|-------", ps.to_strip());
    }
    {
        // base16; f64_room=-1; exceeds_max=False
        par_strip_16_t const ps(-3, +3, par_strip_direction::backward, 256, 272);

        expect_strip_("----+--|-------", ps.to_strip());
    }
    {
        // base16 room 1; f64_room=0; exceeds_max=False
        par_strip_16_t const ps(-3, +3, par_strip_direction::backward, 256, 4096);

        expect_strip_("---+---|-------", ps.to_strip());
    }
}

static void TEST_par_strip_SOFT_CLAMP_AT_MAX_OOM()
{
    // f64 under-reads |d|/R=1e6 as room=X; mark sits on the outer slot without a true exceed
    {
        // soft clamp float under-read bwd; f64_room=5; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 100000100);

        expect_strip_("+-------|--------", ps.to_strip());
    }
    {
        // soft clamp float under-read fwd; f64_room=5; exceeds_max=False
        par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 100, 100000100);

        expect_strip_("--------|-------+", ps.to_strip());
    }
}

static void TEST_par_strip_EXCEED_MAX_OOM()
{
    // rOOM > X must clamp to the outer slot (SPEC). Fails/panics until to_strip clamps.
    {
        // exceed oom~8 bwd; f64_room=8; exceeds_max=True
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 10000000100LL);

        expect_strip_("+-------|--------", ps.to_strip());
    }
    {
        // exceed oom~12 bwd; f64_room=11; exceeds_max=True
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 100, 100000000000100LL);

        expect_strip_("+-------|--------", ps.to_strip());
    }
    {
        // exceed R=1e6 bwd; f64_room=10; exceeds_max=True
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000, 10000000001000000LL);

        expect_strip_("+-------|--------", ps.to_strip());
    }
    {
        // exceed R=1e9 bwd; f64_room=8; exceeds_max=True
        par_strip_10_t const ps(-2, +5, par_strip_direction::backward, 1000000000LL, 100000001000000000LL);

        expect_strip_("+-------|--------", ps.to_strip());
    }
    {
        // exceed narrow window bwd; f64_room=8; exceeds_max=True
        par_strip_10_t const ps(-4, +2, par_strip_direction::backward, 100, 10000000100LL);

        expect_strip_("+------|-------", ps.to_strip());
    }
    {
        // exceed oom~8 fwd; f64_room=8; exceeds_max=True
        par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 100, 10000000100LL);

        expect_strip_("--------|-------+", ps.to_strip());
    }
    {
        // exceed oom~12 fwd; f64_room=11; exceeds_max=True
        par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 100, 100000000000100LL);

        expect_strip_("--------|-------+", ps.to_strip());
    }
    {
        // exceed R=1e6 fwd; f64_room=10; exceeds_max=True
        par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 1000000, 10000000001000000LL);

        expect_strip_("--------|-------+", ps.to_strip());
    }
    {
        // exceed R=1e9 fwd; f64_room=8; exceeds_max=True
        par_strip_10_t const ps(-2, +5, par_strip_direction::forward, 1000000000LL, 100000001000000000LL);

        expect_strip_("--------|-------+", ps.to_strip());
    }
    {
        // exceed narrow window fwd; f64_room=8; exceeds_max=True
        par_strip_10_t const ps(-4, +2, par_strip_direction::forward, 100, 10000000100LL);

        expect_strip_("-------|------+", ps.to_strip());
    }
    {
        // exceed positive-only window; f64_room=8; exceeds_max=True
        par_strip_10_t const ps(0, +3, par_strip_direction::backward, 100, 10000000100LL);

        expect_strip_("+---|----", ps.to_strip());
    }
}

static void TEST_par_strip_SPECTRUM_DOUBLE()
{
    {
        // at par; f64_room=None
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 100.0);

        expect_strip_("--------|--------", ps.to_strip());
    }
    {
        // at par fwd; f64_room=None
        par_strip_f64_t const ps(-2, +5, par_strip_direction::forward, 100.0, 100.0);

        expect_strip_("--------|--------", ps.to_strip());
    }
    {
        // S=0 room 0; f64_room=0
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 0.0);

        expect_strip_("--------|--+-----", ps.to_strip());
    }
    {
        // below min_oom; f64_room=-2
        par_strip_f64_t const ps(-1, +5, par_strip_direction::backward, 100.0, 101.0);

        expect_strip_("-------|-------", ps.to_strip());
    }
    {
        // below raised min_oom; f64_room=-1
        par_strip_f64_t const ps(+1, +5, par_strip_direction::backward, 100.0, 110.0);

        expect_strip_("-----|-----", ps.to_strip());
    }
    {
        // room -2 above; f64_room=-2
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 101.0);

        expect_strip_("-------+|--------", ps.to_strip());
    }
    {
        // room -2 below; f64_room=-2
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 99.0);

        expect_strip_("--------|+-------", ps.to_strip());
    }
    {
        // room -1 above; f64_room=-1
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 110.0);

        expect_strip_("------+-|--------", ps.to_strip());
    }
    {
        // room -1 below; f64_room=-1
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 90.0);

        expect_strip_("--------|-+------", ps.to_strip());
    }
    {
        // room 0 above; f64_room=0
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 200.0);

        expect_strip_("-----+--|--------", ps.to_strip());
    }
    {
        // room 1 above; f64_room=1
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 1100.0);

        expect_strip_("----+---|--------", ps.to_strip());
    }
    {
        // room 2 above; f64_room=2
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 10100.0);

        expect_strip_("---+----|--------", ps.to_strip());
    }
    {
        // room 3 above; f64_room=2
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 100100.0);

        expect_strip_("--+-----|--------", ps.to_strip());
    }
    {
        // room 4 above; f64_room=4
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 1000100.0);

        expect_strip_("-+------|--------", ps.to_strip());
    }
    {
        // room 5 above; f64_room=5
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 10000100.0);

        expect_strip_("+-------|--------", ps.to_strip());
    }
    {
        // fwd room -1; f64_room=-1
        par_strip_f64_t const ps(-2, +5, par_strip_direction::forward, 100.0, 110.0);

        expect_strip_("--------|-+------", ps.to_strip());
    }
    {
        // fwd room -2; f64_room=-2
        par_strip_f64_t const ps(-2, +5, par_strip_direction::forward, 100.0, 91.0);

        expect_strip_("-------+|--------", ps.to_strip());
    }
    {
        // fwd room 0; f64_room=0
        par_strip_f64_t const ps(-2, +5, par_strip_direction::forward, 100.0, 200.0);

        expect_strip_("--------|--+-----", ps.to_strip());
    }
    {
        // boundary 109; f64_room=-2
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 109.0);

        expect_strip_("-------+|--------", ps.to_strip());
    }
    {
        // boundary 89; f64_room=-1
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 89.0);

        expect_strip_("--------|-+------", ps.to_strip());
    }
    {
        // soft clamp float under-read bwd; f64_room=5
        par_strip_f64_t const ps(-2, +5, par_strip_direction::backward, 100.0, 100000100.0);

        expect_strip_("+-------|--------", ps.to_strip());
    }
    {
        // soft clamp float under-read fwd; f64_room=5
        par_strip_f64_t const ps(-2, +5, par_strip_direction::forward, 100.0, 100000100.0);

        expect_strip_("--------|-------+", ps.to_strip());
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

