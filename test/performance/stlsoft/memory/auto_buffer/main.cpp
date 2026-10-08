/* /////////////////////////////////////////////////////////////////////////
 * File:    auto_buffer/main.cpp
 *
 * Purpose: Perf-test for `stlsoft::auto_buffer<>`.
 *
 * Created: ... mid 2010s ...
 * Updated: 30th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

// #ifdef NDEBUG
// # error NDEBUG
// #endif


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/memory/auto_buffer.hpp>

#include <platformstl/diagnostics/stopwatch.hpp>
#include <platformstl/filesystem/file_lines.hpp>
#include <platformstl/filesystem/path_functions.h>
#include <stlsoft/containers/frequency_map.hpp>

#include "perf_group_gaps.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <random>


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if STLSOFT_VER_STLSOFT_MEMORY_HPP_AUTO_BUFFER_MAJOR > 5 ||\
    (   STLSOFT_VER_STLSOFT_MEMORY_HPP_AUTO_BUFFER_MAJOR == 5 &&\
        STLSOFT_VER_STLSOFT_MEMORY_HPP_AUTO_BUFFER_MINOR >= 6)
// # define AUTO_BUFFER_HAS_reserve // can't have reserve() until have capacity()
#endif


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

struct blah_t
{
    int ar[10];
};

typedef stlsoft::auto_buffer<blah_t, 10>                    ab_small_t;
typedef stlsoft::auto_buffer<blah_t, 1000>                  ab_large_t;

// size_t const NUM_ITERATIONS = 10000;

class int_input_iterator
    : public STLSOFT_NS_QUAL(iterator_base)<
        STLSOFT_NS_QUAL_STD(input_iterator_tag)
    ,   int
    ,   std::ptrdiff_t
    ,   void    // By-Value Temporary reference
    ,   int     // By-Value Temporary reference
    >
{
public: // types
    typedef int_input_iterator                              class_type;

public: // construction
    explicit
    int_input_iterator(int const* pi)
        : m_pi(pi)
    {}
    int_input_iterator(class_type& rhs)
        : m_pi(rhs.m_pi)
    {
        rhs.m_pi = NULL;
    }
private:
    void operator =(class_type const&) STLSOFT_COPY_ASSIGNMENT_PROSCRIBED;

public: // operators
    class_type& operator ++()
    {
        ++m_pi;

        return *this;
    }

    value_type operator *() const
    {
        return *m_pi;
    }

    bool operator ==(class_type const& rhs) const
    {
        return m_pi == rhs.m_pi;
    }

    bool operator !=(class_type const& rhs) const
    {
        return !operator ==(rhs);
    }

/// Members
private:
    int const* m_pi;
};


/* /////////////////////////////////////////////////////////////////////////
 * helper function declarations
 */

std::vector<std::vector<int>>
create_integers_arrays(
    std::size_t min_num_arrays
,   std::size_t max_num_arrays
,   std::size_t min_num_integers_in_arrays
,   std::size_t max_num_integers_in_arrays
,   int         seed
);

std::list<std::list<int>>
create_integers_lists(
    std::vector<std::vector<int>> const& arrays
);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    char const* const program_name = platformstl::get_executable_name_from_path(argv[0]).ptr;

    if (argc > 1 && 0 == strcmp("--help", argv[1]))
    {
        std::cout
            << "USAGE: "
            << program_name
            << " [ <seed> ]"
            << std::endl;

        return EXIT_SUCCESS;
    }

    int seed;

    switch (argc)
    {
    case 1:

        seed = 999973;

        break;
    case 2:

        seed = atoi(argv[1]);

        break;
    default:

        std::cerr
            << program_name
            << ": "
            << "too many arguments; use --help for usage"
            << std::endl;

        return EXIT_FAILURE;
    }

    std::size_t     min_num_arrays              =   500;
    std::size_t     max_num_arrays              =   1000;
    std::size_t     min_num_integers_in_arrays  =   2;
    std::size_t     max_num_integers_in_arrays  =   20;


    stlsoft::frequency_map<std::size_t> fm_lengths;

    platformstl::stopwatch sw;
    platformstl::stopwatch sw_skip;

    char const* casename;

    perf_maybe_emit_groupgaps_banner(std::cout);

    std::cout << "creating array(s)" << std::endl;

    auto arrays_of_integers = create_integers_arrays(
        min_num_arrays
    ,   max_num_arrays
    ,   min_num_integers_in_arrays
    ,   max_num_integers_in_arrays
    ,   seed
    );
    auto lists_of_integers = create_integers_lists(arrays_of_integers);

    for (auto const& row : arrays_of_integers)
    {
        fm_lengths.push(row.size());
    }

    std::cout
        << arrays_of_integers.size()
        << " array(s)"
        << std::endl;



#ifdef NDEBUG
    const std::size_t NUM_ITERATIONS = 10000;
    const std::size_t NUM_LIST_ITERATIONS = 100;
    const std::size_t NUM_MOVECTOR_ITERATIONS = 1000;
#else
    const std::size_t NUM_ITERATIONS = 10;
    const std::size_t NUM_LIST_ITERATIONS = 2;
    const std::size_t NUM_MOVECTOR_ITERATIONS = 4;
#endif


    // reserve only
    {
        char const* const grpname = "reserve";

        /* Gap between named auto_buffer operation groups. */
        perf_maybe_emit_group_gap(stdout, grpname);
        fprintf(stdout, "%s:\n", grpname);

        platformstl::stopwatch::interval_type   tm_vec = 0;

        // std::vector::vector :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "std::vector::vector() + #reserve()";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        std::vector<int> row_copy;

                        row_copy.reserve(row.size());

                        // r += static_cast<int>(row_copy.size());
                        r += static_cast<int>(row_copy.capacity());
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu (%d)\n", casename, static_cast<unsigned long>(duration), r);

                    tm_vec = duration;
                }
            }}
        }

        // stlsoft::auto_buffer<...>::auto_buffer :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<  10>::auto_buffer(0) + #reserve()";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 10> row_copy(row.size());

                        r += static_cast<int>(row_copy.size());
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer< 100>::auto_buffer(0) + #reserve()";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 100> row_copy(row.size());

                        r += static_cast<int>(row_copy.size());
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<1000>::auto_buffer(0) + #reserve()";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 1000> row_copy(row.size());

                        r += static_cast<int>(row_copy.size());
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}
        }
    }

    // construct N containing value V
    {
        char const* const grpname = "ctor(n, v)";

        /* Gap between named auto_buffer operation groups. */
        perf_maybe_emit_group_gap(stdout, grpname);
        fprintf(stdout, "%s:\n", grpname);

        platformstl::stopwatch::interval_type   tm_vec = 0;

        // std::vector::vector :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "std::vector::vector(n, v)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        std::vector<int> row_copy(row.size(), 12345678);

                        r += static_cast<int>(row_copy.capacity());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu (%d)\n", casename, static_cast<unsigned long>(duration), r);

                    tm_vec = duration;
                }
            }}
        }

        // stlsoft::auto_buffer<...>::auto_buffer :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<  10>::auto_buffer(n, v)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 10> row_copy(row.size(), 12345678);

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer< 100>::auto_buffer(n, v)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 100> row_copy(row.size(), 12345678);

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<1000>::auto_buffer(n, v)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 1000> row_copy(row.size(), 12345678);

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}
        }
    }

    // copy construction (or as close as can be)
    {
        char const* const grpname = "copy construction";

        /* Gap between named auto_buffer operation groups. */
        perf_maybe_emit_group_gap(stdout, grpname);
        fprintf(stdout, "%s:\n", grpname);

        platformstl::stopwatch::interval_type   tm_vec = 0;

        // std::vector::vector :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "std::vector::vector(class_type const&)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        std::vector<int> row_copy{row};

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu (%d)\n", casename, static_cast<unsigned long>(duration), r);

                    tm_vec = duration;
                }
            }}
        }

        // stlsoft::auto_buffer<...>::auto_buffer :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<  10>::auto_buffer(n) + memcpy()";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 10> row_copy(row.size());

                        std::memcpy(&row_copy[0], &row[0], sizeof(int) * row.size());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer< 100>::auto_buffer(n) + memcpy()";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 100> row_copy(row.size());

                        std::memcpy(&row_copy[0], &row[0], sizeof(int) * row.size());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<1000>::auto_buffer(n) + memcpy()";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 1000> row_copy(row.size());

                        std::memcpy(&row_copy[0], &row[0], sizeof(int) * row.size());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}
        }
    }

    // range construction (or as close as can be)
    {
        char const* const grpname = "range construction";

        /* Gap between named auto_buffer operation groups. */
        perf_maybe_emit_group_gap(stdout, grpname);
        fprintf(stdout, "%s:\n", grpname);

        platformstl::stopwatch::interval_type   tm_vec = 0;

        // std::vector::vector :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "std::vector::vector(from : fit, to : fit)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        std::vector<int> row_copy(row.begin(), row.end());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu (%d)\n", casename, static_cast<unsigned long>(duration), r);

                    tm_vec = duration;
                }
            }}
        }

        // stlsoft::auto_buffer<...>::auto_buffer :
        {
#if __cplusplus >= 201703L

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<  10>::auto_buffer(from : T const*, to : T const*)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 10> row_copy(row.begin(), row.end());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer< 100>::auto_buffer(from : T const*, to : T const*)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 100> row_copy(row.begin(), row.end());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<1000>::auto_buffer(from : T const*, to : T const*)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 1000> row_copy(row.begin(), row.end());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}
#endif
        }
#if __cplusplus < 201703L

        {
            STLSOFT_SUPPRESS_UNUSED(tm_vec);
        }
#endif
    }

    // range construction (or as close as can be)
    {
        char const* const grpname = "range construction (from list)";

        /* Gap between named auto_buffer operation groups. */
        perf_maybe_emit_group_gap(stdout, grpname);
        fprintf(stdout, "%s:\n", grpname);

        platformstl::stopwatch::interval_type   tm_vec = 0;

        // std::vector::vector :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "std::vector::vector(from : fit, to : fit)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_LIST_ITERATIONS; ++i)
                {
                    for (auto const& row : lists_of_integers)
                    {
                        std::vector<int> row_copy(row.begin(), row.end());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }}
                }
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu (%d)\n", casename, static_cast<unsigned long>(duration), r);

                    tm_vec = duration;
                }
            }}
#if __cplusplus < 201703L

            {
                STLSOFT_SUPPRESS_UNUSED(tm_vec);
            }
#endif
        }

        // stlsoft::auto_buffer<...>::auto_buffer :
        {
#if __cplusplus >= 201703L

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<  10>::auto_buffer(from : T const*, to : T const*)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_LIST_ITERATIONS; ++i)
                {
                    for (auto const& row : lists_of_integers)
                    {
                        stlsoft::auto_buffer<int, 10> row_copy(row.begin(), row.end());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }}
                }
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer< 100>::auto_buffer(from : T const*, to : T const*)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_LIST_ITERATIONS; ++i)
                {
                    for (auto const& row : lists_of_integers)
                    {
                        stlsoft::auto_buffer<int, 100> row_copy(row.begin(), row.end());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }}
                }
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<1000>::auto_buffer(from : T const*, to : T const*)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_LIST_ITERATIONS; ++i)
                {
                    for (auto const& row : lists_of_integers)
                    {
                        stlsoft::auto_buffer<int, 1000> row_copy(row.begin(), row.end());

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }}
                }
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}
#endif
        }
    }

#if __cplusplus >= 201703L &&\
    !defined(STLSOFT_COMPILER_IS_MSVC) &&\
    1

    // range construction (or as close as can be)
    {
        char const* const grpname = "range construction (from input-iterator)";

        /* Gap between named auto_buffer operation groups. */
        perf_maybe_emit_group_gap(stdout, grpname);
        fprintf(stdout, "%s:\n", grpname);

        platformstl::stopwatch::interval_type   tm_vec = 0;

        // std::vector::vector :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "std::vector::vector(from : fit, to : fit)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_LIST_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        std::vector<int> row_copy(int_input_iterator(&*row.begin()), int_input_iterator(&*row.end()));

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu (%d)\n", casename, static_cast<unsigned long>(duration), r);

                    tm_vec = duration;
                }
            }}
        }

        // stlsoft::auto_buffer<...>::auto_buffer :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<  10>::auto_buffer(from : T const*, to : T const*)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_LIST_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 10> row_copy(int_input_iterator(&*row.begin()), int_input_iterator(&*row.end()));

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer< 100>::auto_buffer(from : T const*, to : T const*)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_LIST_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 100> row_copy(int_input_iterator(&*row.begin()), int_input_iterator(&*row.end()));

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<1000>::auto_buffer(from : T const*, to : T const*)";

                int r = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_LIST_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        stlsoft::auto_buffer<int, 1000> row_copy(int_input_iterator(&*row.begin()), int_input_iterator(&*row.end()));

                        r += static_cast<int>(row_copy.size());

                        r += row_copy.front();
                        r += row_copy.back();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds();

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}
        }
    }
#endif /* C++ version */


    // move ctor
    {
        char const* const grpname = "move ctor";

        /* Gap between named auto_buffer operation groups. */
        perf_maybe_emit_group_gap(stdout, grpname);
        fprintf(stdout, "%s:\n", grpname);

        platformstl::stopwatch::interval_type   tm_vec = 0;

        // std::vector::vector :
        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "std::vector::vector(class_type&&)";

                int r = 0;

                platformstl::stopwatch::interval_type tm_skip = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_MOVECTOR_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        sw_skip.start();
                        std::vector<int> row_copy(row);
                        sw_skip.stop();
                        std::vector<int> row_copy2(std::move(row_copy));

                        r += static_cast<int>(row_copy2.size());

                        r += row_copy2.front();
                        r += row_copy2.back();

                        tm_skip += sw_skip.get_microseconds();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds() - tm_skip;

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu (%d)\n", casename, static_cast<unsigned long>(duration), r);

                    tm_vec = duration;
                }
            }}
        }
#if __cplusplus < 201703L

        {
            STLSOFT_SUPPRESS_UNUSED(tm_vec);
        }
#endif

        // stlsoft::auto_buffer<...>::auto_buffer :
#if __cplusplus >= 201703L

        {
            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<  10>::auto_buffer(class_type&&)";

                int r = 0;

                platformstl::stopwatch::interval_type tm_skip = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_MOVECTOR_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        sw_skip.stop();
                        stlsoft::auto_buffer<int, 10> row_copy(row.begin(), row.end());
                        sw_skip.start();
                        stlsoft::auto_buffer<int, 10> row_copy2(std::move(row_copy));

                        r += static_cast<int>(row_copy2.size());

                        r += row_copy2.front();
                        r += row_copy2.back();

                        tm_skip += sw_skip.get_microseconds();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds() - tm_skip;

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer< 100>::auto_buffer(class_type&&)";

                int r = 0;

                platformstl::stopwatch::interval_type tm_skip = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_MOVECTOR_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        sw_skip.stop();
                        stlsoft::auto_buffer<int, 100> row_copy(row.begin(), row.end());
                        sw_skip.start();
                        stlsoft::auto_buffer<int, 100> row_copy2(std::move(row_copy));

                        r += static_cast<int>(row_copy2.size());

                        r += row_copy2.front();
                        r += row_copy2.back();

                        tm_skip += sw_skip.get_microseconds();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds() - tm_skip;

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}

            { for (size_t WARMUPS = 2; 0 != WARMUPS; --WARMUPS)
            {
                casename = "stlsoft::auto_buffer<1000>::auto_buffer(class_type&&)";

                int r = 0;

                platformstl::stopwatch::interval_type tm_skip = 0;

                sw.start();
                { for (std::size_t i = 0; i != NUM_MOVECTOR_ITERATIONS; ++i)
                {
                    for (auto const& row : arrays_of_integers)
                    {
                        sw_skip.stop();
                        stlsoft::auto_buffer<int, 1000> row_copy(row.begin(), row.end());
                        sw_skip.start();
                        stlsoft::auto_buffer<int, 1000> row_copy2(std::move(row_copy));

                        r += static_cast<int>(row_copy2.size());

                        r += row_copy2.front();
                        r += row_copy2.back();

                        tm_skip += sw_skip.get_microseconds();
                    }
                }}
                sw.stop();

                auto const duration = sw.get_microseconds() - tm_skip;

                if (1 == WARMUPS)
                {
                    fprintf(stdout, "\t%s: %lu %7.3f %% (%d)\n", casename, static_cast<unsigned long>(duration), (100.0 * duration) / tm_vec, r);
                }
            }}
        }
#endif
    }

#if 0

    fprintf(stdout, "data length frequencies:\n");

    for (auto const& f: fm_lengths)
    {
        fprintf(stdout, "\t%lu\t%lu\n"
        ,   static_cast<unsigned long>(f.first)
        ,   static_cast<unsigned long>(f.second)
        );
    }
#endif

    return EXIT_SUCCESS;
}


/* /////////////////////////////////////////////////////////////////////////
 * helper function implementations
 */

std::vector<std::vector<int>>
create_integers_arrays(
    std::size_t min_num_arrays
,   std::size_t max_num_arrays
,   std::size_t min_num_integers_in_arrays
,   std::size_t max_num_integers_in_arrays
,   int         seed
)
{
    STLSOFT_ASSERT(min_num_arrays <= max_num_arrays);
    STLSOFT_ASSERT(min_num_integers_in_arrays <= max_num_integers_in_arrays);

    std::random_device  rd;
    std::mt19937_64     mt(rd());

    mt.seed(seed);

    std::uniform_int_distribution<std::size_t> dist_num_arrays(min_num_arrays, max_num_arrays);
    std::uniform_int_distribution<std::size_t> dist_num_integers(min_num_integers_in_arrays, max_num_integers_in_arrays);

    std::vector<std::vector<int>> v;

    std::size_t const num_arrays = dist_num_arrays(mt);

    v.reserve(num_arrays);

    for (std::size_t i = 0; i != num_arrays; ++i)
    {
        std::size_t const num_integers = dist_num_integers(mt) * dist_num_integers(mt) * dist_num_integers(mt);

        std::vector<int> row;

        row.reserve(num_integers);

        for (std::size_t j = 0; j != num_integers; ++j)
        {
            row.push_back(static_cast<int>(dist_num_integers(mt)));
        }

        v.push_back(row);
    }

    return v;
}


std::list<std::list<int>>
create_integers_lists(
    std::vector<std::vector<int>> const& arrays
)
{
    std::list<std::list<int>> l;

    for (auto const& i : arrays)
    {
        std::list<int> row;

        for (auto const& j : i)
        {
            row.push_back(j);
        }

        l.push_back(row);
    }

    return l;
}


/* ///////////////////////////// end of file //////////////////////////// */

