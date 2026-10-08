/* /////////////////////////////////////////////////////////////////////////
 * File:    functions/entry.c
 *
 * Purpose: Unit-tests for `platformstl_C_get_current_process_id()`.
 *
 * Created: 8th October 2026
 * Updated: 8th October 2026
 *
 * Copyright (c) 2026, Matthew Wilson and Synesis Information Systems
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <platformstl/process/functions.h>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_EQUALS_SELECTED_PLATFORM_FUNCTION(void);
static void TEST_IS_POSITIVE(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.platformstl.process.functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_EQUALS_SELECTED_PLATFORM_FUNCTION);
        XTESTS_RUN_CASE(TEST_IS_POSITIVE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_EQUALS_SELECTED_PLATFORM_FUNCTION(void)
{
    int expected;
    int actual;

#if defined(PLATFORMSTL_OS_IS_UNIX)

    expected = unixstl_C_get_current_process_id();
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    expected = winstl_C_get_current_process_id();
#else

# error Platform not discriminated
#endif

    actual = platformstl_C_get_current_process_id();

    TEST_INT_EQ(expected, actual);
}

static void TEST_IS_POSITIVE(void)
{
    int const result = platformstl_C_get_current_process_id();

    TEST_INT_GT(0, result);
}


/* ///////////////////////////// end of file //////////////////////////// */

