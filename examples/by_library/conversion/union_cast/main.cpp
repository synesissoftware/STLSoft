/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/conversion/union_cast/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Conversion
 *          library's union_cast component.
 *
 * Created: 10th June 2006
 * Updated: 29th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* STLSoft header files */
#include <stlsoft/conversion/union_cast.hpp>

/* Standard C++ header files */
#include <exception>
#include <iostream>

/* Standard C header files */
#include <stdint.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main()
{

    short*      ps  =   NULL;
    intptr_t    i   =   stlsoft::union_cast<intptr_t>(ps);  // Ok: both same size
#ifdef DEMONSTRATE_ERRORS

    char        c   =   stlsoft::union_cast<char>(ps);      // Compile error: different size
#endif

    STLSOFT_SUPPRESS_UNUSED(i);


    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

