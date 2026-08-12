
#include <winstl/diagnostics/output_debug_line.h>

int main(int argc, char* argv[])
{
    ((void)&argc);
    ((void)&argv);

    winstl_C_diagnostics_output_debug_line_1_m("single string");

    winstl_C_diagnostics_output_debug_line_2_m("two-", "strings");

    winstl_C_diagnostics_output_debug_line_11_m("this", " ", "is", " ", "message", " ", "comprising", " ", "eleven", " ", "elements");

    return 0;
}
