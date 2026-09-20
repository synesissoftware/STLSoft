/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/api/external/time.h
 *
 * Purpose: External preprocessor aliases and support discrimination for
 *          time functions.
 *
 * Created: 30th September 2024
 * Updated: 20th September 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2002-2019, Matthew Wilson and Synesis Software
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

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_time
#define STLSOFT_INCL_STLSOFT_API_external_h_time


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# include <stlsoft/stlsoft.h>
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef STLSOFT_INCL_STLSOFT_INTERNAL_H_SAFESTR
# include <stlsoft/internal/safestr.h>
#endif /* !STLSOFT_INCL_STLSOFT_INTERNAL_H_SAFESTR */

#ifndef STLSOFT_INCL_H_TIME
# define STLSOFT_INCL_H_TIME
# include <time.h>
#endif /* !STLSOFT_INCL_H_TIME */


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 *
 * discriminated symbols:
 *
 * - STLSOFT_LF_SUPPORT_GCC_asctime_r
 * - STLSOFT_LF_SUPPORT_GCC_ctime_r
 * - STLSOFT_LF_SUPPORT_GCC_gmtime_r
 * - STLSOFT_LF_SUPPORT_GCC_localtime_r
 *
 * - STLSOFT_LF_SUPPORT_MSVCRT_asctime_s
 * - STLSOFT_LF_SUPPORT_MSVCRT_ctime_s
 * - STLSOFT_LF_SUPPORT_MSVCRT_gmtime_s
 * - STLSOFT_LF_SUPPORT_MSVCRT_localtime_s
 *
 * - STLSOFT_LF_SUPPORT_STD_asctime_s
 * - STLSOFT_LF_SUPPORT_STD_ctime_s
 * - STLSOFT_LF_SUPPORT_STD_gmtime_r
 * - STLSOFT_LF_SUPPORT_STD_gmtime_s
 * - STLSOFT_LF_SUPPORT_STD_localtime_r
 * - STLSOFT_LF_SUPPORT_STD_localtime_s
 */

/*
 * - STLSOFT_LF_SUPPORT_GCC_asctime_r
 * - STLSOFT_LF_SUPPORT_GCC_ctime_r
 * - STLSOFT_LF_SUPPORT_GCC_gmtime_r
 * - STLSOFT_LF_SUPPORT_GCC_localtime_r
 *
 *
 * NOTE: the following can likely be refined with validation on more
 * platforms
 */
#if 0
#elif 0 ||\
      defined(__GNUC__) ||\
      0

# if 1 &&\
     !defined(__MINGW64__) &&\
     1

#  define STLSOFT_LF_SUPPORT_GCC_asctime_r
#  define STLSOFT_LF_SUPPORT_GCC_ctime_r
#  define STLSOFT_LF_SUPPORT_GCC_gmtime_r
#  define STLSOFT_LF_SUPPORT_GCC_localtime_r
# endif
#endif

/*
 * - STLSOFT_LF_SUPPORT_MSVCRT_asctime_s
 * - STLSOFT_LF_SUPPORT_MSVCRT_ctime_s
 * - STLSOFT_LF_SUPPORT_MSVCRT_gmtime_s
 * - STLSOFT_LF_SUPPORT_MSVCRT_localtime_s
 */
#if 0
#elif 1 &&\
      defined(_WIN32) &&\
      defined(_MSC_VER) &&\
      defined(STLSOFT_USING_SAFE_STR_FUNCTIONS) &&\
      1

# define STLSOFT_LF_SUPPORT_MSVCRT_asctime_s
# define STLSOFT_LF_SUPPORT_MSVCRT_ctime_s
# define STLSOFT_LF_SUPPORT_MSVCRT_gmtime_s
# define STLSOFT_LF_SUPPORT_MSVCRT_localtime_s
#endif

/*
 * - STLSOFT_LF_SUPPORT_STD_asctime_s
 * - STLSOFT_LF_SUPPORT_STD_ctime_s
 * - STLSOFT_LF_SUPPORT_STD_gmtime_r
 * - STLSOFT_LF_SUPPORT_STD_gmtime_s
 * - STLSOFT_LF_SUPPORT_STD_localtime_r
 * - STLSOFT_LF_SUPPORT_STD_localtime_s
 */

#if 0
#elif 1 &&\
      defined(__cplusplus) &&\
      __cplusplus >= 201103L &&\
      1

# define STLSOFT_LF_SUPPORT_STD_asctime_s
# define STLSOFT_LF_SUPPORT_STD_ctime_s
# define STLSOFT_LF_SUPPORT_STD_gmtime_s
# define STLSOFT_LF_SUPPORT_STD_localtime_s
#endif

#if 0
#elif 1 &&\
      defined(__cplusplus) &&\
      __cplusplus >= 202302L &&\
      1

 /* C++23 claims POSIX gmtime_r/localtime_r in the working draft, but MinGW
  * (and MSVC) do not provide them; keep the MSVC exclusion and also exclude
  * MinGW so discrimination falls through to gmtime()/localtime() (or *_s).
  */
# if 1 &&\
     !defined(_MSC_VER) && \
     !defined(__MINGW32__) && \
     !defined(__MINGW64__) &&\
     1

#  define STLSOFT_LF_SUPPORT_STD_gmtime_r
#  define STLSOFT_LF_SUPPORT_STD_localtime_r
# endif
#endif



/* /////////////////////////////////////////////////////////////////////////
 * time functions
 */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_time */

/* ///////////////////////////// end of file //////////////////////////// */

