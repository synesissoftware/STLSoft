/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/api/internal/get_home_directory_.h
 *
 * Purpose: Internal adaptations for obtaining home directory.
 *
 * Created: 27th April 2025
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
 * - Neither the name(s) of Matthew Wilson and Synesis Synesis Information
 *   Systems nor the names of any contributors may be used to endorse or
 *   promote products derived from this software without specific prior
 *   written permission.
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

#ifndef WINSTL_API_INTERNAL_H_get_home_directory_
#define WINSTL_API_INTERNAL_H_get_home_directory_

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef WINSTL_INCL_WINSTL_H_WINSTL
#include <winstl/winstl.h>
#endif /* !WINSTL_INCL_WINSTL_H_WINSTL */

#ifndef STLSOFT_INCL_H_STDDEF
#define STLSOFT_INCL_H_STDDEF
#include <stddef.h>
#endif /* !STLSOFT_INCL_H_STDDEF */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_memfns
#include <stlsoft/api/external/memfns.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_memfns */


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

STLSOFT_INLINE
int WINSTL_API_INTERNAL_System_get_home_directory_a_(
    CHAR    buffer[]
,   DWORD   cchBuffer
)
{
    WINSTL_ASSERT(NULL != buffer || 0 == cchBuffer);

    {
        DWORD const dw_up = STLSOFT_NS_GLOBAL_(GetEnvironmentVariableA)("USERPROFILE", buffer, cchBuffer);

        if (0 == dw_up)
        {
            DWORD const le_1 = STLSOFT_NS_GLOBAL_(GetLastError)();

            if (ERROR_ENVVAR_NOT_FOUND == le_1)
            {
                /* now try for "HOMEDRIVE" and "HOMEPATH" */

                CHAR        drive[WINSTL_CONST_MAX_PATH];
                CHAR        directory[WINSTL_CONST_MAX_PATH];
                DWORD const cchDrive        =   STLSOFT_NS_GLOBAL_(GetEnvironmentVariableA)("HOMEDRIVE", &drive[0], STLSOFT_NUM_ELEMENTS(drive));
                DWORD const le_2            =   STLSOFT_NS_GLOBAL_(GetLastError)();
                DWORD const cchDirectory    =   STLSOFT_NS_GLOBAL_(GetEnvironmentVariableA)("HOMEPATH", &directory[0], STLSOFT_NUM_ELEMENTS(directory));
                DWORD const le_3            =   STLSOFT_NS_GLOBAL_(GetLastError)();

                if (0 == cchDrive)
                {
                    STLSOFT_NS_GLOBAL_(SetLastError)(le_2);

                    return 0;
                }

                if (0 == cchDirectory)
                {
                    STLSOFT_NS_GLOBAL_(SetLastError)(le_3);

                    return 0;
                }

                STLSOFT_NS_GLOBAL_(SetLastError)(ERROR_SUCCESS);

                if (cchBuffer <= cchDrive + cchDirectory)
                {
                    if (0 != cchBuffer)
                    {
                        STLSOFT_NS_GLOBAL_(SetLastError)(ERROR_INSUFFICIENT_BUFFER);

                        buffer[0] = '\0';
                    }

                    return cchDrive + cchDirectory + 1;
                }
                else
                {
                    STLSOFT_API_EXTERNAL_memfns_memcpy(&buffer[0] + 0, drive, sizeof(CHAR) * cchDrive);
                    STLSOFT_API_EXTERNAL_memfns_memcpy(&buffer[0] + cchDrive, directory, sizeof(CHAR) * cchDirectory);
                    buffer[cchDrive + cchDirectory] = '\0';

                    return cchDrive + cchDirectory;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (cchBuffer < dw_up)
            {
                if (0 != cchBuffer)
                {
                    STLSOFT_NS_GLOBAL_(SetLastError)(ERROR_INSUFFICIENT_BUFFER);

                    buffer[0] = '\0';
                }
            }

            return dw_up;
        }
    }
}

STLSOFT_INLINE
int WINSTL_API_INTERNAL_System_get_home_directory_w_(
    WCHAR   buffer[]
,   DWORD   cchBuffer
)
{
    WINSTL_ASSERT(NULL != buffer || 0 == cchBuffer);

    {
        DWORD const dw_up = STLSOFT_NS_GLOBAL_(GetEnvironmentVariableW)(L"USERPROFILE", buffer, cchBuffer);

        if (0 == dw_up)
        {
            DWORD const le_1 = STLSOFT_NS_GLOBAL_(GetLastError)();

            if (ERROR_ENVVAR_NOT_FOUND == le_1)
            {
                /* now try for "HOMEDRIVE" and "HOMEPATH" */

                WCHAR       drive[WINSTL_CONST_MAX_PATH];
                WCHAR       directory[WINSTL_CONST_MAX_PATH];
                DWORD const cchDrive        =   STLSOFT_NS_GLOBAL_(GetEnvironmentVariableW)(L"HOMEDRIVE", &drive[0], STLSOFT_NUM_ELEMENTS(drive));
                DWORD const le_2            =   STLSOFT_NS_GLOBAL_(GetLastError)();
                DWORD const cchDirectory    =   STLSOFT_NS_GLOBAL_(GetEnvironmentVariableW)(L"HOMEPATH", &directory[0], STLSOFT_NUM_ELEMENTS(directory));
                DWORD const le_3            =   STLSOFT_NS_GLOBAL_(GetLastError)();

                if (0 == cchDrive)
                {
                    STLSOFT_NS_GLOBAL_(SetLastError)(le_2);

                    return 0;
                }

                if (0 == cchDirectory)
                {
                    STLSOFT_NS_GLOBAL_(SetLastError)(le_3);

                    return 0;
                }

                STLSOFT_NS_GLOBAL_(SetLastError)(ERROR_SUCCESS);

                if (cchBuffer <= cchDrive + cchDirectory)
                {
                    if (0 != cchBuffer)
                    {
                        STLSOFT_NS_GLOBAL_(SetLastError)(ERROR_INSUFFICIENT_BUFFER);

                        buffer[0] = '\0';
                    }

                    return cchDrive + cchDirectory + 1;
                }
                else
                {
                    STLSOFT_API_EXTERNAL_memfns_memcpy(&buffer[0] + 0, drive, sizeof(WCHAR) * cchDrive);
                    STLSOFT_API_EXTERNAL_memfns_memcpy(&buffer[0] + cchDrive, directory, sizeof(WCHAR) * cchDirectory);
                    buffer[cchDrive + cchDirectory] = L'\0';

                    return cchDrive + cchDirectory;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (cchBuffer < dw_up)
            {
                if (0 != cchBuffer)
                {
                    STLSOFT_NS_GLOBAL_(SetLastError)(ERROR_INSUFFICIENT_BUFFER);

                    buffer[0] = '\0';
                }
            }

            return dw_up;
        }
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
#pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* WINSTL_API_INTERNAL_H_get_home_directory_ */

/* ///////////////////////////// end of file //////////////////////////// */

