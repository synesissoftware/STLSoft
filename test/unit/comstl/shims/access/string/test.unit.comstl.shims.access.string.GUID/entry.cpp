/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.shims.access.string.GUID/entry.cpp
 *
 * Purpose: Unit-tests for GUID string access shims.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/shims/access/string/GUID.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stlsoft/shims/access/string.hpp>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_c_str_ptr_known_guid(void);
    static void test_c_str_len(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.shims.access.string.GUID", verbosity))
    {
        XTESTS_RUN_CASE(test_c_str_ptr_known_guid);
        XTESTS_RUN_CASE(test_c_str_len);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_c_str_ptr_known_guid(void)
{
    cs_char_a_t const*  s = stlsoft::c_str_ptr_a(IID_IUnknown);

    TEST_PTR_NE(NULL, s);
    TEST_UINT_NE(0u, strlen(s));
}

static void test_c_str_len(void)
{
    TEST_UINT_EQ(stlsoft::c_str_len_a(IID_IUnknown), stlsoft::c_str_len(IID_IUnknown));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
