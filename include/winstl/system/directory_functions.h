/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/system/directory_functions.h
 *
 * Purpose: Directory functions.
 *
 * Created: 29th January 2013
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


/** \file winstl/system/directory_functions.h
 *
 * \brief [C++] Directory functions
 *   (\ref group__library__System "System" Library).
 */

#ifndef WINSTL_INCL_WINSTL_SYSTEM_H_DIRECTORY_FUNCTIONS
#define WINSTL_INCL_WINSTL_SYSTEM_H_DIRECTORY_FUNCTIONS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define WINSTL_VER_WINSTL_SYSTEM_H_DIRECTORY_FUNCTIONS_MAJOR       1
# define WINSTL_VER_WINSTL_SYSTEM_H_DIRECTORY_FUNCTIONS_MINOR       0
# define WINSTL_VER_WINSTL_SYSTEM_H_DIRECTORY_FUNCTIONS_REVISION    8
# define WINSTL_VER_WINSTL_SYSTEM_H_DIRECTORY_FUNCTIONS_EDIT        17
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

#ifndef WINSTL_API_INTERNAL_H_get_home_directory_
# include <winstl/api/internal/get_home_directory_.h>
#endif /* WINSTL_API_INTERNAL_H_get_home_directory_ */

#ifndef WINSTL_INCL_WINSTL_API_external_h_SystemInformation
# include <winstl/api/external/SystemInformation.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_SystemInformation */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_memfns
# include <stlsoft/api/external/memfns.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_memfns */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#if !defined(WINSTL_NO_NAMESPACE) && \
    !defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
# if defined(STLSOFT_NO_NAMESPACE)
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
 * API functions
 */

STLSOFT_INLINE
ws_size_t
winstl_C_get_home_directory_a(
    ws_char_a_t buffer[]
,   ws_size_t   cchBuffer
)
{
    return WINSTL_API_INTERNAL_System_get_home_directory_a_(buffer, STLSOFT_STATIC_CAST(DWORD, cchBuffer));
}

STLSOFT_INLINE
ws_size_t
winstl_C_get_home_directory_w(
    ws_char_w_t buffer[]
,   ws_size_t   cchBuffer
)
{
    return WINSTL_API_INTERNAL_System_get_home_directory_w_(buffer, STLSOFT_STATIC_CAST(DWORD, cchBuffer));
}


/* /////////////////////////////////////////////////////////////////////////
 * API functions (C++)
 */

#if defined(__cplusplus)

inline
ws_size_t
get_home_directory(
    ws_char_a_t buffer[]
,   ws_size_t   cchBuffer
)
{
    return winstl_C_get_home_directory_a(buffer, cchBuffer);
}

inline
ws_size_t
get_home_directory(
    ws_char_w_t buffer[]
,   ws_size_t   cchBuffer
)
{
    return winstl_C_get_home_directory_w(buffer, cchBuffer);
}
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

template <ss_size_t N>
inline
ws_size_t
get_home_directory(
    ws_char_a_t   (&ar)[N]
)
{
    return get_home_directory(&ar[0], N);
}

template <ss_size_t N>
inline
ws_size_t
get_home_directory(
    ws_char_w_t   (&ar)[N]
)
{
    return get_home_directory(&ar[0], N);
}
# endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

#ifndef WINSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
} /* namespace winstl */
# else
} /* namespace winstl_project */
} /* namespace stlsoft */
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !WINSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !WINSTL_INCL_WINSTL_SYSTEM_H_DIRECTORY_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */

