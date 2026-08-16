/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/internal/cccap/tinycc.h
 *
 * Purpose: Compiler feature discrimination for Tiny C Compiler.
 *
 * Created: 17th August 2026
 * Updated: 17th August 2026
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


/* STLSOFT:FILE_EXCEPTED */

#ifndef STLSOFT_INCL_STLSOFT_H_STLSOFT
# error This file must not be included independently of stlsoft/stlsoft.h
#endif /* !STLSOFT_INCL_STLSOFT_H_STLSOFT */

/** \file stlsoft/internal/cccap/tinycc.h
 *
 * Compiler feature discrimination for Tiny C Compiler
 */

#ifdef STLSOFT_INCL_H_STLSOFT_CCCAP_TINYCC
# error This file cannot be included more than once in any compilation unit
#endif /* STLSOFT_INCL_H_STLSOFT_CCCAP_TINYCC */


#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_H_STLSOFT_CCCAP_TINYCC_MAJOR       1
# define STLSOFT_VER_H_STLSOFT_CCCAP_TINYCC_MINOR       0
# define STLSOFT_VER_H_STLSOFT_CCCAP_TINYCC_REVISION    0
# define STLSOFT_VER_H_STLSOFT_CCCAP_TINYCC_EDIT        1
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * Structure:
 *
 * - predefined macros extensions
 * - custom macros
 * - preprocessor features
 * - compiler-specific features
 * - support for built-in types
 * - built-in type characteristics
 * - size-specific integer types
 * - support for C/C++ language features
 * - support for C language features
 * - inline assembler
 * - linkage specification
 * - atomics support
 * - calling convention
 * - integer sizes
 * - integral types
 * - still-to-be-determined features
 * - quality assurance features
 * - compiler warning suppression
 * - obsolete features
 */


/* /////////////////////////////////////////////////////////////////////////
 * predefined macros extensions
 */


/* /////////////////////////////////////////////////////////////////////////
 * custom macros
 */


/* /////////////////////////////////////////////////////////////////////////
 * preprocessor features
 *
 * - #pragma message
 * - #pragma once
 * - __COUNTER__
 * - __func__
 * - __FUNCTION__
 * - variadic macros
 */

/* #define STLSOFT_PPF_pragma_message_SUPPORT */

/* #define STLSOFT_PPF_pragma_once_SUPPORT */

/* #define STLSOFT_PPF_COUNTER_SYMBOL_SUPPORT */

#define STLSOFT_PPF_func_SYMBOL_SUPPORT

#define STLSOFT_PPF_FUNCTION_SYMBOL_SUPPORT

#define STLSOFT_PPF_PRETTY_FUNCTION_SYMBOL_SUPPORT

#define STLSOFT_PPF_VARIADIC_MACROS_SUPPORT


/* /////////////////////////////////////////////////////////////////////////
 * compiler-specific features
 */

/* TinyCC does not implement `#pragma GCC diagnostic`, including builds
 * that define `__GNUC__` (such as the `mob` development branch).
 */


/* /////////////////////////////////////////////////////////////////////////
 * support for built-in types
 *
 * - bool
 * - wchar_t
 * - long long
 * - __int8
 * - __int16
 * - __int32
 * - __int64
 * - long double
 */

#define STLSOFT_CF_BUILTIN_long_long_SUPPORT


/* /////////////////////////////////////////////////////////////////////////
 * built-in type characteristics
 *
 * - char is unsigned
 * - wchar_t
 *    - synthesised
 *    - available
 */

#ifdef __CHAR_UNSIGNED__
# define STLSOFT_CF_char_IS_UNSIGNED
#endif /* __CHAR_UNSIGNED__ */

#ifdef __WCHAR_TYPE__
# define STLSOFT_CF_NATIVE_WCHAR_T_SUPPORT
#endif /* __WCHAR_TYPE__ */


/* /////////////////////////////////////////////////////////////////////////
 * support for C/C++ language features
 *
 * - return void
 * - static assertions
 * - anonymous unions
 * - -ve % +ve => -ve result
 *
 *
 * static assertions
 * -----------------
 *
 * Two questions:
 *
 * 1. Are STLSoft-style static assertions (see stlsoft/stlsoft.h)
 * supported by the compiler? This is indicated by the definition of the
 * preprocessor symbol STLSOFT_CF_STATIC_ASSERT_SUPPORT
 *
 * 2. Is the C++11 static_assert keyword supported? This is indicated by the
 * definition of the preprocessor symbol STLSOFT_CF_static_assert_SUPPORT
 */

#define STLSOFT_CF_return_void_SUPPORT

#define STLSOFT_CF_STATIC_ASSERT_SUPPORT

#define STLSOFT_CF_ANONYMOUS_UNION_SUPPORT

#define STLSOFT_CF_NEGATIVE_MODULUS_POSITIVE_GIVES_NEGATIVE_RESULT


/* /////////////////////////////////////////////////////////////////////////
 * support for C language features
 *
 * - inline
 *    - C99 inline keyword
 *    - compiler-specific keyword
 */

#ifndef __cplusplus

 /* TinyCC follows C99 `inline` semantics, not GNU `extern inline`.
  * `static inline` is the portable choice for header helpers.
  */
# define STLSOFT_CUSTOM_C_INLINE                            static inline
#endif


/* /////////////////////////////////////////////////////////////////////////
 * inline assembler
 */

/* #define STSLSOFT_INLINE_ASM_SUPPORTED */
/* #define STSLSOFT_ASM_IN_INLINE_SUPPORTED */


/* /////////////////////////////////////////////////////////////////////////
 * linkage specification
 */


/* /////////////////////////////////////////////////////////////////////////
 * atomics support
 */

/* TinyCC does not provide GCC `__atomic_*` builtins. */


/* /////////////////////////////////////////////////////////////////////////
 * calling convention
 */

#define STLSOFT_CF_CDECL_SUPPORTED

#ifdef STLSOFT_CF_CDECL_SUPPORTED
# define STLSOFT_CDECL
#endif /* STLSOFT_CF_CDECL_SUPPORTED */


/* /////////////////////////////////////////////////////////////////////////
 * integer sizes
 */

#define _STLSOFT_SIZEOF_CHAR                                (1)

#if 0
#elif 0 ||\
      defined(__ILP64__) ||\
      defined(_ILP64) ||\
      0
# error Currently the STLSoft libraries are not compatible with the ILP64 memory model
#elif 0 ||\
      defined(__LP64__) ||\
      defined(_LP64) ||\
      0
 /* LP64 */
# define _STLSOFT_SIZEOF_SHORT                              (2)
# define _STLSOFT_SIZEOF_INT                                (4)
# define _STLSOFT_SIZEOF_LONG                               (8)
# define _STLSOFT_SIZEOF_LONG_LONG                          (8)
#elif 0 || \
      defined(__LLP64__) || \
      defined(_WIN32) || \
      defined(_WIN64) || \
      defined(__i386__) || \
      defined(__i386) || \
      defined(__arm__) || \
      0
 /* LLP64 / ILP32 */
# define _STLSOFT_SIZEOF_SHORT                              (2)
# define _STLSOFT_SIZEOF_INT                                (4)
# define _STLSOFT_SIZEOF_LONG                               (4)
# define _STLSOFT_SIZEOF_LONG_LONG                          (8)
#else /* ? data model */
# error Use of Tiny C Compiler has not been verified with any memory model other than LP64 and LLP64/ILP32
#endif /* data model */

#ifdef __SIZEOF_INT__
# if __SIZEOF_INT__ != _STLSOFT_SIZEOF_INT
#  error `_STLSOFT_SIZEOF_INT` does not match TinyCC `__SIZEOF_INT__`
# endif
#endif
#ifdef __SIZEOF_LONG__
# if __SIZEOF_LONG__ != _STLSOFT_SIZEOF_LONG
#  error `_STLSOFT_SIZEOF_LONG` does not match TinyCC `__SIZEOF_LONG__`
# endif
#endif
#ifdef __SIZEOF_LONG_LONG__
# if __SIZEOF_LONG_LONG__ != _STLSOFT_SIZEOF_LONG_LONG
#  error `_STLSOFT_SIZEOF_LONG_LONG` does not match TinyCC `__SIZEOF_LONG_LONG__`
# endif
#endif


/* /////////////////////////////////////////////////////////////////////////
 * size-specific integer types
 *
 * The purpose of this section is to define the following types:
 *
 *  - 8-bit signed and unsigned integers
 *  - 16-bit signed and unsigned integers
 *  - 32-bit signed and unsigned integers
 *  - (optionally) 64-bit signed and unsigned integers
 */


/* /////////////////////////////////////////////////////////////////////////
 * integral types
 */

/* 8-bit integer */
#define STLSOFT_CF_8BIT_INT_SUPPORT
#define STLSOFT_SI08_T_BASE_TYPE                            signed      char
#define STLSOFT_UI08_T_BASE_TYPE                            unsigned    char

/* 16-bit integer */
#define STLSOFT_CF_16BIT_INT_SUPPORT
#define STLSOFT_SI16_T_BASE_TYPE                            signed      short
#define STLSOFT_UI16_T_BASE_TYPE                            unsigned    short

/* 32-bit integer */
#define STLSOFT_CF_32BIT_INT_SUPPORT
#define STLSOFT_SI32_T_BASE_TYPE                            signed      int
#define STLSOFT_UI32_T_BASE_TYPE                            unsigned    int
#define STLSOFT_CF_LONG_DISTINCT_INT_TYPE

/* 64-bit integer */
#define STLSOFT_CF_64BIT_INT_SUPPORT
#define STLSOFT_CF_64BIT_INT_IS_long_long
#define STLSOFT_SI64_T_BASE_TYPE                            signed      long long
#define STLSOFT_UI64_T_BASE_TYPE                            unsigned    long long

/* ptr-bit integer */
#ifdef __INTPTR_TYPE__
# define STLSOFT_SPTR_T_BASE_TYPE                           __INTPTR_TYPE__
#endif
#ifdef __UINTPTR_TYPE__
# define STLSOFT_UPTR_T_BASE_TYPE                           __UINTPTR_TYPE__
#endif


/* /////////////////////////////////////////////////////////////////////////
 * still-to-be-determined features
 */


/* /////////////////////////////////////////////////////////////////////////
 * quality assurance features
 */

#if defined(_STLSOFT_CUSTOM_ASSERT)
 /* You have defined the preprocessor symbol _STLSOFT_CUSTOM_ASSERT,
  * which stipulates that you will be providing your own assert. This
  * requires that you have defined _STLSOFT_CUSTOM_ASSERT() as a macro
  * taking 1 parameter (the condition to assert).
  *
  * Suppose you have a function DisplayAssert_(), which has the
  * following signature:
  *
  *   void DisplayAssert_(char const* file, int line, char const* expression);
  *
  * Presumably you would also have your own assert macro, say MY_ASSERT(),
  * defined as:
  *
  *   #define MY_ASSERT(expr) ((void)((!(expr)) ? ((void)(DisplayAssert_(__FILE__, __LINE__, #expr))) : ((void)0)))
  *
  * so you would simply need to define _STLSOFT_CUSTOM_ASSERT() in terms of
  * MY_ASSERT(), as in:
  *
  *  #define _STLSOFT_CUSTOM_ASSERT(expr)    MY_ASSERT(expr)
  *
  * where
  */
# define __STLSOFT_CF_ASSERT_SUPPORT
# define STLSOFT_CF_ASSERT_SUPPORT
# define STLSOFT_ASSERT(expr)                               _STLSOFT_CUSTOM_ASSERT(expr)
# if defined(_STLSOFT_CUSTOM_ASSERT_INCLUDE)
#  define   __STLSOFT_CF_ASSERT_INCLUDE_NAME                _STLSOFT_CUSTOM_ASSERT_INCLUDE
# else
#  error You must define _STLSOFT_CUSTOM_ASSERT_INCLUDE along with _STLSOFT_CUSTOM_ASSERT()
# endif /* !_STLSOFT_CUSTOM_ASSERT_INCLUDE */
#else /* ? _STLSOFT_CUSTOM_ASSERT */
# define __STLSOFT_CF_ASSERT_SUPPORT
# define STLSOFT_CF_ASSERT_SUPPORT
# define __STLSOFT_CF_ASSERT_INCLUDE_NAME                   <assert.h>
# define STLSOFT_ASSERT(expr)                               assert(expr)
#endif /* _STLSOFT_CUSTOM_ASSERT */


/* /////////////////////////////////////////////////////////////////////////
 * compiler warning suppression
 */


/* /////////////////////////////////////////////////////////////////////////
 * obsolete features
 */

#include <stlsoft/internal/cccap/obsolete.h>


/* ///////////////////////////// end of file //////////////////////////// */
