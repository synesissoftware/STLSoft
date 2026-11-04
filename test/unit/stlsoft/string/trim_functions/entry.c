/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/trim_functions/entry.c
 *
 * Purpose: Unit-tests for the C string trimming functions.
 *
 * Created: 10th August 2026
 * Updated: 4th November 2026
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
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_EMPTY_SLICE(void);
static void TEST_EMPTY_SLICE_w(void);
static void TEST_trim_left_m(void);
static void TEST_trim_left_w(void);
static void TEST_trim_right_m(void);
static void TEST_trim_right_w(void);
static void TEST_trim_all_m(void);
static void TEST_trim_all_w(void);
static void TEST_EACH_DEFAULT_WHITESPACE_CHARACTER(void);
static void TEST_EACH_DEFAULT_WHITESPACE_CHARACTER_w(void);
static void TEST_ALL_DEFAULT_WHITESPACE(void);
static void TEST_ALL_DEFAULT_WHITESPACE_w(void);
static void TEST_NO_DEFAULT_WHITESPACE(void);
static void TEST_NO_DEFAULT_WHITESPACE_w(void);
static void TEST_trim_left_chars_m(void);
static void TEST_trim_left_chars_w(void);
static void TEST_trim_right_chars_m(void);
static void TEST_trim_right_chars_w(void);
static void TEST_trim_all_chars_m(void);
static void TEST_trim_all_chars_w(void);
static void TEST_trim_all_chars_m_WITH_EMPTY_SET(void);
static void TEST_trim_all_chars_w_WITH_EMPTY_SET(void);
static void TEST_BOUNDED_SLICE(void);
static void TEST_BOUNDED_SLICE_w(void);
static void TEST_EMPTY_RESULT(void);
static void TEST_EMPTY_RESULT_w(void);


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
        XTESTS_RUN_CASE(TEST_EMPTY_SLICE);
        XTESTS_RUN_CASE(TEST_EMPTY_SLICE_w);
        XTESTS_RUN_CASE(TEST_trim_left_m);
        XTESTS_RUN_CASE(TEST_trim_left_w);
        XTESTS_RUN_CASE(TEST_trim_right_m);
        XTESTS_RUN_CASE(TEST_trim_right_w);
        XTESTS_RUN_CASE(TEST_trim_all_m);
        XTESTS_RUN_CASE(TEST_trim_all_w);
        XTESTS_RUN_CASE(TEST_EACH_DEFAULT_WHITESPACE_CHARACTER);
        XTESTS_RUN_CASE(TEST_EACH_DEFAULT_WHITESPACE_CHARACTER_w);
        XTESTS_RUN_CASE(TEST_ALL_DEFAULT_WHITESPACE);
        XTESTS_RUN_CASE(TEST_ALL_DEFAULT_WHITESPACE_w);
        XTESTS_RUN_CASE(TEST_NO_DEFAULT_WHITESPACE);
        XTESTS_RUN_CASE(TEST_NO_DEFAULT_WHITESPACE_w);
        XTESTS_RUN_CASE(TEST_trim_left_chars_m);
        XTESTS_RUN_CASE(TEST_trim_left_chars_w);
        XTESTS_RUN_CASE(TEST_trim_right_chars_m);
        XTESTS_RUN_CASE(TEST_trim_right_chars_w);
        XTESTS_RUN_CASE(TEST_trim_all_chars_m);
        XTESTS_RUN_CASE(TEST_trim_all_chars_w);
        XTESTS_RUN_CASE(TEST_trim_all_chars_m_WITH_EMPTY_SET);
        XTESTS_RUN_CASE(TEST_trim_all_chars_w_WITH_EMPTY_SET);
        XTESTS_RUN_CASE(TEST_BOUNDED_SLICE);
        XTESTS_RUN_CASE(TEST_BOUNDED_SLICE_w);
        XTESTS_RUN_CASE(TEST_EMPTY_RESULT);
        XTESTS_RUN_CASE(TEST_EMPTY_RESULT_w);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

static stlsoft_C_string_slice_m_t make_slice_m_(char const* s)
{
    stlsoft_C_string_slice_m_t result;

    result.len = (NULL == s) ? 0 : strlen(s);
    result.ptr = s;

    return result;
}

static stlsoft_C_string_slice_m_t make_slice_n_m_(char const* s, size_t n)
{
    stlsoft_C_string_slice_m_t result;

    result.len = n;
    result.ptr = s;

    return result;
}

static stlsoft_C_string_slice_w_t make_slice_w_(wchar_t const* s)
{
    stlsoft_C_string_slice_w_t result;

    result.len = (NULL == s) ? 0 : wcslen(s);
    result.ptr = s;

    return result;
}

static stlsoft_C_string_slice_w_t make_slice_n_w_(wchar_t const* s, size_t n)
{
    stlsoft_C_string_slice_w_t result;

    result.len = n;
    result.ptr = s;

    return result;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */


static void TEST_EMPTY_SLICE(void)
{
    stlsoft_C_string_slice_m_t slice;
    stlsoft_C_string_slice_m_t result;

    slice.len = 0;
    slice.ptr = NULL;

    result = stlsoft_C_string_trim_left_m(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_CHAR_EQ('\0', result.ptr[0]);

    result = stlsoft_C_string_trim_right_m(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_CHAR_EQ('\0', result.ptr[0]);

    result = stlsoft_C_string_trim_all_m(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_CHAR_EQ('\0', result.ptr[0]);
}

static void TEST_trim_left_m(void)
{
    char const input[] = "\n\r\t\v  value  ";
    stlsoft_C_string_slice_m_t result =
        stlsoft_C_string_trim_left_m(make_slice_m_(input));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input + 6, result.ptr);
    TEST_MS_EQ_N("value  ", result.ptr, result.len);
}

static void TEST_trim_right_m(void)
{
    char const input[] = "  value\n\r\t\v ";
    stlsoft_C_string_slice_m_t result =
        stlsoft_C_string_trim_right_m(make_slice_m_(input));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_MS_EQ_N("  value", result.ptr, result.len);
}

static void TEST_trim_all_m(void)
{
    char const input[] = "\n\r\t\v  value  \v\t\r\n";
    stlsoft_C_string_slice_m_t result =
        stlsoft_C_string_trim_all_m(make_slice_m_(input));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input + 6, result.ptr);
    TEST_MS_EQ_N("value", result.ptr, result.len);
}

static void TEST_EACH_DEFAULT_WHITESPACE_CHARACTER(void)
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

        result = stlsoft_C_string_trim_left_m(make_slice_n_m_(input, 3));
        TEST_INT_EQ(2u, result.len);
        TEST_PTR_EQ(input + 1, result.ptr);
        TEST_CHAR_EQ('x', result.ptr[0]);

        result = stlsoft_C_string_trim_right_m(make_slice_n_m_(input, 3));
        TEST_INT_EQ(2u, result.len);
        TEST_PTR_EQ(input, result.ptr);
        TEST_CHAR_EQ('x', result.ptr[1]);
    }
}

static void TEST_ALL_DEFAULT_WHITESPACE(void)
{
    char const input[] = " \n\r\t\v";
    stlsoft_C_string_slice_m_t result =
        stlsoft_C_string_trim_all_m(make_slice_n_m_(input, sizeof(input) - 1));

    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_CHAR_EQ('\0', result.ptr[0]);
}

static void TEST_NO_DEFAULT_WHITESPACE(void)
{
    char const input[] = "value";
    stlsoft_C_string_slice_m_t result =
        stlsoft_C_string_trim_all_m(make_slice_m_(input));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_MS_EQ_N(input, result.ptr, result.len);
}

static void TEST_trim_left_chars_m(void)
{
    char const input[] = ",;:value  ";
    char const chars[] = ",;:";
    stlsoft_C_string_slice_m_t result =
        stlsoft_C_string_trim_left_chars_m(
            make_slice_m_(input)
        ,   make_slice_m_(chars));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input + 3, result.ptr);
    TEST_MS_EQ_N("value  ", result.ptr, result.len);
}

static void TEST_trim_right_chars_m(void)
{
    char const input[] = "  value,;:";
    char const chars[] = ",;:";
    stlsoft_C_string_slice_m_t result =
        stlsoft_C_string_trim_right_chars_m(
            make_slice_m_(input)
        ,   make_slice_m_(chars));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_MS_EQ_N("  value", result.ptr, result.len);
}

static void TEST_trim_all_chars_m(void)
{
    char const input[] = ",;:value:;,";
    char const chars[] = ",;:";
    stlsoft_C_string_slice_m_t result =
        stlsoft_C_string_trim_all_chars_m(
            make_slice_m_(input)
        ,   make_slice_m_(chars));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input + 3, result.ptr);
    TEST_MS_EQ_N("value", result.ptr, result.len);
}

static void TEST_trim_all_chars_m_WITH_EMPTY_SET(void)
{
    char const input[] = "  value  ";
    stlsoft_C_string_slice_m_t chars;
    stlsoft_C_string_slice_m_t result;

    chars.len = 0;
    chars.ptr = NULL;

    result = stlsoft_C_string_trim_all_chars_m(make_slice_m_(input), chars);

    TEST_INT_EQ(9u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_MS_EQ_N(input, result.ptr, result.len);
}

static void TEST_BOUNDED_SLICE(void)
{
    char const input[] = "  value  suffix";
    stlsoft_C_string_slice_m_t result =
        stlsoft_C_string_trim_all_m(make_slice_n_m_(input, 9));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input + 2, result.ptr);
    TEST_MS_EQ_N("value", result.ptr, result.len);
}

static void TEST_EMPTY_RESULT(void)
{
    char const input[] = " \t\n";
    stlsoft_C_string_slice_m_t const slice = make_slice_m_(input);
    stlsoft_C_string_slice_m_t result;

    result = stlsoft_C_string_trim_left_m(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_CHAR_EQ('\0', result.ptr[0]);

    result = stlsoft_C_string_trim_right_m(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_CHAR_EQ('\0', result.ptr[0]);

    result = stlsoft_C_string_trim_all_m(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_CHAR_EQ('\0', result.ptr[0]);
}

static void TEST_EMPTY_SLICE_w(void)
{
    stlsoft_C_string_slice_w_t slice;
    stlsoft_C_string_slice_w_t result;

    slice.len = 0;
    slice.ptr = NULL;

    result = stlsoft_C_string_trim_left_w(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_INT_EQ(L'\0', result.ptr[0]);

    result = stlsoft_C_string_trim_right_w(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_INT_EQ(L'\0', result.ptr[0]);

    result = stlsoft_C_string_trim_all_w(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_INT_EQ(L'\0', result.ptr[0]);
}

static void TEST_trim_left_w(void)
{
    wchar_t const input[] = L"\n\r\t\v  value  ";
    stlsoft_C_string_slice_w_t result =
        stlsoft_C_string_trim_left_w(make_slice_w_(input));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input + 6, result.ptr);
    TEST_INT_EQ(0, wcsncmp(L"value  ", result.ptr, result.len));
}

static void TEST_trim_right_w(void)
{
    wchar_t const input[] = L"  value\n\r\t\v ";
    stlsoft_C_string_slice_w_t result =
        stlsoft_C_string_trim_right_w(make_slice_w_(input));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_INT_EQ(0, wcsncmp(L"  value", result.ptr, result.len));
}

static void TEST_trim_all_w(void)
{
    wchar_t const input[] = L"\n\r\t\v  value  \v\t\r\n";
    stlsoft_C_string_slice_w_t result =
        stlsoft_C_string_trim_all_w(make_slice_w_(input));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input + 6, result.ptr);
    TEST_INT_EQ(0, wcsncmp(L"value", result.ptr, result.len));
}

static void TEST_EACH_DEFAULT_WHITESPACE_CHARACTER_w(void)
{
    wchar_t const whitespace[] = L" \n\r\t\v";
    size_t i;

    for (i = 0; i != wcslen(whitespace); ++i)
    {
        wchar_t input[4];
        stlsoft_C_string_slice_w_t result;

        input[0] = whitespace[i];
        input[1] = L'x';
        input[2] = whitespace[i];
        input[3] = L'\0';

        result = stlsoft_C_string_trim_left_w(make_slice_n_w_(input, 3));
        TEST_INT_EQ(2u, result.len);
        TEST_PTR_EQ(input + 1, result.ptr);
        TEST_INT_EQ(L'x', result.ptr[0]);

        result = stlsoft_C_string_trim_right_w(make_slice_n_w_(input, 3));
        TEST_INT_EQ(2u, result.len);
        TEST_PTR_EQ(input, result.ptr);
        TEST_INT_EQ(L'x', result.ptr[1]);
    }
}

static void TEST_ALL_DEFAULT_WHITESPACE_w(void)
{
    wchar_t const input[] = L" \n\r\t\v";
    stlsoft_C_string_slice_w_t result =
        stlsoft_C_string_trim_all_w(make_slice_n_w_(input, wcslen(input)));

    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_INT_EQ(L'\0', result.ptr[0]);
}

static void TEST_NO_DEFAULT_WHITESPACE_w(void)
{
    wchar_t const input[] = L"value";
    stlsoft_C_string_slice_w_t result =
        stlsoft_C_string_trim_all_w(make_slice_w_(input));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_INT_EQ(0, wcsncmp(input, result.ptr, result.len));
}

static void TEST_trim_left_chars_w(void)
{
    wchar_t const input[] = L",;:value  ";
    wchar_t const chars[] = L",;:";
    stlsoft_C_string_slice_w_t result =
        stlsoft_C_string_trim_left_chars_w(
            make_slice_w_(input)
        ,   make_slice_w_(chars));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input + 3, result.ptr);
    TEST_INT_EQ(0, wcsncmp(L"value  ", result.ptr, result.len));
}

static void TEST_trim_right_chars_w(void)
{
    wchar_t const input[] = L"  value,;:";
    wchar_t const chars[] = L",;:";
    stlsoft_C_string_slice_w_t result =
        stlsoft_C_string_trim_right_chars_w(
            make_slice_w_(input)
        ,   make_slice_w_(chars));

    TEST_INT_EQ(7u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_INT_EQ(0, wcsncmp(L"  value", result.ptr, result.len));
}

static void TEST_trim_all_chars_w(void)
{
    wchar_t const input[] = L",;:value:;,";
    wchar_t const chars[] = L",;:";
    stlsoft_C_string_slice_w_t result =
        stlsoft_C_string_trim_all_chars_w(
            make_slice_w_(input)
        ,   make_slice_w_(chars));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input + 3, result.ptr);
    TEST_INT_EQ(0, wcsncmp(L"value", result.ptr, result.len));
}

static void TEST_trim_all_chars_w_WITH_EMPTY_SET(void)
{
    wchar_t const input[] = L"  value  ";
    stlsoft_C_string_slice_w_t chars;
    stlsoft_C_string_slice_w_t result;

    chars.len = 0;
    chars.ptr = NULL;

    result = stlsoft_C_string_trim_all_chars_w(make_slice_w_(input), chars);

    TEST_INT_EQ(9u, result.len);
    TEST_PTR_EQ(input, result.ptr);
    TEST_INT_EQ(0, wcsncmp(input, result.ptr, result.len));
}

static void TEST_BOUNDED_SLICE_w(void)
{
    wchar_t const input[] = L"  value  suffix";
    stlsoft_C_string_slice_w_t result =
        stlsoft_C_string_trim_all_w(make_slice_n_w_(input, 9));

    TEST_INT_EQ(5u, result.len);
    TEST_PTR_EQ(input + 2, result.ptr);
    TEST_INT_EQ(0, wcsncmp(L"value", result.ptr, result.len));
}

static void TEST_EMPTY_RESULT_w(void)
{
    wchar_t const input[] = L" \t\n";
    stlsoft_C_string_slice_w_t const slice = make_slice_w_(input);
    stlsoft_C_string_slice_w_t result;

    result = stlsoft_C_string_trim_left_w(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_INT_EQ(L'\0', result.ptr[0]);

    result = stlsoft_C_string_trim_right_w(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_INT_EQ(L'\0', result.ptr[0]);

    result = stlsoft_C_string_trim_all_w(slice);
    TEST_INT_EQ(0u, result.len);
    TEST_PTR_NE(NULL, result.ptr);
    TEST_INT_EQ(L'\0', result.ptr[0]);
}


/* ///////////////////////////// end of file //////////////////////////// */
