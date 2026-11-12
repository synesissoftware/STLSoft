/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/i18n/codepage_sequence.hpp
 *
 * Purpose: Process Id sequence class.
 *
 * Created: 15th August 2025
 * Updated: 12th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2025-2026, Matthew Wilson and Synesis Information Systems
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


/** \file winstl/i18n/codepage_sequence.hpp
 *
 * \brief [C++] Definition of the winstl::codepage_sequence class
 *   (\ref group__library__I18N "I18N" Library).
 */

#ifndef WINSTL_INCL_WINSTL_I18N_HPP_CODEPAGE_SEQUENCE
#define WINSTL_INCL_WINSTL_I18N_HPP_CODEPAGE_SEQUENCE

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define WINSTL_VER_WINSTL_I18N_HPP_CODEPAGE_SEQUENCE_MAJOR     1
# define WINSTL_VER_WINSTL_I18N_HPP_CODEPAGE_SEQUENCE_MINOR     0
# define WINSTL_VER_WINSTL_I18N_HPP_CODEPAGE_SEQUENCE_REVISION  3
# define WINSTL_VER_WINSTL_I18N_HPP_CODEPAGE_SEQUENCE_EDIT      5
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

#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
# ifndef WINSTL_INCL_WINSTL_EXCEPTION_HPP_WINSTL_EXCEPTION
#  include <winstl/exception/winstl_exception.hpp>
# endif /* !WINSTL_INCL_WINSTL_EXCEPTION_HPP_WINSTL_EXCEPTION */
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
#ifndef WINSTL_INCL_WINSTL_MEMORY_HPP_PROCESSHEAP_ALLOCATOR
# include <winstl/memory/processheap_allocator.hpp>
#endif /* !WINSTL_INCL_WINSTL_MEMORY_HPP_PROCESSHEAP_ALLOCATOR */
#ifndef WINSTL_INCL_WINSTL_REGISTRY_ERROR_HPP_EXCEPTIONS
# include <winstl/registry/error/exceptions.hpp>
#endif /* !WINSTL_INCL_WINSTL_REGISTRY_ERROR_HPP_EXCEPTIONS */
#ifndef STLSOFT_INCL_STLSOFT_ALGORITHMS_HPP_POD
# include <stlsoft/algorithms/pod.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_ALGORITHMS_HPP_POD */
#ifndef STLSOFT_INCL_STLSOFT_COLLECTIONS_UTIL_HPP_COLLECTIONS
# include <stlsoft/collections/util/collections.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_COLLECTIONS_UTIL_HPP_COLLECTIONS */
#ifndef STLSOFT_INCL_STLSOFT_CONVERSION_HPP_STRING_TO_INTEGER
# include <stlsoft/conversion/string_to_integer.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_CONVERSION_HPP_STRING_TO_INTEGER */
#ifndef STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER
# include <stlsoft/memory/auto_buffer.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER */
#ifndef STLSOFT_INCL_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE
# include <stlsoft/smartptr/scoped_handle.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_STD_HPP_ITERATOR_HELPER
# include <stlsoft/util/std/iterator_helper.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_STD_HPP_ITERATOR_HELPER */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_STRING_H_SNPRINTF
# include <stlsoft/util/string/snprintf.h>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_STRING_H_SNPRINTF */

#ifndef WINSTL_INCL_WINSTL_API_external_h_ErrorHandling
# include <winstl/api/external/ErrorHandling.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_ErrorHandling */
#ifndef WINSTL_INCL_WINSTL_API_external_h_Internationalization
# include <winstl/api/external/Internationalization.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_Internationalization */
#ifndef WINSTL_INCL_WINSTL_API_external_h_Registry
# include <winstl/api/external/Registry.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_Registry */


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

/** Codepage sequence
 *
 * \ingroup group__library__I18N
 */
class codepage_sequence
    : public STLSOFT_NS_QUAL(stl_collection_tag)
{
/// \name Member Types
/// @{
public:
    /// The value type
    typedef UINT                                            value_type;
    /// The allocator type
    typedef processheap_allocator<value_type>               allocator_type;
    /// The class type
    typedef codepage_sequence                               class_type;
    /// The non-mutating (const) pointer type
    typedef value_type const*                               const_pointer;
    /// The non-mutating (const) reference type
    typedef value_type const&                               const_reference;
    /// The non-mutating (const) iterator type
    typedef STLSOFT_NS_QUAL(pointer_iterator)<
        value_type
    ,   const_pointer
    ,   const_reference
    >::type                                                 const_iterator;
    /// The size type
    typedef ws_size_t                                       size_type;
    /// The difference type
    typedef ws_ptrdiff_t                                    difference_type;
#if defined(STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT)
    /// The non-mutating (const) reverse iterator type
    typedef STLSOFT_NS_QUAL(const_reverse_bidirectional_iterator_base)<
        const_iterator
    ,   value_type
    ,   const_reference
    ,   const_pointer
    ,   difference_type
    >                                                       const_reverse_iterator;
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */
private:
    typedef STLSOFT_NS_QUAL(auto_buffer)<
        value_type
    ,   64
    ,   allocator_type
    >                                                       buffer_type_;
/// @}

/// \name Construction
/// @{
public:
    /// Constructs a sequence from the current codepages in the host system
    codepage_sequence();
    /// Copies the contents of the sequence
    codepage_sequence(class_type const& rhs);
    /// Releases the storage associated with the process id list
    ~codepage_sequence() STLSOFT_NOEXCEPT;
private:
    void operator =(class_type const&) STLSOFT_COPY_ASSIGNMENT_PROSCRIBED;
/// @}

/// \name Iteration
/// @{
public:
    /// Begins the iteration
    ///
    /// \return An iterator representing the start of the sequence
    const_iterator  cbegin() const;
    /// Ends the iteration
    ///
    /// \return An iterator representing the end of the sequence
    const_iterator  cend() const;

    /// Begins the iteration
    ///
    /// \return An iterator representing the start of the sequence
    const_iterator  begin() const;
    /// Ends the iteration
    ///
    /// \return An iterator representing the end of the sequence
    const_iterator  end() const;

#if defined(STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT)
    /// Begins the reverse iteration
    ///
    /// \return An iterator representing the start of the reverse sequence
    const_reverse_iterator  rbegin() const;
    /// Ends the reverse iteration
    ///
    /// \return An iterator representing the end of the reverse sequence
    const_reverse_iterator  rend() const;
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */
/// @}

/// \name Element Access
/// @{
public:
    /// Returns a reference to the element at the given index
    ///
    /// \param index The required index. Behaviour is undefined, if not within the range [0, size())
    const_reference operator [](size_type index) const;
    /// Returns a pointer to the underlying array
    const_pointer data() const STLSOFT_NOEXCEPT;
/// @}

/// \name Attributes
/// @{
public:
    /// Indicates whether the sequence is empty
    ws_bool_t   empty() const STLSOFT_NOEXCEPT;
    /// Returns the number of identifiers in the sequence
    size_type   size() const STLSOFT_NOEXCEPT;
/// @}

/// \name Fields
/// @{
private:
    buffer_type_    m_cpids;
/// @}
};


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

inline
codepage_sequence::codepage_sequence()
    : m_cpids(0)
{
    static char const keyPath[] = "SYSTEM\\CurrentControlSet\\Control\\Nls\\CodePage";

    HKEY            k;
    LSTATUS const   r1 = WINSTL_API_EXTERNAL_Registry_RegOpenKeyExA(
        HKEY_LOCAL_MACHINE
    ,   keyPath
    ,   0
    ,   KEY_READ
    ,   &k
    );

    if (ERROR_SUCCESS != r1)
    {
        char    msg[201];

        stlsoft_C_snprintf(msg, STLSOFT_NUM_ELEMENTS(msg), "could not open registry key 'HKLM\\%s'", keyPath);

        if (ERROR_ACCESS_DENIED == r1)
        {
            STLSOFT_THROW_X(access_denied_exception(msg, r1));
        }
        else
        {
            STLSOFT_THROW_X(registry_exception(msg, r1));
        }
    }
    else
    {
        stlsoft::scoped_handle<HKEY> scoper_k(k, WINSTL_API_EXTERNAL_Registry_RegCloseKey);

        for (DWORD index = 0; 20000 != index; ++index)
        {
            CHAR            value[21];
            DWORD           cchValue = STLSOFT_NUM_ELEMENTS(value);
            LSTATUS const   r2 = WINSTL_API_EXTERNAL_Registry_RegEnumValueA(k, index, value, &cchValue, NULL, NULL, NULL, NULL);

            if (ERROR_SUCCESS == r2)
            {
                value[cchValue] = '\0';

                CHAR const* endptr;
                UINT const  cp = STLSOFT_NS_QUAL(string_to_integer)(value, (size_t)cchValue, &endptr);

                if (0 != cp ||
                    static_cast<difference_type>(cchValue) == (endptr - value))
                {
                    m_cpids.resize(1 + m_cpids.size());

                    m_cpids[m_cpids.size() - 1] = cp; //CP_ACP
                }
            }
            else
            {
                if (ERROR_NO_MORE_ITEMS == r2)
                {
                    break;
                }
                else if (index > 20000)
                {
                    break;
                }
            }
        }
    }

    STLSOFT_NS_QUAL_STD(sort)(m_cpids.begin(), m_cpids.end());
}

inline
codepage_sequence::codepage_sequence(codepage_sequence const& rhs)
    : m_cpids(rhs.m_cpids.size())
{
    STLSOFT_NS_QUAL_STD(copy)(rhs.m_cpids.begin(), rhs.m_cpids.end(), m_cpids.begin());
}

inline
codepage_sequence::~codepage_sequence() STLSOFT_NOEXCEPT
{}

inline
codepage_sequence::const_iterator
codepage_sequence::cbegin() const
{
    return &*m_cpids.begin();
}

inline
codepage_sequence::const_iterator
codepage_sequence::cend() const
{
    return &*m_cpids.end();
}

inline
codepage_sequence::const_iterator
codepage_sequence::begin() const
{
    return cbegin();
}

inline
codepage_sequence::const_iterator
codepage_sequence::end() const
{
    return cend();
}

#if defined(STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT)

inline
codepage_sequence::const_reverse_iterator
codepage_sequence::rbegin() const
{
    return const_reverse_iterator(end());
}

inline
codepage_sequence::const_reverse_iterator
codepage_sequence::rend() const
{
    return const_reverse_iterator(begin());
}
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */

inline
codepage_sequence::const_reference
codepage_sequence::operator [](codepage_sequence::size_type index) const
{
    WINSTL_MESSAGE_ASSERT("Index out of range", index < size());

    return m_cpids[index];
}

inline
codepage_sequence::const_pointer
codepage_sequence::data() const STLSOFT_NOEXCEPT
{
    return m_cpids.data();
}


inline
ws_bool_t
codepage_sequence::empty() const STLSOFT_NOEXCEPT
{
    return m_cpids.empty();
}

inline
codepage_sequence::size_type
codepage_sequence::size() const STLSOFT_NOEXCEPT
{
    return m_cpids.size();
}
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


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

#endif /* !WINSTL_INCL_WINSTL_I18N_HPP_CODEPAGE_SEQUENCE */

/* ///////////////////////////// end of file //////////////////////////// */

