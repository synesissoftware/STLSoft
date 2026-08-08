/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.exception.comstl_exception/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::comstl_exception`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/exception/comstl_exception.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_status_code(void);
static void test_message(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.exception.comstl_exception", verbosity))
    {
        XTESTS_RUN_CASE(test_status_code);
        XTESTS_RUN_CASE(test_message);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_status_code(void)
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    comstl::comstl_exception  x(E_ACCESSDENIED);

    TEST_INT_EQ((int)E_ACCESSDENIED, (int)x.status_code());
#else /* ? STLSOFT_CF_EXCEPTION_SUPPORT */
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
}

static void test_message(void)
{
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT
    comstl::comstl_exception  x("reason", E_FAIL);

    TEST_PTR_NE(NULL, x.what());
#else /* ? STLSOFT_CF_EXCEPTION_SUPPORT */
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
