/* /////////////////////////////////////////////////////////////////////////
 * File:    unixstl/dl/module.hpp (originally MXModule.h, ::SynesisUnix)
 *
 * Purpose: Contains the module class.
 *
 * Created: 30th October 1997
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 1997-2019, Matthew Wilson and Synesis Software
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


/** \file unixstl/dl/module.hpp
 *
 * \brief [C++] Definition of the unixstl::dl_module class
 *   (\ref group__library__DL "DL" Library).
 */

#ifndef UNIXSTL_INCL_UNIXSTL_DL_HPP_MODULE
#define UNIXSTL_INCL_UNIXSTL_DL_HPP_MODULE

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define UNIXSTL_VER_UNIXSTL_DL_HPP_MODULE_MAJOR    7
# define UNIXSTL_VER_UNIXSTL_DL_HPP_MODULE_MINOR    0
# define UNIXSTL_VER_UNIXSTL_DL_HPP_MODULE_REVISION 2
# define UNIXSTL_VER_UNIXSTL_DL_HPP_MODULE_EDIT     245
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

# ifndef UNIXSTL_INCL_UNIXSTL_HPP_EXCEPTION_UNIXSTL_EXCEPTION
#  include <unixstl/exception/unixstl_exception.hpp>
# endif /* !UNIXSTL_INCL_UNIXSTL_HPP_EXCEPTION_UNIXSTL_EXCEPTION */
#ifndef STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_HPP_STRING
# include <stlsoft/shims/access/string.hpp>
#endif /* !STLSOFT_INCL_STLSOFT_SHIMS_ACCESS_HPP_STRING */
#ifndef UNIXSTL_INCL_UNIXSTL_SHIMS_ACCESS_HPP_STRING
# include <unixstl/shims/access/string.hpp>
#endif /* !UNIXSTL_INCL_UNIXSTL_SHIMS_ACCESS_HPP_STRING */

#ifndef STLSOFT_INCL_H_DLFCN
# define STLSOFT_INCL_H_DLFCN
# include <dlfcn.h>
#endif /* !STLSOFT_INCL_H_DLFCN */
#if 0
#elif defined(UNIXSTL_OS_IS_MACOSX)
# ifndef STLSOFT_INCL_H_ERRNO
#  define STLSOFT_INCL_H_ERRNO
#  include <errno.h>
# endif /* !STLSOFT_INCL_H_ERRNO */
#endif


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef UNIXSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
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
 * classes
 */

/** Class for manipulating dynamically loaded libraries
 *
 * \ingroup group__library__DL
 */
class dl_module
{
public:
    /// The handle type
    typedef void*                                           module_handle_type;
    /// The handle type
    ///
    /// \note This member type is required to make it compatible with
    ///  the STLSoft get_module_handle access shim
    typedef void*                                           handle_type;
    /// The class type
    typedef dl_module                                       class_type;
    /// The entry point type
    typedef void*                                           proc_pointer_type;
    /// The resource type
    typedef handle_type                                     resource_type;

/// \name Construction
/// @{
public:
    /// Constructs by loading the named module
    ///
    /// \param moduleName The file name of the executable module to be loaded.
    /// \param mode The loading mode (as used by ::<code>dlopen()</code>).
    ///
    /// \note If exception-handling is being used, then this throws a
    ///  \link unixstl::unixstl_exception unixstl_exception\endlink
    ///  if the module cannot be loaded
    ss_explicit_k
    dl_module(
        us_char_a_t const*  moduleName
    ,   int                 mode = RTLD_NOW
    );
    /// Constructs by loading the named module
    ///
    /// \param moduleName The file name of the executable module to be loaded.
    /// \param mode The loading mode (as used by ::<code>dlopen()</code>).
    ///
    /// \note If exception-handling is being used, then this throws a
    ///  \link unixstl::unixstl_exception unixstl_exception\endlink
    ///  if the module cannot be loaded
    ss_explicit_k
    dl_module(
        us_char_w_t const*  moduleName
    ,   int                 mode = RTLD_NOW
    );
#if defined(STLSOFT_CF_MEMBER_TEMPLATE_CTOR_SUPPORT)

    /// Constructs by loading the named module
    ///
    /// \param moduleName The file name of the executable module to be
    ///   loaded. The argument may be of any type for which the
    ///   \ref group__concept__Shim__string_access "string access shim"
    ///   stlsoft::c_str_ptr is defined.
    /// \param mode The loading mode (as used by ::<code>dlopen()</code>).
    ///
    /// \note If exception-handling is being used, then this throws a
    ///  \link unixstl::unixstl_exception unixstl_exception\endlink
    ///  if the module cannot be loaded
    template <ss_typename_param_k S>
    ss_explicit_k
    dl_module(
        S const&    moduleName
    ,   int         mode = RTLD_NOW
    )
        : m_hmodule(load(moduleName, mode))
    {
        check_loaded_handle_(m_hmodule);
    }
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_CTOR_SUPPORT */
    /// Constructs by taking ownership of the given handle
    ///
    /// \note If exception-handling is being used, then this throws a
    ///  \link unixstl::unixstl_exception unixstl_exception\endlink
    ///  if the handle is \c nullptr.
    ss_explicit_k
    dl_module(module_handle_type hmodule);
#ifdef STLSOFT_CF_RVALUE_REFERENCES_SUPPORT

    /// Constructs a module instance by taking over the state of the
    /// instance \c rhs
    ///
    /// \param rhs The instance whose state will be taken over. Upon return
    ///   \c rhs <code>get_module_handle()()</code> will obtain \c nullptr
    dl_module(class_type&& rhs) STLSOFT_NOEXCEPT
        : m_hmodule(rhs.detach())
    {}
#endif /* STLSOFT_CF_RVALUE_REFERENCES_SUPPORT */
    /// Closes the module handle
    ~dl_module() STLSOFT_NOEXCEPT;

private:
    dl_module(class_type const&) STLSOFT_COPY_CONSTRUCTION_PROSCRIBED;
    void operator =(class_type const&) STLSOFT_COPY_ASSIGNMENT_PROSCRIBED;
/// @}

/// \name Static operations
/// @{
public:
    /// Loads the named module, returning its handle, which the
    ///   caller must close with unload().
    ///
    /// \param moduleName The file name of the executable module to be loaded.
    /// \param mode The loading mode (as used by ::<code>dlopen()</code>).
    ///
    /// \return The module handle, or \c nullptr if no matching module found.
    static module_handle_type   load(us_char_a_t const* moduleName, int mode = RTLD_NOW);
    /// Loads the named module, returning its handle, which the
    ///   caller must close with unload().
    ///
    /// \param moduleName The file name of the executable module to be loaded.
    /// \param mode The loading mode (as used by ::<code>dlopen()</code>).
    ///
    /// \return The module handle, or \c nullptr if no matching module found.
    static module_handle_type   load(us_char_w_t const* moduleName, int mode = RTLD_NOW);
#if defined(STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT)

    /// Loads the named module, returning its handle, which the
    ///   caller must close with unload().
    ///
    /// \param moduleName The file name of the executable module to be
    ///   loaded. The argument may be of any type for which the
    ///   \ref group__concept__Shim__string_access "string access shim"
    ///   stlsoft::c_str_ptr is defined.
    /// \param mode The loading mode (as used by ::<code>dlopen()</code>).
    ///
    /// \return The module handle, or \c nullptr if no matching module found.
    template <ss_typename_param_k S>
    static module_handle_type   load(S const& moduleName, int mode = RTLD_NOW)
    {
        return class_type::load(STLSOFT_NS_QUAL(c_str_ptr)(moduleName), mode);
    }
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT */
    /// Closes the given module handle
    static void                 unload(module_handle_type hmodule) STLSOFT_NOEXCEPT;
    /// Looks up the named symbol from the given module
    ///
    /// \return A pointer to the named symbol, or \c nullptr if not found
    static proc_pointer_type    get_symbol(module_handle_type hmodule, us_char_a_t const* symbolName);
#if defined(STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT)

    /// Looks up a named symbol from the given module into a typed function pointer variable.
    ///
    /// \return A pointer to the named symbol, or \c nullptr if not found.
    template <ss_typename_param_k F>
    static proc_pointer_type    get_symbol(module_handle_type hmodule, us_char_a_t const* symbolName, F& f)
    {
        proc_pointer_type proc = class_type::get_symbol(hmodule, symbolName);

        f = reinterpret_cast<F>(proc);

        return proc;
    }
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT */
/// @}

/// \name Operations
/// @{
public:
    /// Closes the module handle
    void unload() STLSOFT_NOEXCEPT;

    /// Yields the module handle to the caller
    module_handle_type detach();
/// @}

/// \name Lookup Operations
/// @{
public:
    /// Looks up the named symbol.
    ///
    /// \return A pointer to the named symbol, or \c nullptr if not found
    proc_pointer_type   get_symbol(us_char_a_t const* symbolName);
#if defined(STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT)

    /// Looks up a named symbol into a typed function pointer variable.
    ///
    /// \return A pointer to the named symbol, or \c nullptr if not found.
    template <ss_typename_param_k F>
    proc_pointer_type   get_symbol(us_char_a_t const* symbolName, F& f)
    {
        return class_type::get_symbol(m_hmodule, symbolName, f);
    }
#endif /* STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT */
/// @}

/// \name Accessors
/// @{
public:
    /// Provides access to the underlying module handle
    module_handle_type  get_module_handle() const;

    /// Provides access to the underlying module handle
    module_handle_type  get() const;
/// @}

/// \name Implementation
/// @{
private:
    static
    void
    check_loaded_handle_(
        module_handle_type hmodule
    )
    {
        if (NULL == hmodule)
        {
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
# if 0
# elif defined(UNIXSTL_OS_IS_MACOSX)

            STLSOFT_THROW_X(unixstl_exception("Cannot load module", errno));
# else

            STLSOFT_THROW_X(unixstl_exception("Cannot load module", ::dlerror()));
# endif
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
        }
    }
/// @}

/// \name Member Variables
/// @{
private:
    module_handle_type  m_hmodule;
/// @}
};


/* /////////////////////////////////////////////////////////////////////////
 * backwards compatibility
 */

#if __cplusplus < 202002L

typedef dl_module                                           module;
#endif /* C++ version */


/* /////////////////////////////////////////////////////////////////////////
 * access shims
 */

/** Returns the module handle for the given module
 *
 * \ingroup group__concept__Shim__module_attribute
 */
inline
dl_module::module_handle_type
get_module_handle(UNIXSTL_NS_QUAL(dl_module) const& m)
{
    return m.get_module_handle();
}


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION

inline
dl_module::dl_module(
    us_char_a_t const*  moduleName
,   int                 mode
)
    : m_hmodule(load(moduleName, mode))
{
    check_loaded_handle_(m_hmodule);
}

inline
dl_module::dl_module(
    us_char_w_t const*  moduleName
,   int                 mode
)
    : m_hmodule(load(moduleName, mode))
{
    check_loaded_handle_(m_hmodule);
}

inline
dl_module::dl_module(dl_module::module_handle_type hmodule)
    : m_hmodule(hmodule)
{
    check_loaded_handle_(m_hmodule);
}

inline
dl_module::~dl_module() STLSOFT_NOEXCEPT
{
    unload(m_hmodule);
}

inline
void
dl_module::unload() STLSOFT_NOEXCEPT
{
    if (NULL != m_hmodule)
    {
        unload(m_hmodule);
        m_hmodule = NULL;
    }
}

inline
dl_module::module_handle_type
dl_module::detach()
{
    module_handle_type  h;

    h = m_hmodule;
    m_hmodule = NULL;

    return h;
}

inline
/* static */
dl_module::module_handle_type
dl_module::load(
    us_char_a_t const*  moduleName
,   int                 mode
)
{
    return ::dlopen(moduleName, mode);
}

inline
/* static */
void
dl_module::unload(dl_module::module_handle_type hmodule) STLSOFT_NOEXCEPT
{
    if (NULL != hmodule)
    {
        ::dlclose(hmodule);
    }
}

inline
/* static */
dl_module::proc_pointer_type
dl_module::get_symbol(
    dl_module::module_handle_type   hmodule
,   us_char_a_t const*              symbolName
)
{
    return ::dlsym(hmodule, symbolName);
}

inline
dl_module::proc_pointer_type
dl_module::get_symbol(us_char_a_t const* symbolName)
{
    return get_symbol(m_hmodule, symbolName);
}

inline
dl_module::module_handle_type
dl_module::get_module_handle() const
{
    return m_hmodule;
}

inline
dl_module::module_handle_type
dl_module::get() const
{
    return m_hmodule;
}
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

#ifndef UNIXSTL_NO_NAMESPACE
# if defined(STLSOFT_NO_NAMESPACE) || \
     defined(STLSOFT_DOCUMENTATION_SKIP_SECTION)
} // namespace unixstl
# else
} // namespace unixstl_project
} // namespace stlsoft
# endif /* STLSOFT_NO_NAMESPACE */
#endif /* !UNIXSTL_NO_NAMESPACE */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !UNIXSTL_INCL_UNIXSTL_DL_HPP_MODULE */

/* ///////////////////////////// end of file //////////////////////////// */

