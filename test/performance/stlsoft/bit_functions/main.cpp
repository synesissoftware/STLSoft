/* /////////////////////////////////////////////////////////////////////////
 * File:    test.performance.stlsoft.bit_functions/main.cpp
 *
 * Purpose: Perf-test for bit functions.
 *
 * Created: 24th September 2026
 * Updated: 25th September 2026
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
 * forward declarations
 */

void
emit_result_row(
    char const*             function_name
,   interval_t const*       uint8_ns
,   interval_t const*       uint16_ns
,   interval_t const*       uint32_ns
,   interval_t const*       uint64_ns
,   interval_t const*       int_ns
,   ss_uint64_t             anchor_value
,   bool                    report_per_element
);


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

    ss_size_t const NUM_ITERATIONS   = 20000000;
    ss_size_t const NUM_SAMPLES      = 5;
    ss_size_t const XOR_RANGE_LEN    = 64;
    int const       FN_COL_WIDTH     = 42;
    int const       METRIC_COL_WIDTH = 16;


    interval_t
    median_sample(
        interval_t const*   samples
    ,   ss_size_t           n
    )
    {
        interval_t sorted[NUM_SAMPLES] = {};

        if (0 == n)
        {
            return 0;
        }

        if (n > NUM_SAMPLES)
        {
            n = NUM_SAMPLES;
        }

        for (ss_size_t i = 0; n != i; ++i)
        {
            sorted[i] = samples[i];
        }

        for (ss_size_t i = 1; n != i; ++i)
        {
            interval_t const v = sorted[i];
            ss_size_t j = i;

            for (; 0 != j && sorted[j - 1] > v; --j)
            {
                sorted[j] = sorted[j - 1];
            }

            sorted[j] = v;
        }

        return sorted[n / 2];
    }

    struct row_samples
    {
        interval_t  u8[NUM_SAMPLES];
        interval_t  u16[NUM_SAMPLES];
        interval_t  u32[NUM_SAMPLES];
        interval_t  u64[NUM_SAMPLES];
        interval_t  si[NUM_SAMPLES];
        ss_size_t   n;
        ss_uint64_t anchor;
        bool        has_u8;
        bool        has_u16;
        bool        has_u32;
        bool        has_u64;
        bool        has_si;

        void clear()
        {
            n       = 0;
            anchor  = 0;
            has_u8  = false;
            has_u16 = false;
            has_u32 = false;
            has_u64 = false;
            has_si  = false;
        }

        void push(
            interval_t const*   uint8_ns
        ,   interval_t const*   uint16_ns
        ,   interval_t const*   uint32_ns
        ,   interval_t const*   uint64_ns
        ,   interval_t const*   int_ns
        ,   ss_uint64_t         anchor_value
        )
        {
            has_u8  = NULL != uint8_ns;
            has_u16 = NULL != uint16_ns;
            has_u32 = NULL != uint32_ns;
            has_u64 = NULL != uint64_ns;
            has_si  = NULL != int_ns;

            if (has_u8)
            {
                u8[n] = *uint8_ns;
            }
            if (has_u16)
            {
                u16[n] = *uint16_ns;
            }
            if (has_u32)
            {
                u32[n] = *uint32_ns;
            }
            if (has_u64)
            {
                u64[n] = *uint64_ns;
            }
            if (has_si)
            {
                si[n] = *int_ns;
            }

            anchor = anchor_value;
            ++n;
        }

        void emit(
            char const* function_name
        ,   bool        report_per_element = false
        ) const
        {
            interval_t const med_u8  = has_u8  ? median_sample(u8, n)  : 0;
            interval_t const med_u16 = has_u16 ? median_sample(u16, n) : 0;
            interval_t const med_u32 = has_u32 ? median_sample(u32, n) : 0;
            interval_t const med_u64 = has_u64 ? median_sample(u64, n) : 0;
            interval_t const med_si  = has_si  ? median_sample(si, n)  : 0;

            emit_result_row(
                function_name
            ,   has_u8  ? &med_u8  : NULL
            ,   has_u16 ? &med_u16 : NULL
            ,   has_u32 ? &med_u32 : NULL
            ,   has_u64 ? &med_u64 : NULL
            ,   has_si  ? &med_si  : NULL
            ,   anchor
            ,   report_per_element
            );
        }
    };
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
emit_rate_cell(
    interval_t const*   total_ns
,   double              divisor
);

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
    emit_metric_cell("uint8_t ns");
    emit_metric_cell("uint16_t ns");
    emit_metric_cell("uint32_t ns");
    emit_metric_cell("uint64_t ns");
    emit_metric_cell("int ns");
    emit_metric_cell("uint8_t el");
    emit_metric_cell("uint16_t el");
    emit_metric_cell("uint32_t el");
    emit_metric_cell("uint64_t el");
    emit_metric_cell("anchor");
    std::cout << std::endl;
}

bool
env_is_truey(
    char const* name
)
{
#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif
    char const* const env = ::getenv(name);
#if defined(_MSC_VER)
# pragma warning(pop)
#endif

    if (NULL == env || '\0' == *env)
    {
        return false;
    }

    if (0 == ::strcmp(env, "1") ||
        0 == ::strcmp(env, "ok") ||
        0 == ::strcmp(env, "on") ||
        0 == ::strcmp(env, "true") ||
        0 == ::strcmp(env, "yes") ||
        0 == ::strcmp(env, "y") ||
        0 == ::strcmp(env, "OK") ||
        0 == ::strcmp(env, "ON") ||
        0 == ::strcmp(env, "TRUE") ||
        0 == ::strcmp(env, "YES") ||
        0 == ::strcmp(env, "Y"))
    {
        return true;
    }

    return false;
}

void
maybe_emit_group_gap(
    char const* function_name
)
{
    static bool have_prev = false;
    static char prev_key[64] = "";

    if (!env_is_truey("SIS_PERFTESTS_GROUPGAPS"))
    {
        return;
    }

    char const* const slash = ::strrchr(function_name, '/');
    char const* const pattern = (NULL == slash) ? "" : slash;
    char const*       family = "other";

    if (0 == ::strncmp(function_name, "count_bits", 10))
    {
        family = "count";
    }
    else if (0 == ::strncmp(function_name, "find_highest_bit", 16))
    {
        family = "find";
    }
    else if (0 == ::strncmp(function_name, "calculate_xor", 13))
    {
        family = "xor";
    }

    char key[64];

    snprintf(key, sizeof(key), "%s%s", family, pattern);

    if (have_prev && 0 != ::strcmp(prev_key, key))
    {
        std::cout << std::endl;
    }

    snprintf(prev_key, sizeof(prev_key), "%s", key);
    have_prev = true;
}

void
emit_result_row(
    char const*             function_name
,   interval_t const*       uint8_ns
,   interval_t const*       uint16_ns
,   interval_t const*       uint32_ns
,   interval_t const*       uint64_ns
,   interval_t const*       int_ns
,   ss_uint64_t             anchor_value
,       bool                    report_per_element
)
{
    maybe_emit_group_gap(function_name);

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

    double const per_call    = double(NUM_ITERATIONS);
    double const per_element = double(NUM_ITERATIONS) * double(XOR_RANGE_LEN + 1) / 2.0;

    emit_rate_cell(uint8_ns, per_call);
    emit_rate_cell(uint16_ns, per_call);
    emit_rate_cell(uint32_ns, per_call);
    emit_rate_cell(uint64_ns, per_call);
    emit_rate_cell(int_ns, per_call);

    if (report_per_element)
    {
        emit_rate_cell(uint8_ns, per_element);
        emit_rate_cell(uint16_ns, per_element);
        emit_rate_cell(uint32_ns, per_element);
        emit_rate_cell(uint64_ns, per_element);
    }
    else
    {
        emit_absent_metric_cell();
        emit_absent_metric_cell();
        emit_absent_metric_cell();
        emit_absent_metric_cell();
    }

    emit_metric_cell(thousands(anchor_value).c_str());
    std::cout << std::endl;
}

void
emit_rate_cell(
    interval_t const*   total_ns
,   double              divisor
)
{
    if (NULL == total_ns)
    {
        emit_absent_metric_cell();

        return;
    }

    char            buf[32];
    double const    rate = (0.0 == divisor) ? 0.0 : (double(*total_ns) / divisor);

    snprintf(buf, sizeof(buf), "%.3f", rate);

    emit_metric_cell(buf);
}

void
emit_build_banner()
{
    std::cout << "compiler: " << STLSOFT_COMPILER_VERSION_STRING << std::endl;
    std::cout << "optimisation: ";
#if 0
#elif defined(__OPTIMIZE_SIZE__)

    std::cout << "size";
#elif defined(__OPTIMIZE__)

    std::cout << "speed";
#elif defined(STLSOFT_COMPILER_IS_MSVC) && \
      !defined(STLSOFT_DEBUG)

    std::cout << "speed";
#else

    std::cout << "off";
#endif
#ifdef NDEBUG

    std::cout << ", release";
#else

    std::cout << ", debug-asserts";
#endif
    std::cout << std::endl;
    std::cout
        << "samples: "
        << NUM_SAMPLES
        << " (median; 1 warmup discarded)"
        << std::endl;
    std::cout
        << "width columns are loop ns; ns columns are ns/call; el columns are ns/element"
        << std::endl;
    if (env_is_truey("SIS_PERFTESTS_GROUPGAPS"))
    {
        std::cout
            << "Env: SIS_PERFTESTS_GROUPGAPS=1"
            << std::endl;
    }
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

    row_samples rows;

    emit_build_banner();
    emit_header_row();


    // count_bits_by_Kernighan_method
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(i);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(i);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_Kernighan_method()");
        }
    }


    // count_bits_by_8bit_table
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(i);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(i);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_8bit_table()");
        }
    }


    // count_bits
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(i);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(i);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   &int_int
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits()");
        }

    }

#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt_SUPPORT)
    // count_bits_by_intrinsic (sequential)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(i);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(i);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = i;

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = i;

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();
#endif


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
            ,   &int_uint64
#else
            ,   NULL
#endif
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_intrinsic()");
        }
    }
#endif


    // ------------------------------------------------------------------
    // Dense inputs (~i): high popcount — favourable to the table path
    // ------------------------------------------------------------------

    // count_bits_by_Kernighan_method (dense)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ~ss_uint8_t(i);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ~ss_uint16_t(i);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_Kernighan_method()/~i");
        }
    }


    // count_bits_by_8bit_table (dense)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ~ss_uint8_t(i);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ~ss_uint16_t(i);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_8bit_table()/~i");
        }
    }


    // count_bits (dense)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ~ss_uint8_t(i);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ~ss_uint16_t(i);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   &int_int
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits()/~i");
        }

    }

#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt_SUPPORT)
    // count_bits_by_intrinsic (/~i)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ~ss_uint8_t(i);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ~ss_uint16_t(i);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ~ss_uint32_t(i);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ~ss_uint64_t(i);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();
#endif


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
            ,   &int_uint64
#else
            ,   NULL
#endif
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_intrinsic()/~i");
        }
    }
#endif


    // ------------------------------------------------------------------
    // Max density (all-ones). Source via volatile so inlining cannot
    // constant-fold popcount(~0) to a literal.
    // ------------------------------------------------------------------

    {
        ss_uint8_t  volatile ones8  = ss_uint8_t(~ss_uint8_t(0));
        ss_uint16_t volatile ones16 = ss_uint16_t(~ss_uint16_t(0));
        ss_uint32_t volatile ones32 = ~ss_uint32_t(0);
        ss_uint64_t volatile ones64 = ~ss_uint64_t(0);


        // count_bits_by_Kernighan_method (max)
        for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
        {
            if (int(NUM_SAMPLES) + 1 == W)
            {
                rows.clear();
            }

            stopwatch_t sw;

            ss_uint64_t anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint8_t const v = ones8;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
            }
            sw.stop();

            interval_t const int_uint8 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint16_t const v = ones16;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
            }
            sw.stop();

            interval_t const int_uint16 = sw.get_nanoseconds();


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


            if (W <= int(NUM_SAMPLES))
            {
                rows.push(
                    &int_uint8
                ,   &int_uint16
                ,   &int_uint32
                ,   &int_uint64
                ,   NULL
                ,   anchor_value
                );
            }

            if (1 == W)
            {
                rows.emit("count_bits_by_Kernighan_method()/ones");
            }
        }


        // count_bits_by_8bit_table (max)
        for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
        {
            if (int(NUM_SAMPLES) + 1 == W)
            {
                rows.clear();
            }

            stopwatch_t sw;

            ss_uint64_t anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint8_t const v = ones8;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_8bit_table(v);
            }
            sw.stop();

            interval_t const int_uint8 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint16_t const v = ones16;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_8bit_table(v);
            }
            sw.stop();

            interval_t const int_uint16 = sw.get_nanoseconds();


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


            if (W <= int(NUM_SAMPLES))
            {
                rows.push(
                    &int_uint8
                ,   &int_uint16
                ,   &int_uint32
                ,   &int_uint64
                ,   NULL
                ,   anchor_value
                );
            }

            if (1 == W)
            {
                rows.emit("count_bits_by_8bit_table()/ones");
            }
        }


        // count_bits (max)
        for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
        {
            if (int(NUM_SAMPLES) + 1 == W)
            {
                rows.clear();
            }

            stopwatch_t sw;

            ss_uint64_t anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint8_t const v = ones8;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits(v);
            }
            sw.stop();

            interval_t const int_uint8 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint16_t const v = ones16;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits(v);
            }
            sw.stop();

            interval_t const int_uint16 = sw.get_nanoseconds();


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


            if (W <= int(NUM_SAMPLES))
            {
                rows.push(
                    &int_uint8
                ,   &int_uint16
                ,   &int_uint32
                ,   &int_uint64
                ,   &int_int
                ,   anchor_value
                );
            }

            if (1 == W)
            {
                rows.emit("count_bits()/ones");
            }

        }

#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt_SUPPORT)
        // count_bits_by_intrinsic (/ones)
        for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
        {
            if (int(NUM_SAMPLES) + 1 == W)
            {
                rows.clear();
            }

            stopwatch_t sw;

            ss_uint64_t anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint8_t const v = ones8;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint8 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint16_t const v = ones16;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint16 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint32_t const v = ones32;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint64_t const v = ones64;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint64 = sw.get_nanoseconds();
#endif


            if (W <= int(NUM_SAMPLES))
            {
                rows.push(
                    &int_uint8
                ,   &int_uint16
                ,   &int_uint32
#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
                ,   &int_uint64
#else
                ,   NULL
#endif
                ,   NULL
                ,   anchor_value
                );
            }

            if (1 == W)
            {
                rows.emit("count_bits_by_intrinsic()/ones");
            }
        }
#endif

    }


    // ------------------------------------------------------------------
    // Close-to-max: all-ones with one rotating bit cleared (31 / 63 ones)
    // ------------------------------------------------------------------

    // count_bits_by_Kernighan_method (close-to-max)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(~ss_uint8_t(0)) ^ (ss_uint8_t(1) << (i % 8u));

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(~ss_uint16_t(0)) ^ (ss_uint16_t(1) << (i % 16u));

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_Kernighan_method()/ones^1");
        }
    }


    // count_bits_by_8bit_table (close-to-max)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(~ss_uint8_t(0)) ^ (ss_uint8_t(1) << (i % 8u));

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(~ss_uint16_t(0)) ^ (ss_uint16_t(1) << (i % 16u));

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_8bit_table()/ones^1");
        }
    }


    // count_bits (close-to-max)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(~ss_uint8_t(0)) ^ (ss_uint8_t(1) << (i % 8u));

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(~ss_uint16_t(0)) ^ (ss_uint16_t(1) << (i % 16u));

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   &int_int
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits()/ones^1");
        }

    }

#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt_SUPPORT)
    // count_bits_by_intrinsic (/ones^1)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(~ss_uint8_t(0)) ^ (ss_uint8_t(1) << (i % 8u));

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(~ss_uint16_t(0)) ^ (ss_uint16_t(1) << (i % 16u));

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ~ss_uint32_t(0) ^ (ss_uint32_t(1) << (i % 32u));

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ~ss_uint64_t(0) ^ (ss_uint64_t(1) << (i % 64u));

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();
#endif


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
            ,   &int_uint64
#else
            ,   NULL
#endif
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_intrinsic()/ones^1");
        }
    }
#endif


    // ------------------------------------------------------------------
    // All-zero. Volatile so the call is not constant-folded to 0.
    // ------------------------------------------------------------------

    {
        ss_uint8_t  volatile zero8  = 0;
        ss_uint16_t volatile zero16 = 0;
        ss_uint32_t volatile zero32 = 0;
        ss_uint64_t volatile zero64 = 0;


        // count_bits_by_Kernighan_method (zero)
        for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
        {
            if (int(NUM_SAMPLES) + 1 == W)
            {
                rows.clear();
            }

            stopwatch_t sw;

            ss_uint64_t anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint8_t const v = zero8;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
            }
            sw.stop();

            interval_t const int_uint8 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint16_t const v = zero16;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
            }
            sw.stop();

            interval_t const int_uint16 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint32_t const v = zero32;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
            }
            sw.stop();

            interval_t const int_uint32 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint64_t const v = zero64;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
            }
            sw.stop();

            interval_t const int_uint64 = sw.get_nanoseconds();


            if (W <= int(NUM_SAMPLES))
            {
                rows.push(
                    &int_uint8
                ,   &int_uint16
                ,   &int_uint32
                ,   &int_uint64
                ,   NULL
                ,   anchor_value
                );
            }

            if (1 == W)
            {
                rows.emit("count_bits_by_Kernighan_method()/0");
            }
        }


        // count_bits_by_8bit_table (zero)
        for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
        {
            if (int(NUM_SAMPLES) + 1 == W)
            {
                rows.clear();
            }

            stopwatch_t sw;

            ss_uint64_t anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint8_t const v = zero8;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_8bit_table(v);
            }
            sw.stop();

            interval_t const int_uint8 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint16_t const v = zero16;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_8bit_table(v);
            }
            sw.stop();

            interval_t const int_uint16 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint32_t const v = zero32;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_8bit_table(v);
            }
            sw.stop();

            interval_t const int_uint32 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint64_t const v = zero64;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_8bit_table(v);
            }
            sw.stop();

            interval_t const int_uint64 = sw.get_nanoseconds();


            if (W <= int(NUM_SAMPLES))
            {
                rows.push(
                    &int_uint8
                ,   &int_uint16
                ,   &int_uint32
                ,   &int_uint64
                ,   NULL
                ,   anchor_value
                );
            }

            if (1 == W)
            {
                rows.emit("count_bits_by_8bit_table()/0");
            }
        }


        // count_bits (zero)
        for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
        {
            if (int(NUM_SAMPLES) + 1 == W)
            {
                rows.clear();
            }

            stopwatch_t sw;

            ss_uint64_t anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint8_t const v = zero8;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits(v);
            }
            sw.stop();

            interval_t const int_uint8 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint16_t const v = zero16;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits(v);
            }
            sw.stop();

            interval_t const int_uint16 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint32_t const v = zero32;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits(v);
            }
            sw.stop();

            interval_t const int_uint32 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint64_t const v = zero64;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits(v);
            }
            sw.stop();

            interval_t const int_uint64 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                int const v = static_cast<int>(zero32);

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits(v);
            }
            sw.stop();

            interval_t const int_int = sw.get_nanoseconds();


            if (W <= int(NUM_SAMPLES))
            {
                rows.push(
                    &int_uint8
                ,   &int_uint16
                ,   &int_uint32
                ,   &int_uint64
                ,   &int_int
                ,   anchor_value
                );
            }

            if (1 == W)
            {
                rows.emit("count_bits()/0");
            }

        }

#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt_SUPPORT)
        // count_bits_by_intrinsic (/0)
        for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
        {
            if (int(NUM_SAMPLES) + 1 == W)
            {
                rows.clear();
            }

            stopwatch_t sw;

            ss_uint64_t anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint8_t const v = zero8;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint8 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint16_t const v = zero16;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint16 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint32_t const v = zero32;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint64_t const v = zero64;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::count_bits_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint64 = sw.get_nanoseconds();
#endif


            if (W <= int(NUM_SAMPLES))
            {
                rows.push(
                    &int_uint8
                ,   &int_uint16
                ,   &int_uint32
#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
                ,   &int_uint64
#else
                ,   NULL
#endif
                ,   NULL
                ,   anchor_value
                );
            }

            if (1 == W)
            {
                rows.emit("count_bits_by_intrinsic()/0");
            }
        }
#endif

    }


    // ------------------------------------------------------------------
    // Single rotating bit. The 64-bit shift reaches bits 32..63.
    // ------------------------------------------------------------------

    // count_bits_by_Kernighan_method (bit)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(1) << (i % 8u);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(1) << (i % 16u);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ss_uint32_t(1) << (i % 32u);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ss_uint64_t(1) << (i % 64u);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_Kernighan_method()/bit");
        }
    }


    // count_bits_by_8bit_table (bit)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(1) << (i % 8u);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(1) << (i % 16u);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ss_uint32_t(1) << (i % 32u);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ss_uint64_t(1) << (i % 64u);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_8bit_table()/bit");
        }
    }


    // count_bits (bit)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(1) << (i % 8u);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(1) << (i % 16u);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ss_uint32_t(1) << (i % 32u);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ss_uint64_t(1) << (i % 64u);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            int const v = static_cast<int>(ss_uint32_t(1) << (i % 32u));

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_int = sw.get_nanoseconds();


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   &int_int
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits()/bit");
        }

    }

#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt_SUPPORT)
    // count_bits_by_intrinsic (/bit)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(1) << (i % 8u);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(1) << (i % 16u);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ss_uint32_t(1) << (i % 32u);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ss_uint64_t(1) << (i % 64u);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();
#endif


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
            ,   &int_uint64
#else
            ,   NULL
#endif
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_intrinsic()/bit");
        }
    }
#endif


    // ------------------------------------------------------------------
    // Both halves live. uint32 high 16 bits vary; uint64 high half is i.
    // ------------------------------------------------------------------

    // count_bits_by_Kernighan_method (wide)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = (ss_uint8_t(i) << 4) | ss_uint8_t(i & 0x0fu);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = (ss_uint16_t(i) << 8) | ss_uint16_t(i & 0xffu);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = (ss_uint32_t(i) << 16) | ss_uint32_t(i & 0xffffu);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = (ss_uint64_t(i) << 32) | ss_uint64_t(i);

            anchor_value += stlsoft::count_bits_by_Kernighan_method(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_Kernighan_method()/wide");
        }
    }


    // count_bits_by_8bit_table (wide)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = (ss_uint8_t(i) << 4) | ss_uint8_t(i & 0x0fu);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = (ss_uint16_t(i) << 8) | ss_uint16_t(i & 0xffu);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = (ss_uint32_t(i) << 16) | ss_uint32_t(i & 0xffffu);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = (ss_uint64_t(i) << 32) | ss_uint64_t(i);

            anchor_value += stlsoft::count_bits_by_8bit_table(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_8bit_table()/wide");
        }
    }


    // count_bits (wide)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = (ss_uint8_t(i) << 4) | ss_uint8_t(i & 0x0fu);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = (ss_uint16_t(i) << 8) | ss_uint16_t(i & 0xffu);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = (ss_uint32_t(i) << 16) | ss_uint32_t(i & 0xffffu);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = (ss_uint64_t(i) << 32) | ss_uint64_t(i);

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            int const v = static_cast<int>((ss_uint32_t(i) << 16) | ss_uint32_t(i & 0xffffu));

            anchor_value += stlsoft::count_bits(v);
        }
        sw.stop();

        interval_t const int_int = sw.get_nanoseconds();


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   &int_int
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits()/wide");
        }

    }

#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt_SUPPORT)
    // count_bits_by_intrinsic (/wide)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = (ss_uint8_t(i) << 4) | ss_uint8_t(i & 0x0fu);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = (ss_uint16_t(i) << 8) | ss_uint16_t(i & 0xffu);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = (ss_uint32_t(i) << 16) | ss_uint32_t(i & 0xffffu);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = (ss_uint64_t(i) << 32) | ss_uint64_t(i);

            anchor_value += stlsoft::count_bits_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();
#endif


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
#if defined(STLSOFT_CF__builtin_popcount_SUPPORT) || \
    defined(STLSOFT_CF__popcnt64_SUPPORT)
            ,   &int_uint64
#else
            ,   NULL
#endif
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("count_bits_by_intrinsic()/wide");
        }
    }
#endif


    // find_highest_bit
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("find_highest_bit()");
        }

    }

#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse_SUPPORT)
    // find_highest_bit_by_intrinsic (sequential)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = ss_uint8_t(i);

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = ss_uint16_t(i);

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = i;

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse64_SUPPORT)
        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = i;

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();
#endif


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse64_SUPPORT)
            ,   &int_uint64
#else
            ,   NULL
#endif
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("find_highest_bit_by_intrinsic()");
        }
    }
#endif


    // ------------------------------------------------------------------
    // find_highest_bit: zero, one rotating bit, both halves live.
    // ------------------------------------------------------------------

    {
        ss_uint8_t  volatile zero8  = 0;
        ss_uint16_t volatile zero16 = 0;
        ss_uint32_t volatile zero32 = 0;
        ss_uint64_t volatile zero64 = 0;


        // find_highest_bit (zero)
        for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
        {
            if (int(NUM_SAMPLES) + 1 == W)
            {
                rows.clear();
            }

            stopwatch_t sw;

            ss_uint64_t anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint8_t const v = zero8;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::find_highest_bit(v);
            }
            sw.stop();

            interval_t const int_uint8 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint16_t const v = zero16;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::find_highest_bit(v);
            }
            sw.stop();

            interval_t const int_uint16 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint32_t const v = zero32;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::find_highest_bit(v);
            }
            sw.stop();

            interval_t const int_uint32 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint64_t const v = zero64;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::find_highest_bit(v);
            }
            sw.stop();

            interval_t const int_uint64 = sw.get_nanoseconds();


            if (W <= int(NUM_SAMPLES))
            {
                rows.push(
                    &int_uint8
                ,   &int_uint16
                ,   &int_uint32
                ,   &int_uint64
                ,   NULL
                ,   anchor_value
                );
            }

            if (1 == W)
            {
                rows.emit("find_highest_bit()/0");
            }

        }

#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse_SUPPORT)
        // find_highest_bit_by_intrinsic (/0)
        for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
        {
            if (int(NUM_SAMPLES) + 1 == W)
            {
                rows.clear();
            }

            stopwatch_t sw;

            ss_uint64_t anchor_value = 0;


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint8_t const v = zero8;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint8 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint16_t const v = zero16;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint16 = sw.get_nanoseconds();


            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint32_t const v = zero32;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse64_SUPPORT)
            sw.start();
            for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
            {
                ss_uint64_t const v = zero64;

                STLSOFT_SUPPRESS_UNUSED(i);
                anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
            }
            sw.stop();

            interval_t const int_uint64 = sw.get_nanoseconds();
#endif


            if (W <= int(NUM_SAMPLES))
            {
                rows.push(
                    &int_uint8
                ,   &int_uint16
                ,   &int_uint32
#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse64_SUPPORT)
                ,   &int_uint64
#else
                ,   NULL
#endif
                ,   NULL
                ,   anchor_value
                );
            }

            if (1 == W)
            {
                rows.emit("find_highest_bit_by_intrinsic()/0");
            }
        }
#endif

    }


    // find_highest_bit (bit)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = static_cast<ss_uint8_t>(1u << (i % 8u));

            anchor_value += stlsoft::find_highest_bit(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = static_cast<ss_uint16_t>(1u << (i % 16u));

            anchor_value += stlsoft::find_highest_bit(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ss_uint32_t(1) << (i % 32u);

            anchor_value += stlsoft::find_highest_bit(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ss_uint64_t(1) << (i % 64u);

            anchor_value += stlsoft::find_highest_bit(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("find_highest_bit()/bit");
        }

    }

#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse_SUPPORT)
    // find_highest_bit_by_intrinsic (/bit)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = static_cast<ss_uint8_t>(1u << (i % 8u));

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = static_cast<ss_uint16_t>(1u << (i % 16u));

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = ss_uint32_t(1) << (i % 32u);

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse64_SUPPORT)
        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = ss_uint64_t(1) << (i % 64u);

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();
#endif


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse64_SUPPORT)
            ,   &int_uint64
#else
            ,   NULL
#endif
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("find_highest_bit_by_intrinsic()/bit");
        }
    }
#endif


    // find_highest_bit (wide)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


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
            ss_uint32_t const v = (ss_uint32_t(i) << 16) | ss_uint32_t(i & 0xffffu);

            anchor_value += stlsoft::find_highest_bit(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = (ss_uint64_t(i) << 32) | ss_uint64_t(i);

            anchor_value += stlsoft::find_highest_bit(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("find_highest_bit()/wide");
        }

    }

#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse_SUPPORT)
    // find_highest_bit_by_intrinsic (/wide)
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint8_t const v = static_cast<ss_uint8_t>(i & 0xff);

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint8 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint16_t const v = static_cast<ss_uint16_t>(i & 0xffff);

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint16 = sw.get_nanoseconds();


        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint32_t const v = (ss_uint32_t(i) << 16) | ss_uint32_t(i & 0xffffu);

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint32 = sw.get_nanoseconds();


#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse64_SUPPORT)
        sw.start();
        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            ss_uint64_t const v = (ss_uint64_t(i) << 32) | ss_uint64_t(i);

            anchor_value += stlsoft::find_highest_bit_by_intrinsic(v);
        }
        sw.stop();

        interval_t const int_uint64 = sw.get_nanoseconds();
#endif


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
#if defined(STLSOFT_CF__builtin_clz_SUPPORT) || \
    defined(STLSOFT_CF__BitScanReverse64_SUPPORT)
            ,   &int_uint64
#else
            ,   NULL
#endif
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("find_highest_bit_by_intrinsic()/wide");
        }
    }
#endif


    // calculate_xor_over_range
    for (int W = int(NUM_SAMPLES) + 1; 0 != W; --W)
    {
        if (int(NUM_SAMPLES) + 1 == W)
        {
            rows.clear();
        }

        stopwatch_t sw;

        ss_uint64_t anchor_value = 0;


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


        if (W <= int(NUM_SAMPLES))
        {
            rows.push(
                &int_uint8
            ,   &int_uint16
            ,   &int_uint32
            ,   &int_uint64
            ,   NULL
            ,   anchor_value
            );
        }

        if (1 == W)
        {
            rows.emit("calculate_xor_over_range()", true);
        }
    }


    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

