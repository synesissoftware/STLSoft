/* /////////////////////////////////////////////////////////////////////////
 * File:    inetstl/util/uds_helpers.h
 *
 * Purpose: Unix Domain Sockets helper functions
 *
 * Created: 21st February 2025
 * Updated: 15th October 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2025, Matthew Wilson and Synesis Information Systems
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


/** \file inetstl/util/uds_helpers.h
 *
 * \brief [C, C++] Unix Domain Sockets helper functions
 *   (\ref group__library__Network "Network" Library).
 */

#ifndef INETSTL_INCL_INETSTL_UTIL_H_UDS_HELPERS
#define INETSTL_INCL_INETSTL_UTIL_H_UDS_HELPERS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define INETSTL_VER_INETSTL_UTIL_H_UDS_HELPERS_MAJOR       1
# define INETSTL_VER_INETSTL_UTIL_H_UDS_HELPERS_MINOR       0
# define INETSTL_VER_INETSTL_UTIL_H_UDS_HELPERS_REVISION    2
# define INETSTL_VER_INETSTL_UTIL_H_UDS_HELPERS_EDIT        5
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes - 1
 */

#ifndef INETSTL_INCL_INETSTL_H_INETSTL
# include <inetstl/inetstl.h>
#endif /* !INETSTL_INCL_INETSTL_H_INETSTL */
#ifdef STLSOFT_TRACE_INCLUDE
# pragma message(__FILE__)
#endif /* STLSOFT_TRACE_INCLUDE */


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if 0
#elif defined(INETSTL_OS_IS_LINUX)

#elif defined(INETSTL_OS_IS_MACOSX)

#else

# error This file not supported currently for operating systems other than Linux and macOS. Patches are welcomed
#endif


/* /////////////////////////////////////////////////////////////////////////
 * includes - 2
 */

#ifndef _WIN32
# ifndef STLSOFT_INCL_H_SYS_UN
#  define STLSOFT_INCL_H_SYS_UN
#  include <sys/un.h>
# endif /* !STLSOFT_INCL_H_SYS_UN */
#endif /* _WIN32 */

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

#ifndef STLSOFT_INCL_STLSOFT_API_external_h_memfns
# include <stlsoft/api/external/memfns.h>
#endif /* !STLSOFT_INCL_STLSOFT_API_external_h_memfns */


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Path initialise an instance of `struct sockaddr_un` suitable for passing
 * to `bind()`.
 *
 * @param sa_un Pointer to an instance of `struct sockaddr_un` (or memory
 *  that will be interpreted as such). May not be NULL;
 * @param cb_sa_un Number of accessible bytes in sa_un, which must be at
 *  least 1 + offsetof(struct sockaddr_un, sun_path);
 * @param path Path to be written into `sa_un`;
 * @param pcb_actual Pointer to variable to obtain the actual size of the
 *  path-initialised. May not be NULL;
 *
 * @retval -1 The function failed, and global `errno` has been updated;
 * @retval 0 The function succeeded such that the contents of `sa_un` have
 *  been filled out correctly and the actual size written into
 *  `*pcb_actual`;
 *
 * errno values set in the current conditions:
 *  -# `EINVAL` — path cannot fit into fixed size of `sockaddr_un#sun_path;
 *  -# `EINVAL` — cb_sa_un is smaller than 1 + offsetof(struct sockaddr_un, sun_path);
 *  -# `EINVAL` — path cannot fit into given storage size;
 */
int
inetstl_c_sockaddr_un_init_from_path(
    struct sockaddr_un* sa_un
,   size_t              cb_sa_un
,   char const*         path
,   size_t*             pcb_actual
)
{
    STLSOFT_ASSERT(NULL != sa_un);
    STLSOFT_ASSERT(NULL != pcb_actual);

    *pcb_actual = 0;

    {
        /* As documented in numerous sources, there are some significant
         * idiosynchracies and operating-system differences to be handled,
         * including:
         *
         * - on macOS, `sockaddr_un` has field `sun_len`, which is not
         *   present on Linux;
         * - the field `sun_path` has a fixed size (of 104, or 108, or ...),
         *   and there are some differences in whether a NUL character is
         *   required, hence if the path length is exactly the same as the
         *   available fixed space then there is an issue;
         *
         * Thus, the following complexity (and why not using `SUN_LEN()`).
         */

        size_t const    sa_un_fixed_size    =   offsetof(struct sockaddr_un, sun_path);
        size_t const    sa_cch_sun_path     =   STLSOFT_NUM_ELEMENTS(((struct sockaddr_un*)0)->sun_path);
        size_t const    len_path            =   (NULL == path) ? (path = "", 0) : strlen(path);


#if defined(INETSTL_OS_IS_MACOSX)

        /* on macOS the `sun_len` field is `unsigned char` */
        STLSOFT_STATIC_ASSERT(STLSOFT_NUM_ELEMENTS(((struct sockaddr_un*)0)->sun_path) <= 255);
#endif


        /* provided storage size is not sufficient for even an empty path */
        if (sa_un_fixed_size + 1 > cb_sa_un)
        {
            errno = EINVAL;

            return -1;
        }

        /* path-length is too long for fixed (i.e. maximum) size */
        if (len_path > sa_cch_sun_path)
        {
            errno = EINVAL;

            return -1;
        }

        /* provided storage size is not sufficient for given path */
        if (sa_un_fixed_size + len_path > cb_sa_un)
        {
            errno = EINVAL;

            return -1;
        }

        {
            size_t const    cch_sun_path    =   cb_sa_un - sa_un_fixed_size;
            size_t const    cb_actual       =   sa_un_fixed_size + len_path + ((len_path < sa_cch_sun_path) ? 1 : 0);

            STLSOFT_ASSERT(cb_actual <= cb_sa_un);

#if defined(INETSTL_OS_IS_MACOSX)

            sa_un->sun_len      =   STLSOFT_C_CAST(unsigned char, cb_actual);
#endif
            sa_un->sun_family   =   AF_UNIX;

            strncpy(&sa_un->sun_path[0], path, cch_sun_path);

            *pcb_actual = cb_actual;

            return 0;
        }
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !INETSTL_INCL_INETSTL_UTIL_H_UDS_HELPERS */

/* ///////////////////////////// end of file //////////////////////////// */

