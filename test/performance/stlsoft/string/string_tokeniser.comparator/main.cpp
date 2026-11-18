/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/stlsoft/string/string_tokeniser.comparator/main.cpp
 *
 * Purpose: Perf-test for stlsoft::string_tokeniser_comparator.
 *
 * Created: 18th November 2026
 * Updated: 18th November 2026
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

#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>
#include <stlsoft/string/simple_string.hpp>
#include <stlsoft/string/string_tokeniser.hpp>
#include <stlsoft/stlsoft.h>

#include <iomanip>
#include <iostream>
#include <utility>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

using stlsoft::ss_sint64_t;
using stlsoft::ss_size_t;

typedef stlsoft::std_chrono_hrc_stopwatch                   stopwatch_t;
typedef stopwatch_t::interval_type                          interval_type;
typedef stlsoft::simple_string                              string_t;
typedef stlsoft::string_tokeniser_type_traits<
    string_t
,   string_t
>                                                           traits_t;
typedef stlsoft::string_tokeniser_comparator<
    char
,   string_t
,   traits_t
>                                                           char_comparator_t;
typedef stlsoft::string_tokeniser_comparator<
    string_t
,   string_t
,   traits_t
>                                                           string_comparator_t;

struct char_not_equal_fn_
{
    stlsoft::ss_bool_t
    operator ()(
        char const&     delim
    ,   char const*&    it
    ) const
    {
        return char_comparator_t::not_equal(delim, it);
    }
};

struct string_not_equal_fn_
{
    stlsoft::ss_bool_t
    operator ()(
        string_t const& delim
    ,   char const*&    it
    ) const
    {
        return string_comparator_t::not_equal(delim, it);
    }
};


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

int const   scenario_width_         =   32;
int const   nanos_width_            =   14;
int const   iterations_width_       =   12;
int const   per_iteration_width_    =   14;
int const   per_step_width_         =   12;
int const   anchor_width_           =   12;


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

namespace {

ss_size_t
repeat_count_()
{
    return 20000u;
}

string_t
make_filled_(
    char        ch
,   ss_size_t   n
)
{
    string_t s;

    s.reserve(n);

    { for (ss_size_t i = 0; i != n; ++i)
    {
        s += ch;
    }}

    return s;
}

string_t
make_repeated_(
    char const* piece
)
{
    string_t s;

    s.reserve(repeat_count_() * 5u);

    { for (ss_size_t i = 0; repeat_count_() != i; ++i)
    {
        s += piece;
    }}

    return s;
}

/* Calls not_equal() at every character. Each probe stays inside the
 * buffer: a mismatch returns before reading past the matched prefix, and
 * every pattern below is an exact number of complete groups.
 */
template<
    ss_typename_param_k D
,   ss_typename_param_k T_notEqual
>
STLSOFT_NOINLINE
std::pair<interval_type, ss_sint64_t>
time_not_equal_(
    string_t const& source
,   D const&        delim
,   ss_size_t       iterations
,   T_notEqual      not_equal_fn
)
{
    stopwatch_t sw;
    ss_sint64_t anchor = 0;

    for (int warm = 2; 0 != warm; --warm)
    {
        anchor = 0;

        sw.start();

        { for (ss_size_t i = 0; i != iterations; ++i)
        {
            char const* const   end = source.data() + source.size();

            { for (char const* it = source.data(); it != end; ++it)
            {
                char const* p = it;

                anchor += not_equal_fn(delim, p) ? 1 : 0;
            }}
        }}

        sw.stop();
    }

    return std::make_pair(sw.get_nanoseconds(), anchor);
}

void
display_header_(
    std::ostream& stm
)
{
    stm
        << std::setfill(' ')
        << std::left << std::setw(scenario_width_) << "scenario"
        << "  "
        << std::right << std::setw(nanos_width_) << "nanoseconds"
        << "  "
        << std::setw(iterations_width_) << "iterations"
        << "  "
        << std::setw(per_iteration_width_) << "ns/iteration"
        << "  "
        << std::setw(per_step_width_) << "ns/step"
        << "  "
        << std::setw(anchor_width_) << "anchor"
        << std::endl;
}

/* ns/step divides the measured pass by the number of not_equal() calls. */

void
display_results_(
    std::ostream&                                   stm
,   char const*                                     scenario_name
,   ss_size_t                                       iterations
,   ss_size_t                                       steps_per_pass
,   std::pair<interval_type, ss_sint64_t> const&    result
)
{
    double const    passes  =   static_cast<double>(iterations);
    double const    steps   =   passes * static_cast<double>(steps_per_pass);

    stm
        << std::setfill(' ')
        << std::left << std::setw(scenario_width_) << scenario_name
        << "  "
        << std::right << std::setw(nanos_width_) << result.first
        << "  "
        << std::setw(iterations_width_) << iterations
        << "  "
        << std::setw(per_iteration_width_) << std::fixed << std::setprecision(1) << (static_cast<double>(result.first) / passes)
        << "  "
        << std::setw(per_step_width_) << std::setprecision(3) << (static_cast<double>(result.first) / steps)
        << "  "
        << std::setw(anchor_width_) << result.second
        << std::endl;
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    ss_size_t const scale = (1 < argc) ? static_cast<ss_size_t>(::strtoul(argv[1], NULL, 10)) : 1u;

    if (0u == scale)
    {
        std::cerr << argv[0] << ": scale must be a positive integer" << std::endl;

        return EXIT_FAILURE;
    }

    ss_size_t const     n           =   100u * scale;
    string_t const      letters     =   make_filled_('x', repeat_count_() * 6u);
    string_t const      near_match  =   make_repeated_("aaaab");
    string_t const      full_match  =   make_repeated_("aaaac");
    string_t const      early_delim("YZ");
    string_t const      late_delim("aaaac");

    display_header_(std::cout);

    display_results_(
        std::cout
    ,   "char mismatch"
    ,   n
    ,   letters.size()
    ,   time_not_equal_(letters, ',', n, char_not_equal_fn_())
    );
    display_results_(
        std::cout
    ,   "string mismatch first"
    ,   n
    ,   letters.size()
    ,   time_not_equal_(letters, early_delim, n, string_not_equal_fn_())
    );
    display_results_(
        std::cout
    ,   "string mismatch last"
    ,   n
    ,   near_match.size()
    ,   time_not_equal_(near_match, late_delim, n, string_not_equal_fn_())
    );
    display_results_(
        std::cout
    ,   "string full match"
    ,   n
    ,   full_match.size()
    ,   time_not_equal_(full_match, late_delim, n, string_not_equal_fn_())
    );

    return EXIT_SUCCESS;
}

/* ///////////////////////////// end of file //////////////////////////// */
