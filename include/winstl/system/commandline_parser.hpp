/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/system/commandline_parser.hpp (originally MLCmdArg.h, ::SynesisStd)
 *
 * Purpose: commandline_parser class.
 *
 * Created: 20th May 2000
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2000-2019, Matthew Wilson and Synesis Software
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


/** \file winstl/system/commandline_parser.hpp
 *
 * \brief [C++] Definition of the winstl::basic_commandline_parser
 *  class template
 *   (\ref group__library__System "System" Library).
 */


#ifndef WINSTL_INCL_WINSTL_SYSTEM_HPP_COMMANDLINE_PARSER
#define WINSTL_INCL_WINSTL_SYSTEM_HPP_COMMANDLINE_PARSER

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define WINSTL_VER_WINSTL_SYSTEM_HPP_COMMANDLINE_PARSER_MAJOR      2
# define WINSTL_VER_WINSTL_SYSTEM_HPP_COMMANDLINE_PARSER_MINOR      2
# define WINSTL_VER_WINSTL_SYSTEM_HPP_COMMANDLINE_PARSER_REVISION   2
# define WINSTL_VER_WINSTL_SYSTEM_HPP_COMMANDLINE_PARSER_EDIT       57
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef WINSTL_INCL_WINSTL_H_WINSTL
# include <winstl/winstl.h>
#endif /* !WINSTL_INCL_WINSTL_H_WINSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef WINSTL_INCL_WINSTL_MEMORY_HPP_PROCESSHEAP_ALLOCATOR
# include <winstl/memory/processheap_allocator.hpp>
#endif /* !WINSTL_INCL_WINSTL_MEMORY_HPP_PROCESSHEAP_ALLOCATOR */
#ifndef STLSOFT_INCL_STLSOFT_SYSTEM_HPP_COMMANDLINE_PARSER
# include <stlsoft/system/commandline_parser.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_SYSTEM_HPP_COMMANDLINE_PARSER */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef WINSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
/* There is no stlsoft namespace, so must define ::winstl */
namespace winstl
{
# else
/* Define stlsoft::winstl_project */
namespace stlsoft
{
namespace winstl_project
{
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !WINSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * classes
 */

/** Parses a Windows (<code>WinMain()</code>) command line into parts, and
 * provides array semantics for their access.
 *
\code
winstl::commandline_parser  cp("abc \"d e f\" ghi");

assert(3 == cp.size());
assert(0 == ::strcmp("abc",   cp[0]));
assert(0 == ::strcmp("d e f", cp[1]));
assert(0 == ::strcmp("ghi",   cp[2]));
\endcode
 *
 * \ingroup group__library__System
 */
template<
    ss_typename_param_k C
,   ss_typename_param_k T = STLSOFT_NS_QUAL(stlsoft_char_traits)<C>
,   ss_typename_param_k A = processheap_allocator<C>
>
class basic_commandline_parser
{
public: // types
    /// The character type
    typedef C                                               char_type;
    /// The traits type
    typedef T                                               traits_type;
private:
    /// The traits type
    typedef A                                               allocator_type_;
public:
    /// The current instantiation of the type
    typedef basic_commandline_parser<
        char_type
    ,   traits_type
    ,   allocator_type_
    >                                                       class_type;
private:
    typedef STLSOFT_NS_QUAL(basic_commandline_parser)<
        char_type
    ,   traits_type
    ,   allocator_type_
    >                                                       ss_clp_type_;
public:
    /// The value type
    typedef ss_typename_type_k ss_clp_type_::value_type     value_type;
    /// The non-mutating (const) iterator type
    typedef ss_typename_type_k ss_clp_type_::const_iterator
                                                            const_iterator;
    /// The size type
    typedef ss_size_t                                       size_type;

public: // construction
    /** Parses the given command-line and creates an internal array of
     * pointers to the arguments.
     */
    ss_explicit_k
    basic_commandline_parser(char_type const* cmdLine)
        : m_clp(cmdLine)
    {}

# if 0

    /** Parses the given command-line and creates an internal array of
     * pointers to the arguments.
     */
    ss_explicit_k
    basic_commandline_parser(char_type const* cmdLine, size_type len)
        : m_clp((cmdLine, len)
    {}
# endif

public: // accessors
    /// The number of arguments
    size_type size() const
    {
        return m_clp.size();
    }

    /** Returns a non-mutating (const) pointer to each argument
     *   string.
     *
     * \param index The index of the argument
     *
     * \note The behaviour is undefined if <code>index</code> is greater
     *  than <code>size()</code>. If <code>index</code> is equal to
     *  <code>size()</code>, then the returned reference may not be used,
     *  other than to take its address (which is the address of the
     *  <a href="http://www.extendedstl.com/glossary.html#end-element">"end-element"</a>).
     */
    value_type const& operator [](size_type index) const
    {
        WINSTL_ASSERT(index <= size());

        return m_clp[index];
    }

public: // iteration
    /// An iterator representing the start of the sequence
    const_iterator  begin() const
    {
        return m_clp.begin();
    }
    /// An iterator representing the end of the sequence
    const_iterator  end() const
    {
        return m_clp.end();
    }

private: // implementation

private: // fields
    ss_clp_type_    m_clp;
};


/* /////////////////////////////////////////////////////////////////////////
 * typedefs for commonly encountered types
 */

/** Specialisation of the basic_commandline_parser template for the ANSI character type \c char
 *
 * \ingroup group__library__System
 */
typedef basic_commandline_parser<ws_char_a_t>               commandline_parser_a;
/** Specialisation of the basic_commandline_parser template for the Unicode character type \c wchar_t
 *
 * \ingroup group__library__System
 */
typedef basic_commandline_parser<ws_char_w_t>               commandline_parser_w;
/** Specialisation of the basic_commandline_parser template for the Win32 character type \c TCHAR
 *
 * \ingroup group__library__System
 */
typedef basic_commandline_parser<TCHAR>                     commandline_parser;


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef WINSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
} // namespace winstl
# else
} // namespace winstl_project
} // namespace stlsoft
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !WINSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !WINSTL_INCL_WINSTL_SYSTEM_HPP_COMMANDLINE_PARSER */

/* ///////////////////////////// end of file //////////////////////////// */

