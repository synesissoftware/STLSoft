/* /////////////////////////////////////////////////////////////////////////
 * File:    test/performance/stlsoft/string/string_tokeniser/main.cpp
 *
 * Purpose: Perf-test for stlsoft::string_tokeniser.
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
#include <stlsoft/string/string_view.hpp>
#include <stlsoft/string/tokeniser_functions.hpp>
#include <stlsoft/stlsoft.h>

#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

using stlsoft::ss_sint64_t;
using stlsoft::ss_size_t;

typedef stlsoft::std_chrono_hrc_stopwatch                   stopwatch_t;
typedef stopwatch_t::interval_type                          interval_type;
typedef stlsoft::simple_string                              string_t;
typedef stlsoft::basic_string_view<char>                    view_t;


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
make_char_source_()
{
    string_t s;

    s.reserve(repeat_count_() * 6u);

    { for (ss_size_t i = 0; i != repeat_count_(); ++i)
    {
        s += "field,";
    }}

    return s;
}

string_t
make_crlf_source_()
{
    string_t s;

    s.reserve(repeat_count_() * 6u);

    { for (ss_size_t i = 0; i != repeat_count_(); ++i)
    {
        s += "line\r\n";
    }}

    return s;
}

string_t
make_prefix_source_()
{
    string_t s;

    s.reserve(repeat_count_() * 5u);

    { for (ss_size_t i = 0; i != repeat_count_(); ++i)
    {
        s += "aaaab";
    }}

    return s;
}

template <
    ss_typename_param_k S
,   ss_typename_param_k D
,   ss_typename_param_k B
,   ss_typename_param_k V
>
STLSOFT_NOINLINE
std::pair<interval_type, ss_sint64_t>
time_construct_and_walk_(
    S const&        source
,   D const&        delim
,   ss_size_t       iterations
)
{
    typedef stlsoft::string_tokeniser<S, D, B, V>           tokeniser_t;

    stopwatch_t     sw;
    ss_sint64_t     anchor = 0;

    for (int warm = 2; 0 != warm; --warm)
    {
        anchor = 0;

        sw.start();

        { for (ss_size_t i = 0; i != iterations; ++i)
        {
            tokeniser_t const tokens(source, delim);

            { for (ss_typename_type_k tokeniser_t::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
            {
                anchor += static_cast<ss_sint64_t>((*it).size());
            }}
        }}

        sw.stop();
    }

    return std::make_pair(sw.get_nanoseconds(), anchor);
}

template <
    ss_typename_param_k S
,   ss_typename_param_k D
,   ss_typename_param_k B
,   ss_typename_param_k V
>
STLSOFT_NOINLINE
std::pair<interval_type, ss_sint64_t>
time_walk_(
    S const&        source
,   D const&        delim
,   ss_size_t       iterations
)
{
    typedef stlsoft::string_tokeniser<S, D, B, V>           tokeniser_t;

    tokeniser_t const   tokens(source, delim);
    stopwatch_t         sw;
    ss_sint64_t         anchor = 0;

    for (int warm = 2; 0 != warm; --warm)
    {
        anchor = 0;

        sw.start();

        { for (ss_size_t i = 0; i != iterations; ++i)
        {
            { for (ss_typename_type_k tokeniser_t::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
            {
                anchor += static_cast<ss_sint64_t>((*it).size());
            }}
        }}

        sw.stop();
    }

    return std::make_pair(sw.get_nanoseconds(), anchor);
}

/* strtok and strtok_r write NULs into the buffer, so each pass recopies
 * the source into a scratch buffer allocated outside the timed loop.
 * find_next_token does not mutate, and is timed against the source itself.
 * The comma-separated source has no repeated delimiters, so all four
 * produce the same tokens as string_tokeniser with skip_blank_tokens<true>.
 */

STLSOFT_NOINLINE
std::pair<interval_type, ss_sint64_t>
time_strtok_(
    string_t const& source
,   ss_size_t       iterations
)
{
    std::vector<char>   scratch(source.size() + 1u);
    stopwatch_t         sw;
    ss_sint64_t         anchor = 0;

    for (int warm = 2; 0 != warm; --warm)
    {
        anchor = 0;

        sw.start();

        { for (ss_size_t i = 0; i != iterations; ++i)
        {
            ::memcpy(&scratch[0], source.c_str(), source.size() + 1u);

            { for (char* tok = ::strtok(&scratch[0], ","); NULL != tok; tok = ::strtok(NULL, ","))
            {
                anchor += static_cast<ss_sint64_t>(::strlen(tok));
            }}
        }}

        sw.stop();
    }

    return std::make_pair(sw.get_nanoseconds(), anchor);
}

STLSOFT_NOINLINE
std::pair<interval_type, ss_sint64_t>
time_strtok_r_(
    string_t const& source
,   ss_size_t       iterations
)
{
    std::vector<char>   scratch(source.size() + 1u);
    stopwatch_t         sw;
    ss_sint64_t         anchor = 0;

    for (int warm = 2; 0 != warm; --warm)
    {
        anchor = 0;

        sw.start();

        { for (ss_size_t i = 0; i != iterations; ++i)
        {
            ::memcpy(&scratch[0], source.c_str(), source.size() + 1u);

            char* save = NULL;

#if defined(_WIN32)
            { for (char* tok = ::strtok_s(&scratch[0], ",", &save); NULL != tok; tok = ::strtok_s(NULL, ",", &save))
#else
            { for (char* tok = ::strtok_r(&scratch[0], ",", &save); NULL != tok; tok = ::strtok_r(NULL, ",", &save))
#endif
            {
                anchor += static_cast<ss_sint64_t>(::strlen(tok));
            }}
        }}

        sw.stop();
    }

    return std::make_pair(sw.get_nanoseconds(), anchor);
}

STLSOFT_NOINLINE
std::pair<interval_type, ss_sint64_t>
time_find_next_token_nul_(
    string_t const& source
,   ss_size_t       iterations
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
            char const* p0 = source.c_str();
            char const* p1 = p0;

            { for (; stlsoft::find_next_token(p0, p1, ','); )
            {
                anchor += static_cast<ss_sint64_t>(p1 - p0);
            }}
        }}

        sw.stop();
    }

    return std::make_pair(sw.get_nanoseconds(), anchor);
}

STLSOFT_NOINLINE
std::pair<interval_type, ss_sint64_t>
time_find_next_token_end_(
    string_t const& source
,   ss_size_t       iterations
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
            char const* const   end = source.c_str() + source.size();
            char const*         p0  = source.c_str();
            char const*         p1  = p0;

            { for (;;)
            {
                stlsoft::find_next_token(p0, p1, end, ',');

                if (p0 == p1)
                {
                    break;
                }

                anchor += static_cast<ss_sint64_t>(p1 - p0);

                if (p1 == end)
                {
                    break;
                }
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

/* ns/step divides the measured pass by the number of tokens yielded. */

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

    string_t const      char_source     =   make_char_source_();
    string_t const      crlf_source     =   make_crlf_source_();
    string_t const      prefix_source   =   make_prefix_source_();
    string_t const      crlf_delim("\r\n");
    string_t const      prefix_delim("aaaac");
    view_t const        char_view(char_source.data(), char_source.size());
    view_t const        crlf_view(crlf_source.data(), crlf_source.size());
    view_t const        prefix_view(prefix_source.data(), prefix_source.size());
    ss_size_t const     owning_n        =   20u * scale;
    ss_size_t const     view_n          =   100u * scale;
    ss_size_t const     prefix_n        =   10u * scale;
    ss_size_t const     char_steps      =   repeat_count_();
    ss_size_t const     crlf_steps      =   repeat_count_();
    ss_size_t const     prefix_steps    =   1u;

    display_header_(std::cout);

    display_results_(
        std::cout
    ,   "char owning construct+walk"
    ,   owning_n
    ,   char_steps
    ,   time_construct_and_walk_<string_t, char, stlsoft::skip_blank_tokens<true>, string_t>(char_source, ',', owning_n)
    );
    display_results_(
        std::cout
    ,   "char owning S=view ctor+walk"
    ,   owning_n
    ,   char_steps
    ,   time_construct_and_walk_<view_t, char, stlsoft::skip_blank_tokens<true>, string_t>(char_view, ',', owning_n)
    );
    display_results_(
        std::cout
    ,   "char owning walk"
    ,   view_n
    ,   char_steps
    ,   time_walk_<string_t, char, stlsoft::skip_blank_tokens<true>, string_t>(char_source, ',', view_n)
    );
    display_results_(
        std::cout
    ,   "char view construct+walk"
    ,   view_n
    ,   char_steps
    ,   time_construct_and_walk_<string_t, char, stlsoft::skip_blank_tokens<true>, view_t>(char_source, ',', view_n)
    );
    display_results_(
        std::cout
    ,   "char view S=view ctor+walk"
    ,   view_n
    ,   char_steps
    ,   time_construct_and_walk_<view_t, char, stlsoft::skip_blank_tokens<true>, view_t>(char_view, ',', view_n)
    );
    display_results_(
        std::cout
    ,   "char view walk"
    ,   view_n
    ,   char_steps
    ,   time_walk_<string_t, char, stlsoft::skip_blank_tokens<true>, view_t>(char_source, ',', view_n)
    );
    display_results_(
        std::cout
    ,   "find_next_token end"
    ,   view_n
    ,   char_steps
    ,   time_find_next_token_end_(char_source, view_n)
    );
    display_results_(
        std::cout
    ,   "find_next_token nul"
    ,   view_n
    ,   char_steps
    ,   time_find_next_token_nul_(char_source, view_n)
    );
    display_results_(
        std::cout
    ,   "strtok copy+walk"
    ,   view_n
    ,   char_steps
    ,   time_strtok_(char_source, view_n)
    );
    display_results_(
        std::cout
#if defined(_WIN32)
    ,   "strtok_s copy+walk"
#else
    ,   "strtok_r copy+walk"
#endif
    ,   view_n
    ,   char_steps
    ,   time_strtok_r_(char_source, view_n)
    );
    display_results_(
        std::cout
    ,   "crlf owning construct+walk"
    ,   owning_n
    ,   crlf_steps
    ,   time_construct_and_walk_<string_t, string_t, stlsoft::skip_blank_tokens<true>, string_t>(crlf_source, crlf_delim, owning_n)
    );
    display_results_(
        std::cout
    ,   "crlf owning S=view ctor+walk"
    ,   owning_n
    ,   crlf_steps
    ,   time_construct_and_walk_<view_t, string_t, stlsoft::skip_blank_tokens<true>, string_t>(crlf_view, crlf_delim, owning_n)
    );
    display_results_(
        std::cout
    ,   "crlf view construct+walk"
    ,   view_n
    ,   crlf_steps
    ,   time_construct_and_walk_<string_t, string_t, stlsoft::skip_blank_tokens<true>, view_t>(crlf_source, crlf_delim, view_n)
    );
    display_results_(
        std::cout
    ,   "crlf view S=view ctor+walk"
    ,   view_n
    ,   crlf_steps
    ,   time_construct_and_walk_<view_t, string_t, stlsoft::skip_blank_tokens<true>, view_t>(crlf_view, crlf_delim, view_n)
    );
    display_results_(
        std::cout
    ,   "prefix owning construct+walk"
    ,   prefix_n
    ,   prefix_steps
    ,   time_construct_and_walk_<string_t, string_t, stlsoft::skip_blank_tokens<true>, string_t>(prefix_source, prefix_delim, prefix_n)
    );
    display_results_(
        std::cout
    ,   "prefix owning S=view ctor+walk"
    ,   prefix_n
    ,   prefix_steps
    ,   time_construct_and_walk_<view_t, string_t, stlsoft::skip_blank_tokens<true>, string_t>(prefix_view, prefix_delim, prefix_n)
    );

    return EXIT_SUCCESS;
}

/* ///////////////////////////// end of file //////////////////////////// */

