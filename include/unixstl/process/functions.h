/* /////////////////////////////////////////////////////////////////////////
 * File:    unixstl/process/functions.h
 *
 * Purpose: Process functions.
 *
 * Created: 8th October 2026
 * Updated: 15th October 2026
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


/** \file unixstl/process/functions.h
 *
 * \brief [C, C++] Process functions
 *   (\ref group__library__System "System" Library).
 */

#ifndef UNIXSTL_INCL_UNIXSTL_PROCESS_H_FUNCTIONS
#define UNIXSTL_INCL_UNIXSTL_PROCESS_H_FUNCTIONS

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define UNIXSTL_VER_UNIXSTL_PROCESS_H_FUNCTIONS_MAJOR      1
# define UNIXSTL_VER_UNIXSTL_PROCESS_H_FUNCTIONS_MINOR      1
# define UNIXSTL_VER_UNIXSTL_PROCESS_H_FUNCTIONS_REVISION   1
# define UNIXSTL_VER_UNIXSTL_PROCESS_H_FUNCTIONS_EDIT       2
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

#ifndef STLSOFT_INCL_H_ERRNO
# define STLSOFT_INCL_H_ERRNO
# include <errno.h>
#endif /* !STLSOFT_INCL_H_ERRNO */
#ifndef STLSOFT_INCL_H_LIMITS
# define STLSOFT_INCL_H_LIMITS
# include <limits.h>
#endif /* !STLSOFT_INCL_H_LIMITS */
#ifndef STLSOFT_INCL_H_STDLIB
# define STLSOFT_INCL_H_STDLIB
# include <stdlib.h>
#endif /* !STLSOFT_INCL_H_STDLIB */
#ifndef STLSOFT_INCL_H_STRING
# define STLSOFT_INCL_H_STRING
# include <string.h>
#endif /* !STLSOFT_INCL_H_STRING */

#if 0
#elif defined(_WIN32)

# ifndef WINSTL_INCL_WINSTL_API_external_h_DynamicLinkLibrary
#  include <winstl/api/external/DynamicLinkLibrary.h>
# endif /* !WINSTL_INCL_WINSTL_API_external_h_DynamicLinkLibrary */

# ifndef STLSOFT_INCL_H_PROCESS
#  define STLSOFT_INCL_H_PROCESS
#  include <process.h>
# endif /* !STLSOFT_INCL_H_PROCESS */
# ifndef STLSOFT_INCL_H_WINDOWS
#  define STLSOFT_INCL_H_WINDOWS
#  include <windows.h>
# endif /* !STLSOFT_INCL_H_WINDOWS */
#elif defined(__APPLE__)

# ifndef STLSOFT_INCL_H_LIBPROC
#  define STLSOFT_INCL_H_LIBPROC
#  include <libproc.h>
# endif /* !STLSOFT_INCL_H_LIBPROC */
# ifndef STLSOFT_INCL_MACH_O_H_DYLD
#  define STLSOFT_INCL_MACH_O_H_DYLD
#  include <mach-o/dyld.h>
# endif /* !STLSOFT_INCL_MACH_O_H_DYLD */
# ifndef STLSOFT_INCL_H_UNISTD
#  define STLSOFT_INCL_H_UNISTD
#  include <unistd.h>
# endif /* !STLSOFT_INCL_H_UNISTD */
#elif defined(__linux__)

# ifndef STLSOFT_INCL_H_UNISTD
#  define STLSOFT_INCL_H_UNISTD
#  include <unistd.h>
# endif /* !STLSOFT_INCL_H_UNISTD */
#elif 0 ||\
      defined(__FreeBSD__) ||\
      defined(__NetBSD__) ||\
      defined(__OpenBSD__) ||\
      0

# ifndef STLSOFT_INCL_SYS_H_SYSCTL
#  define STLSOFT_INCL_SYS_H_SYSCTL
#  include <sys/sysctl.h>
# endif /* !STLSOFT_INCL_SYS_H_SYSCTL */
# ifndef STLSOFT_INCL_SYS_H_TYPES
#  define STLSOFT_INCL_SYS_H_TYPES
#  include <sys/types.h>
# endif /* !STLSOFT_INCL_SYS_H_TYPES */
#elif defined(__sun)

# ifndef STLSOFT_INCL_H_UNISTD
#  define STLSOFT_INCL_H_UNISTD
#  include <unistd.h>
# endif /* !STLSOFT_INCL_H_UNISTD */
#else

# ifndef STLSOFT_INCL_SYS_H_TYPES
#  define STLSOFT_INCL_SYS_H_TYPES
#  include <sys/types.h>
# endif /* !STLSOFT_INCL_SYS_H_TYPES */
# ifndef STLSOFT_INCL_H_UNISTD
#  define STLSOFT_INCL_H_UNISTD
#  include <unistd.h>
# endif /* !STLSOFT_INCL_H_UNISTD */
#endif


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
 * functions
 */

/** \brief Obtains the id of the calling process.
 *
 * \ingroup group__library__System
 *
 * \return The process id, as obtained from \c _getpid() on Windows / UNIXem
 *   builds or \c getpid() otherwise.
 */
STLSOFT_INLINE
int
unixstl_C_get_current_process_id(void)
{
#if 0
#elif defined(_WIN32)

    return STLSOFT_NS_GLOBAL(_getpid)();
#else

    STLSOFT_STATIC_ASSERT(sizeof(pid_t) <= sizeof(int));

    return STLSOFT_STATIC_CAST(int, STLSOFT_NS_GLOBAL(getpid)());
#endif
}

/** \brief Obtains the fully qualified path of the current process image
 * (multibyte).
 *
 * \ingroup group__library__System
 *
 * \param buff Destination buffer. May be \c NULL if and only if \c cch is
 *   0;
 * \param cch Number of characters available in \c buff, including space for
 *   a terminating NUL;
 *
 * \return If \c buff is sufficient for the full path and a terminating NUL
 *   character then this returns the length of the path (excluding the NUL
 *   character). Otherwise, as much of the result as can be written is done
 *   so and a character count of <em>at least</em> the full length + 1 (for
 *   the NUL character) is returned. The returned demand may exceed that
 *   minimum. Returns 0 on failure;
 *
 * \pre 0 == cch || NULL != buff
 *
 * \note The normative client pattern is to call with \c cch of 0 to obtain
 *   a sufficient size, allocate, then call again.
 */
STLSOFT_INLINE
us_size_t
unixstl_C_get_current_process_path_m(
    us_char_a_t*    buff
,   us_size_t       cch
)
{
#if !defined(PATH_MAX)
    us_char_a_t     stack[4096];
#else
    us_char_a_t     stack[PATH_MAX];
#endif
    us_char_a_t*    path = &stack[0];
    us_char_a_t*    heap = NULL;
    us_size_t       cap = STLSOFT_NUM_ELEMENTS(stack);
    us_size_t       len = 0;
    us_size_t       result;

    UNIXSTL_ASSERT(0 == cch || NULL != buff);

#if 0
#elif defined(_WIN32)

    /* NOTE: this only for UNIXem-ulation, so we don't care about its
     * performance
     */

    /* Windows / UNIXem: GetModuleFileNameA */
    for (;;)
    {
        DWORD const n = WINSTL_API_EXTERNAL_DynamicLinkLibrary_GetModuleFileNameA(NULL, path, STLSOFT_STATIC_CAST(DWORD, cap));

        if (0 == n)
        {
            if (NULL != heap)
            {
                STLSOFT_NS_GLOBAL(free)(heap);
            }

            return 0;
        }

        if (n < cap)
        {
            len = STLSOFT_STATIC_CAST(us_size_t, n);
            break;
        }

        {
            us_size_t const     newCap = cap * 2;
            us_char_a_t* const  newHeap = STLSOFT_STATIC_CAST(us_char_a_t*, STLSOFT_NS_GLOBAL(realloc)(heap, newCap * sizeof(us_char_a_t)));

            if (NULL == newHeap)
            {
                if (NULL != heap)
                {
                    STLSOFT_NS_GLOBAL(free)(heap);
                }

                errno = ENOMEM;

                return 0;
            }

            heap = newHeap;
            path = heap;
            cap = newCap;
        }
    }
#elif defined(__APPLE__)

    /* macOS: prefer proc_pidpath; fallback to _NSGetExecutablePath (+ realpath). */
    {
        int const ret = STLSOFT_NS_GLOBAL(proc_pidpath)(STLSOFT_NS_GLOBAL(getpid)(), path, STLSOFT_STATIC_CAST(uint32_t, cap));

        if (ret <= 0)
        {
            uint32_t size = STLSOFT_STATIC_CAST(uint32_t, cap);

            if (0 != STLSOFT_NS_GLOBAL(_NSGetExecutablePath)(path, &size))
            {
                us_char_a_t* const newHeap = STLSOFT_STATIC_CAST(us_char_a_t*, STLSOFT_NS_GLOBAL(malloc)(size * sizeof(us_char_a_t)));

                if (NULL == newHeap)
                {
                    errno = ENOMEM;

                    return 0;
                }

                heap = newHeap;
                path = heap;
                cap = size;

                if (0 != STLSOFT_NS_GLOBAL(_NSGetExecutablePath)(path, &size))
                {
                    STLSOFT_NS_GLOBAL(free)(heap);

                    return 0;
                }
            }

            {
                char* const resolved = STLSOFT_NS_GLOBAL(realpath)(path, NULL);

                if (NULL != resolved)
                {
                    us_size_t const cchResolved = STLSOFT_NS_GLOBAL(strlen)(resolved);

                    if (cchResolved + 1 > cap)
                    {
                        us_char_a_t* const newHeap = STLSOFT_STATIC_CAST(us_char_a_t*, STLSOFT_NS_GLOBAL(realloc)(heap, (cchResolved + 1) * sizeof(us_char_a_t)));

                        if (NULL == newHeap)
                        {
                            STLSOFT_NS_GLOBAL(free)(resolved);
                            if (NULL != heap)
                            {
                                STLSOFT_NS_GLOBAL(free)(heap);
                            }

                            errno = ENOMEM;

                            return 0;
                        }

                        heap = newHeap;
                        path = heap;
                        cap = cchResolved + 1;
                    }

                    STLSOFT_NS_GLOBAL(memcpy)(path, resolved, cchResolved + 1);
                    STLSOFT_NS_GLOBAL(free)(resolved);
                }
            }
        }

        len = STLSOFT_NS_GLOBAL(strlen)(path);
    }
#elif defined(__linux__)

    /* Linux: readlink("/proc/self/exe") */
    for (;;)
    {
        ssize_t const n = STLSOFT_NS_GLOBAL(readlink)("/proc/self/exe", path, cap);

        if (n < 0)
        {
            if (NULL != heap)
            {
                STLSOFT_NS_GLOBAL(free)(heap);
            }

            return 0;
        }

        if (STLSOFT_STATIC_CAST(us_size_t, n) < cap)
        {
            path[n] = '\0';
            len = STLSOFT_STATIC_CAST(us_size_t, n);
            break;
        }

        {
            us_size_t const     newCap = cap * 2;
            us_char_a_t* const  newHeap = STLSOFT_STATIC_CAST(us_char_a_t*, STLSOFT_NS_GLOBAL(realloc)(heap, newCap * sizeof(us_char_a_t)));

            if (NULL == newHeap)
            {
                if (NULL != heap)
                {
                    STLSOFT_NS_GLOBAL(free)(heap);
                }

                errno = ENOMEM;

                return 0;
            }

            heap = newHeap;
            path = heap;
            cap = newCap;
        }
    }
#elif 0 ||\
      defined(__FreeBSD__) ||\
      defined(__NetBSD__) ||\
      defined(__OpenBSD__) ||\
      0

    /* BSD: sysctl(KERN_PROC_PATHNAME) */
    {
        int     mib[4];
        size_t  cb = cap;

        mib[0] = CTL_KERN;
        mib[1] = KERN_PROC;
        mib[2] = KERN_PROC_PATHNAME;
        mib[3] = -1;

        if (0 != STLSOFT_NS_GLOBAL(sysctl)(mib, 4, path, &cb, NULL, 0))
        {
            if (ENOMEM == errno)
            {
                us_char_a_t* const newHeap = STLSOFT_STATIC_CAST(us_char_a_t*, STLSOFT_NS_GLOBAL(malloc)(cb));

                if (NULL == newHeap)
                {
                    errno = ENOMEM;

                    return 0;
                }

                heap = newHeap;
                path = heap;
                cap = cb;

                if (0 != STLSOFT_NS_GLOBAL(sysctl)(mib, 4, path, &cb, NULL, 0))
                {
                    STLSOFT_NS_GLOBAL(free)(heap);

                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }

        len = STLSOFT_NS_GLOBAL(strlen)(path);
    }
#elif defined(__sun)

    /* Solaris: getexecname() + realpath() */
    {
        char const* const exe = STLSOFT_NS_GLOBAL(getexecname)();

        if (NULL == exe)
        {
            return 0;
        }

        if (NULL == STLSOFT_NS_GLOBAL(realpath)(exe, path))
        {
            return 0;
        }

        len = STLSOFT_NS_GLOBAL(strlen)(path);
    }
#else

    STLSOFT_SUPPRESS_UNUSED(path);
    STLSOFT_SUPPRESS_UNUSED(cap);
    errno = ENOSYS;

    return 0;
#endif

    if (0 == cch)
    {
        result = len + 1;
    }
    else if (cch <= len)
    {
        us_size_t const nCopy = cch - 1;

        if (0 != nCopy)
        {
            STLSOFT_NS_GLOBAL(memcpy)(buff, path, nCopy * sizeof(us_char_a_t));
        }

        buff[nCopy] = '\0';
        result = len + 1;
    }
    else
    {
        if (0 != len)
        {
            STLSOFT_NS_GLOBAL(memcpy)(buff, path, len * sizeof(us_char_a_t));
        }

        buff[len] = '\0';
        result = len;
    }

    if (NULL != heap)
    {
        STLSOFT_NS_GLOBAL(free)(heap);
    }

    return result;
}


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

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !UNIXSTL_INCL_UNIXSTL_PROCESS_H_FUNCTIONS */

/* ///////////////////////////// end of file //////////////////////////// */

