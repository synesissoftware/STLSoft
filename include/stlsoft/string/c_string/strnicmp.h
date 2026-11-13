/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/string/c_string/strnicmp.h
 *
 * Purpose: Definition of stlsoft_C_strnicmp() and stlsoft_C_wcsnicmp()
 *
 * Created: 25th November 2020
 * Updated: 13th November 2026
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


/** \file stlsoft/string/c_string/strnicmp.h
 *
 * \brief [C, C++] Definition of stlsoft_C_strnicmp() and stlsoft_C_wcsnicmp()
 *
 *   (\ref group__library__String "String" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_STRNICMP
#define STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_STRNICMP

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_STRNICMP_MAJOR       1
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_STRNICMP_MINOR       0
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_STRNICMP_REVISION    5
# define STLSOFT_VER_STLSOFT_STRING_C_STRING_H_STRNICMP_EDIT        8
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

#ifndef STLSOFT_INCL_H_WCTYPE
# define STLSOFT_INCL_H_WCTYPE
# include <wctype.h>
#endif /* !STLSOFT_INCL_H_WCTYPE */

#ifndef STLSOFT_INCL_STLSOFT_API_internal_h_ctype
# include <stlsoft/api/internal/ctype.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_internal_h_ctype */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Compares up to \c n characters of two C-style strings,
 * case-insensitively
 *
 * \param s1 Pointer to the first string
 * \param s2 Pointer to the second string
 * \param n Maximum number of characters to compare
 */
/* DOXYGEN_PARAM_EYECATCHER: brief/retval previously described a find-style
 * API (n1/n2/nullptr); confirm compare semantics and return contract
 */
STLSOFT_INLINE
int
stlsoft_C_strnicmp(
    char const* s1
,   char const* s2
,   size_t      n
)
{
    for (; 0 != n; --n, ++s1, ++s2)
    {
        unsigned char const c1 = (unsigned char)*s1;
        unsigned char const c2 = (unsigned char)*s2;

        if (c1 != c2)
        {
            int const d = STLSOFT_API_INTERNAL_ctype_ASCII_fold_char_toupper_m(c1) -
                            STLSOFT_API_INTERNAL_ctype_ASCII_fold_char_toupper_m(c2);

            if (0 != d)
            {
                return d;
            }
        }
        else if ('\0' == *s1)
        {
            return 0;
        }
    }

    return 0;
}

/** Compares up to \c n characters of two wide C-style strings,
 * case-insensitively
 *
 * \param s1 Pointer to the first string
 * \param s2 Pointer to the second string
 * \param n Maximum number of characters to compare
 */
/* DOXYGEN_PARAM_EYECATCHER: brief/retval previously described a find-style
 * API (n1/n2/nullptr); confirm compare semantics and return contract
 */
STLSOFT_INLINE
int
stlsoft_C_wcsnicmp(
    wchar_t const*  s1
,   wchar_t const*  s2
,   size_t          n
)
{
    for (; 0 != n; --n, ++s1, ++s2)
    {
        wchar_t const c1 = *s1;
        wchar_t const c2 = *s2;

        if (c1 != c2)
        {
            int const d = STLSOFT_API_INTERNAL_ctype_ASCII_fold_char_toupper_w(c1) -
                            STLSOFT_API_INTERNAL_ctype_ASCII_fold_char_toupper_w(c2);

            if (0 != d)
            {
                return d;
            }
        }
        else if (L'\0' == c1)
        {
            return 0;
        }
    }

    return 0;
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
namespace c_string
{


/* /////////////////////////////////////////////////////////////////////////
 * API functions (C++)
 */

inline
int
strnicmp(
    char const* s1
,   char const* s2
,   size_t      n
)
{
    return stlsoft_C_strnicmp(s1, s2, n);
}

inline
int
strnicmp(
    wchar_t const*  s1
,   wchar_t const*  s2
,   size_t          n
)
{
    return stlsoft_C_wcsnicmp(s1, s2, n);
}

inline
int
wcsnicmp(
    wchar_t const*  s1
,   wchar_t const*  s2
,   size_t          n
)
{
    return stlsoft_C_wcsnicmp(s1, s2, n);
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

} /* namespace c_string */
} /* namespace stlsoft */
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_STRNICMP */

/* ///////////////////////////// end of file //////////////////////////// */

