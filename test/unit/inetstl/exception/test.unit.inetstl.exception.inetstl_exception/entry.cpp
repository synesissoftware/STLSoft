/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.inetstl.exception.inetstl_exception/entry.cpp
 *
 * Purpose: Unit-tests for `inetstl::inetstl_exception`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <inetstl/exception/inetstl_exception.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/diagnostics/ProjectIdentifier.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_status_code_only(void);
    static void TEST_reason_and_status_code(void);
    static void TEST_reason_and_qualifier(void);
    static void TEST_project_identifier(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.inetstl.exception.inetstl_exception", verbosity))
    {
        XTESTS_RUN_CASE(TEST_status_code_only);
        XTESTS_RUN_CASE(TEST_reason_and_status_code);
        XTESTS_RUN_CASE(TEST_reason_and_qualifier);
        XTESTS_RUN_CASE(TEST_project_identifier);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_status_code_only()
{
#if defined(INETSTL_OS_IS_UNIX)

    inetstl::inetstl_exception x(EINVAL);

    TEST_INT_EQ(EINVAL, x.status_code());
    TEST_PTR_NE(NULL, x.what());
    TEST_CHAR_NE('\0', x.what()[0]);
#elif defined(INETSTL_OS_IS_WINDOWS)

    inetstl::inetstl_exception x(ERROR_FILE_NOT_FOUND);

    TEST_INT_EQ(ERROR_FILE_NOT_FOUND, x.status_code());
    TEST_PTR_NE(NULL, x.what());
    TEST_CHAR_NE('\0', x.what()[0]);
#else /* ? platform */

# error Platform not discriminated
#endif /* platform */
}

static void TEST_reason_and_status_code()
{
#if defined(INETSTL_OS_IS_UNIX)

    inetstl::inetstl_exception x("test reason", ENOENT);

    TEST_INT_EQ(ENOENT, x.status_code());
    TEST_PTR_NE(NULL, x.what());
    TEST_PTR_NE(NULL, strstr(x.what(), "test reason"));
#elif defined(INETSTL_OS_IS_WINDOWS)

    inetstl::inetstl_exception x("test reason", ERROR_ACCESS_DENIED);

    TEST_INT_EQ(ERROR_ACCESS_DENIED, x.status_code());
    TEST_PTR_NE(NULL, x.what());
    TEST_PTR_NE(NULL, strstr(x.what(), "test reason"));
#else /* ? platform */

# error Platform not discriminated
#endif /* platform */
}

static void TEST_reason_and_qualifier()
{
    inetstl::inetstl_exception x("test reason", "test qualifier");

    TEST_PTR_NE(NULL, x.what());
    TEST_PTR_NE(NULL, strstr(x.what(), "test reason"));
    TEST_PTR_NE(NULL, strstr(x.what(), "test qualifier"));
}

static void TEST_project_identifier()
{
#if defined(INETSTL_OS_IS_UNIX)

    inetstl::inetstl_exception x(EINVAL);
#elif defined(INETSTL_OS_IS_WINDOWS)

    inetstl::inetstl_exception x(ERROR_FILE_NOT_FOUND);
#else /* ? platform */

# error Platform not discriminated
#endif /* platform */

    TEST_BOOLEAN_TRUE(stlsoft::STLSoftProjectIdentifier_InetSTL == x.project_identifier());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
