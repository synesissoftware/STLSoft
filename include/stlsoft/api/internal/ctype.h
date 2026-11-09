/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/api/internal/ctype.h
 *
 * Purpose: Internal adaptations and extensions for ctype.h constructs.
 *
 * Created: 8th November 2026
 * Updated: 8th November 2026
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

#ifndef STLSOFT_INCL_STLSOFT_API_internal_h_ctype
#define STLSOFT_INCL_STLSOFT_API_internal_h_ctype


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

#ifndef STLSOFT_INCL_H_CTYPE
# define STLSOFT_INCL_H_CTYPE
# include <ctype.h>
#endif /* !STLSOFT_INCL_H_CTYPE */
#ifndef STLSOFT_INCL_H_WCHAR
# define STLSOFT_INCL_H_WCHAR
# include <wchar.h>
#endif /* !STLSOFT_INCL_H_WCHAR */


/* /////////////////////////////////////////////////////////////////////////
 * ctype functions
 */

/** \brief Folds an ASCII character to lowercase
 *
 * If \c ch is an uppercase ASCII letter (<code>'A'</code>–<code>'Z'</code>)
 * the corresponding lowercase letter is returned; otherwise \c ch is
 * returned unchanged.
 *
 * \param ch The character to fold;
 *
 * \return The folded character.
 */
STLSOFT_INLINE
char
STLSOFT_API_INTERNAL_ctype_ASCII_fold_char_tolower_m(
    char    ch
)
{
    if ('A' <= ch &&
        ch <= 'Z')
    {
        /* NOTE: the usual good-practice to manipulate via `unsigned char`
         * is not needed here, due the range(s) involved.
         */

        ch = (char)(ch + ('a' - 'A'));
    }

    return ch;
}

/** \brief Folds an ASCII character to uppercase
 *
 * If \c ch is a lowercase ASCII letter (<code>'a'</code>–<code>'z'</code>)
 * the corresponding uppercase letter is returned; otherwise \c ch is
 * returned unchanged.
 *
 * \param ch The character to fold;
 *
 * \return The folded character.
 */
STLSOFT_INLINE
char
STLSOFT_API_INTERNAL_ctype_ASCII_fold_char_toupper_m(
    char    ch
)
{
    if ('a' <= ch &&
        ch <= 'z')
    {
        /* NOTE: the usual good-practice to manipulate via `unsigned char`
         * is not needed here, due the range(s) involved.
         */

        ch = (char)(ch - ('a' - 'A'));
    }

    return ch;
}

/** \brief Folds an ASCII wide character to lowercase
 *
 * If \c ch is an uppercase ASCII letter (<code>L'A'</code>–<code>L'Z'</code>)
 * the corresponding lowercase letter is returned; otherwise \c ch is
 * returned unchanged.
 *
 * \param ch The wide character to fold;
 *
 * \return The folded character.
 */
STLSOFT_INLINE
wchar_t
STLSOFT_API_INTERNAL_ctype_ASCII_fold_char_tolower_w(
    wchar_t ch
)
{
    if (L'A' <= ch &&
        ch <= L'Z')
    {
        ch = (wchar_t)(ch + (L'a' - L'A'));
    }

    return ch;
}

/** \brief Folds an ASCII wide character to uppercase
 *
 * If \c ch is a lowercase ASCII letter (<code>L'a'</code>–<code>L'z'</code>)
 * the corresponding uppercase letter is returned; otherwise \c ch is
 * returned unchanged.
 *
 * \param ch The wide character to fold;
 *
 * \return The folded character.
 */
STLSOFT_INLINE
wchar_t
STLSOFT_API_INTERNAL_ctype_ASCII_fold_char_toupper_w(
    wchar_t ch
)
{
    if (L'a' <= ch &&
        ch <= L'z')
    {
        ch = (wchar_t)(ch - (L'a' - L'A'));
    }

    return ch;
}



/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_API_internal_h_ctype */

/* ///////////////////////////// end of file //////////////////////////// */

