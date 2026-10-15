/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/util/resizeable_buffer_helpers.hpp
 *
 * Purpose: Utility functions for working with resizeable-buffers.
 *
 * Created: 24th December 2020
 * Updated: 16th October 2026
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


/** \file stlsoft/util/resizeable_buffer_helpers.hpp
 *
 * \brief [C++] Helpers for types that model the <em>Resizeable Buffer</em>
 *   concept
 *   (\ref group__library__Utility "Utility" Library).
 *
 * A <em>Resizeable Buffer</em> is a contiguous, growable character sequence
 * used by UnixSTL / WinSTL <code>system_traits</code> and
 * <code>filesystem_traits</code> overloads that take a generic
 * <code>rb</code> rather than a raw pointer and length. Preferred models
 * include \c stlsoft::auto_buffer and \c std::vector; see
 * <strong>CONCEPTS.md</strong> in the project root for the full
 * requirements table, non-models, and the probe-then-fill gold contract
 * for traits overloads.
 *
 * This header provides \c stlsoft::resizeable_buffer_resize, which adapts
 * <code>T::resize</code> whether that member returns \c bool or \c void
 * so generic code has one failure channel (\c bool).
 *
 * \see CONCEPTS.md — <em>The Resizeable Buffer concept</em>
 * \see examples/by_concept/resizeable_buffer/main.cpp
 * \see test/unit/stlsoft/util/resizeable_buffer_helpers/
 */

#ifndef STLSOFT_INCL_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS
#define STLSOFT_INCL_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS_MAJOR       1
# define STLSOFT_VER_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS_MINOR       0
# define STLSOFT_VER_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS_REVISION    5
# define STLSOFT_VER_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS_EDIT        8
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

#ifndef STLSOFT_INCL_STLSOFT_META_HPP_SIZE_OF
# include <stlsoft/meta/size_of.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_META_HPP_SIZE_OF */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
STLSOFT_OPEN_WORKER_NS_(ximpl_stlsoft_util_rb_helpers_)

#if 0
#elif defined(STLSOFT_COMPILER_IS_MSVC) && \
      _MSC_VER < 1310

 /* Have to muck around with state here to get the old girl to work */

template<
    ss_typename_param_k T_rb
>
struct rb_helper_traits_vc6
{
private:
    T_rb* prb;

public:
    ss_explicit_k
    rb_helper_traits_vc6(
        T_rb& rb
    )
        : prb(&rb)
    {}

    bool
    do_resize(
        size_t              newSize
    ,   bool (T_rb::*pfn)(size_t)
    )
    {
        return (prb->*pfn)(newSize);
    }

    bool
    do_resize(
        size_t              newSize
    ,   void (T_rb::*pfn)(size_t)
    )
    {
        (prb->*pfn)(newSize);

        return true;
    }
};

template<
    ss_typename_param_k T
>
inline
rb_helper_traits_vc6<T>
traits_for(
    T& rb
)
{
    return rb_helper_traits_vc6<T>(rb);
}
#else

template<
    ss_typename_param_k T_resizeableBuffer
,   ss_typename_param_k T_character
>
struct rb_helper_traits
{
    typedef T_character                                     char_type;
    typedef T_resizeableBuffer                              buffer_type;

    typedef bool                             (buffer_type::*pfn_b)(size_t);
    typedef void                             (buffer_type::*pfn_v)(size_t);

    static
    bool
    do_resize(
        buffer_type&    buffer
    ,   size_t          newSize
    ,   pfn_b           pfn
    )
    {
        return (buffer.*pfn)(newSize);
    }

    static
    bool
    do_resize(
        buffer_type&    buffer
    ,   size_t          newSize
    ,   pfn_v           pfn
    )
    {
        (buffer.*pfn)(newSize);

        return true;
    }
};
#endif
STLSOFT_CLOSE_WORKER_NS_(ximpl_stlsoft_util_rb_helpers_)
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

/** Invokes <code>resize()</code> on a Resizeable Buffer, unifying
 *  <code>bool</code>- and <code>void</code>-returning members.
 *
 * Prefer this helper over calling <code>rb.resize(newSize)</code>
 * directly in generic code (traits templates, concept examples) so that
 * failure is always reported as <code>false</code> without caring which
 * overload of <code>resize</code> the model provides.
 *
 * \tparam T_resizeableBuffer A type that models <em>Resizeable Buffer</em>
 *   for its <code>value_type</code>. Must declare an unambiguous
 *   <code>resize(size_type)</code> (or <code>resize(size_t)</code>)
 *   member returning either \c bool or \c void, and a nested
 *   <code>value_type</code>.
 *
 * \param rb Reference to the buffer instance to resize
 * \param newSize The requested number of elements after the call
 *   (for path/string use this is typically the probed demand
 *   <em>including</em> the trailing NUL)
 *
 * \retval true The resize succeeded. For \c void-returning
 *   <code>resize</code>, success means the call returned without
 *   throwing (models such as \c std::vector typically throw
 *   <code>std::bad_alloc</code> on exhaustion). For \c bool-returning
 *   <code>resize</code> (e.g. \c stlsoft::auto_buffer), the member's
 *   return value is propagated.
 * \retval false The resize failed. Only reachable when
 *   <code>T_resizeableBuffer::resize</code> returns \c bool and that
 *   call returned \c false. On failure the buffer is left unchanged
 *   when the model obeys the strong guarantee (as
 *   \c stlsoft::auto_buffer does).
 *
 * \note This function does <em>not</em> set <code>errno</code> /
 *   <code>GetLastError</code>. Callers that implement the traits
 *   <code>rb</code> gold contract should, on \c false, set
 *   <code>ENOMEM</code> or <code>ERROR_OUTOFMEMORY</code> (as
 *   appropriate) and return without taking <code>&rb[0]</code> on an
 *   empty buffer.
 *
 * \note Element preservation, contiguity, and trailing-NUL invariants
 *   are properties of the buffer model, not of this helper; see
 *   <strong>CONCEPTS.md</strong>.
 *
 * \see stlsoft::auto_buffer::resize
 * \see CONCEPTS.md — <em>Helper: resizeable_buffer_resize</em> and
 *   <em>Contract for traits overloads that take an rb</em>
 */
template<
    ss_typename_param_k T_resizeableBuffer
>
bool
resizeable_buffer_resize(
    T_resizeableBuffer& rb
,   ss_size_t           newSize
)
{
#ifdef STLSOFT_COMPILER_IS_MSVC
# if _MSC_VER >= 1200
#  pragma warning(push)
# endif /* compiler */
# pragma warning(disable : 4459)
#endif /* compiler */

#if 0
#elif defined(STLSOFT_COMPILER_IS_MSVC) && \
      _MSC_VER < 1310

    STLSOFT_WORKER_NS_USING_(ximpl_stlsoft_util_rb_helpers_, traits_for);

    return traits_for(rb).do_resize(newSize, &T_resizeableBuffer::resize);
#else
    typedef T_resizeableBuffer                              buffer_t;
    typedef ss_typename_type_k buffer_t::value_type         value_t;

    STLSOFT_WORKER_NS_USING_(ximpl_stlsoft_util_rb_helpers_, rb_helper_traits);

    typedef rb_helper_traits<
        buffer_t
    ,   value_t
    >                                                       traits_t;

    return traits_t::do_resize(rb, newSize, &T_resizeableBuffer::resize);
#endif

#ifdef STLSOFT_COMPILER_IS_MSVC
# if _MSC_VER >= 1200
#  pragma warning(pop)
# else /* ? compiler */
#  pragma warning(default : 4459)
# endif /* _MSC_VER */
#endif /* compiler */
}

/* ////////////////////////////////////////////////////////////////////// */

#ifndef STLSOFT_NO_NAMESPACE
} // namespace stlsoft
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS */

/* ///////////////////////////// end of file //////////////////////////// */

