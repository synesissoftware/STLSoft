/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/stlsoft/filesystem/io_functions/entry.cpp
 *
 * Purpose: Component-tests for `stlsoft/filesystem/io_functions`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/filesystem/io_functions.hpp>
#include <stdio.h>
#include <string>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_IO_FUNCTIONS_ROUNDTRIP();
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
        XTESTS_RUN_CASE(TEST_IO_FUNCTIONS_ROUNDTRIP);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_IO_FUNCTIONS_ROUNDTRIP()
{
    char const* path = "test_stlsoft_io.tmp";
#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif
    FILE* fp = fopen(path, "w");
    TEST_PTR_NE(NULL, fp);
    stlsoft::write_string(fp, "line1\n", 6);
    fclose(fp);
    fp = fopen(path, "r");
    std::string line;
    stlsoft::read_line(fp, line);
    fclose(fp);
#if defined(_MSC_VER)
# pragma warning(pop)
#endif
    remove(path);
    TEST_MS_EQ("line1", line);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
