/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/string/simple_string.hpp (originally MSString.h, ::SynesisDev)
 *
 * Purpose: basic_simple_string class template.
 *
 * Created: 19th March 1993
 * Updated: 31st July 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2025, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 1993-2019, Matthew Wilson and Synesis Software
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


/** \file stlsoft/string/simple_string.hpp
 *
 * \brief [C++] Definition of the stlsoft::basic_simple_string class
 *  template
 *   (\ref group__library__String "String" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_STRING_HPP_SIMPLE_STRING
#define STLSOFT_INCL_STLSOFT_STRING_HPP_SIMPLE_STRING

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_STRING_HPP_SIMPLE_STRING_MAJOR     4
# define STLSOFT_VER_STLSOFT_STRING_HPP_SIMPLE_STRING_MINOR     8
# define STLSOFT_VER_STLSOFT_STRING_HPP_SIMPLE_STRING_REVISION  4
# define STLSOFT_VER_STLSOFT_STRING_HPP_SIMPLE_STRING_EDIT      285
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

#ifndef STLSOFT_INCL_STLSOFT_STRING_HPP_CHAR_TRAITS
# include <stlsoft/string/char_traits.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_CHAR_TRAITS */
#ifndef STLSOFT_INCL_STLSOFT_STRING_HPP_STRING_TRAITS_FWD
# include <stlsoft/string/string_traits_fwd.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_STRING_TRAITS_FWD */
#ifndef STLSOFT_INCL_STLSOFT_COLLECTIONS_UTIL_HPP_COLLECTIONS
# include <stlsoft/collections/util/collections.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_COLLECTIONS_UTIL_HPP_COLLECTIONS */
#ifndef STLSOFT_INCL_STLSOFT_MEMORY_HPP_ALLOCATOR_BASE
# include <stlsoft/memory/allocator_base.hpp>       // for STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_HPP_ALLOCATOR_BASE */
#ifndef STLSOFT_INCL_STLSOFT_MEMORY_UTIL_HPP_ALLOCATOR_SELECTOR
# include <stlsoft/memory/util/allocator_selector.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_UTIL_HPP_ALLOCATOR_SELECTOR */
#ifndef STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER
# include <stlsoft/memory/auto_buffer.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_HPP_STD_SWAP
# include <stlsoft/util/std_swap.hpp>       // for stlsoft::std_swap()
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_HPP_STD_SWAP */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_STD_HPP_ITERATOR_GENERATORS
# include <stlsoft/util/std/iterator_generators.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_STD_HPP_ITERATOR_GENERATORS */
#ifndef STLSOFT_INCL_STLSOFT_ALGORITHMS_HPP_BOUNDED
# include <stlsoft/algorithms/bounded.hpp>  // for stlsoft::copy_n()
#endif /* !STLSOFT_INCL_STLSOFT_ALGORITHMS_HPP_BOUNDED */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_HPP_MINMAX
# include <stlsoft/util/minmax.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_HPP_MINMAX */
#ifndef STLSOFT_INCL_STLSOFT_CONVERSION_HPP_SAP_CAST
# include <stlsoft/conversion/sap_cast.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_CONVERSION_HPP_SAP_CAST */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_STD_HPP_ITERATOR_HELPER
# include <stlsoft/util/std/iterator_helper.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_STD_HPP_ITERATOR_HELPER */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_STREAMS_HPP_STRING_INSERTION
# include <stlsoft/util/streams/string_insertion.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_STREAMS_HPP_STRING_INSERTION */

#if defined(__BORLANDC__) && \
    __BORLANDC__ > 0x0580 && \
    defined(STLSOFT_DEBUG)
# include <stdio.h>
#endif /* compiler */

#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
# include <stdexcept>                       // for std::out_of_range
#endif /* !STLSOFT_CF_EXCEPTION_SUPPORT */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_memfns
# include <stlsoft/api/external/memfns.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_memfns */


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if defined(STLSOFT_COMPILER_IS_MSVC) && \
    _MSC_VER < 1200
# define STLSOFT_SIMPLE_STRING_ITERATOR_METHODS_INLINE
#endif /* compiler */


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

/** Simple string class
 *
 * \param C The character type
 * \param T The traits type. On translators that support default template arguments this is defaulted to char_traits<C>
 * \param A The allocator type. On translators that support default template arguments this is defaulted to allocator_selector<C>::allocator_type
 *
 * \ingroup group__library__String
 */
template<
    ss_typename_param_k C
#ifdef STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT
,   ss_typename_param_k T = stlsoft_char_traits<C>
,   ss_typename_param_k A = ss_typename_type_def_k allocator_selector<C>::allocator_type
#else /* ? STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT */
,   ss_typename_param_k T /* = stlsoft_char_traits<C> */
,   ss_typename_param_k A /* = allocator_selector<C>::allocator_type */
#endif /* STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT */
>
// class basic_simple_string
class basic_simple_string
    : public stl_collection_tag
{
/// \name Member Types
/// @{
public:
    /// The value type
    typedef C                                               value_type;
    /// The traits type
    typedef T                                               traits_type;
    /// The allocator type
    typedef A                                               allocator_type;
    /// The current specialisation of the type
    typedef basic_simple_string<
        C
    ,   T
    ,   A
    >                                                       class_type;
    /// The character type
    typedef value_type                                      char_type;
    /// The pointer type
    typedef value_type*                                     pointer;
    /// The non-mutable (const) pointer type
    typedef value_type const*                               const_pointer;
    /// The reference type
    typedef value_type&                                     reference;
    /// The non-mutable (const) reference type
    typedef value_type const&                               const_reference;
    /// The size type
    typedef ss_size_t                                       size_type;
    /// The difference type
    typedef ss_ptrdiff_t                                    difference_type;
    /// The iterator type
    typedef
#if !defined(STLSOFT_COMPILER_IS_BORLAND)
           ss_typename_type_k
#endif /* compiler */
                       pointer_iterator<
        value_type
    ,   pointer
    ,   reference
    >::type                                                 iterator;
    /// The non-mutating (const) iterator type
    typedef
#if !defined(STLSOFT_COMPILER_IS_BORLAND)
         ss_typename_type_k
#endif /* compiler */
                       pointer_iterator<
        value_type const
    ,   const_pointer
    ,   const_reference
    >::type                                                 const_iterator;
#if defined(STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT)

    /// The mutating (non-const) reverse iterator type
    typedef ss_typename_type_k reverse_iterator_generator<
        iterator
    ,   value_type
    ,   reference
    ,   pointer
    ,   difference_type
    >::type                                                 reverse_iterator;
    /// The non-mutating (const) reverse iterator type
    typedef ss_typename_type_k const_reverse_iterator_generator<
        const_iterator
    ,   value_type
    ,   const_reference
    ,   const_pointer
    ,   difference_type
    >::type                                                 const_reverse_iterator;
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */
private:
    /// The allocator type for allocating bytes
    ///
    /// \note This has to be defined here, rather than on a use-by-use basis, because
    /// Borland gets very upset.
#ifdef STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT

    typedef ss_typename_type_k A::ss_template_qual_k rebind<
        ss_byte_t
    >::other                                                byte_ator_type;
#else /* ? STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */

    typedef ss_typename_type_k allocator_selector<
        ss_byte_t
    >::allocator_type                                       byte_ator_type;
#endif /* STLSOFT_LF_ALLOCATOR_REBIND_SUPPORT */
/// @}

/// \name Construction
/// @{
public:
    /// Default constructor
    ss_constexpr_2014_k
    basic_simple_string() STLSOFT_NOEXCEPT;
    /// Copy constructor
    basic_simple_string(class_type const& rhs);
    /// Construct from the given string at the specified position
    basic_simple_string(class_type const& s, size_type pos);
    /// Construct with \c cch characters from the given string at the specified position
    basic_simple_string(class_type const& s, size_type pos, size_type cch);
    /// Construct from the given character string
    basic_simple_string(char_type const* s); // Not, not explicit. Sigh
    /// Construct with \c cch characters from the given character string
    basic_simple_string(char_type const* s, size_type cch);
    /// Construct with \c cch characters each set to \c ch
    basic_simple_string(size_type cch, char_type ch);
    /// Construct from the range [first:last)
#if !defined(STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT)
    basic_simple_string(char_type const* first, char_type const* last);
#else /* ? STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */
    template <ss_typename_param_k II>
    basic_simple_string(II first, II last)
        : m_buffer(ss_nullptr_k)
    {
        assign(first, last);
    }
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

#ifdef STLSOFT_CF_RVALUE_REFERENCES_SUPPORT

    /// Transfers the contents of the instance \c rhs
    basic_simple_string(class_type&& rhs) STLSOFT_NOEXCEPT;
#endif /* STLSOFT_CF_RVALUE_REFERENCES_SUPPORT */

    /// Destructor
    ss_constexpr_2020_k
    ~basic_simple_string() STLSOFT_NOEXCEPT;
/// @}

/// \name Assignment
/// @{
public:
    /// Assigns from the given character string
    class_type& assign(char_type const* s);
    /// Assigns with \c cch characters from the given character string
    class_type& assign(char_type const* s, size_type cch);
    /// Assigns with \c cch characters from the given character string at the specified position
    class_type& assign(class_type const& str, size_type pos, size_type cch);
    /// Assigns from the given string
    class_type& assign(class_type const& str);
    /// Assigns \c cch characters with the value \c ch
    class_type& assign(size_type cch, char_type ch);
    /// Assigns from the range [first:last)
#if !defined(STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT)
    class_type& assign(const_iterator first, const_iterator last);
#else /* ? STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */
    template <ss_typename_param_k II>
    class_type& assign(II first, II last)
    {
# if (  defined(STLSOFT_COMPILER_IS_GCC) && \
        __GNUC__ < 3) || \
     (  defined(STLSOFT_COMPILER_IS_BORLAND) && \
        defined(STLSOFT_CF_STD_LIBRARY_IS_DINKUMWARE_BORLAND))
        typedef ss_typename_type_k std::iterator_traits<II> traits_t;

        return assign_(first, last, traits_t::iterator_category());
# elif defined(STLSOFT_COMPILER_IS_MWERKS) || \
       defined(STLSOFT_COMPILER_IS_DMC)
        return assign_(first, last, stlsoft_iterator_query_category_ptr(II, first));
# else /* ? compiler */
        return assign_(first, last, stlsoft_iterator_query_category(II, first));
# endif /* compiler */
    }
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

    /// Copy assignment operator
    class_type const& operator =(class_type const& rhs);
    /// Assignment operator
    class_type const& operator =(char_type const* s);
    /// Assignment operator
    class_type const& operator =(char_type ch);
/// @}

/// \name Appending
/// @{
public:
    /// Appends the given character string
    class_type& append(char_type const* s);
    /// Appends \c cch characters from the given character string
    class_type& append(char_type const* s, size_type cch);
    /// Assigns \c cch characters from the given character string at the specified position
    class_type& append(class_type const& str, size_type pos, size_type cch);
    /// Appends the given string
    class_type& append(class_type const& str);
    /// Appends \c cch characters with the value \c ch
    class_type& append(size_type cch, char_type ch);
    /// Appends the range [first:last)
#if !defined(STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT)
    class_type& append(const_iterator first, const_iterator last);
#else /* ? STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */
    template <ss_typename_param_k II>
    class_type& append(II first, II last)
    {
# if (  defined(STLSOFT_COMPILER_IS_GCC) && \
        __GNUC__ < 3) || \
     (  defined(STLSOFT_COMPILER_IS_BORLAND) && \
        defined(STLSOFT_CF_STD_LIBRARY_IS_DINKUMWARE_BORLAND))
        typedef ss_typename_type_k std::iterator_traits<II> traits_t;

        return append_(first, last, traits_t::iterator_category());
# elif defined(STLSOFT_COMPILER_IS_MWERKS) || \
       defined(STLSOFT_COMPILER_IS_DMC)
        return append_(first, last, stlsoft_iterator_query_category_ptr(II, first));
# else /* ? compiler */
        return append_(first, last, stlsoft_iterator_query_category(II, first));
# endif /* compiler */
    }
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

    /// Concatenation operator
    class_type& operator +=(char_type ch);
    /// Concatenation operator
    class_type& operator +=(char_type const* s);
    /// Concatenation operator
    class_type& operator +=(class_type const& rhs);

    /// Appends a single character
    void push_back(char_type ch);
    /// Removes the last character
    void pop_back() STLSOFT_NOEXCEPT;
/// @}

/// \name Modifiers
/// @{
public:
    /// Reserves at least cch characters
    void reserve(size_type cch);
    /// Swaps the contents between \c this and \c other
    void swap(class_type& other) STLSOFT_NOEXCEPT;

    /// Resizes the string
    ///
    /// \param cch The new size of the string
    /// \param ch The value with which to initialise additional items if the string is expanded
    void resize(size_type cch, value_type ch = value_type());

    /// Empties the string
    void clear() STLSOFT_NOEXCEPT;
/// @}

/// \name Attributes
/// @{
public:
    /// The number of elements in the string
    size_type size() const STLSOFT_NOEXCEPT;
    /// The maximum number of elements that can be stored in the string
    size_type max_size() const STLSOFT_NOEXCEPT;
    /// The number of elements in the string
    size_type length() const STLSOFT_NOEXCEPT;
    /// The storage currently allocated by the string
    size_type capacity() const STLSOFT_NOEXCEPT;
    /// Indicates whether the string is empty
    ss_bool_t empty() const STLSOFT_NOEXCEPT;
/// @}

/// \name Comparison
/// @{
public:
    /// Equates the substring [pos, pos+cch) of \c this with the substring [0, cchRhs) of the given C-style string \c s
    ss_bool_t equal(size_type pos, size_type cch, value_type const* s, size_type cchRhs) const STLSOFT_NOEXCEPT;
    /// Equates the substring [pos, pos+cch) of \c this with the given C-style string \c s
    ss_bool_t equal(size_type pos, size_type cch, value_type const* s) const STLSOFT_NOEXCEPT;
    /// Equates \c this with the given C-style string \c s
    ss_bool_t equal(value_type const* s) const STLSOFT_NOEXCEPT;
    /// Equates the substring [pos, pos+cch) of \c this with the substring [posRhs, posRhs+cchRhs) of the given string \c rhs
    ss_bool_t equal(size_type pos, size_type cch, class_type const& rhs, size_type posRhs, size_type cchRhs) const STLSOFT_NOEXCEPT;
    /// Equates the substring [pos, pos+cch) of \c this with the given string
    ss_bool_t equal(size_type pos, size_type cch, class_type const& rhs) const STLSOFT_NOEXCEPT;
    /// Equates \c this with the given string \c rhs
    ss_bool_t equal(class_type const& rhs) const STLSOFT_NOEXCEPT;

    /// Compares the substring [pos, pos+cch) of \c this with the substring [0, cchRhs) of the given C-style string \c s
    ss_sint_t compare(size_type pos, size_type cch, value_type const* s, size_type cchRhs) const STLSOFT_NOEXCEPT;
    /// Compares the substring [pos, pos+cch) of \c this with the given C-style string \c s
    ss_sint_t compare(size_type pos, size_type cch, value_type const* s) const STLSOFT_NOEXCEPT;
    /// Compares \c this with the given C-style string \c s
    ss_sint_t compare(value_type const* s) const STLSOFT_NOEXCEPT;
    /// Compares the substring [pos, pos+cch) of \c this with the substring [posRhs, posRhs+cchRhs) of the given string \c rhs
    ss_sint_t compare(size_type pos, size_type cch, class_type const& rhs, size_type posRhs, size_type cchRhs) const STLSOFT_NOEXCEPT;
    /// Compares the substring [pos, pos+cch) of \c this with the given string \c rhs
    ss_sint_t compare(size_type pos, size_type cch, class_type const& rhs) const STLSOFT_NOEXCEPT;
    /// Compares \c this with the given string \c rhs
    ss_sint_t compare(class_type const& rhs) const STLSOFT_NOEXCEPT;

    /// Indicates whether the string contains the string \c s
    bool contains(class_type const& s) const STLSOFT_NOEXCEPT;
    /// Indicates whether the string contains the C-style string \c s
    bool contains(char_type const* s) const STLSOFT_NOEXCEPT;
    /// Indicates whether the string contains the character \c ch
    bool contains(char_type ch) const STLSOFT_NOEXCEPT;

    /// Indicates whether the string starts with the string \c s
    bool starts_with(class_type const& s) const STLSOFT_NOEXCEPT;
    /// Indicates whether the string starts with the C-style string \c s
    bool starts_with(char_type const* s) const STLSOFT_NOEXCEPT;
    /// Indicates whether the string starts with the character \c ch
    bool starts_with(char_type ch) const STLSOFT_NOEXCEPT;

    /// Indicates whether the string ends with the string \c s
    bool ends_with(class_type const& s) const STLSOFT_NOEXCEPT;
    /// Indicates whether the string ends with the C-style string \c s
    bool ends_with(char_type const* s) const STLSOFT_NOEXCEPT;
    /// Indicates whether the string ends with the character \c ch
    bool ends_with(char_type ch) const STLSOFT_NOEXCEPT;
/// @}

/// \name Accessors
/// @{
public:
    /// Returns mutable reference at the given index
    reference       operator [](size_type index) STLSOFT_NOEXCEPT;
    /// Returns non-mutable (const) reference at the given index
    const_reference operator [](size_type index) const STLSOFT_NOEXCEPT;

#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    /// Returns mutable (non-const) reference at the given index
    ///
    /// \note Throws std::out_of_range if index >= size()
    reference               at(size_type index);
    /// Returns non-mutable (const) reference at the given index
    ///
    /// \note Throws std::out_of_range if index >= size()
    const_reference         at(size_type index) const;

    /// Returns a string of maximum length cch, from the position pos
    class_type              substr(size_type pos, size_type cch) const;
    class_type              substr(size_type pos) const;
    class_type              substr() const;
#endif /* !STLSOFT_CF_EXCEPTION_SUPPORT */

    /// Returns null-terminated non-mutable (const) pointer to string data
    value_type const*       c_str() const STLSOFT_NOEXCEPT;
    /// Returns non-mutable (const) pointer to string data
    value_type const*       data() const STLSOFT_NOEXCEPT;

    /// Returns the first character in the string
    ///
    /// \note It is us to the user to ensure that the string is not empty
    reference               front() STLSOFT_NOEXCEPT;
    /// Returns the last character in the string
    ///
    /// \note It is us to the user to ensure that the string is not empty
    reference               back() STLSOFT_NOEXCEPT;
    /// Returns the first character in the string
    ///
    /// \note It is us to the user to ensure that the string is not empty
    const_reference         front() const STLSOFT_NOEXCEPT;
    /// Returns the last character in the string
    ///
    /// \note It is us to the user to ensure that the string is not empty
    const_reference         back() const STLSOFT_NOEXCEPT;

    /// Copies elements into the given destination
    size_type copy(
        value_type* dest
    ,   size_type   cch
    ,   size_type   pos = 0
    ) const STLSOFT_NOEXCEPT;
/// @}

/// \name Iteration
/// @{
public:
    /// Begins the iteration
    ///
    /// \return A non-mutable (const) iterator representing the start of the sequence
#ifdef STLSOFT_SIMPLE_STRING_ITERATOR_METHODS_INLINE
    const_iterator          begin() const STLSOFT_NOEXCEPT
    {
        return const_cast<class_type*>(this)->begin_();
    }
#else /* ? STLSOFT_SIMPLE_STRING_ITERATOR_METHODS_INLINE */
    const_iterator          begin() const STLSOFT_NOEXCEPT;
#endif /* STLSOFT_SIMPLE_STRING_ITERATOR_METHODS_INLINE */
    /// Ends the iteration
    ///
    /// \return A non-mutable (const) iterator representing the end of the sequence
#ifdef STLSOFT_SIMPLE_STRING_ITERATOR_METHODS_INLINE
    const_iterator          end() const STLSOFT_NOEXCEPT
    {
        return const_cast<class_type*>(this)->end_();
    }
#else /* ? STLSOFT_SIMPLE_STRING_ITERATOR_METHODS_INLINE */
    const_iterator          end() const STLSOFT_NOEXCEPT;
#endif /* STLSOFT_SIMPLE_STRING_ITERATOR_METHODS_INLINE */
    /// Begins the iteration
    ///
    /// \return An iterator representing the start of the sequence
    iterator                begin() STLSOFT_NOEXCEPT;
    /// Ends the iteration
    ///
    /// \return An iterator representing the end of the sequence
    iterator                end() STLSOFT_NOEXCEPT;

#if defined(STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT)
    /// Begins the reverse iteration
    ///
    /// \return A non-mutable (const) iterator representing the start of the reverse sequence
    const_reverse_iterator  rbegin() const STLSOFT_NOEXCEPT;
    /// Ends the reverse iteration
    ///
    /// \return A non-mutable (const) iterator representing the end of the reverse sequence
    const_reverse_iterator  rend() const STLSOFT_NOEXCEPT;
    /// Begins the reverse iteration
    ///
    /// \return An iterator representing the start of the reverse sequence
    reverse_iterator        rbegin() STLSOFT_NOEXCEPT;
    /// Ends the reverse iteration
    ///
    /// \return An iterator representing the end of the reverse sequence
    reverse_iterator        rend() STLSOFT_NOEXCEPT;
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */
/// @}

/// \name Implementation
/// @{
private:
    enum { alloc_quantum = 31 };    // Must be (2^n - 1)

    struct string_buffer
    {
        size_type   capacity;       // The number of char places in the buffer
        size_type   length;         // The number of chars in the string (<= capacity)
        char_type   contents[1];    // The first element in the array
    };

    typedef auto_buffer<
        char_type
    ,   auto_buffer_internal_size_calculator<char_type>::value
    ,   allocator_type
    >                                                       buffer_type_;

#ifdef STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST
    typedef string_buffer*                                  member_pointer;
    typedef string_buffer const*                            member_const_pointer;
#else /* ? STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST */
    typedef char_type*                                      member_pointer;
    typedef char_type const*                                member_const_pointer;
#endif /* STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST */

    // Conversion between member pointer and character pointer
    static char_type*           char_pointer_from_member_pointer_(member_pointer ) STLSOFT_NOEXCEPT;

    // Conversion between pointer and buffer
    static ss_constexpr_2014_k string_buffer*       string_buffer_from_member_pointer_(member_pointer ) STLSOFT_NOEXCEPT;
    static ss_constexpr_2014_k string_buffer const* string_buffer_from_member_pointer_(member_const_pointer ) STLSOFT_NOEXCEPT;

    // Conversion between buffer and pointer
    static member_pointer       member_pointer_from_string_buffer_(string_buffer*) STLSOFT_NOEXCEPT;

    // Creating buffer
    static member_pointer       alloc_buffer_(char_type const* s, size_type capacity, size_type length);
    static member_pointer       alloc_buffer_(char_type const* s, size_type cch);
    static member_pointer       alloc_buffer_(char_type const* s);

    // Copying a buffer
    static member_pointer       copy_buffer_(member_pointer );

    // Destroying buffer
    static void                 destroy_buffer_(string_buffer*) STLSOFT_NOEXCEPT;
    static void                 destroy_buffer_(char_type*) STLSOFT_NOEXCEPT;

    // Iteration
    pointer                     begin_() STLSOFT_NOEXCEPT;
    pointer                     end_() STLSOFT_NOEXCEPT;

    // Invariance
    ss_constexpr_2014_k
    ss_bool_t is_valid() const STLSOFT_NOEXCEPT;

    // Empty string
    static char_type const* empty_string_() STLSOFT_NOEXCEPT;

    // Comparison
    static ss_sint_t compare_(
        char_type const*    lhs
    ,   size_type           lhs_len
    ,   char_type const*    rhs
    ,   size_type           rhs_len
    ) STLSOFT_NOEXCEPT;

    // testing known-length lhs against css rhs
    static ss_bool_t equal_(
        char_type const*    lhs
    ,   size_type           lhs_len
    ,   char_type const*    rhs
    ) STLSOFT_NOEXCEPT;
    // testing same-known-length lhs and rhs
    static ss_bool_t equal_(
        char_type const*    lhs
    ,   char_type const*    rhs
    ,   size_type           len
    ) STLSOFT_NOEXCEPT;

    bool contains_(
        char_type const*    s
    ,   size_type           n
    ) const STLSOFT_NOEXCEPT;
    bool starts_with_(
        char_type const*    s
    ,   size_type           n
    ) const STLSOFT_NOEXCEPT;
    bool ends_with_(
        char_type const*    s
    ,   size_type           n
    ) const STLSOFT_NOEXCEPT;


    // Assignment
#if defined(STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT)
    template <ss_typename_param_k II>
# if defined(STLSOFT_COMPILER_IS_MWERKS) || \
     defined(STLSOFT_COMPILER_IS_DMC)
    // There seems to be a bug in CodeWarrior that makes it have a cow with iterator tags by value, so we just use a ptr
    class_type& assign_(II first, II last, STLSOFT_NS_QUAL_STD(input_iterator_tag) const*)
# else /* ? compiler */
    class_type& assign_(II first, II last, STLSOFT_NS_QUAL_STD(input_iterator_tag))
# endif /* compiler */
    {
        STLSOFT_NS_QUAL_STD(copy)(first, last, STLSOFT_NS_QUAL_STD(back_inserter)(*this));

        STLSOFT_ASSERT(is_valid());
        return *this;
    }
    template <ss_typename_param_k II>
# if defined(STLSOFT_COMPILER_IS_MWERKS) || \
     defined(STLSOFT_COMPILER_IS_DMC)
    // There seems to be a bug in CodeWarrior that makes it have a cow with iterator tags by value, so we just use a ptr
    class_type& assign_(II first, II last, STLSOFT_NS_QUAL_STD(forward_iterator_tag) const*)
# else /* ? compiler */
    class_type& assign_(II first, II last, STLSOFT_NS_QUAL_STD(forward_iterator_tag))
# endif /* compiler */
    {
        ss_size_t const n   =   static_cast<ss_size_t>(STLSOFT_NS_QUAL_STD(distance)(first, last));
        buffer_type_    buffer(n);

        copy_n(first, buffer.size(), &buffer[0]);
        assign(buffer.data(), buffer.size());

        STLSOFT_ASSERT(is_valid());

        return *this;
    }
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

    // Appending
#if defined(STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT)
    template <ss_typename_param_k II>
# if defined(STLSOFT_COMPILER_IS_MWERKS) || \
     defined(STLSOFT_COMPILER_IS_DMC)
    class_type& append_(II first, II last, STLSOFT_NS_QUAL_STD(input_iterator_tag) const*)
# else /* ? compiler */
    class_type& append_(II first, II last, STLSOFT_NS_QUAL_STD(input_iterator_tag))
# endif /* compiler */
    {
        STLSOFT_NS_QUAL_STD(copy)(first, last, STLSOFT_NS_QUAL_STD(back_inserter)(*this));

        STLSOFT_ASSERT(is_valid());
        return *this;
    }
    template <ss_typename_param_k II>
# if defined(STLSOFT_COMPILER_IS_MWERKS) || \
     defined(STLSOFT_COMPILER_IS_DMC)
    class_type& append_(II first, II last, STLSOFT_NS_QUAL_STD(forward_iterator_tag) const*)
# else /* ? compiler */
    class_type& append_(II first, II last, STLSOFT_NS_QUAL_STD(forward_iterator_tag))
# endif /* compiler */
    {
        buffer_type_  buffer(static_cast<ss_size_t>(STLSOFT_NS_QUAL_STD(distance)(first, last)));

        std_copy(first, last, &buffer[0]);
        append(buffer.data(), buffer.size());

        STLSOFT_ASSERT(is_valid());
        return *this;
    }
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */
/// @}

/// \name Members
/// @{
private:
    member_pointer  m_buffer;
/// @}
};


/* /////////////////////////////////////////////////////////////////////////
 * typedefs
 */

#ifdef STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT
typedef basic_simple_string<ss_char_a_t>                    simple_string;
typedef basic_simple_string<ss_char_w_t>                    simple_wstring;
#else /* ? STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT */
typedef basic_simple_string<
    ss_char_a_t
,   stlsoft_char_traits<ss_char_a_t>
,   allocator_selector<ss_char_a_t>::allocator_type
>                                                           simple_string;
typedef basic_simple_string<
    ss_char_w_t
,   stlsoft_char_traits<ss_char_w_t>
,   allocator_selector<ss_char_w_t>::allocator_type
>                                                           simple_wstring;
#endif /* STLSOFT_CF_TEMPLATE_CLASS_DEFAULT_CLASS_ARGUMENT_SUPPORT */


/* /////////////////////////////////////////////////////////////////////////
 * traits
 */

/** Specialisation for stlsoft::basic_simple_string<>
 */
# ifdef STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT
template<
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
struct string_traits<
   basic_simple_string<C, T, A>
>
{
    // NOTE: Originally, what is string_type_ was defined as value_type, but
    // Borland objects to value_type::value_type.
    typedef basic_simple_string<C>                                  string_type_;
    typedef ss_typename_type_k string_type_::value_type             char_type;
    typedef ss_typename_type_k string_type_::size_type              size_type;
    typedef char_type const                                         const_char_type;
    typedef string_type_                                            string_type;
    typedef string_type_                                            value_type;
    typedef ss_typename_type_k string_type::pointer                 pointer;
    typedef ss_typename_type_k string_type::const_pointer           const_pointer;
    typedef ss_typename_type_k string_type::iterator                iterator;
    typedef ss_typename_type_k string_type::const_iterator          const_iterator;
#if defined(STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT)
    typedef ss_typename_type_k string_type::reverse_iterator        reverse_iterator;
    typedef ss_typename_type_k string_type::const_reverse_iterator  const_reverse_iterator;
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */
    enum
    {
            is_pointer          =   false
        ,   is_pointer_to_const =   false
        ,   char_type_size      =   sizeof(char_type)
    };

    static string_type empty_string() STLSOFT_NOEXCEPT
    {
        return string_type();
    }
    static string_type construct(string_type const& src, size_type pos, size_type len)
    {
        return string_type(src, pos, len);
    }
# ifdef STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT
    template <ss_typename_param_k I>
    static string_type& assign_inplace(string_type& str, I first, I last)
# else /* ? STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT */
    static string_type& assign_inplace(string_type& str, const_iterator first, const_iterator last)
# endif /* STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT */
    {
        // simple_string can assign in-place
        return str.assign(first, last);
    }
};
# else /* ? STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */
STLSOFT_TEMPLATE_SPECIALISATION
struct string_traits<simple_string>
{
    typedef basic_simple_string<ss_char_a_t>                value_type;
    typedef value_type::value_type                          char_type;
    typedef value_type::size_type                           size_type;
    typedef char_type const                                 const_char_type;
    typedef value_type                                      string_type;
    typedef string_type::pointer                            pointer;
    typedef string_type::const_pointer                      const_pointer;
    typedef string_type::iterator                           iterator;
    typedef string_type::const_iterator                     const_iterator;
#if defined(STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT)
    typedef string_type::reverse_iterator                   reverse_iterator;
    typedef string_type::const_reverse_iterator             const_reverse_iterator;
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */
    enum
    {
            is_pointer          =   false
        ,   is_pointer_to_const =   false
        ,   char_type_size      =   sizeof(char_type)
    };

    static string_type empty_string()
    {
        return string_type();
    }
    static string_type construct(string_type const& src, size_type pos, size_type len)
    {
        return string_type(src, pos, len);
    }
# ifdef STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT
    template <ss_typename_param_k I>
    static string_type& assign_inplace(string_type& str, I first, I last)
# else /* ? STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT */
    static string_type& assign_inplace(string_type& str, const_iterator first, const_iterator last)
# endif /* STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT */
    {
        // simple_string can assign in-place
        return str.assign(first, last);
    }
};

STLSOFT_TEMPLATE_SPECIALISATION
struct string_traits<simple_wstring>
{
    typedef basic_simple_string<ss_char_w_t>                value_type;
    typedef value_type::value_type                          char_type;
    typedef value_type::size_type                           size_type;
    typedef char_type const                                 const_char_type;
    typedef value_type                                      string_type;
    typedef string_type::pointer                            pointer;
    typedef string_type::const_pointer                      const_pointer;
    typedef string_type::iterator                           iterator;
    typedef string_type::const_iterator                     const_iterator;
#if defined(STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT)
    typedef string_type::reverse_iterator                   reverse_iterator;
    typedef string_type::const_reverse_iterator             const_reverse_iterator;
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */
    enum
    {
            is_pointer          =   false
        ,   is_pointer_to_const =   false
        ,   char_type_size      =   sizeof(char_type)
    };

    static string_type empty_string()
    {
        return string_type();
    }
    static string_type construct(string_type const& src, size_type pos, size_type len)
    {
        return string_type(src, pos, len);
    }
# ifdef STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT
    template <ss_typename_param_k I>
    static string_type& assign_inplace(string_type& str, I first, I last)
# else /* ? STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT */
    static string_type& assign_inplace(string_type& str, const_iterator first, const_iterator last)
# endif /* STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT */
    {
        // simple_string can assign in-place
        return str.assign(first, last);
    }
};
# endif /* STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */


/* /////////////////////////////////////////////////////////////////////////
 * operators
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

// operator ==

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
operator ==(
    basic_simple_string<C, T, A> const& lhs
,   basic_simple_string<C, T, A> const& rhs
)
{
    return 0 == lhs.compare(rhs);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator ==(
    basic_simple_string<C, T, A> const&                                 lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator ==(
    basic_simple_string<C, T, A> const& lhs
,   C const*                            rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return 0 == lhs.compare(rhs);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator ==(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   lhs
,   basic_simple_string<C, T, A> const&                                 rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator ==(
    C const*                            lhs
,   basic_simple_string<C, T, A> const& rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return 0 == rhs.compare(lhs);
}

// operator !=

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
operator !=(
    basic_simple_string<C, T, A> const& lhs
,   basic_simple_string<C, T, A> const& rhs
)
{
    return 0 != lhs.compare(rhs);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator !=(
    basic_simple_string<C, T, A> const&                                 lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator !=(
    basic_simple_string<C, T, A> const& lhs
,   C const*                            rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return 0 != lhs.compare(rhs);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator !=(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   lhs
,   basic_simple_string<C, T, A> const&                                 rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator !=(
    C const*                            lhs
,   basic_simple_string<C, T, A> const& rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return 0 != rhs.compare(lhs);
}

// operator <

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
operator <(
    basic_simple_string<C, T, A> const& lhs
,   basic_simple_string<C, T, A> const& rhs
)
{
    return lhs.compare(rhs) < 0;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator <(
    basic_simple_string<C, T, A> const&                                 lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator <(
    basic_simple_string<C, T, A> const& lhs
,   C const*                            rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs.compare(rhs) < 0;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator <(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   lhs
,   basic_simple_string<C, T, A> const&                                 rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator <(
    C const*                            lhs
,   basic_simple_string<C, T, A> const& rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return rhs.compare(lhs) > 0;
}

// operator <=

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
operator <=(
    basic_simple_string<C, T, A> const& lhs
,   basic_simple_string<C, T, A> const& rhs
)
{
    return lhs.compare(rhs) <= 0;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator <=(
    basic_simple_string<C, T, A> const&                                 lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator <=(
    basic_simple_string<C, T, A> const& lhs
,   C const*                            rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs.compare(rhs) <= 0;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator <=(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   lhs
,   basic_simple_string<C, T, A> const&                                 rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator <=(
    C const*                            lhs
,   basic_simple_string<C, T, A> const& rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return rhs.compare(lhs) >= 0;
}

// operator >

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
operator >(
    basic_simple_string<C, T, A> const& lhs
,   basic_simple_string<C, T, A> const& rhs
)
{
    return lhs.compare(rhs) > 0;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator >(
    basic_simple_string<C, T, A> const&                                 lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator >(
    basic_simple_string<C, T, A> const& lhs
,   C const*                            rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs.compare(rhs) > 0;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator >(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   lhs
,   basic_simple_string<C, T, A> const&                                 rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator >(
    C const*                            lhs
,   basic_simple_string<C, T, A> const& rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return rhs.compare(lhs) < 0;
}

// operator >=

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
operator >=(
    basic_simple_string<C, T, A> const& lhs
,   basic_simple_string<C, T, A> const& rhs
)
{
    return lhs.compare(rhs) >= 0;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator >=(
    basic_simple_string<C, T, A> const&                                 lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator >=(
    basic_simple_string<C, T, A> const& lhs
,   C const*                            rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return lhs.compare(rhs) >= 0;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator >=(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   lhs
,   basic_simple_string<C, T, A> const&                                 rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator >=(
    C const*                            lhs
,   basic_simple_string<C, T, A> const& rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return rhs.compare(lhs) <= 0;
}

// operator +

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>
operator +(
    basic_simple_string<C, T, A> const& lhs
,   basic_simple_string<C, T, A> const& rhs
)
{
    return basic_simple_string<C, T, A>(lhs) += rhs;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator +(
    basic_simple_string<C, T, A> const&                                 lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator +(
    basic_simple_string<C, T, A> const& lhs
,   C const*                            rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return basic_simple_string<C, T, A>(lhs) += rhs;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator +(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   lhs
,   basic_simple_string<C, T, A> const&                                 rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator +(
    C const*                            lhs
,   basic_simple_string<C, T, A> const& rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return basic_simple_string<C, T, A>(lhs) += rhs;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator +(
    basic_simple_string<C, T, A> const&                         lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type  rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator +(
    basic_simple_string<C, T, A> const& lhs
,   C                                   rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return basic_simple_string<C, T, A>(lhs) += rhs;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>
#ifdef STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT
operator +(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type  lhs
,   basic_simple_string<C, T, A> const&                         rhs
)
#else /* ? STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
operator +(
    C                                   lhs
,   basic_simple_string<C, T, A> const& rhs
)
#endif /* STLSOFT_CF_TEMPLATE_OUTOFCLASSFN_QUALIFIED_TYPE_SUPPORT */
{
    return basic_simple_string<C, T, A>(1, lhs) += rhs;
}

#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * shims
 */

/* c_str_ptr_null */

/** Returns the corresponding C-string pointer of \c s, or a null pointer
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
C const*
c_str_ptr_null(basic_simple_string<C, T, A> const& s)
{
    return (0 == s.length()) ? ss_nullptr_k : s.c_str();
}
/** char variant of c_str_ptr_null for basic_simple_string specialisations
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_char_a_t const*
c_str_ptr_null_a(basic_simple_string<ss_char_a_t, T, A> const& s)
{
    return c_str_ptr_null(s);
}
/** wchar_t variant of c_str_ptr_null for basic_simple_string specialisations
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_char_w_t const*
c_str_ptr_null_w(basic_simple_string<ss_char_w_t, T, A> const& s)
{
    return c_str_ptr_null(s);
}

/* c_str_ptr */

/** Returns the corresponding C-string pointer of \c s
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
C const*
c_str_ptr(basic_simple_string<C, T, A> const& s)
{
    return s.c_str();
}
/** char variant of c_str_ptr for basic_simple_string specialisations
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_char_a_t const*
c_str_ptr_a(basic_simple_string<ss_char_a_t, T, A> const& s)
{
    return c_str_ptr(s);
}
/** wchar_t variant of c_str_ptr for basic_simple_string specialisations
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_char_w_t const*
c_str_ptr_w(basic_simple_string<ss_char_w_t, T, A> const& s)
{
    return c_str_ptr(s);
}

/* c_str_data */

/** Returns the corresponding C-string pointer of \c s
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
C const*
c_str_data(basic_simple_string<C, T, A> const& s)
{
    return s.data();
}
/** char variant of c_str_data for basic_simple_string specialisations
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_char_a_t const*
c_str_data_a(basic_simple_string<ss_char_a_t, T, A> const& s)
{
    return c_str_data(s);
}
/** wchar_t variant of c_str_data for basic_simple_string specialisations
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_char_w_t const*
c_str_data_w(basic_simple_string<ss_char_w_t, T, A> const& s)
{
    return c_str_data(s);
}

/* c_str_ptr_len */

/** Returns the length (in characters) of \c s, <b><i>not</i></b> including the null-terminating character
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_size_t
c_str_len(basic_simple_string<C, T, A> const& s)
{
    return s.length();
}
/** char variant of c_str_len for basic_simple_string specialisations
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_size_t
c_str_len_a(basic_simple_string<ss_char_a_t, T, A> const& s)
{
    return c_str_len(s);
}
/** wchar_t variant of c_str_len for basic_simple_string specialisations
 *
 * \ingroup group__library__String
 */
template <
    ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_size_t
c_str_len_w(basic_simple_string<ss_char_w_t, T, A> const& s)
{
    return c_str_len(s);
}


/* /////////////////////////////////////////////////////////////////////////
 * stream insertion
 */

template <
    ss_typename_param_k T_stream
,   ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
T_stream&
operator <<(
    T_stream&                           stm
,   basic_simple_string<C, T, A> const& s
)
{
    STLSOFT_NS_USING(util::string_insert);

    string_insert(stm, s.data(), s.size());

    return stm;
}


/* /////////////////////////////////////////////////////////////////////////
 * swapping
 */

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
void
swap(
    basic_simple_string<C, T, A>& lhs
,   basic_simple_string<C, T, A>& rhs
)
{
    lhs.swap(rhs);
}


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

// Implementation

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_typename_type_ret_k basic_simple_string<C, T, A>::char_type*
basic_simple_string<C, T, A>::char_pointer_from_member_pointer_(ss_typename_type_k basic_simple_string<C, T, A>::member_pointer m) STLSOFT_NOEXCEPT
{
#ifdef STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST

    return (ss_nullptr_k == m) ? ss_nullptr_k : m->contents;
#else /* ? STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST */

    return m;
#endif /* STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST */
}


template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_constexpr_2014_k
ss_typename_type_ret_k basic_simple_string<C, T, A>::string_buffer*
basic_simple_string<C, T, A>::string_buffer_from_member_pointer_(ss_typename_type_k basic_simple_string<C, T, A>::member_pointer m) STLSOFT_NOEXCEPT
{
    STLSOFT_MESSAGE_ASSERT("Attempt to convert a null string_buffer in basic_simple_string", ss_nullptr_k != m);

#ifdef STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST

    return m;
#else /* ? STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST */

    return reinterpret_cast<string_buffer*>(const_cast<void*>(ptr_byte_offset(m, -static_cast<ss_ptrdiff_t>(STLSOFT_RAW_OFFSETOF(string_buffer, contents)))));
#endif /* STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST */
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_constexpr_2014_k
ss_typename_type_ret_k basic_simple_string<C, T, A>::string_buffer const*
basic_simple_string<C, T, A>::string_buffer_from_member_pointer_(ss_typename_type_k basic_simple_string<C, T, A>::member_const_pointer m) STLSOFT_NOEXCEPT
{
    STLSOFT_MESSAGE_ASSERT("Attempt to convert a null string_buffer in basic_simple_string", ss_nullptr_k != m);

#ifdef STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST
    return m;
#else /* ? STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST */

    return reinterpret_cast<string_buffer const*>(ptr_byte_offset(m, -static_cast<ss_ptrdiff_t>(STLSOFT_RAW_OFFSETOF(string_buffer, contents))));
#endif /* STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST */
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_typename_type_ret_k basic_simple_string<C, T, A>::member_pointer
basic_simple_string<C, T, A>::member_pointer_from_string_buffer_(ss_typename_type_k basic_simple_string<C, T, A>::string_buffer* b) STLSOFT_NOEXCEPT
{
#ifdef STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST
    return b;
#else /* ? STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST */

    return b->contents;
#endif /* STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST */
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_typename_type_ret_k basic_simple_string<C, T, A>::member_pointer
basic_simple_string<C, T, A>::alloc_buffer_(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   s
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          capacity
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          length
)
{
    // Pre-conditions
    STLSOFT_ASSERT(length <= capacity);
    STLSOFT_ASSERT(length >= traits_type::length_max_null(s, length));

    ss_size_t const members = (STLSOFT_RAW_OFFSETOF(string_buffer, contents) + (sizeof(char_type) - 1)) / sizeof(char_type);

    capacity += 1;                                              // For null terminator
    capacity += members;                                        // Include the internal members.
    capacity = (alloc_quantum + capacity) & ~alloc_quantum;     // Round up to (alloc_quantum + 1)

    byte_ator_type          byte_ator;
# ifdef STLSOFT_LF_ALLOCATOR_ALLOCATE_HAS_HINT

    void* const             raw_buffer  =   byte_ator.allocate(capacity * sizeof(char_type), ss_nullptr_k);
# else /* ? STLSOFT_LF_ALLOCATOR_ALLOCATE_HAS_HINT */

    void* const             raw_buffer  =   byte_ator.allocate(capacity * sizeof(char_type));
# endif /* STLSOFT_LF_ALLOCATOR_ALLOCATE_HAS_HINT */
    string_buffer* const    buffer      =   sap_cast<string_buffer*>(raw_buffer);

    if (ss_nullptr_k != buffer)
    {
        if (ss_nullptr_k == s)
        {
            STLSOFT_ASSERT(0 == length);

            buffer->contents[0] = traits_type::to_char_type(0);
        }
        else
        {
            traits_type::copy(buffer->contents, s, length);

            buffer->contents[length] = traits_type::to_char_type(0);
        }

        buffer->length      =   length;
        buffer->capacity    =   capacity - members;

        return member_pointer_from_string_buffer_(buffer);
    }

    return ss_nullptr_k;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_typename_type_ret_k basic_simple_string<C, T, A>::member_pointer
basic_simple_string<C, T, A>::alloc_buffer_(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   s
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cch
)
{
    size_type   length      =   traits_type::length_max_null(s, cch);
    size_type   capacity    =   cch;

    if (cch < length)
    {
        length = cch;
    }

    return alloc_buffer_(s, capacity, length);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_typename_type_ret_k basic_simple_string<C, T, A>::member_pointer
basic_simple_string<C, T, A>::alloc_buffer_(ss_typename_type_k basic_simple_string<C, T, A>::char_type const* s)
{
    member_pointer res;

    if (ss_nullptr_k == s)
    {
        res = ss_nullptr_k;
    }
    else
    {
        size_type len = traits_type::length(s);

        res = alloc_buffer_(s, len, len);
    }

    return res;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_typename_type_ret_k basic_simple_string<C, T, A>::member_pointer
basic_simple_string<C, T, A>::copy_buffer_(ss_typename_type_k basic_simple_string<C, T, A>::member_pointer m)
{
    if (ss_nullptr_k != m)
    {
        byte_ator_type          byte_ator;
        string_buffer* const    buffer      =   string_buffer_from_member_pointer_(m);
        ss_size_t const         cb          =   buffer->capacity * sizeof(char_type) + STLSOFT_RAW_OFFSETOF(string_buffer, contents);
# ifdef STLSOFT_LF_ALLOCATOR_ALLOCATE_HAS_HINT

        void* const             raw_buffer  =   byte_ator.allocate(cb, ss_nullptr_k);
# else /* ? STLSOFT_LF_ALLOCATOR_ALLOCATE_HAS_HINT */

        void* const             raw_buffer  =   byte_ator.allocate(cb);
# endif /* STLSOFT_LF_ALLOCATOR_ALLOCATE_HAS_HINT */
        string_buffer* const    new_buffer  =   sap_cast<string_buffer*>(raw_buffer);

        if (ss_nullptr_k != new_buffer)
        {
            STLSOFT_API_EXTERNAL_memfns_memcpy(new_buffer, buffer, cb);

            return member_pointer_from_string_buffer_(new_buffer);
        }
    }

    return ss_nullptr_k;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
void
basic_simple_string<C, T, A>::destroy_buffer_(ss_typename_type_k basic_simple_string<C, T, A>::string_buffer* buffer) STLSOFT_NOEXCEPT
{
#ifndef STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST

    // NOTE: the GCC warning "free-nonheap-object" is a very important one,
    // and only suppressed here with confidence that it is being issued in
    // error by (later versions of) GCC C++ compiler
# ifdef __GNUC__

#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wfree-nonheap-object"
# endif
#endif

    byte_ator_type byte_ator;

    byte_ator.deallocate(sap_cast<ss_byte_t*>(buffer), 0);

#ifndef STLSOFT_SIMPLE_STRING_NO_PTR_ADJUST

# ifdef __GNUC__

#  pragma GCC diagnostic pop
# endif
#endif
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
void
basic_simple_string<C, T, A>::destroy_buffer_(ss_typename_type_k basic_simple_string<C, T, A>::char_type* s) STLSOFT_NOEXCEPT
{
    destroy_buffer_(string_buffer_from_member_pointer_(s));
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::pointer
basic_simple_string<C, T, A>::begin_() STLSOFT_NOEXCEPT
{
    return char_pointer_from_member_pointer_(m_buffer);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::pointer
basic_simple_string<C, T, A>::end_() STLSOFT_NOEXCEPT
{
    return begin_() + length();
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_constexpr_2014_k
ss_bool_t
basic_simple_string<C, T, A>::is_valid() const STLSOFT_NOEXCEPT
{
    if (ss_nullptr_k != m_buffer)
    {
        string_buffer const* buffer = string_buffer_from_member_pointer_(m_buffer);

        if (buffer->capacity < 1)
        {
            return false;
        }
        else if (buffer->capacity < buffer->length)
        {
            return false;
        }
        else
        {
            size_type len = traits_type::length(buffer->contents);

            if (buffer->length < len)
            {
                return false;
            }
        }
    }

    return true;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_typename_type_ret_k basic_simple_string<C, T, A>::char_type const*
basic_simple_string<C, T, A>::empty_string_() STLSOFT_NOEXCEPT
{
    // This character array is initialised to 0, which conveniently happens to
    // be the empty string, by the module/application load, so it is
    // guaranteed to be valid, and there are no threading/race conditions
    static char_type s_empty[1];

    STLSOFT_ASSERT(s_empty[0] == '\0'); // Paranoid check

    return s_empty;
}

// Construction

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_constexpr_2014_k
basic_simple_string<C, T, A>::basic_simple_string() STLSOFT_NOEXCEPT
    : m_buffer(ss_nullptr_k)
{
    STLSOFT_ASSERT(is_valid());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>::basic_simple_string(class_type const& rhs)
    : m_buffer(copy_buffer_(rhs.m_buffer))
{
    STLSOFT_ASSERT(rhs.is_valid());
    STLSOFT_ASSERT(is_valid());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>::basic_simple_string(
    ss_typename_type_k basic_simple_string<C, T, A>::class_type const&  rhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          pos
)
    : m_buffer(alloc_buffer_(&rhs[pos], rhs.size() - pos))
{

    STLSOFT_ASSERT(is_valid());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>::basic_simple_string(
    ss_typename_type_k basic_simple_string<C, T, A>::class_type const&  rhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          pos
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cch
)
    : m_buffer(alloc_buffer_(&rhs[pos], cch, minimum(cch, rhs.size() - pos)))
{
    STLSOFT_ASSERT(is_valid());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>::basic_simple_string(ss_typename_type_k basic_simple_string<C, T, A>::char_type const* s)
    : m_buffer(alloc_buffer_(s))
{
    STLSOFT_ASSERT(is_valid());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>::basic_simple_string(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const* s
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type cch
)
    : m_buffer(alloc_buffer_(s, cch))
{
    STLSOFT_ASSERT(is_valid());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>::basic_simple_string(
    ss_typename_type_k basic_simple_string<C, T, A>::size_type  cch
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type  ch
)
    : m_buffer(ss_nullptr_k)
{
    STLSOFT_ASSERT(is_valid());

    assign(cch, ch);
}

#if !defined(STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT)
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>::basic_simple_string(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   first
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   last
)
    : m_buffer(alloc_buffer_(first, last - first))
{
    STLSOFT_ASSERT(is_valid());
}
#endif /* !STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

#ifdef STLSOFT_CF_RVALUE_REFERENCES_SUPPORT

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
basic_simple_string<C, T, A>::basic_simple_string(class_type&& rhs) STLSOFT_NOEXCEPT
    : m_buffer(rhs.m_buffer)
{
    rhs.m_buffer = ss_nullptr_k;
}
#endif /* STLSOFT_CF_RVALUE_REFERENCES_SUPPORT */

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_constexpr_2020_k
basic_simple_string<C, T, A>::~basic_simple_string() STLSOFT_NOEXCEPT
{
#if defined(__BORLANDC__) && \
    __BORLANDC__ > 0x0580 && \
    defined(STLSOFT_DEBUG)

    /* NOTE: this quite unbelievable call sequence is required with Borland
     * 6.1 to prevent the class invariant assertion from firing. It first
     * manifested in Pantheios' fe.WindowRegistry back-end unit-test.
     */

    if (!is_valid())
    {
        this->size();
    }
    else
    {
        this->size();

        fprintf(stdin, "%.*s", int(this->size()), this->data());
    }
#endif /* compiler */

    STLSOFT_ASSERT(is_valid());

    if (ss_nullptr_k != m_buffer)
    {
        destroy_buffer_(m_buffer);
    }
}

// Comparison

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_sint_t
basic_simple_string<C, T, A>::compare_(
    ss_typename_type_k basic_simple_string<C, T, A>::value_type const*  lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          lhs_len
,   ss_typename_type_k basic_simple_string<C, T, A>::value_type const*  rhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          rhs_len
) STLSOFT_NOEXCEPT
{
    size_type   cmp_len =   (lhs_len < rhs_len) ? lhs_len : rhs_len;
    ss_int_t    result  =   traits_type::compare(lhs, rhs, cmp_len);

    if (0 == result)
    {
        result = static_cast<ss_int_t>(lhs_len) - static_cast<ss_int_t>(rhs_len);
    }

    return result;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_sint_t
basic_simple_string<C, T, A>::compare(
    ss_typename_type_k basic_simple_string<C, T, A>::size_type          pos
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cch
,   ss_typename_type_k basic_simple_string<C, T, A>::value_type const*  rhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cchRhs
) const STLSOFT_NOEXCEPT
{
    size_type lhs_len = size();

    if (!(pos < lhs_len))
    {
        pos = lhs_len;
    }
    else
    {
        lhs_len -= pos;
    }

    if (cch < lhs_len)
    {
        lhs_len = cch;
    }

    size_type rhs_len = (ss_nullptr_k == rhs) ? 0 : traits_type::length(rhs);

    if (cchRhs < rhs_len)
    {
        rhs_len = cchRhs;
    }

    return compare_(char_pointer_from_member_pointer_(m_buffer) + pos, lhs_len, rhs, rhs_len);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_sint_t
basic_simple_string<C, T, A>::compare(
    ss_typename_type_k basic_simple_string<C, T, A>::size_type          pos
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cch
,   ss_typename_type_k basic_simple_string<C, T, A>::value_type const*  rhs
) const STLSOFT_NOEXCEPT
{
    size_type lhs_len = size();

    if (!(pos < lhs_len))
    {
        pos = lhs_len;
    }
    else
    {
        lhs_len -= pos;
    }

    if (cch < lhs_len)
    {
        lhs_len = cch;
    }

    size_type rhs_len = (ss_nullptr_k == rhs) ? 0 : traits_type::length(rhs);

    return compare_(char_pointer_from_member_pointer_(m_buffer) + pos, lhs_len, rhs, rhs_len);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_sint_t
basic_simple_string<C, T, A>::compare(
    ss_typename_type_k basic_simple_string<C, T, A>::value_type const* rhs
) const STLSOFT_NOEXCEPT
{
    size_type   lhs_len =   size();
    size_type   rhs_len =   (ss_nullptr_k == rhs) ? 0 : traits_type::length(rhs);

    return compare_(char_pointer_from_member_pointer_(m_buffer), lhs_len, rhs, rhs_len);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_sint_t
basic_simple_string<C, T, A>::compare(
    ss_typename_type_k basic_simple_string<C, T, A>::size_type          pos
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cch
,   ss_typename_type_k basic_simple_string<C, T, A>::class_type const&  rhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          posRhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cchRhs
) const STLSOFT_NOEXCEPT
{
    size_type lhs_len = size();

    if (pos == lhs_len)
    {
        lhs_len = 0u;
    }
    else if (pos + cch > lhs_len)
    {
        lhs_len -= pos;
    }

    if (cch < lhs_len)
    {
        lhs_len = cch;
    }

    size_type rhs_len = rhs.size();

    if (posRhs == rhs_len)
    {
        rhs_len = 0u;
    }
    else if (posRhs + cchRhs > rhs_len)
    {
        rhs_len -= posRhs;
    }

    if (cchRhs < rhs_len)
    {
        rhs_len = cchRhs;
    }

    return compare_(char_pointer_from_member_pointer_(m_buffer) + pos, lhs_len, char_pointer_from_member_pointer_(rhs.m_buffer) + posRhs, rhs_len);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_sint_t
basic_simple_string<C, T, A>::compare(
    ss_typename_type_k basic_simple_string<C, T, A>::size_type          pos
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cch
,   ss_typename_type_k basic_simple_string<C, T, A>::class_type const&  rhs
) const STLSOFT_NOEXCEPT
{
    size_type lhs_len = size();

    if (!(pos < lhs_len))
    {
        pos = lhs_len;
    }
    else
    {
        lhs_len -= pos;
    }

    if (cch < lhs_len)
    {
        lhs_len = cch;
    }

    size_type rhs_len = rhs.size();

    return compare_(char_pointer_from_member_pointer_(m_buffer) + pos, lhs_len, char_pointer_from_member_pointer_(rhs.m_buffer), rhs_len);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_sint_t
basic_simple_string<C, T, A>::compare(
    ss_typename_type_k basic_simple_string<C, T, A>::class_type const& rhs
) const STLSOFT_NOEXCEPT
{
    size_type   lhs_len =   size();
    size_type   rhs_len =   rhs.size();

    return compare_(char_pointer_from_member_pointer_(m_buffer), lhs_len, char_pointer_from_member_pointer_(rhs.m_buffer), rhs_len);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_bool_t
basic_simple_string<C, T, A>::equal_(
    ss_typename_type_k basic_simple_string<C, T, A>::value_type const*  lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          lhs_len
,   ss_typename_type_k basic_simple_string<C, T, A>::value_type const*  rhs
) STLSOFT_NOEXCEPT
{
    for (size_type i = 0; i != lhs_len; ++i, ++rhs, ++lhs)
    {
        if (*rhs == '\0')
        {
            return false;
        }

        if (*lhs != *rhs)
        {
            return false;
        }
    }

    return true;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
/* static */
ss_bool_t
basic_simple_string<C, T, A>::equal_(
    ss_typename_type_k basic_simple_string<C, T, A>::value_type const*  lhs
,   ss_typename_type_k basic_simple_string<C, T, A>::value_type const*  rhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          len
) STLSOFT_NOEXCEPT
{
    for (size_type i = 0; i != len; ++i, ++rhs, ++lhs)
    {
        if (*lhs != *rhs)
        {
            return false;
        }
    }

    return true;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::equal(
    size_type           pos
,   size_type           cch
,   value_type const*   s
,   size_type           cchRhs
) const STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(0 == cchRhs || ss_nullptr_k != s);

    if (0 == cchRhs)
    {
        return true;
    }

    if (cch != cchRhs)
    {
        return false;
    }

    if (ss_nullptr_k == m_buffer)
    {
        if (0 != pos)
        {
            STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("`basic_simple_string#equal()` index out of range"));
        }

        return false;
    }
    else
    {
        string_buffer const* const  buffer  =   string_buffer_from_member_pointer_(m_buffer);
        size_type const             lhs_n   =   minimum(buffer->length - pos, cch);
        size_type const             rhs_len =   traits_type::length(s);
        size_type const             rhs_n   =   minimum(rhs_len, cchRhs);

        if (lhs_n != rhs_n)
        {
            return false;
        }
        else
        {
            return 0 == traits_type::compare(buffer->contents + pos, s, lhs_n);
        }
    }
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::equal(
    size_type           pos
,   size_type           cch
,   value_type const*   s
) const STLSOFT_NOEXCEPT
{
    if (ss_nullptr_k == m_buffer)
    {
        if (ss_nullptr_k == s)
        {
            return true;
        }
        else
        {
            return '\0' == *s;
        }
    }
    else
    {
        string_buffer const* buffer = string_buffer_from_member_pointer_(m_buffer);

        if (ss_nullptr_k == s)
        {
            return 0 == buffer->length;
        }
        else
        {
            char_type const* const  lhs_ptr =   buffer->contents + pos;
            size_type const         lhs_n   =   minimum(buffer->length - pos, cch);

            if (pos >= buffer->length)
            {
                if (pos > buffer->length ||
                    0 != lhs_n)
                {
                    STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("`basic_simple_string#equal()` index out of range"));
                }
            }

            size_type const         rhs_len =   traits_type::length(s);

            if (rhs_len != lhs_n)
            {
                return false;
            }
            else
            {
                return 0 == compare_(lhs_ptr, lhs_n, s, rhs_len);
            }
        }
    }
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::equal(
    ss_typename_type_k basic_simple_string<C, T, A>::value_type const* s
) const STLSOFT_NOEXCEPT
{
    if (ss_nullptr_k == m_buffer)
    {
        if (ss_nullptr_k == s)
        {
            return true;
        }
        else
        {
            return '\0' == *s;
        }
    }
    else
    {
        string_buffer const* buffer = string_buffer_from_member_pointer_(m_buffer);

        return class_type::equal_(buffer->contents, buffer->length, s);
    }
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::equal(
    size_type                                                           pos
,   size_type                                                           cch
,   ss_typename_type_k basic_simple_string<C, T, A>::class_type const&  rhs
,   size_type                                                           posRhs
,   size_type                                                           cchRhs
) const STLSOFT_NOEXCEPT
{
    // find if such a range exists within both
    //
    // if either `pos` out of range then throw

    if (ss_nullptr_k == m_buffer)
    {
        if (0 != pos)
        {
            STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("`basic_simple_string#equal()` index out of range"));
        }

        if (ss_nullptr_k == rhs.m_buffer)
        {
            if (0 != posRhs)
            {
                STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("`basic_simple_string#equal()` index out of range"));
            }
        }

        return 0 == cchRhs;
    }
    else
    {
        string_buffer const* const  lhs_buffer  =   string_buffer_from_member_pointer_(m_buffer);
        char_type const* const      lhs_ptr     =   lhs_buffer->contents + pos;
        size_type const             lhs_n       =   minimum(lhs_buffer->length - pos, cch);

        if (ss_nullptr_k == rhs.m_buffer)
        {
            if (0 != posRhs)
            {
                STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("`basic_simple_string#equal()` index out of range"));
            }

            return 0 == cchRhs;
        }
        else
        {
            string_buffer const* const  rhs_buffer  =   string_buffer_from_member_pointer_(rhs.m_buffer);
            char_type const* const      rhs_ptr     =   rhs_buffer->contents + posRhs;
            size_type const             rhs_n       =   minimum(rhs_buffer->length - posRhs, cchRhs);

            if (lhs_n != rhs_n)
            {
                return false;
            }
            else
            {
                return 0 == traits_type::compare(lhs_ptr, rhs_ptr, lhs_n);
            }
        }
    }
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::equal(
    size_type                                                           pos
,   size_type                                                           cch
,   ss_typename_type_k basic_simple_string<C, T, A>::class_type const&  rhs
) const STLSOFT_NOEXCEPT
{
    if (ss_nullptr_k == rhs.m_buffer)
    {
        return true;
    }
    else
    {
        string_buffer const* const  lhs_buffer  =   string_buffer_from_member_pointer_(m_buffer);
        char_type const* const      lhs_ptr     =   lhs_buffer->contents + pos;
        size_type const             lhs_n       =   minimum(lhs_buffer->length - pos, cch);

        if (pos >= lhs_buffer->length)
        {
            if (pos > lhs_buffer->length ||
                0 != lhs_n)
            {
                STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("`basic_simple_string#equal()` index out of range"));
            }
        }

        string_buffer const* const  rhs_buffer  =   string_buffer_from_member_pointer_(rhs.m_buffer);

        if (0 == rhs_buffer->length)
        {
            return true;
        }
        else
        {
            if (lhs_n != rhs_buffer->length)
            {
                return false;
            }
            else
            {
                return 0 == traits_type::compare(lhs_ptr, rhs_buffer->contents, rhs_buffer->length);
            }
        }
    }
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::equal(
    ss_typename_type_k basic_simple_string<C, T, A>::class_type const& rhs
) const STLSOFT_NOEXCEPT
{
    if (ss_nullptr_k == m_buffer)
    {
        if (ss_nullptr_k == rhs.m_buffer)
        {
            return true;
        }
        else
        {
            string_buffer const* const rhs_buffer = string_buffer_from_member_pointer_(rhs.m_buffer);

            return 0 == rhs_buffer->length;
        }
    }
    else
    {
        string_buffer const* const lhs_buffer = string_buffer_from_member_pointer_(m_buffer);

        if (ss_nullptr_k == rhs.m_buffer)
        {
            return 0 == lhs_buffer->length;
        }
        else
        {
            string_buffer const* const rhs_buffer = string_buffer_from_member_pointer_(rhs.m_buffer);

            if (lhs_buffer->length != rhs_buffer->length)
            {
                return false;
            }
            else
            {
                return 0 == traits_type::compare(lhs_buffer->contents, rhs_buffer->contents, lhs_buffer->length);
            }
        }
    }
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::contains_(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   s
,   size_type                                                           n
) const STLSOFT_NOEXCEPT
{
    if (n > length())
    {
        return false;
    }

    if (0 == n)
    {
        return true;
    }

    char_type first_char = s[0];

    // search for each occurrence of `s[0]` in `this` using `traits_type::find()`, then
    // testing each remaining part of `this` (if long enought) for all of `s`, using
    // `traits::compare()`

    char_type const*    in = data();
    size_type           num_remaining = length();

    for (;;)
    {
        if (ss_nullptr_k == traits_type::find(in, num_remaining, first_char))
        {
            return false;
        }
        else
        {
            size_type remaining_length = length() - (in - data());

            if (n > remaining_length)
            {
                return false;
            }

            if (0 == traits_type::compare(s, in, n))
            {
                return true;
            }
            else
            {
                ++in;
                --num_remaining;
            }
        }
    }
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::starts_with_(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   s
,   size_type                                                           n
) const STLSOFT_NOEXCEPT
{
    if (ss_nullptr_k == m_buffer)
    {
        if (0 == n)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    string_buffer const* buffer = string_buffer_from_member_pointer_(m_buffer);

    if (buffer->length < n)
    {
        return false;
    }
    else
    {
        return class_type::equal_(
            buffer->contents
        ,   s
        ,   n
        );
    }
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::ends_with_(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   s
,   size_type                                                           n
) const STLSOFT_NOEXCEPT
{
    if (ss_nullptr_k == m_buffer)
    {
        if (0 == n)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    string_buffer const* buffer = string_buffer_from_member_pointer_(m_buffer);

    if (buffer->length < n)
    {
        return false;
    }
    else
    {
        return class_type::equal_(
            buffer->contents + (buffer->length - n)
        ,   s
        ,   n
        );
    }
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::contains(ss_typename_type_k basic_simple_string<C, T, A>::class_type const& s) const STLSOFT_NOEXCEPT
{
    return contains_(s.data(), s.length());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::contains(ss_typename_type_k basic_simple_string<C, T, A>::char_type const* s) const STLSOFT_NOEXCEPT
{
    size_type const n = (ss_nullptr_k == s) ? 0 : traits_type::length(s);

    return contains_(s, n);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::contains(ss_typename_type_k basic_simple_string<C, T, A>::char_type ch) const STLSOFT_NOEXCEPT
{
    if (empty())
    {
        return false;
    }

    return ss_nullptr_k != traits_type::find(data(), length(), ch);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::starts_with(ss_typename_type_k basic_simple_string<C, T, A>::class_type const& s) const STLSOFT_NOEXCEPT
{
    return starts_with_(s.data(), s.size());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::starts_with(ss_typename_type_k basic_simple_string<C, T, A>::char_type const* s) const STLSOFT_NOEXCEPT
{
    size_type const n = (ss_nullptr_k == s) ? 0 : traits_type::length(s);

    return starts_with_(s, n);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::starts_with(ss_typename_type_k basic_simple_string<C, T, A>::char_type ch) const STLSOFT_NOEXCEPT
{
    return empty() ? false : (front() == ch);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::ends_with(ss_typename_type_k basic_simple_string<C, T, A>::class_type const& s) const STLSOFT_NOEXCEPT
{
    return ends_with_(s.data(), s.size());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::ends_with(ss_typename_type_k basic_simple_string<C, T, A>::char_type const* s) const STLSOFT_NOEXCEPT
{
    size_type const n = (ss_nullptr_k == s) ? 0 : traits_type::length(s);

    return ends_with_(s, n);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::ends_with(ss_typename_type_k basic_simple_string<C, T, A>::char_type ch) const STLSOFT_NOEXCEPT
{
    return empty() ? false : (back() == ch);
}

// Accessors
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::reference
basic_simple_string<C, T, A>::operator [](ss_typename_type_k basic_simple_string<C, T, A>::size_type index) STLSOFT_NOEXCEPT
{
    STLSOFT_MESSAGE_ASSERT("index access out of range in simple_string", index < size());

    STLSOFT_ASSERT(is_valid());

    return char_pointer_from_member_pointer_(m_buffer)[index];
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::const_reference
basic_simple_string<C, T, A>::operator [](ss_typename_type_k basic_simple_string<C, T, A>::size_type index) const STLSOFT_NOEXCEPT
{
    STLSOFT_MESSAGE_ASSERT("index access out of range in simple_string", index < size() + 1); // Valid to return (const) reference to nul-terminator

    STLSOFT_ASSERT(is_valid());

    return char_pointer_from_member_pointer_(m_buffer)[index];
}

#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::reference
basic_simple_string<C, T, A>::at(ss_typename_type_k basic_simple_string<C, T, A>::size_type index)
{
    STLSOFT_ASSERT(is_valid());

    if (index >= size())
    {
        STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("index out of range"));
    }

    STLSOFT_ASSERT(is_valid());

    return char_pointer_from_member_pointer_(m_buffer)[index];
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::const_reference
basic_simple_string<C, T, A>::at(ss_typename_type_k basic_simple_string<C, T, A>::size_type index) const
{
    STLSOFT_ASSERT(is_valid());

    if (index >= size())
    {
        STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("index out of range"));
    }

    STLSOFT_ASSERT(is_valid());

    return char_pointer_from_member_pointer_(m_buffer)[index];
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type
basic_simple_string<C, T, A>::substr(
    ss_typename_type_k basic_simple_string<C, T, A>::size_type  pos
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type  cch
) const
{
    STLSOFT_ASSERT(is_valid());

    if (pos > size())
    {
        STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("index out of range"));
    }

    STLSOFT_ASSERT(is_valid());

    if (cch > (this->size() - pos))
    {
        cch = this->size() - pos;
    }

    return class_type(this->data() + pos, cch);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type
basic_simple_string<C, T, A>::substr(
    ss_typename_type_k basic_simple_string<C, T, A>::size_type pos
) const
{
    STLSOFT_ASSERT(is_valid());

    if (pos > size())
    {
        STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("index out of range"));
    }

    STLSOFT_ASSERT(is_valid());

    return class_type(this->data() + pos, this->size() - pos);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type
basic_simple_string<C, T, A>::substr() const
{
    return *this;
}
#endif /* !STLSOFT_CF_EXCEPTION_SUPPORT */

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::value_type const*
basic_simple_string<C, T, A>::c_str() const STLSOFT_NOEXCEPT
{
    return (ss_nullptr_k == m_buffer) ? empty_string_() : char_pointer_from_member_pointer_(m_buffer);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::value_type const*
basic_simple_string<C, T, A>::data() const STLSOFT_NOEXCEPT
{
    return (ss_nullptr_k == m_buffer) ? empty_string_() : char_pointer_from_member_pointer_(m_buffer);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::reference
basic_simple_string<C, T, A>::front() STLSOFT_NOEXCEPT
{
    return (*this)[0];
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::reference
basic_simple_string<C, T, A>::back() STLSOFT_NOEXCEPT
{
    return (*this)[size() - 1];
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::const_reference
basic_simple_string<C, T, A>::front() const STLSOFT_NOEXCEPT
{
    return (*this)[0];
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::const_reference
basic_simple_string<C, T, A>::back() const STLSOFT_NOEXCEPT
{
    return (*this)[size() - 1];
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::size_type
basic_simple_string<C, T, A>::copy(
    ss_typename_type_k basic_simple_string<C, T, A>::value_type*    dest
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type      cch
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type      pos /* = 0 */
) const STLSOFT_NOEXCEPT
{
    size_type len = size();

    if (pos < len)
    {
        if (len < pos + cch)
        {
            cch = len - pos;
        }

        traits_type::copy(dest, data() + pos, cch);
    }
    else
    {
        cch = 0;
    }

    return cch;
}

// Iteration

#ifndef STLSOFT_SIMPLE_STRING_ITERATOR_METHODS_INLINE

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::const_iterator
basic_simple_string<C, T, A>::begin() const STLSOFT_NOEXCEPT
{
    return const_cast<class_type*>(this)->begin_();
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::const_iterator
basic_simple_string<C, T, A>::end() const STLSOFT_NOEXCEPT
{
    return const_cast<class_type*>(this)->end_();
}
#endif /* !STLSOFT_SIMPLE_STRING_ITERATOR_METHODS_INLINE */

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::iterator
basic_simple_string<C, T, A>::begin() STLSOFT_NOEXCEPT
{
    return begin_();
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::iterator
basic_simple_string<C, T, A>::end() STLSOFT_NOEXCEPT
{
    return end_();
}

#if defined(STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT)
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::const_reverse_iterator
basic_simple_string<C, T, A>::rbegin() const STLSOFT_NOEXCEPT
{
    return const_reverse_iterator(end());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::const_reverse_iterator
basic_simple_string<C, T, A>::rend() const STLSOFT_NOEXCEPT
{
    return const_reverse_iterator(begin());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::reverse_iterator
basic_simple_string<C, T, A>::rbegin() STLSOFT_NOEXCEPT
{
    return reverse_iterator(end());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::reverse_iterator
basic_simple_string<C, T, A>::rend() STLSOFT_NOEXCEPT
{
    return reverse_iterator(begin());
}
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */

// Assignment
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::assign(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   s
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cch
)
{
    STLSOFT_ASSERT(is_valid());

    if (ss_nullptr_k == m_buffer)
    {
        if (0 == cch)
        {
            // Nothing to do
        }
        else
        {
            m_buffer = alloc_buffer_(s, cch);
        }
    }
    else
    {
        if (ss_nullptr_k == s)
        {
            destroy_buffer_(m_buffer);

            m_buffer = ss_nullptr_k;
        }
        else
        {
            // Here is an opportunity to optimise a bit. We will do more so in a
            // later release, but for the moment we will reuse our existing
            // buffer if its capacity is sufficient for our purposes

            string_buffer* const buffer = string_buffer_from_member_pointer_(m_buffer);

            // If:
            //
            // - the required size fits, AND
            // - the source string is not within the existing buffer

            if (cch < buffer->capacity &&
                (   s < &buffer->contents[0] ||
                    s > &buffer->contents[cch]))
            {
                traits_type::move(buffer->contents, s, cch);
                buffer->contents[cch] = 0;
                buffer->length = cch;
            }
            else
            {
                member_pointer const new_buffer = alloc_buffer_(s, cch, cch);

                destroy_buffer_(m_buffer);

                m_buffer = new_buffer;
            }
        }
    }

    STLSOFT_ASSERT(is_valid());
    return *this;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::assign(ss_typename_type_k basic_simple_string<C, T, A>::char_type const* s)
{
    return assign(s, (ss_nullptr_k == s) ? 0 : traits_type::length(s));
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::assign(
    ss_typename_type_k basic_simple_string<C, T, A>::class_type const&  rhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          pos
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cch
)
{
    char_type*  s   =   char_pointer_from_member_pointer_(rhs.m_buffer);
    size_type   len =   rhs.size();

    if (len < pos)
    {
        pos = len;
    }

    if (len - pos < cch)
    {
        cch = len - pos;
    }

    if (ss_nullptr_k != s)
    {
        s += pos;
    }
    else
    {
        cch = 0;
    }

    return assign(s, cch);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::assign(ss_typename_type_k basic_simple_string<C, T, A>::class_type const& rhs)
{
    return assign(char_pointer_from_member_pointer_(rhs.m_buffer), rhs.size());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::assign(
    ss_typename_type_k basic_simple_string<C, T, A>::size_type  cch
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type  ch
)
{
    buffer_type_    buffer(cch);

    static_cast<void>(STLSOFT_NS_QUAL_STD(fill)(buffer.begin(), buffer.end(), ch));

    return assign(buffer.data(), buffer.size());
}

#if !defined(STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT)
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::assign(
    ss_typename_type_k basic_simple_string<C, T, A>::const_iterator first
,   ss_typename_type_k basic_simple_string<C, T, A>::const_iterator last
)
{
    // We have to use this strange appearing this, because of Visual C++ .NET's
    // disgusting STL swill. Sigh!
    return assign(&(*first), last - first);
}
#endif /* !STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type const&
basic_simple_string<C, T, A>::operator =(ss_typename_type_k basic_simple_string<C, T, A>::class_type const& rhs)
{
    return assign(rhs);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type const&
basic_simple_string<C, T, A>::operator =(ss_typename_type_k basic_simple_string<C, T, A>::char_type const* s)
{
    return assign(s);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type const&
basic_simple_string<C, T, A>::operator =(ss_typename_type_k basic_simple_string<C, T, A>::char_type ch)
{
    char_type   sz[2] = { ch, traits_type::to_char_type(0) };

    return assign(sz);
}


// Appending
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::append(
    ss_typename_type_k basic_simple_string<C, T, A>::char_type const*   s
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cch
)
{
    STLSOFT_ASSERT(is_valid());

    if (ss_nullptr_k == m_buffer)
    {
        assign(s, cch);
    }
    else
    {
        if (ss_nullptr_k == s ||
            0 == cch)
        {
            // Nothing to do
        }
        else
        {
#if 1
            // We're taking a length here, which may have been done already.
            // This should be optimised out in a subsequent release
            size_type len = traits_type::length_max(s, cch);

            if (len < cch)
            {
                cch = len;
            }
#endif /* 0 */

            string_buffer*  old_buffer  =   ss_nullptr_k;
            string_buffer*  buffer      =   string_buffer_from_member_pointer_(m_buffer);
            size_type const buf_len     =   buffer->length;

            if (buffer->capacity - buf_len < 1 + cch)
            {
                // Allocate a new buffer of sufficient size
                member_pointer const new_buffer = alloc_buffer_(buffer->contents, buf_len + cch);

                if (ss_nullptr_k == new_buffer) // Some allocators do not throw on failure!
                {
                    cch = 0;
                }
                else
                {
                    old_buffer = buffer;    // Mark for destruction, but hold around in case appending from self
                    m_buffer = new_buffer;
                    buffer = string_buffer_from_member_pointer_(new_buffer);
                }
            }

            traits_type::copy(buffer->contents + buf_len, s, cch);
            buffer->length += cch;
            buffer->contents[buffer->length] = traits_type::to_char_type(0);

            if (ss_nullptr_k != old_buffer)
            {
                destroy_buffer_(old_buffer);
            }
        }
    }

    STLSOFT_ASSERT(is_valid());
    return *this;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::append(ss_typename_type_k basic_simple_string<C, T, A>::char_type const* s)
{
    return append(s, (ss_nullptr_k == s) ? 0 : traits_type::length(s));
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::append(
    ss_typename_type_k basic_simple_string<C, T, A>::class_type const&  rhs
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          pos
,   ss_typename_type_k basic_simple_string<C, T, A>::size_type          cch
)
{
    char_type*  s   =   char_pointer_from_member_pointer_(rhs.m_buffer);
    size_type   len =   rhs.size();

    if (len < pos)
    {
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
        STLSOFT_THROW_X(STLSOFT_NS_QUAL_STD(out_of_range)("index out of range"));
#else /* ? STLSOFT_CF_EXCEPTION_SUPPORT */
        pos = len;
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
    }

    if (len - pos < cch)
    {
        cch = len - pos;
    }

    if (ss_nullptr_k != s)
    {
        s += pos;
    }
    else
    {
        cch = 0;
    }

    return append(s, cch);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::append(ss_typename_type_k basic_simple_string<C, T, A>::class_type const& s)
{
    return append(char_pointer_from_member_pointer_(s.m_buffer), s.size());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::append(
    ss_typename_type_k basic_simple_string<C, T, A>::size_type  cch
,   ss_typename_type_k basic_simple_string<C, T, A>::char_type  ch
)
{
    if (ss_nullptr_k == m_buffer)
    {
        assign(cch, ch);
    }
    else
    {
        buffer_type_    buffer(cch);

        static_cast<void>(STLSOFT_NS_QUAL_STD(fill)(buffer.begin(), buffer.end(), ch));

        append(buffer.data(), buffer.size());
    }

    return *this;
}

#if !defined(STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT)
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::append(
    ss_typename_type_k basic_simple_string<C, T, A>::const_iterator first
,   ss_typename_type_k basic_simple_string<C, T, A>::const_iterator last
)
{
    // We have to use this strange appearing code because of Visual C++ .NET's
    // disgusting STL swill. Sigh!
    return append(&(*first), last - first);
}
#endif /* !STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT */

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::operator +=(ss_typename_type_k basic_simple_string<C, T, A>::char_type ch)
{
    return append(1, ch);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::operator +=(ss_typename_type_k basic_simple_string<C, T, A>::char_type const* s)
{
    return append(s);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::class_type&
basic_simple_string<C, T, A>::operator +=(ss_typename_type_k basic_simple_string<C, T, A>::class_type const& rhs)
{
    return append(rhs);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
void
basic_simple_string<C, T, A>::push_back(ss_typename_type_k basic_simple_string<C, T, A>::char_type ch)
{
    append(1, ch);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
void
basic_simple_string<C, T, A>::pop_back() STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(is_valid());

    if (0 != size())
    {
        string_buffer* const buffer = string_buffer_from_member_pointer_(m_buffer);

        buffer->contents[--buffer->length] = '\0';
    }
}

// Modifiers

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
void
basic_simple_string<C, T, A>::reserve(ss_typename_type_k basic_simple_string<C, T, A>::size_type cch)
{
    if (size() < cch)
    {
        if (ss_nullptr_k == m_buffer)
        {
            m_buffer = alloc_buffer_(ss_nullptr_k, cch, 0);
        }
        else
        {
            if (cch <= string_buffer_from_member_pointer_(m_buffer)->capacity)
            {
                ; // Nothing to do
            }
            else
            {
                // Allocate a new buffer of sufficient size
                member_pointer const new_buffer = alloc_buffer_(c_str(), cch, size());

                if (ss_nullptr_k != new_buffer) // Some allocators do not throw on failure!
                {
                    destroy_buffer_(m_buffer);
                    m_buffer = new_buffer;
                }
            }
        }
    }
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
void
basic_simple_string<C, T, A>::swap(ss_typename_type_k basic_simple_string<C, T, A>::class_type& other) STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(is_valid());
    STLSOFT_ASSERT(other.is_valid());

    std_swap(m_buffer, other.m_buffer);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
void
basic_simple_string<C, T, A>::resize(
    ss_typename_type_k basic_simple_string<C, T, A>::size_type  cch
,   ss_typename_type_k basic_simple_string<C, T, A>::value_type ch
)
{
    STLSOFT_ASSERT(is_valid());

    size_type const len = size();

    if (len != cch)
    {
        if (len < cch)
        {
            /* Ensure storage for cch characters (+ nul), preserving the
             * existing len characters. Note: must NOT use assign(c_str(),
             * cch) — that would copy cch characters from a source of only
             * len characters (heap over-read).
             */

            if (ss_nullptr_k == m_buffer)
            {
                m_buffer = alloc_buffer_(ss_nullptr_k, cch, 0);
            }
            else
            {
                string_buffer* const buffer = string_buffer_from_member_pointer_(m_buffer);

                if (cch >= buffer->capacity)
                {
                    member_pointer const new_buffer = alloc_buffer_(buffer->contents, cch, len);

                    destroy_buffer_(m_buffer);

                    m_buffer = new_buffer;
                }
            }

            if (ss_nullptr_k != m_buffer)
            {
                traits_type::assign(char_pointer_from_member_pointer_(m_buffer) + len, cch - len, ch);

                string_buffer* const buffer = string_buffer_from_member_pointer_(m_buffer);

                buffer->length = cch;
                buffer->contents[buffer->length] = traits_type::to_char_type(0);
            }
        }
        else
        {
            string_buffer* const buffer = string_buffer_from_member_pointer_(m_buffer);

            buffer->length = cch;
            buffer->contents[buffer->length] = traits_type::to_char_type(0);
        }
    }

    STLSOFT_ASSERT(is_valid());
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
void
basic_simple_string<C, T, A>::clear() STLSOFT_NOEXCEPT
{
    if (ss_nullptr_k != m_buffer)
    {
        string_buffer* buffer = string_buffer_from_member_pointer_(m_buffer);

        buffer->length      =   0;
        buffer->contents[0] =   traits_type::to_char_type(0);
    }
}

// Attributes
template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::size_type
basic_simple_string<C, T, A>::size() const STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(is_valid());

    return (ss_nullptr_k == m_buffer) ? 0 : string_buffer_from_member_pointer_(m_buffer)->length;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::size_type
basic_simple_string<C, T, A>::max_size() const STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(is_valid());

    return static_cast<size_type>(-1) / sizeof(char_type);
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::size_type
basic_simple_string<C, T, A>::length() const STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(is_valid());

    return size();
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_typename_type_ret_k basic_simple_string<C, T, A>::size_type
basic_simple_string<C, T, A>::capacity() const STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(is_valid());

    return (ss_nullptr_k == m_buffer) ? 0 : string_buffer_from_member_pointer_(m_buffer)->capacity;
}

template <
    ss_typename_param_k C
,   ss_typename_param_k T
,   ss_typename_param_k A
>
inline
ss_bool_t
basic_simple_string<C, T, A>::empty() const STLSOFT_NOEXCEPT
{
    STLSOFT_ASSERT(is_valid());

    return 0 == size();
}

#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} // namespace stlsoft
#endif /* STLSOFT_NO_NAMESPACE */

/* In the special case of Intel behaving as VC++ 7.0 or earlier on Win32, we
 * illegally insert into the std namespace.
 */
#if defined(STLSOFT_CF_std_NAMESPACE)
# if ( ( defined(STLSOFT_COMPILER_IS_INTEL) && \
         defined(_MSC_VER))) && \
     _MSC_VER < 1310
namespace std
{
    template <
        ss_typename_param_k C
    ,   ss_typename_param_k T
    ,   ss_typename_param_k A
    >
    inline
    void
    swap(
        STLSOFT_NS_QUAL(basic_simple_string)<C, T, A>&  lhs
    ,   STLSOFT_NS_QUAL(basic_simple_string)<C, T, A>&  rhs
    )
    {
        lhs.swap(rhs);
    }
} // namespace std
# endif /* INTEL && _MSC_VER < 1310 */
#endif /* STLSOFT_CF_std_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_STRING_HPP_SIMPLE_STRING */

/* ///////////////////////////// end of file //////////////////////////// */

