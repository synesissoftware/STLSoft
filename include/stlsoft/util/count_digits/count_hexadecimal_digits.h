/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/util/count_digits/count_hexadecimal_digits.h
 *
 * Purpose: Functions for efficient counting of hexadecimal digits in
 *          integers.
 *
 * Created: 18th December 2024
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2024, Matthew Wilson and Synesis Information Systems
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


/** \file stlsoft/util/count_digits/count_hexadecimal_digits.h
 *
 * \brief [C, C++] Functions for efficient counting of hexadecimal digits in
 *   integers
 *   (\ref group__library__Utility "Utility" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_HEXADECIMAL_DIGITS
#define STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_HEXADECIMAL_DIGITS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_HEXADECIMAL_DIGITS_MAJOR    1
# define STLSOFT_VER_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_HEXADECIMAL_DIGITS_MINOR    0
# define STLSOFT_VER_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_HEXADECIMAL_DIGITS_REVISION 2
# define STLSOFT_VER_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_HEXADECIMAL_DIGITS_EDIT     2
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


/* /////////////////////////////////////////////////////////////////////////
 * API functions (C)
 */

STLSOFT_INLINE
int
stlsoft_C_count_hexadecimal_digits_uint32(
    STLSOFT_NS_QUAL(ss_uint32_t) i
)
{
    if (0 == i)
    {
        return 1u;
    }
    else
    {
        if (i >= 0x10000)
        {
            if (i >= 0x1000000)
            {
                if (i >= 0x10000000)
                {
                    return 8;
                }
                else
                {
                    return 7;
                }
            }
            else
            {
                if (i >= 0x100000)
                {
                    return 6;
                }
                else
                {
                    return 5;
                }
            }
        }
        else
        {
            if (i >= 0x100)
            {
                if (i >= 0x1000)
                {
                    return 4;
                }
                else
                {
                    return 3;
                }
            }
            else
            {
                if (i >= 0x10)
                {
                    return 2;
                }
                else
                {
                    return 1;
                }
            }
        }
    }
}

STLSOFT_INLINE
int
stlsoft_C_count_hexadecimal_digits_uint64(
    STLSOFT_NS_QUAL(ss_uint64_t) i
)
{
    if (0 == i)
    {
        return 1u;
    }
    else
    {
        if (i >= 0x100000000)
        {
            if (i >= 0x1000000000000)
            {
                if (i >= 0x100000000000000)
                {
                    if (i >= 0x1000000000000000)
                    {
                        return 16;
                    }
                    else
                    {
                        return 15;
                    }
                }
                else
                {
                    if (i >= 0x10000000000000)
                    {
                        return 14;
                    }
                    else
                    {
                        return 13;
                    }
                }
            }
            else
            {
                if (i >= 0x10000000000)
                {
                    if (i >= 0x100000000000)
                    {
                        return 12;
                    }
                    else
                    {
                        return 11;
                    }
                }
                else
                {
                    if (i >= 0x1000000000)
                    {
                        return 10;
                    }
                    else
                    {
                        return 9;
                    }
                }
            }
        }
        else
        {
            if (i >= 0x10000)
            {
                if (i >= 0x1000000)
                {
                    if (i >= 0x10000000)
                    {
                        return 8;
                    }
                    else
                    {
                        return 7;
                    }
                }
                else
                {
                    if (i >= 0x100000)
                    {
                        return 6;
                    }
                    else
                    {
                        return 5;
                    }
                }
            }
            else
            {
                if (i >= 0x100)
                {
                    if (i >= 0x1000)
                    {
                        return 4;
                    }
                    else
                    {
                        return 3;
                    }
                }
                else
                {
                    if (i >= 0x10)
                    {
                        return 2;
                    }
                    else
                    {
                        return 1;
                    }
                }
            }
        }
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifdef __cplusplus

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * API functions (C++)
 */

inline
int
count_hexadecimal_digits(
    ss_uint8_t i
)
{
    return stlsoft_C_count_hexadecimal_digits_uint32(i);
}

inline
int
count_hexadecimal_digits(
    ss_uint16_t i
)
{
    return stlsoft_C_count_hexadecimal_digits_uint32(i);
}

inline
int
count_hexadecimal_digits(
    ss_uint32_t i
)
{
    return stlsoft_C_count_hexadecimal_digits_uint32(i);
}

inline
int
count_hexadecimal_digits(
    ss_uint64_t i
)
{
    return stlsoft_C_count_hexadecimal_digits_uint64(i);
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} /* namespace stlsoft */
#endif /* STLSOFT_NO_NAMESPACE */

#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_HEXADECIMAL_DIGITS */

/* ///////////////////////////// end of file //////////////////////////// */

