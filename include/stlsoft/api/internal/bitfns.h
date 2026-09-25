/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/api/internal/bitfns.h
 *
 * Purpose: Internal adaptations for bit functions.
 *
 * Created: 24th September 2026
 * Updated: 25th September 2026
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


/* WARNING: this file contains undocumented internal features that are
 * subject to change at any time, so if you use them it is at your own risk.
 */

#ifndef STLSOFT_INCL_STLSOFT_API_internal_h_bitfns
#define STLSOFT_INCL_STLSOFT_API_internal_h_bitfns


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# include <stlsoft/stlsoft.h>
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_bitfns
# include <stlsoft/api/external/bitfns.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_bitfns */


/* /////////////////////////////////////////////////////////////////////////
 * bit functions
 */

#ifndef STLSOFT_API_INTERNAL_bitfns_popcount_uint16

# if 0 ||\
     defined (STLSOFT_API_EXTERNAL_bitfns_popcount_uint) ||\
     defined (STLSOFT_API_EXTERNAL_bitfns_popcnt_uint16) ||\
     0

STLSOFT_INLINE
int
STLSOFT_API_INTERNAL_bitfns_popcount_uint16(
    STLSOFT_NS_QUAL(ss_uint16_t) v
)
{
#  if 0
#  elif defined(STLSOFT_API_EXTERNAL_bitfns_popcount_uint)

    return STLSOFT_API_EXTERNAL_bitfns_popcount_uint(STLSOFT_C_CAST(unsigned int, v));
#  elif defined(STLSOFT_API_EXTERNAL_bitfns_popcnt_uint16)

    return STLSOFT_API_EXTERNAL_bitfns_popcnt_uint16(STLSOFT_C_CAST(unsigned short, v));
#  else

#   error Unexpected
#  endif
}
#  define STLSOFT_API_INTERNAL_bitfns_popcount_uint16       STLSOFT_API_INTERNAL_bitfns_popcount_uint16
# endif
#endif

#ifndef STLSOFT_API_INTERNAL_bitfns_popcount_uint32

# if 0 ||\
     defined (STLSOFT_API_EXTERNAL_bitfns_popcount_uint) ||\
     defined (STLSOFT_API_EXTERNAL_bitfns_popcnt_uint32) ||\
     0

STLSOFT_INLINE
int
STLSOFT_API_INTERNAL_bitfns_popcount_uint32(
    STLSOFT_NS_QUAL(ss_uint32_t) v
)
{
#  if 0
#  elif defined(STLSOFT_API_EXTERNAL_bitfns_popcount_uint)

    return STLSOFT_API_EXTERNAL_bitfns_popcount_uint(STLSOFT_C_CAST(unsigned int, v));
#  elif defined(STLSOFT_API_EXTERNAL_bitfns_popcnt_uint32)

    return STLSOFT_API_EXTERNAL_bitfns_popcnt_uint32(STLSOFT_C_CAST(unsigned int, v));
#  else

#   error Unexpected
#  endif
}
#  define STLSOFT_API_INTERNAL_bitfns_popcount_uint32       STLSOFT_API_INTERNAL_bitfns_popcount_uint32
# endif
#endif

#ifndef STLSOFT_API_INTERNAL_bitfns_popcount_uint64

# if 0 ||\
     defined (STLSOFT_API_EXTERNAL_bitfns_popcount_ullong) ||\
     defined (STLSOFT_API_EXTERNAL_bitfns_popcnt_uint64) ||\
     0

STLSOFT_INLINE
int
STLSOFT_API_INTERNAL_bitfns_popcount_uint64(
    STLSOFT_NS_QUAL(ss_uint64_t) v
)
{
#  if 0
#  elif defined(STLSOFT_API_EXTERNAL_bitfns_popcount_ullong)

    return STLSOFT_API_EXTERNAL_bitfns_popcount_ullong(STLSOFT_C_CAST(unsigned long long, v));
#  elif defined(STLSOFT_API_EXTERNAL_bitfns_popcnt_uint64)

    return STLSOFT_C_CAST(int, STLSOFT_API_EXTERNAL_bitfns_popcnt_uint64(STLSOFT_C_CAST(unsigned __int64, v)));
#  else

#   error Unexpected
#  endif
}
#  define STLSOFT_API_INTERNAL_bitfns_popcount_uint64       STLSOFT_API_INTERNAL_bitfns_popcount_uint64
# endif
#endif


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_API_internal_h_bitfns */

/* ///////////////////////////// end of file //////////////////////////// */

