/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/system/environment/functions.h
 *
 * Purpose: Environment functions.
 *
 * Created: 4th March 2011
 * Updated: 8th October 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2005-2019, Matthew Wilson and Synesis Software
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


/** \file stlsoft/system/environment/functions.h
 *
 * \brief [C, C++] Environment functions
 *   (\ref group__library__System "System" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_SYSTEM_ENVIRONMENT_H_FUNCTIONS
#define STLSOFT_INCL_STLSOFT_SYSTEM_ENVIRONMENT_H_FUNCTIONS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_SYSTEM_ENVIRONMENT_H_FUNCTIONS_MAJOR       1
# define STLSOFT_VER_STLSOFT_SYSTEM_ENVIRONMENT_H_FUNCTIONS_MINOR       0
# define STLSOFT_VER_STLSOFT_SYSTEM_ENVIRONMENT_H_FUNCTIONS_REVISION    4
# define STLSOFT_VER_STLSOFT_SYSTEM_ENVIRONMENT_H_FUNCTIONS_EDIT        16
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

#ifndef STLSOFT_INCL_H_ERRNO
# define STLSOFT_INCL_H_ERRNO
# include <errno.h>
#endif /* !STLSOFT_INCL_H_ERRNO */
#ifndef STLSOFT_INCL_H_STDLIB
# define STLSOFT_INCL_H_STDLIB
# include <stdlib.h>
#endif /* !STLSOFT_INCL_H_STDLIB */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * API functions (C)
 */

/** Indicates whether the named environment variable exists.
 *
 * \retval 0 The environment variable does not exist;
 * \retval !0 The environment variable does exist;
 *
 * \pre (NULL != name)
 */
STLSOFT_INLINE
ss_truthy_t
stlsoft_C_environment_variable_exists_m(
    char const* name
) STLSOFT_NOEXCEPT
{
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS) && \
    defined(STLSOFT_COMPILER_IS_MSVC)

    char    buff[1];
    size_t  n;
    errno_t e = STLSOFT_NS_GLOBAL(getenv_s)(&n, &buff[0], STLSOFT_NUM_ELEMENTS(buff), name);

    if (0 == e)
    {
        if (0 == n)
        {
            // variable doesn't exist
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (ERANGE == e)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
#else

    return NULL != STLSOFT_NS_GLOBAL(getenv)(name);
#endif
}
#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

/** [DEPRECATED]  \see stlsoft_C_environment_variable_exists_m
 *
 */
STLSOFT_DEPRECATED_("`stlsoft_C_environment_variable_exists_a()` is deprecated, and will be removed from a future release, and you should instead use `stlsoft_C_environment_variable_exists_m()`") // applied here rather than on template because above class_type precipitates
STLSOFT_INLINE
ss_truthy_t
stlsoft_C_environment_variable_exists_a(
    char const* name
) STLSOFT_NOEXCEPT
{
    return stlsoft_C_environment_variable_exists_m(name);
}
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * language
 */

#ifdef __cplusplus


/* /////////////////////////////////////////////////////////////////////////
 * API functions (C++)
 */

/** \see stlsoft_C_environment_variable_exists_m
 */
inline
ss_truthy_t
environment_variable_exists(
    char const* name
)
{
    return stlsoft_C_environment_variable_exists_m(name);
}


/* /////////////////////////////////////////////////////////////////////////
 * language
 */

#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} /* namespace stlsoft */
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_SYSTEM_ENVIRONMENT_H_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */

