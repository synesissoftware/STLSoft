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
#include <stlsoft/api/internal/stdio.h>
#include <stlsoft/diagnostics/std_chrono_hrc_stopwatch.hpp>
#include <stlsoft/string/string_view.hpp>
#include <stlsoft/util/string/snprintf.h>

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#if __cplusplus >= 201703L
# include <string_view>
#endif /* C++17+ */
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

typedef platformstl::basic_file_lines<
    char
,   std::string
>                                                           file_lines_std_string_t;
typedef platformstl::basic_file_lines<
    char
,   stlsoft::simple_string
>                                                           file_lines_stlsoft_simple_string_t;
typedef platformstl::basic_file_lines<
    char
,   stlsoft::string_view
>                                                           file_lines_stlsoft_string_view_t;
#if __cplusplus >= 201703L

typedef platformstl::basic_file_lines<
    char
,   std::string_view
>                                                           file_lines_std_string_view_t;
#endif /* C++17+ */


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

char const TEST_FILE_NAME[] = "test.performance.platformstl.file_lines.txt";

std::size_t const COLUMN_WIDTH_ANCHOR           = 12;
std::size_t const COLUMN_WIDTH_IMPLEMENTATION   = 48;
std::size_t const COLUMN_WIDTH_ITERATIONS       = 12;
std::size_t const COLUMN_WIDTH_NS_PER_OPERATION = 12;
std::size_t const COLUMN_WIDTH_SCENARIO         = 24;
std::size_t const COLUMN_WIDTH_TOTAL_TIME       = 16;
const std::size_t NUM_ITERATIONS = 1000;
const std::size_t NUM_WARMUPS = 2;

} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

enum line_ending_t
{
        line_ending_lf     =   0
    ,   line_ending_crlf
    ,   line_ending_cr
};

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

char const*
line_ending_name_(
    line_ending_t ending
)
{
    switch (ending)
    {
    case line_ending_cr:

        return "CR";
    case line_ending_crlf:

        return "CRLF";
    case line_ending_lf:
    default:

        return "LF";
    }
}

bool
write_test_file(
    std::size_t     num_lines
,   std::size_t     line_length
,   line_ending_t   ending
)
{
    char const* eol     =   "\n";
    std::size_t eol_len =   1u;

    switch (ending)
    {
    case line_ending_cr:

        eol = "\r";
        break;
    case line_ending_crlf:

        eol     =   "\r\n";
        eol_len =   2u;
        break;
    case line_ending_lf:
    default:

        break;
    }

    std::string const line = make_line(line_length);

    FILE* stm = NULL;

    if (0 != STLSOFT_API_INTERNAL_stdio_fopen_m(TEST_FILE_NAME, "wb", &stm))
    {
        return false;
    }

    for (std::size_t i = 0; num_lines != i; ++i)
    {
        if (line.size() != fwrite(line.data(), 1u, line.size(), stm))
        {
            fclose(stm);
            return false;
        }
        if (eol_len != fwrite(eol, 1u, eol_len, stm))
        {
            fclose(stm);
            return false;
        }
    }

    return (0 == fclose(stm));
}

template <typename T_file_lines>
std::size_t
read_file_lines_()
{
    T_file_lines lines(TEST_FILE_NAME);
    std::size_t anchor = lines.size();

    for (typename T_file_lines::const_iterator i = lines.begin(); lines.end() != i; ++i)
    {
        anchor += (*i).size();
    }

    return anchor;
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
        << std::left
        << std::setw(COLUMN_WIDTH_SCENARIO) << scenario
        << std::setw(COLUMN_WIDTH_IMPLEMENTATION) << implementation
        << std::right
        << std::setw(COLUMN_WIDTH_ITERATIONS) << num_iterations
        << std::setw(COLUMN_WIDTH_TOTAL_TIME) << result.first
        << std::setw(COLUMN_WIDTH_NS_PER_OPERATION) << std::fixed << std::setprecision(3)
        << (static_cast<double>(result.first) / num_iterations)
        << std::setw(COLUMN_WIDTH_ANCHOR) << result.second
        << std::endl;
}

void
run_scenario(
    std::size_t     num_lines
,   std::size_t     line_length
,   line_ending_t   ending
)
{
    char scenario[64];

    stlsoft::snprintf(
        scenario
    ,   sizeof(scenario)
    ,   "%lu %s x %lu %s"
    ,   static_cast<unsigned long>(num_lines)
    ,   (1u == num_lines) ? "line" : "lines"
    ,   static_cast<unsigned long>(line_length)
    ,   line_ending_name_(ending)
    );

    if (!write_test_file(num_lines, line_length, ending))
    {
        std::cerr
            << "failed to write "
            << TEST_FILE_NAME
            << std::endl
            ;

        return;
    }

    result_t const getline = time_(NUM_ITERATIONS, []() -> std::size_t {
        std::vector<std::string> lines;
        std::string line;
        std::size_t anchor = 0;
        FILE* stm = NULL;

        if (0 != STLSOFT_API_INTERNAL_stdio_fopen_m(TEST_FILE_NAME, "rb", &stm))
        {
            return 0u;
        }

        for (int ch = fgetc(stm); EOF != ch; ch = fgetc(stm))
        {
            if ('\n' == ch)
            {
                anchor += line.size();
                lines.push_back(line);
                line.clear();
            }
            else
            {
                line.push_back(static_cast<char>(ch));
            }
        }

        if (0u != line.size())
        {
            anchor += line.size();
            lines.push_back(line);
        }

        fclose(stm);

        return lines.size() + anchor;
    });

    result_t const file_lines_std_string = time_(NUM_ITERATIONS, []() -> std::size_t {
        return read_file_lines_<file_lines_std_string_t>();
    });

    result_t const file_lines_stlsoft_simple_string = time_(NUM_ITERATIONS, []() -> std::size_t {
        return read_file_lines_<file_lines_stlsoft_simple_string_t>();
    });

    result_t const file_lines_stlsoft_string_view = time_(NUM_ITERATIONS, []() -> std::size_t {
        return read_file_lines_<file_lines_stlsoft_string_view_t>();
    });

    display_result(scenario, "vector<std::string>+getline", NUM_ITERATIONS, getline);
    display_result(scenario, "basic_file_lines<std::string>", NUM_ITERATIONS, file_lines_std_string);
    display_result(scenario, "basic_file_lines<stlsoft::simple_string>", NUM_ITERATIONS, file_lines_stlsoft_simple_string);
    display_result(scenario, "basic_file_lines<stlsoft::string_view>", NUM_ITERATIONS, file_lines_stlsoft_string_view);
#if __cplusplus >= 201703L

    result_t const file_lines_std_string_view = time_(NUM_ITERATIONS, []() -> std::size_t {
        return read_file_lines_<file_lines_std_string_view_t>();
    });

    display_result(scenario, "basic_file_lines<std::string_view>", NUM_ITERATIONS, file_lines_std_string_view);
#endif /* C++17+ */
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int /*argc*/, char* /*argv*/[])
{
    std::cout
        << std::left
        << std::setw(COLUMN_WIDTH_SCENARIO) << "scenario"
        << std::setw(COLUMN_WIDTH_IMPLEMENTATION) << "implementation"
        << std::right
        << std::setw(COLUMN_WIDTH_ITERATIONS) << "iterations"
        << std::setw(COLUMN_WIDTH_TOTAL_TIME) << "total-ns"
        << std::setw(COLUMN_WIDTH_NS_PER_OPERATION) << "ns/op"
        << std::setw(COLUMN_WIDTH_ANCHOR) << "anchor"
        << std::endl
        ;

    struct scenario_t
    {
        std::size_t     num_lines;
        std::size_t     line_length;
        line_ending_t   ending;
    };

    /* LF, then CRLF, then CR. The two large shapes match the original LF
     * runs. The small shapes (one line, a handful of lines, about 2KB) are
     * the fixed-cost region a later small-file path has to beat.
     */
    scenario_t const scenarios[] =
    {
            { 1000, 64, line_ending_lf,   },
            { 1000, 64, line_ending_crlf, },
            { 1000, 64, line_ending_cr,   },
            { 5000, 80, line_ending_lf,   },
            { 5000, 80, line_ending_crlf, },
            { 5000, 80, line_ending_cr,   },
            {    1, 16, line_ending_lf,   },
            {    1, 16, line_ending_crlf, },
            {    1, 16, line_ending_cr,   },
            {    8, 32, line_ending_lf,   },
            {    8, 32, line_ending_crlf, },
            {    8, 32, line_ending_cr,   },
            {   32, 64, line_ending_lf,   },
            {   32, 64, line_ending_crlf, },
            {   32, 64, line_ending_cr,   },
    };

    { for (std::size_t i = 0; STLSOFT_NUM_ELEMENTS(scenarios) != i; ++i)
    {
        run_scenario(scenarios[i].num_lines, scenarios[i].line_length, scenarios[i].ending);
    }}

    std::remove(TEST_FILE_NAME);

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

