/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.limits.integral_limits/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::integral_limits`.
 *
 * Created: 21st November 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/limits/integral_limits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <limits>
#if __cplusplus >= 201402L
# include <sstream>
#endif

/* Standard C header files */
#include <limits.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_min_max();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.limits.integral_limits", verbosity))
    {
        XTESTS_RUN_CASE(test_min_max);


        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

struct int_wrapper
{
    typedef int                                             value_type;

    int value;
};

namespace stlsoft {

    template <>
    struct integral_limits<int_wrapper>
    {
        typedef int_wrapper                                 value_type;

        /** Returns the minimum value for the type */
        static value_type minimum()
        {
            int_wrapper w = { INT_MIN };

            return w;
        }
        /** Returns the maximum value for the type */
        static value_type maximum()
        {
            int_wrapper w = { INT_MAX };

            return w;
        }
    };
} // namespace stlsoft


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::ss_sint32_t;
    using stlsoft::ss_uint64_t;


static void test_min_max()
{
    {
        typedef signed int                                  int_t;
        typedef stlsoft::integral_limits<int_t>             limits_t;

        TEST_INT_EQ(std::numeric_limits<int_t>::min(), limits_t::minimum());
        TEST_INT_EQ(std::numeric_limits<int_t>::max(), limits_t::maximum());
    }

    {
        typedef unsigned long                               int_t;
        typedef stlsoft::integral_limits<int_t>             limits_t;

        TEST_INT_EQ(std::numeric_limits<int_t>::min(), limits_t::minimum());
        TEST_INT_EQ(std::numeric_limits<int_t>::max(), limits_t::maximum());
    }

    {
        typedef signed short                                int_t;
        typedef stlsoft::integral_limits<int_t>             limits_t;

        TEST_INT_EQ(std::numeric_limits<int_t>::min(), limits_t::minimum());
        TEST_INT_EQ(std::numeric_limits<int_t>::max(), limits_t::maximum());
    }

    {
        typedef ss_uint64_t                                 int_t;
        typedef stlsoft::integral_limits<int_t>             limits_t;

        TEST_INT_EQ(std::numeric_limits<int_t>::min(), limits_t::minimum());
        TEST_INT_EQ(std::numeric_limits<int_t>::max(), limits_t::maximum());
    }

    {
        typedef int_wrapper                                 int_t;
        typedef stlsoft::integral_limits<int_t>             limits_t;

        TEST_INT_EQ(std::numeric_limits<int_t::value_type>::min(), limits_t::minimum().value);
        TEST_INT_EQ(std::numeric_limits<int_t::value_type>::max(), limits_t::maximum().value);
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

