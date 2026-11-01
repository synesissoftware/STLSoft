/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/api/external/memfns.h
 *
 * Purpose: External adaptations for memXXX() functions.
 *
 * Created: 25th September 2024
 * Updated: 2nd November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2024-2026, Matthew Wilson and Synesis Information Systems
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


/* WARNING: this file contains undocumented external features that are
 * subject to change at any time, so if you use them it is at your own risk.
 */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_memfns
#define STLSOFT_INCL_STLSOFT_API_external_h_memfns


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# include <stlsoft/stlsoft.h>
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#if 0
#elif 0 || \
      defined(STLSOFT_COMPILER_IS_BORLAND) || \
      (   defined(STLSOFT_COMPILER_IS_INTEL) && \
          defined(_WIN32))|| \
      defined(STLSOFT_COMPILER_IS_MSVC) || \
      0
# ifndef STLSOFT_INCL_H_MEMORY
#  define STLSOFT_INCL_H_MEMORY
#  include <memory.h>
# endif /* !STLSOFT_INCL_H_MEMORY */
#else /* ? compiler */
# ifndef STLSOFT_INCL_H_STRING
#  define STLSOFT_INCL_H_STRING
#  include <string.h>
# endif /* !STLSOFT_INCL_H_STRING */
#endif /* compiler */
#ifndef STLSOFT_INCL_H_STDDEF
# define STLSOFT_INCL_H_STDDEF
# include <stddef.h>
#endif /* !STLSOFT_INCL_H_STDDEF */
#ifndef STLSOFT_INCL_H_WCHAR
# define STLSOFT_INCL_H_WCHAR
# include <wchar.h>
#endif /* !STLSOFT_INCL_H_WCHAR */


/* /////////////////////////////////////////////////////////////////////////
 * memory functions
 */

#ifndef STLSOFT_API_EXTERNAL_memfns_memchr
# define STLSOFT_API_EXTERNAL_memfns_memchr                 STLSOFT_NS_GLOBAL_(memchr)
#endif /* !STLSOFT_API_EXTERNAL_memfns_memchr */

#ifndef STLSOFT_API_EXTERNAL_memfns_memcmp
# define STLSOFT_API_EXTERNAL_memfns_memcmp                 STLSOFT_NS_GLOBAL_(memcmp)
#endif /* !STLSOFT_API_EXTERNAL_memfns_memcmp */

#ifndef STLSOFT_API_EXTERNAL_memfns_memcpy
# define STLSOFT_API_EXTERNAL_memfns_memcpy                 STLSOFT_NS_GLOBAL_(memcpy)
#endif /* !STLSOFT_API_EXTERNAL_memfns_memcpy */

#ifndef STLSOFT_API_EXTERNAL_memfns_memmove
# define STLSOFT_API_EXTERNAL_memfns_memmove                STLSOFT_NS_GLOBAL_(memmove)
#endif /* !STLSOFT_API_EXTERNAL_memfns_memmove */

#ifndef STLSOFT_API_EXTERNAL_memfns_memset
# define STLSOFT_API_EXTERNAL_memfns_memset                 STLSOFT_NS_GLOBAL_(memset)
#endif /* !STLSOFT_API_EXTERNAL_memfns_memset */

#ifndef STLSOFT_API_EXTERNAL_memfns_wmemchr
# define STLSOFT_API_EXTERNAL_memfns_wmemchr                STLSOFT_NS_GLOBAL_(wmemchr)
#endif /* !STLSOFT_API_EXTERNAL_memfns_wmemchr */

#ifndef STLSOFT_API_EXTERNAL_memfns_wmemcmp
# define STLSOFT_API_EXTERNAL_memfns_wmemcmp                STLSOFT_NS_GLOBAL_(wmemcmp)
#endif /* !STLSOFT_API_EXTERNAL_memfns_wmemcmp */

#ifndef STLSOFT_API_EXTERNAL_memfns_wmemcpy
# define STLSOFT_API_EXTERNAL_memfns_wmemcpy                STLSOFT_NS_GLOBAL_(wmemcpy)
#endif /* !STLSOFT_API_EXTERNAL_memfns_wmemcpy */

#ifndef STLSOFT_API_EXTERNAL_memfns_wmemmove
# define STLSOFT_API_EXTERNAL_memfns_wmemmove               STLSOFT_NS_GLOBAL_(wmemmove)
#endif /* !STLSOFT_API_EXTERNAL_memfns_wmemmove */

#ifndef STLSOFT_API_EXTERNAL_memfns_wmemset
# define STLSOFT_API_EXTERNAL_memfns_wmemset                STLSOFT_NS_GLOBAL_(wmemset)
#endif /* !STLSOFT_API_EXTERNAL_memfns_wmemset */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_memfns */

/* ///////////////////////////// end of file //////////////////////////// */

