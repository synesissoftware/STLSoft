/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_concept/string_access_shims/time_functions/main.cpp
 *
 * Purpose: C++ example program demonstrating use of string access shims.
 *
 * Created: 27th January 2017
 * Updated: 28th April 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <platformstl/platformstl.hpp>

#include <stlsoft/shims/access/string/std/chrono.hpp>
#include <stlsoft/shims/access/string/std/time.hpp>
#ifdef ACE
# include <acestl/shims/access/string/time_value.hpp>
#endif
#ifdef PLATFORMSTL_OS_IS_UNIX
# include <unixstl/shims/access/string/timeval.hpp>
# ifdef _WIN32
#  include <unixem/time.h>
# endif
#endif
#ifdef PLATFORMSTL_OS_IS_WINDOWS
# include <winstl/shims/access/string/time.hpp>
#endif

#include <chrono>

#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

inline
void
output_by_(
    char const*     type
,   char const*     tm
,   size_t          cchTm
)
{
    fprintf(stdout, "time is %.*s (type %s) \n", int(cchTm), tm, type);
}

template<
    typename    T_string
>
inline
void
output_by(
    char const*     type
,   T_string const& tm
)
{
    output_by_(type, stlsoft::c_str_data_a(tm), stlsoft::c_str_len_a(tm));
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main()
{
    //  std::chrono::system_clock

#if __cplusplus >= 201103L

    {
        auto const now = std::chrono::system_clock::now();

        output_by("std::chrono::system_clock", now);
    }
#endif


    // struct tm

    time_t now;

    ::time(&now);

    struct tm* const tm = ::localtime(&now);

    output_by("struct tm", tm);


    // ACE_Time_Value
#ifdef ACE
    {
        ACE_Time_Value atv(now, 123456);

        output_by("ACE_Time_Value", atv);
    }
#endif


    // struct timeval
#ifdef PLATFORMSTL_OS_IS_UNIX
    {
        struct timeval  tv;

        tv.tv_sec   =   static_cast<long>(::timegm(tm));
        tv.tv_usec  =   123456;

        output_by("struct timeval", tv);
    }
#endif


    // SYSTEMTIME
#ifdef PLATFORMSTL_OS_IS_WINDOWS
    SYSTEMTIME st;

    ::GetLocalTime(&st);

    {
        output_by("SYSTEMTIME", st);
    }
#endif


    // FILETIME
#ifdef PLATFORMSTL_OS_IS_WINDOWS
    {
        FILETIME ft;

        ::SystemTimeToFileTime(&st, &ft);

        output_by("FILETIME", ft);
    }
#endif


    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

