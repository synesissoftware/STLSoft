/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.shims.access.string.dirent/entry.cpp
 *
 * Purpose: Unit-tests for UnixSTL `unixstl/shims/access/string/dirent.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/shims/access/string/dirent.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <dirent.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_c_str_data_null(void);
    static void test_c_str_ptr_with_name(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.shims.access.string.dirent", verbosity))
    {
        XTESTS_RUN_CASE(test_c_str_data_null);
        XTESTS_RUN_CASE(test_c_str_ptr_with_name);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_c_str_data_null()
{
    TEST_MS_EQ("", stlsoft::c_str_data_a(static_cast<struct dirent const*>(NULL)));
    TEST_MS_EQ("", stlsoft::c_str_data(static_cast<struct dirent const*>(NULL)));
}

static void test_c_str_ptr_with_name()
{
    struct dirent entry;
    strcpy(entry.d_name, "filename.ext");

    TEST_MS_EQ("filename.ext", stlsoft::c_str_ptr_a(&entry));
    TEST_INT_EQ(strlen("filename.ext"), stlsoft::c_str_len_a(&entry));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
