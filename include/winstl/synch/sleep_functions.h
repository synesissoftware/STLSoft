/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/synch/sleep_functions.h
 *
 * Purpose: WinSTL time functions.
 *
 * Created: 11th June 2006
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2006-2019, Matthew Wilson and Synesis Software
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Information Systems
 *   nor the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file winstl/synch/sleep_functions.h
 *
 * \brief [C, C++] Various time functions
 *   (\ref group__library__Synch "Synchronisation" Library).
 */

#ifndef WINSTL_INCL_WINSTL_SYNCH_H_SLEEP_FUNCTIONS
#define WINSTL_INCL_WINSTL_SYNCH_H_SLEEP_FUNCTIONS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define WINSTL_VER_WINSTL_SYNCH_H_SLEEP_FUNCTIONS_MAJOR    2
# define WINSTL_VER_WINSTL_SYNCH_H_SLEEP_FUNCTIONS_MINOR    2
# define WINSTL_VER_WINSTL_SYNCH_H_SLEEP_FUNCTIONS_REVISION 2
# define WINSTL_VER_WINSTL_SYNCH_H_SLEEP_FUNCTIONS_EDIT     36
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef WINSTL_INCL_WINSTL_H_WINSTL
# include <winstl/winstl.h>
#endif /* !WINSTL_INCL_WINSTL_H_WINSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef WINSTL_INCL_WINSTL_TIME_H_COMPARISON_FUNCTIONS
# include <winstl/time/comparison_functions.h>
#endif /* !WINSTL_INCL_WINSTL_TIME_H_COMPARISON_FUNCTIONS */

#ifndef WINSTL_INCL_WINSTL_API_external_h_ErrorHandling
# include <winstl/api/external/ErrorHandling.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_ErrorHandling */
#ifndef WINSTL_INCL_WINSTL_API_external_h_ProcessAndThread
# include <winstl/api/external/ProcessAndThread.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_ProcessAndThread */
#ifndef WINSTL_INCL_WINSTL_API_external_h_Synchronization
# include <winstl/api/external/Synchronization.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_Synchronization */
#ifndef WINSTL_INCL_WINSTL_API_external_h_Time
# include <winstl/api/external/Time.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_Time */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#if !defined(WINSTL_NO_NAMESPACE) && \
    !defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
# if defined(STLSOFT_NO_NAMESPACE)
/* There is no stlsoft namespace, so must define ::winstl */
namespace winstl
{
# else
/* Define stlsoft::winstl_project */
namespace stlsoft
{
namespace winstl_project
{
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !WINSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

/** [C, C++] Puts the calling thread to sleep for (at least) the given
 * number of microseconds.
 *
\code
winstl_C_micro_sleep(100000);  // Sleep for 0.1 seconds
winstl_C_micro_sleep(100);     // Sleep for 0.1 milliseconds
\endcode
 *
 * \param microseconds The number of microseconds to wait
 *
 * \return A boolean value indicating whether the operation was
 *  successful. If not, <code>::GetLastError()</code> will contain a code
 *  code representing the reason for failure.
 *
 * \see winstl::micro_sleep
 *
 * \note Because Windows provides sleep facilities (via Windows API function
 *   <code>::Sleep(dwMilliseconds : DWORD)</code>) at millisecond
 *   granularity, calling this function with values less than 1000 results
 *   in the equivalent behaviour as if called with 1000.
 */
STLSOFT_INLINE
ws_int_t
winstl_C_micro_sleep(
    ws_uint_t   microseconds
) STLSOFT_NOEXCEPT
{
    LARGE_INTEGER   liFrequency;
    LARGE_INTEGER   liCountStart;
    LARGE_INTEGER   liCountCurrent;

    /* NOTE: compiler should be able to generate good code for adjacent
     * division&modulo (aka `std::div()`)
     */
    DWORD milliseconds      =   microseconds / 1000;
    DWORD microseconds_rem  =   microseconds % 1000;

    /* Algorithm:
     *
     * 1 - if milliseconds >= 225, then we do a straight `::Sleep()`;
     * 2 - if microseconds == 0, then we do a straight `::Sleep()`;
     * 3 - if microseconds < 25000, then we do a busy
     *     wait (via `::Sleep(0)` and `::QueryPerformanceCounter()`);
     * 4 - use (`::CreateWaitableTimer()`);
     */

    /* 1 ? */
    if (microseconds >= 225000)
    {
        goto us_simple_sleep_by_milliseconds;
    }

    /* 2 ? */
    if (0 == milliseconds &&
        0 == microseconds_rem)
    {
        goto us_simple_sleep_by_milliseconds;
    }

    /* 3 and 4 : we collect the QPC frequency and initial count */

    if (!WINSTL_API_EXTERNAL_Time_QueryPerformanceFrequency(&liFrequency))
    {
        goto us_simple_sleep_by_milliseconds;
    }

    if (!WINSTL_API_EXTERNAL_Time_QueryPerformanceCounter(&liCountStart))
    {
        goto us_simple_sleep_by_milliseconds;
    }

    /* 3 ? */
    if (microseconds < 25000)
    {
us_qpc_check:

        for (int i = 0; ; ++i)
        {
            WINSTL_API_EXTERNAL_ProcessAndThread_Sleep(0);

            if (!WINSTL_API_EXTERNAL_Time_QueryPerformanceCounter(&liCountCurrent))
            {
                goto us_simple_sleep_by_milliseconds;
            }
            else
            {
                LONGLONG const d = winstl_C_difference_in_microseconds_QPC(&liCountCurrent, &liCountStart, &liFrequency);

                if (d >= microseconds)
                {
                    return ws_true_v;
                }
            }
        }
    }

    /* 4 */
    {
        HANDLE hTimer;

        if (NULL == (hTimer = STLSOFT_NS_GLOBAL(CreateWaitableTimer)(NULL, TRUE, NULL)))
        {
            goto us_simple_sleep_by_milliseconds;
        }
        else
        {
            LARGE_INTEGER ft;

            ft.QuadPart = -((10 * (LONGLONG)microseconds) / 1);

            if (!STLSOFT_NS_GLOBAL(SetWaitableTimer)(hTimer, &ft, 0, NULL, NULL, 0))
            {
                STLSOFT_NS_GLOBAL(CloseHandle)(hTimer);

                goto us_simple_sleep_by_milliseconds;
            }
            else
            {
                WINSTL_API_EXTERNAL_Synchronization_WaitForSingleObject(hTimer, INFINITE);

                STLSOFT_NS_GLOBAL(CloseHandle)(hTimer);

                goto us_qpc_check;
            }
        }
    }


us_simple_sleep_by_milliseconds:

    return (WINSTL_API_EXTERNAL_ProcessAndThread_Sleep(milliseconds), ws_true_v);
}


/* /////////////////////////////////////////////////////////////////////////
 * obsolete symbols
 *
 * NOTE: these are only defined if:
 *
 * - we're generating documentation, or
 * - STLSOFT_OBSOLETE is specified, or
 * - it's STLSoft 1.10 (or earlier)
 */

#if defined(STLSOFT_DOCUMENTATION_SKIP_SECTION) || \
    defined(STLSOFT_OBSOLETE) || \
    _STLSOFT_VER < 0x010b0000

/** \def winstl__micro_sleep
 *
 * \deprecated Use winstl_C_micro_sleep
 */
# define winstl__micro_sleep                                winstl_C_micro_sleep

#endif /* obsolete || 1.10- */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifdef STLSOFT_DOCUMENTATION_SKIP_SECTION
namespace winstl
{
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * C++ functions
 */

#ifdef __cplusplus

/** [C++] Puts the calling thread to sleep for (at least) the given
 * number of microseconds.
 *
\code
  winstl::micro_sleep(100000);  // Sleep for 0.1 approximately seconds
  winstl::micro_sleep(100);     // Sleep for 0.1 approximately milliseconds
\endcode
 *
 * \param microseconds The number of microseconds to wait
 *
 * \return A boolean value indicating whether the operation was
 *  successful. If not, <code>::GetLastError()</code> will contain a code
 *  representing the reason for failure.
 */
inline
ws_int_t
micro_sleep(
    ws_uint_t microseconds
) STLSOFT_NOEXCEPT
{
    return winstl_C_micro_sleep(microseconds);
}
#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef WINSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
} /* namespace winstl */
# else
} /* namespace winstl_project */
} /* namespace stlsoft */
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !WINSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !WINSTL_INCL_WINSTL_SYNCH_H_SLEEP_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */

