/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.iterator.FILE_iterator/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::FILE_iterator`.
 *
 * Created: 24th March 2025
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

 #include <platformstl/filesystem/file_lines.hpp>
#include <platformstl/filesystem/FILE_stream.hpp>
#include <stlsoft/iterator/FILE_iterator.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>
#include <stlsoft/stlsoft.h>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>

/* STLSoft header files */
#include <platformstl/filesystem/FILE_stream.hpp>
#include <platformstl/filesystem/file_lines.hpp>

/* Standard C++ header files */
#include <algorithm>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_1();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.FILE_stream", verbosity))
    {
        XTESTS_RUN_CASE(test_1);


        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

namespace stlsoft {

} // namespace stlsoft


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::FILE_iterator;

    using ::xtests::cpp::util::temp_file;


static void test_1()
{
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen);

    char const* const strings[] =
    {
        "abc"
    ,   ""
    ,   "jklmnopqrstuvwxyz"
    };


    {
        platformstl::FILE_stream    stm(f.c_str(), "w");

        std::copy(
#if __cplusplus >= 201103L
            std::begin(strings), std::end(strings)
#else
            &strings[0], &strings[0] + STLSOFT_NUM_ELEMENTS(strings)
#endif
        ,   FILE_iterator<char const*>(stlsoft::get_FILE_ptr(stm), "%s\n")
        );
    }

    {
        platformstl::file_lines     lines(f.c_str());

        XTESTS_REQUIRE(TEST_INT_EQ(3u, lines.size()));
        TEST_MS_EQ_N("abc", lines[0], lines[0].size());
        TEST_MS_EQ_N("", lines[1], lines[1].size());
        TEST_MS_EQ_N("jklmnopqrstuvwxyz", lines[2], lines[2].size());
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

