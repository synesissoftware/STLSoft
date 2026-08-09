/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.stlsoft.filesystem.path_buffer/entry.cpp
 *
 * Purpose: Component-tests for `stlsoft/filesystem/path_buffer`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/filesystem/path_buffer.hpp>
#include <stdio.h>
#include <string>
#include <string>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_path_buffer_assign(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.stlsoft.filesystem.path_buffer", verbosity))
    {
        XTESTS_RUN_CASE(test_path_buffer_assign);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_path_buffer_assign()
{
    stlsoft::basic_path_buffer<char, std::allocator<char>, 64> pb;
    pb.assign("a/b", 3);
    TEST_MS_EQ("a/b", pb.c_str());
    TEST_INTEGER_EQUAL(3, static_cast<int>(pb.size()));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
