/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.platformstl.filesystem.file_lines/entry.cpp
 *
 * Purpose: Component-tests for `platformstl::file_lines`.
 *
 * Created: 23rd September 2026
 * Updated: 23rd September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <platformstl/filesystem/file_lines.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>
#include <xtests/xtests.h>

/* STLSoft header files */
#include <platformstl/exception/invalid_file_type_exception.hpp>
#include <platformstl/filesystem/FILE_stream.hpp>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    void TEST_EMPTY_FILE();
    void TEST_FILE_WITH_ONE_LINE_UNTERMINATED();
    void TEST_FILE_WITH_ONE_LINE_TERMINATED();
    void TEST_FILE_WITH_THREE_LINES();
    void TEST_FILE_WITH_ONE_LINE_TERMINATED_BY_CRLF();
    void TEST_FILE_WITH_THREE_LINES_SEPARATED_BY_CRLF();
    void TEST_FILE_WITH_CONSECUTIVE_CRLF_GIVES_EMPTY_LINE();
    void TEST_FILE_WITH_ONE_LINE_TERMINATED_BY_CR();
    void TEST_FILE_WITH_THREE_LINES_SEPARATED_BY_CR();
    void TEST_FILE_WITH_CONSECUTIVE_CR_GIVES_EMPTY_LINE();
    void TEST_FILE_CONTAINING_NUL_CHARACTER_THROWS();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.file_lines", verbosity))
    {
        XTESTS_RUN_CASE(TEST_EMPTY_FILE);
        XTESTS_RUN_CASE(TEST_FILE_WITH_ONE_LINE_UNTERMINATED);
        XTESTS_RUN_CASE(TEST_FILE_WITH_ONE_LINE_TERMINATED);
        XTESTS_RUN_CASE(TEST_FILE_WITH_THREE_LINES);
        XTESTS_RUN_CASE(TEST_FILE_WITH_ONE_LINE_TERMINATED_BY_CRLF);
        XTESTS_RUN_CASE(TEST_FILE_WITH_THREE_LINES_SEPARATED_BY_CRLF);
        XTESTS_RUN_CASE(TEST_FILE_WITH_CONSECUTIVE_CRLF_GIVES_EMPTY_LINE);
        XTESTS_RUN_CASE(TEST_FILE_WITH_ONE_LINE_TERMINATED_BY_CR);
        XTESTS_RUN_CASE(TEST_FILE_WITH_THREE_LINES_SEPARATED_BY_CR);
        XTESTS_RUN_CASE(TEST_FILE_WITH_CONSECUTIVE_CR_GIVES_EMPTY_LINE);
        XTESTS_RUN_CASE_THAT_THROWS(TEST_FILE_CONTAINING_NUL_CHARACTER_THROWS, platformstl::invalid_file_type_exception);

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


void TEST_EMPTY_FILE()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    platformstl::file_lines lines(f.c_str());

    TEST_INT_EQ(0u, lines.size());
}

void TEST_FILE_WITH_ONE_LINE_UNTERMINATED()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    {
        platformstl::FILE_stream stm(f.c_str(), "w");

        stm.write("abc");
    }

    platformstl::file_lines lines(f.c_str());

    REQUIRE(TEST_INT_EQ(1u, lines.size()));
    TEST_MS_EQ("abc", lines[0]);
}

void TEST_FILE_WITH_ONE_LINE_TERMINATED()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    {
        platformstl::FILE_stream stm(f.c_str(), "w");

        stm.write_line("abc");
    }

    platformstl::file_lines lines(f.c_str());

    REQUIRE(TEST_INT_EQ(1u, lines.size()));
    TEST_MS_EQ("abc", lines[0]);
}

void TEST_FILE_WITH_THREE_LINES()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    {
        platformstl::FILE_stream stm(f.c_str(), "w");

        stm.write_line("abc");
        stm.write("\nghi");
    }

    platformstl::file_lines lines(f.c_str());

    REQUIRE(TEST_INT_EQ(3u, lines.size()));
    TEST_MS_EQ("abc", lines[0]);
    TEST_MS_EQ("", lines[1]);
    TEST_MS_EQ("ghi", lines[2]);
}

void TEST_FILE_WITH_ONE_LINE_TERMINATED_BY_CRLF()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    {
        platformstl::FILE_stream stm(f.c_str(), "wb");

        stm.write("abc\r\n");
    }

    platformstl::file_lines lines(f.c_str());

    REQUIRE(TEST_INT_EQ(1u, lines.size()));
    TEST_MS_EQ("abc", lines[0]);
}

void TEST_FILE_WITH_THREE_LINES_SEPARATED_BY_CRLF()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    {
        platformstl::FILE_stream stm(f.c_str(), "wb");

        stm.write("abc\r\ndef\r\nghi\r\n");
    }

    platformstl::file_lines lines(f.c_str());

    REQUIRE(TEST_INT_EQ(3u, lines.size()));
    TEST_MS_EQ("abc", lines[0]);
    TEST_MS_EQ("def", lines[1]);
    TEST_MS_EQ("ghi", lines[2]);
}

void TEST_FILE_WITH_CONSECUTIVE_CRLF_GIVES_EMPTY_LINE()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    {
        platformstl::FILE_stream stm(f.c_str(), "wb");

        stm.write("abc\r\n\r\nghi");
    }

    platformstl::file_lines lines(f.c_str());

    REQUIRE(TEST_INT_EQ(3u, lines.size()));
    TEST_MS_EQ("abc", lines[0]);
    TEST_MS_EQ("", lines[1]);
    TEST_MS_EQ("ghi", lines[2]);
}

void TEST_FILE_WITH_ONE_LINE_TERMINATED_BY_CR()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    {
        platformstl::FILE_stream stm(f.c_str(), "wb");

        stm.write("abc\r");
    }

    platformstl::file_lines lines(f.c_str());

    REQUIRE(TEST_INT_EQ(1u, lines.size()));
    TEST_MS_EQ("abc", lines[0]);
}

void TEST_FILE_WITH_THREE_LINES_SEPARATED_BY_CR()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    {
        platformstl::FILE_stream stm(f.c_str(), "wb");

        stm.write("abc\rdef\rghi\r");
    }

    platformstl::file_lines lines(f.c_str());

    REQUIRE(TEST_INT_EQ(3u, lines.size()));
    TEST_MS_EQ("abc", lines[0]);
    TEST_MS_EQ("def", lines[1]);
    TEST_MS_EQ("ghi", lines[2]);
}

void TEST_FILE_WITH_CONSECUTIVE_CR_GIVES_EMPTY_LINE()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    {
        platformstl::FILE_stream stm(f.c_str(), "wb");

        stm.write("abc\r\rghi");
    }

    platformstl::file_lines lines(f.c_str());

    REQUIRE(TEST_INT_EQ(3u, lines.size()));
    TEST_MS_EQ("abc", lines[0]);
    TEST_MS_EQ("", lines[1]);
    TEST_MS_EQ("ghi", lines[2]);
}

void TEST_FILE_CONTAINING_NUL_CHARACTER_THROWS()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    {
        char const                  contents[]  =   { 'a', 'b', 'c', '\0', 'd', 'e', 'f' };
        platformstl::FILE_stream    stm(f.c_str(), "wb");

        stm.write_binary(contents, sizeof(contents));
    }

    platformstl::file_lines lines(f.c_str());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

