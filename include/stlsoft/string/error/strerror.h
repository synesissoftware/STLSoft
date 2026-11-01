/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/string/error/strerror.h
 *
 * Purpose: Definition of stlsoft_C_strerror()
 *
 * Created: 2nd November 2026
 * Updated: 2nd November 2026
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


/** \file stlsoft/string/error/strerror.h
 *
 * \brief [C, C++] Definition of stlsoft_C_strerror()
 *   (\ref group__library__String "String" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_STRING_ERROR_H_STRERROR
#define STLSOFT_INCL_STLSOFT_STRING_ERROR_H_STRERROR

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_STRING_ERROR_H_STRERROR_MAJOR      1
# define STLSOFT_VER_STLSOFT_STRING_ERROR_H_STRERROR_MINOR      0
# define STLSOFT_VER_STLSOFT_STRING_ERROR_H_STRERROR_REVISION   1
# define STLSOFT_VER_STLSOFT_STRING_ERROR_H_STRERROR_EDIT       1
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

#ifndef STLSOFT_INCL_STLSOFT_INTERNAL_H_SAFESTR
# include <stlsoft/internal/safestr.h>
#endif /* !STLSOFT_INCL_STLSOFT_INTERNAL_H_SAFESTR */

#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS
# ifndef STLSOFT_INCL_STLSOFT_MEMORY_H_AUTO_BUFFER
#  include <stlsoft/memory/auto_buffer.h>
# endif /* !STLSOFT_INCL_STLSOFT_MEMORY_H_AUTO_BUFFER */
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */

#ifndef STLSOFT_INCL_H_ERRNO
# define STLSOFT_INCL_H_ERRNO
# include <errno.h>
#endif /* !STLSOFT_INCL_H_ERRNO */
#ifndef STLSOFT_INCL_H_STDDEF
# define STLSOFT_INCL_H_STDDEF
# include <stddef.h>
#endif /* !STLSOFT_INCL_H_STDDEF */
#ifndef STLSOFT_INCL_H_STRING
# define STLSOFT_INCL_H_STRING
# include <string.h>
#endif /* !STLSOFT_INCL_H_STRING */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Obtains the text for an errno value.
 *
 * \param e Errno value;
 * \param cchDest Capacity of \c dest, in bytes, including the terminating
 *   NUL. A capacity of 0 does not write through \c dest;
 * \param dest Destination. It may be \c nullptr only when \c cchDest is 0;
 * \param pcchRequired Optional pointer to receive the required size in
 *   bytes;
 *
 * \return A non-nullptr C string. The "Classic CRT" returns \c strerror(e).
 *   The "Secure CRT" returns \c dest when \c cchDest is not 0 and \c dest
 *   is not \c nullptr, including when the message is truncated. Otherwise
 *   it returns a pointer to a static empty string.
 *
 * When \c pcchRequired is not \c nullptr and \c cchDest is 0,
 * \c *pcchRequired receives the full size in bytes, including the
 * terminating NUL. When \c pcchRequired is not \c nullptr and \c cchDest
 * is not 0, \c *pcchRequired receives \c strlen() of the full message. That
 * length does not include the terminating NUL.
 *
 * A classic call returns \c strerror(e) and does not copy that text into
 * \c dest. When \c cchDest is not 0 and \c dest is not \c nullptr,
 * \c dest[0] is set to NUL and the following bytes are left unchanged.
 * The lengths above are measured from \c strerror(e).
 *
 * A secure call with a non-zero \c cchDest and a non-null \c dest calls
 * \c strerror_s(dest, cchDest, e). That function NUL-terminates \c dest and
 * truncates when the message does not fit. \c dest is returned either way.
 * A null \c dest or a zero \c cchDest does not call \c strerror_s(),
 * because that call treats those arguments as an invalid parameter.
 *
 * When \c pcchRequired is not \c nullptr and the secure message does not
 * fit in \c dest, including when \c cchDest is 0, the full length is
 * obtained with an \c STLSOFT_C_AUTO_BUFFER of 200 elements.
 * \c strerror_s() is called on that buffer, and the buffer is doubled,
 * until the message is not truncated.
 *
 * \pre 0 == cchDest || nullptr != dest
 */
STLSOFT_INLINE
char const*
stlsoft_C_strerror(
    int             e
,   size_t          cchDest
,   char            dest[/* cchDest */]
,   size_t*         pcchRequired /* = NULL */
)
{
    STLSOFT_ASSERT(0 == cchDest || NULL != dest);
#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

    char const*     r = "";
    int             fits = 0;

    if (0 != cchDest && NULL != dest)
    {
        errno_t const err = STLSOFT_NS_GLOBAL(strerror_s)(
            dest
        ,   cchDest
        ,   e
        );

        if (0 != err)
        {
            dest[0] = '\0';
        }
        else if (STLSOFT_NS_GLOBAL(strlen)(dest) + 1 < cchDest)
        {
            fits = 1;
        }

        r = dest;
    }

    if (NULL != pcchRequired)
    {
        if (fits)
        {
            *pcchRequired = STLSOFT_NS_GLOBAL(strlen)(dest);
        }
        else
        {
            STLSOFT_C_AUTO_BUFFER_DECLARE(char, 200, buff);
            size_t n = 0;

            STLSOFT_C_AUTO_BUFFER_INITIALISE_FROM_INTERNAL(buff);

            for (;;)
            {
                errno_t const err = STLSOFT_NS_GLOBAL(strerror_s)(
                    buff.ptr
                ,   buff.size
                ,   e
                );

                if (0 == err)
                {
                    n = STLSOFT_NS_GLOBAL(strlen)(buff.ptr);

                    if (n + 1 < buff.size)
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }

                if (buff.size > (((size_t)-1) / 2) ||
                    0 != STLSOFT_C_AUTO_BUFFER_RESIZE(buff, buff.size * 2))
                {
                    break;
                }
            }

            STLSOFT_C_AUTO_BUFFER_FREE(buff);

            if (0 == cchDest)
            {
                *pcchRequired = n + 1;
            }
            else
            {
                *pcchRequired = n;
            }
        }
    }

    return r;
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

    char const* const r = STLSOFT_NS_GLOBAL(strerror)(e);

    if (0 != cchDest && NULL != dest)
    {
        dest[0] = '\0';
    }

    if (NULL != pcchRequired)
    {
        size_t const n = STLSOFT_NS_GLOBAL(strlen)(r);

        *pcchRequired = (0 == cchDest) ? (n + 1) : n;
    }

    return r;
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_STRING_ERROR_H_STRERROR */

/* ///////////////////////////// end of file //////////////////////////// */
