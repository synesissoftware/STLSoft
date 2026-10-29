/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/memory/heapwalk_sequence/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Memory library.
 *
 * Created: 15th September 2006
 * Updated: 9th October 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* WinSTL header files */
#include <winstl/memory/heapwalk_sequence.hpp>


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
        cout    << "This program demonstrates use of the heapwalk_sequence" << endl
                << " class by enumerating all the currently allocated blocks" << endl
                << " of the process heap." << endl;

        winstl::heapwalk_sequence   blocks;

        { for (winstl::heapwalk_sequence::const_iterator b = blocks.begin(); b != blocks.end(); ++b)
        {
            cout << "  Block of size " << (*b).cbData << " at " << (*b).lpData << endl;
        }}

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

