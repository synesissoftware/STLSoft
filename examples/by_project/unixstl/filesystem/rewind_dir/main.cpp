/* /////////////////////////////////////////////////////////////////////////
 * Purpose: Illustrates the use of `unixstl::filesystem_traits<>` functions
 *          `open_dir()`, `read_dir()`, `rewind_dir()`, and `close_dir()` to
 *          enumerate a directory in two passes: the first to count the
 *          entries, and the second - after rewinding - to collect their
 *          names into a container sized in advance.
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/filesystem_traits.hpp>

#include <platformstl/filesystem/path_functions.h>

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <string.h>


typedef unixstl::filesystem_traits<char>                    fs_traits_t;


int main(int argc, char* argv[])
{
    char const* const   program_name    =   platformstl::get_executable_name_from_path(argv[0]).ptr;
    char const*         root_dir        =   ss_nullptr_k;

    if (argc > 1 && 0 == strcmp("--help", argv[1]))
    {
        std::cout
            << "USAGE: "
            << program_name
            << " [<directory>]"
            << std::endl;

        return EXIT_SUCCESS;
    }

    switch (argc)
    {
    case 1:

        root_dir = ".";
        break;
    case 2:

        root_dir = argv[1];
        break;

    default:

        std::cerr
            << program_name
            << ": "
            << "too many arguments; use --help for usage"
            << std::endl;

        return EXIT_FAILURE;
    }

    DIR* const h = fs_traits_t::open_dir(root_dir);

    if (NULL == h)
    {
        std::cerr
            << program_name
            << ": "
            << "could not open directory '"
            << root_dir
            << "'"
            << std::endl;

        return EXIT_FAILURE;
    }
    else
    {
        std::vector<std::string>    names;
        size_t                      count   =   0;

        // pass 1: count the entries

        while (NULL != fs_traits_t::read_dir(h))
        {
            ++count;
        }

        std::cout
            << "'"
            << root_dir
            << "' contains "
            << count
            << " entries (including '.' and '..')"
            << std::endl;

        // rewind, so that the next read_dir() returns the first entry again

        fs_traits_t::rewind_dir(h);

        // pass 2: collect the names, without any reallocation

        names.reserve(count);

        for (struct dirent const* de; NULL != (de = fs_traits_t::read_dir(h)); )
        {
            names.push_back(de->d_name);
        }

        fs_traits_t::close_dir(h);

        for (std::vector<std::string>::const_iterator i = names.begin(); names.end() != i; ++i)
        {
            std::cout
                << "\t"
                << *i
                << std::endl;
        }
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

