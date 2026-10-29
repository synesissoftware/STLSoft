/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/memory/auto_buffer/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Memory library
 *          component auto_buffer.
 *
 * Created: 15th September 2006
 * Updated: 30th May 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* STLSoft header files */
#include <stlsoft/memory/auto_buffer.hpp>


/* Standard C++ header files */
#include <exception>
#include <iostream>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/* Standard C header files */
#include <stdlib.h> // for EXIT_FAILURE, EXIT_SUCCESS


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

typedef stlsoft::auto_buffer<char, 128>                     buffer_t;
// typedef std::vector<char>                                   buffer_t;


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

void
do_a_gazillion_allocations()
{
    for (size_t i = 0; i != 100; ++i)
    {
        for (size_t j = 0; j != 1000; ++j)
        {
            buffer_t buffer(1 + i * 10 + j * 1000);
        }
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main()
{
    try
    {
        buffer_t buff(0);


        // Resize within the bounds of the internal buffer
        buff.resize(10, 'a');

        char* const p0 = buff.data();

        ::memset(&buff[0], '1', buff.size());


        // Resize outside the bounds of the internal buffer, and go to the heap
        buff.resize(100, 'b');

        char* const p1 = buff.data();

        ::memset(&buff[0], '2', buff.size());


        do_a_gazillion_allocations();


        // Resize again outside the bounds of the internal buffer, and go to the heap
        buff.resize(10000, 'c');

        char* const p2 = buff.data();

        ::memset(&buff[0], '3', buff.size());


        do_a_gazillion_allocations();


        // Resize outside the bounds of the internal buffer, and go to the heap
        buff.resize(100, 'd');

        char* const p3 = buff.data();

        ::memset(&buff[0], '4', buff.size());


        do_a_gazillion_allocations();


        // Resize again outside the bounds of the internal buffer but within the previous external allocation, which will not require another trip to the heap
        buff.resize(10000, 'e');

        char* const p4 = buff.data();

        ::memset(&buff[0], '5', buff.size());


        do_a_gazillion_allocations();


        // Resize again outside the bounds of the internal buffer, and go to the heap
        buff.resize(10001, 'f');

        char* const p5 = buff.data();

        ::memset(&buff[0], '6', buff.size());


        do_a_gazillion_allocations();


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

