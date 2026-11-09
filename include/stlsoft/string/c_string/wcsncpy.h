/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/string/c_string/wcsncpy.h
 *
 * Purpose: Definition of stlsoft_C_wcsncpy()
 *
 * Created: 2nd November 2026
 * Updated: 9th November 2026
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


/** \file stlsoft/string/c_string/wcsncpy.h
 *
 * \brief [C, C++] Definition of stlsoft_C_wcsncpy()
 *   (\ref group__library__String "String" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_WCSNCPY
#define STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_WCSNCPY

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_WCSNCPY_MAJOR    1
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_WCSNCPY_MINOR    0
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_WCSNCPY_REVISION 3
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_WCSNCPY_EDIT     3
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

#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS
# ifndef STLSOFT_INCL_H_ERRNO
#  define STLSOFT_INCL_H_ERRNO
#  include <errno.h>
# endif /* !STLSOFT_INCL_H_ERRNO */
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
#ifndef STLSOFT_INCL_H_STDDEF
# define STLSOFT_INCL_H_STDDEF
# include <stddef.h>
#endif /* !STLSOFT_INCL_H_STDDEF */
#ifndef STLSOFT_INCL_H_WCHAR
# define STLSOFT_INCL_H_WCHAR
# include <wchar.h>
#endif /* !STLSOFT_INCL_H_WCHAR */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Copies at most \c cchSrc wide characters from \c src into \c dest.
 *
 * \param dest Destination buffer. It may be \c nullptr only when \c cchDest
 *   is 0;
 * \param cchDest Capacity of \c dest, in wide characters. The secure CRT
 *   needs room for a terminating NUL. A capacity of 0 copies nothing;
 * \param src Source. It is read only when \c cchDest is not 0;
 * \param cchSrc Maximum number of wide characters copied from \c src;
 *
 * \return \c dest in all circumstances.
 *
 * A \c cchDest of 0 returns \c dest without reading \c src or writing
 * through \c dest. \c errno is unchanged. Neither \c wcsncpy() nor
 * \c wcsncpy_s() is called.
 *
 * When \c STLSOFT_USING_SAFE_STR_FUNCTIONS is defined the function calls
 * \c wcsncpy_s(dest, cchDest, src, cchSrc). A successful copy is
 * NUL-terminated and is not padded after that NUL. A \c cchSrc of 0 stores
 * a NUL at \c dest[0]. Success leaves \c errno unchanged. Failure assigns
 * the \c wcsncpy_s result to \c errno. A result that does not fit produces
 * \c ERANGE and writes a NUL at \c dest[0]. \c dest is returned either way.
 *
 * Otherwise the function calls \c wcsncpy(dest, src, cchSrc) and does not
 * consult a non-zero \c cchDest. Exactly \c cchSrc wide characters are
 * written. If a NUL is copied before that count is exhausted, the remainder
 * of the count is padded with NULs. If no NUL is copied, the destination is
 * not terminated. \c errno is unchanged. \c dest must hold \c cchSrc wide
 * characters.
 *
 * \pre 0 == cchDest || nullptr != dest
 */
STLSOFT_INLINE
wchar_t*
stlsoft_C_wcsncpy(
    wchar_t*        dest
,   size_t          cchDest
,   wchar_t const*  src
,   size_t          cchSrc
)
{
    STLSOFT_ASSERT(0 == cchDest || NULL != dest);

    if (0 == cchDest)
    {
        return dest;
    }
    else
    {
#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

        errno_t const e = STLSOFT_NS_GLOBAL(wcsncpy_s)(
            dest
        ,   cchDest
        ,   src
        ,   cchSrc
        );

        if (0 != e)
        {
            errno = e;
        }

        return dest;
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

        return STLSOFT_NS_GLOBAL(wcsncpy)(dest, src, cchSrc);
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_WCSNCPY */

/* ///////////////////////////// end of file //////////////////////////// */
