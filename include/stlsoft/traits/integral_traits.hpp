/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/traits/integral_traits.hpp
 *
 * Purpose: integral_traits classes.
 *
 * Created: 21st November 2024
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


/** \file stlsoft/traits/integral_traits.hpp
 *
 * \brief [C++] Definition of the stlsoft::integral_traits class
 *   template
 *   (\ref group__library__Utility "Utility" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_UTIL_HPP_INTEGRAL_TRAITS
#define STLSOFT_INCL_STLSOFT_UTIL_HPP_INTEGRAL_TRAITS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_UTIL_HPP_INTEGRAL_TRAITS_MAJOR     1
# define STLSOFT_VER_STLSOFT_UTIL_HPP_INTEGRAL_TRAITS_MINOR     0
# define STLSOFT_VER_STLSOFT_UTIL_HPP_INTEGRAL_TRAITS_REVISION  2
# define STLSOFT_VER_STLSOFT_UTIL_HPP_INTEGRAL_TRAITS_EDIT      3
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


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * classes
 */

// struct integral_traits

#ifdef STLSOFT_DOCUMENTATION_SKIP_SECTION

/** Traits class for expressing common attributes and operations for
 * integral types
 *
 * \ingroup group__library__Traits
 *
 * \param T The integral type
 * \param U The underlying type. Must be
 */
template<
    ss_typename_param_k T
,   ss_typename_param_k U = T
>
struct integral_traits
{
public: // types
    typedef T                                               integer_type;

    typedef U                                               underlying_type;

    static_assert(stlsoft::is_integral_type<integer_type>::value);

    static
    underlying_type
    get_underlying_value(
        integer_type const&
    ) STLSOFT_NOEXCEPT;

    static
    integer_type
    from_underlying_type(
        underlying_type const&
    );
};
#else /* ? STLSOFT_DOCUMENTATION_SKIP_SECTION */

template<
    ss_typename_param_k T
>
struct integral_traits;

# define STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(T)             \
    STLSOFT_TEMPLATE_SPECIALISATION                                         \
    struct integral_traits<T>                                               \
    {                                                                       \
        typedef T                               integer_type;               \
        typedef T                               underlying_type;            \
        static                                                              \
        underlying_type const&                                              \
        get_underlying_value(                                               \
            integer_type const& v                                           \
        ) STLSOFT_NOEXCEPT                                                  \
        {                                                                   \
            return v;                                                       \
        }                                                                   \
        static                                                              \
        integer_type                                                        \
        from_underlying_type(                                               \
            underlying_type const& v                                        \
        ) STLSOFT_NOEXCEPT                                                  \
        {                                                                   \
            return v;                                                       \
        }                                                                   \
    }

STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(ss_sint8_t);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(ss_uint8_t);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(ss_sint16_t);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(ss_uint16_t);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(ss_sint32_t);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(ss_uint32_t);
#ifdef STLSOFT_CF_64BIT_INT_SUPPORT
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(ss_sint64_t);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(ss_uint64_t);
#endif /* STLSOFT_CF_64BIT_INT_SUPPORT */
#ifdef STLSOFT_CF_CHAR_DISTINCT_INT_TYPE
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(signed char);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(unsigned char);
#endif /* STLSOFT_CF_CHAR_DISTINCT_INT_TYPE */
#ifdef STLSOFT_CF_SHORT_DISTINCT_INT_TYPE
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(signed short);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(unsigned short);
#endif /* STLSOFT_CF_SHORT_DISTINCT_INT_TYPE */
#ifdef STLSOFT_CF_INT_DISTINCT_INT_TYPE
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(signed int);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(unsigned int);
#endif /* STLSOFT_CF_INT_DISTINCT_INT_TYPE */
#ifdef STLSOFT_CF_LONG_DISTINCT_INT_TYPE
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(signed long);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(unsigned long);
#endif /* STLSOFT_CF_LONG_DISTINCT_INT_TYPE */
#ifdef STLSOFT_CF_LONG_LONG_DISTINCT_INT_TYPE
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(signed long long);
STLSOFT_IMPLEMENT_integral_traits_FOR_INTEGRAL_TYPE(unsigned long long);
#endif /* STLSOFT_CF_LONG_LONG_DISTINCT_INT_TYPE */
#endif /* STLSOFT_DOCUMENTATION_SKIP_SECTION */


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

#endif /* !STLSOFT_INCL_STLSOFT_UTIL_HPP_INTEGRAL_TRAITS */

/* ///////////////////////////// end of file //////////////////////////// */

