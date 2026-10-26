/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/containers/unicode_point_map.hpp
 *
 * Purpose: A container that measures the frequencies of the unique Unicode
 *          character points it contains.
 *
 * Created: 5th November 2024
 * Updated: 26th October 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2024-2026, Matthew Wilson and Synesis Information Systems
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


/** \file stlsoft/containers/unicode_point_map.hpp
 *
 * \brief [C++] Definition of the stlsoft::unicode_point_map container class
 *   template
 *   (\ref group__library__Container "Container" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_CONTAINERS_HPP_UNICODE_POINT_MAP
#define STLSOFT_INCL_STLSOFT_CONTAINERS_HPP_UNICODE_POINT_MAP

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_CONTAINERS_HPP_UNICODE_POINT_MAP_MAJOR     1
# define STLSOFT_VER_STLSOFT_CONTAINERS_HPP_UNICODE_POINT_MAP_MINOR     1
# define STLSOFT_VER_STLSOFT_CONTAINERS_HPP_UNICODE_POINT_MAP_REVISION  1
# define STLSOFT_VER_STLSOFT_CONTAINERS_HPP_UNICODE_POINT_MAP_EDIT      6
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

#ifndef STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER
# include <stlsoft/memory/auto_buffer.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER */
#ifndef STLSOFT_INCL_STLSOFT_ALGORITHMS_HPP_POD
# include <stlsoft/algorithms/pod.hpp>          // for pod_copy_n(), etc.
#endif /* !STLSOFT_INCL_STLSOFT_ALGORITHMS_HPP_POD */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_STD_HPP_ITERATOR_GENERATORS
# include <stlsoft/util/std/iterator_generators.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_STD_HPP_ITERATOR_GENERATORS */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_HPP_STD_SWAP
# include <stlsoft/util/std_swap.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_HPP_STD_SWAP */

#if __cplusplus >= 201103L
# ifndef STLSOFT_INCL_INITIALIZER_LIST
#  define STLSOFT_INCL_INITIALIZER_LIST
#  include <initializer_list>
# endif /* !STLSOFT_INCL_INITIALIZER_LIST */
# ifndef STLSOFT_INCL_UNORDERED_MAP
#  define STLSOFT_INCL_UNORDERED_MAP
#  include <unordered_map>
# endif /* !STLSOFT_INCL_UNORDERED_MAP */
#else
# ifndef STLSOFT_INCL_MAP
#  define STLSOFT_INCL_MAP
#  include <map>
# endif /* !STLSOFT_INCL_MAP */
#endif
#include <utility>


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

/** A container that measures the frequencies of the unique Unicode
 *  character points it contains.
 *
 * \ingroup group__library__Container
 */
class unicode_point_map
{
public: // types
#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

    typedef unicode_point_map                               collection_type;
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */
    /// This type
    typedef unicode_point_map                               class_type;
    /// The char type
    typedef char                                            char_type;
    //// The unicode-point type
    typedef ss_uint32_t                                     unicode_point_type;
    /// The count type
    typedef ss_sint64_t                                     count_type;
    /// The size type
    typedef ss_size_t                                       size_type;
    /// The key type
    struct                                                  key_type;
    /// The value type
    typedef std::pair<
        unicode_point_type
    ,   count_type
    >                                                       value_type;
private:
    typedef auto_buffer<
        count_type
    >                                                       vec_type_;
#if __cplusplus >= 201103L
    typedef std::unordered_map<
        unicode_point_type
    ,   count_type
    >                                                       map_type_;
#else
    typedef std::map<
        unicode_point_type
    ,   count_type
    >                                                       map_type_;
#endif
public:
    /// The iterator type
    class const_iterator;

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

    struct key_type
    {
    public: // construction
        key_type(char_type c)
        {
            union
            {
                char c;
                ss_uint8_t u8;
                ss_uint32_t u32;
            } u;

            u.u32 = 0;
            u.c = c;

            STLSOFT_MESSAGE_ASSERT("`c` may not contain a non-ASCII value", 0 == (u.u32 & 0xFFFFFF80));

            this->key = u.u32;
        }
        key_type(unicode_point_type upt)
        {
            this->key = upt;
        }
    private:
        template <ss_typename_param_k T_unacceptable>
        ss_explicit_k
        key_type(T_unacceptable const&)
# if __cplusplus >= 201103L
         = delete
# endif
        ;

    public: // fields
        unicode_point_type  key;
    };

    class const_iterator
        : public STLSOFT_NS_QUAL(iterator_base)<
                STLSOFT_NS_QUAL_STD(input_iterator_tag)
            ,   value_type
            ,   ss_ptrdiff_t
            ,   void        // By-Value Temporary reference
            ,   value_type  // By-Value Temporary reference
            >
    {
        friend class unicode_point_map;

    public: // types
        typedef const_iterator                                  class_type;

    private: // construction
        ss_explicit_k
        const_iterator(
            collection_type const& collection
        );
    public:
        const_iterator();
        const_iterator(class_type const& rhs);
        class_type& operator =(class_type const& rhs);

    public: // operators
        value_type
        operator *() const STLSOFT_NOEXCEPT;

        bool
        operator ==(class_type const& rhs) const STLSOFT_NOEXCEPT;
        bool
        operator !=(class_type const& rhs) const STLSOFT_NOEXCEPT;

        const_iterator&
        operator ++();
        const_iterator
        operator ++(int);

    private: // implementation
        bool
        is_at_end() const STLSOFT_NOEXCEPT;

    private: // fields
        collection_type const*      m_collection;
        vec_type_::const_iterator   m_vec_iter;
        map_type_::const_iterator   m_map_iter;
    };
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


public: // construction
    /// Constructs an empty instance
    unicode_point_map();
    /// Constructs an empty instance with the requisite extent of contiguous
    /// storage
    ss_explicit_k
    unicode_point_map(
        unicode_point_type default_contiguous_ceiling
    );
#if __cplusplus >= 201103L
    unicode_point_map(
        std::initializer_list<key_type> init_list
    );
    unicode_point_map(
        unicode_point_type              default_contiguous_ceiling
    ,   std::initializer_list<key_type> init_list
    );
#endif


public: // operations
    void
    clear() STLSOFT_NOEXCEPT;

#if 0 // TODO: implement these methods in next version

    class_type&
    merge(class_type const& rhs);

    class_type&
    operator +=(class_type const& rhs);
#endif

    void
    push(key_type key);

    count_type
    push_n(
        key_type    key
    ,   count_type  count
    );

    void
    swap(class_type& rhs) STLSOFT_NOEXCEPT;


public: // lookup
    bool
    contains(key_type c) const;

    count_type
    count(key_type key) const;

    const_iterator
    find(key_type c) const;

    count_type
    operator [](key_type key) const;


public: // attributes
    bool
    empty() const STLSOFT_NOEXCEPT;

    size_type
    size() const STLSOFT_NOEXCEPT;

    count_type
    total() const STLSOFT_NOEXCEPT;


public: // iteration
    const_iterator
    begin() const;

    const_iterator
    end() const;

    const_iterator
    cbegin() const;

    const_iterator
    cend() const;


private: // implementation


private: // fields
    size_type   m_len;
    count_type  m_total;
    vec_type_   m_vec;
    map_type_   m_map;
};


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION


// //// unicode_point_map::const_iterator

// construction

inline
/* ss_explicit_k */
unicode_point_map::const_iterator::const_iterator(
    collection_type const& collection
)
    : m_collection(&collection)
    , m_vec_iter(collection.m_vec.begin())
    , m_map_iter(collection.m_map.begin())
{
    // advance to first non-zero element in vec

    for (; collection.m_vec.end() != m_vec_iter; ++m_vec_iter)
    {
        if (0 != *m_vec_iter)
        {
            break;
        }
    }
}

inline
unicode_point_map::const_iterator::const_iterator()
    : m_collection(NULL)
    , m_vec_iter()
    , m_map_iter()
{}

inline
unicode_point_map::const_iterator::const_iterator(class_type const& rhs)
    : m_collection(rhs.m_collection)
    , m_vec_iter(rhs.m_vec_iter)
    , m_map_iter(rhs.m_map_iter)
{}

inline
unicode_point_map::const_iterator&
unicode_point_map::const_iterator::operator =(class_type const& rhs)
{
    m_collection = rhs.m_collection;
    m_vec_iter = rhs.m_vec_iter;
    m_map_iter = rhs.m_map_iter;

    return *this;
}


// operators

inline
unicode_point_map::const_iterator::value_type
unicode_point_map::const_iterator::operator *() const STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(!is_at_end());

    if (m_vec_iter != m_collection->m_vec.end())
    {
        return std::make_pair(static_cast<unicode_point_type>(std::distance(m_collection->m_vec.begin(), m_vec_iter)), *m_vec_iter);
    }
    else
    {
        return *m_map_iter;
    }
}

inline
bool
unicode_point_map::const_iterator::operator ==(class_type const& rhs) const STLSOFT_NOEXCEPT
{
    STLSOFT_MESSAGE_ASSERT("cannot compare iterators from different containers", NULL == m_collection || NULL == rhs.m_collection || m_collection == rhs.m_collection);

    if (is_at_end())
    {
        if (rhs.is_at_end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (rhs.is_at_end())
        {
            return false;
        }
        else
        {
            if (m_vec_iter != rhs.m_vec_iter)
            {
                return false;
            }

            if (m_map_iter != rhs.m_map_iter)
            {
                return false;
            }

            return true;
        }
    }
}

inline
bool
unicode_point_map::const_iterator::operator !=(class_type const& rhs) const STLSOFT_NOEXCEPT
{
    return !operator ==(rhs);
}

inline
unicode_point_map::const_iterator&
unicode_point_map::const_iterator::operator ++()
{
    STLSOFT_ASSERT(!is_at_end());

    if (m_vec_iter != m_collection->m_vec.end())
    {
        while (m_vec_iter != m_collection->m_vec.end())
        {
            if (0 != *++m_vec_iter)
            {
                break;
            }
        }
    }
    else
    {
        ++m_map_iter;
    }

    return *this;
}

inline
unicode_point_map::const_iterator
unicode_point_map::const_iterator::operator ++(int)
{
    class_type  r(*this);

    operator ++();

    return r;
}

// implementation

inline
bool
unicode_point_map::const_iterator::is_at_end() const STLSOFT_NOEXCEPT
{
    if (NULL == m_collection)
    {
        return true;
    }

    if (m_vec_iter != m_collection->m_vec.end())
    {
        return false;
    }

    if (m_map_iter != m_collection->m_map.end())
    {
        return false;
    }

    return true;
}


// //// unicode_point_map

// construction

inline
unicode_point_map::unicode_point_map()
    : m_len(0)
    , m_total(0)
    , m_vec(0)
    , m_map()
{}

inline
unicode_point_map::unicode_point_map(
    unicode_point_type default_contiguous_ceiling
)
    : m_len(0)
    , m_total(0)
    , m_vec(default_contiguous_ceiling, 0)
    , m_map()
{}

#if __cplusplus >= 201103L

inline
unicode_point_map::unicode_point_map(
    std::initializer_list<key_type> init_list
)
    : m_len(0)
    , m_total(0)
    , m_vec(0)
    , m_map()
{
    for (auto k : init_list)
    {
        push(k);
    }
}

inline
unicode_point_map::unicode_point_map(
    unicode_point_type              default_contiguous_ceiling
,   std::initializer_list<key_type> init_list
)
    : m_len(0)
    , m_total(0)
    , m_vec(default_contiguous_ceiling, 0)
    , m_map()
{
    for (auto k : init_list)
    {
        push(k);
    }
}
#endif


// operations

inline
void
unicode_point_map::clear() STLSOFT_NOEXCEPT
{
    m_len = 0;
    m_total = 0;
    pod_fill_n(m_vec.begin(), m_vec.size(), count_type());
    m_map.clear();
}

#if 0

class_type&
merge(class_type const& rhs);

class_type&
operator +=(class_type const& rhs);
#endif

inline
void
unicode_point_map::push(key_type key)
{
    push_n(key, 1);
}

inline
unicode_point_map::count_type
unicode_point_map::push_n(
    key_type    key
,   count_type  count
)
{
    if (key.key < m_vec.size())
    {
        count_type const prev = m_vec[key.key];
        count_type const curr = prev + count;

        m_vec[key.key] = curr;

        if (0 == prev)
        {
            if (0 != curr)
            {
                ++m_len;
            }
        }
        else
        {
            if (0 == curr)
            {
                --m_len;
            }
        }

        m_total += count;

        return prev;
    }
    else
    {
        map_type_::iterator it = m_map.find(key.key);

        if (m_map.end() == it)
        {
            if (0 != count)
            {
                m_map.insert(std::make_pair(key.key, count));

                ++m_len;
            }

            m_total += count;

            return 0;
        }
        else
        {
            count_type const prev = (*it).second;

            if (0 == ((*it).second += count))
            {
                m_map.erase(it);

                --m_len;
            }

            m_total += count;

            return prev;
        }
    }
}

inline
void
unicode_point_map::swap(class_type& rhs) STLSOFT_NOEXCEPT
{
    std_swap(m_len, rhs.m_len);
    std_swap(m_total, rhs.m_total);
    std_swap(m_vec, rhs.m_vec);
    std_swap(m_map, rhs.m_map);
}


// lookup

inline
bool
unicode_point_map::contains(key_type key) const
{
    if (key.key < m_vec.size())
    {
        return 0 != m_vec[key.key];
    }
    else
    {
        map_type_::const_iterator it = m_map.find(key.key);

        if (m_map.end() == it)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

inline
unicode_point_map::count_type
unicode_point_map::count(key_type key) const
{
    if (key.key < m_vec.size())
    {
        return m_vec[key.key];
    }
    else
    {
        map_type_::const_iterator it = m_map.find(key.key);

        if (m_map.end() == it)
        {
            return 0;
        }
        else
        {
            return (*it).second;
        }
    }
}

#if 0
    const_iterator
    find(key_type c) const;
#endif

inline
unicode_point_map::count_type
unicode_point_map::operator [](key_type key) const
{
    return count(key);
}

// attributes

inline
bool
unicode_point_map::empty() const STLSOFT_NOEXCEPT
{
    return 0 == m_len;
}

inline
unicode_point_map::size_type
unicode_point_map::size() const STLSOFT_NOEXCEPT
{
    return m_len;
}

inline
unicode_point_map::count_type
unicode_point_map::total() const STLSOFT_NOEXCEPT
{
    return m_total;
}


// iteration

inline
unicode_point_map::const_iterator
unicode_point_map::begin() const
{
    return cbegin();
}

inline
unicode_point_map::const_iterator
unicode_point_map::end() const
{
    return cend();
}

inline
unicode_point_map::const_iterator
unicode_point_map::cbegin() const
{
    return const_iterator(*this);
}

inline
unicode_point_map::const_iterator
unicode_point_map::cend() const
{
    return const_iterator();
}
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */

#if !defined(STLSOFT_COMPILER_IS_WATCOM)

inline
void
swap(
    unicode_point_map& lhs
,   unicode_point_map& rhs
)
{
    lhs.swap(rhs);
}
#endif /* compiler */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} // namespace stlsoft
#endif /* STLSOFT_NO_NAMESPACE */

#if defined(STLSOFT_CF_std_NAMESPACE)
namespace std
{

# ifdef STLSOFT_ALLOW_std_swap_SPECIALISATIONS

    inline
    void
    swap(
        STLSOFT_NS_QUAL(unicode_point_map)& lhs
    ,   STLSOFT_NS_QUAL(unicode_point_map)& rhs
    )
    {
        lhs.swap(rhs);
    }
# endif
} // namespace std
#endif /* STLSOFT_CF_std_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_CONTAINERS_HPP_UNICODE_POINT_MAP */

/* ///////////////////////////// end of file //////////////////////////// */

