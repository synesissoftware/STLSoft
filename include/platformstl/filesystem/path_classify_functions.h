/* /////////////////////////////////////////////////////////////////////////
 * File:    platformstl/filesystem/path_classify_functions.h
 *
 * Purpose: Platform intersecting path classification functions (R14).
 *
 * Created: 20th October 2026
 * Updated: 20th October 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2026, Matthew Wilson and Synesis Information Systems
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


/** \file platformstl/filesystem/path_classify_functions.h
 *
 * \brief [C, C++] Intersecting path classification functions
 *   (\ref group__library__FileSystem "File System" Library).
 *
 * Portable kinds, flags, and predicates per the PlatformSTL path-classify
 * contract. Drive / UNC forms are host-only (use WinSTL); on Windows they
 * map to \c platformstl_C_PathType_Invalid rather than portable names.
 */

#ifndef PLATFORMSTL_INCL_PLATFORMSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS
#define PLATFORMSTL_INCL_PLATFORMSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define PLATFORMSTL_VER_PLATFORMSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS_MAJOR     1
# define PLATFORMSTL_VER_PLATFORMSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS_MINOR     0
# define PLATFORMSTL_VER_PLATFORMSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS_REVISION  1
# define PLATFORMSTL_VER_PLATFORMSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS_EDIT      1
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef PLATFORMSTL_INCL_PLATFORMSTL_H_PLATFORMSTL
# include <platformstl/platformstl.h>
#endif /* !PLATFORMSTL_INCL_PLATFORMSTL_H_PLATFORMSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef STLSOFT_INCL_STLSOFT_STRING_H_STRING_SLICE
# include <stlsoft/string/string_slice.h>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_H_STRING_SLICE */

#if defined(PLATFORMSTL_OS_IS_UNIX)
# ifndef UNIXSTL_INCL_UNIXSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS
#  include <unixstl/filesystem/path_classify_functions.h>
# endif /* !UNIXSTL_INCL_UNIXSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS */
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)
# ifndef WINSTL_INCL_WINSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS
#  include <winstl/filesystem/path_classify_functions.h>
# endif /* !WINSTL_INCL_WINSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS */
#else /* ? operating system */
# error Operating system not discriminated
#endif /* operating system */


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

/** Portable path-classification kinds (intersecting set). Numeric layout
 * aligns with UNIXSTL / WinSTL through \c HomeRooted; reserved_* slots
 * correspond to WinSTL drive / UNC kinds but are <b>not</b> returned by
 * this API — host-only inputs become \c Invalid.
 */
enum platformstl_C_path_classification_t
{
        platformstl_C_PathType_MIN_VALUE            =   -10000

    ,   platformstl_C_PathType_InvalidSlashRuns     =   -3
    ,   platformstl_C_PathType_InvalidChars         =   -2
    ,   platformstl_C_PathType_Invalid              =   -1
    ,   platformstl_C_PathType_Unknown              =   0
    ,   platformstl_C_PathType_Empty
    ,   platformstl_C_PathType_Relative
    ,   platformstl_C_PathType_SlashRooted
    ,   platformstl_C_PathType_reserved_1           /*!< host-only (drive-relative) */
    ,   platformstl_C_PathType_reserved_2           /*!< host-only (drive-rooted) */
    ,   platformstl_C_PathType_reserved_3           /*!< host-only (UNC incomplete) */
    ,   platformstl_C_PathType_reserved_4           /*!< host-only (UNC rooted) */
    ,   platformstl_C_PathType_HomeRooted

    /* no enumerator to be placed AFTER this one */
    ,   platformstl_C_PathType_MAX_VALUE
};
#ifndef __cplusplus
typedef enum platformstl_C_path_classification_t            platformstl_C_path_classification_t;
#endif /* !__cplusplus */

#if defined(PLATFORMSTL_OS_IS_UNIX)

typedef unixstl_C_path_classification_results_m_t           platformstl_C_path_classification_results_m_t;
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

typedef winstl_C_path_classification_results_m_t            platformstl_C_path_classification_results_m_t;
typedef winstl_C_path_classification_results_w_t            platformstl_C_path_classification_results_w_t;
#else /* ? operating system */

# error Operating system not discriminated
#endif /* operating system */


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

#define PLATFORMSTL_PATH_CLASSIFY_F_NONE                    (0)

#define PLATFORMSTL_PATH_CLASSIFY_F_IGNORESLASHRUNS         (0x00000001)
#define PLATFORMSTL_PATH_CLASSIFY_F_IGNOREINVALIDCHARS      (0x00000002)
#define PLATFORMSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME      (0x00000004)

/** Portable flag mask (UNIXSTL intersection; excludes WinSTL-only bits). */
#define PLATFORMSTL_PATH_CLASSIFY_F_MASK_                   (0x00000007)


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

# if defined(PLATFORMSTL_OS_IS_WINDOWS)

STLSOFT_INLINE
platformstl_C_path_classification_t
platformstl_C_path_classification_from_winstl_(
    winstl_C_path_classification_t  pc
)
{
    switch (pc)
    {
    case winstl_C_PathType_InvalidSlashRuns:
    case winstl_C_PathType_InvalidChars:
    case winstl_C_PathType_Invalid:
    case winstl_C_PathType_Unknown:
    case winstl_C_PathType_Empty:
    case winstl_C_PathType_Relative:
    case winstl_C_PathType_SlashRooted:
    case winstl_C_PathType_HomeRooted:

        return (platformstl_C_path_classification_t)(int)pc;
    default:

        /* Drive* / Unc* — unsupported in the portable intersection. */
        return platformstl_C_PathType_Invalid;
    }
}
# endif /* PLATFORMSTL_OS_IS_WINDOWS */
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

STLSOFT_INLINE
platformstl_C_path_classification_t
platformstl_C_path_classify_m(
    char const*                                     s
,   size_t                                          cch
,   int                                             parseFlags
,   platformstl_C_path_classification_results_m_t*  results
)
{
    PLATFORMSTL_MESSAGE_ASSERT(
        "unrecognised parsing flags"
    ,   0 == (~PLATFORMSTL_PATH_CLASSIFY_F_MASK_ & parseFlags)
    );

#if defined(PLATFORMSTL_OS_IS_UNIX)

    return (platformstl_C_path_classification_t)(int)unixstl_C_path_classify_m(s, cch, parseFlags, results);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    return platformstl_C_path_classification_from_winstl_(
        winstl_C_path_classify_m(s, cch, parseFlags, results)
    );
#else /* ? operating system */

# error Operating system not discriminated
#endif /* operating system */
}

#if defined(PLATFORMSTL_OS_IS_WINDOWS)

STLSOFT_INLINE
platformstl_C_path_classification_t
platformstl_C_path_classify_w(
    wchar_t const*                                  s
,   size_t                                          cch
,   int                                             parseFlags
,   platformstl_C_path_classification_results_w_t*  results
)
{
    PLATFORMSTL_MESSAGE_ASSERT(
        "unrecognised parsing flags"
    ,   0 == (~PLATFORMSTL_PATH_CLASSIFY_F_MASK_ & parseFlags)
    );

    return platformstl_C_path_classification_from_winstl_(
        winstl_C_path_classify_w(s, cch, parseFlags, results)
    );
}
#endif /* PLATFORMSTL_OS_IS_WINDOWS */

STLSOFT_INLINE
platformstl_C_path_classification_t
platformstl_C_path_classify_root_m(
    char const*                     s
,   size_t                          cch
,   int                             parseFlags
,   stlsoft_C_string_slice_m_t*     root
)
{
    PLATFORMSTL_MESSAGE_ASSERT(
        "unrecognised parsing flags"
    ,   0 == (~PLATFORMSTL_PATH_CLASSIFY_F_MASK_ & parseFlags)
    );

#if defined(PLATFORMSTL_OS_IS_UNIX)

    return (platformstl_C_path_classification_t)(int)unixstl_C_path_classify_root_m(s, cch, parseFlags, root);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    return platformstl_C_path_classification_from_winstl_(
        winstl_C_path_classify_root_m(s, cch, parseFlags, root)
    );
#else /* ? operating system */

# error Operating system not discriminated
#endif /* operating system */
}

#if defined(PLATFORMSTL_OS_IS_WINDOWS)

STLSOFT_INLINE
platformstl_C_path_classification_t
platformstl_C_path_classify_root_w(
    wchar_t const*                  s
,   size_t                          cch
,   int                             parseFlags
,   stlsoft_C_string_slice_w_t*     root
)
{
    PLATFORMSTL_MESSAGE_ASSERT(
        "unrecognised parsing flags"
    ,   0 == (~PLATFORMSTL_PATH_CLASSIFY_F_MASK_ & parseFlags)
    );

    return platformstl_C_path_classification_from_winstl_(
        winstl_C_path_classify_root_w(s, cch, parseFlags, root)
    );
}

#endif /* PLATFORMSTL_OS_IS_WINDOWS */

STLSOFT_INLINE
STLSOFT_NS_QUAL(ss_truthy_t)
platformstl_C_path_is_rooted(
    platformstl_C_path_classification_t pc
)
{
    switch (pc)
    {
    case platformstl_C_PathType_SlashRooted:
    case platformstl_C_PathType_HomeRooted:

        return 1;
    default:

        return 0;
    }
}

/** Absolute in the <b>host</b> sense (R1 / R2): on Unix, identical to
 * \c platformstl_C_path_is_rooted; on Windows, \c HomeRooted only among
 * portable kinds (\c SlashRooted is rooted but <b>not</b> absolute).
 *
 * Portable code must not assume absolute ≡ rooted when targeting Windows.
 */
STLSOFT_INLINE
STLSOFT_NS_QUAL(ss_truthy_t)
platformstl_C_path_is_absolute(
    platformstl_C_path_classification_t pc
)
{
#if defined(PLATFORMSTL_OS_IS_UNIX)

    return platformstl_C_path_is_rooted(pc);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    switch (pc)
    {
    case platformstl_C_PathType_HomeRooted:

        return 1;
    default:

        return 0;
    }
#else /* ? operating system */

# error Operating system not discriminated
#endif /* operating system */
}

#ifdef __cplusplus

inline
platformstl_C_path_classification_t
platformstl_C_path_classify(
    char const*                                     s
,   size_t                                          cch
,   int                                             parseFlags
,   platformstl_C_path_classification_results_m_t*  results
)
{
    return platformstl_C_path_classify_m(s, cch, parseFlags, results);
}

inline
platformstl_C_path_classification_t
platformstl_C_path_classify_root(
    char const*                     s
,   size_t                          cch
,   int                             parseFlags
,   stlsoft_C_string_slice_m_t*     root
)
{
    return platformstl_C_path_classify_root_m(s, cch, parseFlags, root);
}

# if defined(PLATFORMSTL_OS_IS_WINDOWS)

inline
platformstl_C_path_classification_t
platformstl_C_path_classify(
    wchar_t const*                                  s
,   size_t                                          cch
,   int                                             parseFlags
,   platformstl_C_path_classification_results_w_t*  results
)
{
    return platformstl_C_path_classify_w(s, cch, parseFlags, results);
}

inline
platformstl_C_path_classification_t
platformstl_C_path_classify_root(
    wchar_t const*                  s
,   size_t                          cch
,   int                             parseFlags
,   stlsoft_C_string_slice_w_t*     root
)
{
    return platformstl_C_path_classify_root_w(s, cch, parseFlags, root);
}
# endif /* PLATFORMSTL_OS_IS_WINDOWS */
#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef PLATFORMSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
/* There is no stlsoft namespace, so must define ::platformstl */
namespace platformstl
{
# else
/* Define stlsoft::platformstl_project */
namespace stlsoft
{
namespace platformstl_project
{
# endif /* STLSOFT_NO_NAMESPACE */

#ifndef __cplusplus
# error
#endif /* !__cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * C++ types
 */

typedef platformstl_C_path_classification_t                 path_classification_t;
typedef platformstl_C_path_classification_results_m_t       path_classification_results_m_t;
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
typedef platformstl_C_path_classification_results_w_t       path_classification_results_w_t;
#endif /* PLATFORMSTL_OS_IS_WINDOWS */


/* /////////////////////////////////////////////////////////////////////////
 * C++ API functions
 */

/**
 *
 * \param path
 *
 * \note The function does NOT use string-access shims to elicit
 *   from \c path the C-style string pointer and length, because the API
 *   returns results in slices, whose contents could be invalidated. Instead
 *   the function assumes that \c path is of a notional type that provides
 *   the methods <code>data()</code> and <code>size()</code>
 */
template<
    ss_typename_param_k T_string
,   ss_typename_param_k T_results
>
path_classification_t
path_classify(
    T_string const&         path
,   int                     parseFlags
,   T_results*              results
)
{
    PLATFORMSTL_ASSERT(0 == path.size() || ss_nullptr_k != path.data());

    return platformstl_C_path_classify(path.data(), path.size(), parseFlags, results);
}

template<
    ss_typename_param_k T_string
,   ss_typename_param_k T_results
>
path_classification_t
path_classify_root(
    T_string const&         path
,   int                     parseFlags
,   T_results*              results
)
{
    PLATFORMSTL_ASSERT(0 == path.size() || ss_nullptr_k != path.data());

    return platformstl_C_path_classify_root(path.data(), path.size(), parseFlags, results);
}

inline
bool
path_is_rooted(
    path_classification_t   pc
)
{
    return 0 != platformstl_C_path_is_rooted(pc);
}

inline
bool
path_is_absolute(
    path_classification_t   pc
)
{
    return 0 != platformstl_C_path_is_absolute(pc);
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
} /* namespace platformstl */
# else
} /* namespace platformstl_project */
} /* namespace stlsoft */
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !PLATFORMSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * backwards compatibility
 *
 * Older UPPER-case enumerator names are retained (as macros) until at
 * least STLSoft 1.13.
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

# define PLATFORMSTL_C_PathType_Empty                       platformstl_C_PathType_Empty
# define PLATFORMSTL_C_PathType_HomeRooted                  platformstl_C_PathType_HomeRooted
# define PLATFORMSTL_C_PathType_Invalid                     platformstl_C_PathType_Invalid
# define PLATFORMSTL_C_PathType_InvalidChars                platformstl_C_PathType_InvalidChars
# define PLATFORMSTL_C_PathType_InvalidSlashRuns            platformstl_C_PathType_InvalidSlashRuns
# define PLATFORMSTL_C_PathType_MAX_VALUE                   platformstl_C_PathType_MAX_VALUE
# define PLATFORMSTL_C_PathType_MIN_VALUE                   platformstl_C_PathType_MIN_VALUE
# define PLATFORMSTL_C_PathType_Relative                    platformstl_C_PathType_Relative
# define PLATFORMSTL_C_PathType_SlashRooted                 platformstl_C_PathType_SlashRooted
# define PLATFORMSTL_C_PathType_Unknown                     platformstl_C_PathType_Unknown
# define PLATFORMSTL_C_PathType_reserved_1                  platformstl_C_PathType_reserved_1
# define PLATFORMSTL_C_PathType_reserved_2                  platformstl_C_PathType_reserved_2
# define PLATFORMSTL_C_PathType_reserved_3                  platformstl_C_PathType_reserved_3
# define PLATFORMSTL_C_PathType_reserved_4                  platformstl_C_PathType_reserved_4
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !PLATFORMSTL_INCL_PLATFORMSTL_FILESYSTEM_H_PATH_CLASSIFY_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */
