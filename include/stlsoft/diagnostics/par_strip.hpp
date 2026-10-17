/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/diagnostics/par_strip.hpp
 *
 * Purpose: Definition of the par_strip class template.
 *
 * Created: 24th September 2026
 * Updated: 24th September 2026
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


/** \file stlsoft/diagnostics/par_strip.hpp
 *
 * \brief [C++] Definition of the par_strip class template
 *   (\ref group__library__Diagnostic "Diagnostic" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_PAR_STRIP
#define STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_PAR_STRIP

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_PAR_STRIP_MAJOR    1
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_PAR_STRIP_MINOR    0
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_PAR_STRIP_REVISION 1
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_PAR_STRIP_EDIT     1
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if __cplusplus < 201103L
# error stlsoft/diagnostics/par_strip.hpp requires C++11 or later
#endif /* C++11- */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# include <stlsoft/stlsoft.h>
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#include <cassert>
#include <string>


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

/** Which side of a par-strip is the favourable direction.
 *
 * \ingroup group__library__Diagnostic
 *
 * Forward places a sample greater than the reference on the right.
 * Backward places that same sample on the left. Timing uses backward.
 */
enum class par_strip_direction
{
        backward    =   0
    ,   forward     =   1
};


/** One-shot order-of-magnitude comparison of a sample against a reference.
 *
 * \ingroup group__library__Diagnostic
 *
 * \tparam V_base Integer radix. Must be at least 2. Part of the type, not
 *   a field;
 * \tparam T_value Non-negative value type. The primary specialisation is
 *   `ss_sint64_t`. Floating-point types are also supported;
 *
 * The normative pictures, classification, and preconditions are in the
 * par-strip specification in the freelibs workspace
 * (`.management/strategy/parstrip/SPEC.md`).
 *
 * `write_strip()` is the algorithm and is intentionally unimplemented.
 * `to_strip()` is a wrapper around it.
 *
 * Copy and move are the implicit value operations.
 */
template<
    int                 V_base
,   ss_typename_param_k T_value
>
class par_strip
{
public: // types
    /// This type
    typedef par_strip<
        V_base
    ,   T_value
    >                                                       class_type;
    /// The value type
    typedef T_value                                         value_type;
    /// The direction enumeration
    typedef par_strip_direction                             direction_type;

public: // constants
    /// The radix baked into this specialisation
    static const int    base    =   V_base;

public: // construction
    /// Constructs a strip from the given bounds, direction, and values.
    ///
    /// \param min_oom Smallest order drawn on each side;
    /// \param max_oom Largest order drawn on each side;
    /// \param direction Forward or backward;
    /// \param reference Reference (par) value. Must be strictly positive;
    /// \param sample Sample value. Must be non-negative;
    ///
    /// \pre min_oom < max_oom
    /// \pre reference > 0
    /// \pre sample >= 0
    /// \pre V_base >= 2
    par_strip(
        int             min_oom
    ,   int             max_oom
    ,   direction_type  direction
    ,   value_type      reference
    ,   value_type      sample
    );

public: // accessors
    /// Smallest order drawn on each side
    int             min_oom() const STLSOFT_NOEXCEPT;
    /// Largest order drawn on each side
    int             max_oom() const STLSOFT_NOEXCEPT;
    /// Forward or backward
    direction_type  direction() const STLSOFT_NOEXCEPT;
    /// Reference (par) value
    value_type      reference() const STLSOFT_NOEXCEPT;
    /// Sample value
    value_type      sample() const STLSOFT_NOEXCEPT;
    /// Character count of the rendered strip
    ss_size_t       strip_length() const STLSOFT_NOEXCEPT;

public: // operations
    /// Writes the strip into `dest`.
    ///
    /// \param dest Buffer of at least `strip_length()` characters
    /// \param cch Capacity of `dest`, in characters
    ///
    /// \pre NULL != dest
    /// \pre cch >= strip_length()
    ///
    /// \return The number of characters written, which is `strip_length()`
    ///
    /// Does not write a terminating NUL. The algorithm is intentionally
    /// unimplemented: the body returns 0 until the classification is
    /// filled in.
    ss_size_t   write_strip(char* dest, ss_size_t cch) const;

    /// The strip as a string. Equivalent to `write_strip()` into a buffer
    /// of `strip_length()` characters.
    std::string to_strip() const;

private: // fields
    direction_type  m_direction;
    int             m_max_oom;
    int             m_min_oom;
    value_type      m_reference;
    value_type      m_sample;
};


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

template<
    int                 V_base
,   ss_typename_param_k T_value
>
inline
par_strip<V_base, T_value>::par_strip(
    int             min_oom
,   int             max_oom
,   direction_type  direction
,   value_type      reference
,   value_type      sample
)
    : m_direction(direction)
    , m_max_oom(max_oom)
    , m_min_oom(min_oom)
    , m_reference(reference)
    , m_sample(sample)
{
    static_assert(V_base >= 2, "par_strip base must be >= 2");

    assert(min_oom < max_oom);
    assert(reference > value_type());
    assert(sample >= value_type());
}

template<
    int                 V_base
,   ss_typename_param_k T_value
>
inline
int
par_strip<V_base, T_value>::min_oom() const STLSOFT_NOEXCEPT
{
    return m_min_oom;
}

template<
    int                 V_base
,   ss_typename_param_k T_value
>
inline
int
par_strip<V_base, T_value>::max_oom() const STLSOFT_NOEXCEPT
{
    return m_max_oom;
}

template<
    int                 V_base
,   ss_typename_param_k T_value
>
inline
typename par_strip<V_base, T_value>::direction_type
par_strip<V_base, T_value>::direction() const STLSOFT_NOEXCEPT
{
    return m_direction;
}

template<
    int                 V_base
,   ss_typename_param_k T_value
>
inline
typename par_strip<V_base, T_value>::value_type
par_strip<V_base, T_value>::reference() const STLSOFT_NOEXCEPT
{
    return m_reference;
}

template<
    int                 V_base
,   ss_typename_param_k T_value
>
inline
typename par_strip<V_base, T_value>::value_type
par_strip<V_base, T_value>::sample() const STLSOFT_NOEXCEPT
{
    return m_sample;
}

template<
    int                 V_base
,   ss_typename_param_k T_value
>
inline
ss_size_t
par_strip<V_base, T_value>::strip_length() const STLSOFT_NOEXCEPT
{
    int const side_length = (m_max_oom - m_min_oom) + 1;

    return static_cast<ss_size_t>((2 * side_length) + 1);
}

template<
    int                 V_base
,   ss_typename_param_k T_value
>
inline
ss_size_t
par_strip<V_base, T_value>::write_strip(
    char*       dest
,   ss_size_t   cch
) const
{
    assert(NULL != dest);
    assert(cch >= strip_length());

    ((void)dest);
    ((void)cch);

    // RENDER: classify ROOM and write the single mark. Normative
    // pictures are in the par-strip specification. Return strip_length().

    return 0;
}

template<
    int                 V_base
,   ss_typename_param_k T_value
>
inline
std::string
par_strip<V_base, T_value>::to_strip() const
{
    ss_size_t const n = strip_length();
    std::string     s(static_cast<std::size_t>(n), '\0');
    ss_size_t const written = write_strip(&s[0], n);

    s.resize(static_cast<std::size_t>(written));

    return s;
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

#endif /* !STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_PAR_STRIP */

/* ///////////////////////////// end of file //////////////////////////// */

