/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/windows_shell/memory_functions/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Windows Shell
 *          library memory functions.
 *
 * Created: 9th December 2006
 * Updated: 29th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* WinSTL header files */
#include <winstl/error/error_desc.hpp>
#include <winstl/shell/memory/functions.h>

/* STLSoft header files */
#include <stlsoft/smartptr/scoped_handle.hpp>

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
        void    *p1 =   winstl::SHMemAlloc(10);
        void    *p2 =   winstl::SHMemAlloc(10000);
        void    *p3 =   winstl::SHMemAlloc(0);
        void    *p4 =   winstl::SHMemAlloc(2000000000);

        if (NULL == p1)
        {
            cerr << "Failed to allocate 10 bytes: " << winstl::error_desc_a() << endl;
        }
        else
        {
            WINSTL_ASSERT(winstl::SHMemDidAlloc(p1));
        }

        if (NULL == p2)
        {
            cerr << "Failed to allocate 10000 bytes: " << winstl::error_desc_a() << endl;
        }
        else
        {
            WINSTL_ASSERT(winstl::SHMemDidAlloc(p2));
        }

        if (NULL == p3)
        {
            cerr << "Failed to allocate 0 bytes: " << winstl::error_desc_a() << endl;
        }
        else
        {
            WINSTL_ASSERT(winstl::SHMemDidAlloc(p3));
        }

        if (NULL == p4)
        {
            cerr << "Failed to allocate 2000000000 bytes: " << winstl::error_desc_a() << endl;
        }
        else
        {
            WINSTL_ASSERT(winstl::SHMemDidAlloc(p4));
        }

        size_t  cb1 =   winstl::SHMemGetSize(p1);
        size_t  cb2 =   winstl::SHMemGetSize(p2);
        size_t  cb3 =   winstl::SHMemGetSize(p3);
        size_t  cb4 =   winstl::SHMemGetSize(p4);

        STLSOFT_SUPPRESS_UNUSED(cb1);
        STLSOFT_SUPPRESS_UNUSED(cb2);
        STLSOFT_SUPPRESS_UNUSED(cb3);
        STLSOFT_SUPPRESS_UNUSED(cb4);

        p1  =   winstl::SHMemRealloc(p1, 0);
        p2  =   winstl::SHMemRealloc(p2, 1);
        p3  =   winstl::SHMemRealloc(p3, 100);
        p4  =   winstl::SHMemRealloc(p4, 10000);

        cb1 =   winstl::SHMemGetSize(p1);
        cb2 =   winstl::SHMemGetSize(p2);
        cb3 =   winstl::SHMemGetSize(p3);
        cb4 =   winstl::SHMemGetSize(p4);

        winstl::SHMemFree(p1);
        winstl::SHMemFree(p2);
        winstl::SHMemFree(p3);
        winstl::SHMemFree(p4);

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

