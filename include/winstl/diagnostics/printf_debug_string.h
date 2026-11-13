/* /////////////////////////////////////////////////////////////////////////
 * File:    winstl/diagnostics/printf_debug_string.h
 *
 * Purpose: Functions to write lines to the Windows debugger.
 *
 * Created: 18th August 2025
 * Updated: 13th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2025-2026, Matthew Wilson and Synesis Information Systems
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


/** \file winstl/diagnostics/printf_debug_string.h
 *
 * \brief [C++] Functions to printf to the Windows debugger.
 *   (\ref group__library__Diagnostic "Diagnostic" Library).
 */

#ifndef WINSTL_INCL_WINSTL_DIAGNOSTICS_H_PRINTF_DEBUG_LINE
#define WINSTL_INCL_WINSTL_DIAGNOSTICS_H_PRINTF_DEBUG_LINE

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define WINSTL_VER_WINSTL_DIAGNOSTICS_H_PRINTF_DEBUG_LINE_MAJOR    1
# define WINSTL_VER_WINSTL_DIAGNOSTICS_H_PRINTF_DEBUG_LINE_MINOR    0
# define WINSTL_VER_WINSTL_DIAGNOSTICS_H_PRINTF_DEBUG_LINE_REVISION 2
# define WINSTL_VER_WINSTL_DIAGNOSTICS_H_PRINTF_DEBUG_LINE_EDIT     4
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


#ifndef STLSOFT_INCL_STLSOFT_UTIL_STRING_H_VSNPRINTF
# include <stlsoft/util/string/vsnprintf.h>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_STRING_H_VSNPRINTF */

#ifndef STLSOFT_INCL_H_ERRNO
# define STLSOFT_INCL_H_ERRNO
# include <errno.h>
#endif /* !STLSOFT_INCL_H_ERRNO */

#ifndef WINSTL_INCL_WINSTL_API_external_h_Debugging
# include <winstl/api/external/Debugging.h>
#endif /* !WINSTL_INCL_WINSTL_API_external_h_Debugging */


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* ////////////////////////////////////////////////////////////////////// */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

/* This is provided to facilitate unit-testing */
#ifndef WINSTL_DIAGNOSTICS_PRINTF_DEBUG_LINE_SUPPRESS_ODS_

STLSOFT_INLINE
void
winstl_C_call_OutputDebugStringA_(
    WINSTL_NS_QUAL(ws_char_a_t) const* s
)
{
    if (NULL != s)
    {
        WINSTL_API_EXTERNAL_Debugging_OutputDebugStringA(s);
    }
}
#endif /* WINSTL_DIAGNOSTICS_PRINTF_DEBUG_LINE_SUPPRESS_ODS_ */
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Writes a formatted string to \c OutputDebugString.
 *
 */
#if 0
#elif defined(__GNUC__)
__attribute__((format(printf, 1, 2)))
#endif
STLSOFT_INLINE
int
winstl_C_printf_debug_string(
    WINSTL_NS_QUAL(ws_char_a_t) const* fmt
,   ...
)
{
    CHAR    msg[4092];
    int     r;
    va_list args;

    WINSTL_ASSERT(NULL != fmt);

    msg[STLSOFT_NUM_ELEMENTS(msg) - 1] = '~';

    va_start(args, fmt);

    r = STLSOFT_NS_QUAL(stlsoft_C_vsnprintf)(&msg[0], STLSOFT_NUM_ELEMENTS(msg), fmt, args);

    va_end(args);

    if (r < 1)
    {
        if ('~' == msg[STLSOFT_NUM_ELEMENTS(msg) - 1])
        {
            // int const e = errno;

            return r;
        }
        else
        {
            r = (int)STLSOFT_NUM_ELEMENTS(msg);
        }
    }

    if (r >= STLSOFT_C_CAST(int, STLSOFT_NUM_ELEMENTS(msg)))
    {
        // too large, so we want to add trailing \n if that was present

        size_t const n = strlen(fmt);

        if ('\n' == fmt[n - 1])
        {
            msg[STLSOFT_NUM_ELEMENTS(msg) - 1] = '\0';
            msg[STLSOFT_NUM_ELEMENTS(msg) - 2] = '\n';
            msg[STLSOFT_NUM_ELEMENTS(msg) - 3] = '\r';
            msg[STLSOFT_NUM_ELEMENTS(msg) - 4] = '.';
            msg[STLSOFT_NUM_ELEMENTS(msg) - 5] = '.';
            msg[STLSOFT_NUM_ELEMENTS(msg) - 6] = '.';
            msg[STLSOFT_NUM_ELEMENTS(msg) - 7] = ' ';

            r = STLSOFT_NUM_ELEMENTS(msg) - 1;
        }
    }

    winstl_C_call_OutputDebugStringA_(msg);

    return r;
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !WINSTL_INCL_WINSTL_DIAGNOSTICS_H_PRINTF_DEBUG_LINE */

/* ///////////////////////////// end of file //////////////////////////// */

