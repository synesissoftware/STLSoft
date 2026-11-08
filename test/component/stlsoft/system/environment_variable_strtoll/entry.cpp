/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/stlsoft/system/environment_variable_strtoll/entry.cpp
 *
 * Purpose: Component tests for
 *          `stlsoft_C_environment_variable_strtoll_m()`.
 *
 * Created: 28th September 2026
 * Updated: 8th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/system/environment/functions.h>


/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <platformstl/system/environment_variable_scope.hpp>
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_environment_variable_strtoll_WHEN_ABSENT();
    static void TEST_environment_variable_strtoll_WHEN_DECIMAL();
    static void TEST_environment_variable_strtoll_WHEN_BASE_PREFIXES();
    static void TEST_environment_variable_strtoll_WHEN_LEADING_WHITESPACE();
    static void TEST_environment_variable_strtoll_WHEN_NOT_COMPLETE();
    static void TEST_environment_variable_strtoll_WHEN_OUT_OF_RANGE();
    static void TEST_environment_variable_strtoll_WHEN_LONG_VALUE();
    static void TEST_environment_variable_strtoll_WHEN_ERASED();
    static void TEST_environment_variable_strtoll_WHEN_VALUE_REPLACED();
    static void TEST_environment_variable_strtoll_EXACT_NAME();
    static void TEST_environment_variable_strtoll_CASE_SENSITIVITY();
    static void TEST_environment_variable_strtoll_CPP_WRAPPER();
#ifndef _WIN32
    static void TEST_environment_variable_strtoll_WHEN_EMPTY();
#endif /* !_WIN32 */
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.stlsoft.system.environment_variable_strtoll", verbosity))
    {
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_WHEN_ABSENT);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_WHEN_DECIMAL);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_WHEN_BASE_PREFIXES);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_WHEN_LEADING_WHITESPACE);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_WHEN_NOT_COMPLETE);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_WHEN_OUT_OF_RANGE);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_WHEN_LONG_VALUE);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_WHEN_ERASED);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_WHEN_VALUE_REPLACED);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_EXACT_NAME);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_CASE_SENSITIVITY);
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_CPP_WRAPPER);
#ifndef _WIN32
        XTESTS_RUN_CASE(TEST_environment_variable_strtoll_WHEN_EMPTY);
#endif /* !_WIN32 */

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

namespace {

    using platformstl::environment_variable_scope;

    stlsoft::ss_sint64_t const SENTINEL_ = 0x5a5a5a5a;

    char const VAR_NAME[]           =   "STLSOFT_CT_ENV_VAR_STRTOLL";
    char const VAR_NAME_EXTRA[]     =   "STLSOFT_CT_ENV_VAR_STRTOLL_EXTRA";
    char const VAR_NAME_LOWER[]     =   "stlsoft_ct_env_var_strtoll_case";
    char const VAR_NAME_PREFIX[]    =   "STLSOFT_CT_ENV_VAR_STRTOL";
    char const VAR_NAME_UPPER[]     =   "STLSOFT_CT_ENV_VAR_STRTOLL_CASE";
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

#define TEST_READ_PARSED_(name, expected)                               \
                                                                        \
    do                                                                  \
    {                                                                   \
        stlsoft::ss_sint64_t result_ = SENTINEL_;                       \
                                                                        \
        errno = EPERM;                                                  \
                                                                        \
        stlsoft::ss_truthy_t const parsed_ =                            \
            stlsoft::stlsoft_C_environment_variable_strtoll_m(          \
                (name)                                                  \
            ,   &result_                                                \
            );                                                          \
                                                                        \
        TEST_BOOLEAN_TRUE(parsed_);                                     \
        TEST_INT_EQ((expected), result_);                               \
        TEST_INT_EQ(0, errno);                                          \
    } while (0)

#define TEST_READ_REJECTED_(name, expected_errno)                       \
                                                                        \
    do                                                                  \
    {                                                                   \
        stlsoft::ss_sint64_t result_ = SENTINEL_;                       \
                                                                        \
        errno = EPERM;                                                  \
                                                                        \
        stlsoft::ss_truthy_t const parsed_ =                            \
            stlsoft::stlsoft_C_environment_variable_strtoll_m(          \
                (name)                                                  \
            ,   &result_                                                \
            );                                                          \
                                                                        \
        TEST_BOOLEAN_FALSE(parsed_);                                    \
        TEST_INT_EQ(0, result_);                                        \
        TEST_INT_EQ((expected_errno), errno);                           \
    } while (0)

#define TEST_PARSED_(value, expected)                                   \
                                                                        \
    do                                                                  \
    {                                                                   \
        environment_variable_scope const scope_(VAR_NAME, (value));     \
                                                                        \
        TEST_READ_PARSED_(VAR_NAME, (expected));                        \
    } while (0)

#define TEST_REJECTED_(value, expected_errno)                           \
                                                                        \
    do                                                                  \
    {                                                                   \
        environment_variable_scope const scope_(VAR_NAME, (value));     \
                                                                        \
        TEST_READ_REJECTED_(VAR_NAME, (expected_errno));                \
    } while (0)


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void fill_n_(
    char*   buff
,   int     n
,   char    ch
)
{
    int i;

    for (i = 0; i != n; ++i)
    {
        buff[i] = ch;
    }

    buff[n] = '\0';
}

/* Absence is a failed lookup: the function returns 0, sets errno to EINVAL,
 * and writes 0 through result.
 */
static void TEST_environment_variable_strtoll_WHEN_ABSENT()
{
    environment_variable_scope const absent(VAR_NAME, ss_nullptr_k);

    TEST_READ_REJECTED_(VAR_NAME, EINVAL);
}

static void TEST_environment_variable_strtoll_WHEN_DECIMAL()
{
    TEST_PARSED_("0", 0);
    TEST_PARSED_("00", 0);
    TEST_PARSED_("+0", 0);
    TEST_PARSED_("-0", 0);
    TEST_PARSED_("1", 1);
    TEST_PARSED_("42", 42);
    TEST_PARSED_("+42", 42);
    TEST_PARSED_("-42", -42);
    TEST_PARSED_("   -42", -42);
    TEST_PARSED_("      -42", -42);
    TEST_PARSED_("         -42", -42);
    TEST_PARSED_("            -42", -42);
    TEST_PARSED_("               -42", -42);
    TEST_PARSED_("                  -42", -42);
    TEST_PARSED_("                     -42", -42);
    TEST_PARSED_("                        -42", -42);
    TEST_PARSED_("                           -42", -42);
    TEST_PARSED_("                              -42", -42);
    TEST_PARSED_("-123456", -123456);

    TEST_PARSED_("9223372036854775807", STLSOFT_GEN_SINT64_SUFFIX(9223372036854775807));
    TEST_PARSED_("-9223372036854775807", -STLSOFT_GEN_SINT64_SUFFIX(9223372036854775807));
    TEST_PARSED_("-9223372036854775808", -STLSOFT_GEN_SINT64_SUFFIX(9223372036854775807) - 1);
}

/* Base 0 follows strtoll(): a leading 0 selects octal and a leading 0x
 * selects hexadecimal. The whole value must be one subject sequence.
 */
static void TEST_environment_variable_strtoll_WHEN_BASE_PREFIXES()
{
    TEST_PARSED_("010", 8);
    TEST_PARSED_("+010", 8);
    TEST_PARSED_("-010", -8);
    TEST_PARSED_("0x10", 16);
    TEST_PARSED_("0X10", 16);
    TEST_PARSED_("0xff", 255);
    TEST_PARSED_("0xFf", 255);
    TEST_PARSED_("+0x10", 16);
    TEST_PARSED_("-0x10", -16);
    TEST_PARSED_("0x0", 0);
}

/* Leading whitespace belongs to a strtoll() subject sequence. Trailing
 * characters, including whitespace, do not.
 */
static void TEST_environment_variable_strtoll_WHEN_LEADING_WHITESPACE()
{
    TEST_PARSED_(" 42", 42);
    TEST_PARSED_("\t42", 42);
    TEST_PARSED_(" \t -42", -42);
    TEST_PARSED_("  +0x10", 16);

    TEST_REJECTED_("42 ", EINVAL);
    TEST_REJECTED_(" 42 ", EINVAL);
    TEST_REJECTED_("42\n", EINVAL);
}

static void TEST_environment_variable_strtoll_WHEN_NOT_COMPLETE()
{
    TEST_REJECTED_("abc", EINVAL);
    TEST_REJECTED_("  ", EINVAL);
    TEST_REJECTED_("+", EINVAL);
    TEST_REJECTED_("-", EINVAL);
    TEST_REJECTED_("++1", EINVAL);
    TEST_REJECTED_("--1", EINVAL);
    TEST_REJECTED_("0x", EINVAL);
    TEST_REJECTED_("0xG", EINVAL);
    TEST_REJECTED_("123abc", EINVAL);
    TEST_REJECTED_("08", EINVAL);
    TEST_REJECTED_("09", EINVAL);
    TEST_REJECTED_("1.5", EINVAL);
    TEST_REJECTED_("1e2", EINVAL);
}

static void TEST_environment_variable_strtoll_WHEN_OUT_OF_RANGE()
{
    /* Out-of-range values are rejected with ERANGE and result is set to 0,
     * rather than the saturated limits that strtoll() returns.
     */
    TEST_REJECTED_("9223372036854775808", ERANGE);
    TEST_REJECTED_("-9223372036854775809", ERANGE);
}

/* The complete environment-variable value is read before parsing, so a
 * valid value remains valid when preceded by substantial whitespace.
 */
static void TEST_environment_variable_strtoll_WHEN_LONG_VALUE()
{
    char text[1024];

    fill_n_(text, 1000, ' ');
    text[1000] = '-';
    text[1001] = '4';
    text[1002] = '2';
    text[1003] = '\0';
    TEST_PARSED_(text, -42);

    text[1003] = 'x';
    text[1004] = '\0';
    TEST_REJECTED_(text, EINVAL);
}

static void TEST_environment_variable_strtoll_WHEN_ERASED()
{
    environment_variable_scope const present(VAR_NAME, "5");

    TEST_READ_PARSED_(VAR_NAME, 5);

    environment_variable_scope const erased(VAR_NAME, ss_nullptr_k);

    TEST_READ_REJECTED_(VAR_NAME, EINVAL);
}

static void TEST_environment_variable_strtoll_WHEN_VALUE_REPLACED()
{
    environment_variable_scope const first(VAR_NAME, "11");

    TEST_READ_PARSED_(VAR_NAME, 11);

    environment_variable_scope const second(VAR_NAME, "22");

    TEST_READ_PARSED_(VAR_NAME, 22);
}

static void TEST_environment_variable_strtoll_EXACT_NAME()
{
    environment_variable_scope const extra_absent(VAR_NAME_EXTRA, ss_nullptr_k);
    environment_variable_scope const prefix_absent(VAR_NAME_PREFIX, ss_nullptr_k);
    environment_variable_scope const present(VAR_NAME, "42");

    TEST_READ_PARSED_(VAR_NAME, 42);
    TEST_READ_REJECTED_(VAR_NAME_EXTRA, EINVAL);
    TEST_READ_REJECTED_(VAR_NAME_PREFIX, EINVAL);

    environment_variable_scope const erased(VAR_NAME, ss_nullptr_k);
    environment_variable_scope const extra(VAR_NAME_EXTRA, "7");

    TEST_READ_REJECTED_(VAR_NAME, EINVAL);
    TEST_READ_PARSED_(VAR_NAME_EXTRA, 7);
}

/* UNIX names are case-sensitive; the Windows CRT folds case.
 */
static void TEST_environment_variable_strtoll_CASE_SENSITIVITY()
{
    environment_variable_scope const lower(VAR_NAME_LOWER, ss_nullptr_k);
    environment_variable_scope const upper(VAR_NAME_UPPER, "7");

    TEST_READ_PARSED_(VAR_NAME_UPPER, 7);
#ifdef _WIN32

    TEST_READ_PARSED_(VAR_NAME_LOWER, 7);
#else

    TEST_READ_REJECTED_(VAR_NAME_LOWER, EINVAL);
#endif
}

static void TEST_environment_variable_strtoll_CPP_WRAPPER()
{
    environment_variable_scope const value(VAR_NAME, "9223372036854775807");
    stlsoft::ss_sint64_t result = SENTINEL_;

    TEST_BOOLEAN_TRUE(stlsoft::environment_variable_strtoll(VAR_NAME, &result));
    TEST_INT_EQ(STLSOFT_GEN_SINT64_SUFFIX(9223372036854775807), result);
}

#ifndef _WIN32

/* An empty value is defined on UNIX, and it is not a number. The Windows
 * CRT treats an empty assignment as erasure, so this case is UNIX-only.
 */
static void TEST_environment_variable_strtoll_WHEN_EMPTY()
{
    TEST_REJECTED_("", EINVAL);
}
#endif /* !_WIN32 */
} // anonymous namespace

#undef TEST_PARSED_
#undef TEST_READ_PARSED_
#undef TEST_READ_REJECTED_
#undef TEST_REJECTED_


/* ///////////////////////////// end of file //////////////////////////// */

