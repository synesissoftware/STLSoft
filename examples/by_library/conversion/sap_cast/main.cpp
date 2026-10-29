/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/by_library/conversion/sap_cast/main.cpp
 *
 * Purpose: C++ example program demonstrating use of the Conversion
 *          library's sap_cast cast operator.
 *
 * Created: 9th June 2006
 * Updated: 15th October 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* STLSoft header files */
#include <stlsoft/conversion/sap_cast.hpp>


/* ////////////////////////////////////////////////////////////////////// */

class   X
{};

int main()
{
    short*                  ps      =   NULL;
    int volatile*           pvi     =   NULL;
    unsigned const*         pcu     =   NULL;
    long const volatile*    pcvl    =   NULL;

    // Can cast ps to any non-const, non-volatile pointer type, or ...
    stlsoft::sap_cast<short*>(ps);                      // Valid cast
    stlsoft::sap_cast<int*>(ps);                        // Valid cast
    stlsoft::sap_cast<unsigned*>(ps);                   // Valid cast
    stlsoft::sap_cast<long*>(ps);                       // Valid cast
    stlsoft::sap_cast<double*>(ps);                     // Valid cast
    stlsoft::sap_cast<X*>(ps);                          // Valid cast
    // ... any non-const, volatile pointer type, or ...
    stlsoft::sap_cast<short volatile*>(ps);             // Valid cast
    stlsoft::sap_cast<int volatile*>(ps);               // Valid cast
    stlsoft::sap_cast<unsigned volatile*>(ps);          // Valid cast
    stlsoft::sap_cast<long volatile*>(ps);              // Valid cast
    stlsoft::sap_cast<double volatile*>(ps);            // Valid cast
    stlsoft::sap_cast<X volatile*>(ps);                 // Valid cast
    // ... any const, non-volatile pointer type, or ...
    stlsoft::sap_cast<short const*>(ps);                // Valid cast
    stlsoft::sap_cast<int const*>(ps);                  // Valid cast
    stlsoft::sap_cast<unsigned const*>(ps);             // Valid cast
    stlsoft::sap_cast<long const*>(ps);                 // Valid cast
    stlsoft::sap_cast<double const*>(ps);               // Valid cast
    stlsoft::sap_cast<X const*>(ps);                    // Valid cast
    // ... any const, volatile pointer type.
    stlsoft::sap_cast<short const volatile*>(ps);       // Valid cast
    stlsoft::sap_cast<int const volatile*>(ps);         // Valid cast
    stlsoft::sap_cast<unsigned const volatile*>(ps);    // Valid cast
    stlsoft::sap_cast<long const volatile*>(ps);        // Valid cast
    stlsoft::sap_cast<double const volatile*>(ps);      // Valid cast
    stlsoft::sap_cast<X const volatile*>(ps);           // Valid cast

    // Can cast pvi to any non-const, volatile pointer type, or ...
    stlsoft::sap_cast<short volatile*>(pvi);            // Valid cast
    stlsoft::sap_cast<int volatile*>(pvi);              // Valid cast
    stlsoft::sap_cast<unsigned volatile*>(pvi);         // Valid cast
    stlsoft::sap_cast<long volatile*>(pvi);             // Valid cast
    stlsoft::sap_cast<double volatile*>(pvi);           // Valid cast
    // ... any const, volatile pointer type.
    stlsoft::sap_cast<short const volatile*>(pvi);      // Valid cast
    stlsoft::sap_cast<int const volatile*>(pvi);        // Valid cast
    stlsoft::sap_cast<unsigned const volatile*>(pvi);   // Valid cast
    stlsoft::sap_cast<long const volatile*>(pvi);       // Valid cast
    stlsoft::sap_cast<double const volatile*>(pvi);     // Valid cast

    // Can cast pcu to any non-const, volatile pointer type, or ...
    stlsoft::sap_cast<short const*>(pcu);               // Valid cast
    stlsoft::sap_cast<int const*>(pcu);                 // Valid cast
    stlsoft::sap_cast<unsigned const*>(pcu);            // Valid cast
    stlsoft::sap_cast<long const*>(pcu);                // Valid cast
    stlsoft::sap_cast<double const*>(pcu);              // Valid cast
    // ... any const, volatile pointer type.
    stlsoft::sap_cast<short const volatile*>(pcu);      // Valid cast
    stlsoft::sap_cast<int const volatile*>(pcu);        // Valid cast
    stlsoft::sap_cast<unsigned const volatile*>(pcu);   // Valid cast
    stlsoft::sap_cast<long const volatile*>(pcu);       // Valid cast
    stlsoft::sap_cast<double const volatile*>(pcu);     // Valid cast

    // Can cast pcvl to any const, volatile pointer type
    stlsoft::sap_cast<short const volatile*>(pcvl);     // Valid cast
    stlsoft::sap_cast<int const volatile*>(pcvl);       // Valid cast
    stlsoft::sap_cast<unsigned const volatile*>(pcvl);  // Valid cast
    stlsoft::sap_cast<long const volatile*>(pcvl);      // Valid cast
    stlsoft::sap_cast<double const volatile*>(pcvl);    // Valid cast

#ifdef DEMONSTRATE_ERRORS

    // However, if we try and change the cv-qualifier, we run into trouble

    // We cannot remove volatile, or ...
    stlsoft::sap_cast<int *>(pvi);                      // Compile error
    stlsoft::sap_cast<int const *>(pvi);                // Compile error
    // ... remove const, or ...
    stlsoft::sap_cast<unsigned *>(pcu);                 // Compile error
    stlsoft::sap_cast<unsigned volatile *>(pcu);        // Compile error
    // ... remove const and volatile.
    stlsoft::sap_cast<long *>(pcvl);                    // Compile error
#endif


    return 0;
}


/* ///////////////////////////// end of file //////////////////////////// */

