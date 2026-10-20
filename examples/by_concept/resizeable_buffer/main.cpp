/* /////////////////////////////////////////////////////////////////////////
 * File:    by_concept/resizeable_buffer/main.cpp
 *
 * Purpose: C++ example program demonstrating the Resizeable Buffer
 *          concept: probe-then-fill into `stlsoft::auto_buffer` and
 *          `std::vector` via `platformstl` traits `rb` overloads (see
 *          CONCEPTS.md).
 *
 * Created: 15th October 2026
 * Updated: 15th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <platformstl/filesystem/filesystem_traits.hpp>
#include <platformstl/system/system_traits.hpp>

#include <stlsoft/memory/auto_buffer.hpp>
#include <stlsoft/util/resizeable_buffer_helpers.hpp>

#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

typedef platformstl::system_traits<char>                    system_traits_t;
typedef platformstl::filesystem_traits<char>                filesystem_traits_t;
typedef stlsoft::auto_buffer<char>                          ab_t;
typedef std::vector<char>                                   vec_t;


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

static
void
print_cstr_field(
    char const*     label
,   char const*     s
,   size_t          n
)
{
    std::cout
        << label
        << " ("
        << n
        << " chars): '"
        << (NULL != s ? s : "")
        << "'"
        << std::endl;
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int /* argc */, char* /* argv */[])
{
    /* Preferred model: stlsoft::auto_buffer — empty demand, traits resize.
     */
    {
        ab_t            home(0);
        size_t const    n = system_traits_t::get_home_directory(home);

        if (0 == n)
        {
            std::cerr << "get_home_directory failed" << std::endl;
        }
        else
        {
            print_cstr_field("home (auto_buffer)", home.data(), n);
        }
    }

    /* Also a model: std::vector — same rb overload contract.
     */
    {
        vec_t           cwd;
        size_t const    n = filesystem_traits_t::get_current_directory(cwd);

        if (0 == n)
        {
            std::cerr << "get_current_directory failed" << std::endl;
        }
        else
        {
            print_cstr_field("cwd (vector)", &cwd[0], n);
        }
    }

    /* Environment value into an empty auto_buffer (traits resize via
     * resizeable_buffer_resize internally).
     */
    {
        char const      name[] = "PATH";
        ab_t            path(0);
        size_t const    n = system_traits_t::get_environment_variable(name, path);

        if (0 == n)
        {
            std::cerr << "get_environment_variable(\"" << name << "\") failed" << std::endl;
        }
        else
        {
            print_cstr_field("PATH (auto_buffer)", path.data(), n);
        }
    }

    /* Direct use of the helper: grow a vector before writing into it.
     */
    {
        vec_t   scratch;

        if (!stlsoft::resizeable_buffer_resize(scratch, 8))
        {
            std::cerr << "resizeable_buffer_resize failed" << std::endl;

            return EXIT_FAILURE;
        }

        scratch[0] = 'r';
        scratch[1] = 'b';
        scratch[2] = '\0';

        print_cstr_field("helper grown vector", &scratch[0], 2);
    }

    /* Path helper on an rb: append a directory separator when missing.
     */
    {
        vec_t           dir;
        size_t const    n = filesystem_traits_t::get_current_directory(dir);

        if (0 != n)
        {
            size_t const n2 = filesystem_traits_t::ensure_dir_end(dir);

            print_cstr_field("cwd with dir-end", &dir[0], n2);
        }
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

