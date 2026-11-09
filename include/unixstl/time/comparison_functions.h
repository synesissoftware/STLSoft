/* /////////////////////////////////////////////////////////////////////////
 * File:    unixstl/time/comparison_functions.h
 *
 * Purpose: Comparison functions for UNIX time structures.
 *
 * Created: 19th November 2024
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


/** \file unixstl/time/comparison_functions.h
 *
 * \brief [C, C++] Comparison functions for UNIX time types
 *   (\ref group__library__Time "Time" Library).
 */

#ifndef UNIXSTL_INCL_UNIXSTL_TIME_H_COMPARISON_FUNCTIONS
#define UNIXSTL_INCL_UNIXSTL_TIME_H_COMPARISON_FUNCTIONS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define UNIXSTL_VER_UNIXSTL_TIME_H_COMPARISON_FUNCTIONS_MAJOR      1
# define UNIXSTL_VER_UNIXSTL_TIME_H_COMPARISON_FUNCTIONS_MINOR      0
# define UNIXSTL_VER_UNIXSTL_TIME_H_COMPARISON_FUNCTIONS_REVISION   3
# define UNIXSTL_VER_UNIXSTL_TIME_H_COMPARISON_FUNCTIONS_EDIT       3
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef UNIXSTL_INCL_UNIXSTL_H_UNIXSTL
# include <unixstl/unixstl.h>
#endif /* !UNIXSTL_INCL_UNIXSTL_H_UNIXSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#ifndef STLSOFT_INCL_H_STRING
# define STLSOFT_INCL_H_STRING
# include <string.h>
#endif /* !STLSOFT_INCL_H_STRING */
#ifndef STLSOFT_INCL_SYS_H_TIME
# define STLSOFT_INCL_SYS_H_TIME
# include <sys/time.h>
#endif /* !STLSOFT_INCL_SYS_H_TIME */

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_memfns
# include <stlsoft/api/external/memfns.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_memfns */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#if !defined(UNIXSTL_NO_NAMESPACE) && \
    !defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
# if defined(STLSOFT_NO_NAMESPACE)
/* There is no stlsoft namespace, so must define ::unixstl */
namespace unixstl
{
# else
/* Define stlsoft::unixstl_project */
namespace stlsoft
{
namespace unixstl_project
{
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !UNIXSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * C functions
 */

/** Compares two <code>struct timeval</code> instances
 *
 * \ingroup group__library__Time
 *
 * \pre nullptr != lhs
 * \pre nullptr != rhs
 */
STLSOFT_INLINE
us_sint_t
unixstl_C_compare_timevals(
    struct timeval const*   lhs
,   struct timeval const*   rhs
)
{
    UNIXSTL_ASSERT(NULL != lhs);
    UNIXSTL_ASSERT(NULL != rhs);

    if (0 == STLSOFT_API_EXTERNAL_memfns_memcmp(lhs, rhs, sizeof(struct timeval)))
    {
        return 0;
    }
    else
    {
        us_sint64_t const lhs_us = lhs->tv_sec * 1000 * 1000 + lhs->tv_usec;
        us_sint64_t const rhs_us = rhs->tv_sec * 1000 * 1000 + rhs->tv_usec;

        if (lhs_us < rhs_us)
        {
            return -1;
        }

        if (lhs_us > rhs_us)
        {
            return +1;
        }

        return 0;
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifdef STLSOFT_DOCUMENTATION_SKIP_SECTION
namespace unixstl
{
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * C++ functions
 */

#ifdef __cplusplus

/** Compares two <code>struct timeval</code> instances
 *
 * Implemented in terms of unixstl_C_compare_timevals()
 *
 * \ingroup group__library__Time
 */
inline
us_sint_t
compare(
    struct timeval const&   lhs
,   struct timeval const&   rhs
)
{
    return unixstl_C_compare_timevals(&lhs, &rhs);
}

/** Compares two <code>struct timeval</code> instances
 *
 * Implemented in terms of unixstl_C_compare_timevals()
 *
 * \ingroup group__library__Time
 */
inline
us_sint_t
compare(
    struct timeval const*   lhs
,   struct timeval const*   rhs
)
{
    return unixstl_C_compare_timevals(lhs, rhs);
}
#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef UNIXSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
} /* namespace unixstl */
# else
} /* namespace unixstl_project */
} /* namespace stlsoft */
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !UNIXSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !UNIXSTL_INCL_UNIXSTL_TIME_H_COMPARISON_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */

