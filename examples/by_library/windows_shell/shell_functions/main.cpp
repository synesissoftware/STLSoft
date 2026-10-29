/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/windows_shell/shell_functions/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Windows Shell
 *          library filesystem functions.
 *
 * Created: 9th December 2006
 * Updated: 9th October 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* WinSTL header files */
#include <winstl/error/error_desc.hpp>
#include <winstl/filesystem/current_directory.hpp>
#include <winstl/shell/browse_for_folder.hpp>
#include <winstl/shell/file_operations.hpp>
#include <winstl/shell/memory/functions.h>

/* STLSoft header files */
#include <stlsoft/smartptr/scoped_handle.hpp>

/* Standard C++ header files */
#include <exception>
#include <iostream>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/* Standard C header files */
#include <stdlib.h> // for EXIT_FAILURE, EXIT_SUCCESS


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main()
{
    try
    {
        CHAR            displayName[_MAX_PATH + 1];
        LPITEMIDLIST    iil;
        HRESULT         hr  =   ::SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &iil);

        if (FAILED(hr))
        {
            cerr << "Could not get the My Computer special folder location: " << winstl::error_desc(hr) << endl;
        }
        else
        {
            stlsoft::scoped_handle<void*>   iil_(iil, winstl::SHMemFree);

            if (winstl::browse_for_folder("Select a file to send to the recycle bin", displayName, BIF_BROWSEINCLUDEFILES, iil))
            {
                winstl::shell_delete(displayName, FOF_ALLOWUNDO);
            }
        }

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

