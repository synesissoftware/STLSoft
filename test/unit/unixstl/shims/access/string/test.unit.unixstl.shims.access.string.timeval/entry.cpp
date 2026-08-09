/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.shims.access.string.timeval/entry.cpp
 *
 * Purpose: Unit-tests for string-access-shims for UNIX `timeval`.
 *
 * Created: 5th May 2014
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#define STLSOFT_MINIMUM_SAS_INCLUDES

/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <unixstl/shims/access/string/timeval.hpp>

/* /////////////////////////////////////////////////////////////////////////
 * includes
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
#include <time.h>

#ifdef _WIN32
# include <unixem/time.h>
#endif


#ifdef STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_STRING_STD_HPP_TIME
# error Cannot include stlsoft/shims/access/string/std/time.hpp
#endif /* STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_STRING_STD_HPP_TIME */


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_calls_possible();
    static void test_c_str_len();
    static void test_c_str_ptr();
    static void test_invalid_value_conversion();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
* main()
*/

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.shims.access.string.timeval", verbosity))
    {
        XTESTS_RUN_CASE(test_calls_possible);
        XTESTS_RUN_CASE(test_c_str_len);
        XTESTS_RUN_CASE(test_c_str_ptr);
        XTESTS_RUN_CASE(test_invalid_value_conversion);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    char const* get_fixed_date_string()
    {
        return "May 05 05:03:02.013987 2014";
    }

    struct timeval get_fixed_date()
    {
        struct tm   tm;

        tm.tm_year  =   2014 - 1900;
        tm.tm_mon   =   4;
        tm.tm_mday  =   5;
        tm.tm_hour  =   5;
        tm.tm_min   =   3;
        tm.tm_sec   =   2;

        tm.tm_wday  =   1;
        tm.tm_yday  =   0;
        tm.tm_isdst =   0;

        char const* const   s1 = ::asctime(&tm);

        struct timeval  tv;

#ifdef _WIN32
        tv.tv_sec   =   static_cast<long>(::timegm(&tm));
#else
        tv.tv_sec   =   ::timegm(&tm);
#endif
        tv.tv_usec  =   13987;

        // ((void)&s1);
        STLSOFT_SUPPRESS_UNUSED(s1);

        return tv;
    }

static void test_calls_possible()
{
    {
        struct timeval tv = get_fixed_date();

        stlsoft::c_str_data_a(tv);
        stlsoft::c_str_data(tv);

        stlsoft::c_str_len_a(tv);
        stlsoft::c_str_len(tv);

        stlsoft::c_str_ptr_a(tv);
        stlsoft::c_str_ptr(tv);

        stlsoft::c_str_ptr_null_a(tv);
        stlsoft::c_str_ptr_null(tv);

        TEST_PASSED();
    }

    {
        struct timeval  tv_ =   get_fixed_date();
        struct timeval* tv  =   &tv_;

        stlsoft::c_str_data_a(tv);
        stlsoft::c_str_data(tv);

        stlsoft::c_str_len_a(tv);
        stlsoft::c_str_len(tv);

        stlsoft::c_str_ptr_a(tv);
        stlsoft::c_str_ptr(tv);

        stlsoft::c_str_ptr_null_a(tv);
        stlsoft::c_str_ptr_null(tv);

        TEST_PASSED();
    }
}

static void test_c_str_len()
{
    {
        struct timeval tv = get_fixed_date();

        TEST_INT_EQ(27u, stlsoft::c_str_len_a(tv));
        TEST_INT_EQ(27u, stlsoft::c_str_len(tv));
    }

    {
        struct timeval  tv_ =   get_fixed_date();
        struct timeval* tv  =   &tv_;

        TEST_INT_EQ(27u, stlsoft::c_str_len_a(tv));
        TEST_INT_EQ(27u, stlsoft::c_str_len(tv));
    }
}

static void test_c_str_ptr()
{
    {
        struct timeval tv = get_fixed_date();

        TEST_MS_EQ(get_fixed_date_string(), stlsoft::c_str_ptr_a(tv));
        TEST_MS_EQ(get_fixed_date_string(), stlsoft::c_str_ptr(tv));
    }

    {
        struct timeval  tv_ =   get_fixed_date();
        struct timeval* tv  =   &tv_;

        TEST_MS_EQ(get_fixed_date_string(), stlsoft::c_str_ptr_a(tv));
        TEST_MS_EQ(get_fixed_date_string(), stlsoft::c_str_ptr(tv));
    }
}

static void test_invalid_value_conversion()
{
    {
        struct timeval tv = get_fixed_date();

        tv.tv_usec  =   -1;

        TEST_INT_EQ(STLSOFT_NUM_ELEMENTS("(invalid time)") - 1, stlsoft::c_str_len_a(tv));
        TEST_MS_EQ("(invalid time)", stlsoft::c_str_ptr_a(tv));
    }

    {
        struct timeval tv = get_fixed_date();

        tv.tv_sec   =   -1;

        TEST_INT_EQ(STLSOFT_NUM_ELEMENTS("(invalid time)") - 1, stlsoft::c_str_len_a(tv));
        TEST_MS_EQ("(invalid time)", stlsoft::c_str_ptr_a(tv));
    }

    {
        struct timeval tv = get_fixed_date();

        tv.tv_sec   =   -1;
        tv.tv_usec  =   -1;

        TEST_INT_EQ(STLSOFT_NUM_ELEMENTS("(invalid time)") - 1, stlsoft::c_str_len_a(tv));
        TEST_MS_EQ("(invalid time)", stlsoft::c_str_ptr_a(tv));
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

