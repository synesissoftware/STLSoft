/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.exception.variant_type_exception/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::variant_type_exception`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/exception/variant_type_exception.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_status_code(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.exception.variant_type_exception", verbosity))
    {
        XTESTS_RUN_CASE(test_status_code);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_status_code(void)
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    comstl::variant_type_exception  x("bad variant", DISP_E_BADVARTYPE);

    TEST_INT_EQ((int)DISP_E_BADVARTYPE, (int)x.status_code());
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
