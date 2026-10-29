/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/windows_toolhelp/module_sequence/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the ToolHelp library.
 *
 * Created: 22nd May 2006
 * Updated: 29th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* WinSTL header files */
#include <winstl/toolhelp/module_sequence.hpp>

/* Standard C++ header files */
#include <exception>
#include <iostream>

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
        // 1. Construct an instance of module_sequence. There is no parameter
        // required for module_sequence.
        winstl::module_sequence    modules;

        // 2. Declare iterator instances (since we're using a manual loop,
        // rather than an algorithm).
        winstl::module_sequence::const_iterator    b   =   modules.begin();
        winstl::module_sequence::const_iterator    e   =   modules.end();

        // 3. Loop through the range.
        for (; b != e; ++b)
        {
            // 3.1. Print out the module handle and the file name.
            cout << (*b).hModule << ": " << (*b).szExePath << endl;
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

