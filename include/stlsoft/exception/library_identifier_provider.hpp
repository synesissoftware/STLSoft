/* /////////////////////////////////////////////////////////////////////////
 * File:    stlsoft/exception/library_identifier_provider.hpp
 *
 * Purpose: Define the library_identifier_provider inteface.
 *
 * Created: 29th December 2016
 * Updated: 9th November 2026
 *
 * Home:    http://stlsoft.org/
 *
 * Copyright (c) 2019-2026, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2016-2019, Matthew Wilson and Synesis Software
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



#ifndef STLSOFT_INCL_STLSOFT_EXCEPTION_HPP_LIBRARY_IDENTIFIER_PROVIDER
#define STLSOFT_INCL_STLSOFT_EXCEPTION_HPP_LIBRARY_IDENTIFIER_PROVIDER

#ifndef STLSOFT_DOCUMENTATION_SKIP_SECTION
# define STLSOFT_VER_STLSOFT_EXCEPTION_HPP_LIBRARY_IDENTIFIER_PROVIDER_MAJOR    1
# define STLSOFT_VER_STLSOFT_EXCEPTION_HPP_LIBRARY_IDENTIFIER_PROVIDER_MINOR    1
# define STLSOFT_VER_STLSOFT_EXCEPTION_HPP_LIBRARY_IDENTIFIER_PROVIDER_REVISION 4
# define STLSOFT_VER_STLSOFT_EXCEPTION_HPP_LIBRARY_IDENTIFIER_PROVIDER_EDIT     10
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

#ifndef WINSTL_INCL_WINSTL_DIAGNOSTICS_H_LIBRARYIDENTIFIER
# include <stlsoft/diagnostics/LibraryIdentifier.h>
#endif /* !WINSTL_INCL_WINSTL_DIAGNOSTICS_H_LIBRARYIDENTIFIER */

#ifndef STLSOFT_INCL_STLSOFT_QUALITY_H_CONTRACT
# include <stlsoft/quality/contract.h>
#endif /* !STLSOFT_INCL_STLSOFT_QUALITY_H_CONTRACT */
#ifndef STLSOFT_INCL_STLSOFT_QUALITY_H_COVER
# include <stlsoft/quality/cover.h>
#endif /* !STLSOFT_INCL_STLSOFT_QUALITY_H_COVER */


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


class library_identifier_provider
{
public: // types
    typedef library_identifier_provider                     class_type;
    /// The library identifier type
    typedef STLSoftLibraryIdentifier_t                      library_identifier_type;
private:

protected: // construction
    library_identifier_provider()
    {}
    ~library_identifier_provider() STLSOFT_NOEXCEPT
    {}
    library_identifier_provider(class_type const& /* rhs */)
    {}
private:
    void operator =(class_type const&) STLSOFT_COPY_ASSIGNMENT_PROSCRIBED;

public: // modifiers
    void swap(class_type& /* rhs */) STLSOFT_NOEXCEPT
    {}

public: // overrides
    virtual library_identifier_type
    library_identifier() const = 0;

private:
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

/* ////////////////////////////////////////////////////////////////////// */

#endif /* !STLSOFT_INCL_STLSOFT_EXCEPTION_HPP_LIBRARY_IDENTIFIER_PROVIDER */

/* ///////////////////////////// end of file //////////////////////////// */

