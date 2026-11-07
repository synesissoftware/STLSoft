/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/api/internal/DynamicLinkLibrary.h
 *
 * Purpose: Internal preprocessor aliases for internal Windows' Dynamic Link
 *          Library Functions API.
 *
 * Created: 30th November 2020
 * Updated: 15th October 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2020-2026, Matthew Wilson and Synesis Information Systems
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

#ifndef WINSTL_INCL_WINSTL_API_internal_h_DynamicLinkLibrary
#define WINSTL_INCL_WINSTL_API_internal_h_DynamicLinkLibrary


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef WINSTL_INCL_WINSTL_H_WINSTL
# include <winstl/winstl.h>
#endif /* !WINSTL_INCL_WINSTL_H_WINSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef WINSTL_INCL_WINSTL_API_external_h_DynamicLinkLibrary
# include <winstl/api/external/DynamicLinkLibrary.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_DynamicLinkLibrary */
#ifndef WINSTL_INCL_WINSTL_API_external_h_ErrorHandling
# include <winstl/api/external/ErrorHandling.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_ErrorHandling */
#ifndef WINSTL_INCL_WINSTL_API_external_h_MemoryManagement
# include <winstl/api/external/MemoryManagement.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_MemoryManagement */


/* /////////////////////////////////////////////////////////////////////////
 * Windows' File Management Functions
 */

/** Obtains the fully qualified path for the file that contains the
 * specified module (that must have been loaded by the current process).
 *
 * \param hModule A handle to the loaded module for which the path is to be
 *   obtained;
 * \param filename A pointer to the buffer into which to write the path. May
 *   not be NULL unless \c cchFilename is 0;
 * \param cchFilename Number of available bytes in \c filename;
 *
 * \return The number of characters written if cchFilename is sufficient to
 *   hold the entire string; the number of characters required (including
 *   for terminating NUL character) if not.
 *
 * \note The number of characters required returned is 2 (not 1) more than
 *   the number of characters in the string, due to the underlying API
 *   function not providing any direct indication as to (in)sufficient size.
 */
STLSOFT_INLINE
DWORD
WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameA(
    HMODULE hModule
,   CHAR    filename[]
,   DWORD   cchFilename
) STLSOFT_NOEXCEPT
{
    WINSTL_ASSERT(0 == cchFilename || NULL != filename);

    CHAR stub[1];

    if (NULL == filename)
    {
        filename = &stub[0];
    }

    /* When given a too-small buffer GetModuleFileNameA() does not return
     * the required size, but rather it copies as much as is possible + the
     * NUL character and returns cchBuffer.
     *
     * Hence, we must use the following algorithm:
     * - try with the given buffer and: if fails (for other reason that
     *   insufficient buffer) then fail; otherwise check for buffer being
     *   definitely sufficient and return with success;
     * - otherwise, insufficient, so: try with stack memory (e.g. 2 x
     *   WINSTL_CONST_MAX_PATH), and otherwise try with heap memory
     *   (WINSTL_CONST_NT_MAX_PATH). If succeeds, ensure that does set
     *   ERROR_INSUFFICIENT_BUFFER if 0 != cchFilename; otherwise ensure
     *   that does not set ERROR_INSUFFICIENT_BUFFER;
     */

    if (0 != cchFilename)
    {
        /* try with what is given, as that might be sufficient */

        DWORD const cch = WINSTL_API_EXTERNAL_DynamicLinkLibrary_GetModuleFileNameA(hModule, filename, cchFilename);

        if (0 == cch)
        {
            /* failed for reason other than insufficient buffer */

            return 0;
        }
        else
        {
            /* The return value can only be trusted if 2+ spare characters in buffer */

            if (cch + 1 < cchFilename)
            {
                /* prospective check (against future changes) */

                if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
                {
                    WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
                }

                return cch;
            }
        }
    }

    {
        /* stack memory */
        {
            CHAR        buff[2 * WINSTL_CONST_MAX_PATH];
            DWORD const cch = WINSTL_API_EXTERNAL_DynamicLinkLibrary_GetModuleFileNameA(hModule, buff, STLSOFT_NUM_ELEMENTS(buff));

            if (0 == cch)
            {
                /* failed for reason other than insufficient buffer */

                return 0;
            }
            else
            {
                /* The return value can only be trusted if 2+ spare characters in buffer */

                if (cch + 1 < STLSOFT_NUM_ELEMENTS(buff))
                {
                    /* prospective check (against future changes) */

                    if (0 == cchFilename)
                    {
                        if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
                        {
                            WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
                        }
                    }
                    else
                    {
                        WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_INSUFFICIENT_BUFFER);
                    }

                    return 2 + cch;
                }
            }
        }

        /* heap memory */
        {
            DWORD const     n       =   (1 + WINSTL_CONST_NT_MAX_PATH);
            DWORD const     cb      =   n * sizeof(CHAR);
            CHAR* const     buff2   =   STLSOFT_STATIC_CAST(CHAR*, WINSTL_API_EXTERNAL_MemoryManagement_HeapAlloc(WINSTL_API_EXTERNAL_MemoryManagement_GetProcessHeap(), 0, cb));

            if (NULL == buff2)
            {
                WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_OUTOFMEMORY);

                return 0;
            }
            else
            {
                DWORD const cch2 = WINSTL_API_EXTERNAL_DynamicLinkLibrary_GetModuleFileNameA(hModule, &buff2[0], n);

                WINSTL_API_EXTERNAL_MemoryManagement_HeapFree(WINSTL_API_EXTERNAL_MemoryManagement_GetProcessHeap(), 0, buff2);

                if (0 == cch2)
                {
                    return 0;
                }
                else
                {
                    if (0 == cchFilename)
                    {
                        if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
                        {
                            WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
                        }
                    }
                    else
                    {
                        WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_INSUFFICIENT_BUFFER);
                    }

                    return 2 + cch2;
                }
            }
        }
    }
}

/** Obtains the fully qualified path for the file that contains the
 * specified module (that must have been loaded by the current process).
 *
 * \param hModule A handle to the loaded module for which the path is to be
 *   obtained;
 * \param filename A pointer to the buffer into which to write the path. May
 *   not be NULL unless \c cchFilename is 0;
 * \param cchFilename Number of available characters in \c filename;
 *
 * \return The number of characters written if cchFilename is sufficient to
 *   hold the entire string; the number of characters required (including
 *   for terminating NUL character) if not.
 *
 * \note The number of characters required returned is 2 (not 1) more than
 *   the number of characters in the string, due to the underlying API
 *   function not providing any direct indication as to (in)sufficient size.
 */
STLSOFT_INLINE
DWORD
WINSTL_API_INTERNAL_DynamicLinkLibrary_GetModuleFileNameW(
    HMODULE hModule
,   WCHAR   filename[]
,   DWORD   cchFilename
) STLSOFT_NOEXCEPT
{
    WINSTL_ASSERT(0 == cchFilename || NULL != filename);

    WCHAR stub[1];

    if (NULL == filename)
    {
        filename = &stub[0];
    }

    /* When given a too-small buffer GetModuleFileNameA() does not return
     * the required size, but rather it copies as much as is possible + the
     * NUL character and returns cchBuffer.
     *
     * Hence, we must use the following algorithm:
     * - try with the given buffer and: if fails (for other reason that
     *   insufficient buffer) then fail; otherwise check for buffer being
     *   definitely sufficient and return with success;
     * - otherwise, insufficient, so: try with stack memory (e.g. 2 x
     *   WINSTL_CONST_MAX_PATH), and otherwise try with heap memory
     *   (WINSTL_CONST_NT_MAX_PATH). If succeeds, ensure that does set
     *   ERROR_INSUFFICIENT_BUFFER if 0 != cchFilename; otherwise ensure
     *   that does not set ERROR_INSUFFICIENT_BUFFER;
     */

    if (0 != cchFilename)
    {
        /* try with what is given, as that might be sufficient */

        DWORD const cch = WINSTL_API_EXTERNAL_DynamicLinkLibrary_GetModuleFileNameW(hModule, filename, cchFilename);

        if (0 == cch)
        {
            /* failed for reason other than insufficient buffer */

            return 0;
        }
        else
        {
            /* The return value can only be trusted if 2+ spare characters in buffer */

            if (cch + 1 < cchFilename)
            {
                /* prospective check (against future changes) */

                if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
                {
                    WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
                }

                return cch;
            }
        }
    }

    {
        /* stack memory */
        {
            WCHAR       buff[2 * WINSTL_CONST_MAX_PATH];
            DWORD const cch = WINSTL_API_EXTERNAL_DynamicLinkLibrary_GetModuleFileNameW(hModule, buff, STLSOFT_NUM_ELEMENTS(buff));

            if (0 == cch)
            {
                /* failed for reason other than insufficient buffer */

                return 0;
            }
            else
            {
                /* The return value can only be trusted if 2+ spare characters in buffer */

                if (cch + 1 < STLSOFT_NUM_ELEMENTS(buff))
                {
                    /* prospective check (against future changes) */

                    if (0 == cchFilename)
                    {
                        if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
                        {
                            WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
                        }
                    }
                    else
                    {
                        WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_INSUFFICIENT_BUFFER);
                    }

                    return 2 + cch;
                }
            }
        }

        /* heap memory */
        {
            DWORD const     n       =   (1 + WINSTL_CONST_NT_MAX_PATH);
            DWORD const     cb      =   n * sizeof(WCHAR);
            WCHAR* const    buff2   =   STLSOFT_STATIC_CAST(WCHAR*, WINSTL_API_EXTERNAL_MemoryManagement_HeapAlloc(WINSTL_API_EXTERNAL_MemoryManagement_GetProcessHeap(), 0, cb));

            if (NULL == buff2)
            {
                WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_OUTOFMEMORY);

                return 0;
            }
            else
            {
                DWORD const cch2 = WINSTL_API_EXTERNAL_DynamicLinkLibrary_GetModuleFileNameW(hModule, &buff2[0], n);

                WINSTL_API_EXTERNAL_MemoryManagement_HeapFree(WINSTL_API_EXTERNAL_MemoryManagement_GetProcessHeap(), 0, buff2);

                if (0 == cch2)
                {
                    return 0;
                }
                else
                {
                    if (0 == cchFilename)
                    {
                        if (ERROR_INSUFFICIENT_BUFFER == WINSTL_API_EXTERNAL_ErrorHandling_GetLastError())
                        {
                            WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_SUCCESS);
                        }
                    }
                    else
                    {
                        WINSTL_API_EXTERNAL_ErrorHandling_SetLastError(ERROR_INSUFFICIENT_BUFFER);
                    }

                    return 2 + cch2;
                }
            }
        }
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !WINSTL_INCL_WINSTL_API_internal_h_DynamicLinkLibrary */

/* ///////////////////////////// end of file //////////////////////////// */

