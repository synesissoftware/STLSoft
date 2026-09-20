/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.traits.integral_printf_format_traits/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::integral_printf_format_traits`.
 *
 * Created: 20th October 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/traits/integral_printf_format_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/util/string/snprintf.h>

/* Standard C++ header files */

/* Standard C header files */


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_char();
    static void test_char_signed();
    static void test_char_unsigned();
    static void test_short_signed();
    static void test_short_unsigned();
    static void test_int_signed();
    static void test_int_unsigned();
    static void test_long_signed();
    static void test_long_unsigned();
#ifdef STLSOFT_CF_BUILTIN_long_long_SUPPORT
    static void test_long_long_signed();
    static void test_long_long_unsigned();
#endif /* STLSOFT_CF_BUILTIN_long_long_SUPPORT */
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.traits.integral_printf_format_traits", verbosity))
    {
        XTESTS_RUN_CASE(test_char);
        XTESTS_RUN_CASE(test_char_signed);
        XTESTS_RUN_CASE(test_char_unsigned);
        XTESTS_RUN_CASE(test_short_signed);
        XTESTS_RUN_CASE(test_short_unsigned);
        XTESTS_RUN_CASE(test_int_signed);
        XTESTS_RUN_CASE(test_int_unsigned);
        XTESTS_RUN_CASE(test_long_signed);
        XTESTS_RUN_CASE(test_long_unsigned);
#ifdef STLSOFT_CF_BUILTIN_long_long_SUPPORT
        XTESTS_RUN_CASE(test_long_long_signed);
        XTESTS_RUN_CASE(test_long_long_unsigned);
#endif /* STLSOFT_CF_BUILTIN_long_long_SUPPORT */

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_char()
{
    typedef char                                            int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

#ifdef STLSOFT_CF_char_IS_UNSIGNED
    TEST_MS_EQ("%u", ipft_t::decimal_format_a());
#else /* ? STLSOFT_CF_char_IS_UNSIGNED */
    TEST_MS_EQ("%d", ipft_t::decimal_format_a());
#endif /* STLSOFT_CF_char_IS_UNSIGNED */
    TEST_MS_EQ("%x", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%X", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%o", ipft_t::octal_format_a());

#ifdef STLSOFT_CF_char_IS_UNSIGNED
    TEST_WS_EQ(L"%u", ipft_t::decimal_format_w());
#else /* ? STLSOFT_CF_char_IS_UNSIGNED */
    TEST_WS_EQ(L"%d", ipft_t::decimal_format_w());
#endif /* STLSOFT_CF_char_IS_UNSIGNED */
    TEST_WS_EQ(L"%x", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%X", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%o", ipft_t::octal_format_w());

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
#ifdef STLSOFT_CF_char_IS_UNSIGNED
    TEST_MS_EQ("%u", ipft_t::format_a());
#else /* ? STLSOFT_CF_char_IS_UNSIGNED */
    TEST_MS_EQ("%d", ipft_t::format_a());
#endif /* STLSOFT_CF_char_IS_UNSIGNED */
    TEST_MS_EQ("%x", ipft_t::hex_format_a());

#ifdef STLSOFT_CF_char_IS_UNSIGNED
    TEST_WS_EQ(L"%u", ipft_t::format_w());
#else /* ? STLSOFT_CF_char_IS_UNSIGNED */
    TEST_WS_EQ(L"%d", ipft_t::format_w());
#endif /* STLSOFT_CF_char_IS_UNSIGNED */
    TEST_WS_EQ(L"%x", ipft_t::hex_format_w());
# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>

    {
        char    buff[21];

        {
            int_t const v   =   123;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::decimal_format_a(), v);

            XTESTS_REQUIRE(TEST_INT_EQ(3, r));
            TEST_MS_EQ("123", buff);
        }

        {
            int_t const v   =   123;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::hexadecimal_format_a(false), v);

            XTESTS_REQUIRE(TEST_INT_EQ(2, r));
            TEST_MS_EQ("7b", buff);
        }

        {
            int_t const v   =   123;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::octal_format_a(), v);

            XTESTS_REQUIRE(TEST_INT_EQ(3, r));
            TEST_MS_EQ("173", buff);
        }
    }
}

static void test_char_signed()
{
    typedef char signed                                     int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

    TEST_MS_EQ("%d", ipft_t::decimal_format_a());
    TEST_MS_EQ("%x", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%X", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%o", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%d", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%x", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%X", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%o", ipft_t::octal_format_w());

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%d", ipft_t::format_a());
    TEST_MS_EQ("%x", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%d", ipft_t::format_w());
    TEST_WS_EQ(L"%x", ipft_t::hex_format_w());
# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
}

static void test_char_unsigned()
{
    typedef char unsigned                                   int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

    TEST_MS_EQ("%u", ipft_t::decimal_format_a());
    TEST_MS_EQ("%x", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%X", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%o", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%u", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%x", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%X", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%o", ipft_t::octal_format_w());

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%u", ipft_t::format_a());
    TEST_MS_EQ("%x", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%u", ipft_t::format_w());
    TEST_WS_EQ(L"%x", ipft_t::hex_format_w());
# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
}

static void test_short_signed()
{
    typedef short signed                                    int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

    TEST_MS_EQ("%d", ipft_t::decimal_format_a());
    TEST_MS_EQ("%x", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%X", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%o", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%d", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%x", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%X", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%o", ipft_t::octal_format_w());

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%d", ipft_t::format_a());
    TEST_MS_EQ("%x", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%d", ipft_t::format_w());
    TEST_WS_EQ(L"%x", ipft_t::hex_format_w());
# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>

    {
        char    buff[21];

        {
            int_t const v   =   -12345;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::decimal_format_a(), v);

            XTESTS_REQUIRE(TEST_INT_EQ(6, r));
            TEST_MS_EQ("-12345", buff);
        }

        {
            int_t const v   =   12345;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::hexadecimal_format_a(false), v);

            XTESTS_REQUIRE(TEST_INT_EQ(4, r));
            TEST_MS_EQ("3039", buff);
        }

        {
            int_t const v   =   12345;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::octal_format_a(), v);

            XTESTS_REQUIRE(TEST_INT_EQ(5, r));
            TEST_MS_EQ("30071", buff);
        }
    }
}

static void test_short_unsigned()
{
    typedef short unsigned                                  int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

    TEST_MS_EQ("%u", ipft_t::decimal_format_a());
    TEST_MS_EQ("%x", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%X", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%o", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%u", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%x", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%X", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%o", ipft_t::octal_format_w());

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%u", ipft_t::format_a());
    TEST_MS_EQ("%x", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%u", ipft_t::format_w());
    TEST_WS_EQ(L"%x", ipft_t::hex_format_w());
# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
}

static void test_int_signed()
{
    typedef int signed                                      int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

    TEST_MS_EQ("%d", ipft_t::decimal_format_a());
    TEST_MS_EQ("%x", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%X", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%o", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%d", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%x", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%X", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%o", ipft_t::octal_format_w());

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%d", ipft_t::format_a());
    TEST_MS_EQ("%x", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%d", ipft_t::format_w());
    TEST_WS_EQ(L"%x", ipft_t::hex_format_w());
# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
}

static void test_int_unsigned()
{
    typedef int unsigned                                    int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

    TEST_MS_EQ("%u", ipft_t::decimal_format_a());
    TEST_MS_EQ("%x", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%X", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%o", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%u", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%x", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%X", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%o", ipft_t::octal_format_w());

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%u", ipft_t::format_a());
    TEST_MS_EQ("%x", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%u", ipft_t::format_w());
    TEST_WS_EQ(L"%x", ipft_t::hex_format_w());
# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>

    {
        char    buff[21];

        {
            int_t const v   =   9090909;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::decimal_format_a(), v);

            XTESTS_REQUIRE(TEST_INT_EQ(7, r));
            TEST_MS_EQ("9090909", buff);
        }

        {
            int_t const v   =   9090909;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::hexadecimal_format_a(true), v);

            XTESTS_REQUIRE(TEST_INT_EQ(6, r));
            TEST_MS_EQ("8AB75D", buff);
        }

        {
            int_t const v   =   9090909;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::octal_format_a(), v);

            XTESTS_REQUIRE(TEST_INT_EQ(8, r));
            TEST_MS_EQ("42533535", buff);
        }
    }
}

static void test_long_signed()
{
    typedef long signed                                     int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

    TEST_MS_EQ("%ld", ipft_t::decimal_format_a());
    TEST_MS_EQ("%lx", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%lX", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%lo", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%ld", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%lx", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%lX", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%lo", ipft_t::octal_format_w());

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%ld", ipft_t::format_a());
    TEST_MS_EQ("%lx", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%ld", ipft_t::format_w());
    TEST_WS_EQ(L"%lx", ipft_t::hex_format_w());
# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
}

static void test_long_unsigned()
{
    typedef long unsigned                                   int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

    TEST_MS_EQ("%lu", ipft_t::decimal_format_a());
    TEST_MS_EQ("%lx", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%lX", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%lo", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%lu", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%lx", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%lX", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%lo", ipft_t::octal_format_w());

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%lu", ipft_t::format_a());
    TEST_MS_EQ("%lx", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%lu", ipft_t::format_w());
    TEST_WS_EQ(L"%lx", ipft_t::hex_format_w());
# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
}
#ifdef STLSOFT_CF_BUILTIN_long_long_SUPPORT

static void test_long_long_signed()
{
    typedef long long signed                                int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

# if 0
# elif defined(STLSOFT_CF_64_BIT_PRINTF_USES_I64)
    TEST_MS_EQ("%I64d", ipft_t::decimal_format_a());
    TEST_MS_EQ("%I64x", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%I64X", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%I64o", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%I64d", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%I64x", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%I64X", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%I64o", ipft_t::octal_format_w());

#  include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%I64d", ipft_t::format_a());
    TEST_MS_EQ("%I64x", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%I64d", ipft_t::format_w());
    TEST_WS_EQ(L"%I64x", ipft_t::hex_format_w());
#  include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
# elif defined(STLSOFT_CF_64_BIT_PRINTF_USES_LL)

    TEST_MS_EQ("%lld", ipft_t::decimal_format_a());
    TEST_MS_EQ("%llx", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%llX", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%llo", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%lld", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%llx", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%llX", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%llo", ipft_t::octal_format_w());

#  include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%lld", ipft_t::format_a());
    TEST_MS_EQ("%llx", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%lld", ipft_t::format_w());
    TEST_WS_EQ(L"%llx", ipft_t::hex_format_w());
#  include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
# else

#  error Further compiler discrimination is required
# endif /* printf-64 */

    {
        char    buff[21];

        {
            int_t const v   =   123456789123456789;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::decimal_format_a(), v);

            XTESTS_REQUIRE(TEST_INT_EQ(18, r));
            TEST_MS_EQ("123456789123456789", buff);
        }

        {
            int_t const v   =   123456789123456789;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::hexadecimal_format_a(true), v);

            XTESTS_REQUIRE(TEST_INT_EQ(15, r));
            TEST_MS_EQ("1B69B4BACD05F15", buff);
        }

        {
            int_t const v   =   123456789123456789;
            int const   r   =   stlsoft::snprintf(buff, STLSOFT_NUM_ELEMENTS(buff), ipft_t::octal_format_a(), v);

            XTESTS_REQUIRE(TEST_INT_EQ(19, r));
            TEST_MS_EQ("6664664565464057425", buff);
        }
    }
}

static void test_long_long_unsigned()
{
    typedef long long unsigned                              int_t;
    typedef stlsoft::integral_printf_format_traits<
        int_t
    >                                                       ipft_t;

# if 0
# elif defined(STLSOFT_CF_64_BIT_PRINTF_USES_I64)

    TEST_MS_EQ("%I64u", ipft_t::decimal_format_a());
    TEST_MS_EQ("%I64x", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%I64X", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%I64o", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%I64u", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%I64x", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%I64X", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%I64o", ipft_t::octal_format_w());

#  include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%I64u", ipft_t::format_a());
    TEST_MS_EQ("%I64x", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%I64u", ipft_t::format_w());
    TEST_WS_EQ(L"%I64x", ipft_t::hex_format_w());
#  include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
# elif defined(STLSOFT_CF_64_BIT_PRINTF_USES_LL)

    TEST_MS_EQ("%llu", ipft_t::decimal_format_a());
    TEST_MS_EQ("%llx", ipft_t::hexadecimal_format_a(false));
    TEST_MS_EQ("%llX", ipft_t::hexadecimal_format_a(true));
    TEST_MS_EQ("%llo", ipft_t::octal_format_a());

    TEST_WS_EQ(L"%llu", ipft_t::decimal_format_w());
    TEST_WS_EQ(L"%llx", ipft_t::hexadecimal_format_w(false));
    TEST_WS_EQ(L"%llX", ipft_t::hexadecimal_format_w(true));
    TEST_WS_EQ(L"%llo", ipft_t::octal_format_w());

#  include <stlsoft/internal/warnings/push/suppress_deprecation_.h>
    TEST_MS_EQ("%llu", ipft_t::format_a());
    TEST_MS_EQ("%llx", ipft_t::hex_format_a());

    TEST_WS_EQ(L"%llu", ipft_t::format_w());
    TEST_WS_EQ(L"%llx", ipft_t::hex_format_w());
#  include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
# else

#  error Further compiler discrimination is required
# endif /* printf-64 */
}
#endif /* STLSOFT_CF_BUILTIN_long_long_SUPPORT */
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

