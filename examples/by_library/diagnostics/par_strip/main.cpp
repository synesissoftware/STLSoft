/* /////////////////////////////////////////////////////////////////////////
 * File:    by_library/diagnostics/par_strip/main.cpp
 *
 * Purpose: C++ example program demonstrating `stlsoft::par_strip`.
 *
 * Created: 24th September 2026
 * Updated: 24th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <stlsoft/diagnostics/par_strip.hpp>

#include <iostream>

#include <stdlib.h>


int main()
{
    using stlsoft::par_strip;
    using stlsoft::par_strip_direction;
    using stlsoft::ss_sint64_t;

    typedef par_strip<10, ss_sint64_t>                  par_strip_10_t;

    par_strip_10_t const backward_slower(-2, +5, par_strip_direction::backward, 100, 110);
    par_strip_10_t const backward_faster(-2, +5, par_strip_direction::backward, 100, 91);

    std::cout << "timing 110ns vs 100ns: " << backward_slower.to_strip() << std::endl;
    std::cout << "timing  91ns vs 100ns: " << backward_faster.to_strip() << std::endl;

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

