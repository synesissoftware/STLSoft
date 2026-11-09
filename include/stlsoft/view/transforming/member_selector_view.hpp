/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/view/transforming/member_selector_view.hpp
 *
 * Purpose: Contains the member_selector_view class template.
 *
 * Created: 9th May 2025
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2025, Matthew Wilson and Synesis Information Systems
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


/** \file stlsoft/view/transforming/member_selector_view.hpp
 *
 * \brief [C++] Definition of the stlsoft::member_selector_view
 *   class template
 *   (\ref group__library__View "View" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_VIEW_TRANSFORMING_HPP_MEMBER_SELECTOR_VIEW
#define STLSOFT_INCL_STLSOFT_VIEW_TRANSFORMING_HPP_MEMBER_SELECTOR_VIEW

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_VIEW_TRANSFORMING_HPP_MEMBER_SELECTOR_VIEW_MAJOR       0
# define STLSOFT_VER_STLSOFT_VIEW_TRANSFORMING_HPP_MEMBER_SELECTOR_VIEW_MINOR       0
# define STLSOFT_VER_STLSOFT_VIEW_TRANSFORMING_HPP_MEMBER_SELECTOR_VIEW_REVISION    1
# define STLSOFT_VER_STLSOFT_VIEW_TRANSFORMING_HPP_MEMBER_SELECTOR_VIEW_EDIT        2
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

#ifndef STLSOFT_INCL_STLSOFT_ITERATORS_HPP_MEMBER_SELECTOR_ITERATOR
# include <stlsoft/iterators/member_selector_iterator.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_ITERATORS_HPP_MEMBER_SELECTOR_ITERATOR */


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

/** View adapter, that provides a sequence view of the given member of the
 * sequence of the adapted type.
 */
template<
    class               C
,   ss_typename_param_k M
,   ss_typename_param_k I // = ss_typename_type_k C::iterator
>
class member_selector_view
{
public: // types
    typedef C                                               wrapped_class_type;
    typedef M                                               member_type;
    typedef I                                               providing_iterator_type;
    typedef member_selector_view<
        wrapped_class_type
    ,   member_type
    ,   providing_iterator_type
    >                                                       class_type;
    typedef member_selector_iterator<
        I
    ,   C
    ,   M
    >                                                       iterator_type;
    typedef member_selector_iterator<
        I
    ,   C
    ,   M
    >                                                       const_iterator_type;

public: // construction
    member_selector_view(
        providing_iterator_type from
    ,   providing_iterator_type to
    ,   M                   C::*member
    )
        : m_from(from)
        , m_to(to)
        , m_member(member)
    {}

public: // iteration
    iterator_type       begin()
    {
        return iterator_type(m_from, m_member);
    }
    iterator_type       end()
    {
        return iterator_type(m_to, m_member);
    }
    const_iterator_type begin() const
    {
        return const_iterator_type(m_from, m_member);
    }
    const_iterator_type end() const
    {
        return const_iterator_type(m_to, m_member);
    }

private: // fields
    providing_iterator_type m_from;
    providing_iterator_type m_to;
    M                   C::*m_member;
};

template<
    ss_typename_param_k I
,   class               C
,   ss_typename_param_k M
>
inline
member_selector_view<C, M, I>
make_member_selector_view(
    I       from
,   I       to
,   M   C::*member
)
{
    return member_selector_view<C, M, I>(from, to, member);
}

template<
    class               C
,   ss_typename_param_k M
,   ss_size_t           V_dimension
>
inline
member_selector_view<C, M, C*>
make_member_selector_view(
    C     (&ar)[V_dimension]
,   M   C::*member
)
{
    // return make_member_selector_view<C, M, C const*>(&ar[0], &ar[0] + V_dimension, member);
    return make_member_selector_view(&ar[0], &ar[0] + V_dimension, member);
}

#if 0

template<
class               C
,   ss_typename_param_k M
,   ss_size_t           V_dimension
>
inline
member_selector_view<C, M, C*>
make_member_selector_view(
    C     (&ar)[V_dimension]
    ,   M   C::*member
)
{
    return make_member_selector_view(&ar[0], &ar[0] + V_dimension, member);
}
#endif


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

#endif /* !STLSOFT_INCL_STLSOFT_VIEW_TRANSFORMING_HPP_MEMBER_SELECTOR_VIEW */

/* ///////////////////////////// end of file //////////////////////////// */

