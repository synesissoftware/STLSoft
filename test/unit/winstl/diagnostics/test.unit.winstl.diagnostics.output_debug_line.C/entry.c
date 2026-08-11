/* /////////////////////////////////////////////////////////////////////////
 * File:        test.unit.winstl.diagnostics.output_debug_line.C/entry.c
 *
 * Purpose: Unit test for `winstl_C_diagnostics_output_debug_line_1_m()`, etc.
 *
 * Created: 22nd November 2011
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

static void winstl_C_call_OutputDebugStringA_(char const* s);
#define WINSTL_DIAGNOSTICS_OUTPUT_DEBUG_LINE_SUPPRESS_ODS_
#include <winstl/diagnostics/output_debug_line.h>

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* cstring header files */
#include <cstring/cstring.h>

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void test_1_0(void);
static void test_1_1(void);
static void test_1_2(void);
static void test_1_3(void);
static void test_1_5(void);
static void test_1_6(void);
static void test_1_7(void);
static void test_1_8(void);
static void test_1_9(void);
static void test_1_10(void);
static void test_1_11(void);

static int setup(void* param);
static int teardown(void* param);
static cstring_t string = cstring_t_DEFAULT;
static void* setupParam = &string;


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.unit.winstl.diagnostics.C.output_debug_line", verbosity, setup, teardown, setupParam))
    {
        XTESTS_RUN_CASE(test_1_0);
        XTESTS_RUN_CASE(test_1_1);
        XTESTS_RUN_CASE(test_1_2);
        XTESTS_RUN_CASE(test_1_3);
        XTESTS_RUN_CASE(test_1_5);
        XTESTS_RUN_CASE(test_1_6);
        XTESTS_RUN_CASE(test_1_7);
        XTESTS_RUN_CASE(test_1_8);
        XTESTS_RUN_CASE(test_1_9);
        XTESTS_RUN_CASE(test_1_10);
        XTESTS_RUN_CASE(test_1_11);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void winstl_C_call_OutputDebugStringA_(char const* s)
{
    CSTRING_RC rc = cstring_append(&string, s);

    if (CSTRING_RC_SUCCESS != rc)
    {
        fprintf(stderr, "CSTRING append failed: %s (%d)\n", cstring_getStatusCodeString(rc), rc);
        exit(EXIT_XTESTS_FAILURE);
    }
}

static int setup(void* param)
{
    STLSOFT_SUPPRESS_UNUSED(param);

    return CSTRING_RC_SUCCESS != cstring_init(&string);
}

static int teardown(void* param)
{
    STLSOFT_SUPPRESS_UNUSED(param);

    cstring_destroy(&string);

    return 0; /* Currently ignored by xTests */
}


static void test_1_0()
{
    winstl_C_diagnostics_output_debug_line_1_m(NULL);

    TEST_INT_EQ(1u, string.len);
    TEST_MS_EQ("\n", string.ptr);
}

static void test_1_1()
{
    winstl_C_diagnostics_output_debug_line_1_m("");

    TEST_INT_EQ(1u, string.len);
    TEST_MS_EQ("\n", string.ptr);
}

static void test_1_2()
{
    winstl_C_diagnostics_output_debug_line_1_m("abc");

    TEST_INT_EQ(4u, string.len);
    TEST_MS_EQ("abc\n", string.ptr);
}

static void test_1_3()
{
    { size_t i; for (i = 1; i != 10000000; i *= 10)
    {
        char* s = malloc(i + 1);

        if (NULL != s)
        {
            memset(s, '~', i);
            s[i] = '\0';

            winstl_C_diagnostics_output_debug_line_1_m(s);

            TEST_INT_EQ(i + 1, string.len);
            TEST_MS_EQ_N(s, string.ptr, i);
            TEST_CHAR_EQ('\n', string.ptr[i]);

            free(s);

            cstring_truncate(&string, 0u);
        }
    }}
}

static void test_1_5()
{
    winstl_C_diagnostics_output_debug_line_2_m(NULL, NULL);

    TEST_INT_EQ(1u, string.len);
    TEST_MS_EQ("\n", string.ptr);
}

static void test_1_6()
{
    winstl_C_diagnostics_output_debug_line_2_m("", NULL);

    TEST_INT_EQ(1u, string.len);
    TEST_MS_EQ("\n", string.ptr);
}

static void test_1_7()
{
    winstl_C_diagnostics_output_debug_line_2_m(NULL, "");

    TEST_INT_EQ(1u, string.len);
    TEST_MS_EQ("\n", string.ptr);
}

static void test_1_8()
{
    winstl_C_diagnostics_output_debug_line_2_m("", "");

    TEST_INT_EQ(1u, string.len);
    TEST_MS_EQ("\n", string.ptr);
}

static void test_1_9()
{
    winstl_C_diagnostics_output_debug_line_2_m("abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    TEST_INT_EQ(53u, string.len);
    TEST_MS_EQ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\n", string.ptr);
}

static void test_1_10()
{
    winstl_C_diagnostics_output_debug_line_2_m("abcdefghijklm", "nopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

    TEST_INT_EQ(53u, string.len);
    TEST_MS_EQ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\n", string.ptr);
}

static void test_1_11()
{
    { size_t i; for (i = 1; i != 10000000; i *= 10)
    {
        char* s = malloc(i + 1);

        if (NULL != s)
        {
            memset(s, '~', i);
            s[i] = '\0';

            winstl_C_diagnostics_output_debug_line_2_m(s, s);

            TEST_INT_EQ(2 * i + 1, string.len);
            TEST_MS_EQ_N(s, string.ptr + 0, i);
            TEST_MS_EQ_N(s, string.ptr + i, i);
            TEST_CHAR_EQ('\n', string.ptr[2 * i]);

            free(s);

            cstring_truncate(&string, 0u);
        }
    }}
}


/* ///////////////////////////// end of file //////////////////////////// */

