/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/api/internal/stdio.h
 *
 * Purpose: Internal adaptations for stdio.h constructs.
 *
 * Created: 11th November 2020
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2020-2026, Matthew Wilson and Synesis Information Systems
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
 * - Neither the name(s) of Matthew Wilson and Synesis Synesis Information
 *   Systems nor the names of any contributors may be used to endorse or
 *   promote products derived from this software without specific prior
 *   written permission.
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

#ifndef STLSOFT_INCL_STLSOFT_API_internal_h_stdio
#define STLSOFT_INCL_STLSOFT_API_internal_h_stdio


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

#ifndef STLSOFT_INCL_H_ERRNO
# define STLSOFT_INCL_H_ERRNO
# include <errno.h>
#endif /* !STLSOFT_INCL_H_ERRNO */
#ifndef STLSOFT_INCL_H_STDARG
# define STLSOFT_INCL_H_STDARG
# include <stdarg.h>
#endif /* !STLSOFT_INCL_H_STDARG */
#ifndef STLSOFT_INCL_H_STDIO
# define STLSOFT_INCL_H_STDIO
# include <stdio.h>
#endif /* !STLSOFT_INCL_H_STDIO */
#if defined(STLSOFT_COMPILER_IS_MSVC)
# ifndef STLSOFT_INCL_H_WCHAR
#  define STLSOFT_INCL_H_WCHAR
#  include <wchar.h>
# endif /* !STLSOFT_INCL_H_WCHAR */
#endif /* STLSOFT_COMPILER_IS_MSVC */


/* /////////////////////////////////////////////////////////////////////////
 * feature support detection
 */

#ifndef STLSOFT_vsnprintf_SUPPORT
# if 0
# elif defined(STLSOFT_COMPILER_IS_MSVC)

#  if _MSC_VER >= 1400

#   define STLSOFT_vsnprintf_SUPPORT(b, n, f, a)            STLSOFT_NS_GLOBAL(_vsnprintf_s)((b), (n), _TRUNCATE, (f), a);
#  else /* ? _MSC_VER */

#   define STLSOFT_vsnprintf_SUPPORT(b, n, f, a)            STLSOFT_NS_GLOBAL(_vsnprintf)((b), (n), (f), a);
#  endif /* _MSC_VER */
# else /* ? compiler */

#  define STLSOFT_vsnprintf_SUPPORT(b, n, f, a)             STLSOFT_NS_GLOBAL(vsnprintf)((b), (n), (f), a);
# endif /* compiler */
#endif /* !STLSOFT_vsnprintf_SUPPORT */

#ifndef STLSOFT_vsnwprintf_SUPPORT
# if 0
# elif defined(STLSOFT_COMPILER_IS_MSVC)

#  if _MSC_VER >= 1400

#   define STLSOFT_vsnwprintf_SUPPORT(b, n, f, a)           STLSOFT_NS_GLOBAL(_vsnwprintf_s)((b), (n), _TRUNCATE, (f), a);
#  else /* ? _MSC_VER */

#   define STLSOFT_vsnwprintf_SUPPORT(b, n, f, a)           STLSOFT_NS_GLOBAL(_vsnwprintf)((b), (n), (f), a);
#  endif /* _MSC_VER */
# endif /* compiler */
#endif /* !STLSOFT_vsnwprintf_SUPPORT */


/* /////////////////////////////////////////////////////////////////////////
 * stdio functions
 */

/* /////////////////////////////////////////////////////////
 * file stream (FILE*) functions
 */

/** Opens a file, via fopen_s() when STLSOFT_USING_SAFE_STR_FUNCTIONS is
 * defined and the compiler is Visual C/C++, otherwise via fopen().
 *
 * \param path The path of the file to open. May not be \c nullptr
 * \param mode The open mode. May not be \c nullptr
 * \param ph Pointer to receive the file handle. May not be \c nullptr
 *
 * \retval 0 if the operation succeeded;
 * \retval an "errno" value if the operation failed;
 *
 * \pre nullptr != path
 * \pre nullptr != mode
 * \pre nullptr != ph
 */
STLSOFT_INLINE
int
STLSOFT_API_INTERNAL_stdio_fopen_m(
    char const* path
,   char const* mode
,   FILE**      ph
)
{
    STLSOFT_ASSERT(NULL != path);
    STLSOFT_ASSERT(NULL != mode);
    STLSOFT_ASSERT(NULL != ph);

#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS) &&\
    defined(STLSOFT_COMPILER_IS_MSVC)

    return STLSOFT_NS_GLOBAL_(fopen_s)(ph, path, mode);
#else
    *ph = STLSOFT_NS_GLOBAL_(fopen)(path, mode);

    return (NULL == *ph) ? errno : 0;
#endif
}

#if defined(STLSOFT_COMPILER_IS_MSVC)

STLSOFT_INLINE
int
STLSOFT_API_INTERNAL_stdio_fopen_w(
    wchar_t const*  path
,   wchar_t const*  mode
,   FILE**          ph
)
{
    STLSOFT_ASSERT(NULL != path);
    STLSOFT_ASSERT(NULL != mode);
    STLSOFT_ASSERT(NULL != ph);

#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

    return STLSOFT_NS_GLOBAL_(_wfopen_s)(ph, path, mode);
#else // }
    *ph = STLSOFT_NS_GLOBAL_(_wfopen)(path, mode);

    return (NULL == *ph) ? errno : 0;
#endif
}
#endif /* STLSOFT_COMPILER_IS_MSVC */


/* /////////////////////////////////////////////////////////
 * formatting functions
 */

STLSOFT_INLINE
int
STLSOFT_API_INTERNAL_stdio_vsnprintf(
    char            buf[]
,   size_t          cchBuf
,   char const*     fmt
,   va_list         args
)
{
    STLSOFT_ASSERT(0 == cchBuf || NULL != buf);
    STLSOFT_ASSERT(NULL != fmt);

    return STLSOFT_vsnprintf_SUPPORT(buf, cchBuf, fmt, args);
}
#ifdef STLSOFT_vsnwprintf_SUPPORT

STLSOFT_INLINE
int
STLSOFT_API_INTERNAL_stdio_vsnwprintf(
    wchar_t         buf[]
,   size_t          cchBuf
,   wchar_t const*  fmt
,   va_list         args
)
{
    STLSOFT_ASSERT(0 == cchBuf || NULL != buf);
    STLSOFT_ASSERT(NULL != fmt);

    return STLSOFT_vsnwprintf_SUPPORT(buf, cchBuf, fmt, args);
}
#endif /* STLSOFT_vsnwprintf_SUPPORT */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_API_internal_h_stdio */

/* ///////////////////////////// end of file //////////////////////////// */

