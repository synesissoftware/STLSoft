/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/diagnostics/gram_utils.hpp
 *
 * Purpose: OOM Histogram utilities.
 *
 * Created: 14th May 2013
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2013-2019, Matthew Wilson and Synesis Software
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


/** \file stlsoft/diagnostics/gram_utils.hpp
 *
 * \brief [C++] OOM Histogram utilities
 *   (\ref group__library__Diagnostic "Diagnostic" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_GRAM_UTILS
#define STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_GRAM_UTILS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_GRAM_UTILS_MAJOR       2
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_GRAM_UTILS_MINOR       0
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_GRAM_UTILS_REVISION    2
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_GRAM_UTILS_EDIT        19
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
#ifndef STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DECIMAL_DIGITS
# include <stlsoft/util/count_digits/count_decimal_digits.h>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DECIMAL_DIGITS */


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

/** Calculates the Decimal Order-Of-Magnitude of a `uint64_t`, which is 0
 * for 0, and the number of digits for every other number
 *
 * \see stlsoft::count_decimal_digits
 */
inline
unsigned
calc_doom(
    ss_uint64_t v
)
{
    // NOTE: since the _vast_ majority of OOM values will be in the lower
    // part of the 64-bit range, we do a low-biased form of the algorithm
    // provided by count_decimal_digits()

    if (v >= 100000000)
    {
        return count_decimal_digits(v);
    }
    else
    {
        if (v >= 10000)
        {
            if (v >= 1000000)
            {
                if (v >= 10000000)
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
                if (v >= 100000)
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
            if (v >= 100)
            {
                if (v >= 1000)
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
                if (v >= 10)
                {
                    return 2;
                }
                else
                {
                    if (v > 0)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
        }
    }
}

/** Converts an order-of-magnitude to a character according to the given
 * parameters
 *
 * \param doom The order-of-magnitude to be represented;
 * \param ch_0 The character to use when \c doom is 0;
 * \param ch_overflow The character to use when \c doom is outside the range
 *  (as defined by \c cch_range and \c range);
 * \param cch_range The number of characters represented by \c range;
 * \param range The range of characters to represent orders-of-magnitude 0,
 *  1, 2, ..., for example "abcd" representing 1s, 10s, 100s, 1000s
 *
 * \see stlsoft::calc_doom()
 */
inline
char
gram_doom_to_char(
    unsigned    doom
,   char        ch_0
,   char        ch_overflow
,   ss_size_t   cch_range
,   char const  range[]
)
{
    if (0 == doom)
    {
        return ch_0;
    }
    else
    {
        if (doom > cch_range)
        {
            return ch_overflow;
        }
        else
        {
            return range[doom - 1];
        }
    }
}

/** Converts an order-of-magnitude to a character using defaults
 *
 */
inline
char
gram_doom_to_char(
    unsigned    doom
)
{
    return gram_doom_to_char(
                doom
            ,   '_'
            ,   '*'
            ,   26
            ,   "abcdefghijklmnopqrstuvwxyz"
            );
}

/** Converts a histogram to a character-strip according to the given
 * parameters
 *
 * \param gram The histogram;
 * \param ch_0 The character to use when \c doom is 0;
 * \param ch_overflow The character to use when \c doom is outside the range
 *  (as defined by \c cch_range and \c range);
 * \param cch_range The number of characters represented by \c range;
 * \param range The range of characters to represent orders-of-magnitude 0,
 *  1, 2, ..., for example "abcd" representing 1s, 10s, 100s, 1000s
 *
 * \see stlsoft::doomgram
 */
template <ss_typename_param_k T_gram>
inline
stlsoft_C_string_slice_m_t
gram_to_strip(
    T_gram const&   gram
,   char            ch_0
,   char            ch_overflow
,   ss_size_t       cch_range
,   char const      range[]
,   char          (*ar)[12]
)
{
    (*ar)[0]    =   gram_doom_to_char(calc_doom(gram.num_events_in_1ns()), ch_0, ch_overflow, cch_range, range);
    (*ar)[1]    =   gram_doom_to_char(calc_doom(gram.num_events_in_10ns()), ch_0, ch_overflow, cch_range, range);
    (*ar)[2]    =   gram_doom_to_char(calc_doom(gram.num_events_in_100ns()), ch_0, ch_overflow, cch_range, range);
    (*ar)[3]    =   gram_doom_to_char(calc_doom(gram.num_events_in_1us()), ch_0, ch_overflow, cch_range, range);
    (*ar)[4]    =   gram_doom_to_char(calc_doom(gram.num_events_in_10us()), ch_0, ch_overflow, cch_range, range);
    (*ar)[5]    =   gram_doom_to_char(calc_doom(gram.num_events_in_100us()), ch_0, ch_overflow, cch_range, range);
    (*ar)[6]    =   gram_doom_to_char(calc_doom(gram.num_events_in_1ms()), ch_0, ch_overflow, cch_range, range);
    (*ar)[7]    =   gram_doom_to_char(calc_doom(gram.num_events_in_10ms()), ch_0, ch_overflow, cch_range, range);
    (*ar)[8]    =   gram_doom_to_char(calc_doom(gram.num_events_in_100ms()), ch_0, ch_overflow, cch_range, range);
    (*ar)[9]    =   gram_doom_to_char(calc_doom(gram.num_events_in_1s()), ch_0, ch_overflow, cch_range, range);
    (*ar)[10]   =   gram_doom_to_char(calc_doom(gram.num_events_in_10s()), ch_0, ch_overflow, cch_range, range);
    (*ar)[11]   =   gram_doom_to_char(calc_doom(gram.num_events_ge_100s()), ch_0, ch_overflow, cch_range, range);

    return stlsoft_C_string_slice_m_t::create(&(*ar)[0], 12);
}

/** Converts a histogram to a character-strip using defaults
 *
 */
template <ss_typename_param_k T_gram>
inline
stlsoft_C_string_slice_m_t
gram_to_strip(
    T_gram const&   gram
,   char          (*ar)[12]
)
{
    return gram_to_strip(
                gram
            ,   '_'
            ,   '*'
            ,   26
            ,   "abcdefghijklmnopqrstuvwxyz"
            ,   ar
            );
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} // namespace stlsoft
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_GRAM_UTILS */

/* ///////////////////////////// end of file //////////////////////////// */

