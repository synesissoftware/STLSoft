/* /////////////////////////////////////////////////////////////////////////
 * File:    rewind_dir/main.cpp
 *
 * Purpose: Scratch test for `unixstl::filesystem_traits<>::rewind_dir()`,
 *          exploring its interaction with `open_dir()`, `read_dir()`, and
 *          `close_dir()`, on a directory given on the command-line (or the
 *          current directory, if none is given).
 *
 * Created: 8th October 2026
 * Updated: 8th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/filesystem_traits.hpp>

#include <platformstl/filesystem/path_functions.h>

#include <stdio.h>
#include <stdlib.h>


typedef unixstl::filesystem_traits<char>                    fs_traits_t;


namespace {

    /* Reads up to `max` entries from `h`, printing each, and returns the
     * number read
     */
    size_t
    dump_entries(
        DIR*        h
    ,   char const* label
    ,   size_t      max
    )
    {
        size_t n = 0;

        fprintf(stdout, "%s:\n", label);

        for (struct dirent const* de; n < max && NULL != (de = fs_traits_t::read_dir(h)); ++n)
        {
            fprintf(stdout, "\t%s\n", de->d_name);
        }

        fprintf(stdout, "\t(%lu entries)\n", static_cast<unsigned long>(n));

        return n;
    }
} // anonymous namespace


int main(int argc, char* argv[])
{
    char const* const   program_name    =   platformstl::get_executable_name_from_path(argv[0]).ptr;
    char const*         dir             =   ".";

    if (argc > 1)
    {
        dir = argv[1];
    }

    DIR* const h = fs_traits_t::open_dir(dir);

    if (NULL == h)
    {
        fprintf(stderr, "%s: could not open directory '%s'\n", program_name, dir);

        return EXIT_FAILURE;
    }
    else
    {
        size_t const    n1  =   dump_entries(h, "first pass (full)", ~size_t(0));
        size_t const    n2  =   dump_entries(h, "(no rewind; expect nothing)", ~size_t(0));

        fs_traits_t::rewind_dir(h);

        size_t const    n3  =   dump_entries(h, "second pass (after rewind)", ~size_t(0));

        fs_traits_t::rewind_dir(h);

        size_t const    n4  =   dump_entries(h, "third pass (after rewind; first two entries only)", 2);

        fs_traits_t::rewind_dir(h);

        size_t const    n5  =   dump_entries(h, "fourth pass (after rewind from partial read)", ~size_t(0));

        fs_traits_t::close_dir(h);

        fprintf(stdout, "\nsummary: n1=%lu; n2=%lu; n3=%lu; n4=%lu; n5=%lu\n"
        ,   static_cast<unsigned long>(n1)
        ,   static_cast<unsigned long>(n2)
        ,   static_cast<unsigned long>(n3)
        ,   static_cast<unsigned long>(n4)
        ,   static_cast<unsigned long>(n5)
        );

        if (0 != n2 || n1 != n3 || n1 != n5)
        {
            fprintf(stderr, "%s: unexpected entry counts\n", program_name);

            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

