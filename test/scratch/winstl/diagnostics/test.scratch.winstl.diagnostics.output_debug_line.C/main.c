/* /////////////////////////////////////////////////////////////////////////
 * File:    test.scratch.winstl.diagnostics.output_debug_line.C/main.c
 *
 * Purpose: Scratch test for `winstl_C_diagnostics_output_debug_line_1_m()`, etc.
 *
 * Created: 5th January 2011
 * Updated: 12th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* STLSoft header files */
#include <winstl/diagnostics/output_debug_line.h>

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>

/* ////////////////////////////////////////////////////////////////////// */

static int main_(int argc, char** argv)
{
    ((void)&argc);
    ((void)&argv);


    winstl_C_diagnostics_output_debug_line_1_m("line #1");
    winstl_C_diagnostics_output_debug_line_1_m("line number 2");

    winstl_C_diagnostics_output_debug_line_2_m("line ", "#3");

    winstl_C_diagnostics_output_debug_line_3_m("line ", "number ", "4");


    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    return main_(argc, argv);
}


/* ///////////////////////////// end of file //////////////////////////// */
