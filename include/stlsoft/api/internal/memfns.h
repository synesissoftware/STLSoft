/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/api/internal/memfns.h
 *
 * Purpose: Internal adaptations for memXXX() functions.
 *
 * Created: 2nd January 2021
 * Updated: 2nd November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2021-2024, Matthew Wilson and Synesis Information Systems
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

#ifndef STLSOFT_INCL_STLSOFT_API_internal_h_memfns
#define STLSOFT_INCL_STLSOFT_API_internal_h_memfns


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# include <stlsoft/stlsoft.h>
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_memfns
# include <stlsoft/api/external/memfns.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_memfns */


/* /////////////////////////////////////////////////////////////////////////
 * memory functions
 */

/** The C standard function memcpy() requires that its pointer parameters
 * are non-\c nullptr even in the case where the copy byte-count is 0. GCC
 * warns about this and appears to be really aggressive in its analysis (in
 * later versions, anyway), so this adaptation function is required to
 * ensure that passing \c nullptr when count is 0 - WHICH IS THE SENSIBLE
 * SEMANTIC - are available throughout the STLSoft libs.
 */
STLSOFT_INLINE
void*
STLSOFT_API_INTERNAL_memfns_memcpy(
    void*       dest
,   void const* src
,   size_t      count
)
{
    void* const r = dest;

    STLSOFT_ASSERT(0 == count || (NULL != dest && NULL != src));

    if (0 != count)
    {
#if 1 && \
    defined(__GNUC__) && \
    1

        char    dummyDest[1];
        char    dummySrc[1];

        if (NULL == dest)
        {
            STLSOFT_ASSERT(0 == count);

            dest    =   &dummyDest[0];
            count   =   0;
        }
        if (NULL == src)
        {
            STLSOFT_ASSERT(0 == count);

            src     =   &dummySrc[0];
            count   =   0;
        }
#endif

        STLSOFT_API_EXTERNAL_memfns_memcpy(dest, src, count);
    }

    return r;
}

/** Adaptation of memset() that, like STLSOFT_API_INTERNAL_memfns_memcpy(),
 * permits \c nullptr \c dest when \c count is 0.
 *
 * \param dest Pointer to the destination. May be \c nullptr only if
 *   \c count is 0
 * \param value The value to set
 * \param count The number of bytes to set
 *
 * \return \c dest
 *
 * \pre 0 == count || nullptr != dest
 */
STLSOFT_INLINE
void*
STLSOFT_API_INTERNAL_memfns_memset(
    void*       dest
,   int         value
,   size_t      count
)
{
    void* const r = dest;

    STLSOFT_ASSERT(0 == count || NULL != dest);

    if (0 != count)
    {
#if 1 && \
    defined(__GNUC__) && \
    1

        char    dummyDest[1];

        if (NULL == dest)
        {
            STLSOFT_ASSERT(0 == count);

            dest    =   &dummyDest[0];
            count   =   0;
        }
#endif

        STLSOFT_API_EXTERNAL_memfns_memset(dest, value, count);
    }

    return r;
}

/** Wide-character equivalent of STLSOFT_API_INTERNAL_memfns_memcpy().
 *
 * \param dest Pointer to the destination. May be \c nullptr only if
 *   \c count is 0
 * \param src Pointer to the source. May be \c nullptr only if \c count is 0
 * \param count The number of wide characters to copy
 *
 * \return \c dest
 *
 * \pre 0 == count || (nullptr != dest && nullptr != src)
 */
STLSOFT_INLINE
wchar_t*
STLSOFT_API_INTERNAL_memfns_wmemcpy(
    wchar_t*        dest
,   wchar_t  const* src
,   size_t          count
)
{
    wchar_t* const r = dest;

    STLSOFT_ASSERT(0 == count || (NULL != dest && NULL != src));

    if (0 != count)
    {
#if 1 && \
    defined(__GNUC__) && \
    1

        wchar_t dummyDest[1];
        wchar_t dummySrc[1];

        if (NULL == dest)
        {
            STLSOFT_ASSERT(0 == count);

            dest    =   &dummyDest[0];
            count   =   0;
        }
        if (NULL == src)
        {
            STLSOFT_ASSERT(0 == count);

            src     =   &dummySrc[0];
            count   =   0;
        }
#endif

        STLSOFT_API_EXTERNAL_memfns_wmemcpy(dest, src, count);
    }

    return r;
}

/** Wide-character equivalent of STLSOFT_API_INTERNAL_memfns_memset().
 *
 * \param dest Pointer to the destination. May be \c nullptr only if
 *   \c count is 0
 * \param value The value to set
 * \param count The number of wide characters to set
 *
 * \return \c dest
 *
 * \pre 0 == count || nullptr != dest
 */
STLSOFT_INLINE
wchar_t*
STLSOFT_API_INTERNAL_memfns_wmemset(
    wchar_t*    dest
,   wchar_t     value
,   size_t      count
)
{
    wchar_t* const r = dest;

    STLSOFT_ASSERT(0 == count || NULL != dest);

    if (0 != count)
    {
#if 1 && \
    defined(__GNUC__) && \
    1

        wchar_t dummyDest[1];

        if (NULL == dest)
        {
            STLSOFT_ASSERT(0 == count);

            dest    =   &dummyDest[0];
            count   =   0;
        }
#endif

        STLSOFT_API_EXTERNAL_memfns_wmemset(dest, value, count);
    }

    return r;
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_API_internal_h_memfns */

/* ///////////////////////////// end of file //////////////////////////// */

