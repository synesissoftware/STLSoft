/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/filesystem/io_functions/write_string.hpp
 *
 * Purpose: Definition of stlsoft::write_string<>() function template.
 *
 * Created: 22nd February 2024
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2024, Matthew Wilson and Synesis Information Systems
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


/** \file stlsoft/filesystem/io_functions/write_string.hpp
 *
 * \brief [C++] Definition of the stlsoft::write_string() function
 *   template
 *   (\ref group__library__FileSystem "File System" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_FILESYSTEM_IO_FUNCTIONS_HPP_WRITE_STRING
#define STLSOFT_INCL_STLSOFT_FILESYSTEM_IO_FUNCTIONS_HPP_WRITE_STRING

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_FILESYSTEM_IO_FUNCTIONS_HPP_WRITE_STRING_MAJOR     1
# define STLSOFT_VER_STLSOFT_FILESYSTEM_IO_FUNCTIONS_HPP_WRITE_STRING_MINOR     0
# define STLSOFT_VER_STLSOFT_FILESYSTEM_IO_FUNCTIONS_HPP_WRITE_STRING_REVISION  3
# define STLSOFT_VER_STLSOFT_FILESYSTEM_IO_FUNCTIONS_HPP_WRITE_STRING_EDIT      5
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

// #ifndef STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER
// # include <stlsoft/memory/auto_buffer.hpp>
// #endif /* !STLSOFT_INCL_STLSOFT_MEMORY_HPP_AUTO_BUFFER */
#ifndef STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_HPP_STRING
# include <stlsoft/shims/access/string.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_HPP_STRING */
#ifndef STLSOFT_INCL_STLSOFT_SHIMS_ATTRIBUTE_HPP_GET_FILE_PTR
# include <stlsoft/shims/attribute/get_FILE_ptr.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_SHIMS_ATTRIBUTE_HPP_GET_FILE_PTR */

#ifndef STLSOFT_INCL_H_STDIO
# define STLSOFT_INCL_H_STDIO
# include <stdio.h>
#endif /* !STLSOFT_INCL_H_STDIO */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * typedefs
 */


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

namespace write_string_impl {

    ss_size_t
    write_string_3_(
        FILE*               stm
    ,   ss_char_a_t const*  s
    ,   ss_size_t           n
    )
    {
        static const ss_char_a_t s_empty[] = { 0 };

        if (0 == n)
        {
            s = s_empty;
        }

        return STLSOFT_NS_GLOBAL(fwrite)(s, n, sizeof(ss_char_a_t), stm);
    }
} // namespace write_string_impl
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

/** Writes a string (of type `T_string`) into a stream (of type `T_stream`)
 *
 * \tparam T_stream The type of the stream
 * \tparam T_string The type of the string
 *
 * \param stm The stream
 * \param s The string to be written
 *
 * \return The number of characters (not bytes) written to the stream, which
 *   may be less than that required if the complete write fails
 */
template <
    ss_typename_param_k T_stream
,   ss_typename_param_k T_string
>
ss_size_t
write_string(
    T_stream&       stm
,   T_string const& s
)
{
    return write_string_impl::write_string_3_(
        get_FILE_ptr(stm)
    ,   STLSOFT_NS_QUAL(c_str_data_a)(s)
    ,   STLSOFT_NS_QUAL(c_str_len_a)(s)
    );
}

/** Writes a C-style string into a stream (of type `T_stream`)
 *
 * \tparam T_stream The type of the stream
 * \tparam T_char The type of the character
 *
 * \param stm The stream
 * \param s Pointer to the first character to be written
 * \param n The number of characters in \c s
 *
 * \return The number of characters (not bytes) written to the stream, which
 *   may be less than \c n if the complete write fails
 */
template <
    ss_typename_param_k T_stream
,   ss_typename_param_k T_char
>
ss_size_t
write_string(
    T_stream&       stm
,   T_char const*   s
,   ss_size_t       n
)
{
    return write_string_impl::write_string_3_(
        get_FILE_ptr(stm)
    ,   s
    ,   n
    );
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

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_FILESYSTEM_IO_FUNCTIONS_HPP_WRITE_STRING */

/* ///////////////////////////// end of file //////////////////////////// */

