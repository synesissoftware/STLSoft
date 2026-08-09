/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.winstl.filesystem.path/entry.cpp
 *
 * Purpose: Component-tests for `filesystem/path`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/filesystem/path.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_join(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.winstl.filesystem.path", verbosity))
    {
        XTESTS_RUN_CASE(test_join);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_join(void)
{
    winstl::path p("C:/temp");
    p.push("file.txt");
    TEST_MS_EQ("C:/temp/file.txt", stlsoft::c_str_ptr_a(p));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
