/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/string/trim_functions.h
 *
 * Purpose: C string slice trimming functions.
 *
 * Created: 10th August 2026
 * Updated: 26th October 2026
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


/** \file stlsoft/string/trim_functions.h
 *
 * \brief [C] Definition of the STLSoft_C_string_trim_*() suite of functions
 *   (\ref group__library__String "String" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_STRING_H_TRIM_FUNCTIONS
#define STLSOFT_INCL_STLSOFT_STRING_H_TRIM_FUNCTIONS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_STRING_H_TRIM_FUNCTIONS_MAJOR      1
# define STLSOFT_VER_STLSOFT_STRING_H_TRIM_FUNCTIONS_MINOR      0
# define STLSOFT_VER_STLSOFT_STRING_H_TRIM_FUNCTIONS_REVISION   0
# define STLSOFT_VER_STLSOFT_STRING_H_TRIM_FUNCTIONS_EDIT       3
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

#ifndef STLSOFT_INCL_STLSOFT_STRING_H_STRING_SLICE
# include <stlsoft/string/string_slice.h>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_H_STRING_SLICE */


/* /////////////////////////////////////////////////////////////////////////
 * language
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* !STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

STLSOFT_INLINE
ss_truthy_t
STLSoft_C_string_slice_trim_contains_char_m_(
    stlsoft_C_string_slice_m_t  trim_chars
,   char                        ch
)
{
    size_t i;

    for (i = 0; i != trim_chars.len; ++i)
    {
        if (trim_chars.ptr[i] == ch)
        {
            return 1;
        }
    }

    return 0;
}
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

STLSOFT_INLINE
stlsoft_C_string_slice_m_t
STLSoft_C_string_trim_left_chars_a(
    stlsoft_C_string_slice_m_t       slice
,   stlsoft_C_string_slice_m_t const trim_chars
)
{
    size_t first;

    STLSOFT_ASSERT(0 == slice.len || NULL != slice.ptr);
    STLSOFT_ASSERT(0 == trim_chars.len || NULL != trim_chars.ptr);

    for (first = 0; first != slice.len; ++first)
    {
        if (!STLSoft_C_string_slice_trim_contains_char_m_(trim_chars, slice.ptr[first]))
        {
            break;
        }
    }

    return stlsoft_C_string_slice_make_m(
        (first == slice.len) ? NULL : slice.ptr + first
    ,   slice.len - first);
}

STLSOFT_INLINE
stlsoft_C_string_slice_m_t
STLSoft_C_string_trim_right_chars_a(
    stlsoft_C_string_slice_m_t       slice
,   stlsoft_C_string_slice_m_t const trim_chars
)
{
    size_t last;

    STLSOFT_ASSERT(0 == slice.len || NULL != slice.ptr);
    STLSOFT_ASSERT(0 == trim_chars.len || NULL != trim_chars.ptr);

    last = slice.len;

    while (0 != last &&
           STLSoft_C_string_slice_trim_contains_char_m_(trim_chars, slice.ptr[last - 1]))
    {
        --last;
    }

    return stlsoft_C_string_slice_make_m(
        (0u == last) ? NULL : slice.ptr
    ,   last);
}

STLSOFT_INLINE
stlsoft_C_string_slice_m_t
STLSoft_C_string_trim_all_chars_a(
    stlsoft_C_string_slice_m_t       slice
,   stlsoft_C_string_slice_m_t const trim_chars
)
{
    size_t first;
    size_t last;

    STLSOFT_ASSERT(0 == slice.len || NULL != slice.ptr);
    STLSOFT_ASSERT(0 == trim_chars.len || NULL != trim_chars.ptr);

    for (first = 0; first != slice.len; ++first)
    {
        if (!STLSoft_C_string_slice_trim_contains_char_m_(trim_chars, slice.ptr[first]))
        {
            break;
        }
    }

    last = slice.len;

    while (first != last &&
           STLSoft_C_string_slice_trim_contains_char_m_(trim_chars, slice.ptr[last - 1]))
    {
        --last;
    }

    return stlsoft_C_string_slice_make_m(
        (first == last) ? NULL : slice.ptr + first
    ,   last - first);
}

STLSOFT_INLINE
stlsoft_C_string_slice_m_t
STLSoft_C_string_trim_left_a(
    stlsoft_C_string_slice_m_t slice
)
{
    static char const trim_chars[] = " \n\r\t\v";
    stlsoft_C_string_slice_m_t const chars = { sizeof(trim_chars) - 1, trim_chars };

    return STLSoft_C_string_trim_left_chars_a(slice, chars);
}

STLSOFT_INLINE
stlsoft_C_string_slice_m_t
STLSoft_C_string_trim_right_a(
    stlsoft_C_string_slice_m_t slice
)
{
    static char const trim_chars[] = " \n\r\t\v";
    stlsoft_C_string_slice_m_t const chars = { sizeof(trim_chars) - 1, trim_chars };

    return STLSoft_C_string_trim_right_chars_a(slice, chars);
}

STLSOFT_INLINE
stlsoft_C_string_slice_m_t
STLSoft_C_string_trim_all_a(
    stlsoft_C_string_slice_m_t slice
)
{
    static char const trim_chars[] = " \n\r\t\v";
    stlsoft_C_string_slice_m_t const chars = { sizeof(trim_chars) - 1, trim_chars };

    return STLSoft_C_string_trim_all_chars_a(slice, chars);
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} /* namespace stlsoft */
#endif /* !STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_STRING_H_TRIM_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */

