/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/stlsoft/string/c_string/main.cpp
 *
 * Purpose: Perf-test for stlsoft/string/c_string functions.
 *
 * Created: 20th October 2026
 * Updated: 20th October 2026
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
 * includes
 */

#include <stlsoft/string/c_string/strnchr.h>
#include <stlsoft/string/c_string/strnicmp.h>
#include <stlsoft/string/c_string/strnistrn.h>
#include <stlsoft/string/c_string/strnpbrkn.h>
#include <stlsoft/string/c_string/strnrchr.h>
#include <stlsoft/string/c_string/strnstrn.h>

#if __cplusplus >= 201103L
# include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>
#else
# include <platformstl/diagnostics/stopwatch.hpp>
#endif /* C++11+ */
#include <stlsoft/conversion/number/grouping_functions.hpp>

#include "perf_group_gaps.hpp"

#include <iomanip>
#include <iostream>
#include <string>

#include <stdlib.h>
#include <string.h>
#if !defined(_WIN32)
# include <strings.h>
#endif /* !_WIN32 */


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

#if __cplusplus >= 201103L

typedef stlsoft::std_chrono_hrc_stopwatch                   stopwatch_t;
#else

typedef platformstl::stopwatch                              stopwatch_t;
#endif /* C++11+ */
typedef stopwatch_t::interval_type                          interval_t;

using stlsoft::ss_sint64_t;
using stlsoft::ss_size_t;

typedef ss_sint64_t (*timed_fn_t)();


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

    ss_size_t const NUM_ITERATIONS  = 1000000;
    ss_size_t const HAY_N           = 96;
    int const       FN_COL          = 22;
    int const       SC_COL          = 12;
    int const       NS_COL          = 16;
    int const       AN_COL          = 16;

    char const      PATTERN[]       = "The Quick Brown Fox Jumps Over The Lazy Dog!!";
    ss_size_t const CMP_N           = sizeof(PATTERN) - 1;

    char const      NEEDLE_EARLY[]  = "brown";
    char const      NEEDLE_LATE[]   = "jumps";
    char const      NEEDLE_MISS[]   = "####";
    char const      NEEDLE_EARLY_CI[] = "BROWN";
    char const      NEEDLE_LATE_CI[]  = "JUMPS";

    char const      SET_EARLY[]     = "xyzQ";
    char const      SET_LATE[]      = "xyzZ";
    char const      SET_MISS[]      = "xyz#";

    ss_size_t const IX_EARLY_CH     = 3;
    ss_size_t const IX_LATE_CH      = HAY_N - 4;
    ss_size_t const IX_EARLY_ND     = 8;
    ss_size_t const IX_LATE_ND      = HAY_N - 12;

    char            haystack[128];
    char            cmp_lhs[64];
    char            cmp_rhs_equal[64];
    char            cmp_rhs_early[64];
    char            cmp_rhs_late[64];

#if defined(_WIN32)
    char const      BASELINE_STRNICMP_NAME[] = "_strnicmp";
#else
    char const      BASELINE_STRNICMP_NAME[] = "strncasecmp";
#endif
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

/* Times the char forms of the c_string helpers on one fixed haystack. Where
 * a C-library function does the same work it is timed beside the helper:
 * memchr, strpbrk, strstr, and strncasecmp or _strnicmp. strnrchr is timed
 * beside a local reverse scan. strnistrn is timed on its own.
 */

namespace {

    STLSOFT_STATIC_ASSERT(CMP_N < sizeof(cmp_lhs));
    STLSOFT_STATIC_ASSERT(HAY_N + 1 <= sizeof(haystack));
    STLSOFT_STATIC_ASSERT(IX_EARLY_ND + 5 <= IX_LATE_ND);
    STLSOFT_STATIC_ASSERT(IX_LATE_ND + 5 <= IX_LATE_CH);


    template <ss_typename_param_k T_integer>
    std::string
    thousands(
        T_integer const& v
    )
    {
        char    dest[41];
        size_t  n = stlsoft::format_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3;0", v);

        /* format_thousands() counts the terminating NUL. */
        if (0 != n)
        {
            --n;
        }

        return std::string(dest, n);
    }

    char
    flip_alpha_case(
        char c
    )
    {
        if ('a' <= c && c <= 'z')
        {
            return static_cast<char>(c - 'a' + 'A');
        }

        if ('A' <= c && c <= 'Z')
        {
            return static_cast<char>(c - 'A' + 'a');
        }

        return c;
    }

    ss_sint64_t
    ptr_anchor(
        char const* base
    ,   void const* p
    )
    {
        if (NULL == p)
        {
            return -1;
        }

        return static_cast<ss_sint64_t>(static_cast<char const*>(p) - base);
    }

    ss_sint64_t
    sign_of(
        int r
    )
    {
        if (0 < r)
        {
            return +1;
        }

        if (r < 0)
        {
            return -1;
        }

        return 0;
    }

    char const*
    local_strnrchr(
        char const* s
    ,   size_t      n
    ,   int         ch
    )
    {
        if (0 != n)
        {
            size_t      i;
            char const* p;

            for (i = 0, p = s + (n - 1); i != n; ++i, --p)
            {
                if (ch == *p)
                {
                    return p;
                }
            }
        }

        return NULL;
    }

    int
    baseline_strnicmp(
        char const* s1
    ,   char const* s2
    ,   size_t      n
    )
    {
#if defined(_WIN32)

        return ::_strnicmp(s1, s2, n);
#else

        return ::strncasecmp(s1, s2, n);
#endif
    }

    void
    prepare_inputs()
    {
        ::memset(haystack, 'a', sizeof(haystack));

        haystack[HAY_N] = '\0';
        haystack[IX_EARLY_CH] = 'Q';
        haystack[IX_LATE_CH] = 'Z';
        ::memcpy(haystack + IX_EARLY_ND, NEEDLE_EARLY, sizeof(NEEDLE_EARLY) - 1);
        ::memcpy(haystack + IX_LATE_ND, NEEDLE_LATE, sizeof(NEEDLE_LATE) - 1);

        ::memcpy(cmp_lhs, PATTERN, CMP_N);
        cmp_lhs[CMP_N] = '\0';

        for (ss_size_t i = 0; CMP_N != i; ++i)
        {
            cmp_rhs_equal[i] = flip_alpha_case(cmp_lhs[i]);
        }

        cmp_rhs_equal[CMP_N] = '\0';

        ::memcpy(cmp_rhs_early, cmp_rhs_equal, CMP_N + 1);
        ::memcpy(cmp_rhs_late, cmp_rhs_equal, CMP_N + 1);
        cmp_rhs_early[0] = '#';
        cmp_rhs_late[CMP_N - 1] = '#';
    }


    ss_sint64_t fn_strnicmp_stl_early()
    {
        return sign_of(stlsoft_C_strnicmp(cmp_lhs, cmp_rhs_early, CMP_N));
    }

    ss_sint64_t fn_strnicmp_crt_early()
    {
        return sign_of(baseline_strnicmp(cmp_lhs, cmp_rhs_early, CMP_N));
    }

    ss_sint64_t fn_strnicmp_stl_late()
    {
        return sign_of(stlsoft_C_strnicmp(cmp_lhs, cmp_rhs_late, CMP_N));
    }

    ss_sint64_t fn_strnicmp_crt_late()
    {
        return sign_of(baseline_strnicmp(cmp_lhs, cmp_rhs_late, CMP_N));
    }

    ss_sint64_t fn_strnicmp_stl_equal()
    {
        return sign_of(stlsoft_C_strnicmp(cmp_lhs, cmp_rhs_equal, CMP_N));
    }

    ss_sint64_t fn_strnicmp_crt_equal()
    {
        return sign_of(baseline_strnicmp(cmp_lhs, cmp_rhs_equal, CMP_N));
    }

    ss_sint64_t fn_strnchr_stl_start()
    {
        return ptr_anchor(haystack, stlsoft_C_strnchr(haystack, HAY_N, 'Q'));
    }

    ss_sint64_t fn_strnchr_crt_start()
    {
        return ptr_anchor(haystack, ::memchr(haystack, 'Q', HAY_N));
    }

    ss_sint64_t fn_strnchr_stl_end()
    {
        return ptr_anchor(haystack, stlsoft_C_strnchr(haystack, HAY_N, 'Z'));
    }

    ss_sint64_t fn_strnchr_crt_end()
    {
        return ptr_anchor(haystack, ::memchr(haystack, 'Z', HAY_N));
    }

    ss_sint64_t fn_strnchr_stl_miss()
    {
        return ptr_anchor(haystack, stlsoft_C_strnchr(haystack, HAY_N, '#'));
    }

    ss_sint64_t fn_strnchr_crt_miss()
    {
        return ptr_anchor(haystack, ::memchr(haystack, '#', HAY_N));
    }

    ss_sint64_t fn_strnistrn_stl_start()
    {
        return ptr_anchor(haystack, stlsoft_C_strnistrn(haystack, HAY_N, NEEDLE_EARLY_CI, sizeof(NEEDLE_EARLY_CI) - 1));
    }

    ss_sint64_t fn_strnistrn_stl_end()
    {
        return ptr_anchor(haystack, stlsoft_C_strnistrn(haystack, HAY_N, NEEDLE_LATE_CI, sizeof(NEEDLE_LATE_CI) - 1));
    }

    ss_sint64_t fn_strnistrn_stl_miss()
    {
        return ptr_anchor(haystack, stlsoft_C_strnistrn(haystack, HAY_N, NEEDLE_MISS, sizeof(NEEDLE_MISS) - 1));
    }

    ss_sint64_t fn_strnpbrkn_stl_start()
    {
        return ptr_anchor(haystack, stlsoft_C_strnpbrkn(haystack, HAY_N, SET_EARLY, sizeof(SET_EARLY) - 1));
    }

    ss_sint64_t fn_strnpbrkn_crt_start()
    {
        return ptr_anchor(haystack, ::strpbrk(haystack, SET_EARLY));
    }

    ss_sint64_t fn_strnpbrkn_stl_end()
    {
        return ptr_anchor(haystack, stlsoft_C_strnpbrkn(haystack, HAY_N, SET_LATE, sizeof(SET_LATE) - 1));
    }

    ss_sint64_t fn_strnpbrkn_crt_end()
    {
        return ptr_anchor(haystack, ::strpbrk(haystack, SET_LATE));
    }

    ss_sint64_t fn_strnpbrkn_stl_miss()
    {
        return ptr_anchor(haystack, stlsoft_C_strnpbrkn(haystack, HAY_N, SET_MISS, sizeof(SET_MISS) - 1));
    }

    ss_sint64_t fn_strnpbrkn_crt_miss()
    {
        return ptr_anchor(haystack, ::strpbrk(haystack, SET_MISS));
    }

    ss_sint64_t fn_strnrchr_stl_start()
    {
        return ptr_anchor(haystack, stlsoft_C_strnrchr(haystack, HAY_N, 'Q'));
    }

    ss_sint64_t fn_strnrchr_loc_start()
    {
        return ptr_anchor(haystack, local_strnrchr(haystack, HAY_N, 'Q'));
    }

    ss_sint64_t fn_strnrchr_stl_end()
    {
        return ptr_anchor(haystack, stlsoft_C_strnrchr(haystack, HAY_N, 'Z'));
    }

    ss_sint64_t fn_strnrchr_loc_end()
    {
        return ptr_anchor(haystack, local_strnrchr(haystack, HAY_N, 'Z'));
    }

    ss_sint64_t fn_strnrchr_stl_miss()
    {
        return ptr_anchor(haystack, stlsoft_C_strnrchr(haystack, HAY_N, '#'));
    }

    ss_sint64_t fn_strnrchr_loc_miss()
    {
        return ptr_anchor(haystack, local_strnrchr(haystack, HAY_N, '#'));
    }

    ss_sint64_t fn_strnstrn_stl_start()
    {
        return ptr_anchor(haystack, stlsoft_C_strnstrn(haystack, HAY_N, NEEDLE_EARLY, sizeof(NEEDLE_EARLY) - 1));
    }

    ss_sint64_t fn_strnstrn_crt_start()
    {
        return ptr_anchor(haystack, ::strstr(haystack, NEEDLE_EARLY));
    }

    ss_sint64_t fn_strnstrn_stl_end()
    {
        return ptr_anchor(haystack, stlsoft_C_strnstrn(haystack, HAY_N, NEEDLE_LATE, sizeof(NEEDLE_LATE) - 1));
    }

    ss_sint64_t fn_strnstrn_crt_end()
    {
        return ptr_anchor(haystack, ::strstr(haystack, NEEDLE_LATE));
    }

    ss_sint64_t fn_strnstrn_stl_miss()
    {
        return ptr_anchor(haystack, stlsoft_C_strnstrn(haystack, HAY_N, NEEDLE_MISS, sizeof(NEEDLE_MISS) - 1));
    }

    ss_sint64_t fn_strnstrn_crt_miss()
    {
        return ptr_anchor(haystack, ::strstr(haystack, NEEDLE_MISS));
    }


    struct row_spec
    {
        char const* group;
        char const* function_name;
        char const* scenario;
        timed_fn_t  fn;
    };

    row_spec const ROWS[] =
    {
        { "strnicmp",   "stlsoft_C_strnicmp",   "differ-early", fn_strnicmp_stl_early, },
        { "strnicmp",   BASELINE_STRNICMP_NAME, "differ-early", fn_strnicmp_crt_early, },
        { "strnicmp",   "stlsoft_C_strnicmp",   "differ-late",  fn_strnicmp_stl_late, },
        { "strnicmp",   BASELINE_STRNICMP_NAME, "differ-late",  fn_strnicmp_crt_late, },
        { "strnicmp",   "stlsoft_C_strnicmp",   "equal",        fn_strnicmp_stl_equal, },
        { "strnicmp",   BASELINE_STRNICMP_NAME, "equal",        fn_strnicmp_crt_equal, },

        { "strnchr",    "stlsoft_C_strnchr",    "near-start",   fn_strnchr_stl_start, },
        { "strnchr",    "memchr",               "near-start",   fn_strnchr_crt_start, },
        { "strnchr",    "stlsoft_C_strnchr",    "near-end",     fn_strnchr_stl_end, },
        { "strnchr",    "memchr",               "near-end",     fn_strnchr_crt_end, },
        { "strnchr",    "stlsoft_C_strnchr",    "miss",         fn_strnchr_stl_miss, },
        { "strnchr",    "memchr",               "miss",         fn_strnchr_crt_miss, },

        { "strnistrn",  "stlsoft_C_strnistrn",  "near-start",   fn_strnistrn_stl_start, },
        { "strnistrn",  "stlsoft_C_strnistrn",  "near-end",     fn_strnistrn_stl_end, },
        { "strnistrn",  "stlsoft_C_strnistrn",  "miss",         fn_strnistrn_stl_miss, },

        { "strnpbrkn",  "stlsoft_C_strnpbrkn",  "near-start",   fn_strnpbrkn_stl_start, },
        { "strnpbrkn",  "strpbrk",              "near-start",   fn_strnpbrkn_crt_start, },
        { "strnpbrkn",  "stlsoft_C_strnpbrkn",  "near-end",     fn_strnpbrkn_stl_end, },
        { "strnpbrkn",  "strpbrk",              "near-end",     fn_strnpbrkn_crt_end, },
        { "strnpbrkn",  "stlsoft_C_strnpbrkn",  "miss",         fn_strnpbrkn_stl_miss, },
        { "strnpbrkn",  "strpbrk",              "miss",         fn_strnpbrkn_crt_miss, },

        { "strnrchr",   "stlsoft_C_strnrchr",   "near-start",   fn_strnrchr_stl_start, },
        { "strnrchr",   "local_strnrchr",       "near-start",   fn_strnrchr_loc_start, },
        { "strnrchr",   "stlsoft_C_strnrchr",   "near-end",     fn_strnrchr_stl_end, },
        { "strnrchr",   "local_strnrchr",       "near-end",     fn_strnrchr_loc_end, },
        { "strnrchr",   "stlsoft_C_strnrchr",   "miss",         fn_strnrchr_stl_miss, },
        { "strnrchr",   "local_strnrchr",       "miss",         fn_strnrchr_loc_miss, },

        { "strnstrn",   "stlsoft_C_strnstrn",   "near-start",   fn_strnstrn_stl_start, },
        { "strnstrn",   "strstr",               "near-start",   fn_strnstrn_crt_start, },
        { "strnstrn",   "stlsoft_C_strnstrn",   "near-end",     fn_strnstrn_stl_end, },
        { "strnstrn",   "strstr",               "near-end",     fn_strnstrn_crt_end, },
        { "strnstrn",   "stlsoft_C_strnstrn",   "miss",         fn_strnstrn_stl_miss, },
        { "strnstrn",   "strstr",               "miss",         fn_strnstrn_crt_miss, },
    };


    interval_t
    time_calls(
        timed_fn_t      fn
    ,   ss_sint64_t&    anchor
    )
    {
        /* Volatile reload keeps the call in the loop. The callee is an
         * indirect target, so the scan is not hoisted out of the timing.
         */
        timed_fn_t volatile vf = fn;
        stopwatch_t         sw;
        ss_sint64_t         local = 0;

        sw.start();

        for (ss_size_t i = 0; NUM_ITERATIONS != i; ++i)
        {
            timed_fn_t const call = vf;

            local += call();
        }

        sw.stop();

        anchor = local;

        return sw.get_nanoseconds();
    }

    void
    emit_header()
    {
        std::cout
            << '\t'
            << std::setw(FN_COL) << std::left << "function"
            << '\t'
            << std::setw(SC_COL) << std::left << "scenario"
            << '\t'
            << std::setw(NS_COL) << std::right << "nanoseconds"
            << '\t'
            << std::setw(AN_COL) << std::right << "anchor"
            << std::endl;
    }

    void
    emit_row(
        char const* function_name
    ,   char const* scenario
    ,   interval_t  nanoseconds
    ,   ss_sint64_t anchor
    )
    {
        std::cout
            << '\t'
            << std::setw(FN_COL) << std::left << function_name
            << '\t'
            << std::setw(SC_COL) << std::left << scenario
            << '\t'
            << std::setw(NS_COL) << std::right << thousands(nanoseconds)
            << '\t'
            << std::setw(AN_COL) << std::right << thousands(anchor)
            << std::endl;
    }

    void
    measure(
        row_spec const& row
    )
    {
        interval_t  ns = 0;
        ss_sint64_t anchor = 0;

        perf_maybe_emit_group_gap(std::cout, row.group);

        for (int w = 2; 0 != w; --w)
        {
            ns = time_calls(row.fn, anchor);
        }

        emit_row(row.function_name, row.scenario, ns, anchor);
    }
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int /*argc*/, char* /*argv*/[])
{
    prepare_inputs();

    perf_maybe_emit_groupgaps_banner(std::cout);

    std::cout
        << "c_string"
        << "\titerations=" << thousands(NUM_ITERATIONS)
        << "\thaystack=" << HAY_N
        << "\tcompare=" << CMP_N
        << std::endl;

    emit_header();

    for (ss_size_t i = 0; i != STLSOFT_NUM_ELEMENTS(ROWS); ++i)
    {
        measure(ROWS[i]);
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

