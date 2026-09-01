/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.string_to_integer/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::string_to_integer`.
 *
 * Created: 18th November 2008
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */

#define STLSOFT_MINIMUM_SAS_INCLUDES


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/conversion/string_to_integer.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
// #include <limits>

/* Standard C header files */
// #include <ctype.h>
#include <stdint.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#ifdef STLSOFT_COMPILER_IS_BORLAND
# undef NULL
# define NULL   0
#endif


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void test_specialisations_1(void);
    static void test_specialisations_2(void);
    static void test_0(void);
    static void TEST_EMPTY(void);
    static void test_positives_implicit(void);
    static void test_positives_explicit(void);
    static void test_negatives(void);
    static void test_bad(void);
    static void TEST_INVALID_STRINGS(void);
    static void test_spaces(void);
    static void test_len_spaces(void);
    static void test_trailing(void);
    static void test_len_trailing(void);
    static void test_len_truncated(void);
    static void test_increasing_length(void);
    static void test_decimal_leading_plus(void);
    static void test_endptr(void);
    static void TEST_POLLUTED_STRINGS(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.string_to_integer", verbosity))
    {
        XTESTS_RUN_CASE(test_specialisations_1);
        XTESTS_RUN_CASE(test_specialisations_2);
        XTESTS_RUN_CASE(test_0);
        XTESTS_RUN_CASE(TEST_EMPTY);
        XTESTS_RUN_CASE(test_positives_implicit);
        XTESTS_RUN_CASE(test_positives_explicit);
        XTESTS_RUN_CASE(test_negatives);
        XTESTS_RUN_CASE(test_bad);
        XTESTS_RUN_CASE(TEST_INVALID_STRINGS);
        XTESTS_RUN_CASE(test_spaces);
        XTESTS_RUN_CASE(test_len_spaces);
        XTESTS_RUN_CASE(test_trailing);
        XTESTS_RUN_CASE(test_len_trailing);
        XTESTS_RUN_CASE(test_len_truncated);
        XTESTS_RUN_CASE(test_increasing_length);
        XTESTS_RUN_CASE(test_decimal_leading_plus);
        XTESTS_RUN_CASE(test_endptr);
        XTESTS_RUN_CASE(TEST_POLLUTED_STRINGS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{
    using stlsoft::sint64_t;
    using stlsoft::uint64_t;


static void test_specialisations_1()
{
    {
        stlsoft::string_to_integer( "0", static_cast<char const**>(0));
    }
    {
        stlsoft::string_to_integer(L"0", static_cast<wchar_t const**>(0));
    }


    {
        char const* endptr;
        stlsoft::string_to_integer( "0", &endptr);
        XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
        TEST_MS_EQ("0", endptr - 1);
    }
    {
        wchar_t const* endptr;
        stlsoft::string_to_integer(L"0", &endptr);
        XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
        TEST_WS_EQ(L"0", endptr - 1);
    }


    {
        char const* endptr;
        stlsoft::string_to_integer( "0", 1u, &endptr);
        XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
        TEST_MS_EQ("0", endptr - 1);
    }
    {
        wchar_t const* endptr;
        stlsoft::string_to_integer(L"0", 1u, &endptr);
        XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
        TEST_WS_EQ(L"0", endptr - 1);
    }


    {
        char const* endptr;
        stlsoft::string_to_integer( "0", 1, &endptr);
        XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
        TEST_MS_EQ("0", endptr - 1);
    }
    {
        wchar_t const* endptr;
        stlsoft::string_to_integer(L"0", 1, &endptr);
        XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
        TEST_WS_EQ(L"0", endptr - 1);
    }


    {
        char const* endptr;
        stlsoft::string_to_integer( "0", 0, &endptr);
        XTESTS_REQUIRE(TEST_PTR_EQ(NULL, endptr));
    }
    {
        wchar_t const* endptr;
        stlsoft::string_to_integer(L"0", 0, &endptr);
        XTESTS_REQUIRE(TEST_PTR_EQ(NULL, endptr));
    }


#if 0
    {
        stlsoft::string_to_integer<char>( "0", NULL);
    }
    {
        stlsoft::string_to_integer<wchar_t>(L"0", NULL);
    }


    {
        stlsoft::string_to_integer<char>( "0", 0, NULL);
    }
    {
        stlsoft::string_to_integer<wchar_t>(L"0", 0, NULL);
    }
#endif /* 0 */


    {
        stlsoft::string_to_integer( "0", NULL);
    }
    {
        stlsoft::string_to_integer(L"0", NULL);
    }

    TEST_PASSED();
}

static void test_specialisations_2()
{

#if 0
    {
        stlsoft::string_to_integer( std::string("0"), static_cast<char const**>(0));
    }
    {
        stlsoft::string_to_integer(L"0", static_cast<wchar_t const**>(0));
    }


    {
        char const* endptr;
        stlsoft::string_to_integer( std::string("0"), &endptr);
    }
    {
        wchar_t const* endptr;
        stlsoft::string_to_integer(L"0", &endptr);
    }


    {
        stlsoft::string_to_integer<char>( std::string("0"), NULL);
    }
    {
        stlsoft::string_to_integer<wchar_t>(L"0", NULL);
    }


    {
        stlsoft::string_to_integer( std::string("0"), NULL);
    }
    {
        stlsoft::string_to_integer(L"0", NULL);
    }
#endif /* 0 */

    TEST_PASSED();
}

static void test_0()
{
    TEST_INT_EQ(0, stlsoft::string_to_integer( "0", static_cast<char const**>(0)));

    TEST_INT_EQ(0, stlsoft::string_to_integer(L"0", static_cast<wchar_t const**>(0)));
}

static void TEST_EMPTY()
{
    TEST_INT_EQ(0, stlsoft::string_to_integer( "", static_cast<char const**>(0)));

    TEST_INT_EQ(0, stlsoft::string_to_integer(L"", static_cast<wchar_t const**>(0)));

    {
        char const  input[] = "";
        char const* endptr;

        int const   r   =   stlsoft::string_to_integer(input, &endptr);

        TEST_INT_EQ(0, r);
        TEST_PTR_EQ(input, endptr);
    }
}

static void test_positives_implicit()
{
    TEST_INT_EQ(1, stlsoft::string_to_integer("1", static_cast<char const**>(0)));
    TEST_INT_EQ(7, stlsoft::string_to_integer("7", static_cast<char const**>(0)));
    TEST_INT_EQ(10, stlsoft::string_to_integer("10", static_cast<char const**>(0)));
    TEST_INT_EQ(11, stlsoft::string_to_integer("11", static_cast<char const**>(0)));
    TEST_INT_EQ(123456, stlsoft::string_to_integer("123456", static_cast<char const**>(0)));
    TEST_INT_EQ(654321, stlsoft::string_to_integer("654321", static_cast<char const**>(0)));

    TEST_INT_EQ(1, stlsoft::string_to_integer(L"1", static_cast<wchar_t const**>(0)));
    TEST_INT_EQ(7, stlsoft::string_to_integer(L"7", static_cast<wchar_t const**>(0)));
    TEST_INT_EQ(10, stlsoft::string_to_integer(L"10", static_cast<wchar_t const**>(0)));
    TEST_INT_EQ(11, stlsoft::string_to_integer(L"11", static_cast<wchar_t const**>(0)));
    TEST_INT_EQ(123456, stlsoft::string_to_integer(L"123456", static_cast<wchar_t const**>(0)));
    TEST_INT_EQ(654321, stlsoft::string_to_integer(L"654321", static_cast<wchar_t const**>(0)));
}

static void test_positives_explicit()
{
    TEST_INT_EQ(+1, stlsoft::string_to_integer("+1", static_cast<char const**>(0)));
    TEST_INT_EQ(+7, stlsoft::string_to_integer("+7", static_cast<char const**>(0)));
    TEST_INT_EQ(+10, stlsoft::string_to_integer("+10", static_cast<char const**>(0)));
    TEST_INT_EQ(+11, stlsoft::string_to_integer("+11", static_cast<char const**>(0)));
    TEST_INT_EQ(+123456, stlsoft::string_to_integer("+123456", static_cast<char const**>(0)));
    TEST_INT_EQ(+654321, stlsoft::string_to_integer("+654321", static_cast<char const**>(0)));
}

static void test_negatives()
{
    TEST_INT_EQ(-1, stlsoft::string_to_integer("-1", static_cast<char const**>(0)));
    TEST_INT_EQ(-7, stlsoft::string_to_integer("-7", static_cast<char const**>(0)));
    TEST_INT_EQ(-10, stlsoft::string_to_integer("-10", static_cast<char const**>(0)));
    TEST_INT_EQ(-11, stlsoft::string_to_integer("-11", static_cast<char const**>(0)));
    TEST_INT_EQ(-123456, stlsoft::string_to_integer("-123456", static_cast<char const**>(0)));
    TEST_INT_EQ(-654321, stlsoft::string_to_integer("-654321", static_cast<char const**>(0)));
}

static void test_bad()
{
    char const* endptr = NULL;

    TEST_INT_EQ(0, stlsoft::string_to_integer("--0", &endptr));
    TEST_CHAR_EQ('-', *endptr);
    TEST_MS_EQ("-0", endptr);

    TEST_INT_EQ(0, stlsoft::string_to_integer("++0", &endptr));
    TEST_CHAR_EQ('+', *endptr);
    TEST_MS_EQ("+0", endptr);

    TEST_INT_EQ(0, stlsoft::string_to_integer("~0", &endptr));
    TEST_CHAR_EQ('~', *endptr);
    TEST_MS_EQ("~0", endptr);

    TEST_INT_EQ(0, stlsoft::string_to_integer("   ~0", &endptr));
    TEST_CHAR_EQ('~', *endptr);
    TEST_MS_EQ("~0", endptr);
}

static void TEST_INVALID_STRINGS()
{
    char const* endptr = NULL;

    {
        char const input[] = "AllowDeprecatedCP";

        TEST_INT_EQ(0, stlsoft::string_to_integer(input, &endptr));
        TEST_PTR_EQ(input, endptr);

        TEST_INT_EQ(0, stlsoft::string_to_integer(input, STLSOFT_NUM_ELEMENTS(input) - 1, &endptr));
        TEST_PTR_EQ(input, endptr);
    }
}

static void test_spaces()
{
    TEST_INT_EQ(1, stlsoft::string_to_integer(" \t\r\n\v\b1", static_cast<char const**>(0)));
    TEST_INT_EQ(7, stlsoft::string_to_integer(" \t\r\n\v\b7", static_cast<char const**>(0)));
    TEST_INT_EQ(10, stlsoft::string_to_integer(" \t\r\n\v\b10", static_cast<char const**>(0)));
    TEST_INT_EQ(11, stlsoft::string_to_integer(" \t\r\n\v\b11", static_cast<char const**>(0)));
    TEST_INT_EQ(123456, stlsoft::string_to_integer(" \t\r\n\v\b123456", static_cast<char const**>(0)));
    TEST_INT_EQ(654321, stlsoft::string_to_integer(" \t\r\n\v\b654321", static_cast<char const**>(0)));

    TEST_INT_EQ(+1, stlsoft::string_to_integer(" \t\r\n\v\b+1", static_cast<char const**>(0)));
    TEST_INT_EQ(+7, stlsoft::string_to_integer(" \t\r\n\v\b+7", static_cast<char const**>(0)));
    TEST_INT_EQ(+10, stlsoft::string_to_integer(" \t\r\n\v\b+10", static_cast<char const**>(0)));
    TEST_INT_EQ(+11, stlsoft::string_to_integer(" \t\r\n\v\b+11", static_cast<char const**>(0)));
    TEST_INT_EQ(+123456, stlsoft::string_to_integer(" \t\r\n\v\b+123456", static_cast<char const**>(0)));
    TEST_INT_EQ(+654321, stlsoft::string_to_integer(" \t\r\n\v\b+654321", static_cast<char const**>(0)));

    TEST_INT_EQ(-1, stlsoft::string_to_integer(" \t\r\n\v\b-1", static_cast<char const**>(0)));
    TEST_INT_EQ(-7, stlsoft::string_to_integer(" \t\r\n\v\b-7", static_cast<char const**>(0)));
    TEST_INT_EQ(-10, stlsoft::string_to_integer(" \t\r\n\v\b-10", static_cast<char const**>(0)));
    TEST_INT_EQ(-11, stlsoft::string_to_integer(" \t\r\n\v\b-11", static_cast<char const**>(0)));
    TEST_INT_EQ(-123456, stlsoft::string_to_integer(" \t\r\n\v\b-123456", static_cast<char const**>(0)));
    TEST_INT_EQ(-654321, stlsoft::string_to_integer(" \t\r\n\v\b-654321", static_cast<char const**>(0)));
}

static void test_len_spaces()
{
    TEST_INT_EQ(1, stlsoft::string_to_integer(" \t\r\n\v\b1", 7, static_cast<char const**>(0)));
    TEST_INT_EQ(7, stlsoft::string_to_integer(" \t\r\n\v\b7", 7, static_cast<char const**>(0)));
    TEST_INT_EQ(10, stlsoft::string_to_integer(" \t\r\n\v\b10", 8, static_cast<char const**>(0)));
    TEST_INT_EQ(11, stlsoft::string_to_integer(" \t\r\n\v\b11", 8, static_cast<char const**>(0)));
    TEST_INT_EQ(123456, stlsoft::string_to_integer(" \t\r\n\v\b123456", 12, static_cast<char const**>(0)));
    TEST_INT_EQ(654321, stlsoft::string_to_integer(" \t\r\n\v\b654321", 12, static_cast<char const**>(0)));

    TEST_INT_EQ(+1, stlsoft::string_to_integer(" \t\r\n\v\b+1", 8, static_cast<char const**>(0)));
    TEST_INT_EQ(+7, stlsoft::string_to_integer(" \t\r\n\v\b+7", 8, static_cast<char const**>(0)));
    TEST_INT_EQ(+10, stlsoft::string_to_integer(" \t\r\n\v\b+10", 9, static_cast<char const**>(0)));
    TEST_INT_EQ(+11, stlsoft::string_to_integer(" \t\r\n\v\b+11", 9, static_cast<char const**>(0)));
    TEST_INT_EQ(+123456, stlsoft::string_to_integer(" \t\r\n\v\b+123456", 13, static_cast<char const**>(0)));
    TEST_INT_EQ(+654321, stlsoft::string_to_integer(" \t\r\n\v\b+654321", 13, static_cast<char const**>(0)));

    TEST_INT_EQ(-1, stlsoft::string_to_integer(" \t\r\n\v\b-1", 8, static_cast<char const**>(0)));
    TEST_INT_EQ(-7, stlsoft::string_to_integer(" \t\r\n\v\b-7", 8, static_cast<char const**>(0)));
    TEST_INT_EQ(-10, stlsoft::string_to_integer(" \t\r\n\v\b-10", 9, static_cast<char const**>(0)));
    TEST_INT_EQ(-11, stlsoft::string_to_integer(" \t\r\n\v\b-11", 9, static_cast<char const**>(0)));
    TEST_INT_EQ(-123456, stlsoft::string_to_integer(" \t\r\n\v\b-123456", 13, static_cast<char const**>(0)));
    TEST_INT_EQ(-654321, stlsoft::string_to_integer(" \t\r\n\v\b-654321", 13, static_cast<char const**>(0)));
}

static void test_trailing()
{
    char const* endptr = NULL;

    TEST_INT_EQ(1, stlsoft::string_to_integer("1abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(7, stlsoft::string_to_integer("7abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(10, stlsoft::string_to_integer("10abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(11, stlsoft::string_to_integer("11abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(123456, stlsoft::string_to_integer("123456abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(654321, stlsoft::string_to_integer("654321abc", &endptr));
    TEST_MS_EQ("abc", endptr);

    TEST_INT_EQ(+1, stlsoft::string_to_integer("+1abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(+7, stlsoft::string_to_integer("+7abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(+10, stlsoft::string_to_integer("+10abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(+11, stlsoft::string_to_integer("+11abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(+123456, stlsoft::string_to_integer("+123456abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(+654321, stlsoft::string_to_integer("+654321abc", &endptr));
    TEST_MS_EQ("abc", endptr);

    TEST_INT_EQ(-1, stlsoft::string_to_integer("-1abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(-7, stlsoft::string_to_integer("-7abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(-10, stlsoft::string_to_integer("-10abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(-11, stlsoft::string_to_integer("-11abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(-123456, stlsoft::string_to_integer("-123456abc", &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(-654321, stlsoft::string_to_integer("-654321abc", &endptr));
    TEST_MS_EQ("abc", endptr);
}

static void test_len_trailing()
{
    char const* endptr = NULL;

    TEST_INT_EQ(1, stlsoft::string_to_integer("1abc", 4, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(7, stlsoft::string_to_integer("7abc", 4, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(10, stlsoft::string_to_integer("10abc", 5, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(11, stlsoft::string_to_integer("11abc", 5, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(123456, stlsoft::string_to_integer("123456abc", 9, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(654321, stlsoft::string_to_integer("654321abc", 9, &endptr));
    TEST_MS_EQ("abc", endptr);

    TEST_INT_EQ(+1, stlsoft::string_to_integer("+1abc", 5, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(+7, stlsoft::string_to_integer("+7abc", 5, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(+10, stlsoft::string_to_integer("+10abc", 6, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(+11, stlsoft::string_to_integer("+11abc", 6, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(+123456, stlsoft::string_to_integer("+123456abc", 10, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(+654321, stlsoft::string_to_integer("+654321abc", 10, &endptr));
    TEST_MS_EQ("abc", endptr);

    TEST_INT_EQ(-1, stlsoft::string_to_integer("-1abc", 5, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(-7, stlsoft::string_to_integer("-7abc", 5, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(-10, stlsoft::string_to_integer("-10abc", 6, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(-11, stlsoft::string_to_integer("-11abc", 6, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(-123456, stlsoft::string_to_integer("-123456abc", 10, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(-654321, stlsoft::string_to_integer("-654321abc", 10, &endptr));
    TEST_MS_EQ("abc", endptr);
}

static void test_len_truncated()
{
    char const* endptr = NULL;

    TEST_INT_EQ(1, stlsoft::string_to_integer("1abc", 2, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(7, stlsoft::string_to_integer("7abc", 2, &endptr));
    TEST_MS_EQ("abc", endptr);
    TEST_INT_EQ(10, stlsoft::string_to_integer("10abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(11, stlsoft::string_to_integer("11abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(12, stlsoft::string_to_integer("123456abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(65, stlsoft::string_to_integer("654321abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));

    TEST_INT_EQ(+1, stlsoft::string_to_integer("+1abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(+7, stlsoft::string_to_integer("+7abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(+1, stlsoft::string_to_integer("+10abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(+1, stlsoft::string_to_integer("+11abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(+1, stlsoft::string_to_integer("+123456abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(+6, stlsoft::string_to_integer("+654321abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));

    TEST_INT_EQ(-1, stlsoft::string_to_integer("-1abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(-7, stlsoft::string_to_integer("-7abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(-1, stlsoft::string_to_integer("-10abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(-1, stlsoft::string_to_integer("-11abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(-1, stlsoft::string_to_integer("-123456abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
    TEST_INT_EQ(-6, stlsoft::string_to_integer("-654321abc", 2, &endptr));
    XTESTS_REQUIRE(TEST_PTR_NE(NULL, endptr));
}

static void test_increasing_length()
{
    {
        const char  number[]    =   "1000000000";
        int         result      =   0;

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(number); ++i)
        {
            int n = stlsoft::string_to_integer(number, i, NULL);

            TEST_INT_EQ(result, n);

            result = (0 == result) ? 1 : (result * 10);
        }}
    }

    {
        const wchar_t   number[]    =   L"1000000000";
        int             result      =   0;

        { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(number); ++i)
        {
            int n = stlsoft::string_to_integer(number, i, NULL);

            TEST_INT_EQ(result, n);

            result = (0 == result) ? 1 : (result * 10);
        }}
    }
}

static void test_decimal_leading_plus()
{
    char const* endptr = NULL;

    TEST_INT_EQ(123, stlsoft::string_to_integer(" +123abc", 8, &endptr));
    TEST_MS_EQ("abc", endptr);

    TEST_INT_EQ(0, stlsoft::string_to_integer(" +abc123", 8, &endptr));
    TEST_MS_EQ("+abc123", endptr);

    TEST_INT_EQ(0, stlsoft::string_to_integer(" abc123", 7, &endptr));
    TEST_MS_EQ("abc123", endptr);
}

static void test_endptr()
{
    {
        char const  src[]   =   "0";
        char const* endptr  =   NULL;

        TEST_INT_EQ(0, stlsoft::string_to_integer(src, &endptr));
        TEST_PTR_EQ(src + 1, endptr);
    }

    {
        char const  src[]   =   "0";
        char const* endptr  =   NULL;

        TEST_INT_EQ(0, stlsoft::string_to_integer(src, STLSOFT_NUM_ELEMENTS(src) - 1u, &endptr));
        TEST_PTR_EQ(src + 1, endptr);
    }

    {
        char const* endptr;
        stlsoft::string_to_integer("0", 0, &endptr);
        XTESTS_REQUIRE(TEST_PTR_EQ(NULL, endptr));
    }
}

static void TEST_POLLUTED_STRINGS()
{
    char const* endptr = NULL;

    TEST_INT_EQ(-123, stlsoft::string_to_integer(" -123abc", 8, &endptr));
    TEST_MS_EQ("abc", endptr);

    TEST_INT_EQ(123, stlsoft::string_to_integer(" +123abc", 8, &endptr));
    TEST_MS_EQ("abc", endptr);

    TEST_INT_EQ(123, stlsoft::string_to_integer(" 123abc", 8, &endptr));
    TEST_MS_EQ("abc", endptr);

    TEST_INT_EQ(0, stlsoft::string_to_integer(" -abc123", 8, &endptr));
    TEST_MS_EQ("-abc123", endptr);

    TEST_INT_EQ(0, stlsoft::string_to_integer(" +abc123", 8, &endptr));
    TEST_MS_EQ("+abc123", endptr);

    TEST_INT_EQ(0, stlsoft::string_to_integer(" abc123", 7, &endptr));
    TEST_MS_EQ("abc123", endptr);
}
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */

