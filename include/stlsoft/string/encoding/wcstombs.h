/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/string/encoding/wcstombs.h
 *
 * Purpose: Definition of stlsoft_C_wcstombs()
 *
 * Created: 28th October 2026
 * Updated: 28th October 2026
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


/** \file stlsoft/string/encoding/wcstombs.h
 *
 * \brief [C, C++] Definition of stlsoft_C_wcstombs()
 *
 *   (\ref group__library__String "String" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_STRING_ENCODING_H_WCSTOMBS
#define STLSOFT_INCL_STLSOFT_STRING_ENCODING_H_WCSTOMBS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_STRING_ENCODING_H_WCSTOMBS_MAJOR       1
# define STLSOFT_VER_STLSOFT_STRING_ENCODING_H_WCSTOMBS_MINOR       0
# define STLSOFT_VER_STLSOFT_STRING_ENCODING_H_WCSTOMBS_REVISION    1
# define STLSOFT_VER_STLSOFT_STRING_ENCODING_H_WCSTOMBS_EDIT        2
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

#ifndef STLSOFT_INCL_H_ERRNO
# define STLSOFT_INCL_H_ERRNO
# include <errno.h>
#endif /* !STLSOFT_INCL_H_ERRNO */
#ifndef STLSOFT_INCL_H_STDLIB
# define STLSOFT_INCL_H_STDLIB
# include <stdlib.h>
#endif /* !STLSOFT_INCL_H_STDLIB */
#ifndef STLSOFT_INCL_H_WCHAR
# define STLSOFT_INCL_H_WCHAR
# include <wchar.h>
#endif /* !STLSOFT_INCL_H_WCHAR */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Converts wide characters to multibyte characters.
 *
 * \param dest Destination, or NULL to query the length of a NUL-terminated
 *   src. cchDest and cchSrc are ignored in that case.
 * \param cchDest Capacity of dest, in bytes.
 * \param src Source string.
 * \param cchSrc Maximum number of source characters to read.
 *
 * \return The number of bytes stored or required, excluding the terminating
 *   NUL, or (size_t)-1 when src is not valid in the current locale (errno
 *   is set).
 *
 * At most min(cchDest, cchSrc) characters are stored. A NUL is written at
 * [count] when count < cchDest. When the destination is full, the classic
 * CRT stores cchDest characters and does not write a NUL; the secure CRT
 * keeps a NUL in the last slot and the count is cchDest - 1. That partial
 * store is a success.
 */
STLSOFT_INLINE
size_t
stlsoft_C_wcstombs(
    char*           dest
,   size_t          cchDest
,   wchar_t const*  src
,   size_t          cchSrc
)
{
    if (NULL == dest)
    {
#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

        size_t  numConverted = 0;
        int     err;

        STLSOFT_SUPPRESS_UNUSED(cchDest);
        STLSOFT_SUPPRESS_UNUSED(cchSrc);

        err = STLSOFT_NS_GLOBAL(wcstombs_s)(&numConverted, NULL, 0, src, 0);

        if (0 != err)
        {
            errno = err;

            return (size_t)-1;
        }

        if (0 != numConverted)
        {
            --numConverted;
        }

        return numConverted;
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

        STLSOFT_SUPPRESS_UNUSED(cchDest);
        STLSOFT_SUPPRESS_UNUSED(cchSrc);

        return STLSOFT_NS_GLOBAL(wcstombs)(NULL, src, 0);
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
    }

    if (0 == cchDest ||
        0 == cchSrc)
    {
        if (0 != cchDest)
        {
            dest[0] = '\0';
        }

        return 0;
    }

#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

    {
        size_t const    limit = (cchSrc < cchDest) ? cchSrc : cchDest;
        size_t          numConverted = 0;
        int             err;

        if (limit < cchDest)
        {
            err = STLSOFT_NS_GLOBAL(wcstombs_s)(&numConverted, dest, limit + 1, src, limit);
        }
        else
        {
            err = STLSOFT_NS_GLOBAL(wcstombs_s)(&numConverted, dest, cchDest, src, _TRUNCATE);
        }

        if (STRUNCATE == err)
        {
            errno = 0;

            if (0 != numConverted)
            {
                --numConverted;
            }

            return numConverted;
        }

        if (0 != err)
        {
            errno = err;

            return (size_t)-1;
        }

        if (0 != numConverted)
        {
            --numConverted;
        }

        return numConverted;
    }
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

    {
        size_t const    limit = (cchSrc < cchDest) ? cchSrc : cchDest;
        size_t const    n = STLSOFT_NS_GLOBAL(wcstombs)(dest, src, limit);

        if ((size_t)-1 == n)
        {
            return n;
        }

        if (n < cchDest)
        {
            dest[n] = '\0';
        }

        return n;
    }
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
namespace encoding
{


/* /////////////////////////////////////////////////////////////////////////
 * API functions (C++)
 */

inline
size_t
wcstombs(
    char*           dest
,   size_t          cchDest
,   wchar_t const*  src
,   size_t          cchSrc
)
{
    return stlsoft_C_wcstombs(dest, cchDest, src, cchSrc);
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

} /* namespace encoding */
} /* namespace stlsoft */
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_STRING_ENCODING_H_WCSTOMBS */

/* ///////////////////////////// end of file //////////////////////////// */


