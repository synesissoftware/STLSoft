/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/filesystem/io_functions.write_string/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::write_string<>()`.
 *
 * Created: 22nd January 2024
 * Updated: 14th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/filesystem/io_functions/write_string.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <platformstl/filesystem/FILE_stream.hpp>
#include <platformstl/filesystem/file_lines.hpp>

/* Standard C++ header files */
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_WRITE_CSS_N_EMPTY();
    static void TEST_WRITE_CSS_N_1_CHARACTER();
    static void TEST_WRITE_CSS_N_1_LONG_STRING();
    static void TEST_WRITE_CSS_N_3_STRINGS();

    static void TEST_WRITE_CSS_EMPTY();
    static void TEST_WRITE_CSS_1_CHARACTER();
    static void TEST_WRITE_CSS_1_LONG_STRING();
    static void TEST_WRITE_CSS_3_STRINGS();

    static void TEST_WRITE_STDSTRING_EMPTY();
    static void TEST_WRITE_STDSTRING_1_CHARACTER();
    static void TEST_WRITE_STDSTRING_1_LONG_STRING();
    static void TEST_WRITE_STDSTRING_3_STRINGS();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.filesystem.io_functions.write_string", verbosity))
    {
        XTESTS_RUN_CASE(TEST_WRITE_CSS_N_EMPTY);
        XTESTS_RUN_CASE(TEST_WRITE_CSS_N_1_CHARACTER);
        XTESTS_RUN_CASE(TEST_WRITE_CSS_N_1_LONG_STRING);
        XTESTS_RUN_CASE(TEST_WRITE_CSS_N_3_STRINGS);

        XTESTS_RUN_CASE(TEST_WRITE_CSS_EMPTY);
        XTESTS_RUN_CASE(TEST_WRITE_CSS_1_CHARACTER);
        XTESTS_RUN_CASE(TEST_WRITE_CSS_1_LONG_STRING);
        XTESTS_RUN_CASE(TEST_WRITE_CSS_3_STRINGS);

        XTESTS_RUN_CASE(TEST_WRITE_STDSTRING_EMPTY);
        XTESTS_RUN_CASE(TEST_WRITE_STDSTRING_1_CHARACTER);
        XTESTS_RUN_CASE(TEST_WRITE_STDSTRING_1_LONG_STRING);
        XTESTS_RUN_CASE(TEST_WRITE_STDSTRING_3_STRINGS);


        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using ::xtests::cpp::util::temp_file;


static void TEST_WRITE_CSS_N_EMPTY()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        stlsoft::write_string(stm, "", 0);
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(0u, lines.size());
    }
}

static void TEST_WRITE_CSS_N_1_CHARACTER()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        stlsoft::write_string(stm, "a", 1);
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(1u, lines.size());
        TEST_MS_EQ_N("a", lines[0], lines[0].size());
    }
}

static void TEST_WRITE_CSS_N_1_LONG_STRING()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        stlsoft::write_string(stm, "abcdefghijklmnopqrstuvwxyz", 26);
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(1u, lines.size());
        TEST_MS_EQ_N("abcdefghijklmnopqrstuvwxyz", lines[0], lines[0].size());
    }
}

static void TEST_WRITE_CSS_N_3_STRINGS()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        stlsoft::write_string(stm, "abc\n", 4);
        stlsoft::write_string(stm, "defg\n", 5);
        stlsoft::write_string(stm, "hi\n", 3);
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(3u, lines.size());
        TEST_MS_EQ_N("abc", lines[0], lines[0].size());
        TEST_MS_EQ_N("defg", lines[1], lines[1].size());
        TEST_MS_EQ_N("hi", lines[2], lines[2].size());
    }
}


static void TEST_WRITE_CSS_EMPTY()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        stlsoft::write_string(stm, "");
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(0u, lines.size());
    }
}

static void TEST_WRITE_CSS_1_CHARACTER()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        stlsoft::write_string(stm, "a");
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(1u, lines.size());
        TEST_MS_EQ_N("a", lines[0], lines[0].size());
    }
}

static void TEST_WRITE_CSS_1_LONG_STRING()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        stlsoft::write_string(stm, "abcdefghijklmnopqrstuvwxyz");
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(1u, lines.size());
        TEST_MS_EQ_N("abcdefghijklmnopqrstuvwxyz", lines[0], lines[0].size());
    }
}

static void TEST_WRITE_CSS_3_STRINGS()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        stlsoft::write_string(stm, "abc\n");
        stlsoft::write_string(stm, "defg\n");
        stlsoft::write_string(stm, "hi\n");
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(3u, lines.size());
        TEST_MS_EQ_N("abc", lines[0], lines[0].size());
        TEST_MS_EQ_N("defg", lines[1], lines[1].size());
        TEST_MS_EQ_N("hi", lines[2], lines[2].size());
    }
}


static void TEST_WRITE_STDSTRING_EMPTY()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        std::string const           s;

        stlsoft::write_string(stm, s);
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(0u, lines.size());
    }
}

static void TEST_WRITE_STDSTRING_1_CHARACTER()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        std::string const           s("a");

        stlsoft::write_string(stm, s);
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(1u, lines.size());
        TEST_MS_EQ_N("a", lines[0], lines[0].size());
    }
}

static void TEST_WRITE_STDSTRING_1_LONG_STRING()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        std::string const           s("abcdefghijklmnopqrstuvwxyz");

        stlsoft::write_string(stm, s);
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(1u, lines.size());
        TEST_MS_EQ_N("abcdefghijklmnopqrstuvwxyz", lines[0], lines[0].size());
    }
}

static void TEST_WRITE_STDSTRING_3_STRINGS()
{
    temp_file   f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        std::string const           s1("abc\n");
        std::string const           s2("defg\n");
        std::string const           s3("hi\n");

        stlsoft::write_string(stm, s1);
        stlsoft::write_string(stm, s2);
        stlsoft::write_string(stm, s3);
    }

    {
        platformstl::file_lines     lines(f.c_str());

        TEST_INT_EQ(3u, lines.size());
        TEST_MS_EQ_N("abc", lines[0], lines[0].size());
        TEST_MS_EQ_N("defg", lines[1], lines[1].size());
        TEST_MS_EQ_N("hi", lines[2], lines[2].size());
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

