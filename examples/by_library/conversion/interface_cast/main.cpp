/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/conversion/interface_cast/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Conversion
 *          library's interface_cast component.
 *
 * Created: 9th December 2006
 * Updated: 5th September 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* COMSTL header files */
#include <comstl/conversion/interface_cast.hpp>

/* STLSoft header files */
#include <stlsoft/smartptr/ref_ptr.hpp>

/* Windows header files */
#include <ole2.h>

/* Standard C++ header files */
#include <exception>
#include <iostream>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main()
{
    try
    {
        /* Get a stream to play with ... */
        LPSTREAM    pstm;
        HRESULT     hr = ::CreateStreamOnHGlobal(NULL, true, &pstm);

        if (SUCCEEDED(hr))
        {
            stlsoft::ref_ptr<IStream>   stm(pstm, false);   /* Eat the reference */

            /* Can the pointer be cast to IStorage*? */
            if (comstl::interface_cast_test<IStorage*>(pstm))
            {
                comstl::interface_cast_noaddref<IStorage*>->SetClass(CLSID_NULL);

                comstl::interface_cast_noaddref<IStorage*>->SetClass(CLSID_NULL);
            }

            /* Can the wrapper be cast to IStorage*? */
            if (comstl::interface_cast_test<IStorage*>(stm))
            {
                // . . .
            }

        }
    }
    catch (std::exception& x)
    {
        std::cerr << "exception: " << x.what() << std::endl;
    }


    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

