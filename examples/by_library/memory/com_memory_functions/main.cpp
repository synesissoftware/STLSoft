/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/memory/com_memory_functions/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the COMSTL memory
 *          functions.
 *
 * Created: 9th December 2006
 * Updated: 9th October 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* COMSTL header files */
#include <comstl/memory/functions.h>
#include <comstl/util/initialisers.hpp>

/* WinSTL header files */
#include <winstl/error/error_desc.hpp>

/* Standard C++ header files */
#include <exception>
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main()
{
    try
    {
        /* Initialise the COM libraries with the com_init scoping class */
        comstl::com_init init;

        void*   p1  =   ::CoTaskMemAlloc(10);
        void*   p2  =   ::CoTaskMemAlloc(10000);
        void*   p3  =   ::CoTaskMemAlloc(0);
        void*   p4  =   ::CoTaskMemAlloc(2000000000);

        if (NULL == p1)
        {
            cerr << "Failed to allocate 10 bytes: " << winstl::error_desc_a() << endl;
        }
        else
        {
            WINSTL_ASSERT(comstl::CoTaskMemDidAlloc(p1));
        }

        if (NULL == p2)
        {
            cerr << "Failed to allocate 10000 bytes: " << winstl::error_desc_a() << endl;
        }
        else
        {
            WINSTL_ASSERT(comstl::CoTaskMemDidAlloc(p2));
        }

        if (NULL == p3)
        {
            cerr << "Failed to allocate 0 bytes: " << winstl::error_desc_a() << endl;
        }
        else
        {
            WINSTL_ASSERT(comstl::CoTaskMemDidAlloc(p3));
        }

        if (NULL == p4)
        {
            cerr << "Failed to allocate 2000000000 bytes: " << winstl::error_desc_a() << endl;
        }
        else
        {
            WINSTL_ASSERT(comstl::CoTaskMemDidAlloc(p4));
        }

        size_t  cb1 =   comstl::CoTaskMemGetSize(p1);
        size_t  cb2 =   comstl::CoTaskMemGetSize(p2);
        size_t  cb3 =   comstl::CoTaskMemGetSize(p3);
        size_t  cb4 =   comstl::CoTaskMemGetSize(p4);

        STLSOFT_SUPPRESS_UNUSED(cb1);
        STLSOFT_SUPPRESS_UNUSED(cb2);
        STLSOFT_SUPPRESS_UNUSED(cb3);
        STLSOFT_SUPPRESS_UNUSED(cb4);

        p1  =   CoTaskMemRealloc(p1, 0);
        p2  =   CoTaskMemRealloc(p2, 1);
        p3  =   CoTaskMemRealloc(p3, 100);
        p4  =   CoTaskMemRealloc(p4, 10000);

        cb1 =   comstl::CoTaskMemGetSize(p1);
        cb2 =   comstl::CoTaskMemGetSize(p2);
        cb3 =   comstl::CoTaskMemGetSize(p3);
        cb4 =   comstl::CoTaskMemGetSize(p4);

        CoTaskMemFree(p1);
        CoTaskMemFree(p2);
        CoTaskMemFree(p3);
        CoTaskMemFree(p4);

        return EXIT_SUCCESS;
    }
    catch (std::exception& x)
    {
        cerr << "Error: " << x.what() << endl;

        return EXIT_FAILURE;
    }
    catch (...)
    {
        cerr << "Unknown error" << endl;

        return EXIT_FAILURE;
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

