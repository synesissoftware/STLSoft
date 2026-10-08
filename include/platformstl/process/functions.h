/* /////////////////////////////////////////////////////////////////////////
 * File:    platformstl/process/functions.h
 *
 * Purpose: Process functions.
 *
 * Created: 8th October 2026
 * Updated: 8th October 2026
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


/** \file platformstl/process/functions.h
 *
 * \brief [C, C++] Process functions
 *   (\ref group__library__System "System" Library).
 */

#ifndef PLATFORMSTL_INCL_PLATFORMSTL_PROCESS_H_FUNCTIONS
#define PLATFORMSTL_INCL_PLATFORMSTL_PROCESS_H_FUNCTIONS

#ifndef PLATFORMSTL_DOCUMENTATION_SKIP_SECTION
# define PLATFORMSTL_VER_PLATFORMSTL_PROCESS_H_FUNCTIONS_MAJOR      1
# define PLATFORMSTL_VER_PLATFORMSTL_PROCESS_H_FUNCTIONS_MINOR      0
# define PLATFORMSTL_VER_PLATFORMSTL_PROCESS_H_FUNCTIONS_REVISION   1
# define PLATFORMSTL_VER_PLATFORMSTL_PROCESS_H_FUNCTIONS_EDIT       1
#endif /* !PLATFORMSTL_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef PLATFORMSTL_INCL_PLATFORMSTL_H_PLATFORMSTL
# include <platformstl/platformstl.h>
#endif /* !PLATFORMSTL_INCL_PLATFORMSTL_H_PLATFORMSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */

#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

# include <unixstl/process/functions.h>
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

# include <winstl/process/functions.h>
#else

# error Operating system not discriminated
#endif

#include <stlsoft/quality/contract.h>
#include <stlsoft/quality/cover.h>


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#if !defined(PLATFORMSTL_NO_NAMESPACE) && \
    !defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
# if defined(STLSOFT_NO_NAMESPACE)
/* There is no stlsoft namespace, so must define ::platformstl */
namespace platformstl
{
# else
/* Define stlsoft::platformstl_project */
namespace stlsoft
{
namespace platformstl_project
{
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !PLATFORMSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * functions (C)
 */

STLSOFT_INLINE
int
platformstl_C_get_current_process_id(void)
{
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

    return UNIXSTL_NS_QUAL(unixstl_C_get_current_process_id)();
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    return WINSTL_NS_QUAL(winstl_C_get_current_process_id)();
#else

# error Platform not discriminated
#endif
}


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef PLATFORMSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
} /* namespace platformstl */
# else
} /* namespace platformstl_project */
} /* namespace stlsoft */
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !PLATFORMSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !PLATFORMSTL_INCL_PLATFORMSTL_PROCESS_H_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */

