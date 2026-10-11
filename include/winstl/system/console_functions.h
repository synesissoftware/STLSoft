/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/system/console_functions.h
 *
 * Purpose: Windows console functions.
 *
 * Created: 3rd December 2005
 * Updated: 11th October 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2005-2019, Matthew Wilson and Synesis Software
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


/** \file winstl/system/console_functions.h
 *
 * \brief [C, C++] Windows console functions.
 *   (\ref group__library__System "System" Library).
 */

#ifndef WINSTL_INCL_WINSTL_SYSTEM_H_CONSOLE_FUNCTIONS
#define WINSTL_INCL_WINSTL_SYSTEM_H_CONSOLE_FUNCTIONS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define WINSTL_VER_WINSTL_SYSTEM_H_CONSOLE_FUNCTIONS_MAJOR     2
# define WINSTL_VER_WINSTL_SYSTEM_H_CONSOLE_FUNCTIONS_MINOR     6
# define WINSTL_VER_WINSTL_SYSTEM_H_CONSOLE_FUNCTIONS_REVISION  2
# define WINSTL_VER_WINSTL_SYSTEM_H_CONSOLE_FUNCTIONS_EDIT      56
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

#if 0 ||\
    defined(STLSOFT_MINGW) ||\
    defined(_MSC_VER) ||\
    0
# ifndef STLSOFT_INCL_H_IO
#  define STLSOFT_INCL_H_IO
#  include <io.h>
# endif /* !STLSOFT_INCL_H_IO */
#endif
#ifndef STLSOFT_INCL_H_STDIO
# define STLSOFT_INCL_H_STDIO
# include <stdio.h>
#endif /* !STLSOFT_INCL_H_STDIO */

#ifndef WINSTL_INCL_WINSTL_API_external_h_Console
# include <winstl/api/external/Console.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_Console */
#ifndef WINSTL_INCL_WINSTL_API_external_h_DynamicLinkLibrary
# include <winstl/api/external/DynamicLinkLibrary.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_DynamicLinkLibrary */
#ifndef WINSTL_INCL_WINSTL_API_external_h_ErrorHandling
# include <winstl/api/external/ErrorHandling.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_ErrorHandling */
#ifndef WINSTL_INCL_WINSTL_API_external_h_FileManagement
# include <winstl/api/external/FileManagement.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_FileManagement */
#ifndef WINSTL_INCL_WINSTL_API_external_h_HandleAndObject
# include <winstl/api/external/HandleAndObject.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_HandleAndObject */

#ifndef STLSOFT_INCL_STLSOFT_MEMORY_H_AUTO_BUFFER
# include <stlsoft/memory/auto_buffer.h>
#endif /* !STLSOFT_INCL_STLSOFT_MEMORY_H_AUTO_BUFFER */
#ifndef STLSOFT_INCL_STLSOFT_STRING_H_STRING_SLICE
# include <stlsoft/string/string_slice.h>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_H_STRING_SLICE */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_memfns
# include <stlsoft/api/external/memfns.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_memfns */

#ifndef WINSTL_INCL_WINSTL_API_H_winstl_win32_winnt_
# include <winstl/api/winstl_win32_winnt_.h>
#endif /* !WINSTL_INCL_WINSTL_API_H_winstl_win32_winnt_ */


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
 * helpers
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

STLSOFT_INLINE
long
winstl_C_console_read_silent_character_from_(
    HANDLE h
)
{
    DWORD currMode;

    if (!WINSTL_API_EXTERNAL_Console_GetConsoleMode(h, &currMode) ||
        !WINSTL_API_EXTERNAL_Console_SetConsoleMode(h, 0))
    {
        return -1;
    }
    else
    {
        LONG c = -1;

        for (;;)
        {
            INPUT_RECORD    ir;
            DWORD           numRead;

            if (!WINSTL_API_EXTERNAL_Console_ReadConsoleInput(h, &ir, 1, &numRead))
            {
                c = -1;

                break;
            }
            else
            {
                if (0 == numRead)
                {
                    c = -1;

                    break;
                }
                else
                {
                    if (KEY_EVENT == ir.EventType)
                    {
                        if (ir.Event.KeyEvent.bKeyDown)
                        {
#ifdef UNICODE

                            if (0 != ir.Event.KeyEvent.uChar.UnicodeChar)
                            {
                                c = STLSOFT_C_CAST(long, ir.Event.KeyEvent.uChar.UnicodeChar);

                                break;
                            }
#else /* ? UNICODE */

                            if (0 != ir.Event.KeyEvent.uChar.AsciiChar)
                            {
                                c = STLSOFT_C_CAST(long, ir.Event.KeyEvent.uChar.AsciiChar);

                                break;
                            }
#endif /* UNICODE */
                        }
                    }
                }
            }
        }

        WINSTL_API_EXTERNAL_Console_SetConsoleMode(h, currMode);

        return c;
    }
}

STLSOFT_INLINE
ss_truthy_t
winstl_C_isatty_fd_(
    int fd
)
{
    int (*pfn_isatty)(int);

#if 0 ||\
    defined(STLSOFT_MINGW) ||\
    defined(_MSC_VER) ||\
    0

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>

    pfn_isatty  =   STLSOFT_NS_GLOBAL(_isatty);

# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
#else

    pfn_isatty  =   STLSOFT_NS_GLOBAL(isatty);
#endif

    return (*pfn_isatty)(fd);
}

STLSOFT_INLINE
ss_truthy_t
winstl_C_isatty_stm_(
    FILE* stm
)
{
    int (*pfn_fileno)(FILE*);

#if defined(_MSC_VER)

# include <stlsoft/internal/warnings/push/suppress_deprecation_.h>

    pfn_fileno  =   STLSOFT_NS_GLOBAL(_fileno);

# include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
#else

    pfn_fileno  =   STLSOFT_NS_GLOBAL(fileno);
#endif

    int const fd = (*pfn_fileno)(stm);

    return winstl_C_isatty_fd_(fd);
}
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

/** Evalutes the current width of the console.
 *
 * \ingroup group__library__System
 */
STLSOFT_INLINE
ws_size_t
winstl_C_get_console_width(void)
{
    HANDLE hStdOut = WINSTL_API_EXTERNAL_Console_GetStdHandle(STD_OUTPUT_HANDLE);

    if (INVALID_HANDLE_VALUE != hStdOut)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if (WINSTL_API_EXTERNAL_Console_GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            return csbi.dwMaximumWindowSize.X;
        }
    }

#ifdef STLSOFT_DEBUG

    WINSTL_API_EXTERNAL_ErrorHandling_GetLastError();
#endif /* STLSOFT_DEBUG */

    return ~stlsoft_static_cast(ws_size_t, 0);
}

#if 1 &&\
    !defined(STLSOFT_DOCUMENTATION_SKIP_SECTION) &&\
    (   WINSTL_WIN32_WINNT < 0x0500 ||\
        (   defined(STLSOFT_COMPILER_IS_BORLAND) &&\
            !defined(CONSOLE_NO_SELECTION))) &&\
    1

STLSOFT_INLINE
HWND
GetConsoleWindow()
{
    typedef HWND (WINAPI *GCW_t)();

    HMODULE Kernel32    =   WINSTL_API_EXTERNAL_DynamicLinkLibrary_LoadLibraryA("KERNEL32");
    GCW_t   pfn         =   stlsoft_reinterpret_cast(GCW_t, WINSTL_API_EXTERNAL_DynamicLinkLibrary_GetProcAddress(Kernel32, "GetConsoleWindow"));

    if (NULL == pfn)
    {
        return NULL;
    }
    else
    {
        HWND hwnd = (*pfn)();

        WINSTL_API_EXTERNAL_DynamicLinkLibrary_FreeLibrary(Kernel32);

        return hwnd;
    }
}
#endif /* _WIN32_WINNT */

/** Returns the window handle of the current console, or NULL if it cannot
 *    be found
 *
 * \ingroup group__library__System
 *
 * \warning This only works on Windows 2000, or later, operating systems. It
 *    will return \c nullptr on other operating systems.
 */
STLSOFT_INLINE
HWND
winstl_C_get_console_window(void)
{
    return GetConsoleWindow();
}

STLSOFT_INLINE
long
winstl_C_console_read_silent_character_from_stdin(void)
{
    HANDLE h = WINSTL_API_EXTERNAL_Console_GetStdHandle(STD_INPUT_HANDLE);

    return winstl_C_console_read_silent_character_from_(h);
}

STLSOFT_INLINE
long
winstl_C_console_read_silent_character_from_CONIN(void)
{
    HANDLE hConin = WINSTL_API_EXTERNAL_FileManagement_CreateFileA(
                        "CONIN$"
                    ,   GENERIC_READ | GENERIC_WRITE
                    ,   FILE_SHARE_READ | FILE_SHARE_WRITE
                    ,   NULL
                    ,   OPEN_EXISTING
                    ,   0
                    ,   NULL
                    );

    if (INVALID_HANDLE_VALUE == hConin)
    {
        return -1;
    }
    else
    {
        long const  l   =   winstl_C_console_read_silent_character_from_(hConin);
        DWORD const e   =   WINSTL_API_EXTERNAL_ErrorHandling_GetLastError();

        WINSTL_API_EXTERNAL_HandleAndObject_CloseHandle(hConin);

        WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(e);

        return l;
    }
}

STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(winstl_C_console_read_silent_character_from_CONIO, winstl_C_console_read_silent_character_from_CONIN)
STLSOFT_INLINE
long
winstl_C_console_read_silent_character_from_CONIO(void)
{
    return winstl_C_console_read_silent_character_from_CONIN();
}

STLSOFT_INLINE
ss_truthy_t
winstl_C_isatty_fd(
    int fd
)
{
    return winstl_C_isatty_fd_(fd);
}

STLSOFT_INLINE
ss_truthy_t
winstl_C_isatty_stm(
    FILE* stm
)
{
    return winstl_C_isatty_stm_(stm);
}

/** Writes a multibyte string to the given console.
 *
 * \param hConsole T.B.C.
 * \param slice Pointer to the multibyte slice to be written;
 *
 * \pre nullptr != slice
 */
STLSOFT_INLINE
ss_truthy_t
winstl_C_write_console_string_m(
    HANDLE                              hConsole
,   stlsoft_C_string_slice_m_t const*   slice
) STLSOFT_NOEXCEPT
{
    DWORD numWritten;

    WINSTL_ASSERT(NULL != slice);

    return WINSTL_API_EXTERNAL_Console_WriteConsoleA(
        hConsole
    ,   slice->ptr, STLSOFT_STATIC_CAST(DWORD, slice->len)
    ,   &numWritten
    ,   NULL
    );
}

/** Writes a wide string to the given console.
 *
 * \param hConsole T.B.C.
 * \param slice Pointer to the wide slice to be written;
 *
 * \pre nullptr != slice
 */
STLSOFT_INLINE
ss_truthy_t
winstl_C_write_console_string_w(
    HANDLE                              hConsole
,   stlsoft_C_string_slice_w_t const*   slice
) STLSOFT_NOEXCEPT
{
    DWORD numWritten;

    WINSTL_ASSERT(NULL != slice);

    return WINSTL_API_EXTERNAL_Console_WriteConsoleW(
        hConsole
    ,   slice->ptr, STLSOFT_STATIC_CAST(DWORD, slice->len)
    ,   &numWritten
    ,   NULL
    );
}

/** Writes a multibyte string to the given console along with an end-of-line
 * sequence.
 *
 * \param hConsole T.B.C.
 * \param slice Pointer to the multibyte slice to be written;
 *
 * \pre nullptr != slice
 */
STLSOFT_INLINE
ss_truthy_t
winstl_C_write_console_line_m(
    HANDLE                              hConsole
,   stlsoft_C_string_slice_m_t const*   slice
) STLSOFT_NOEXCEPT
{
    typedef ws_char_a_t                                     char_t_;

    WINSTL_ASSERT(NULL != slice);

    STLSOFT_C_AUTO_BUFFER_DECLARE(char_t_, 100, buff);

    STLSOFT_C_AUTO_BUFFER_INITIALISE_FROM_INTERNAL(buff);

    if (0 != STLSOFT_C_AUTO_BUFFER_RESIZE(buff, 2 + slice->len))
    {
        WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_OUTOFMEMORY);

        errno = ENOMEM;

        return 0;
    }
    else
    {
        stlsoft_C_string_slice_m_t slice2;

        STLSOFT_API_EXTERNAL_memfns_memcpy(buff.ptr + 0, slice->ptr, sizeof(char_t_) * slice->len);
        STLSOFT_API_EXTERNAL_memfns_memcpy(buff.ptr + slice->len, "\r\n", sizeof(char_t_) * 2);

        slice2.len = 2 + slice->len;
        slice2.ptr = buff.ptr;

        ss_truthy_t r = winstl_C_write_console_string_m(hConsole, &slice2);

        STLSOFT_C_AUTO_BUFFER_FREE(buff);

        return r;
    }
}

/** Writes a wide string to the given console along with an end-of-line
 * sequence.
 *
 * \param hConsole T.B.C.
 * \param slice Pointer to the wide slice to be written;
 *
 * \pre nullptr != slice
 */
STLSOFT_INLINE
ss_truthy_t
winstl_C_write_console_line_w(
    HANDLE                              hConsole
,   stlsoft_C_string_slice_w_t const*   slice
) STLSOFT_NOEXCEPT
{
    typedef ws_char_w_t                                     char_t_;

    WINSTL_ASSERT(NULL != slice);

    STLSOFT_C_AUTO_BUFFER_DECLARE(char_t_, 100, buff);

    STLSOFT_C_AUTO_BUFFER_INITIALISE_FROM_INTERNAL(buff);

    if (0 != STLSOFT_C_AUTO_BUFFER_RESIZE(buff, 2 + slice->len))
    {
        WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_OUTOFMEMORY);

        errno = ENOMEM;

        return 0;
    }
    else
    {
        stlsoft_C_string_slice_w_t slice2;

        STLSOFT_API_EXTERNAL_memfns_memcpy(buff.ptr + 0, slice->ptr, sizeof(char_t_) * slice->len);
        STLSOFT_API_EXTERNAL_memfns_memcpy(buff.ptr + slice->len, L"\r\n", sizeof(char_t_) * 2);

        slice2.len = 2 + slice->len;
        slice2.ptr = buff.ptr;

        ss_truthy_t r = winstl_C_write_console_string_w(hConsole, &slice2);

        STLSOFT_C_AUTO_BUFFER_FREE(buff);

        return r;
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * obsolete symbols
 *
 * NOTE: these are only defined if:
 *
 * - we're generating documentation, or
 * - STLSOFT_OBSOLETE is specified, or
 * - it's STLSoft 1.9 (or earlier)
 */

#if defined(STLSOFT_DOCUMENTATION_SKIP_SECTION) || \
    defined(STLSOFT_OBSOLETE) || \
    _STLSOFT_VER < 0x010a0000

/** \def winstl__get_console_window
 *
 * \deprecated Use winstl_C_get_console_window
 */
# define winstl__get_console_window                         winstl_C_get_console_window
/** \def winstl__get_console_width
 *
 * \deprecated Use winstl_C_get_console_width
 */
# define winstl__get_console_width                          winstl_C_get_console_width
#endif /* obsolete || 1.9 */


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

#if defined(__cplusplus)

/** Evalutes the current width of the console.
 *
 * \ingroup group__library__System
 */
inline
ws_size_t
get_console_width()
{
    return winstl_C_get_console_width();
}

/** Returns the window handle of the current console, or NULL if it cannot
 *    be found
 *
 * \ingroup group__library__System
 *
 * \warning This only works on Windows 2000, or later, operating systems. It
 *    will return \c nullptr on other operating systems.
 */
inline
HWND
get_console_window()
{
    return winstl_C_get_console_window();
}

inline
long
console_read_silent_character_from_stdin()
{
    return winstl_C_console_read_silent_character_from_stdin();
}

inline
long
console_read_silent_character_from_CONIN()
{
    return winstl_C_console_read_silent_character_from_CONIN();
}

STLSOFT_DECLARE_FUNCTION_DEPRECATION_IN_FAVOUR_OF(console_read_silent_character_from_CONIO, console_read_silent_character_from_CONIN)
inline
long
console_read_silent_character_from_CONIO()
{
    return winstl_C_console_read_silent_character_from_CONIN();
}

inline
bool
isatty(
    int fd
)
{
    return 0 != winstl_C_isatty_fd(fd);
}

inline
bool
isatty(
    FILE* stm
)
{
    return 0 != winstl_C_isatty_stm(stm);
}

/** Writes a multibyte string to the given console.
 *
 * \param hConsole T.B.C.
 * \param s Pointer to the first character in the multibyte string;
 * \param n Number of characters in the string;
 *
 * \pre nullptr != s || 0 == n
 */
inline
bool
write_console_string(
    HANDLE              hConsole
,   ws_char_a_t const*  s
,   ws_size_t           n
) STLSOFT_NOEXCEPT
{
    stlsoft_C_string_slice_m_t const slice { n, s };

    return 0 != winstl_C_write_console_string_m(hConsole, &slice);
}

/** Writes a wide string to the given console.
 *
 * \param hConsole T.B.C.
 * \param s Pointer to the first character in the wide string;
 * \param n Number of characters in the string;
 *
 * \pre nullptr != s || 0 == n
 */
inline
bool
write_console_string(
    HANDLE              hConsole
,   ws_char_w_t const*  s
,   ws_size_t           n
) STLSOFT_NOEXCEPT
{
    stlsoft_C_string_slice_w_t const slice { n, s };

    return 0 != winstl_C_write_console_string_w(hConsole, &slice);
}

/** Writes a multibyte string to the given console along with an end-of-line
 * sequence.
 *
 * \param hConsole T.B.C.
 * \param s Pointer to the first character in the multibyte string;
 * \param n Number of characters in the string;
 *
 * \pre nullptr != s || 0 == n
 */
inline
bool
write_console_line(
    HANDLE              hConsole
,   ws_char_a_t const*  s
,   ws_size_t           n
) STLSOFT_NOEXCEPT
{
    stlsoft_C_string_slice_m_t const slice { n, s };

    return 0 != winstl_C_write_console_line_m(hConsole, &slice);
}

/** Writes a wide string to the given console along with an end-of-line
 * sequence.
 *
 * \param hConsole T.B.C.
 * \param s Pointer to the first character in the wide string;
 * \param n Number of characters in the string;
 *
 * \pre nullptr != s || 0 == n
 */
inline
bool
write_console_line(
    HANDLE              hConsole
,   ws_char_w_t const*  s
,   ws_size_t           n
) STLSOFT_NOEXCEPT
{
    stlsoft_C_string_slice_w_t const slice { n, s };

    return 0 != winstl_C_write_console_line_w(hConsole, &slice);
}
#endif /* __cplusplus */


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

#endif /* !WINSTL_INCL_WINSTL_SYSTEM_H_CONSOLE_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */

