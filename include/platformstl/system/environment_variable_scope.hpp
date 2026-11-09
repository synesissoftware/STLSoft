/* /////////////////////////////////////////////////////////////////////////
 * File:    platformstl/system/environment_variable_scope.hpp
 *
 * Purpose: Definition of the environment_variable_scope class.
 *
 * Created: 26th April 2025
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


/** \file platformstl/system/environment_variable_scope.hpp
 *
 * \brief [C++] Definition of the platformstl::environment_variable_scope
 *  class
 *   (\ref group__library__System "System" Library).
 */

#ifndef PLATFORMSTL_INCL_PLATFORMSTL_SYSTEM_HPP_ENVIRONMENT_SCOPE
#define PLATFORMSTL_INCL_PLATFORMSTL_SYSTEM_HPP_ENVIRONMENT_SCOPE

/* File version */
#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define PLATFORMSTL_VER_PLATFORMSTL_SYSTEM_HPP_ENVIRONMENT_SCOPE_MAJOR     2
# define PLATFORMSTL_VER_PLATFORMSTL_SYSTEM_HPP_ENVIRONMENT_SCOPE_MINOR     2
# define PLATFORMSTL_VER_PLATFORMSTL_SYSTEM_HPP_ENVIRONMENT_SCOPE_REVISION  15
# define PLATFORMSTL_VER_PLATFORMSTL_SYSTEM_HPP_ENVIRONMENT_SCOPE_EDIT      47
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef PLATFORMSTL_INCL_PLATFORMSTL_HPP_PLATFORMSTL
# include <platformstl/platformstl.hpp>
#endif /* !PLATFORMSTL_INCL_PLATFORMSTL_HPP_PLATFORMSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef PLATFORMSTL_INCL_PLATFORMSTL_SYSTEM_HPP_ENVIRONMENT_VARIABLE_TRAITS
# include <platformstl/system/environment_variable_traits.hpp>
#endif /* !PLATFORMSTL_INCL_PLATFORMSTL_SYSTEM_HPP_ENVIRONMENT_VARIABLE_TRAITS */
#ifndef STLSOFT_INCL_STLSOFT_STRING_HPP_SIMPLE_STRING
# include <stlsoft/string/simple_string.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_SIMPLE_STRING */
#ifndef STLSOFT_INCL_STLSOFT_STRING_H_STRING_SLICE
# include <stlsoft/string/string_slice.h>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_H_STRING_SLICE */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#if defined(STLSOFT_NO_NAMESPACE) || \
    defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
/* There is no stlsoft namespace, so must define ::platformstl */
namespace platformstl
{
#else
/* Define stlsoft::platformstl_project */
namespace stlsoft
{
namespace platformstl_project
{
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * classes
 */

/** T.B.C.
 *
 */
class environment_variable_scope
{
public: // types
    /// The character type
    typedef ss_char_a_t                                     char_type;
    /// The traits type
    typedef environment_variable_traits                     traits_type;
    /// The class type
    typedef environment_variable_scope                      class_type;
    /// The slice type
    typedef STLSOFT_NS_QUAL(string_slice_m_t)               slice_type;
private:
    // NOTE: has to be simple_string, because it can handle a NULL
    typedef STLSOFT_NS_QUAL(simple_string)                  string_type_;

public: // construction
    /// T.B.C.
    ///
    /// \param name T.B.C.
    /// \param new_value T.B.C.
    environment_variable_scope(
        char_type const*    name
    ,   char_type const*    new_value
    )
        : m_existed()
        , m_name(name)
        , m_current(test_ptr_(name, exists_flag_()))
    {
        if (ss_nullptr_k == new_value)
        {
            traits_type::erase_variable(name);
        }
        else
        {
            traits_type::set_variable(name, new_value);
        }
    }
    /// T.B.C.
    ///
    /// \note This is not declared `noexcept`, as a future version might
    ///  throw in the case that the erasure/reset fails
    ~environment_variable_scope()
    {
        if (m_existed)
        {
            traits_type::set_variable(m_name.c_str(), m_current.c_str());
        }
        else
        {
            traits_type::erase_variable(m_name.c_str());
        }
    }
private:
    environment_variable_scope(class_type const&) STLSOFT_COPY_CONSTRUCTION_PROSCRIBED;
    void operator =(class_type const&) STLSOFT_COPY_ASSIGNMENT_PROSCRIBED;

public: // attributes
    /// Indicates whether the named environment variable existed at the time
    /// of construction of the scoping instance
    bool
    existed() const STLSOFT_NOEXCEPT
    {
        return m_existed;
    }

    /// Obtains the value, if present, of the named environment variable if
    /// it existed at the time of construction of the scoping instance
    slice_type
    current() const STLSOFT_NOEXCEPT
    {
        if (m_existed)
        {
            return slice_type::create(m_current.data(), m_current.size());
        }
        else
        {
            return slice_type::create();
        }
    }

private: // implementation
    static
    char_type const*
    test_ptr_(
        char_type const*    name
    ,   bool&               exists
    )
    {
        char const* const value = traits_type::get_variable(name);

        exists = ss_nullptr_k != value;

        return value;
    }
    bool&
    exists_flag_() STLSOFT_NOEXCEPT
    {
        return m_existed;
    }

private: // fields
    bool            m_existed;
    string_type_    m_name;
    string_type_    m_current;
};


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

} // namespace platformstl_project
} // namespace stlsoft


/* /////////////////////////////////////////////////////////////////////////
* inclusion control
*/

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !PLATFORMSTL_INCL_PLATFORMSTL_SYSTEM_HPP_ENVIRONMENT_SCOPE */

/* ///////////////////////////// end of file //////////////////////////// */

