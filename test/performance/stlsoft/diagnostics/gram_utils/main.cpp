/* /////////////////////////////////////////////////////////////////////////
 * File:    gram_utils/main.cpp
 *
 * Purpose: Perf-test for gram_utils
 *
 * Created: 17th December 2024
 * Updated: 30th September 2026
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

#include <stlsoft/diagnostics/gram_utils.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* STLSoft header files */
#include <stlsoft/diagnostics/doomgram.hpp>
#if __cplusplus >= 201103L
# include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>
#else
# include <platformstl/diagnostics/stopwatch.hpp>
#endif /* C++11+ */
#include <stlsoft/conversion/number/grouping_functions.hpp>

#include "perf_group_gaps.hpp"

/* Standard header files */

#include <iomanip>
#include <iostream>

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

using stlsoft::ss_size_t;


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

    ss_size_t const NUM_ITERATIONS = 10000000;
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
    char    dest[41];
    size_t  n = stlsoft::format_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3;0", v);

    return std::string(dest, n);
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int /*argc*/, char* /*argv*/[])
{
    perf_maybe_emit_groupgaps_banner(std::cout);

    stopwatch_t sw;

    for (int W = 2; 0 != W; --W)
    {
        sw.start();

        unsigned anchor_value = 0;

        for (unsigned i = 0; NUM_ITERATIONS != i; ++i)
        {
            anchor_value += stlsoft::calc_doom(i);
        }

        sw.stop();

        if (1 == W)
        {
            std::cout
                << '\t'
                << std::setw(20) << std::right << thousands(sw.get_nanoseconds())
                << '\t'
                << anchor_value
                << std::endl;
        }
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

