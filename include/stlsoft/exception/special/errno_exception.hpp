/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/exception/special/errno_exception.hpp
 *
 * Purpose: Defines the errno_exception exception class.
 *
 * Created: 17th May 2014
 * Updated: 14th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2014-2019, Matthew Wilson and Synesis Software
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


/** \file stlsoft/exception/special/errno_exception.hpp
 *
 * \brief [C++] Defines the errno_exception exception class
 *   (\ref group__library__Exception "Exception" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_EXCEPTIONS_SPECIAL_HPP_ERRNO_EXCEPTION
#define STLSOFT_INCL_STLSOFT_EXCEPTIONS_SPECIAL_HPP_ERRNO_EXCEPTION

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_EXCEPTIONS_SPECIAL_HPP_ERRNO_EXCEPTION_MAJOR       1
# define STLSOFT_VER_STLSOFT_EXCEPTIONS_SPECIAL_HPP_ERRNO_EXCEPTION_MINOR       2
# define STLSOFT_VER_STLSOFT_EXCEPTIONS_SPECIAL_HPP_ERRNO_EXCEPTION_REVISION    4
# define STLSOFT_VER_STLSOFT_EXCEPTIONS_SPECIAL_HPP_ERRNO_EXCEPTION_EDIT        23
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

#ifndef STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_STRING_STD_H_C_STRING
# include <stlsoft/shims/access/string/std/c_string.h>
#endif /* !STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_STRING_STD_H_C_STRING */

#ifndef STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_STRDUP
# include <stlsoft/string/c_string/strdup.h>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_C_STRING_H_STRDUP*/
#ifndef STLSOFT_INCL_STLSOFT_STRING_ERROR_H_STRERROR
# include <stlsoft/string/error/strerror.h>
#endif /* !STLSOFT_INCL_STLSOFT_STRING_ERROR_H_STRERROR */

#ifndef STLSOFT_INCL_NEW
# define STLSOFT_INCL_NEW
# include <new>
#endif /* !STLSOFT_INCL_NEW */
#ifndef STLSOFT_INCL_STDEXCEPT
# define STLSOFT_INCL_STDEXCEPT
# include <stdexcept>
#endif /* !STLSOFT_INCL_STDEXCEPT */
#ifndef STLSOFT_INCL_H_ERRNO
# define STLSOFT_INCL_H_ERRNO
# include <errno.h>
#endif /* !STLSOFT_INCL_H_ERRNO */
#ifndef STLSOFT_INCL_H_STDLIB
# define STLSOFT_INCL_H_STDLIB
# include <stdlib.h>
#endif /* !STLSOFT_INCL_H_STDLIB */
#ifndef STLSOFT_INCL_H_STRING
# define STLSOFT_INCL_H_STRING
# include <string.h>
#endif /* !STLSOFT_INCL_H_STRING */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
namespace stlsoft
{
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * classes
 */

class errno_exception
    : public std::runtime_error
{
public: // types
    typedef std::runtime_error                              parent_class_type;
    typedef errno_exception                                 class_type;

public: // construction
    /// Constructs an instance from the given errno value
    ss_explicit_k
    errno_exception(int e)
        : parent_class_type(make_message_(e))
        , ErrnoValue(e)
    {
        free_context_(construction_context_);
    }
    /// Constructs an instance from the given errno value and message
    errno_exception(
        int         e
    ,   char const* message
    )
        : parent_class_type(message)
        , ErrnoValue(e)
    {}
    /// Constructs an instance from the given errno value and message
    template <ss_typename_param_k S>
    errno_exception(
        int         e
    ,   S const&    message
    )
        : parent_class_type(c_str_ptr_a(message))
        , ErrnoValue(e)
    {}
#if 0
#elif defined(__GNUC__)
    ~errno_exception() STLSOFT_NOEXCEPT_STDOVR
    {}
#endif

private:
    void operator =(class_type const&) STLSOFT_COPY_ASSIGNMENT_PROSCRIBED;

private: // implementation
    static
    char const*
    ENOMEM_stock_message_() STLSOFT_NOEXCEPT
    {
#if 0
#elif defined(_MSC_VER)

        return "Not enough memory";
#else

        return "Cannot allocate memory";
#endif
    }

    char const*
    strerror_message_(
        int e
    )
    {
        char                buff[241];
        char const* const   text = stlsoft_C_strerror(
            e
        ,   sizeof(buff)
        ,   buff
        ,   NULL
        );

        /* buff is returned only when the worker wrote that array. The
         * pointer dies with this frame, so the text is copied.
         * std::runtime_error copies after this function returns. Any other
         * result is a static string. An empty buffer stored no message.
         */
        if (text == buff)
        {
            char const* const   message =   ('\0' != text[0]) ? text : "unknown failure";
            char* const         r       =   stlsoft_C_strdup(message);

            if (NULL == r)
            {
                STLSOFT_THROW_X(std::bad_alloc());
            }

            construction_context_ = r;

            return r;
        }
        else
        {
            return text;
        }
    }

    char const*
    make_message_(
        int e
    )
    {
        construction_context_ = NULL;

        switch (e)
        {
        case ENOMEM:

            return ENOMEM_stock_message_();
        default:

            return strerror_message_(e);
        }
    }

    static
    void
    free_context_(
        void* pv
    )
    {
        if (NULL != pv)
        {
            STLSOFT_NS_GLOBAL(free)(pv);
        }
    }

public: // fields
    int const   ErrnoValue;
private:
    void*       construction_context_;
};


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef STLSOFT_NO_NAMESPACE
} // namespace stlsoft
#endif /* STLSOFT_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_EXCEPTIONS_SPECIAL_HPP_ERRNO_EXCEPTION */

/* ///////////////////////////// end of file //////////////////////////// */

