/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/shims/logical/is_null/std/shared_ptr.hpp
 *
 * Purpose: Generic adapted case of is_null shim std::shared_ptr<>.
 *
 * Created: 4th October 2016
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2016-2019, Matthew Wilson and Synesis Software
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


/* STLSOFT:C++98:FILE_DEPRECATED */
/* STLSOFT:C++03:FILE_DEPRECATED */

/** \file stlsoft/shims/logical/is_null/std/shared_ptr.hpp
 *
 * \brief [C++] Generic adapted case of is_null shim std::shared_ptr<>
 *   (\ref group__concept__Shim__Logical__is_null "is_null Logical Shim").
 */

#ifndef STLSOFT_INCL_STLSOFT_SHIMS_LOGICAL_IS_NULL_STD_HPP_SHARED_PTR
#define STLSOFT_INCL_STLSOFT_SHIMS_LOGICAL_IS_NULL_STD_HPP_SHARED_PTR

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_SHIMS_LOGICAL_IS_NULL_STD_HPP_SHARED_PTR_MAJOR     1
# define STLSOFT_VER_STLSOFT_SHIMS_LOGICAL_IS_NULL_STD_HPP_SHARED_PTR_MINOR     0
# define STLSOFT_VER_STLSOFT_SHIMS_LOGICAL_IS_NULL_STD_HPP_SHARED_PTR_REVISION  3
# define STLSOFT_VER_STLSOFT_SHIMS_LOGICAL_IS_NULL_STD_HPP_SHARED_PTR_EDIT      8
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

# ifndef STLSOFT_INCL_MEMORY
#  define STLSOFT_INCL_MEMORY
#  include <memory>
# endif /* !STLSOFT_INCL_MEMORY */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* !STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * shims
 */

/** is_null shim
 *
 * \ingroup group__library__SmartPointer
 */
template <ss_typename_param_k T>
inline
bool
is_null(
    STLSOFT_NS_QUAL_STD(shared_ptr)<T> const& p
) STLSOFT_NOEXCEPT
{
    return NULL == p.get();
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} // namespace stlsoft
#endif /* !STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

/* ////////////////////////////////////////////////////////////////////// */

#endif /* !STLSOFT_INCL_STLSOFT_SHIMS_LOGICAL_IS_NULL_STD_HPP_SHARED_PTR */

/* ///////////////////////////// end of file //////////////////////////// */

