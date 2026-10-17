
// #define UNIXSTL_USE_SEMAPHORE_APPLE_DISPATCH
// #define UNIXSTL_USE_SEMAPHORE_POSIX

#include <platformstl/system/directory_functions.h>

#include <platformstl/filesystem/path_functions.h>

#include <errno.h>
#include <stdio.h>


int main(int /* argc */, char* argv[])
{
    char const* const   program_name    =   platformstl::get_executable_name_from_path(argv[0]).ptr;
    char                buffer[1001];
    size_t const        n               =   platformstl::get_home_directory(buffer, STLSOFT_NUM_ELEMENTS(buffer));

    if (0 == n)
    {
        int const e = errno;

        fprintf(stderr, "%s: could not obtain home directory: %d\n", program_name, e);

        return EXIT_FAILURE;
    }
    else
    {
        fprintf(stdout, "home directory: %s\n", buffer);

        return EXIT_SUCCESS;
    }
}
