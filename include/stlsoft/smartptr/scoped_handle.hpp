/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/smartptr/scoped_handle.hpp (evolved from MLResPtr.h, ::SynesisStd)
 *
 * Purpose: scoped_handle - specialisable RAII class for arbitrary resource
 *          types.
 *
 * Created: 1st November 1994
 * Updated: 11th November 2026
 *
 * Thanks:  Adi Shavit, for requesting the indirect functionality
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 1994-2019, Matthew Wilson and Synesis Software
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


/** \file stlsoft/smartptr/scoped_handle.hpp
 *
 * \brief [C++] Definition of the stlsoft::scoped_handle smart
 *   pointer class template
 *   (\ref group__library__SmartPointer "Smart Pointer" Library).
 */

#ifndef STLSOFT_INCL_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE
#define STLSOFT_INCL_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE_MAJOR       5
# define STLSOFT_VER_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE_MINOR       7
# define STLSOFT_VER_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE_REVISION    2
# define STLSOFT_VER_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE_EDIT        692
#endif /* !STLSOFT_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/stlsoft.h>

#if defined(STLSOFT_COMPILER_IS_BORLAND)

# include <stlsoft/smartptr/scoped_handle_borland.hpp>
#else /* ? compiler */

# include "./scoped_handle/scoped_handle_cc.hpp"
#endif


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_message_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_message_SUPPORT */

#endif /* !STLSOFT_INCL_STLSOFT_SMARTPTR_HPP_SCOPED_HANDLE */

/* ///////////////////////////// end of file //////////////////////////// */

