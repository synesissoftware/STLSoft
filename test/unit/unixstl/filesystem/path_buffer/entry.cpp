/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/unixstl/filesystem/path_buffer/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/path_buffer.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/filesystem/path_buffer.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_DEFAULT_CONSTRUCTED_EMPTY();
    static void TEST_ASSIGN_AND_CLEAR();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_DEFAULT_CONSTRUCTED_EMPTY);
        XTESTS_RUN_CASE(TEST_ASSIGN_AND_CLEAR);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_DEFAULT_CONSTRUCTED_EMPTY()
{
    unixstl::path_buffer_a buf;

    TEST_INT_EQ(0, buf.size());
    TEST_MS_EQ("", buf.c_str());
}

static void TEST_ASSIGN_AND_CLEAR()
{
    unixstl::path_buffer_a buf;

    buf.assign("hello/world", ::strlen("hello/world"));
    TEST_MS_EQ("hello/world", buf.c_str());

    buf.assign("", 0);
    TEST_INT_EQ(0, buf.size());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
