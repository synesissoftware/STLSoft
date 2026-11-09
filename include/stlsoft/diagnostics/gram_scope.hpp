/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/diagnostics/gram_scope.hpp
 *
 * Purpose: Definition of the LibraryIdentifier enumeration.
 *
 * Created: 13th May 2013
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


/** \file stlsoft/diagnostics/gram_scope.hpp
 *
 * \brief [C++] Definition of the gram_scope class template
 *   (\ref group__library__Diagnostic "Diagnostic" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_GRAM_SCOPE
#define STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_GRAM_SCOPE

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_GRAM_SCOPE_MAJOR       1
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_GRAM_SCOPE_MINOR       0
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_GRAM_SCOPE_REVISION    3
# define STLSOFT_VER_STLSOFT_DIAGNOSTICS_HPP_GRAM_SCOPE_EDIT        4
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
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* STLSOFT_NO_NAMESPACE */

/* /////////////////////////////////////////////////////////////////////////
 * classes
 */

/** Scoping class for histogram timings
 *
 * \ingroup group__library__Diagnostic
 *
 * \tparam T_gram
 * \tparam T_stopwatch
 *
 * \see doomgram
 * \see std_chrono_hrc_stopwatch
 */
template<
    ss_typename_param_k T_gram
,   ss_typename_param_k T_stopwatch
>
class gram_scope
{
public: // types
    /// The histogram type
    typedef T_gram                                          gram_type;
    /// The stopwatch type
    typedef T_stopwatch                                     stopwatch_type;
    /// This type
    typedef gram_scope<
        gram_type
    ,   stopwatch_type
    >                                                       class_type;
private:
    typedef ss_typename_type_k stopwatch_type::interval_type
                                                            interval_type_;

public: // construction
    gram_scope(
        gram_type&      gram
    ,   stopwatch_type& sw
    )
        : m_gram(gram)
        , m_sw(sw)
    {
        m_sw.start();
    }
    ~gram_scope()
    {
        interval_type_ const d_ns = (m_sw.stop(), m_sw.get_nanoseconds());

        m_gram.push_event_time_ns(d_ns);
    }
private:
    gram_scope(class_type const&) STLSOFT_COPY_CONSTRUCTION_PROSCRIBED;
    void operator =(class_type const&) STLSOFT_COPY_ASSIGNMENT_PROSCRIBED;


private: // fields
    gram_type&      m_gram;
    stopwatch_type& m_sw;
};


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

#endif /* !STLSOFT_INCL_STLSOFT_DIAGNOSTICS_HPP_GRAM_SCOPE */

/* ///////////////////////////// end of file //////////////////////////// */

