/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.filesystem.functionals/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/filesystem/functionals.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/filesystem/functionals.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_path_compare_equal(void);
    static void test_path_compare_rooted(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.functionals", verbosity))
    {
        XTESTS_RUN_CASE(test_path_compare_equal);
        XTESTS_RUN_CASE(test_path_compare_rooted);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

typedef unixstl::path_compare<char> path_compare_t;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_path_compare_equal()
{
    path_compare_t cmp;

    TEST_BOOLEAN_TRUE(cmp("a/b", "a/b"));
    TEST_BOOLEAN_FALSE(cmp("a/b", "a/c"));
}

static void test_path_compare_rooted()
{
    path_compare_t cmp;

    TEST_BOOLEAN_TRUE(cmp("/usr/bin", "/usr/bin"));
    TEST_BOOLEAN_FALSE(cmp("/usr/bin", "/usr/lib"));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
