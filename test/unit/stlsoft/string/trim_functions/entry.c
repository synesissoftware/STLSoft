/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.string.trim_functions/entry.c
 *
 * Purpose: Unit-tests for the C string trimming functions.
 *
 * Created: 10th August 2026
 * Updated: 20th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/trim_functions.h>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <xtests/terse-api.h>
#include <xtests/xtests.h>

#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_empty_slice(void);
static void TEST_default_left(void);
static void TEST_default_right(void);
static void TEST_default_all(void);
static void TEST_default_whitespace_characters(void);
static void TEST_all_default_whitespace(void);
static void TEST_no_default_whitespace(void);
static void TEST_custom_left(void);
static void TEST_custom_right(void);
static void TEST_custom_all(void);
static void TEST_custom_empty_set(void);
static void TEST_bounded_slice(void);
static void TEST_empty_result(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.trim_functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_empty_slice);
        XTESTS_RUN_CASE(TEST_default_left);
        XTESTS_RUN_CASE(TEST_default_right);
        XTESTS_RUN_CASE(TEST_default_all);
        XTESTS_RUN_CASE(TEST_default_whitespace_characters);
        XTESTS_RUN_CASE(TEST_all_default_whitespace);
        XTESTS_RUN_CASE(TEST_no_default_whitespace);
        XTESTS_RUN_CASE(TEST_custom_left);
        XTESTS_RUN_CASE(TEST_custom_right);
        XTESTS_RUN_CASE(TEST_custom_all);
        XTESTS_RUN_CASE(TEST_custom_empty_set);
        XTESTS_RUN_CASE(TEST_bounded_slice);
        XTESTS_RUN_CASE(TEST_empty_result);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static stlsoft_C_string_slice_m_t make_slice(char const* s)
{
    stlsoft_C_string_slice_m_t result;

    result.len = (NULL == s) ? 0 : strlen(s);
    result.ptr = s;

    return result;
}

static stlsoft_C_string_slice_m_t make_slice_n(char const* s, size_t n)
{
    stlsoft_C_string_slice_m_t result;

    result.len = n;
    result.ptr = s;

    return result;
}

static void TEST_empty_slice(void)
{
    stlsoft_C_string_slice_m_t slice;
    stlsoft_C_string_slice_m_t result;

    slice.len = 0;
    slice.ptr = NULL;

    result = STLSoft_C_string_trim_left_a(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NULL(result.ptr);

    result = STLSoft_C_string_trim_right_a(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NULL(result.ptr);

    result = STLSoft_C_string_trim_all_a(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NULL(result.ptr);
}

static void TEST_default_left(void)
{
    char const input[] = "\n\r\t\v  value  ";
    stlsoft_C_string_slice_m_t result =
        STLSoft_C_string_trim_left_a(make_slice(input));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input + 6, result.ptr);
    TEST_MS_EQ_N("value  ", result.ptr, result.len);
}

static void TEST_default_right(void)
{
    char const input[] = "  value\n\r\t\v ";
    stlsoft_C_string_slice_m_t result =
        STLSoft_C_string_trim_right_a(make_slice(input));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_MS_EQ_N("  value", result.ptr, result.len);
}

static void TEST_default_all(void)
{
    char const input[] = "\n\r\t\v  value  \v\t\r\n";
    stlsoft_C_string_slice_m_t result =
        STLSoft_C_string_trim_all_a(make_slice(input));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input + 6, result.ptr);
    TEST_MS_EQ_N("value", result.ptr, result.len);
}

static void TEST_default_whitespace_characters(void)
{
    char const whitespace[] = " \n\r\t\v";
    size_t i;

    for (i = 0; i != sizeof(whitespace) - 1; ++i)
    {
        char input[4];
        stlsoft_C_string_slice_m_t result;

        input[0] = whitespace[i];
        input[1] = 'x';
        input[2] = whitespace[i];
        input[3] = '\0';

        result = STLSoft_C_string_trim_left_a(make_slice_n(input, 3));
        TEST_INT_EQ(2u, result.len);
        TEST_PTR_EQ(input + 1, result.ptr);
        TEST_CHAR_EQ('x', result.ptr[0]);

        result = STLSoft_C_string_trim_right_a(make_slice_n(input, 3));
        TEST_INT_EQ(2u, result.len);
        TEST_PTR_EQ(input, result.ptr);
        TEST_CHAR_EQ('x', result.ptr[1]);
    }
}

static void TEST_all_default_whitespace(void)
{
    char const input[] = " \n\r\t\v";
    stlsoft_C_string_slice_m_t result =
        STLSoft_C_string_trim_all_a(make_slice_n(input, sizeof(input) - 1));

    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NULL(result.ptr);
}

static void TEST_no_default_whitespace(void)
{
    char const input[] = "value";
    stlsoft_C_string_slice_m_t result =
        STLSoft_C_string_trim_all_a(make_slice(input));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_MS_EQ_N(input, result.ptr, result.len);
}

static void TEST_custom_left(void)
{
    char const input[] = ",;:value  ";
    char const chars[] = ",;:";
    stlsoft_C_string_slice_m_t result =
        STLSoft_C_string_trim_left_chars_a(
            make_slice(input)
        ,   make_slice(chars));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input + 3, result.ptr);
    TEST_MS_EQ_N("value  ", result.ptr, result.len);
}

static void TEST_custom_right(void)
{
    char const input[] = "  value,;:";
    char const chars[] = ",;:";
    stlsoft_C_string_slice_m_t result =
        STLSoft_C_string_trim_right_chars_a(
            make_slice(input)
        ,   make_slice(chars));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_MS_EQ_N("  value", result.ptr, result.len);
}

static void TEST_custom_all(void)
{
    char const input[] = ",;:value:;,";
    char const chars[] = ",;:";
    stlsoft_C_string_slice_m_t result =
        STLSoft_C_string_trim_all_chars_a(
            make_slice(input)
        ,   make_slice(chars));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input + 3, result.ptr);
    TEST_MS_EQ_N("value", result.ptr, result.len);
}

static void TEST_custom_empty_set(void)
{
    char const input[] = "  value  ";
    stlsoft_C_string_slice_m_t chars;
    stlsoft_C_string_slice_m_t result;

    chars.len = 0;
    chars.ptr = NULL;

    result = STLSoft_C_string_trim_all_chars_a(make_slice(input), chars);

    TEST_INT_EQ(9u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_MS_EQ_N(input, result.ptr, result.len);
}

static void TEST_bounded_slice(void)
{
    char const input[] = "  value  suffix";
    stlsoft_C_string_slice_m_t result =
        STLSoft_C_string_trim_all_a(make_slice_n(input, 9));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input + 2, result.ptr);
    TEST_MS_EQ_N("value", result.ptr, result.len);
}

static void TEST_empty_result(void)
{
    char const input[] = " \t\n";
    stlsoft_C_string_slice_m_t const slice = make_slice(input);
    stlsoft_C_string_slice_m_t result;

    result = STLSoft_C_string_trim_left_a(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NULL(result.ptr);

    result = STLSoft_C_string_trim_right_a(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NULL(result.ptr);

    result = STLSoft_C_string_trim_all_a(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NULL(result.ptr);
}


/* ///////////////////////////// end of file //////////////////////////// */
