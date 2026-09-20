/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.traits.integral_traits/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::integral_traits`.
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

#include <stlsoft/traits/integral_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/limits/integral_limits.hpp>
#include <stlsoft/meta/is_same_type.hpp>

/* Standard C++ header files */
#include <limits>
#if __cplusplus >= 201402L
# include <sstream>
#endif

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_1();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.traits.integral_traits", verbosity))
    {
        XTESTS_RUN_CASE(test_1);


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
    struct integral_traits<int_wrapper>
    {
        typedef int_wrapper                                 integer_type;
        typedef int                                         underlying_type;

        static
        underlying_type
        get_underlying_value(
            integer_type const& value
        ) STLSOFT_NOEXCEPT
        {
            return value.value;
        }

        static
        integer_type
        from_underlying_type(
            underlying_type const& value
        )
        {
            int_wrapper w = { value };

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


static void test_1()
{
    {
        typedef signed char                                 int_t;
        typedef stlsoft::integral_traits<int_t>             traits_t;

        STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<traits_t::integer_type, traits_t::underlying_type>::value));

        TEST_INT_EQ(123, traits_t::get_underlying_value(123));
        TEST_INT_EQ(123, traits_t::from_underlying_type(123));
    }

    {
        typedef unsigned int                                int_t;
        typedef stlsoft::integral_traits<int_t>             traits_t;

        STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<traits_t::integer_type, traits_t::underlying_type>::value));

        TEST_INT_EQ(12345678u, traits_t::get_underlying_value(12345678));
        TEST_INT_EQ(12345678u, traits_t::from_underlying_type(12345678));
    }

    {
        typedef signed long long                            int_t;
        typedef stlsoft::integral_traits<int_t>             traits_t;

        STLSOFT_STATIC_ASSERT((stlsoft::is_same_type<traits_t::integer_type, traits_t::underlying_type>::value));

        TEST_INT_EQ(12345678, traits_t::get_underlying_value(12345678));
        TEST_INT_EQ(12345678, traits_t::from_underlying_type(12345678));
    }

    {
        typedef int_wrapper                                 int_t;
        typedef stlsoft::integral_traits<int_t>             traits_t;

        STLSOFT_STATIC_ASSERT((!stlsoft::is_same_type<traits_t::integer_type, traits_t::underlying_type>::value));

        {
            int_wrapper iw_12345678 = { 12345678 };

            TEST_INT_EQ(12345678, traits_t::get_underlying_value(iw_12345678));
        }
        TEST_INT_EQ(12345678, traits_t::from_underlying_type(12345678).value);
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

