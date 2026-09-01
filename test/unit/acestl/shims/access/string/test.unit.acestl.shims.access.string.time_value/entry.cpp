/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.acestl.shims.access.string.time_value/entry.cpp
 *
 * Purpose: Unit-tests for string-access-shims for `ACE_Time_Value`.
 *
 * Created: 7th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#define STLSOFT_MINIMUM_SAS_INCLUDES


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <acestl/shims/access/string/time_value.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_calls_possible();
    static void TEST_c_str_len();
    static void TEST_c_str_ptr_format_and_milliseconds();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.acestl.shims.access.string.time_value", verbosity))
    {
        XTESTS_RUN_CASE(TEST_calls_possible);
        XTESTS_RUN_CASE(TEST_c_str_len);
        XTESTS_RUN_CASE(TEST_c_str_ptr_format_and_milliseconds);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_calls_possible()
{
    ACE_Time_Value const tv(1, 234567);

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

static void TEST_c_str_len()
{
    ACE_Time_Value const tv(1, 234567);

    TEST_INT_EQ(23u, stlsoft::c_str_len_a(tv));
    TEST_INT_EQ(23u, stlsoft::c_str_len(tv));
}

static void TEST_c_str_ptr_format_and_milliseconds()
{
    /* Format is localtime("%Y-%m-%d %H:%M:%S") + ".%03ld" milliseconds
     * (usec / 1000). Length is fixed at 23; avoid absolute wall-clock
     * equality because localtime is timezone-dependent.
     */
    long const sec = 1;
    long const usec = 234567;
    long const msec = usec / 1000;

    ACE_Time_Value const tv(sec, usec);
    stlsoft::basic_shim_string<char> const s = stlsoft::c_str_ptr_a(tv);
    char const* const ptr = s.data();

    TEST_INT_EQ(23u, s.size());
    TEST_INT_EQ(23, static_cast<int>(::strlen(ptr)));

    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    int millis = -1;

    TEST_INT_EQ(
        7
    ,   ::sscanf(
            ptr
        ,   "%d-%d-%d %d:%d:%d.%d"
        ,   &year
        ,   &month
        ,   &day
        ,   &hour
        ,   &minute
        ,   &second
        ,   &millis
        )
    );

    TEST_BOOLEAN_TRUE(year >= 1970);
    TEST_BOOLEAN_TRUE(month >= 1 && month <= 12);
    TEST_BOOLEAN_TRUE(day >= 1 && day <= 31);
    TEST_BOOLEAN_TRUE(hour >= 0 && hour <= 23);
    TEST_BOOLEAN_TRUE(minute >= 0 && minute <= 59);
    TEST_BOOLEAN_TRUE(second >= 0 && second <= 60);
    TEST_INT_EQ(msec, millis);

    char expected_suffix[8];

    TEST_INT_EQ(4, ::snprintf(expected_suffix, sizeof(expected_suffix), ".%03ld", msec));

    TEST_MS_EQ(expected_suffix, ptr + 19);
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
