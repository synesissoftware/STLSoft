/* /////////////////////////////////////////////////////////////////////////
 * File:    itoslice/main.c
 *
 * Purpose: Scratch test for `stlsoft_C_itoslice_a()` etc.
 *
 * Created: 18th December 2016
 * Updated: 29th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* STLSoft Header Files */
#include <stlsoft/conversion/itoslice.h>

/* Standard C Header Files */
#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void
f_int(int isVerbose)
{
    char    num[21];

    stlsoft_C_string_slice_a_t const r1 = stlsoft_C_itoslice_a(0, num, STLSOFT_NUM_ELEMENTS(num));

    if (isVerbose)
    {
        printf("r1='%.*s'\n", (int)r1.len, r1.ptr);
    }

    stlsoft_C_string_slice_a_t const r2 = stlsoft_C_itoslice21_a(-123456789, &num);

    if (isVerbose)
    {
        printf("r2='%.*s'\n", (int)r2.len, r2.ptr);
    }
}

static void
f_long(int isVerbose)
{
    char    num[21];

    stlsoft_C_string_slice_a_t const r1 = stlsoft_C_ltoslice_a(0, num, STLSOFT_NUM_ELEMENTS(num));

    if (isVerbose)
    {
        printf("r1='%.*s'\n", (int)r1.len, r1.ptr);
    }

    stlsoft_C_string_slice_a_t const r2 = stlsoft_C_ltoslice21_a(-123456789, &num);

    if (isVerbose)
    {
        printf("r2='%.*s'\n", (int)r2.len, r2.ptr);
    }
}

static void
f_unsigned(int isVerbose)
{
    char    num[21];

    stlsoft_C_string_slice_a_t const r1 = stlsoft_C_utoslice_a(0, num, STLSOFT_NUM_ELEMENTS(num));

    if (isVerbose)
    {
        printf("r1='%.*s'\n", (int)r1.len, r1.ptr);
    }

    stlsoft_C_string_slice_a_t const r2 = stlsoft_C_utoslice21_a(123456789, &num);

    if (isVerbose)
    {
        printf("r2='%.*s'\n", (int)r2.len, r2.ptr);
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char** argv)
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
    puts("itoslice: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

    int isVerbose = 0;

    { for (int i = 1; argc != i; ++i)
    {
        if (0 == strcmp("--verbose", argv[i]))
        {
            isVerbose = 1;
        }
    }}


    f_int(isVerbose);
    f_long(isVerbose);
    f_unsigned(isVerbose);


    return EXIT_SUCCESS;
}

/* ///////////////////////////// end of file //////////////////////////// */
