/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/unixstl/process/functions/entry.c
 *
 * Purpose: Unit-tests for `unixstl_C_get_current_process_id()` and
 *          `unixstl_C_get_current_process_path_m()`.
 *
 * Created: 8th October 2026
 * Updated: 2nd November 2026
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

#include <unixstl/process/functions.h>

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
#include <string.h>

#if defined(_WIN32) && \
    (   defined(STLSOFT_COMPILER_IS_MSVC) || \
        defined(STLSOFT_COMPILER_IS_INTEL))
# include <process.h>
#else
# include <sys/types.h>
# include <unistd.h>
#endif


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_EQUALS_NATIVE_PROCESS_ID(void);
static void TEST_IS_POSITIVE(void);
static void TEST_IS_STABLE(void);
static void TEST_PATH_ZERO_CAPACITY_REPORTS_DEMAND(void);
static void TEST_PATH_EXACT_CAPACITY_COPIES_FULL_PATH(void);
static void TEST_PATH_ONE_CHARACTER_WRITES_ONLY_NUL(void);
static void TEST_PATH_SHORT_BUFFER_COPIES_PREFIX(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.process.functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_EQUALS_NATIVE_PROCESS_ID);
        XTESTS_RUN_CASE(TEST_IS_POSITIVE);
        XTESTS_RUN_CASE(TEST_IS_STABLE);
        XTESTS_RUN_CASE(TEST_PATH_ZERO_CAPACITY_REPORTS_DEMAND);
        XTESTS_RUN_CASE(TEST_PATH_EXACT_CAPACITY_COPIES_FULL_PATH);
        XTESTS_RUN_CASE(TEST_PATH_ONE_CHARACTER_WRITES_ONLY_NUL);
        XTESTS_RUN_CASE(TEST_PATH_SHORT_BUFFER_COPIES_PREFIX);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void TEST_EQUALS_NATIVE_PROCESS_ID(void)
{
    int expected;
    int actual;

#if 0
#elif defined(_WIN32) && \
      ( 0 ||\
        defined(STLSOFT_COMPILER_IS_MSVC) ||\
        defined(STLSOFT_COMPILER_IS_INTEL) ||\
        0)

    expected = _getpid();
#else

    expected = STLSOFT_STATIC_CAST(int, getpid());
#endif

    actual = unixstl_C_get_current_process_id();

    TEST_INT_EQ(expected, actual);
}

static void TEST_IS_POSITIVE(void)
{
    int const result = unixstl_C_get_current_process_id();

    TEST_INT_GT(0, result);
}

static void TEST_IS_STABLE(void)
{
    int const first = unixstl_C_get_current_process_id();
    int const second = unixstl_C_get_current_process_id();

    TEST_INT_EQ(first, second);
}

static void TEST_PATH_ZERO_CAPACITY_REPORTS_DEMAND(void)
{
    us_size_t const demand = unixstl_C_get_current_process_path_m(NULL, 0);

    TEST_INT_GT(1, STLSOFT_STATIC_CAST(int, demand));
}

static void TEST_PATH_EXACT_CAPACITY_COPIES_FULL_PATH(void)
{
    us_size_t const demand = unixstl_C_get_current_process_path_m(NULL, 0);
    us_char_a_t*    buff;
    us_size_t       written;

    TEST_INT_GT(1, STLSOFT_STATIC_CAST(int, demand));

    if (demand < 2)
    {
        return;
    }

    buff = STLSOFT_STATIC_CAST(us_char_a_t*, malloc(demand));

    if (NULL == buff)
    {
        TEST_FAIL("malloc failed");

        return;
    }

    memset(buff, 'X', demand);

    written = unixstl_C_get_current_process_path_m(buff, demand);

    TEST_INT_EQ(STLSOFT_STATIC_CAST(int, demand - 1), STLSOFT_STATIC_CAST(int, written));
    TEST_INT_EQ(0, STLSOFT_STATIC_CAST(int, buff[written]));
    TEST_INT_EQ(STLSOFT_STATIC_CAST(int, written), STLSOFT_STATIC_CAST(int, strlen(buff)));

    free(buff);
}

static void TEST_PATH_ONE_CHARACTER_WRITES_ONLY_NUL(void)
{
    us_size_t const demand = unixstl_C_get_current_process_path_m(NULL, 0);
    us_char_a_t     buff[1];
    us_size_t       written;

    TEST_INT_GT(1, STLSOFT_STATIC_CAST(int, demand));

    if (demand < 2)
    {
        return;
    }

    buff[0] = 'Z';

    written = unixstl_C_get_current_process_path_m(buff, 1);

    TEST_INT_EQ(STLSOFT_STATIC_CAST(int, demand), STLSOFT_STATIC_CAST(int, written));
    TEST_INT_EQ(0, STLSOFT_STATIC_CAST(int, buff[0]));
}

static void TEST_PATH_SHORT_BUFFER_COPIES_PREFIX(void)
{
    us_size_t const demand = unixstl_C_get_current_process_path_m(NULL, 0);
    us_char_a_t*    full;
    us_char_a_t     trunc[3];
    us_size_t       full_len;
    us_size_t       written;

    TEST_INT_GT(2, STLSOFT_STATIC_CAST(int, demand));

    if (demand < 3)
    {
        return;
    }

    full = STLSOFT_STATIC_CAST(us_char_a_t*, malloc(demand));

    if (NULL == full)
    {
        TEST_FAIL("malloc failed");

        return;
    }

    full_len = unixstl_C_get_current_process_path_m(full, demand);

    TEST_INT_GT(1, STLSOFT_STATIC_CAST(int, full_len));

    trunc[0] = 'A';
    trunc[1] = 'B';
    trunc[2] = 'C';

    written = unixstl_C_get_current_process_path_m(trunc, 2);

    TEST_INT_EQ(STLSOFT_STATIC_CAST(int, full_len + 1), STLSOFT_STATIC_CAST(int, written));
    TEST_INT_EQ(STLSOFT_STATIC_CAST(int, full[0]), STLSOFT_STATIC_CAST(int, trunc[0]));
    TEST_INT_EQ(0, STLSOFT_STATIC_CAST(int, trunc[1]));
    TEST_INT_EQ(STLSOFT_STATIC_CAST(int, 'C'), STLSOFT_STATIC_CAST(int, trunc[2]));

    free(full);
}


/* ///////////////////////////// end of file //////////////////////////// */

