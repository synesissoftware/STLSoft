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
 * (and whether \c resize is a one-argument member or a two-argument member
 * with a defaulted fill value, as on pre-C++11 \c std::vector) so generic
 * code has one failure channel (\c bool).
 *
 * \see CONCEPTS.md — <em>The Resizeable Buffer concept</em>
 * \see examples/by_concept/resizeable_buffer/main.cpp
 * \see test/unit/stlsoft/util/resizeable_buffer_helpers/
 */

#ifndef STLSOFT_INCL_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS
#define STLSOFT_INCL_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS_MAJOR       1
# define STLSOFT_VER_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS_MINOR       1
# define STLSOFT_VER_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS_REVISION    1
# define STLSOFT_VER_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS_EDIT        9
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

#ifndef STLSOFT_INCL_STLSOFT_META_HPP_YESNO
# include <stlsoft/meta/yesno.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_META_HPP_YESNO */


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

# if 0
# elif defined(STLSOFT_COMPILER_IS_MSVC) && \
       _MSC_VER < 1310

 /* Have to muck around with state here to get the old girl to work.
  *
  * VC6 cannot use the SFINAE / direct-call path below. Keep
  * pointer-to-member overload sets, and add a two-argument void
  * resize (pre-C++11 vector shape) without adding a two-argument
  * bool resize (that would make auto_buffer's &resize ambiguous).
  */

template<
    ss_typename_param_k T_rb
>
struct rb_helper_traits_vc6
{
private:
    T_rb* prb;

public:
    typedef ss_typename_type_k T_rb::value_type             value_type;

    ss_explicit_k
    rb_helper_traits_vc6(
        T_rb& rb
    )
        : prb(&rb)
    {}

    bool
    do_resize(
        size_t              newSize
    ,   bool   (T_rb::*pfn)(size_t)
    )
    {
        return (prb->*pfn)(newSize);
    }

    bool
    do_resize(
        size_t              newSize
    ,   void   (T_rb::*pfn)(size_t)
    )
    {
        (prb->*pfn)(newSize);

        return true;
    }

    bool
    do_resize(
        size_t              newSize
    ,   void   (T_rb::*pfn)(size_t, value_type)
    )
    {
        (prb->*pfn)(newSize, value_type());

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
# else /* ? compiler */

 /* Prefer a direct rb.resize(newSize) call so that:
  * - one-argument resize(size) works;
  * - two-argument resize(size, value = value()) works via the default
  *   (pre-C++11 vector);
  * - C++11 vector's two overloads are not made ambiguous by forming
  *   &T::resize against competing member-pointer parameter types.
  *
  * Detect a one-argument bool / ss_bool_t-returning resize via SFINAE on
  * the member-pointer type so auto_buffer's failure channel is preserved.
  */

template<
    ss_typename_param_k T_resizeableBuffer
>
struct rb_has_bool_one_arg_resize
{
    typedef char                                            yes_type_;
    typedef char                                            (&no_type_)[2];

    template<
        ss_typename_param_k U
    ,   ss_bool_t (U::*)(ss_size_t)
    >
    struct ptm
    {};

    template<
        ss_typename_param_k U
    >
    static
    yes_type_
    test(
        ptm<U, &U::resize>*
    );

    template<
        ss_typename_param_k U
    >
    static
    no_type_
    test(
        ...
    );

    enum { value = sizeof(test<T_resizeableBuffer>(0)) == sizeof(yes_type_) };
};

template<
    ss_typename_param_k T_resizeableBuffer
>
inline
bool
rb_invoke_resize(
    T_resizeableBuffer& rb
,   ss_size_t           newSize
,   yes_type
)
{
    return rb.resize(newSize);
}

template<
    ss_typename_param_k T_resizeableBuffer
>
inline
bool
rb_invoke_resize(
    T_resizeableBuffer& rb
,   ss_size_t           newSize
,   no_type
)
{
    rb.resize(newSize);

    return true;
}
# endif /* compiler */

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
 *   for its <code>value_type</code>. Must provide a nested
 *   <code>value_type</code> and a <code>resize</code> member that can be
 *   invoked as <code>rb.resize(newSize)</code> — either a one-argument
 *   <code>resize(size_type)</code> returning \c bool / \c ss_bool_t or
 *   \c void, or a two-argument <code>resize(size_type, value_type)</code>
 *   with a defaulted fill (as on pre-C++11 \c std::vector).
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
 *   <code>T_resizeableBuffer::resize</code> returns \c bool / \c ss_bool_t
 *   and that call returned \c false. On failure the buffer is left
 *   unchanged when the model obeys the strong guarantee (as
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

    STLSOFT_WORKER_NS_USING_(ximpl_stlsoft_util_rb_helpers_, rb_has_bool_one_arg_resize);
    STLSOFT_WORKER_NS_USING_(ximpl_stlsoft_util_rb_helpers_, rb_invoke_resize);

    typedef value_to_yesno_type<
        rb_has_bool_one_arg_resize<T_resizeableBuffer>::value
    >                                                       yesno_t;

    return rb_invoke_resize(
        rb
    ,   newSize
    ,   ss_typename_type_k yesno_t::type()
    );
#endif

#ifdef STLSOFT_COMPILER_IS_MSVC
# if _MSC_VER >= 1200
#  pragma warning(pop)
# else /* ? compiler */
#  pragma warning(default : 4459)
# endif /* _MSC_VER */
#endif /* compiler */
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

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_UTIL_HPP_RESIZEABLE_BUFFER_HELPERS */

/* ///////////////////////////// end of file //////////////////////////// */
