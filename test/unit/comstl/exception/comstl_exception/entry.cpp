/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/exception/comstl_exception/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::comstl_exception`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/exception/comstl_exception.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_status_code();
    static void TEST_MESSAGE();
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
        XTESTS_RUN_CASE(TEST_status_code);
        XTESTS_RUN_CASE(TEST_MESSAGE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_status_code()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    comstl::comstl_exception  x(E_ACCESSDENIED);

    TEST_INT_EQ((int)E_ACCESSDENIED, (int)x.status_code());
#else /* ? STLSOFT_CF_EXCEPTION_SUPPORT */
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
}

static void TEST_MESSAGE()
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    comstl::comstl_exception  x("reason", E_FAIL);

    TEST_PTR_NE(NULL, x.what());
#else /* ? STLSOFT_CF_EXCEPTION_SUPPORT */
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
