/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/windows_clipboard/clipboard_scope/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Windows Clipboard
 *          library.
 *
 * Created: 6th June 2006
 * Updated: 29th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* WinSTL header files */
#include <winstl/clipboard/clipboard_scope.hpp>

/* Standard C++ header files */
#include <iostream>


int main()
{
    try
    {
        // 1. Set the data on the clipboard
        {
            winstl::clipboard_scope scope;

            scope.set_data("The data");
        }

        // 2. Get the data from the clipboard
        {
            winstl::clipboard_scope scope;
            char const*             str;

            scope.get_data(str);

            std::cout << "Clipboard data: " << str << std::endl;

            scope.get_allocator().deallocate(str);
        }
    }
    catch (winstl::clipboard_scope_exception& x)
    {
        std::cerr << "Exception: " << x.what() << std::endl;
    }
    catch (std::exception& x)
    {
        std::cerr << "Exception: " << x.what() << std::endl;
    }

    return 0;
}


/* ///////////////////////////// end of file //////////////////////////// */

