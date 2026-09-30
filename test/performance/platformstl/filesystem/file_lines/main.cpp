/* /////////////////////////////////////////////////////////////////////////
 * File:    test.performance.platformstl.file_lines/main.cpp
 *
 * Purpose: Comparative perf-test for platformstl::file_lines and
 *          std::ifstream + std::getline.
 *
 * Created: 23rd September 2026
 * Updated: 30th September 2026
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
#include <exception>
#include <fstream>
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

/* TEMPORARY: stderr progress for the MinGW segfault. Flushed per line so
 * the last message is the step that died.
 */
bool trace_step_ = false;

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
    if (trace_step_)
    {
        std::cerr << "[file_lines.perf]   construct" << std::endl;
    }

    T_file_lines lines(TEST_FILE_NAME);

    if (trace_step_)
    {
        std::cerr
            << "[file_lines.perf]   iterate size="
            << lines.size()
            << std::endl
            ;
    }

    std::size_t anchor = lines.size();

    for (typename T_file_lines::const_iterator i = lines.begin(); lines.end() != i; ++i)
    {
        anchor += (*i).size();
    }

    if (trace_step_)
    {
        std::cerr
            << "[file_lines.perf]   walked anchor="
            << anchor
            << std::endl
            ;
    }

    return anchor;
}

template <typename F>
result_t
time_(
    char const* label
,   std::size_t num_iterations
,   F           fn
)
{
    interval_t interval = 0;
    std::size_t anchor = 0;

    std::cerr << "[file_lines.perf] " << label << " begin" << std::endl;

    for (std::size_t w = NUM_WARMUPS; 0 != w; --w)
    {
        stopwatch_t sw;

        anchor = 0;
        sw.start();

        for (std::size_t i = 0; num_iterations != i; ++i)
        {
            bool const trace_iter = (0u == i) || (0u == (i % 100u)) || (num_iterations - 1u == i);

            if (trace_iter)
            {
                std::cerr
                    << "[file_lines.perf] "
                    << label
                    << " warmup="
                    << w
                    << " iter="
                    << i
                    << " enter"
                    << std::endl
                    ;
            }

            trace_step_ = trace_iter;
            anchor += fn();
            trace_step_ = false;

            if (trace_iter)
            {
                std::cerr
                    << "[file_lines.perf] "
                    << label
                    << " warmup="
                    << w
                    << " iter="
                    << i
                    << " leave anchor="
                    << anchor
                    << std::endl
                    ;
            }
        }

        sw.stop();

        if (1 == w)
        {
            interval = sw.get_nanoseconds();
        }
    }

    std::cerr << "[file_lines.perf] " << label << " end" << std::endl;

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

#if defined(STLSOFT_MINGW)

/* MinGW libstdc++ `std::ifstream` segfaults on open. FILE* already reads
 * this fixture, so the getline baseline uses that source and still times
 * `std::getline`.
 */
class fread_streambuf
    : public std::streambuf
{
public:
    explicit fread_streambuf(FILE* stm)
        : stm_(stm)
    {
        setg(buffer_, buffer_, buffer_);
    }

private:
    fread_streambuf(fread_streambuf const&);
    void operator =(fread_streambuf const&);

    int_type underflow()
    {
        if (gptr() < egptr())
        {
            return traits_type::to_int_type(*gptr());
        }

        std::size_t const n = std::fread(buffer_, 1u, sizeof(buffer_), stm_);

        if (0u == n)
        {
            return traits_type::eof();
        }

        setg(buffer_, buffer_, buffer_ + n);

        return traits_type::to_int_type(*gptr());
    }

private:
    FILE*   stm_;
    char    buffer_[4096];
};

#endif /* STLSOFT_MINGW */

std::size_t
read_getline_(
    std::istream&   stm
,   line_ending_t   ending
)
{
    std::vector<std::string> lines;
    std::string line;
    std::size_t anchor = 0;
    char const delimiter = (line_ending_cr == ending) ? '\r' : '\n';

    if (trace_step_)
    {
        std::cerr << "[file_lines.perf]   getline read" << std::endl;
    }

    while (std::getline(stm, line, delimiter))
    {
        if (line_ending_crlf == ending && !line.empty() && '\r' == line.back())
        {
            line.pop_back();
        }

        anchor += line.size();
        lines.push_back(line);
    }

    return lines.size() + anchor;
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

    std::cerr << "[file_lines.perf] scenario " << scenario << " write" << std::endl;

    if (!write_test_file(num_lines, line_length, ending))
    {
        std::cerr
            << "[file_lines.perf] failed to write "
            << TEST_FILE_NAME
            << std::endl
            ;

        return;
    }

    std::cerr << "[file_lines.perf] scenario " << scenario << " wrote" << std::endl;

    result_t const getc = time_("vector<std::string>+getc", NUM_ITERATIONS, []() -> std::size_t {
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

#if defined(STLSOFT_MINGW)

    /* Avoid std::ifstream. Its constructor is the MinGW segfault. */
    result_t const getline = time_("vector<std::string>+getline(FILE*)", NUM_ITERATIONS, [ending]() -> std::size_t {
        FILE* fp = NULL;

        if (trace_step_)
        {
            std::cerr << "[file_lines.perf]   getline open" << std::endl;
        }

        if (0 != STLSOFT_API_INTERNAL_stdio_fopen_m(TEST_FILE_NAME, "rb", &fp))
        {
            return 0u;
        }

        std::size_t anchor = 0;

        {
            fread_streambuf buf(fp);
            std::istream stm(&buf);

            anchor = read_getline_(stm, ending);
        }

        fclose(fp);

        return anchor;
    });
#else /* ? STLSOFT_MINGW */

    result_t const getline = time_("vector<std::string>+getline", NUM_ITERATIONS, [ending]() -> std::size_t {
        if (trace_step_)
        {
            std::cerr << "[file_lines.perf]   getline open" << std::endl;
        }

        std::ifstream stm(TEST_FILE_NAME, std::ios::binary);

        return read_getline_(stm, ending);
    });
#endif /* STLSOFT_MINGW */

    result_t const file_lines_std_string = time_("basic_file_lines<std::string>", NUM_ITERATIONS, []() -> std::size_t {
        return read_file_lines_<file_lines_std_string_t>();
    });

    result_t const file_lines_stlsoft_simple_string = time_("basic_file_lines<stlsoft::simple_string>", NUM_ITERATIONS, []() -> std::size_t {
        return read_file_lines_<file_lines_stlsoft_simple_string_t>();
    });

    result_t const file_lines_stlsoft_string_view = time_("basic_file_lines<stlsoft::string_view>", NUM_ITERATIONS, []() -> std::size_t {
        return read_file_lines_<file_lines_stlsoft_string_view_t>();
    });

    display_result(scenario, "vector<std::string>+getc", NUM_ITERATIONS, getc);
#if defined(STLSOFT_MINGW)

    display_result(scenario, "vector<std::string>+getline(FILE*)", NUM_ITERATIONS, getline);
#else /* ? STLSOFT_MINGW */

    display_result(scenario, "vector<std::string>+getline", NUM_ITERATIONS, getline);
#endif /* STLSOFT_MINGW */
    display_result(scenario, "basic_file_lines<std::string>", NUM_ITERATIONS, file_lines_std_string);
    display_result(scenario, "basic_file_lines<stlsoft::simple_string>", NUM_ITERATIONS, file_lines_stlsoft_simple_string);
    display_result(scenario, "basic_file_lines<stlsoft::string_view>", NUM_ITERATIONS, file_lines_stlsoft_string_view);
#if __cplusplus >= 201703L

    result_t const file_lines_std_string_view = time_("basic_file_lines<std::string_view>", NUM_ITERATIONS, []() -> std::size_t {
        return read_file_lines_<file_lines_std_string_view_t>();
    });

    display_result(scenario, "basic_file_lines<std::string_view>", NUM_ITERATIONS, file_lines_std_string_view);
#endif /* C++17+ */
}


/* /////////////////////////////////////////////////////////////////////////
 * startup probe
 *
 * TEMPORARY. Flushed C stdio, including a constructor before main, so a
 * crash during C++ startup still leaves a line. The full matrix runs only
 * when SIS_FILE_LINES_PERF_FULL is set.
 */

char const TRACE_FILE_NAME_[] = "file_lines.perf.trace.txt";

static void trace_c_(char const* stage)
{
    /* Disk first: CI showed exit 1 with no console lines from this exe. */
    if (FILE* const tf = std::fopen(TRACE_FILE_NAME_, "a"))
    {
        std::fprintf(tf, "[file_lines.perf] %s\n", stage);
        std::fflush(tf);
        std::fclose(tf);
    }

    std::fprintf(stdout, "[file_lines.perf] %s\n", stage);
    std::fprintf(stderr, "[file_lines.perf] %s\n", stage);
    std::fflush(stdout);
    std::fflush(stderr);
}

#if defined(__GNUC__)

__attribute__((constructor(101)))
static void trace_pre_main_early_()
{
    std::setvbuf(stdout, NULL, _IONBF, 0);
    std::setvbuf(stderr, NULL, _IONBF, 0);
    trace_c_("constructor early");
}

__attribute__((constructor(65535)))
static void trace_pre_main_late_()
{
    trace_c_("constructor late");
}

#endif /* __GNUC__ */

static int probe_()
{
    trace_c_("probe write");

    if (!write_test_file(1u, 3u, line_ending_lf))
    {
        trace_c_("probe write failed");

        return EXIT_FAILURE;
    }

    trace_c_("probe write done");
    trace_c_("probe fgetc");

    {
        FILE* stm = NULL;

        if (0 != STLSOFT_API_INTERNAL_stdio_fopen_m(TEST_FILE_NAME, "rb", &stm))
        {
            trace_c_("probe fgetc open failed");

            return EXIT_FAILURE;
        }

        int const ch = std::fgetc(stm);

        std::fclose(stm);
        std::fprintf(stderr, "[file_lines.perf] probe fgetc ch=%d\n", ch);
        std::fflush(stderr);
    }

#if defined(STLSOFT_MINGW)

    trace_c_("probe streambuf getline");

    {
        FILE* fp = NULL;

        if (0 != STLSOFT_API_INTERNAL_stdio_fopen_m(TEST_FILE_NAME, "rb", &fp))
        {
            trace_c_("probe streambuf open failed");

            return EXIT_FAILURE;
        }

        std::size_t anchor = 0u;

        {
            fread_streambuf buf(fp);
            std::istream stm(&buf);

            trace_c_("probe streambuf opened");

            anchor = read_getline_(stm, line_ending_lf);
        }

        std::fclose(fp);
        std::fprintf(stderr, "[file_lines.perf] probe streambuf anchor=%lu\n", static_cast<unsigned long>(anchor));
        std::fflush(stderr);
    }

#endif /* STLSOFT_MINGW */

    trace_c_("probe file_lines std::string");

    try
    {
        file_lines_std_string_t lines(TEST_FILE_NAME);

        std::fprintf(stderr, "[file_lines.perf] probe file_lines std::string size=%lu\n", static_cast<unsigned long>(lines.size()));
        std::fflush(stderr);
    }
    catch (std::exception const& x)
    {
        std::fprintf(stderr, "[file_lines.perf] probe file_lines std::string exception: %s\n", x.what());
        std::fflush(stderr);

        return EXIT_FAILURE;
    }

    trace_c_("probe file_lines simple_string");

    try
    {
        file_lines_stlsoft_simple_string_t lines(TEST_FILE_NAME);

        std::fprintf(stderr, "[file_lines.perf] probe file_lines simple_string size=%lu\n", static_cast<unsigned long>(lines.size()));
        std::fflush(stderr);
    }
    catch (std::exception const& x)
    {
        std::fprintf(stderr, "[file_lines.perf] probe file_lines simple_string exception: %s\n", x.what());
        std::fflush(stderr);

        return EXIT_FAILURE;
    }

    trace_c_("probe file_lines string_view");

    try
    {
        file_lines_stlsoft_string_view_t lines(TEST_FILE_NAME);

        std::fprintf(stderr, "[file_lines.perf] probe file_lines string_view size=%lu\n", static_cast<unsigned long>(lines.size()));
        std::fflush(stderr);
    }
    catch (std::exception const& x)
    {
        std::fprintf(stderr, "[file_lines.perf] probe file_lines string_view exception: %s\n", x.what());
        std::fflush(stderr);

        return EXIT_FAILURE;
    }

    /* Known MinGW crash site. Last, so the lines above still appear. */
    trace_c_("probe ifstream");

    try
    {
        std::ifstream stm(TEST_FILE_NAME, std::ios::binary);

        trace_c_("probe ifstream opened");

        std::size_t const anchor = read_getline_(stm, line_ending_lf);

        std::fprintf(stderr, "[file_lines.perf] probe ifstream anchor=%lu\n", static_cast<unsigned long>(anchor));
        std::fflush(stderr);
    }
    catch (std::exception const& x)
    {
        std::fprintf(stderr, "[file_lines.perf] probe ifstream exception: %s\n", x.what());
        std::fflush(stderr);

        return EXIT_FAILURE;
    }

    trace_c_("probe passed");

    return EXIT_SUCCESS;
}

/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int /*argc*/, char* /*argv*/[])
{
    trace_c_("main");

    int const probe = probe_();

    if (0 != probe)
    {
        trace_c_("probe failed");

        return probe;
    }

    char const* const full = std::getenv("SIS_FILE_LINES_PERF_FULL");

    if (NULL == full || '\0' == full[0] || '0' == full[0])
    {
        trace_c_("full matrix skipped");
        std::remove(TEST_FILE_NAME);

        return EXIT_SUCCESS;
    }

    std::cerr << std::unitbuf;
    std::cerr << "[file_lines.perf] start" << std::endl;

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

    std::cerr << "[file_lines.perf] remove " << TEST_FILE_NAME << std::endl;

    std::remove(TEST_FILE_NAME);

    std::cerr << "[file_lines.perf] done" << std::endl;

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

