/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/controls/creation_functions.h
 *
 * Purpose: Control creation functions.
 *
 * Created: 7th May 2000
 * Updated: 1st November 2026
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


/** \file winstl/controls/creation_functions.h
 *
 * \brief [C, C++] Control creation functions
 *   (\ref group__library__Windows_Control "Windows Control" Library).
 */

#ifndef WINSTL_INCL_WINSTL_CONTROL_H_CREATION_FUNCTIONS
#define WINSTL_INCL_WINSTL_CONTROL_H_CREATION_FUNCTIONS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define WINSTL_VER_WINSTL_CONTROL_H_CREATION_FUNCTIONS_MAJOR       2
# define WINSTL_VER_WINSTL_CONTROL_H_CREATION_FUNCTIONS_MINOR       0
# define WINSTL_VER_WINSTL_CONTROL_H_CREATION_FUNCTIONS_REVISION    11
# define WINSTL_VER_WINSTL_CONTROL_H_CREATION_FUNCTIONS_EDIT        37
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

#ifdef __cplusplus
# ifndef STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_STRING_H_FWD
#  include <stlsoft/shims/access/string/fwd.h>
# endif /* !STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_STRING_H_FWD */
#endif /* __cplusplus */
#ifndef WINSTL_INCL_WINSTL_WINDOW_H_CREATION_FUNCTIONS
# include <winstl/window/creation_functions.h>
#endif /* !WINSTL_INCL_WINSTL_WINDOW_H_CREATION_FUNCTIONS */


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
 * helper functions
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
STLSOFT_INLINE
HMENU
winstl_C_control_creation_functions_Id2HMENU_(
    int     id
)
{
    union
    {
        ws_intptr_t     i;
        HMENU           h;
    } u;

    STLSOFT_STATIC_ASSERT(sizeof(u.i) == sizeof(u.h));

    u.i = id;

    return u.h;
}

#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

/**
 *
 * \ingroup group__library__Windows_Control
 */
STLSOFT_INLINE
void
winstl_C_setchildfont_(
    HWND    hwnd
,   HWND    hwndParent
)
{
    STLSOFT_SUPPRESS_UNUSED(hwnd);
    STLSOFT_SUPPRESS_UNUSED(hwndParent);

    /* ::SendMessage(hwndParent, WM_SETFONT, ::SendMessage(hwnd, WM_GETFONT, 0, 0L), 1); */
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
STLSOFT_INLINE
HWND
winstl_C_CreateStaticA(
    HWND                hwndParent
,   ws_char_a_t const*  name
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    HWND hwnd = winstl__CreateWindowA("STATIC", name, WS_CHILD | WS_VISIBLE, x, y, cx, cy, hwndParent, winstl_C_control_creation_functions_Id2HMENU_(id), NULL, NULL);

    winstl_C_setchildfont_(hwnd, hwndParent);

    return hwnd;
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
STLSOFT_INLINE
HWND
winstl_C_CreateStaticW(
    HWND                hwndParent
,   ws_char_w_t const*  name
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    HWND hwnd = winstl__CreateWindowW(L"STATIC", name, WS_CHILD | WS_VISIBLE, x, y, cx, cy, hwndParent, winstl_C_control_creation_functions_Id2HMENU_(id), NULL, NULL);

    winstl_C_setchildfont_(hwnd, hwndParent);

    return hwnd;
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
STLSOFT_INLINE
HWND
winstl_C_CreateStaticFrame(
    HWND    hwndParent
,   DWORD   frameStyle
,   int     x
,   int     y
,   int     cx
,   int     cy
,   int     id
)
{
    HWND hwnd;

    WINSTL_ASSERT(SS_BLACKFRAME == frameStyle || SS_GRAYFRAME == frameStyle || SS_WHITEFRAME == frameStyle || SS_ETCHEDFRAME == frameStyle);

    hwnd = winstl__CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE | frameStyle, x, y, cx, cy, hwndParent, winstl_C_control_creation_functions_Id2HMENU_(id), NULL, NULL);

    winstl_C_setchildfont_(hwnd, hwndParent);

    return hwnd;
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
STLSOFT_INLINE
HWND
winstl_C_CreateEditA(
    HWND                hwndParent
,   ws_char_a_t const*  text
,   DWORD               editStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl__CreateWindowA("EDIT", text, WS_CHILD | WS_VISIBLE | WS_TABSTOP | (0xFFFF & editStyle), x, y, cx, cy, hwndParent, winstl_C_control_creation_functions_Id2HMENU_(id), NULL, NULL);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
STLSOFT_INLINE
HWND
winstl_C_CreateEditW(
    HWND                hwndParent
,   ws_char_w_t const*  text
,   DWORD               editStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl__CreateWindowW(L"EDIT", text, WS_CHILD | WS_VISIBLE | WS_TABSTOP | (0xFFFF & editStyle), x, y, cx, cy, hwndParent, winstl_C_control_creation_functions_Id2HMENU_(id), NULL, NULL);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
STLSOFT_INLINE
HWND
winstl_C_CreateCheckboxA(
    HWND                hwndParent
,   ws_char_a_t const*  name
,   DWORD               buttonStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl__CreateWindowA("BUTTON", name, WS_CHILD | WS_VISIBLE | WS_TABSTOP | (0xFFFF & buttonStyle), x, y, cx, cy, hwndParent, winstl_C_control_creation_functions_Id2HMENU_(id), NULL, NULL);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
STLSOFT_INLINE
HWND
winstl_C_CreateCheckboxW(
    HWND                hwndParent
,   ws_char_w_t const*  name
,   DWORD               buttonStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl__CreateWindowW(L"BUTTON", name, WS_CHILD | WS_VISIBLE | WS_TABSTOP | (0xFFFF & buttonStyle), x, y, cx, cy, hwndParent, winstl_C_control_creation_functions_Id2HMENU_(id), NULL, NULL);
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifdef STLSOFT_DOCUMENTATION_SKIP_SECTION
namespace winstl
{
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * C++ functions
 */

#ifdef __cplusplus

/**
 *
 * \ingroup group__library__Windows_Control
 */
inline
HWND
winstl_C_CreateStatic(
    HWND                hwndParent
,   ws_char_a_t const*  name
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateStaticA(hwndParent, name, x, y, cx, cy, id);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
inline
HWND
winstl_C_CreateStatic(
    HWND                hwndParent
,   ws_char_w_t const*  name
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateStaticW(hwndParent, name, x, y, cx, cy, id);
}


/**
 *
 * \ingroup group__library__Windows_Control
 */
inline
HWND
winstl_C_CreateEdit(
    HWND                hwndParent
,   ws_char_a_t const*  text
,   DWORD               editStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateEditA(hwndParent, text, editStyle, x, y, cx, cy, id);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
inline
HWND
winstl_C_CreateEdit(
    HWND                hwndParent
,   ws_char_w_t const*  text
,   DWORD               editStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateEditW(hwndParent, text, editStyle, x, y, cx, cy, id);
}


/**
 *
 * \ingroup group__library__Windows_Control
 */
inline
HWND
winstl_C_CreateCheckbox(
    HWND                hwndParent
,   ws_char_a_t const*  name
,   DWORD               buttonStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateCheckboxA(hwndParent, name, buttonStyle, x, y, cx, cy, id);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
inline
HWND
winstl_C_CreateCheckbox(
    HWND                hwndParent
,   ws_char_w_t const*  name
,   DWORD               buttonStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateCheckboxW(hwndParent, name, buttonStyle, x, y, cx, cy, id);
}


/**
 *
 * \ingroup group__library__Windows_Control
 */
template <ss_typename_param_k S>
inline
HWND
CreateStatic(
    HWND        hwndParent
,   S const&    name
,   int         x
,   int         y
,   int         cx
,   int         cy
,   int         id
)
{
    return winstl_C_CreateStatic(hwndParent, STLSOFT_NS_QUAL(c_str_ptr)(name), x, y, cx, cy, id);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
template <ss_typename_param_k S>
inline
HWND
CreateStatic(
    HWND        hwndParent
,   S const&    name
,   RECT const& rc
,   int         id
)
{
    return winstl_C_CreateStatic(hwndParent, STLSOFT_NS_QUAL(c_str_ptr)(name), rc.left, rc.top, (rc.right - rc.left), (rc.bottom - rc.top), id);
}


/**
 *
 * \ingroup group__library__Windows_Control
 */
template <ss_typename_param_k S>
inline
HWND
CreateEdit
    HWND        hwndParent
,   S const&    text
,   DWORD       editStyle
,   int         x
,   int         y
,   int         cx
,   int         cy
,   int         id
)
{
    return winstl_C_CreateEdit(hwndParent, STLSOFT_NS_QUAL(c_str_ptr)(text), editStyle, x, y, cx, cy, id);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
template <ss_typename_param_k S>
inline
HWND
CreateEdit(
    HWND        hwndParent
,   S const&    text
,   DWORD       editStyle
,   RECT const& rc
,   int         id
)
{
    return winstl_C_CreateEdit(hwndParent, STLSOFT_NS_QUAL(c_str_ptr)(text), editStyle, rc.left, rc.top, (rc.right - rc.left), (rc.bottom - rc.top), id);
}


/**
 *
 * \ingroup group__library__Windows_Control
 */
inline
HWND
CreateStaticFrame(
    HWND    hwndParent
,   DWORD   frameStyle
,   int     x
,   int     y
,   int     cx
,   int     cy
,   int     id = -1
)
{
    return winstl_C_CreateStaticFrame(hwndParent, frameStyle, x, y, cx, cy, id);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
inline
HWND
CreateStaticFrame(
    HWND        hwndParent
,   DWORD       frameStyle
,   RECT const& rc
,   int         id = -1
)
{
    return CreateStaticFrame(hwndParent, frameStyle, rc.left, rc.top, (rc.right - rc.left), (rc.bottom - rc.top), id);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
template <ss_typename_param_k S>
inline
HWND
CreateCheckbox(
    HWND        hwndParent
,   S const&    name
,   DWORD       buttonStyle
,   int         x
,   int         y
,   int         cx
,   int         cy
,   int         id
)
{
    return winstl_C_CreateCheckbox(hwndParent, STLSOFT_NS_QUAL(c_str_ptr)(name), buttonStyle, x, y, cx, cy, id);
}

/**
 *
 * \ingroup group__library__Windows_Control
 */
template <ss_typename_param_k S>
inline
HWND
CreateCheckbox(
    HWND        hwndParent
,   S const&    name
,   DWORD       buttonStyle
,   RECT const& rc
,   int         id
)
{
    return winstl_C_CreateCheckbox(hwndParent, STLSOFT_NS_QUAL(c_str_ptr)(name), buttonStyle, rc.left, rc.top, (rc.right - rc.left), (rc.bottom - rc.top), id);
}
#endif /* __cplusplus */

/* /////////////////////////////////////////////////////////////////////////
 * backwards compatibility
 *
 * Retained, deprecated, until at least STLSoft 1.13. The compiler message
 * names the winstl_C_Create* function, or winstl_C_setchildfont_, that the
 * wrapper calls.
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

/** \deprecated Use winstl_C_setchildfont_
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__setchildfont_, winstl_C_setchildfont_)
STLSOFT_INLINE
void
winstl__setchildfont_(
    HWND    hwnd
,   HWND    hwndParent
)
{
    winstl_C_setchildfont_(hwnd, hwndParent);
}

/** \deprecated Use winstl_C_CreateStaticA
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateStaticA, winstl_C_CreateStaticA)
STLSOFT_INLINE
HWND
winstl__CreateStaticA(
    HWND                hwndParent
,   ws_char_a_t const*  name
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateStaticA(hwndParent, name, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateStaticW
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateStaticW, winstl_C_CreateStaticW)
STLSOFT_INLINE
HWND
winstl__CreateStaticW(
    HWND                hwndParent
,   ws_char_w_t const*  name
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateStaticW(hwndParent, name, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateStaticFrame
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateStaticFrame, winstl_C_CreateStaticFrame)
STLSOFT_INLINE
HWND
winstl__CreateStaticFrame(
    HWND    hwndParent
,   DWORD   frameStyle
,   int     x
,   int     y
,   int     cx
,   int     cy
,   int     id
)
{
    return winstl_C_CreateStaticFrame(hwndParent, frameStyle, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateEditA
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateEditA, winstl_C_CreateEditA)
STLSOFT_INLINE
HWND
winstl__CreateEditA(
    HWND                hwndParent
,   ws_char_a_t const*  text
,   DWORD               editStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateEditA(hwndParent, text, editStyle, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateEditW
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateEditW, winstl_C_CreateEditW)
STLSOFT_INLINE
HWND
winstl__CreateEditW(
    HWND                hwndParent
,   ws_char_w_t const*  text
,   DWORD               editStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateEditW(hwndParent, text, editStyle, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateCheckboxA
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateCheckboxA, winstl_C_CreateCheckboxA)
STLSOFT_INLINE
HWND
winstl__CreateCheckboxA(
    HWND                hwndParent
,   ws_char_a_t const*  name
,   DWORD               buttonStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateCheckboxA(hwndParent, name, buttonStyle, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateCheckboxW
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateCheckboxW, winstl_C_CreateCheckboxW)
STLSOFT_INLINE
HWND
winstl__CreateCheckboxW(
    HWND                hwndParent
,   ws_char_w_t const*  name
,   DWORD               buttonStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateCheckboxW(hwndParent, name, buttonStyle, x, y, cx, cy, id);
}

#ifdef __cplusplus

/** \deprecated Use winstl_C_CreateStatic
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateStatic, winstl_C_CreateStatic)
STLSOFT_INLINE
HWND
winstl__CreateStatic(
    HWND                hwndParent
,   ws_char_a_t const*  name
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateStatic(hwndParent, name, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateStatic
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateStatic, winstl_C_CreateStatic)
STLSOFT_INLINE
HWND
winstl__CreateStatic(
    HWND                hwndParent
,   ws_char_w_t const*  name
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateStatic(hwndParent, name, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateEdit
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateEdit, winstl_C_CreateEdit)
STLSOFT_INLINE
HWND
winstl__CreateEdit(
    HWND                hwndParent
,   ws_char_a_t const*  text
,   DWORD               editStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateEdit(hwndParent, text, editStyle, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateEdit
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateEdit, winstl_C_CreateEdit)
STLSOFT_INLINE
HWND
winstl__CreateEdit(
    HWND                hwndParent
,   ws_char_w_t const*  text
,   DWORD               editStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateEdit(hwndParent, text, editStyle, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateCheckbox
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateCheckbox, winstl_C_CreateCheckbox)
STLSOFT_INLINE
HWND
winstl__CreateCheckbox(
    HWND                hwndParent
,   ws_char_a_t const*  name
,   DWORD               buttonStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateCheckbox(hwndParent, name, buttonStyle, x, y, cx, cy, id);
}

/** \deprecated Use winstl_C_CreateCheckbox
 */
STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl__CreateCheckbox, winstl_C_CreateCheckbox)
STLSOFT_INLINE
HWND
winstl__CreateCheckbox(
    HWND                hwndParent
,   ws_char_w_t const*  name
,   DWORD               buttonStyle
,   int                 x
,   int                 y
,   int                 cx
,   int                 cy
,   int                 id
)
{
    return winstl_C_CreateCheckbox(hwndParent, name, buttonStyle, x, y, cx, cy, id);
}

#endif /* __cplusplus */

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

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !WINSTL_INCL_WINSTL_CONTROL_H_CREATION_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */

