/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.number.group_functions/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::format_thousands` and
 *          `stlsoft::translate_thousands`.
 *
 * Created: 28th March 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/conversion/number/grouping_functions.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_format_thousands_SIMPLE();
    static void TEST_format_thousands_987654321_WITH_DEFAULT_SEPARATORS();
    static void TEST_format_thousands_18446744073709551615_WITH_DEFAULT_SEPARATORS();
    static void TEST_format_thousands_minus9223372036854775808_WITH_DEFAULT_SEPARATORS();
    static void TEST_format_thousands_987654321_WITH_CUSTOM_SEPARATORS();

    static void TEST_translate_thousands_MULTIBYTE();
    static void TEST_translate_thousands_WIDE();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.number.group_functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_format_thousands_SIMPLE);
        XTESTS_RUN_CASE(TEST_format_thousands_987654321_WITH_DEFAULT_SEPARATORS);
        XTESTS_RUN_CASE(TEST_format_thousands_18446744073709551615_WITH_DEFAULT_SEPARATORS);
        XTESTS_RUN_CASE(TEST_format_thousands_minus9223372036854775808_WITH_DEFAULT_SEPARATORS);
        XTESTS_RUN_CASE(TEST_format_thousands_987654321_WITH_CUSTOM_SEPARATORS);

        XTESTS_RUN_CASE(TEST_translate_thousands_MULTIBYTE);
        XTESTS_RUN_CASE(TEST_translate_thousands_WIDE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::ss_sint64_t;
    using stlsoft::ss_uint64_t;
    typedef std::string                                     string_a_t;


static void TEST_format_thousands_SIMPLE()
{
    char const* const pictures[] =
    {
        "1"
        , "2"
        , ";2"
        , "2;"
        , "4"
        , ";4"
        , "4;"
        , "8"
        , ";8"
        , "8;"
    };

    char      dest[101];
    const int v  =  0;
    size_t    n;

    for (size_t i = 0; STLSOFT_NUM_ELEMENTS(pictures) != i; ++i)
    {
        n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), pictures[i], v);

        TEST_INT_EQ(2u, n);
        TEST_MS_EQ("0", string_a_t(dest, n - 1));
    }
}

static void TEST_format_thousands_987654321_WITH_DEFAULT_SEPARATORS()
{
    char      dest[101];
    const int v  =  987654321;
    size_t    n;

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "9", v);

    TEST_INT_EQ(10u, n);
    TEST_MS_EQ("987654321", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "1", v);

    TEST_INT_EQ(11u, n);
    TEST_MS_EQ("98765432,1", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "2;1", v);

    TEST_INT_EQ(12u, n);
    TEST_MS_EQ("987654,3,21", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), ";3;1", v);

    TEST_INT_EQ(12u, n);
    TEST_MS_EQ("98765,4,321", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), ";3;3", v);

    TEST_INT_EQ(12u, n);
    TEST_MS_EQ("987,654,321", string_a_t(dest, n - 1));

    {
        n = stlsoft::format_thousands(static_cast<char*>(NULL), 0u, ";3;3", v);

        TEST_INT_EQ(12u, n);
    }

    {
        n = stlsoft::format_thousands(static_cast<char*>(NULL), 12u, ";3;3", v);

        TEST_INT_EQ(12u, n);
        TEST_MS_EQ("987,654,321", string_a_t(dest, n - 1));
    }

    {
        dest[0] = '\0';

        n = stlsoft::format_thousands(static_cast<char*>(NULL), 10u, ";3;3", v);

        TEST_INT_EQ(12u, n);
        TEST_MS_EQ("", string_a_t(dest, n - 1));
    }
}

static void TEST_format_thousands_18446744073709551615_WITH_DEFAULT_SEPARATORS()
{
    char                dest[101];
    const ss_uint64_t   v  =  STLSOFT_GEN_UINT64_SUFFIX(18446744073709551615);
    size_t              n;

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "9", v);

    TEST_INT_EQ(21u + 1u, n);
    TEST_MS_EQ("18446744073,709551615", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "1", v);

    TEST_INT_EQ(21u + 1u, n);
    TEST_MS_EQ("1844674407370955161,5", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "2;1", v);

    TEST_INT_EQ(22u + 1u, n);
    TEST_MS_EQ("18446744073709551,6,15", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), ";3;1", v);

    TEST_INT_EQ(22u + 1u, n);
    TEST_MS_EQ("1844674407370955,1,615", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), ";3;3", v);

    TEST_INT_EQ(22u + 1u, n);
    TEST_MS_EQ("18446744073709,551,615", string_a_t(dest, n - 1));
}

static void TEST_format_thousands_minus9223372036854775808_WITH_DEFAULT_SEPARATORS()
{
    char                dest[101];
    const ss_sint64_t   v  =  STLSOFT_GEN_SINT64_SUFFIX(-9223372036854775807) - 1;
    size_t              n;

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "9", v);

    TEST_INT_EQ(21u + 1u, n);
    TEST_MS_EQ("-9223372036,854775808", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "1", v);

    TEST_INT_EQ(21u + 1u, n);
    TEST_MS_EQ("-922337203685477580,8", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "2;1", v);

    TEST_INT_EQ(22u + 1u, n);
    TEST_MS_EQ("-9223372036854775,8,08", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), ";3;1", v);

    TEST_INT_EQ(22u + 1u, n);
    TEST_MS_EQ("-922337203685477,5,808", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), ";3;3", v);

    TEST_INT_EQ(22u + 1u, n);
    TEST_MS_EQ("-9223372036854,775,808", string_a_t(dest, n - 1));
}

static void TEST_format_thousands_987654321_WITH_CUSTOM_SEPARATORS()
{
    char      dest[101];
    const int v  =  987654321;
    size_t    n;

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "9", v, '|', '.');

    TEST_INT_EQ(10u, n);
    TEST_MS_EQ("987654321", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "1", v, '|', '.');

    TEST_INT_EQ(11u, n);
    TEST_MS_EQ("98765432.1", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "2|1", v, '|', '.');

    TEST_INT_EQ(12u, n);
    TEST_MS_EQ("987654.3.21", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "|3|1", v, '|', '.');

    TEST_INT_EQ(12u, n);
    TEST_MS_EQ("98765.4.321", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "|3|3", v, '|', '.');

    TEST_INT_EQ(12u, n);
    TEST_MS_EQ("987.654.321", string_a_t(dest, n - 1));

    n = stlsoft::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), "|3|1|2", v, '|', '.');

    TEST_INT_EQ(13u, n);
    TEST_MS_EQ("987.65.4.321", string_a_t(dest, n - 1));
}

static void TEST_translate_thousands_MULTIBYTE()
{
    char        dest[101];

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3", "123456789", ';', ',');

        TEST_INT_EQ(10u + 1u, n);
        TEST_MS_EQ("123456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), ";3", "123456789", ';', ',');

        TEST_INT_EQ(10u + 1u, n);
        TEST_MS_EQ("123456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3;3", "123456789", ';', ',');

        TEST_INT_EQ(11u + 1u, n);
        TEST_MS_EQ("123,456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), ";3;3", "123456789", ';', ',');

        TEST_INT_EQ(11u + 1u, n);
        TEST_MS_EQ("123,456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3;3;3", "123456789", ';', ',');

        TEST_INT_EQ(11u + 1u, n);
        TEST_MS_EQ("123,456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3;0", "123456789", ';', ',');

        TEST_INT_EQ(11u + 1u, n);
        TEST_MS_EQ("123,456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "1;1;1;1;1;1;1;1;1", "123456789", ';', ',');

        TEST_INT_EQ(17u + 1u, n);
        TEST_MS_EQ("1,2,3,4,5,6,7,8,9", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), "3;3;3", "abcdefghi", ';', ',');

        TEST_INT_EQ(11u + 1u, n);
        TEST_MS_EQ("abc,def,ghi", dest);
    }
}

static void TEST_translate_thousands_WIDE()
{
    wchar_t dest[101];

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), L"3", L"123456789", L';', L',');

        TEST_INT_EQ(10u + 1u, n);
        TEST_WS_EQ(L"123456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), L";3", L"123456789", L';', L',');

        TEST_INT_EQ(10u + 1u, n);
        TEST_WS_EQ(L"123456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), L"3;3", L"123456789", L';', L',');

        TEST_INT_EQ(11u + 1u, n);
        TEST_WS_EQ(L"123,456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), L";3;3", L"123456789", L';', L',');

        TEST_INT_EQ(11u + 1u, n);
        TEST_WS_EQ(L"123,456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), L"3;3;3", L"123456789", L';', L',');

        TEST_INT_EQ(11u + 1u, n);
        TEST_WS_EQ(L"123,456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), L"3;0", L"123456789", L';', L',');

        TEST_INT_EQ(11u + 1u, n);
        TEST_WS_EQ(L"123,456,789", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), L"1;1;1;1;1;1;1;1;1", L"123456789", L';', L',');

        TEST_INT_EQ(17u + 1u, n);
        TEST_WS_EQ(L"1,2,3,4,5,6,7,8,9", dest);
    }

    {
        size_t const    n   =   stlsoft::translate_thousands(dest, STLSOFT_NUM_ELEMENTS(dest), L"3;3;3", L"abcdefghi", L';', L',');

        TEST_INT_EQ(11u + 1u, n);
        TEST_WS_EQ(L"abc,def,ghi", dest);
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

