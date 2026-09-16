
#include <winstl/system/console_functions.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    ((void)&argc);
    ((void)&argv);


    /* winstl_C_write_console_string_m() */
    {
        printf("\nwinstl_C_write_console_string_m():\n");

        {
            stlsoft_C_string_slice_m_t const slice = { 19, "multibyte message\r\n" };

            winstl_C_write_console_string_m(GetStdHandle(STD_OUTPUT_HANDLE), &slice);
        }

    }

    /* winstl_C_write_console_string_w() */
    {
        printf("\nwinstl_C_write_console_string_w():\n");

        {
            stlsoft_C_string_slice_w_t const slice = { 14, L"wide message\r\n" };

            winstl_C_write_console_string_w(GetStdHandle(STD_OUTPUT_HANDLE), &slice);
        }

    }


    /* winstl_C_write_console_line_m() */
    {
        printf("\nwinstl_C_write_console_line_m():\n");

        {
            stlsoft_C_string_slice_m_t const slice = { 17, "multibyte message" };

            winstl_C_write_console_line_m(GetStdHandle(STD_OUTPUT_HANDLE), &slice);
        }

    }

    /* winstl_C_write_console_line_w() */
    {
        printf("\nwinstl_C_write_console_line_w():\n");

        {
            stlsoft_C_string_slice_w_t const slice = { 12, L"wide message" };

            winstl_C_write_console_line_w(GetStdHandle(STD_OUTPUT_HANDLE), &slice);
        }

    }


    return 0;
}
