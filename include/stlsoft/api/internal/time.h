/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/api/internal/time.h
 *
 * Purpose: Internal adaptations for time.h constructs.
 *
 * Created: 11th January 2017
 * Updated: 2nd November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2024, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2017-2019, Matthew Wilson and Synesis Software
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


/* WARNING: this file contains undocumented internal features that are
 * subject to change at any time, so if you use them it is at your own risk.
 */

#ifndef STLSOFT_INCL_STLSOFT_API_internal_h_time
#define STLSOFT_INCL_STLSOFT_API_internal_h_time


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# include <stlsoft/stlsoft.h>
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef STLSOFT_INCL_STLSOFT_QUALITY_H_CONTRACT
# include <stlsoft/quality/contract.h>
#endif /* !STLSOFT_INCL_STLSOFT_QUALITY_H_CONTRACT */
#ifndef STLSOFT_INCL_STLSOFT_QUALITY_H_COVER
# include <stlsoft/quality/cover.h>
#endif /* !STLSOFT_INCL_STLSOFT_QUALITY_H_COVER */

#ifndef STLSOFT_INCL_H_ERRNO
# define STLSOFT_INCL_H_ERRNO
# include <errno.h>
#endif /* !STLSOFT_INCL_H_ERRNO */
#ifndef STLSOFT_INCL_H_TIME
# define STLSOFT_INCL_H_TIME
# include <time.h>
#endif /* !STLSOFT_INCL_H_TIME */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_time
# include <stlsoft/api/external/time.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_time */


/* /////////////////////////////////////////////////////////////////////////
 * time functions
 */

/** Converts the time epoch into calendar time via call to `::gmtime()` (or
 * a "safe" equivalent such as `::gmtime_r()` and `::gmtime_s()`), as well
 * as providing some standardisation of input validity.
 *
 * \ingroup group__library__Time
 *
 * The function is implemented in terms of standard or compiler-specific or
 * platform-specific functionality in descending order of availability:
 * - standard function `::gmtime_r()`;
 * - GCC function `::gmtime_r()`;
 * - MSVC function `::gmtime_s()`;
 * - `::gmtime()`;
 *
 * See the discrimination of API functions in stlsoft/api/external/time.h
 * for more information.
 *
 * \param tm Pointer to calendar time structure. May not be \c nullptr
 * \param t Pointer to the time since epoch. May not be \c nullptr
 *
 * \retval 0 if the operation succeeded;
 * \retval an "errno" value if the operation failed;
 *
 * \note When none of the reentrant or "safe" functions is available, the
 *   implementation falls back to `::gmtime()`, which may not be
 *   thread-safe; the result is copied to \c tm before returning.
 *
 * \pre nullptr != tm
 * \pre nullptr != t
 */
STLSOFT_INLINE
int
STLSOFT_API_INTERNAL_Time_gmtime(
    struct tm*      tm
,   time_t const*   t
)
{
    STLSOFT_ASSERT(NULL != tm);
    STLSOFT_ASSERT(NULL != t);

#if 0
#elif 0 ||\
      defined(STLSOFT_LF_SUPPORT_GCC_gmtime_r) ||\
      0

    {
        struct tm const* const ptm = STLSOFT_NS_GLOBAL_(gmtime_r)(t, tm);

        STLSOFT_COVER_MARK_LINE();

        if (NULL == ptm)
        {
            STLSOFT_COVER_MARK_LINE();

            return errno;
        }
        else
        {
            STLSOFT_COVER_MARK_LINE();

            return 0;
        }
    }
#elif 0 ||\
      defined(STLSOFT_LF_SUPPORT_MSVCRT_gmtime_s) ||\
      0

    {
        STLSOFT_COVER_MARK_LINE();

        return STLSOFT_NS_GLOBAL_(gmtime_s)(tm, t);
    }
#else

    {
        struct tm const* const ptm = STLSOFT_NS_GLOBAL_(gmtime)(t);

        STLSOFT_COVER_MARK_LINE();

        if (NULL == ptm)
        {
            STLSOFT_COVER_MARK_LINE();

            return errno;
        }
        else
        {
            STLSOFT_COVER_MARK_LINE();

            *tm = *ptm;

            return 0;
        }
    }
#endif
}

/** Converts the time epoch into calendar time via call to `::localtime()`
 * (or a "safe" equivalent such as `::localtime_r()` and `::localtime_s()`),
 * as well as providing some standardisation of input validity.
 *
 * \ingroup group__library__Time
 *
 * The function is implemented in terms of standard or compiler-specific or
 * platform-specific functionality in descending order of availability:
 * - standard function `::localtime_r()`;
 * - GCC function `::localtime_r()`;
 * - MSVC function `::localtime_s()`;
 * - `::localtime()`;
 *
 * See the discrimination of API functions in stlsoft/api/external/time.h
 * for more information.
 *
 * \param tm Pointer to calendar time structure. May not be \c nullptr
 * \param t Pointer to the time since epoch. May not be \c nullptr
 *
 * \retval 0 if the operation succeeded;
 * \retval an "errno" value if the operation failed;
 *
 * \note When none of the reentrant or "safe" functions is available, the
 *   implementation falls back to `::localtime()`, which may not be
 *   thread-safe; the result is copied to \c tm before returning.
 *
 * \pre nullptr != tm
 * \pre nullptr != t
 */
STLSOFT_INLINE
int
STLSOFT_API_INTERNAL_Time_localtime(
    struct tm*      tm
,   time_t const*   t
)
{
    STLSOFT_ASSERT(NULL != tm);
    STLSOFT_ASSERT(NULL != t);

#if 0
#elif 0 ||\
      defined(STLSOFT_LF_SUPPORT_GCC_localtime_r) ||\
      0

    {
        struct tm const* const ptm = STLSOFT_NS_GLOBAL_(localtime_r)(t, tm);

        STLSOFT_COVER_MARK_LINE();

        if (NULL == ptm)
        {
            STLSOFT_COVER_MARK_LINE();

            return errno;
        }
        else
        {
            STLSOFT_COVER_MARK_LINE();

            return 0;
        }
    }
#elif 0 ||\
      defined(STLSOFT_LF_SUPPORT_MSVCRT_localtime_s) ||\
      0

    {
        STLSOFT_COVER_MARK_LINE();

        return STLSOFT_NS_GLOBAL_(localtime_s)(tm, t);
    }
#else

    {
        struct tm const* const ptm = STLSOFT_NS_GLOBAL_(localtime)(t);

        STLSOFT_COVER_MARK_LINE();

        if (NULL == ptm)
        {
            STLSOFT_COVER_MARK_LINE();

            return errno;
        }
        else
        {
            STLSOFT_COVER_MARK_LINE();

            *tm = *ptm;

            return 0;
        }
    }
#endif
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_API_internal_h_time */

/* ///////////////////////////// end of file //////////////////////////// */

