/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/string/c_string/strdup.h
 *
 * Purpose: Definition of stlsoft_C_strdup() and stlsoft_C_wcsdup()
 *
 * Created: 1st November 2026
 * Updated: 1st November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2026, Matthew Wilson and Synesis Information Systems
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


/** \file stlsoft/string/c_string/strdup.h
 *
 * \brief [C, C++] Definition of stlsoft_C_strdup() and stlsoft_C_wcsdup()
 *   (\ref group__library__String "String" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_STRDUP
#define STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_STRDUP

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_STRDUP_MAJOR     1
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_STRDUP_MINOR     0
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_STRDUP_REVISION  1
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_STRDUP_EDIT      1
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

#ifndef STLSOFT_INCL_STLSOFT_INTERNAL_H_SAFESTR
# include <stlsoft/internal/safestr.h>
#endif /* !STLSOFT_INCL_STLSOFT_INTERNAL_H_SAFESTR */

#ifndef STLSOFT_INCL_H_STDDEF
# define STLSOFT_INCL_H_STDDEF
# include <stddef.h>
#endif /* !STLSOFT_INCL_H_STDDEF */
#ifndef STLSOFT_INCL_H_STDLIB
# define STLSOFT_INCL_H_STDLIB
# include <stdlib.h>
#endif /* !STLSOFT_INCL_H_STDLIB */
#ifndef STLSOFT_INCL_H_STRING
# define STLSOFT_INCL_H_STRING
# include <string.h>
#endif /* !STLSOFT_INCL_H_STRING */
#ifndef STLSOFT_INCL_H_WCHAR
# define STLSOFT_INCL_H_WCHAR
# include <wchar.h>
#endif /* !STLSOFT_INCL_H_WCHAR */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Allocates a copy of a NUL-terminated multibyte string.
 *
 * \param src Source string. It may be \c nullptr;
 *
 * \return A new string, or \c nullptr when \c src is \c nullptr or
 *   allocation fails. The caller releases a non-null result with \c free().
 *
 * A null \c src returns \c nullptr. \c errno is unchanged. Neither
 * \c strdup() nor \c _strdup() is called.
 *
 * Otherwise the function calls \c _strdup(src) when
 * \c STLSOFT_USING_SAFE_STR_FUNCTIONS is defined, and \c strdup(src)
 * otherwise. The copy includes the terminating NUL. Allocation failure
 * returns \c nullptr and leaves \c errno as that call set it.
 */
STLSOFT_INLINE
char*
stlsoft_C_strdup(
    char const* src
)
{
    if (NULL == src)
    {
        return NULL;
    }
    else
    {
#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

        return STLSOFT_NS_GLOBAL(_strdup)(src);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

        return STLSOFT_NS_GLOBAL(strdup)(src);
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
    }
}

/** Allocates a copy of a NUL-terminated wide string.
 *
 * \param src Source string. It may be \c nullptr;
 *
 * \return A new string, or \c nullptr when \c src is \c nullptr or
 *   allocation fails. The caller releases a non-null result with \c free().
 *
 * A null \c src returns \c nullptr. \c errno is unchanged. Neither
 * \c wcsdup() nor \c _wcsdup() is called.
 *
 * Otherwise the function calls \c _wcsdup(src) when
 * \c STLSOFT_USING_SAFE_STR_FUNCTIONS is defined. Otherwise it calls
 * \c wcsdup(src), except where that function is absent: the copy is then
 * allocated with \c malloc() and filled with \c memcpy(). The copy includes
 * the terminating NUL. Allocation failure returns \c nullptr and leaves
 * \c errno as the allocator set it.
 */
STLSOFT_INLINE
wchar_t*
stlsoft_C_wcsdup(
    wchar_t const*  src
)
{
    if (NULL == src)
    {
        return NULL;
    }
    else
    {
#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

        return STLSOFT_NS_GLOBAL(_wcsdup)(src);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

# if defined(STLSOFT_COMPILER_IS_BORLAND) ||\
     (   defined(STLSOFT_COMPILER_IS_GCC) &&\
         !defined(WIN32)) ||\
     defined(STLSOFT_COMPILER_IS_WATCOM)

        size_t const    n = STLSOFT_NS_GLOBAL(wcslen)(src);
        wchar_t* const  r = stlsoft_static_cast(wchar_t*, STLSOFT_NS_GLOBAL(malloc)(sizeof(wchar_t) * (1u + n));

        if (NULL != r)
        {
            STLSOFT_NS_GLOBAL(memcpy)(r, src, sizeof(wchar_t) * (1u + n));
        }

        return r;
# else /* ? compiler */

        return STLSOFT_NS_GLOBAL(wcsdup)(src);
# endif /* compiler */
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_STRDUP */

/* ///////////////////////////// end of file //////////////////////////// */
