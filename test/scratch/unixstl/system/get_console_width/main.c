
#include <unixstl/unixstl.h>
#include <unixstl/system/console_functions.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  STLSOFT_SUPPRESS_UNUSED(argc);
  STLSOFT_SUPPRESS_UNUSED(argv);

  fprintf(stderr, "console width: %d\n", (int)unixstl_C_get_console_width());

  return EXIT_SUCCESS;
}
