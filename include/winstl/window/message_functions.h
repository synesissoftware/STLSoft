/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/window/message_functions.h (originally MWBase.h, ::SynesisWin)
 *
 * Purpose: Message functions.
 *
 * Created: 7th May 2000
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


/** \file winstl/window/message_functions.h
 *
 * \brief [C, C++] Message functions
 *   (\ref group__library__Windows_Window "Windows Window" Library).
 */

#ifndef WINSTL_INCL_WINSTL_WINDOW_H_MESSAGE_FUNCTIONS
#define WINSTL_INCL_WINSTL_WINDOW_H_MESSAGE_FUNCTIONS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define WINSTL_VER_WINSTL_WINDOW_H_MESSAGE_FUNCTIONS_MAJOR     4
# define WINSTL_VER_WINSTL_WINDOW_H_MESSAGE_FUNCTIONS_MINOR     0
# define WINSTL_VER_WINSTL_WINDOW_H_MESSAGE_FUNCTIONS_REVISION  9
# define WINSTL_VER_WINSTL_WINDOW_H_MESSAGE_FUNCTIONS_EDIT      55
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

#ifndef WINSTL_INCL_WINSTL_API_external_h_WindowsAndMessages
# include <winstl/api/external/WindowsAndMessages.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_WindowsAndMessages */


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
 * C functions
 */

STLSOFT_INLINE
LRESULT
winstl_C_SendMessageA(
    HWND    hwnd
,   UINT    uMsg
,   WPARAM  wParam
,   LPARAM  lParam
)
{
    return WINSTL_API_EXTERNAL_WindowsAndMessages_SendMessageA(hwnd, uMsg, wParam, lParam);
}

STLSOFT_INLINE
LRESULT
winstl_C_SendMessageW(
    HWND    hwnd
,   UINT    uMsg
,   WPARAM  wParam
,   LPARAM  lParam
)
{
    return WINSTL_API_EXTERNAL_WindowsAndMessages_SendMessageW(hwnd, uMsg, wParam, lParam);
}

STLSOFT_INLINE
LRESULT
winstl_C_SendMessage(
    HWND    hwnd
,   UINT    uMsg
,   WPARAM  wParam
,   LPARAM  lParam
)
{
    return WINSTL_API_EXTERNAL_WindowsAndMessages_SendMessage(hwnd, uMsg, wParam, lParam);
}


/* /////////////////////////////////////////////////////////////////////////
 * C++ functions
 */

#if !defined(WINSTL_NO_NAMESPACE) &&\
    !defined(STLSOFT_COMPILER_IS_BORLAND)

inline
LRESULT
SendMessageA(
    HWND    hwnd
,   UINT    uMsg
,   WPARAM  wParam
,   LPARAM  lParam
)
{
    return winstl_C_SendMessageA(hwnd, uMsg, wParam, lParam);
}

inline
LRESULT
SendMessageW(
    HWND    hwnd
,   UINT    uMsg
,   WPARAM  wParam
,   LPARAM  lParam
)
{
    return winstl_C_SendMessageW(hwnd, uMsg, wParam, lParam);
}
#endif /* !WINSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * backwards compatibility
 *
 * Retained, deprecated, until at least STLSoft 1.13. The compiler message
 * names the winstl_C_SendMessage* function that the wrapper calls.
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

/** \deprecated Use winstl_C_SendMessageA
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__SendMessageA, winstl_C_SendMessageA)
STLSOFT_INLINE
LRESULT
winstl__SendMessageA(
    HWND    hwnd
,   UINT    uMsg
,   WPARAM  wParam
,   LPARAM  lParam
)
{
    return winstl_C_SendMessageA(hwnd, uMsg, wParam, lParam);
}

/** \deprecated Use winstl_C_SendMessageW
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__SendMessageW, winstl_C_SendMessageW)
STLSOFT_INLINE
LRESULT
winstl__SendMessageW(
    HWND    hwnd
,   UINT    uMsg
,   WPARAM  wParam
,   LPARAM  lParam
)
{
    return winstl_C_SendMessageW(hwnd, uMsg, wParam, lParam);
}

/** \deprecated Use winstl_C_SendMessage
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__SendMessage, winstl_C_SendMessage)
STLSOFT_INLINE
LRESULT
winstl__SendMessage(
    HWND    hwnd
,   UINT    uMsg
,   WPARAM  wParam
,   LPARAM  lParam
)
{
    return winstl_C_SendMessage(hwnd, uMsg, wParam, lParam);
}

#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * namespace
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

#endif /* !WINSTL_INCL_WINSTL_WINDOW_H_MESSAGE_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */

