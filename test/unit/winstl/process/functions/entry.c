/* /////////////////////////////////////////////////////////////////////////
 * File:    functions/entry.c
 *
 * Purpose: Unit-tests for `winstl_C_get_current_process_id()`.
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

#include <winstl/process/functions.h>

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

#include <process.h>
#include <windows.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_EQUALS_GETPID(void);
static void TEST_EQUALS_CURRENT_PROCESS_ID(void);
static void TEST_IS_POSITIVE(void);
static void TEST_IS_STABLE(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.process.functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_EQUALS_GETPID);
        XTESTS_RUN_CASE(TEST_EQUALS_CURRENT_PROCESS_ID);
        XTESTS_RUN_CASE(TEST_IS_POSITIVE);
        XTESTS_RUN_CASE(TEST_IS_STABLE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_EQUALS_GETPID(void)
{
    int const expected = _getpid();
    int const actual = winstl_C_get_current_process_id();

    TEST_INT_EQ(expected, actual);
}

static void TEST_EQUALS_CURRENT_PROCESS_ID(void)
{
    int const expected = STLSOFT_STATIC_CAST(int, GetCurrentProcessId());
    int const actual = winstl_C_get_current_process_id();

    TEST_INT_EQ(expected, actual);
}

static void TEST_IS_POSITIVE(void)
{
    int const result = winstl_C_get_current_process_id();

    TEST_INT_GT(0, result);
}

static void TEST_IS_STABLE(void)
{
    int const first = winstl_C_get_current_process_id();
    int const second = winstl_C_get_current_process_id();

    TEST_INT_EQ(first, second);
}


/* ///////////////////////////// end of file //////////////////////////// */

