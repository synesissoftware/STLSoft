/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/util/count_digits.h
 *
 * Purpose: Functions for efficient counting of digits in integers.
 *
 * Created: 18th December 2024
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2024, Matthew Wilson and Synesis Information Systems
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


/** \file stlsoft/util/count_digits.h
 *
 * \brief [C, C++] Functions for efficient counting of digits in integers
 *   (\ref group__library__Utility "Utility" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DIGITS
#define STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DIGITS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DIGITS_MAJOR    1
# define STLSOFT_VER_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DIGITS_MINOR    0
# define STLSOFT_VER_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DIGITS_REVISION 2
# define STLSOFT_VER_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DIGITS_EDIT     2
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


#ifndef STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DECIMAL_DIGITS
# include <stlsoft/util/count_digits/count_decimal_digits.h>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DECIMAL_DIGITS */
#ifndef STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_HEXADECIMAL_DIGITS
# include <stlsoft/util/count_digits/count_hexadecimal_digits.h>
#endif /* !STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_HEXADECIMAL_DIGITS */



/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_UTIL_INCL_COUNT_DIGITS_H_COUNT_DIGITS */

/* ///////////////////////////// end of file //////////////////////////// */

