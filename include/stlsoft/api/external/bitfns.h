/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/api/external/bitfns.h
 *
 * Purpose: External adaptations for bit functions.
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


/* WARNING: this file contains undocumented external features that are
 * subject to change at any time, so if you use them it is at your own risk.
 */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_bitfns
#define STLSOFT_INCL_STLSOFT_API_external_h_bitfns


/* /////////////////////////////////////////////////////////////////////////
 * includes - 1
 */

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# include <stlsoft/stlsoft.h>
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */


/* /////////////////////////////////////////////////////////////////////////
 * intrinsics support
 *
 * Detection follows p99/src/p99_portable.h. GCC and Clang builtins are
 * preferred over the MSVC intrinsics when both are visible (clang-cl).
 *
 * Detected features/macros:
 *
 * 1. "Count leading zeros"
 *   - discriminated symbols:
 *     - STLSOFT_CF__BitScanReverse_SUPPORT
 *     - STLSOFT_CF__BitScanReverse64_SUPPORT
 *     - STLSOFT_CF__builtin_clz_SUPPORT
 *     - STLSOFT_CF__builtin_clzll_SUPPORT
 *
 *   - Clang/GCC may provide:
 *     - int __builtin_clz(unsigned int)
 *     - int __builtin_clzll(unsigned long long)
 *
 *   - VC++ may provide:
 *     - unsigned char _BitScanReverse(unsigned long*, unsigned long)
 *     - unsigned char _BitScanReverse64(unsigned long*, unsigned __int64)
 *
 *     NOTE: _BitScanReverse(64)() have different semantics to clz(ll) in
 *       that the former find the index of the most significant bit and the
 *       latter find the number of leading zeros.
 *
 * 2. "Population count"
 *
 *   - discriminated symbols:
 *     - STLSOFT_CF__builtin_popcount_SUPPORT
 *     - STLSOFT_CF__builtin_popcountll_SUPPORT
 *     - STLSOFT_CF__popcnt16_SUPPORT
 *     - STLSOFT_CF__popcnt_SUPPORT
 *     - STLSOFT_CF__popcnt64_SUPPORT
 *
 * - Clang/GCC may provide:
 *   - int __builtin_popcount(unsigned int)
 *   - int __builtin_popcountll(unsigned long long)
 *
 *   - VC++ may provide:
 *     - unsigned short   __popcnt16(unsigned short)
 *     - unsigned int     __popcnt(unsigned int)
 *     - unsigned __int64 __popcnt64(unsigned __int64)
 */


/* /////////////////////////////////////////////////////////
 * reject any other definition of the symbols under purview
 */

#ifdef STLSOFT_CF__BitScanReverse_SUPPORT
# error STLSOFT_CF__BitScanReverse_SUPPORT may not be defined
#endif /* STLSOFT_CF__BitScanReverse_SUPPORT */
#ifdef STLSOFT_CF__BitScanReverse64_SUPPORT
# error STLSOFT_CF__BitScanReverse64_SUPPORT may not be defined
#endif /* STLSOFT_CF__BitScanReverse64_SUPPORT */

#ifdef STLSOFT_CF__builtin_clz_SUPPORT
# error STLSOFT_CF__builtin_clz_SUPPORT may not be defined
#endif /* STLSOFT_CF__builtin_clz_SUPPORT */
#ifdef STLSOFT_CF__builtin_clzll_SUPPORT
# error STLSOFT_CF__builtin_clzll_SUPPORT may not be defined
#endif /* STLSOFT_CF__builtin_clzll_SUPPORT */

#ifdef STLSOFT_CF__builtin_popcount_SUPPORT
# error STLSOFT_CF__builtin_popcount_SUPPORT may not be defined
#endif /* STLSOFT_CF__builtin_popcount_SUPPORT */
#ifdef STLSOFT_CF__builtin_popcountll_SUPPORT
# error STLSOFT_CF__builtin_popcountll_SUPPORT may not be defined
#endif /* STLSOFT_CF__builtin_popcountll_SUPPORT */

#ifdef STLSOFT_CF__popcnt16_SUPPORT
# error STLSOFT_CF__popcnt16_SUPPORT may not be defined
#endif /* STLSOFT_CF__popcnt16_SUPPORT */
#ifdef STLSOFT_CF__popcnt_SUPPORT
# error STLSOFT_CF__popcnt_SUPPORT may not be defined
#endif /* STLSOFT_CF__popcnt_SUPPORT */
#ifdef STLSOFT_CF__popcnt64_SUPPORT
# error STLSOFT_CF__popcnt64_SUPPORT may not be defined
#endif /* STLSOFT_CF__popcnt64_SUPPORT */


/* /////////////////////////////////////////////////////////
 * "Count leading zeros"
 *
 *   - STLSOFT_CF__BitScanReverse_SUPPORT
 *   - STLSOFT_CF__BitScanReverse64_SUPPORT
 *   - STLSOFT_CF__builtin_clz_SUPPORT
 *   - STLSOFT_CF__builtin_clzll_SUPPORT
 */


/* STLSOFT_CF__BitScanReverse_SUPPORT, STLSOFT_CF__BitScanReverse64_SUPPORT */

#if 0
#elif defined(_MSC_VER) &&\
     _MSC_VER >= 1400

# define STLSOFT_CF__BitScanReverse_SUPPORT
# if 0 ||\
     defined(_M_ARM64) ||\
     defined(_M_ARM64EC) ||\
     defined(_M_X64) ||\
     0

#  define STLSOFT_CF__BitScanReverse64_SUPPORT
# endif
#endif


/* STLSOFT_CF__builtin_clz_SUPPORT, STLSOFT_CF__builtin_clzll_SUPPORT */

#if 0
#elif defined(__has_builtin)

# if __has_builtin(__builtin_clz)

#  define STLSOFT_CF__builtin_clz_SUPPORT
# endif

# if __has_builtin(__builtin_clzll)

#  define STLSOFT_CF__builtin_clzll_SUPPORT
# endif
#endif

#ifndef STLSOFT_CF__builtin_clz_SUPPORT

# if 0
# elif defined(STLSOFT_CLANG_VER) &&\
     STLSOFT_CLANG_VER >= 40000

#  define STLSOFT_CF__builtin_clz_SUPPORT
# elif defined(STLSOFT_GCC_VER) &&\
     STLSOFT_GCC_VER >= 30400

#  define STLSOFT_CF__builtin_clz_SUPPORT
# endif
#endif

#ifndef STLSOFT_CF__builtin_clzll_SUPPORT

# if 0
# elif defined(STLSOFT_CLANG_VER) &&\
     STLSOFT_CLANG_VER >= 40000

#  define STLSOFT_CF__builtin_clzll_SUPPORT
# elif defined(STLSOFT_GCC_VER) &&\
     STLSOFT_GCC_VER >= 30400

#  define STLSOFT_CF__builtin_clzll_SUPPORT
# endif
#endif


/* /////////////////////////////////////////////////////////
 * "Population count"
 *
 *   - STLSOFT_CF__builtin_popcount_SUPPORT
 *   - STLSOFT_CF__builtin_popcountll_SUPPORT
 *   - STLSOFT_CF__popcnt16_SUPPORT
 *   - STLSOFT_CF__popcnt_SUPPORT
 *   - STLSOFT_CF__popcnt64_SUPPORT
 */

/* STLSOFT_CF__builtin_popcount_SUPPORT, STLSOFT_CF__builtin_popcountll_SUPPORT */

#if 0
#elif defined(__has_builtin)

# if __has_builtin(__builtin_popcount)

#  define STLSOFT_CF__builtin_popcount_SUPPORT
# endif

# if __has_builtin(__builtin_popcountll)

#  define STLSOFT_CF__builtin_popcountll_SUPPORT
# endif
#endif

#ifndef STLSOFT_CF__builtin_popcount_SUPPORT

# if 0
# elif defined(STLSOFT_CLANG_VER) &&\
     STLSOFT_CLANG_VER >= 40000

#  define STLSOFT_CF__builtin_popcount_SUPPORT
# elif defined(STLSOFT_GCC_VER) &&\
     STLSOFT_GCC_VER >= 30400

#  define STLSOFT_CF__builtin_popcount_SUPPORT
# endif
#endif

#ifndef STLSOFT_CF__builtin_popcountll_SUPPORT

# if 0
# elif defined(STLSOFT_CLANG_VER) &&\
     STLSOFT_CLANG_VER >= 40000

#  define STLSOFT_CF__builtin_popcountll_SUPPORT
# elif defined(STLSOFT_GCC_VER) &&\
     STLSOFT_GCC_VER >= 30400

#  define STLSOFT_CF__builtin_popcountll_SUPPORT
# endif
#endif


/* STLSOFT_CF__popcnt16_SUPPORT, STLSOFT_CF__popcnt_SUPPORT
 *
 * x86 and x64 from MSVC 15.00. ARM64 from Visual Studio 2022 17.11
 * (_MSC_VER 1941). Not 32-bit ARM. Not ARM64EC: those two intrinsics
 * are declared for x86, x64, and ARM64 only.
 */

#if 0
#elif 1 &&\
      defined(_MSC_VER) &&\
      _MSC_VER >= 1500 &&\
      ( 0 ||\
        defined(_M_IX86) ||\
        defined(_M_X64) ||\
        0) &&\
      1

# define STLSOFT_CF__popcnt16_SUPPORT
# define STLSOFT_CF__popcnt_SUPPORT
#elif 1 &&\
      defined(_MSC_VER) &&\
      _MSC_VER >= 1941 &&\
      defined(_M_ARM64) &&\
      1

# define STLSOFT_CF__popcnt16_SUPPORT
# define STLSOFT_CF__popcnt_SUPPORT
#endif


/* STLSOFT_CF__popcnt64_SUPPORT
 *
 * x64 from MSVC 15.00. ARM64 and ARM64EC from Visual Studio 2022 17.11
 * (_MSC_VER 1941).
 */

#if 0
#elif defined(_MSC_VER) &&\
     _MSC_VER >= 1500 &&\
     defined(_M_X64)

# define STLSOFT_CF__popcnt64_SUPPORT
#elif defined(_MSC_VER) &&\
     _MSC_VER >= 1941 &&\
     (  0 ||\
        defined(_M_ARM64) ||\
        defined(_M_ARM64EC) ||\
        0)

# define STLSOFT_CF__popcnt64_SUPPORT
#endif


/* /////////////////////////////////////////////////////////////////////////
 * includes - 2
 */

#if 0
#elif 0 ||\
      defined(STLSOFT_CF__popcnt16_SUPPORT) ||\
      defined(STLSOFT_CF__popcnt_SUPPORT) ||\
      defined(STLSOFT_CF__popcnt64_SUPPORT) ||\
      defined(STLSOFT_CF__BitScanReverse_SUPPORT) ||\
      defined(STLSOFT_CF__BitScanReverse64_SUPPORT) ||\
      0

# include <intrin.h>
#endif


/* /////////////////////////////////////////////////////////////////////////
 * bit functions
 */

#ifndef STLSOFT_API_EXTERNAL_bitfns_BitScanReverse_uint32

# if 0
# elif defined(STLSOFT_CF__BitScanReverse_SUPPORT)

#  define STLSOFT_API_EXTERNAL_bitfns_BitScanReverse_uint32 _BitScanReverse
# else

# endif
#endif /* !STLSOFT_API_EXTERNAL_bitfns_BitScanReverse_uint32 */


#ifndef STLSOFT_API_EXTERNAL_bitfns_BitScanReverse_uint64

# if 0
# elif defined(STLSOFT_CF__BitScanReverse64_SUPPORT)

#  define STLSOFT_API_EXTERNAL_bitfns_BitScanReverse_uint64 _BitScanReverse64
# else

# endif
#endif /* !STLSOFT_API_EXTERNAL_bitfns_BitScanReverse_uint64 */


#ifndef STLSOFT_API_EXTERNAL_bitfns_clz_uint

# if 0
# elif defined(STLSOFT_CF__builtin_clz_SUPPORT)

#  define STLSOFT_API_EXTERNAL_bitfns_clz_uint              __builtin_clz
# else

# endif
#endif /* !STLSOFT_API_EXTERNAL_bitfns_clz_uint */


#ifndef STLSOFT_API_EXTERNAL_bitfns_clz_ullong

# if 0
# elif defined(STLSOFT_CF__builtin_clzll_SUPPORT)

#  define STLSOFT_API_EXTERNAL_bitfns_clz_ullong            __builtin_clzll
# else

# endif
#endif /* !STLSOFT_API_EXTERNAL_bitfns_clz_ullong */


#ifndef STLSOFT_API_EXTERNAL_bitfns_popcount_uint

# if 0
# elif defined(STLSOFT_CF__builtin_popcount_SUPPORT)

#  define STLSOFT_API_EXTERNAL_bitfns_popcount_uint         __builtin_popcount
# else

# endif
#endif /* !STLSOFT_API_EXTERNAL_bitfns_popcount_uint */


#ifndef STLSOFT_API_EXTERNAL_bitfns_popcount_ullong

# if 0
# elif defined(STLSOFT_CF__builtin_popcountll_SUPPORT)

#  define STLSOFT_API_EXTERNAL_bitfns_popcount_ullong       __builtin_popcountll
# else

# endif
#endif /* !STLSOFT_API_EXTERNAL_bitfns_popcount_ullong */


#ifndef STLSOFT_API_EXTERNAL_bitfns_popcnt_uint16

# if 0
# elif defined(STLSOFT_CF__popcnt16_SUPPORT)

#  define STLSOFT_API_EXTERNAL_bitfns_popcnt_uint16         __popcnt16
# else

# endif
#endif /* !STLSOFT_API_EXTERNAL_bitfns_popcnt_uint16 */


#ifndef STLSOFT_API_EXTERNAL_bitfns_popcnt_uint32

# if 0
# elif defined(STLSOFT_CF__popcnt_SUPPORT)

#  define STLSOFT_API_EXTERNAL_bitfns_popcnt_uint32         __popcnt
# else

# endif
#endif /* !STLSOFT_API_EXTERNAL_bitfns_popcnt_uint32 */


#ifndef STLSOFT_API_EXTERNAL_bitfns_popcnt_uint64

# if 0
# elif defined(STLSOFT_CF__popcnt64_SUPPORT)

#  define STLSOFT_API_EXTERNAL_bitfns_popcnt_uint64         __popcnt64
# else

# endif
#endif /* !STLSOFT_API_EXTERNAL_bitfns_popcnt_uint64 */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_bitfns */

/* ///////////////////////////// end of file //////////////////////////// */

