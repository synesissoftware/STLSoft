/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.conversion.number.grouping_functions/entry.cpp
 *
 * Purpose: Unit-tests for `winstl::format_thousands`.
 *
 * Created: 30th November 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * hook includes
 */

#include <winstl/winstl.h>

#define real_GetLocaleInfoA                                 GetLocaleInfoA
#define real_GetLocaleInfoW                                 GetLocaleInfoW
#define GetLocaleInfoA                                      hooked_GetLocaleInfoA
#define GetLocaleInfoW                                      hooked_GetLocaleInfoW

static
int
hooked_GetLocaleInfoA(
    LCID    Locale
,   LCTYPE  LCType
,   LPSTR   lpLCData
,   int     cchData
);
static
int
hooked_GetLocaleInfoW(
    LCID    Locale
,   LCTYPE  LCType
,   LPWSTR  lpLCData
,   int     cchData
);

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/conversion/number/grouping_functions.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */

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
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.conversion.number.grouping_functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_format_thousands_SIMPLE);
        XTESTS_RUN_CASE(TEST_format_thousands_987654321_WITH_DEFAULT_SEPARATORS);
        XTESTS_RUN_CASE(TEST_format_thousands_18446744073709551615_WITH_DEFAULT_SEPARATORS);
        XTESTS_RUN_CASE(TEST_format_thousands_minus9223372036854775808_WITH_DEFAULT_SEPARATORS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static char const*      s_picture_m =   NULL;
static wchar_t const*   s_picture_w =   NULL;

static
int
hooked_GetLocaleInfoA(
    LCID    Locale
,   LCTYPE  LCType
,   LPSTR   lpLCData
,   int     cchData
)
{
    if (LOCALE_USER_DEFAULT == Locale &&
        LOCALE_SGROUPING == LCType &&
        NULL != s_picture_m)
    {
        int const len = static_cast<int>(stlsoft::c_str_len_a(s_picture_m));

        if (NULL == lpLCData)
        {
            return len + 1;
        }
        else
        {
            if (cchData > len)
            {
                ::memcpy(lpLCData, s_picture_m, (1 + len) * sizeof(char));

                return 0;
            }
            else
            {
                ::SetLastError(ERROR_INSUFFICIENT_BUFFER);

                return 0;
            }
        }
    }
    else
    {
        return real_GetLocaleInfoA(Locale, LCType, lpLCData, cchData);
    }
}

static
int
hooked_GetLocaleInfoW(
    LCID    Locale
,   LCTYPE  LCType
,   LPWSTR  lpLCData
,   int     cchData
)
{
    if (LOCALE_USER_DEFAULT == Locale &&
        LOCALE_SGROUPING == LCType &&
        NULL != s_picture_w)
    {
        int const len = static_cast<int>(stlsoft::c_str_len_w(s_picture_w));

        if (NULL == lpLCData)
        {
            return len + 1;
        }
        else
        {
            if (cchData > len)
            {
                ::memcpy(lpLCData, s_picture_w, (1 + len) * sizeof(wchar_t));

                return 0;
            }
            else
            {
                ::SetLastError(ERROR_INSUFFICIENT_BUFFER);

                return 0;
            }
        }
    }
    else
    {
        return real_GetLocaleInfoW(Locale, LCType, lpLCData, cchData);
    }
}


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
        s_picture_m = pictures[i];

        n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

        TEST_INT_EQ(2u, n);
        TEST_MS_EQ("0", string_a_t(dest, n - 1));

        s_picture_m = NULL;
    }
}

static void TEST_format_thousands_987654321_WITH_DEFAULT_SEPARATORS()
{
    char      dest[101];
    const int v  =  987654321;
    size_t    n;

    s_picture_m = "9";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(10u, n);
    TEST_MS_EQ("987654321", string_a_t(dest, n - 1));

    s_picture_m = "1";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(11u, n);
    TEST_MS_EQ("98765432,1", string_a_t(dest, n - 1));

    s_picture_m = "2;1";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(12u, n);
    TEST_MS_EQ("987654,3,21", string_a_t(dest, n - 1));

    s_picture_m = "3;1";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(12u, n);
    TEST_MS_EQ("98765,4,321", string_a_t(dest, n - 1));

    s_picture_m = "3;3";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(12u, n);
    TEST_MS_EQ("987,654,321", string_a_t(dest, n - 1));

    {
        s_picture_m = ";3;3";
        n = winstl::format_thousands(static_cast<char*>(NULL), 0u, v);

        TEST_INT_EQ(12u, n);
    }

    {
        s_picture_m = ";3;3";
        n = winstl::format_thousands(static_cast<char*>(NULL), 12u, v);

        TEST_INT_EQ(12u, n);
        TEST_MS_EQ("987,654,321", string_a_t(dest, n - 1));
    }

    {
        dest[0] = '\0';

        s_picture_m = ";3;3";
        n = winstl::format_thousands(static_cast<char*>(NULL), 10u, v);

        TEST_INT_EQ(12u, n);
        TEST_MS_EQ("", string_a_t(dest, n - 1));
    }

    s_picture_m = NULL;
}

static void TEST_format_thousands_18446744073709551615_WITH_DEFAULT_SEPARATORS()
{
    char                dest[101];
    const ss_uint64_t   v  =  STLSOFT_GEN_UINT64_SUFFIX(18446744073709551615);
    size_t              n;

    s_picture_m = "9";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(21u + 1, n);
    TEST_MS_EQ("18446744073,709551615", string_a_t(dest, n - 1));

    s_picture_m = "1";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(21u + 1, n);
    TEST_MS_EQ("1844674407370955161,5", string_a_t(dest, n - 1));

    s_picture_m = "2;1";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(22u + 1, n);
    TEST_MS_EQ("18446744073709551,6,15", string_a_t(dest, n - 1));

    s_picture_m = "3;1";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(22u + 1, n);
    TEST_MS_EQ("1844674407370955,1,615", string_a_t(dest, n - 1));

    s_picture_m = ";3;3";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(22u + 1, n);
    TEST_MS_EQ("18446744073709,551,615", string_a_t(dest, n - 1));

    s_picture_m = NULL;
}

static void TEST_format_thousands_minus9223372036854775808_WITH_DEFAULT_SEPARATORS()
{
    char                dest[101];
    const ss_sint64_t   v  =  STLSOFT_GEN_SINT64_SUFFIX(-9223372036854775807) - 1;
    size_t              n;

    s_picture_m = "9";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(21u + 1, n);
    TEST_MS_EQ("-9223372036,854775808", string_a_t(dest, n - 1));

    s_picture_m = "1";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(21u + 1, n);
    TEST_MS_EQ("-922337203685477580,8", string_a_t(dest, n - 1));

    s_picture_m = "2;1";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(22u + 1, n);
    TEST_MS_EQ("-9223372036854775,8,08", string_a_t(dest, n - 1));

    s_picture_m = ";3;1";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(22u + 1, n);
    TEST_MS_EQ("-922337203685477,5,808", string_a_t(dest, n - 1));

    s_picture_m = ";3;3";
    n = winstl::format_thousands(&dest[0], STLSOFT_NUM_ELEMENTS(dest), v);

    TEST_INT_EQ(22u + 1, n);
    TEST_MS_EQ("-9223372036854,775,808", string_a_t(dest, n - 1));

    s_picture_m = NULL;
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

