/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/util/string/vsnprintf.h
 *
 * Purpose: vsn(w)printf() variants.
 *
 * Created: 15th July 2012
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2012-2019, Matthew Wilson and Synesis Software
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


/** \file stlsoft/util/string/vsnprintf.h
 *
 * \brief [C++] vsn(w)printf() variants
 *   (\ref group__library__Utility "Utility" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_UTIL_STRING_H_VSNPRINTF
#define STLSOFT_INCL_STLSOFT_UTIL_STRING_H_VSNPRINTF

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_UTIL_STRING_H_VSNPRINTF_MAJOR      1
# define STLSOFT_VER_STLSOFT_UTIL_STRING_H_VSNPRINTF_MINOR      0
# define STLSOFT_VER_STLSOFT_UTIL_STRING_H_VSNPRINTF_REVISION   6
# define STLSOFT_VER_STLSOFT_UTIL_STRING_H_VSNPRINTF_EDIT       13
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# include <stlsoft/stlsoft.h>
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef STLSOFT_INCL_H_STDARG
# define STLSOFT_INCL_H_STDARG
# include <stdarg.h>
#endif /* !STLSOFT_INCL_H_STDARG */
#ifndef STLSOFT_INCL_H_STDIO
# define STLSOFT_INCL_H_STDIO
# include <stdio.h>
#endif /* !STLSOFT_INCL_H_STDIO */

#ifndef STLSOFT_INCL_STLSOFT_API_internal_h_stdio
# include <stlsoft/api/internal/stdio.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_internal_h_stdio */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

/** vsnprintf() - equivalent
 */
STLSOFT_INLINE
int
stlsoft_C_vsnprintf(
    ss_char_a_t*        buf
,   ss_size_t           cchBuf
,   ss_char_a_t const*  fmt
,   va_list             args
)
{
    return STLSOFT_API_INTERNAL_stdio_vsnprintf(buf, cchBuf, fmt, args);
}
#if defined(__cplusplus) &&\
    defined(STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT)

/* buffer-overload */
template <ss_size_t N>
inline
int
stlsoft_C_vsnprintf(
    ss_char_a_t       (&buf)[N]
,   ss_char_a_t const*  fmt
,   va_list             args
)
{
    return STLSOFT_API_INTERNAL_stdio_vsnprintf(&buf[0], N, fmt, args);
}
#endif /* C++ && STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
#ifdef STLSOFT_vsnwprintf_SUPPORT

/** vsnwprintf() - equivalent
 */
STLSOFT_INLINE
int
stlsoft_C_vsnwprintf(
    ss_char_w_t*        buf
,   ss_size_t           cchBuf
,   ss_char_w_t const*  fmt
,   va_list             args
)
{
    return STLSOFT_API_INTERNAL_stdio_vsnwprintf(buf, cchBuf, fmt, args);
}
# if defined(__cplusplus) &&\
     defined(STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT)

/* buffer-overload */
template <ss_size_t N>
inline
int
stlsoft_C_vsnwprintf(
    ss_char_w_t       (&buf)[N]
,   ss_char_w_t const*  fmt
,   va_list             args
)
{
    return STLSOFT_API_INTERNAL_stdio_vsnwprintf(&buf[0], N, fmt, args);
}
# endif /* C++ && STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
#endif /* STLSOFT_vsnwprintf_SUPPORT */


/* /////////////////////////////////////////////////////////////////////////
 * C++ functions
 */

#ifndef STLSOFT_NO_NAMESPACE

inline
int
vsnprintf(
    ss_char_a_t*        buf
,   ss_size_t           cchBuf
,   ss_char_a_t const*  fmt
,   va_list             args
)
{
    return stlsoft_C_vsnprintf(buf, cchBuf, fmt, args);
}

# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
template <ss_size_t N>
inline
int
vsnprintf(
    ss_char_a_t       (&buf)[N]
,   ss_char_a_t const*  fmt
,   va_list             args
)
{
    return stlsoft_C_vsnprintf(&buf[0], N, fmt, args);
}
# endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
# ifdef STLSOFT_vsnwprintf_SUPPORT

inline
int
vsnwprintf(
    ss_char_w_t*        buf
,   ss_size_t           cchBuf
,   ss_char_w_t const*  fmt
,   va_list             args
)
{
    return stlsoft_C_vsnwprintf(buf, cchBuf, fmt, args);
}
#  ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

template <ss_size_t N>
inline
int
vsnwprintf(
    ss_char_w_t       (&buf)[N]
,   ss_char_w_t const*  fmt
,   va_list             args
)
{
    return stlsoft_C_vsnwprintf(&buf[0], N, fmt, args);
}
#  endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
# endif /* STLSOFT_vsnwprintf_SUPPORT */
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} /* namespace stlsoft */
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_UTIL_STRING_H_VSNPRINTF */

/* ///////////////////////////// end of file //////////////////////////// */

