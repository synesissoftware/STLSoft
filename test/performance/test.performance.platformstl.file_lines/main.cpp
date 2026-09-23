/* /////////////////////////////////////////////////////////////////////////
 * File:    test.performance.platformstl.file_lines/main.cpp
 *
 * Purpose: Comparative perf-test for platformstl::file_lines and
 *          std::ifstream + std::getline.
 *
 * Created: 23rd September 2026
 * Updated: 23rd September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <platformstl/filesystem/file_lines.hpp>
#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

typedef stlsoft::std_chrono_hrc_stopwatch                   stopwatch_t;
typedef stopwatch_t::interval_type                          interval_t;

typedef std::pair<
    interval_t
,   std::size_t
>                                                           result_t;


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

char const TEST_FILE_NAME[] = "test.performance.platformstl.file_lines.txt";

const std::size_t NUM_ITERATIONS = 1000;
const std::size_t NUM_WARMUPS = 2;

} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

std::string
make_line(
    std::size_t length
)
{
    std::string line(length, 'x');

    for (std::size_t i = 0; length != i; ++i)
    {
        line[i] = static_cast<char>('a' + (i % 26));
    }

    return line;
}

bool
write_test_file(
    std::size_t num_lines
,   std::size_t line_length
)
{
    std::ofstream stm(TEST_FILE_NAME, std::ios::binary | std::ios::trunc);

    if (!stm)
    {
        return false;
    }

    std::string const line = make_line(line_length);

    for (std::size_t i = 0; num_lines != i; ++i)
    {
        stm << line << '\n';
    }

    return static_cast<bool>(stm);
}

template <typename F>
result_t
time_(
    std::size_t num_iterations
,   F           fn
)
{
    interval_t interval = 0;
    std::size_t anchor = 0;

    for (std::size_t w = NUM_WARMUPS; 0 != w; --w)
    {
        stopwatch_t sw;

        anchor = 0;
        sw.start();

        for (std::size_t i = 0; num_iterations != i; ++i)
        {
            anchor += fn();
        }

        sw.stop();

        if (1 == w)
        {
            interval = sw.get_nanoseconds();
        }
    }

    return std::make_pair(interval, anchor);
}

void
display_result(
    char const*     scenario
,   char const*     implementation
,   std::size_t     num_iterations
,   result_t const& result
)
{
    std::cout
        << '\t'
        << scenario
        << '\t'
        << implementation
        << '\t'
        << num_iterations
        << '\t'
        << std::setw(16) << std::right << result.first
        << '\t'
        << std::setw(12) << std::right << std::fixed << std::setprecision(3)
        << (static_cast<double>(result.first) / num_iterations)
        << '\t'
        << result.second
        << std::endl;
}

void
run_scenario(
    std::size_t num_lines
,   std::size_t line_length
)
{
    char scenario[64];

    std::snprintf(
        scenario
    ,   sizeof(scenario)
    ,   "%lu lines x %lu chars"
    ,   static_cast<unsigned long>(num_lines)
    ,   static_cast<unsigned long>(line_length)
    );

    if (!write_test_file(num_lines, line_length))
    {
        std::cerr
            << "failed to write "
            << TEST_FILE_NAME
            << std::endl
            ;

        return;
    }

    result_t const file_lines = time_(NUM_ITERATIONS, []() -> std::size_t {
        platformstl::file_lines_a lines(TEST_FILE_NAME);
        std::size_t anchor = lines.size();

        for (platformstl::file_lines_a::const_iterator i = lines.begin(); lines.end() != i; ++i)
        {
            anchor += (*i).size();
        }

        return anchor;
    });

    result_t const getline = time_(NUM_ITERATIONS, []() -> std::size_t {
        std::ifstream stm(TEST_FILE_NAME);
        std::vector<std::string> lines;
        std::string line;
        std::size_t anchor = 0;

        while (std::getline(stm, line))
        {
            anchor += line.size();
            lines.push_back(line);
        }

        return lines.size() + anchor;
    });

    display_result(scenario, "platformstl::file_lines", NUM_ITERATIONS, file_lines);
    display_result(scenario, "std::ifstream+getline", NUM_ITERATIONS, getline);
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int /*argc*/, char* /*argv*/[])
{
    std::cout
        << "scenario\timplementation\titerations\ttotal-ns\tns/op\tanchor"
        << std::endl
        ;

    run_scenario(1000, 64);
    run_scenario(5000, 80);

    std::remove(TEST_FILE_NAME);

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

