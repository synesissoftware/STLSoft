/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/system/commandline_parser.hpp (originally MLCmdArg.h, ::SynesisStd)
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


/** \file stlsoft/system/commandline_parser.hpp
 *
 * \brief [C++] Definition of the stlsoft::basic_commandline_parser
 *  class template
 *   (\ref group__library__System "System" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_SYSTEM_HPP_COMMANDLINE_PARSER
#define STLSOFT_INCL_STLSOFT_SYSTEM_HPP_COMMANDLINE_PARSER

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_SYSTEM_HPP_COMMANDLINE_PARSER_MAJOR    2
# define STLSOFT_VER_STLSOFT_SYSTEM_HPP_COMMANDLINE_PARSER_MINOR    3
# define STLSOFT_VER_STLSOFT_SYSTEM_HPP_COMMANDLINE_PARSER_REVISION 2
# define STLSOFT_VER_STLSOFT_SYSTEM_HPP_COMMANDLINE_PARSER_EDIT     61
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

#if defined(STLSOFT_COMPILER_IS_MSVC) && \
    _MSC_VER < 1200
# error stlsoft/system/commandline_parser.hpp is not compatible with Visual C++ 5.0 or earlier
#endif /* compiler */

#ifndef STLSOFT_INCL_STLSOFT_MEMORY_UTIL_HPP_ALLOCATOR_FEATURES
# include <stlsoft/memory/util/allocator_features.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_UTIL_HPP_ALLOCATOR_FEATURES */
#ifndef STLSOFT_INCL_STLSOFT_MEMORY_UTIL_HPP_ALLOCATOR_SELECTOR
# include <stlsoft/memory/util/allocator_selector.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_UTIL_HPP_ALLOCATOR_SELECTOR */
#ifndef STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER
# include <stlsoft/memory/auto_buffer.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER */
#ifndef STLSOFT_INCL_STLSOFT_STRING_HPP_CHAR_TRAITS
# include <stlsoft/string/char_traits.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_CHAR_TRAITS */
#ifndef STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_HPP_STRING
# include <stlsoft/shims/access/string.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_HPP_STRING */

#ifndef STLSOFT_INCL_H_CTYPE
# define STLSOFT_INCL_H_CTYPE
# include <ctype.h>     // for isspace()
#endif /* !STLSOFT_INCL_H_CTYPE */


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

/** Parses a command line into parts, and provides sequence semantics for
 * their access.
 *
\code
stlsoft::commandline_parser_a  cp("abc \"d e f\" ghi");

assert(3 == cp.size());
assert(0 == ::strcmp("abc",   cp[0]));
assert(0 == ::strcmp("d e f", cp[1]));
assert(0 == ::strcmp("ghi",   cp[2]));

std::copy(cp.begin(), cp.end()
        , std::ostream_iterator<char const*>(std::cout, "\n"));
\endcode
 *
 * \ingroup group__library__System
 */
template<
    ss_typename_param_k C
,   ss_typename_param_k T = STLSOFT_NS_QUAL(stlsoft_char_traits)<C>
,   ss_typename_param_k A = ss_typename_type_def_k allocator_selector<C>::allocator_type
>
class basic_commandline_parser
{
public: // types
    /// The character type
    typedef C                                               char_type;
    /// The traits type
    typedef T                                               traits_type;
#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
    typedef A                                               allocator_type;
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */
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
    typedef ss_bool_t                                       bool_type_;
    typedef char_type*                                      pointer_type_;
#ifdef STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT
    typedef ss_typename_type_k A::ss_template_qual_k rebind<
        pointer_type_
    >::other                                                pointers_allocator_type_;
#else /* ? STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
    typedef ss_typename_type_k allocator_selector<
        pointer_type_
    >::allocator_type                                       pointers_allocator_type_;
#endif /* STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
    typedef STLSOFT_NS_QUAL(auto_buffer)<
        char_type
    ,   256
    ,   allocator_type_
    >                                                       buffer_type_;
    typedef STLSOFT_NS_QUAL(auto_buffer)<
        pointer_type_
    ,   20
    ,   pointers_allocator_type_
    >                                                       pointers_type_;
    typedef ss_typename_type_k buffer_type_::iterator       iterator;
public:
    /// The value type
    typedef ss_typename_type_k pointers_type_::value_type   value_type;
    /// The non-mutating (const) iterator type
    typedef ss_typename_type_k pointers_type_::const_iterator
                                                            const_iterator;
    /// The size type
    typedef ss_size_t                                       size_type;

public: // construction
    /** Parses the given command-line and creates an internal array of
     * pointers to the arguments.
     */
    ss_explicit_k
    basic_commandline_parser(char_type const* cmdLine)
        : m_buffer(1 + STLSOFT_NS_QUAL(c_str_len)(cmdLine))
        , m_pointers(0)
    {
        STLSOFT_ASSERT(NULL != cmdLine);

        traits_type::copy(&m_buffer[0], cmdLine, m_buffer.size());

        // Here's the algorithm:
        //
        // Walk the string, mindful of quotes, remembering whether in
        // string-escaped section, and writing the nul-character into the
        // spaces before arguments so can present pointers

        enum state_t
        {
                space
            ,   argument
            ,   quotedArgument
        };

        state_t     state   =   space;
        iterator    b       =   m_buffer.begin();
        iterator    e       =   m_buffer.end() - 1;

        for (; b != e; ++b)
        {
            char_type const ch = *b;

            STLSOFT_ASSERT('\0' != ch);

            bool remove_ch = false;

            switch (state)
            {
            case space:

                if (!isspace(ch))
                {
                    if ('"' == ch)
                    {
                        remove_ch = true;

                        state = quotedArgument;
                    }
                    else
                    {
                        state = argument;
                    }

                    add_pointer_(&*b);
                }
                break;
            case argument:

                if (isspace(ch))
                {
                    *b = '\0';

                    state = space;
                }
                else if ('"' == ch)
                {
                    remove_ch = true;

                    state = quotedArgument;
                }
                break;
            case quotedArgument:

                if ('"' == ch)
                {
                    remove_ch = true;

                    state = argument;
                }
                break;
            }

            if (remove_ch)
            {
                // special case - must remove
                {
                    size_type const num_processed = b - m_buffer.begin();
                    size_type const num_remaining = m_buffer.size() - num_processed;

                    STLSOFT_API_EXTERNAL_memfns_memmove(&m_buffer[num_processed] + 0, &m_buffer[num_processed] + 1, sizeof(char_type) * (num_remaining - 1));
                    m_buffer.resize(m_buffer.size() - 1);

                    --b;
                    --e;
                }
            }
        }

        add_pointer_(NULL);
    }

public: // accessors
    /// The number of arguments
    size_type size() const
    {
        return m_pointers.size() - 1;
    }

    /** Returns a non-mutating (const) pointer to each argument
     *   string.
     *
     * \param index The index of the argument
     *
     * \note The behaviour is undefined if <code>index</code> is not less
     *  than <code>size()</code>.
     */
    value_type const& operator [](size_type index) const
    {
        STLSOFT_ASSERT(index <= size());

        return m_pointers[index];
    }

public: // iteration
    /// An iterator representing the start of the sequence
    const_iterator  begin() const
    {
        return m_pointers.begin();
    }
    /// An iterator representing the end of the sequence
    const_iterator  end() const
    {
        return m_pointers.end() - 1;
    }

private: // implementation
    bool_type_
    add_pointer_(pointer_type_ p)
    {
        if (!m_pointers.resize(1 + m_pointers.size()))
        {
            return false;
        }

        m_pointers[m_pointers.size() - 1] = p;

        return true;
    }

private: // fields
    buffer_type_    m_buffer;
    pointers_type_  m_pointers;
};


/* /////////////////////////////////////////////////////////////////////////
 * typedefs for commonly encountered types
 */

/** Specialisation of the basic_commandline_parser template for the ANSI character type \c char
 *
 * \ingroup group__library__System
 */
typedef basic_commandline_parser<ss_char_a_t>               commandline_parser_a;
/** Specialisation of the basic_commandline_parser template for the Unicode character type \c wchar_t
 *
 * \ingroup group__library__System
 */
typedef basic_commandline_parser<ss_char_w_t>               commandline_parser_w;


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

#endif /* !STLSOFT_INCL_STLSOFT_SYSTEM_HPP_COMMANDLINE_PARSER */

/* ///////////////////////////// end of file //////////////////////////// */

