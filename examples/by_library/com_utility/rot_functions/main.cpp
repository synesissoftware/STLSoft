/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/com_utility/rot_functions/main.cpp
 *
 * Purpose: C++ example program demonstrating use of various COMSTL
 *          components to manipulate the COM Running Object Table.
 *
 * Created: 13th December 2006
 * Updated: 9th October 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* COMSTL header files */
#include <comstl/collections/enumerator_sequence.hpp>
#include <comstl/error/errorinfo_desc.hpp>
#include <comstl/util/creation_functions.hpp>
#include <comstl/util/initialisers.hpp>
#include <comstl/util/rot_functions.h>
#include <comstl/util/value_policies.hpp>

/* STLSoft header files */
#include <stlsoft/smartptr/ref_ptr.hpp>
#include <stlsoft/smartptr/scoped_handle.hpp>

/* PlatformSTL header files */
#include <platformstl/error/error_desc.hpp>


/* Standard C++ header files */
#include <exception>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::wcout;

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

static int main_()
{
    // Create a bind context for retrieving information from the monikers
    IBindCtx    *pbc;
    HRESULT     hr  =   ::CreateBindCtx(0, &pbc);

    if (FAILED(hr))
    {
        cerr << "Failed to create bind context: " << platformstl::error_desc(hr) << endl;
    }
    else
    {
        stlsoft::ref_ptr<IBindCtx>  bindctx(pbc, false); // Consume the reference
        IEnumMoniker                *pen;

        // Get an enumerator to all objects currently in the ROT
        hr = comstl::Rot_EnumRunning(&pen);

        if (FAILED(hr))
        {
            cerr << "Failed to enumerate running objects: " << platformstl::error_desc(hr) << endl;
        }
        else
        {
            // Define a specialisation of comstl::enumerator_sequence for
            // wrapping the enumerator instance
            typedef comstl::enumerator_sequence<IEnumMoniker
                                            ,   IMoniker*
                                            ,   comstl::interface_policy<IMoniker>
                                            >       enum_t;

            enum_t      en(pen, false); // Consume the reference

            { for (enum_t::iterator b = en.begin(); b != en.end(); ++b)
            {
                LPOLESTR    displayName;

                hr = (*b)->GetDisplayName(bindctx.get(), NULL, &displayName);

                if (FAILED(hr))
                {
                    cerr << "Failed to get display name: " << platformstl::error_desc(hr) << endl;
                }
                else
                {
                    // Set the displayName to be released when it's finished with.
                    stlsoft::scoped_handle<void*>   _(displayName, ::CoTaskMemFree);

                    wcout << L"Display name: " << displayName << endl;
                }
            }}
        }
    }

    return EXIT_SUCCESS;
}

int main()
{
    try
    {
        // Initialise the COM libraries
        comstl::com_initialiser coinit;

        return main_();
    }
    catch (std::exception& x)
    {
        cerr << "Unhandled error: " << x.what() << endl;

        return EXIT_FAILURE;
    }
    catch (...)
    {
        cerr << "Unhandled unknown error" << endl;

        return EXIT_FAILURE;
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

