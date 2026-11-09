/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/api/internal/SystemInformation.h
 *
 * Purpose: Internal preprocessor aliases for internal Windows' System
 *          Information Functions API.
 *
 * Created: 25th May 2025
 * Updated: 9th November 2026
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


/* WARNING: this file contains undocumented internal features that are
 * subject to change at any time, so if you use them it is at your own risk.
 */

#ifndef WINSTL_INCL_WINSTL_API_internal_h_SystemInformation
#define WINSTL_INCL_WINSTL_API_internal_h_SystemInformation


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef WINSTL_INCL_WINSTL_H_WINSTL
# include <winstl/winstl.h>
#endif /* !WINSTL_INCL_WINSTL_H_WINSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef WINSTL_INCL_WINSTL_API_external_h_ErrorHandling
# include <winstl/api/external/ErrorHandling.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_ErrorHandling */
#ifndef WINSTL_INCL_WINSTL_API_external_h_MemoryManagement
# include <winstl/api/external/MemoryManagement.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_MemoryManagement */
#ifndef WINSTL_INCL_WINSTL_API_external_h_SystemInformation
# include <winstl/api/external/SystemInformation.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_SystemInformation */


/* /////////////////////////////////////////////////////////////////////////
 * Windows' System Information Functions
 */

/** Invokes the underlying `GetEnvironmentVariableA()` and applies last-error
 * and contingent buffer adjustment accordingly.
 */
STLSOFT_INLINE
DWORD
WINSTL_API_INTERNAL_SystemInformation_GetEnvironmentVariableA(
    LPCSTR  lpName
,   LPSTR   lpBuffer
,   DWORD   nSize
) STLSOFT_NOEXCEPT
{
    DWORD const n = WINSTL_API_EXTERNAL_SystemInformation_GetEnvironmentVariableA(lpName, lpBuffer, nSize);

    if (n > nSize)
    {
        if (0 == nSize)
        {
            if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
            {
                WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
            }
        }
        else
        {
            WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_INSUFFICIENT_BUFFER);

            lpBuffer[0] = '\0';
        }
    }

    return n;
}

/** Invokes the underlying `GetEnvironmentVariableW()` and applies last-error
 * and contingent buffer adjustment accordingly.
 */
STLSOFT_INLINE
DWORD
WINSTL_API_INTERNAL_SystemInformation_GetEnvironmentVariableW(
    LPCWSTR lpName
,   LPWSTR  lpBuffer
,   DWORD   nSize
) STLSOFT_NOEXCEPT
{
    DWORD const n = WINSTL_API_EXTERNAL_SystemInformation_GetEnvironmentVariableW(lpName, lpBuffer, nSize);

    if (n > nSize)
    {
        if (0 == nSize)
        {
            if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
            {
                WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
            }
        }
        else
        {
            WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_INSUFFICIENT_BUFFER);

            lpBuffer[0] = L'\0';
        }
    }

    return n;
}

/** Invokes the underlying `GetSystemDirectoryA()` and applies last-error
 * and contingent buffer adjustment accordingly.
 */
STLSOFT_INLINE
DWORD
WINSTL_API_INTERNAL_SystemInformation_GetSystemDirectoryA(
    CHAR    buff[]
,   DWORD   cchBuff
) STLSOFT_NOEXCEPT
{
    DWORD const n = WINSTL_API_EXTERNAL_SystemInformation_GetSystemDirectoryA(buff, cchBuff);

    if (n > cchBuff)
    {
        if (0 == cchBuff)
        {
            if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
            {
                WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
            }
        }
        else
        {
            WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_INSUFFICIENT_BUFFER);

            buff[0] = '\0';
        }
    }

    return n;
}

/** Invokes the underlying `GetSystemDirectoryW()` and applies last-error
 * and contingent buffer adjustment accordingly.
 */
STLSOFT_INLINE
DWORD
WINSTL_API_INTERNAL_SystemInformation_GetSystemDirectoryW(
    WCHAR   buff[]
,   DWORD   cchBuff
) STLSOFT_NOEXCEPT
{
    DWORD const n = WINSTL_API_EXTERNAL_SystemInformation_GetSystemDirectoryW(buff, cchBuff);

    if (n > cchBuff)
    {
        if (0 == cchBuff)
        {
            if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
            {
                WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
            }
        }
        else
        {
            WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_INSUFFICIENT_BUFFER);

            buff[0] = L'\0';
        }
    }

    return n;
}


/** T.B.C.
 *
 * \return The number of characters written if cchFilename is sufficient to
 *  hold the entire string; the number of characters required (including for
 *  terminating NUL character) if not
 */
STLSOFT_INLINE
DWORD
WINSTL_API_INTERNAL_SystemInformation_GetWindowsDirectoryA(
    CHAR    buff[]
,   DWORD   cchBuff
) STLSOFT_NOEXCEPT
{
    DWORD const n = WINSTL_API_EXTERNAL_SystemInformation_GetWindowsDirectoryA(buff, cchBuff);

    if (n > cchBuff)
    {
        if (0 == cchBuff)
        {
            if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
            {
                WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
            }
        }
        else
        {
            WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_INSUFFICIENT_BUFFER);

            buff[0] = '\0';
        }
    }

    return n;
}

/** T.B.C.
 *
 * \return The number of characters written if cchFilename is sufficient to
 *  hold the entire string; the number of characters required (including for
 *  terminating NUL character) if not
 */
STLSOFT_INLINE
DWORD
WINSTL_API_INTERNAL_SystemInformation_GetWindowsDirectoryW(
    WCHAR   buff[]
,   DWORD   cchBuff
) STLSOFT_NOEXCEPT
{
    DWORD const n = WINSTL_API_EXTERNAL_SystemInformation_GetWindowsDirectoryW(buff, cchBuff);

    if (n > cchBuff)
    {
        if (0 == cchBuff)
        {
            if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
            {
                WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
            }
        }
        else
        {
            WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_INSUFFICIENT_BUFFER);

            buff[0] = L'\0';
        }
    }

    return n;
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !WINSTL_INCL_WINSTL_API_internal_h_SystemInformation */

/* ///////////////////////////// end of file //////////////////////////// */

