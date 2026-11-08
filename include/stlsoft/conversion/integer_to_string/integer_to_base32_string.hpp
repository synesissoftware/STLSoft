/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/conversion/integer_to_string/integer_to_base32_string.hpp
 *
 * Purpose: Very efficient integer to string conversion functions for base-32
 *          representation.
 *
 * Created: 17th February 2024
 * Updated: 15th October 2026
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


/** \file stlsoft/conversion/integer_to_string/integer_to_base32_string.hpp
 *
 * \brief [C++] Very efficient integer to string conversion functions
 *   for base-32 representation
 *  (\ref group__library__Conversion "Conversion" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_CONVERSION_INTEGER_TO_STRING_HPP_INTEGER_TO_BASE32_STRING
#define STLSOFT_INCL_STLSOFT_CONVERSION_INTEGER_TO_STRING_HPP_INTEGER_TO_BASE32_STRING

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_CONVERSION_INTEGER_TO_STRING_HPP_INTEGER_TO_BASE32_STRING_MAJOR    1
# define STLSOFT_VER_STLSOFT_CONVERSION_INTEGER_TO_STRING_HPP_INTEGER_TO_BASE32_STRING_MINOR    0
# define STLSOFT_VER_STLSOFT_CONVERSION_INTEGER_TO_STRING_HPP_INTEGER_TO_BASE32_STRING_REVISION 2
# define STLSOFT_VER_STLSOFT_CONVERSION_INTEGER_TO_STRING_HPP_INTEGER_TO_BASE32_STRING_EDIT     4
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

#ifndef STLSOFT_INCL_STLSOFT_META_HPP_IS_INTEGRAL_TYPE
# include <stlsoft/meta/is_integral_type.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_META_HPP_IS_INTEGRAL_TYPE */
#ifndef STLSOFT_INCL_STLSOFT_META_HPP_IS_SIGNED_TYPE
# include <stlsoft/meta/is_signed_type.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_META_HPP_IS_SIGNED_TYPE */
#ifndef STLSOFT_INCL_STLSOFT_META_HPP_N_TYPES
# include <stlsoft/meta/n_types.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_META_HPP_N_TYPES */
#ifndef STLSOFT_INCL_STLSOFT_META_HPP_YESNO
# include <stlsoft/meta/yesno.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_META_HPP_YESNO */
#ifndef STLSOFT_INCL_STLSOFT_LIMITS_HPP_INTEGRAL_FORMAT_WIDTH_LIMITS
# include <stlsoft/limits/integral_format_width_limits.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_LIMITS_HPP_INTEGRAL_FORMAT_WIDTH_LIMITS */
#ifndef STLSOFT_INCL_STLSOFT_LIMITS_HPP_INTEGRAL_LIMITS
# include <stlsoft/limits/integral_limits.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_LIMITS_HPP_INTEGRAL_LIMITS */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_HPP_SIGN_TRAITS
# include <stlsoft/util/sign_traits.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_HPP_SIGN_TRAITS */

#ifndef STLSOFT_INCL_STLSOFT_QUALITY_H_COVER
# include <stlsoft/quality/cover.h>
#endif /* !STLSOFT_INCL_STLSOFT_QUALITY_H_COVER */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_memfns
# include <stlsoft/api/external/memfns.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_memfns */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * worker functions
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

STLSOFT_OPEN_WORKER_NS_(ximpl_I2S)

/* get subscriptable pointer to array of base-32 characters */
template <ss_typename_param_k T_character>
inline
T_character const*
#ifdef STLSOFT_CF_TEMPLATE_TYPE_REQUIRED_IN_ARGS
# define STLSOFT_I2S_32b2S_GET_DIGIT_CHARACTER(T_character) get_base32_digit_character(static_cast<T_character*>(0))
get_base32_digit_character(T_character*)
#else /* ? STLSOFT_CF_TEMPLATE_TYPE_REQUIRED_IN_ARGS */
# define STLSOFT_I2S_32b2S_GET_DIGIT_CHARACTER(T_character) get_base32_digit_character<T_character>()
get_base32_digit_character()
#endif /* STLSOFT_CF_TEMPLATE_TYPE_REQUIRED_IN_ARGS */
{
    static T_character const s_characters[63] =
    {
            'v'     // -31
        ,   'u'     // -30
        ,   't'     // -29
        ,   's'     // -28
        ,   'r'     // -27
        ,   'q'     // -26
        ,   'p'     // -25
        ,   'o'     // -24
        ,   'n'     // -23
        ,   'm'     // -22
        ,   'l'     // -21
        ,   'k'     // -20
        ,   'j'     // -19
        ,   'i'     // -18
        ,   'h'     // -17
        ,   'g'     // -16
        ,   'f'     // -15
        ,   'e'     // -14
        ,   'd'     // -13
        ,   'c'     // -12
        ,   'b'     // -11
        ,   'a'     // -10
        ,   '9'     //  -9
        ,   '8'     //  -8
        ,   '7'     //  -7
        ,   '6'     //  -6
        ,   '5'     //  -5
        ,   '4'     //  -4
        ,   '3'     //  -3
        ,   '2'     //  -2
        ,   '1'     //  -1
        ,   '0'     //   0
        ,   '1'     //  +1
        ,   '2'     //  +2
        ,   '3'     //  +3
        ,   '4'     //  +4
        ,   '5'     //  +5
        ,   '6'     //  +6
        ,   '7'     //  +7
        ,   '8'     //  +8
        ,   '9'     //  +9
        ,   'a'     // +10
        ,   'b'     // +11
        ,   'c'     // +12
        ,   'd'     // +13
        ,   'e'     // +14
        ,   'f'     // +15
        ,   'g'     // +16
        ,   'h'     // +17
        ,   'i'     // +18
        ,   'j'     // +19
        ,   'k'     // +20
        ,   'l'     // +21
        ,   'm'     // +22
        ,   'n'     // +23
        ,   'o'     // +24
        ,   'p'     // +25
        ,   'q'     // +26
        ,   'r'     // +27
        ,   's'     // +28
        ,   't'     // +29
        ,   'u'     // +30
        ,   'v'     // +31
    };
#if 0
    static T_character const* s_mid = s_characters + 31;

    return s_mid;
#else /* ? 0 */
    return s_characters + 31;
#endif /* 0 */
}

/* selector traits class for remainder type */
template <ss_typename_param_k T_Integer>
struct i2s_base32_remainder_traits_t
{
#if 0
    typedef T_Integer                                       remainder_type;
#else
    typedef unsigned int                                    remainder_type;
#endif
};

/* main conversion function (unsigned) */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
>
inline
T_character const*
unsigned_integer_to_base32_string_3_(
    T_character*            buf
,   ss_size_t               cchBuf
,   T_integer /* const& */  i
)
{
    STLSOFT_STATIC_ASSERT(0 != stlsoft::is_integral_type<T_integer>::value);
    STLSOFT_STATIC_ASSERT(0 == stlsoft::is_signed_type<T_integer>::value);

    typedef i2s_base32_remainder_traits_t<T_integer>    remainder_traits_t;

    T_character* end = buf + (cchBuf - 1);

    // Whichever we do it, we write the NUL character (and move down one)
    *end-- = '\0';

    STLSOFT_COVER_MARK_LINE();

    if (0 == i)
    {
        STLSOFT_COVER_MARK_LINE();

        *end = '0';

        return end;
    }
    else
    {
        STLSOFT_COVER_MARK_LINE();

        T_character const* const hchars = STLSOFT_I2S_32b2S_GET_DIGIT_CHARACTER(T_character);

        T_character* p = end;

        for (;;)
        {
            STLSOFT_COVER_MARK_LINE();

            ss_typename_type_k remainder_traits_t::remainder_type const rem = i & 0x1f;

            *p = hchars[rem];

            i >>= 5;

            if (0 == i)
            {
                STLSOFT_COVER_MARK_LINE();

                break;
            }
            else
            {
                STLSOFT_COVER_MARK_LINE();

                --p;
            }
        }

        STLSOFT_COVER_MARK_LINE();

        return p;
    }
}

/* secondary conversion function (unsigned) that calculates numWritten */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
>
inline
T_character const*
unsigned_integer_to_base32_string_4_(
    T_character*        buf
,   ss_size_t           cchBuf
,   T_integer const&    i
,   ss_size_t*          numWritten
)
{
    STLSOFT_COVER_MARK_LINE();

    STLSOFT_ASSERT(ss_nullptr_k != numWritten);

    T_character const* const r = unsigned_integer_to_base32_string_3_<T_integer, T_character>(buf, cchBuf, i);

    STLSOFT_COVER_MARK_LINE();

    *numWritten = cchBuf - ((r - buf) + 1);

    STLSOFT_COVER_MARK_LINE();

    return r;
}

/* (invalid) generic form of signed-minimum-handler */
template<
    ss_typename_param_k T_character
>
void
i2s_handle_signed_minimum_in_base32_2_(
    T_character*    buf
,   ss_size_t       cchBuf
,   ...
);

/* 8-bit form of signed-minimum-handler */
template<
    ss_typename_param_k T_character
>
inline
T_character const*
i2s_handle_signed_minimum_in_base32_2_(
    T_character*        buf
,   ss_size_t           cchBuf
,   size_type<1> const&
)
{
    STLSOFT_COVER_MARK_LINE();

    static T_character const  s_minimum[] = { '-', '4', '0', '\0' };

    STLSOFT_ASSERT(cchBuf >= STLSOFT_NUM_ELEMENTS(s_minimum));

    T_character* const  end =   buf + cchBuf;
    T_character* const  r   =   end - STLSOFT_NUM_ELEMENTS(s_minimum);

    STLSOFT_API_EXTERNAL_memfns_memcpy(r, s_minimum, sizeof(T_character) * STLSOFT_NUM_ELEMENTS(s_minimum));

    STLSOFT_COVER_MARK_LINE();

    return r;
}

/* 16-bit form of signed-minimum-handler */
template<
    ss_typename_param_k T_character
>
inline
T_character const*
i2s_handle_signed_minimum_in_base32_2_(
    T_character*        buf
,   ss_size_t           cchBuf
,   size_type<2> const&
)
{
    STLSOFT_COVER_MARK_LINE();

    static T_character const  s_minimum[] = { '-', '1', '0', '0', '0', '\0' };

    STLSOFT_ASSERT(cchBuf >= STLSOFT_NUM_ELEMENTS(s_minimum));

    T_character* const  end =   buf + cchBuf;
    T_character* const  r   =   end - STLSOFT_NUM_ELEMENTS(s_minimum);

    STLSOFT_API_EXTERNAL_memfns_memcpy(r, s_minimum, sizeof(T_character) * STLSOFT_NUM_ELEMENTS(s_minimum));

    STLSOFT_COVER_MARK_LINE();

    return r;
}

/* 32-bit form of signed-minimum-handler */
template<
    ss_typename_param_k T_character
>
inline
T_character const*
i2s_handle_signed_minimum_in_base32_2_(
    T_character*        buf
,   ss_size_t           cchBuf
,   size_type<4> const&
)
{
    STLSOFT_COVER_MARK_LINE();

    static T_character const  s_minimum[] = { '-', '2', '0', '0', '0', '0', '0', '0', '\0' };

    STLSOFT_ASSERT(cchBuf >= STLSOFT_NUM_ELEMENTS(s_minimum));

    T_character* const  end =   buf + cchBuf;
    T_character* const  r   =   end - STLSOFT_NUM_ELEMENTS(s_minimum);

    STLSOFT_API_EXTERNAL_memfns_memcpy(r, s_minimum, sizeof(T_character) * STLSOFT_NUM_ELEMENTS(s_minimum));

    STLSOFT_COVER_MARK_LINE();

    return r;
}

/* 64-bit form of signed-minimum-handler */
template<
    ss_typename_param_k T_character
>
inline
T_character const*
i2s_handle_signed_minimum_in_base32_2_(
    T_character*        buf
,   ss_size_t           cchBuf
,   size_type<8> const&
)
{
    STLSOFT_COVER_MARK_LINE();

    static T_character const  s_minimum[] = { '-', '8', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0' };

    STLSOFT_ASSERT(cchBuf >= STLSOFT_NUM_ELEMENTS(s_minimum));

    T_character* const  end =   buf + cchBuf;
    T_character* const  r   =   end - STLSOFT_NUM_ELEMENTS(s_minimum);

    STLSOFT_API_EXTERNAL_memfns_memcpy(r, s_minimum, sizeof(T_character) * STLSOFT_NUM_ELEMENTS(s_minimum));

    STLSOFT_COVER_MARK_LINE();

    return r;
}

/* generic signed-type catch-all handler : casts to sized, signed type */
template<
    ss_typename_param_k T_character
,   ss_typename_param_k T_integer
>
inline
T_character const*
i2s_handle_signed_minimum_in_base32_(
    T_character*    buf
,   ss_size_t       cchBuf
,   T_integer    /* i */
)
{
    STLSOFT_STATIC_ASSERT(0 != stlsoft::is_signed_type<T_integer>::value);

    STLSOFT_COVER_MARK_LINE();

    enum { sizeofI = sizeof(T_integer) };

    typedef size_type<sizeofI>      sized_t;

    // Need to use ???_base32_2_ otherwise get ambiguities
    return i2s_handle_signed_minimum_in_base32_2_(buf, cchBuf, sized_t());
}

/* secondary conversion function (signed), implemented in terms of unsigned version */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
>
inline
T_character const*
signed_integer_to_base32_string_3_(
    T_character*            buf
,   ss_size_t               cchBuf
,   T_integer /* const& */  i
)
{
    STLSOFT_COVER_MARK_LINE();

    STLSOFT_STATIC_ASSERT(0 != stlsoft::is_integral_type<T_integer>::value);
    STLSOFT_STATIC_ASSERT(0 != stlsoft::is_signed_type<T_integer>::value);

    typedef integral_limits<T_integer>                                  limit_traits_t;

    typedef ss_typename_type_k sign_traits<T_integer>::unsigned_type    unsigned_t;

    if (i < 0)
    {
        STLSOFT_COVER_MARK_LINE();

        if (i == limit_traits_t::minimum())
        {
            STLSOFT_COVER_MARK_LINE();

            return i2s_handle_signed_minimum_in_base32_(buf, cchBuf, i);
        }
        else
        {
            STLSOFT_COVER_MARK_LINE();

            T_character const* r2 = unsigned_integer_to_base32_string_3_(buf, cchBuf, unsigned_t(-i));

            *const_cast<T_character*>(--r2) = T_character('-');

            STLSOFT_COVER_MARK_LINE();

            return r2;
        }
    }
    else
    {
        STLSOFT_COVER_MARK_LINE();

        return unsigned_integer_to_base32_string_3_(buf, cchBuf, unsigned_t(i));
    }
}

/* secondary conversion function (signed) that calculates numWritten */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
>
inline
T_character const*
signed_integer_to_base32_string_4_(
    T_character*        buf
,   ss_size_t           cchBuf
,   T_integer const&    i
,   ss_size_t*          numWritten
)
{
    STLSOFT_COVER_MARK_LINE();

    STLSOFT_ASSERT(ss_nullptr_k != numWritten);

    T_character const* const r = signed_integer_to_base32_string_3_<T_integer, T_character>(buf, cchBuf, i);

    *numWritten = cchBuf - ((r - buf) + 1);

    STLSOFT_COVER_MARK_LINE();

    return r;
}

/* TMP compile-time selector of unsigned/signed work function */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
>
inline
T_character const*
integer_to_base32_string_if_signed_(
    yes_type
,   T_character*        buf
,   ss_size_t           cchBuf
,   T_integer const&    i
,   ss_size_t*          numWritten
)
{
    STLSOFT_COVER_MARK_LINE();

    return signed_integer_to_base32_string_4_(buf, cchBuf, i, numWritten);
}

/* TMP compile-time selector of unsigned/signed work function */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
>
inline
T_character const*
integer_to_base32_string_if_signed_(
    no_type
,   T_character*        buf
,   ss_size_t           cchBuf
,   T_integer const&    i
,   ss_size_t*          numWritten
)
{
    STLSOFT_COVER_MARK_LINE();

    return unsigned_integer_to_base32_string_4_(buf, cchBuf, i, numWritten);
}

/* TMP compile-time selector of unsigned/signed work function */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
>
inline
T_character const*
integer_to_base32_string_if_signed_(
    yes_type
,   T_character*        buf
,   ss_size_t           cchBuf
,   T_integer const&    i
)
{
    STLSOFT_COVER_MARK_LINE();

    return signed_integer_to_base32_string_3_(buf, cchBuf, i);
}

/* TMP compile-time selector of unsigned/signed work function */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
>
inline
T_character const*
integer_to_base32_string_if_signed_(
    no_type
,   T_character*        buf
,   ss_size_t           cchBuf
,   T_integer const&    i
)
{
    STLSOFT_COVER_MARK_LINE();

    return unsigned_integer_to_base32_string_3_(buf, cchBuf, i);
}

STLSOFT_CLOSE_WORKER_NS_(ximpl_I2S)

#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Converts an integer value into a base-32 string representation in the
 * given character buffer, assigning the number of characters (excluding
 * the NUL character) written into the given size variable.
 *
 * \tparam T_integer Type of the integer to be converted
 * \tparam T_character Type of the character array into which the conversion
 *   will be written
 *
 * \param buf Pointer to the buffer
 * \param cchBuf Number of character available in \c buf
 * \param i The value to be converted to octal string
 * \param numWritten Pointer to a variable to receive the number of
 *   characters written (excluding NUL character);
 *
 * \pre nullptr != buf
 * \pre cchBuf > integral_format_width_limits<T_integer>::maxDuotrigesimalWidth
 * \pre nullptr != numWritten
 */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
>
inline
T_character const*
integer_to_base32_string(
    T_character*        buf
,   ss_size_t           cchBuf
,   T_integer const&    i
,   ss_size_t*          numWritten
)
{
    STLSOFT_MESSAGE_STATIC_ASSERT(0 != stlsoft::is_integral_type<T_integer>::value, "value must be an integral type");

    typedef ss_typename_type_k is_signed_type<T_integer>::type signed_yesno_t;

    STLSOFT_COVER_MARK_LINE();

    return STLSOFT_WORKER_NS_QUAL_(ximpl_I2S, integer_to_base32_string_if_signed_)(signed_yesno_t(), buf, cchBuf, i, numWritten);
}

/** Converts an integer value into a base-32 string representation in the
 * given character buffer.
 *
 * \tparam T_integer Type of the integer to be converted
 * \tparam T_character Type of the character array into which the conversion
 *   will be written
 *
 * \param buf Pointer to the buffer
 * \param cchBuf Number of character available in \c buf
 * \param i The value to be converted to octal string
 *
 * \pre nullptr != buf
 * \pre cchBuf > integral_format_width_limits<T_integer>::maxDuotrigesimalWidth
 */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
>
inline
T_character const*
integer_to_base32_string(
    T_character*        buf
,   ss_size_t           cchBuf
,   T_integer const&    i
)
{
    STLSOFT_MESSAGE_STATIC_ASSERT(0 != stlsoft::is_integral_type<T_integer>::value, "value must be an integral type");

    typedef ss_typename_type_k is_signed_type<T_integer>::type signed_yesno_t;

    STLSOFT_COVER_MARK_LINE();

    return STLSOFT_WORKER_NS_QUAL_(ximpl_I2S, integer_to_base32_string_if_signed_)(signed_yesno_t(), buf, cchBuf, i);
}

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

/** Converts an integer value into a base-32 string representation in the
 * given character buffer.
 *
 * \tparam T_integer Type of the integer to be converted
 * \tparam T_character Type of the character array into which the conversion
 *   will be written
 * \tparam V_dimension Dimension of the character array \c ar
 *
 * \param ar Reference to a character buffer of size \c V_dimension
 * \param i The value to be converted to octal string
 */
template<
    ss_typename_param_k T_integer
,   ss_typename_param_k T_character
,   ss_size_t           V_dimension
>
inline
T_character const*
integer_to_base32_string(
    T_character       (&ar)[V_dimension]
,   T_integer const&    i
)
{
    STLSOFT_MESSAGE_STATIC_ASSERT(0 != stlsoft::is_integral_type<T_integer>::value, "value must be an integral type");

    typedef integral_format_width_limits<T_integer> width_traits_t;

    STLSOFT_MESSAGE_STATIC_ASSERT(V_dimension >= 1 + width_traits_t::maxDuotrigesimalWidth, "array is of insufficient size for the longest expressable value of the integral type");
    STLSOFT_SUPPRESS_UNUSED(width_traits_t::maxDuotrigesimalWidth);

    STLSOFT_COVER_MARK_LINE();

    return integer_to_base32_string(&ar[0], V_dimension, i);
}
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} // namespace stlsoft
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_CONVERSION_INTEGER_TO_STRING_HPP_INTEGER_TO_BASE32_STRING */

/* ///////////////////////////// end of file //////////////////////////// */

