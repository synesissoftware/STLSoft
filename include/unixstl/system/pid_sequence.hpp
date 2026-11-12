/* /////////////////////////////////////////////////////////////////////////
 * File:    unixstl/system/pid_sequence.hpp
 *
 * Purpose: Process Id sequence class.
 *
 * Created: 16th August 2025
 * Updated: 12th November 2026
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


/** \file unixstl/system/pid_sequence.hpp
 *
 * \brief [C++] Definition of the unixstl::pid_sequence class
 *   (\ref group__library__System "System" Library).
 */

#ifndef UNIXSTL_INCL_UNIXSTL_SYSTEM_HPP_PID_SEQUENCE
#define UNIXSTL_INCL_UNIXSTL_SYSTEM_HPP_PID_SEQUENCE

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define UNIXSTL_VER_UNIXSTL_SYSTEM_HPP_PID_SEQUENCE_MAJOR      0
# define UNIXSTL_VER_UNIXSTL_SYSTEM_HPP_PID_SEQUENCE_MINOR      0
# define UNIXSTL_VER_UNIXSTL_SYSTEM_HPP_PID_SEQUENCE_REVISION   3
# define UNIXSTL_VER_UNIXSTL_SYSTEM_HPP_PID_SEQUENCE_EDIT       5
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef UNIXSTL_INCL_UNIXSTL_H_UNIXSTL
# include <unixstl/unixstl.h>
#endif /* !UNIXSTL_INCL_UNIXSTL_H_UNIXSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
# ifndef UNIXSTL_INCL_UNIXSTL_EXCEPTION_HPP_ACCESS_EXCEPTION
#  include <unixstl/exception/access_exception.hpp>
# endif /* !UNIXSTL_INCL_UNIXSTL_EXCEPTION_HPP_ACCESS_EXCEPTION */
# ifndef UNIXSTL_INCL_UNIXSTL_EXCEPTION_HPP_FILESYSTEM_EXCEPTION
#  include <unixstl/exception/filesystem_exception.hpp>
# endif /* !UNIXSTL_INCL_UNIXSTL_EXCEPTION_HPP_FILESYSTEM_EXCEPTION */
# ifndef UNIXSTL_INCL_UNIXSTL_EXCEPTION_HPP_FILE_NOT_FOUND_EXCEPTION
#  include <unixstl/exception/file_not_found_exception.hpp>
# endif /* !UNIXSTL_INCL_UNIXSTL_EXCEPTION_HPP_FILE_NOT_FOUND_EXCEPTION */
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
#ifndef UNIXSTL_INCL_UNIXSTL_FILESYSTEM_HPP_FILESYSTEM_TRAITS
# include <unixstl/filesystem/filesystem_traits.hpp>
#endif /* !UNIXSTL_INCL_UNIXSTL_FILESYSTEM_HPP_FILESYSTEM_TRAITS */
#ifndef STLSOFT_INCL_STLSOFT_ALGORITHMS_HPP_POD
# include <stlsoft/algorithms/pod.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_ALGORITHMS_HPP_POD */
#ifndef STLSOFT_INCL_STLSOFT_COLLECTIONS_UTIL_HPP_COLLECTIONS
# include <stlsoft/collections/util/collections.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_COLLECTIONS_UTIL_HPP_COLLECTIONS */
#ifndef STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER
# include <stlsoft/memory/auto_buffer.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER */
#ifndef STLSOFT_INCL_STLSOFT_MEMORY_HPP_MALLOC_ALLOCATOR
# include <stlsoft/memory/malloc_allocator.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_HPP_MALLOC_ALLOCATOR */
#ifndef STLSOFT_INCL_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE
# include <stlsoft/smartptr/scoped_handle.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_HPP_STD_SWAP
# include <stlsoft/util/std_swap.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_HPP_STD_SWAP */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_STD_HPP_ITERATOR_HELPER
# include <stlsoft/util/std/iterator_helper.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_STD_HPP_ITERATOR_HELPER */

#ifndef STLSOFT_INCL_H_ERRNO
# define STLSOFT_INCL_H_ERRNO
# include <errno.h>
#endif /* !STLSOFT_INCL_H_ERRNO */

#if 0
#elif defined(UNIXSTL_OS_IS_LINUX)
#elif defined(UNIXSTL_OS_IS_MACOSX)

# ifndef STLSOFT_INCL_H_LIBPROC
#  define STLSOFT_INCL_H_LIBPROC
#  include <libproc.h>
# endif /* !STLSOFT_INCL_H_LIBPROC */
#else

# error Operating system not currently supported
#endif


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef UNIXSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
/* There is no stlsoft namespace, so must define ::unixstl */
namespace unixstl
{
# else
/* Define stlsoft::unixstl_project */
namespace stlsoft
{
namespace unixstl_project
{
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !UNIXSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * classes
 */

/** Process Id sequence
 *
 * \ingroup group__library__System
 */
class pid_sequence
    : public STLSOFT_NS_QUAL(stl_collection_tag)
{
/// \name Member Types
/// @{
public:
    /// The value type
    typedef int                                             value_type;
    /// The allocator type
    typedef malloc_allocator<value_type>                    allocator_type;
    /// The class type
    typedef pid_sequence                                    class_type;
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
    typedef us_size_t                                       size_type;
    /// The difference type
    typedef us_ptrdiff_t                                    difference_type;
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
#if 0
#elif defined(UNIXSTL_OS_IS_LINUX)
    ,   256
#elif defined(UNIXSTL_OS_IS_MACOSX)
    ,   512
#else
# error Operating system not currently supported
#endif
    ,   allocator_type
    >                                                       buffer_type_;
    typedef char                                            char_type_;
    typedef filesystem_traits<char_type_>                   traits_type_;
public:

    enum
    {
            elideSched  =   0x0001  //!< causes the scheduler process to be elided from the list
        ,   elideInit   =   0x0002  //!< causes the init process to be elided from the list
        ,   sort        =   0x0004  //!< causes the process ids to be sorted
    };
/// @}

/// \name Construction
/// @{
public:
    /// Constructs a sequence from the current processes in the host system
    ss_explicit_k pid_sequence(us_uint32_t flags = elideSched | elideInit);
    /// Copies the contents of the sequence
    pid_sequence(class_type const& rhs);
    /// Releases the storage associated with the process id list
    ~pid_sequence() STLSOFT_NOEXCEPT;
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
/// @}

/// \name Attributes
/// @{
public:
    /// Indicates whether the sequence is empty
    us_bool_t   empty() const STLSOFT_NOEXCEPT;
    /// Returns the number of identifiers in the sequence
    size_type   size() const STLSOFT_NOEXCEPT;
/// @}

/// \name System Traits
/// @{
public:
    /// The process identifier of the Idle process
    ///
    /// \note The Idle process is a pseudo-process. You should not attempt to
    ///        manipulate it using the process control functions
    static value_type   schedProcessId()
    {
#if 0
#elif defined(UNIXSTL_OS_IS_LINUX)

        return 0;
#elif defined(UNIXSTL_OS_IS_MACOSX)

        return 0;
#else

# error Operating system not currently supported
#endif
    }
    /// The process identifier of the System process
    ///
    /// \note The System process is a pseudo-process. You should not attempt to
    ///        manipulate it using the process control functions
    static value_type   initProcessId()
    {
#if 0
#elif defined(UNIXSTL_OS_IS_LINUX)

        return 1;
#elif defined(UNIXSTL_OS_IS_MACOSX)

        return 1;
#else

# error Operating system not currently supported
#endif
    }
/// @}

/// \name Fields
/// @{
private:
    buffer_type_    m_pids;
/// @}
};


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

inline
pid_sequence::pid_sequence(us_uint32_t flags)
    : m_pids(buffer_type_::internal_size())
{
#if 0
#elif defined(UNIXSTL_OS_IS_LINUX)

    DIR* const dir = traits_type_::open_dir("/proc");

    if (NULL == dir)
    {
        int const e = errno;

        char const* const message = "could not open '/proc'";

        switch (e)
        {
        case EACCES:
# ifdef EPERM
        case EPERM:
# endif // EPERM

            STLSOFT_THROW_X(access_exception(message, e));

        case ENOENT:
# ifdef ENOTDIR
        case ENOTDIR:
# endif // ENOTDIR

            STLSOFT_THROW_X(file_not_found_exception(message, e));

        default:

            STLSOFT_THROW_X(filesystem_exception(message, e));
        }
    }
    else
    {
        stlsoft::scoped_handle<DIR*> scoper_dir(dir, traits_type_::close_dir);

        size_type n = 0;

        for (struct dirent const* de; NULL != (de = traits_type_::read_dir(dir)); )
        {
            int const pid = atoi(de->d_name);

            if (0 == pid)
            {
                continue;
            }

            if (n == m_pids.size())
            {
                if (!m_pids.resize(2 * m_pids.size()))
                {
                    break;
                }
            }

            m_pids[n] = pid;

            ++n;
        }

        m_pids.resize(n);
    }
#elif defined(UNIXSTL_OS_IS_MACOSX)

    for (;;)
    {
        int const n = proc_listallpids(&m_pids[0], m_pids.size() * sizeof(value_type));

        if (n < 1)
        {
            break;
        }
        else
        {
            if (n < (int)m_pids.size())
            {
                m_pids.resize((size_t)n);

                break;
            }
            else
            {
                if (!m_pids.resize(2 * m_pids.size()))
                {
                    break;
                }
            }
        }
    }
#else

# error Operating system not currently supported
#endif

    if (flags & (elideInit | elideSched))
    {
        if (flags & elideInit)
        {
            value_type* pInit = STLSOFT_NS_QUAL_STD(find)(m_pids.begin(), m_pids.end(), initProcessId());

            if (m_pids.end() != pInit)
            {
                /* size() - 1 must not underflow: an empty buffer would
                 * turn resize() into an enormous allocation request and
                 * trip GCC -Walloc-size-larger-than= (as -Werror).
                 */
                size_type const size = m_pids.size();

                if (0 != size)
                {
                    std_swap(*pInit, m_pids[size - 1]);
                    m_pids.resize(size - 1);
                }
            }
        }

        if (flags & elideSched)
        {
            value_type* pSched = STLSOFT_NS_QUAL_STD(find)(m_pids.begin(), m_pids.end(), schedProcessId());

            if (m_pids.end() != pSched)
            {
                size_type const size = m_pids.size();

                if (0 != size)
                {
                    std_swap(*pSched, m_pids[size - 1]);
                    m_pids.resize(size - 1);
                }
            }
        }
    }

    if (flags & sort)
    {
        STLSOFT_NS_QUAL_STD(sort)(m_pids.begin(), m_pids.end());
    }
}

inline
pid_sequence::pid_sequence(pid_sequence const& rhs)
    : m_pids(rhs.m_pids.size())
{
    STLSOFT_NS_QUAL_STD(copy)(rhs.m_pids.begin(), rhs.m_pids.end(), m_pids.begin());
}

inline
pid_sequence::~pid_sequence() STLSOFT_NOEXCEPT
{}

inline
pid_sequence::const_iterator
pid_sequence::cbegin() const
{
    return &*m_pids.begin();
}

inline
pid_sequence::const_iterator
pid_sequence::cend() const
{
    return &*m_pids.end();
}

inline
pid_sequence::const_iterator
pid_sequence::begin() const
{
    return cbegin();
}

inline
pid_sequence::const_iterator
pid_sequence::end() const
{
    return cend();
}

#if defined(STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT)

inline
pid_sequence::const_reverse_iterator
pid_sequence::rbegin() const
{
    return const_reverse_iterator(end());
}

inline
pid_sequence::const_reverse_iterator
pid_sequence::rend() const
{
    return const_reverse_iterator(begin());
}
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */

inline
pid_sequence::const_reference
pid_sequence::operator [](pid_sequence::size_type index) const
{
    UNIXSTL_MESSAGE_ASSERT("Index out of range", index < size());

    return m_pids[index];
}

inline
us_bool_t
pid_sequence::empty() const STLSOFT_NOEXCEPT
{
    return m_pids.empty();
}

inline
pid_sequence::size_type
pid_sequence::size() const STLSOFT_NOEXCEPT
{
    return m_pids.size();
}
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef UNIXSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
} // namespace unixstl
# else
} // namespace unixstl_project
} // namespace stlsoft
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !UNIXSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !UNIXSTL_INCL_UNIXSTL_SYSTEM_HPP_PID_SEQUENCE */

/* ///////////////////////////// end of file //////////////////////////// */

