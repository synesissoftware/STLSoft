/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/time/fast_strftime/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::fast_strftime()` and
 *          `stlsoft::fast_wcsftime()`.
 *
 * Created: 9th August 2026
 * Updated: 19th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/time/fast_strftime.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_fast_strftime_WITH_EMPTY_FORMAT();
    static void TEST_fast_strftime_WITH_LITERAL_ONLY_FORMAT();
    static void TEST_fast_strftime_WITH_SPECIFIER_percent();
    static void TEST_fast_strftime_WITH_SPECIFIER_a();
    static void TEST_fast_strftime_WITH_SPECIFIER_A();
    static void TEST_fast_strftime_WITH_SPECIFIER_b();
    static void TEST_fast_strftime_WITH_SPECIFIER_B();
    static void TEST_fast_strftime_WITH_SPECIFIER_C();
    static void TEST_fast_strftime_WITH_SPECIFIER_d();
    static void TEST_fast_strftime_WITH_SPECIFIER_h();
    static void TEST_fast_strftime_WITH_SPECIFIER_H();
    static void TEST_fast_strftime_WITH_SPECIFIER_I();
    static void TEST_fast_strftime_WITH_SPECIFIER_j();
    static void TEST_fast_strftime_WITH_SPECIFIER_m();
    static void TEST_fast_strftime_WITH_SPECIFIER_M();
    static void TEST_fast_strftime_WITH_SPECIFIER_S();
    static void TEST_fast_strftime_WITH_SPECIFIER_U();
    static void TEST_fast_strftime_WITH_SPECIFIER_w();
    static void TEST_fast_strftime_WITH_SPECIFIER_W();
    static void TEST_fast_strftime_WITH_SPECIFIER_y();
    static void TEST_fast_strftime_WITH_SPECIFIER_Y();
    static void TEST_fast_strftime_WITH_SPECIFIER_D();
    static void TEST_fast_strftime_WITH_SPECIFIER_e();
    static void TEST_fast_strftime_WITH_SPECIFIER_F();
    static void TEST_fast_strftime_WITH_SPECIFIER_n();
    static void TEST_fast_strftime_WITH_SPECIFIER_R();
    static void TEST_fast_strftime_WITH_SPECIFIER_t();
    static void TEST_fast_strftime_WITH_SPECIFIER_T();
    static void TEST_fast_strftime_WITH_SPECIFIER_u();
    static void TEST_fast_strftime_WITH_MULTIPLE_SPECIFIERS();
    static void TEST_fast_strftime_WITH_HASH_MODIFIER_ON_NUMERIC_SPECIFIERS();
    static void TEST_fast_strftime_WITH_HASH_MODIFIER_ON_SPECIFIER_j();
    static void TEST_fast_strftime_WITH_HASH_MODIFIER_ON_COMPOSITE_SPECIFIERS();
    static void TEST_fast_strftime_WITH_HASH_MODIFIER_ON_UNAFFECTED_SPECIFIERS();
    static void TEST_fast_strftime_WITH_BUFFER_OF_EXACT_FIT();
    static void TEST_fast_strftime_WITH_BUFFER_ONE_ELEMENT_TOO_SMALL();
    static void TEST_fast_wcsftime_WITH_LITERAL_ONLY_FORMAT();
    static void TEST_fast_wcsftime_WITH_SPECIFIER_percent();
    static void TEST_fast_wcsftime_WITH_NAME_SPECIFIERS();
    static void TEST_fast_wcsftime_WITH_NUMERIC_SPECIFIERS();
    static void TEST_fast_wcsftime_WITH_COMPOSITE_SPECIFIERS();
    static void TEST_fast_wcsftime_WITH_MULTIPLE_SPECIFIERS();
    static void TEST_fast_wcsftime_WITH_HASH_MODIFIER();
    static void TEST_fast_wcsftime_WITH_BUFFER_OF_EXACT_FIT();
    static void TEST_fast_wcsftime_WITH_BUFFER_ONE_ELEMENT_TOO_SMALL();
    static void TEST_fast_strftime_WITH_WIDE_OVERLOAD();
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
    static void TEST_fast_strftime_WITH_ARRAY_OVERLOAD();
    static void TEST_fast_strftime_WITH_WIDE_ARRAY_OVERLOAD();
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_EMPTY_FORMAT);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_LITERAL_ONLY_FORMAT);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_percent);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_a);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_A);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_b);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_B);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_C);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_d);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_h);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_H);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_I);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_j);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_m);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_M);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_S);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_U);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_w);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_W);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_y);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_Y);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_D);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_e);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_F);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_n);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_R);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_t);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_T);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_SPECIFIER_u);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_MULTIPLE_SPECIFIERS);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_HASH_MODIFIER_ON_NUMERIC_SPECIFIERS);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_HASH_MODIFIER_ON_SPECIFIER_j);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_HASH_MODIFIER_ON_COMPOSITE_SPECIFIERS);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_HASH_MODIFIER_ON_UNAFFECTED_SPECIFIERS);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_BUFFER_OF_EXACT_FIT);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_BUFFER_ONE_ELEMENT_TOO_SMALL);
        XTESTS_RUN_CASE(TEST_fast_wcsftime_WITH_LITERAL_ONLY_FORMAT);
        XTESTS_RUN_CASE(TEST_fast_wcsftime_WITH_SPECIFIER_percent);
        XTESTS_RUN_CASE(TEST_fast_wcsftime_WITH_NAME_SPECIFIERS);
        XTESTS_RUN_CASE(TEST_fast_wcsftime_WITH_NUMERIC_SPECIFIERS);
        XTESTS_RUN_CASE(TEST_fast_wcsftime_WITH_COMPOSITE_SPECIFIERS);
        XTESTS_RUN_CASE(TEST_fast_wcsftime_WITH_MULTIPLE_SPECIFIERS);
        XTESTS_RUN_CASE(TEST_fast_wcsftime_WITH_HASH_MODIFIER);
        XTESTS_RUN_CASE(TEST_fast_wcsftime_WITH_BUFFER_OF_EXACT_FIT);
        XTESTS_RUN_CASE(TEST_fast_wcsftime_WITH_BUFFER_ONE_ELEMENT_TOO_SMALL);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_WIDE_OVERLOAD);
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_ARRAY_OVERLOAD);
        XTESTS_RUN_CASE(TEST_fast_strftime_WITH_WIDE_ARRAY_OVERLOAD);
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

/*
 * Constructs a `tm` from explicit field values, without reference to the
 * time zone or the current locale, so that the tests are independent of
 * the operating environment.
 *
 * `month` is 1-based (January == 1); `year` is the calendar year; `wday`
 * is 0-based, with Sunday == 0; `yday` is 0-based, with 1st January == 0.
 */
static struct tm make_tm(
    int year
,   int month
,   int mday
,   int hour
,   int minute
,   int second
,   int wday
,   int yday
)
{
    struct tm r;

    ::memset(&r, 0, sizeof(r));

    r.tm_year   =   year - 1900;
    r.tm_mon    =   month - 1;
    r.tm_mday   =   mday;
    r.tm_hour   =   hour;
    r.tm_min    =   minute;
    r.tm_sec    =   second;
    r.tm_wday   =   wday;
    r.tm_yday   =   yday;

    return r;
}


/* The assertions are in macros, so that failures are reported at the line
 * of the scenario that failed, not within a shared helper.
 *
 * Each macro also checks that the byte following the terminating NUL
 * remains undisturbed.
 */

/* Formats into a roomy buffer; expects the stated result and length. */
#define EXPECT_STRFTIME_(expected, fmt, tm_expr)                                            \
                                                                                            \
    do                                                                                      \
    {                                                                                       \
        struct tm const tm_     =   (tm_expr);                                              \
        char            buff_[64];                                                          \
                                                                                            \
        ::memset(&buff_[0], '~', sizeof(buff_));                                            \
                                                                                            \
        size_t const    n_      =   stlsoft::fast_strftime(&buff_[0], sizeof(buff_), (fmt), &tm_);  \
                                                                                            \
        TEST_INT_EQ(sizeof(expected) - 1, n_);                                              \
        TEST_MS_EQ((expected), &buff_[0]);                                                  \
        TEST_CHAR_EQ('~', buff_[sizeof(expected)]);                                         \
    } while (0)

/* Formats into a buffer that is exactly large enough (result + NUL). */
#define EXPECT_STRFTIME_EXACT_FIT_(expected, fmt, tm_expr)                                  \
                                                                                            \
    do                                                                                      \
    {                                                                                       \
        struct tm const tm_     =   (tm_expr);                                              \
        char            buff_[sizeof(expected)];                                            \
                                                                                            \
        ::memset(&buff_[0], '~', sizeof(buff_));                                            \
                                                                                            \
        size_t const    n_      =   stlsoft::fast_strftime(&buff_[0], sizeof(buff_), (fmt), &tm_);  \
                                                                                            \
        TEST_INT_EQ(sizeof(expected) - 1, n_);                                              \
        TEST_MS_EQ((expected), &buff_[0]);                                                  \
    } while (0)

/* Formats into a buffer one element too small for (result + NUL); expects
 * the failure indication (0).
 */
#define EXPECT_STRFTIME_ONE_TOO_SMALL_(expected, fmt, tm_expr)                              \
                                                                                            \
    do                                                                                      \
    {                                                                                       \
        struct tm const tm_     =   (tm_expr);                                              \
        char            buff_[sizeof(expected) - 1];                                        \
                                                                                            \
        ::memset(&buff_[0], '~', sizeof(buff_));                                            \
                                                                                            \
        size_t const    n_      =   stlsoft::fast_strftime(&buff_[0], sizeof(buff_), (fmt), &tm_);  \
                                                                                            \
        TEST_INT_EQ(static_cast<size_t>(0), n_);                                            \
    } while (0)

/* Wide equivalents. */
#define EXPECT_WCSFTIME_(expected, fmt, tm_expr)                                            \
                                                                                            \
    do                                                                                      \
    {                                                                                       \
        struct tm const tm_     =   (tm_expr);                                              \
        wchar_t         buff_[64];                                                          \
                                                                                            \
        ::wmemset(&buff_[0], L'~', STLSOFT_NUM_ELEMENTS(buff_));                            \
                                                                                            \
        size_t const    n_      =   stlsoft::fast_wcsftime(&buff_[0], STLSOFT_NUM_ELEMENTS(buff_), (fmt), &tm_);  \
                                                                                            \
        TEST_INT_EQ((sizeof(expected) / sizeof(wchar_t)) - 1, n_);                          \
        TEST_WS_EQ((expected), &buff_[0]);                                                  \
        TEST_BOOLEAN_TRUE(L'~' == buff_[sizeof(expected) / sizeof(wchar_t)]);               \
    } while (0)

#define EXPECT_WCSFTIME_EXACT_FIT_(expected, fmt, tm_expr)                                  \
                                                                                            \
    do                                                                                      \
    {                                                                                       \
        struct tm const tm_     =   (tm_expr);                                              \
        wchar_t         buff_[sizeof(expected) / sizeof(wchar_t)];                          \
                                                                                            \
        ::wmemset(&buff_[0], L'~', STLSOFT_NUM_ELEMENTS(buff_));                            \
                                                                                            \
        size_t const    n_      =   stlsoft::fast_wcsftime(&buff_[0], STLSOFT_NUM_ELEMENTS(buff_), (fmt), &tm_);  \
                                                                                            \
        TEST_INT_EQ((sizeof(expected) / sizeof(wchar_t)) - 1, n_);                          \
        TEST_WS_EQ((expected), &buff_[0]);                                                  \
    } while (0)

#define EXPECT_WCSFTIME_ONE_TOO_SMALL_(expected, fmt, tm_expr)                              \
                                                                                            \
    do                                                                                      \
    {                                                                                       \
        struct tm const tm_     =   (tm_expr);                                              \
        wchar_t         buff_[(sizeof(expected) / sizeof(wchar_t)) - 1];                    \
                                                                                            \
        ::wmemset(&buff_[0], L'~', STLSOFT_NUM_ELEMENTS(buff_));                            \
                                                                                            \
        size_t const    n_      =   stlsoft::fast_wcsftime(&buff_[0], STLSOFT_NUM_ELEMENTS(buff_), (fmt), &tm_);  \
                                                                                            \
        TEST_INT_EQ(static_cast<size_t>(0), n_);                                            \
    } while (0)


static void TEST_fast_strftime_WITH_EMPTY_FORMAT()
{
    struct tm const tm_nominal = make_tm(2026, 11, 19, 13, 45, 7, 4, 322);

    EXPECT_STRFTIME_("", "", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));

    {
        char            buff[2] = { '~', '~', };
        size_t const    n       =   stlsoft::fast_strftime(&buff[0], 1, "", &tm_nominal);

        TEST_INT_EQ(static_cast<size_t>(0), n);
        TEST_CHAR_EQ('\0', buff[0]);
        TEST_CHAR_EQ('~', buff[1]);
    }
}

static void TEST_fast_strftime_WITH_LITERAL_ONLY_FORMAT()
{
    EXPECT_STRFTIME_("a",             "a",             make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("abc",           "abc",           make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("Hello, world!", "Hello, world!", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("2026-11-19",    "2026-11-19",    make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("a#b",           "a#b",           make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("  ",            "  ",            make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_SPECIFIER_percent()
{
    EXPECT_STRFTIME_("%",    "%%",    make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("%%",   "%%%%",  make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("100%", "100%%", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("%d",   "%%d",   make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("[%]",  "[%%]",  make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("%19",  "%%%d",  make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_SPECIFIER_a()
{
    EXPECT_STRFTIME_("Sun", "%a", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_STRFTIME_("Mon", "%a", make_tm(2026, 11, 16, 13, 45, 7, 1, 319));
    EXPECT_STRFTIME_("Tue", "%a", make_tm(2026, 11, 17, 13, 45, 7, 2, 320));
    EXPECT_STRFTIME_("Wed", "%a", make_tm(2026, 11, 18, 13, 45, 7, 3, 321));
    EXPECT_STRFTIME_("Thu", "%a", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("Fri", "%a", make_tm(2026, 11, 20, 13, 45, 7, 5, 323));
    EXPECT_STRFTIME_("Sat", "%a", make_tm(2026, 11, 21, 13, 45, 7, 6, 324));
}

static void TEST_fast_strftime_WITH_SPECIFIER_A()
{
    EXPECT_STRFTIME_("Sunday",    "%A", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_STRFTIME_("Monday",    "%A", make_tm(2026, 11, 16, 13, 45, 7, 1, 319));
    EXPECT_STRFTIME_("Tuesday",   "%A", make_tm(2026, 11, 17, 13, 45, 7, 2, 320));
    EXPECT_STRFTIME_("Wednesday", "%A", make_tm(2026, 11, 18, 13, 45, 7, 3, 321));
    EXPECT_STRFTIME_("Thursday",  "%A", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("Friday",    "%A", make_tm(2026, 11, 20, 13, 45, 7, 5, 323));
    EXPECT_STRFTIME_("Saturday",  "%A", make_tm(2026, 11, 21, 13, 45, 7, 6, 324));
}

static void TEST_fast_strftime_WITH_SPECIFIER_b()
{
    EXPECT_STRFTIME_("Jan", "%b", make_tm(2026, 1, 15, 13, 45, 7, 4, 14));
    EXPECT_STRFTIME_("Feb", "%b", make_tm(2026, 2, 15, 13, 45, 7, 0, 45));
    EXPECT_STRFTIME_("Mar", "%b", make_tm(2026, 3, 15, 13, 45, 7, 0, 73));
    EXPECT_STRFTIME_("Apr", "%b", make_tm(2026, 4, 15, 13, 45, 7, 3, 104));
    EXPECT_STRFTIME_("May", "%b", make_tm(2026, 5, 15, 13, 45, 7, 5, 134));
    EXPECT_STRFTIME_("Jun", "%b", make_tm(2026, 6, 15, 13, 45, 7, 1, 165));
    EXPECT_STRFTIME_("Jul", "%b", make_tm(2026, 7, 15, 13, 45, 7, 3, 195));
    EXPECT_STRFTIME_("Aug", "%b", make_tm(2026, 8, 15, 13, 45, 7, 6, 226));
    EXPECT_STRFTIME_("Sep", "%b", make_tm(2026, 9, 15, 13, 45, 7, 2, 257));
    EXPECT_STRFTIME_("Oct", "%b", make_tm(2026, 10, 15, 13, 45, 7, 4, 287));
    EXPECT_STRFTIME_("Nov", "%b", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_STRFTIME_("Dec", "%b", make_tm(2026, 12, 15, 13, 45, 7, 2, 348));
}

static void TEST_fast_strftime_WITH_SPECIFIER_B()
{
    EXPECT_STRFTIME_("January",   "%B", make_tm(2026, 1, 15, 13, 45, 7, 4, 14));
    EXPECT_STRFTIME_("February",  "%B", make_tm(2026, 2, 15, 13, 45, 7, 0, 45));
    EXPECT_STRFTIME_("March",     "%B", make_tm(2026, 3, 15, 13, 45, 7, 0, 73));
    EXPECT_STRFTIME_("April",     "%B", make_tm(2026, 4, 15, 13, 45, 7, 3, 104));
    EXPECT_STRFTIME_("May",       "%B", make_tm(2026, 5, 15, 13, 45, 7, 5, 134));
    EXPECT_STRFTIME_("June",      "%B", make_tm(2026, 6, 15, 13, 45, 7, 1, 165));
    EXPECT_STRFTIME_("July",      "%B", make_tm(2026, 7, 15, 13, 45, 7, 3, 195));
    EXPECT_STRFTIME_("August",    "%B", make_tm(2026, 8, 15, 13, 45, 7, 6, 226));
    EXPECT_STRFTIME_("September", "%B", make_tm(2026, 9, 15, 13, 45, 7, 2, 257));
    EXPECT_STRFTIME_("October",   "%B", make_tm(2026, 10, 15, 13, 45, 7, 4, 287));
    EXPECT_STRFTIME_("November",  "%B", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_STRFTIME_("December",  "%B", make_tm(2026, 12, 15, 13, 45, 7, 2, 348));
}

static void TEST_fast_strftime_WITH_SPECIFIER_C()
{
    EXPECT_STRFTIME_("19", "%C", make_tm(1900, 1, 1, 0, 0, 0, 1, 0));
    EXPECT_STRFTIME_("19", "%C", make_tm(1999, 1, 1, 0, 0, 0, 5, 0));
    EXPECT_STRFTIME_("20", "%C", make_tm(2000, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("20", "%C", make_tm(2026, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("99", "%C", make_tm(9999, 1, 1, 0, 0, 0, 5, 0));
}

static void TEST_fast_strftime_WITH_SPECIFIER_d()
{
    EXPECT_STRFTIME_("01", "%d", make_tm(2026, 1, 1, 13, 45, 7, 4, 0));
    EXPECT_STRFTIME_("09", "%d", make_tm(2026, 1, 9, 13, 45, 7, 5, 8));
    EXPECT_STRFTIME_("10", "%d", make_tm(2026, 1, 10, 13, 45, 7, 6, 9));
    EXPECT_STRFTIME_("31", "%d", make_tm(2026, 1, 31, 13, 45, 7, 6, 30));
}

static void TEST_fast_strftime_WITH_SPECIFIER_h()
{
    EXPECT_STRFTIME_("Jan", "%h", make_tm(2026, 1, 15, 13, 45, 7, 4, 14));
    EXPECT_STRFTIME_("Feb", "%h", make_tm(2026, 2, 15, 13, 45, 7, 0, 45));
    EXPECT_STRFTIME_("Mar", "%h", make_tm(2026, 3, 15, 13, 45, 7, 0, 73));
    EXPECT_STRFTIME_("Apr", "%h", make_tm(2026, 4, 15, 13, 45, 7, 3, 104));
    EXPECT_STRFTIME_("May", "%h", make_tm(2026, 5, 15, 13, 45, 7, 5, 134));
    EXPECT_STRFTIME_("Jun", "%h", make_tm(2026, 6, 15, 13, 45, 7, 1, 165));
    EXPECT_STRFTIME_("Jul", "%h", make_tm(2026, 7, 15, 13, 45, 7, 3, 195));
    EXPECT_STRFTIME_("Aug", "%h", make_tm(2026, 8, 15, 13, 45, 7, 6, 226));
    EXPECT_STRFTIME_("Sep", "%h", make_tm(2026, 9, 15, 13, 45, 7, 2, 257));
    EXPECT_STRFTIME_("Oct", "%h", make_tm(2026, 10, 15, 13, 45, 7, 4, 287));
    EXPECT_STRFTIME_("Nov", "%h", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_STRFTIME_("Dec", "%h", make_tm(2026, 12, 15, 13, 45, 7, 2, 348));
}

static void TEST_fast_strftime_WITH_SPECIFIER_H()
{
    EXPECT_STRFTIME_("00", "%H", make_tm(2026, 11, 19, 0, 45, 7, 4, 322));
    EXPECT_STRFTIME_("01", "%H", make_tm(2026, 11, 19, 1, 45, 7, 4, 322));
    EXPECT_STRFTIME_("09", "%H", make_tm(2026, 11, 19, 9, 45, 7, 4, 322));
    EXPECT_STRFTIME_("10", "%H", make_tm(2026, 11, 19, 10, 45, 7, 4, 322));
    EXPECT_STRFTIME_("12", "%H", make_tm(2026, 11, 19, 12, 45, 7, 4, 322));
    EXPECT_STRFTIME_("13", "%H", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("23", "%H", make_tm(2026, 11, 19, 23, 45, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_SPECIFIER_I()
{
    EXPECT_STRFTIME_("12", "%I", make_tm(2026, 11, 19, 0, 45, 7, 4, 322));
    EXPECT_STRFTIME_("01", "%I", make_tm(2026, 11, 19, 1, 45, 7, 4, 322));
    EXPECT_STRFTIME_("09", "%I", make_tm(2026, 11, 19, 9, 45, 7, 4, 322));
    EXPECT_STRFTIME_("10", "%I", make_tm(2026, 11, 19, 10, 45, 7, 4, 322));
    EXPECT_STRFTIME_("11", "%I", make_tm(2026, 11, 19, 11, 45, 7, 4, 322));
    EXPECT_STRFTIME_("12", "%I", make_tm(2026, 11, 19, 12, 45, 7, 4, 322));
    EXPECT_STRFTIME_("01", "%I", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("11", "%I", make_tm(2026, 11, 19, 23, 45, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_SPECIFIER_j()
{
    EXPECT_STRFTIME_("001", "%j", make_tm(2026, 1, 1, 13, 45, 7, 4, 0));
    EXPECT_STRFTIME_("009", "%j", make_tm(2026, 1, 9, 13, 45, 7, 5, 8));
    EXPECT_STRFTIME_("010", "%j", make_tm(2026, 1, 10, 13, 45, 7, 6, 9));
    EXPECT_STRFTIME_("031", "%j", make_tm(2026, 1, 31, 13, 45, 7, 6, 30));
    EXPECT_STRFTIME_("060", "%j", make_tm(2000, 2, 29, 13, 45, 7, 2, 59));
    EXPECT_STRFTIME_("099", "%j", make_tm(2026, 4, 9, 13, 45, 7, 4, 98));
    EXPECT_STRFTIME_("100", "%j", make_tm(2026, 4, 10, 13, 45, 7, 5, 99));
    EXPECT_STRFTIME_("323", "%j", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("366", "%j", make_tm(2024, 12, 31, 13, 45, 7, 2, 365));
}

static void TEST_fast_strftime_WITH_SPECIFIER_m()
{
    EXPECT_STRFTIME_("01", "%m", make_tm(2026, 1, 15, 13, 45, 7, 4, 14));
    EXPECT_STRFTIME_("02", "%m", make_tm(2026, 2, 15, 13, 45, 7, 0, 45));
    EXPECT_STRFTIME_("03", "%m", make_tm(2026, 3, 15, 13, 45, 7, 0, 73));
    EXPECT_STRFTIME_("04", "%m", make_tm(2026, 4, 15, 13, 45, 7, 3, 104));
    EXPECT_STRFTIME_("05", "%m", make_tm(2026, 5, 15, 13, 45, 7, 5, 134));
    EXPECT_STRFTIME_("06", "%m", make_tm(2026, 6, 15, 13, 45, 7, 1, 165));
    EXPECT_STRFTIME_("07", "%m", make_tm(2026, 7, 15, 13, 45, 7, 3, 195));
    EXPECT_STRFTIME_("08", "%m", make_tm(2026, 8, 15, 13, 45, 7, 6, 226));
    EXPECT_STRFTIME_("09", "%m", make_tm(2026, 9, 15, 13, 45, 7, 2, 257));
    EXPECT_STRFTIME_("10", "%m", make_tm(2026, 10, 15, 13, 45, 7, 4, 287));
    EXPECT_STRFTIME_("11", "%m", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_STRFTIME_("12", "%m", make_tm(2026, 12, 15, 13, 45, 7, 2, 348));
}

static void TEST_fast_strftime_WITH_SPECIFIER_M()
{
    EXPECT_STRFTIME_("00", "%M", make_tm(2026, 11, 19, 13, 0, 7, 4, 322));
    EXPECT_STRFTIME_("05", "%M", make_tm(2026, 11, 19, 13, 5, 7, 4, 322));
    EXPECT_STRFTIME_("10", "%M", make_tm(2026, 11, 19, 13, 10, 7, 4, 322));
    EXPECT_STRFTIME_("59", "%M", make_tm(2026, 11, 19, 13, 59, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_SPECIFIER_S()
{
    EXPECT_STRFTIME_("00", "%S", make_tm(2026, 11, 19, 13, 45, 0, 4, 322));
    EXPECT_STRFTIME_("07", "%S", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("10", "%S", make_tm(2026, 11, 19, 13, 45, 10, 4, 322));
    EXPECT_STRFTIME_("59", "%S", make_tm(2026, 11, 19, 13, 45, 59, 4, 322));
}

static void TEST_fast_strftime_WITH_SPECIFIER_U()
{
    EXPECT_STRFTIME_("01", "%U", make_tm(2023, 1, 1, 0, 0, 0, 0, 0));
    EXPECT_STRFTIME_("01", "%U", make_tm(2023, 1, 2, 0, 0, 0, 1, 1));
    EXPECT_STRFTIME_("01", "%U", make_tm(2023, 1, 3, 0, 0, 0, 2, 2));
    EXPECT_STRFTIME_("01", "%U", make_tm(2023, 1, 4, 0, 0, 0, 3, 3));
    EXPECT_STRFTIME_("01", "%U", make_tm(2023, 1, 5, 0, 0, 0, 4, 4));
    EXPECT_STRFTIME_("01", "%U", make_tm(2023, 1, 6, 0, 0, 0, 5, 5));
    EXPECT_STRFTIME_("01", "%U", make_tm(2023, 1, 7, 0, 0, 0, 6, 6));
    EXPECT_STRFTIME_("02", "%U", make_tm(2023, 1, 8, 0, 0, 0, 0, 7));
    EXPECT_STRFTIME_("00", "%U", make_tm(2018, 1, 1, 0, 0, 0, 1, 0));
    EXPECT_STRFTIME_("00", "%U", make_tm(2018, 1, 2, 0, 0, 0, 2, 1));
    EXPECT_STRFTIME_("00", "%U", make_tm(2018, 1, 3, 0, 0, 0, 3, 2));
    EXPECT_STRFTIME_("00", "%U", make_tm(2018, 1, 4, 0, 0, 0, 4, 3));
    EXPECT_STRFTIME_("00", "%U", make_tm(2018, 1, 5, 0, 0, 0, 5, 4));
    EXPECT_STRFTIME_("00", "%U", make_tm(2018, 1, 6, 0, 0, 0, 6, 5));
    EXPECT_STRFTIME_("01", "%U", make_tm(2018, 1, 7, 0, 0, 0, 0, 6));
    EXPECT_STRFTIME_("01", "%U", make_tm(2018, 1, 8, 0, 0, 0, 1, 7));
    EXPECT_STRFTIME_("00", "%U", make_tm(2019, 1, 1, 0, 0, 0, 2, 0));
    EXPECT_STRFTIME_("00", "%U", make_tm(2019, 1, 2, 0, 0, 0, 3, 1));
    EXPECT_STRFTIME_("00", "%U", make_tm(2019, 1, 3, 0, 0, 0, 4, 2));
    EXPECT_STRFTIME_("00", "%U", make_tm(2019, 1, 4, 0, 0, 0, 5, 3));
    EXPECT_STRFTIME_("00", "%U", make_tm(2019, 1, 5, 0, 0, 0, 6, 4));
    EXPECT_STRFTIME_("01", "%U", make_tm(2019, 1, 6, 0, 0, 0, 0, 5));
    EXPECT_STRFTIME_("01", "%U", make_tm(2019, 1, 7, 0, 0, 0, 1, 6));
    EXPECT_STRFTIME_("01", "%U", make_tm(2019, 1, 8, 0, 0, 0, 2, 7));
    EXPECT_STRFTIME_("00", "%U", make_tm(2025, 1, 1, 0, 0, 0, 3, 0));
    EXPECT_STRFTIME_("00", "%U", make_tm(2025, 1, 2, 0, 0, 0, 4, 1));
    EXPECT_STRFTIME_("00", "%U", make_tm(2025, 1, 3, 0, 0, 0, 5, 2));
    EXPECT_STRFTIME_("00", "%U", make_tm(2025, 1, 4, 0, 0, 0, 6, 3));
    EXPECT_STRFTIME_("01", "%U", make_tm(2025, 1, 5, 0, 0, 0, 0, 4));
    EXPECT_STRFTIME_("01", "%U", make_tm(2025, 1, 6, 0, 0, 0, 1, 5));
    EXPECT_STRFTIME_("01", "%U", make_tm(2025, 1, 7, 0, 0, 0, 2, 6));
    EXPECT_STRFTIME_("01", "%U", make_tm(2025, 1, 8, 0, 0, 0, 3, 7));
    EXPECT_STRFTIME_("00", "%U", make_tm(2026, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("00", "%U", make_tm(2026, 1, 2, 0, 0, 0, 5, 1));
    EXPECT_STRFTIME_("00", "%U", make_tm(2026, 1, 3, 0, 0, 0, 6, 2));
    EXPECT_STRFTIME_("01", "%U", make_tm(2026, 1, 4, 0, 0, 0, 0, 3));
    EXPECT_STRFTIME_("01", "%U", make_tm(2026, 1, 5, 0, 0, 0, 1, 4));
    EXPECT_STRFTIME_("01", "%U", make_tm(2026, 1, 6, 0, 0, 0, 2, 5));
    EXPECT_STRFTIME_("01", "%U", make_tm(2026, 1, 7, 0, 0, 0, 3, 6));
    EXPECT_STRFTIME_("01", "%U", make_tm(2026, 1, 8, 0, 0, 0, 4, 7));
    EXPECT_STRFTIME_("00", "%U", make_tm(2021, 1, 1, 0, 0, 0, 5, 0));
    EXPECT_STRFTIME_("00", "%U", make_tm(2021, 1, 2, 0, 0, 0, 6, 1));
    EXPECT_STRFTIME_("01", "%U", make_tm(2021, 1, 3, 0, 0, 0, 0, 2));
    EXPECT_STRFTIME_("01", "%U", make_tm(2021, 1, 4, 0, 0, 0, 1, 3));
    EXPECT_STRFTIME_("01", "%U", make_tm(2021, 1, 5, 0, 0, 0, 2, 4));
    EXPECT_STRFTIME_("01", "%U", make_tm(2021, 1, 6, 0, 0, 0, 3, 5));
    EXPECT_STRFTIME_("01", "%U", make_tm(2021, 1, 7, 0, 0, 0, 4, 6));
    EXPECT_STRFTIME_("01", "%U", make_tm(2021, 1, 8, 0, 0, 0, 5, 7));
    EXPECT_STRFTIME_("00", "%U", make_tm(2022, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("01", "%U", make_tm(2022, 1, 2, 0, 0, 0, 0, 1));
    EXPECT_STRFTIME_("01", "%U", make_tm(2022, 1, 3, 0, 0, 0, 1, 2));
    EXPECT_STRFTIME_("01", "%U", make_tm(2022, 1, 4, 0, 0, 0, 2, 3));
    EXPECT_STRFTIME_("01", "%U", make_tm(2022, 1, 5, 0, 0, 0, 3, 4));
    EXPECT_STRFTIME_("01", "%U", make_tm(2022, 1, 6, 0, 0, 0, 4, 5));
    EXPECT_STRFTIME_("01", "%U", make_tm(2022, 1, 7, 0, 0, 0, 5, 6));
    EXPECT_STRFTIME_("01", "%U", make_tm(2022, 1, 8, 0, 0, 0, 6, 7));
    EXPECT_STRFTIME_("00", "%U", make_tm(1900, 1, 1, 0, 0, 0, 1, 0));
    EXPECT_STRFTIME_("00", "%U", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("09", "%U", make_tm(2000, 2, 29, 23, 59, 59, 2, 59));
    EXPECT_STRFTIME_("10", "%U", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_STRFTIME_("52", "%U", make_tm(2024, 12, 31, 12, 0, 0, 2, 365));
    EXPECT_STRFTIME_("46", "%U", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("52", "%U", make_tm(9999, 12, 31, 23, 59, 59, 5, 364));
}

static void TEST_fast_strftime_WITH_SPECIFIER_w()
{
    EXPECT_STRFTIME_("0", "%w", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_STRFTIME_("1", "%w", make_tm(2026, 11, 16, 13, 45, 7, 1, 319));
    EXPECT_STRFTIME_("2", "%w", make_tm(2026, 11, 17, 13, 45, 7, 2, 320));
    EXPECT_STRFTIME_("3", "%w", make_tm(2026, 11, 18, 13, 45, 7, 3, 321));
    EXPECT_STRFTIME_("4", "%w", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("5", "%w", make_tm(2026, 11, 20, 13, 45, 7, 5, 323));
    EXPECT_STRFTIME_("6", "%w", make_tm(2026, 11, 21, 13, 45, 7, 6, 324));
}

static void TEST_fast_strftime_WITH_SPECIFIER_W()
{
    EXPECT_STRFTIME_("00", "%W", make_tm(2023, 1, 1, 0, 0, 0, 0, 0));
    EXPECT_STRFTIME_("01", "%W", make_tm(2023, 1, 2, 0, 0, 0, 1, 1));
    EXPECT_STRFTIME_("01", "%W", make_tm(2023, 1, 3, 0, 0, 0, 2, 2));
    EXPECT_STRFTIME_("01", "%W", make_tm(2023, 1, 4, 0, 0, 0, 3, 3));
    EXPECT_STRFTIME_("01", "%W", make_tm(2023, 1, 5, 0, 0, 0, 4, 4));
    EXPECT_STRFTIME_("01", "%W", make_tm(2023, 1, 6, 0, 0, 0, 5, 5));
    EXPECT_STRFTIME_("01", "%W", make_tm(2023, 1, 7, 0, 0, 0, 6, 6));
    EXPECT_STRFTIME_("01", "%W", make_tm(2023, 1, 8, 0, 0, 0, 0, 7));
    EXPECT_STRFTIME_("01", "%W", make_tm(2018, 1, 1, 0, 0, 0, 1, 0));
    EXPECT_STRFTIME_("01", "%W", make_tm(2018, 1, 2, 0, 0, 0, 2, 1));
    EXPECT_STRFTIME_("01", "%W", make_tm(2018, 1, 3, 0, 0, 0, 3, 2));
    EXPECT_STRFTIME_("01", "%W", make_tm(2018, 1, 4, 0, 0, 0, 4, 3));
    EXPECT_STRFTIME_("01", "%W", make_tm(2018, 1, 5, 0, 0, 0, 5, 4));
    EXPECT_STRFTIME_("01", "%W", make_tm(2018, 1, 6, 0, 0, 0, 6, 5));
    EXPECT_STRFTIME_("01", "%W", make_tm(2018, 1, 7, 0, 0, 0, 0, 6));
    EXPECT_STRFTIME_("02", "%W", make_tm(2018, 1, 8, 0, 0, 0, 1, 7));
    EXPECT_STRFTIME_("00", "%W", make_tm(2019, 1, 1, 0, 0, 0, 2, 0));
    EXPECT_STRFTIME_("00", "%W", make_tm(2019, 1, 2, 0, 0, 0, 3, 1));
    EXPECT_STRFTIME_("00", "%W", make_tm(2019, 1, 3, 0, 0, 0, 4, 2));
    EXPECT_STRFTIME_("00", "%W", make_tm(2019, 1, 4, 0, 0, 0, 5, 3));
    EXPECT_STRFTIME_("00", "%W", make_tm(2019, 1, 5, 0, 0, 0, 6, 4));
    EXPECT_STRFTIME_("00", "%W", make_tm(2019, 1, 6, 0, 0, 0, 0, 5));
    EXPECT_STRFTIME_("01", "%W", make_tm(2019, 1, 7, 0, 0, 0, 1, 6));
    EXPECT_STRFTIME_("01", "%W", make_tm(2019, 1, 8, 0, 0, 0, 2, 7));
    EXPECT_STRFTIME_("00", "%W", make_tm(2025, 1, 1, 0, 0, 0, 3, 0));
    EXPECT_STRFTIME_("00", "%W", make_tm(2025, 1, 2, 0, 0, 0, 4, 1));
    EXPECT_STRFTIME_("00", "%W", make_tm(2025, 1, 3, 0, 0, 0, 5, 2));
    EXPECT_STRFTIME_("00", "%W", make_tm(2025, 1, 4, 0, 0, 0, 6, 3));
    EXPECT_STRFTIME_("00", "%W", make_tm(2025, 1, 5, 0, 0, 0, 0, 4));
    EXPECT_STRFTIME_("01", "%W", make_tm(2025, 1, 6, 0, 0, 0, 1, 5));
    EXPECT_STRFTIME_("01", "%W", make_tm(2025, 1, 7, 0, 0, 0, 2, 6));
    EXPECT_STRFTIME_("01", "%W", make_tm(2025, 1, 8, 0, 0, 0, 3, 7));
    EXPECT_STRFTIME_("00", "%W", make_tm(2026, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("00", "%W", make_tm(2026, 1, 2, 0, 0, 0, 5, 1));
    EXPECT_STRFTIME_("00", "%W", make_tm(2026, 1, 3, 0, 0, 0, 6, 2));
    EXPECT_STRFTIME_("00", "%W", make_tm(2026, 1, 4, 0, 0, 0, 0, 3));
    EXPECT_STRFTIME_("01", "%W", make_tm(2026, 1, 5, 0, 0, 0, 1, 4));
    EXPECT_STRFTIME_("01", "%W", make_tm(2026, 1, 6, 0, 0, 0, 2, 5));
    EXPECT_STRFTIME_("01", "%W", make_tm(2026, 1, 7, 0, 0, 0, 3, 6));
    EXPECT_STRFTIME_("01", "%W", make_tm(2026, 1, 8, 0, 0, 0, 4, 7));
    EXPECT_STRFTIME_("00", "%W", make_tm(2021, 1, 1, 0, 0, 0, 5, 0));
    EXPECT_STRFTIME_("00", "%W", make_tm(2021, 1, 2, 0, 0, 0, 6, 1));
    EXPECT_STRFTIME_("00", "%W", make_tm(2021, 1, 3, 0, 0, 0, 0, 2));
    EXPECT_STRFTIME_("01", "%W", make_tm(2021, 1, 4, 0, 0, 0, 1, 3));
    EXPECT_STRFTIME_("01", "%W", make_tm(2021, 1, 5, 0, 0, 0, 2, 4));
    EXPECT_STRFTIME_("01", "%W", make_tm(2021, 1, 6, 0, 0, 0, 3, 5));
    EXPECT_STRFTIME_("01", "%W", make_tm(2021, 1, 7, 0, 0, 0, 4, 6));
    EXPECT_STRFTIME_("01", "%W", make_tm(2021, 1, 8, 0, 0, 0, 5, 7));
    EXPECT_STRFTIME_("00", "%W", make_tm(2022, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("00", "%W", make_tm(2022, 1, 2, 0, 0, 0, 0, 1));
    EXPECT_STRFTIME_("01", "%W", make_tm(2022, 1, 3, 0, 0, 0, 1, 2));
    EXPECT_STRFTIME_("01", "%W", make_tm(2022, 1, 4, 0, 0, 0, 2, 3));
    EXPECT_STRFTIME_("01", "%W", make_tm(2022, 1, 5, 0, 0, 0, 3, 4));
    EXPECT_STRFTIME_("01", "%W", make_tm(2022, 1, 6, 0, 0, 0, 4, 5));
    EXPECT_STRFTIME_("01", "%W", make_tm(2022, 1, 7, 0, 0, 0, 5, 6));
    EXPECT_STRFTIME_("01", "%W", make_tm(2022, 1, 8, 0, 0, 0, 6, 7));
    EXPECT_STRFTIME_("01", "%W", make_tm(1900, 1, 1, 0, 0, 0, 1, 0));
    EXPECT_STRFTIME_("00", "%W", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("09", "%W", make_tm(2000, 2, 29, 23, 59, 59, 2, 59));
    EXPECT_STRFTIME_("10", "%W", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_STRFTIME_("53", "%W", make_tm(2024, 12, 31, 12, 0, 0, 2, 365));
    EXPECT_STRFTIME_("46", "%W", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("52", "%W", make_tm(9999, 12, 31, 23, 59, 59, 5, 364));
}

static void TEST_fast_strftime_WITH_SPECIFIER_y()
{
    EXPECT_STRFTIME_("00", "%y", make_tm(1900, 1, 1, 0, 0, 0, 1, 0));
    EXPECT_STRFTIME_("01", "%y", make_tm(1901, 1, 1, 0, 0, 0, 2, 0));
    EXPECT_STRFTIME_("09", "%y", make_tm(1909, 1, 1, 0, 0, 0, 5, 0));
    EXPECT_STRFTIME_("10", "%y", make_tm(1910, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("70", "%y", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("99", "%y", make_tm(1999, 1, 1, 0, 0, 0, 5, 0));
    EXPECT_STRFTIME_("00", "%y", make_tm(2000, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("05", "%y", make_tm(2005, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("26", "%y", make_tm(2026, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("99", "%y", make_tm(9999, 1, 1, 0, 0, 0, 5, 0));
}

static void TEST_fast_strftime_WITH_SPECIFIER_Y()
{
    EXPECT_STRFTIME_("1900", "%Y", make_tm(1900, 1, 1, 0, 0, 0, 1, 0));
    EXPECT_STRFTIME_("1901", "%Y", make_tm(1901, 1, 1, 0, 0, 0, 2, 0));
    EXPECT_STRFTIME_("1909", "%Y", make_tm(1909, 1, 1, 0, 0, 0, 5, 0));
    EXPECT_STRFTIME_("1910", "%Y", make_tm(1910, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("1970", "%Y", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("1999", "%Y", make_tm(1999, 1, 1, 0, 0, 0, 5, 0));
    EXPECT_STRFTIME_("2000", "%Y", make_tm(2000, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("2005", "%Y", make_tm(2005, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("2026", "%Y", make_tm(2026, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("9999", "%Y", make_tm(9999, 1, 1, 0, 0, 0, 5, 0));
    EXPECT_STRFTIME_("2024", "%Y", make_tm(2024, 12, 31, 12, 0, 0, 2, 365));
}

static void TEST_fast_strftime_WITH_SPECIFIER_D()
{
    EXPECT_STRFTIME_("01/01/70", "%D", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("02/29/00", "%D", make_tm(2000, 2, 29, 23, 59, 59, 2, 59));
    EXPECT_STRFTIME_("03/07/05", "%D", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_STRFTIME_("12/31/24", "%D", make_tm(2024, 12, 31, 12, 0, 0, 2, 365));
    EXPECT_STRFTIME_("11/19/26", "%D", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("12/31/99", "%D", make_tm(9999, 12, 31, 23, 59, 59, 5, 364));
    EXPECT_STRFTIME_("01/01/00", "%D", make_tm(1900, 1, 1, 0, 0, 0, 1, 0));
}

static void TEST_fast_strftime_WITH_SPECIFIER_e()
{
    EXPECT_STRFTIME_(" 1", "%e", make_tm(2026, 1, 1, 13, 45, 7, 4, 0));
    EXPECT_STRFTIME_(" 9", "%e", make_tm(2026, 1, 9, 13, 45, 7, 5, 8));
    EXPECT_STRFTIME_("10", "%e", make_tm(2026, 1, 10, 13, 45, 7, 6, 9));
    EXPECT_STRFTIME_("31", "%e", make_tm(2026, 1, 31, 13, 45, 7, 6, 30));
}

static void TEST_fast_strftime_WITH_SPECIFIER_F()
{
    EXPECT_STRFTIME_("1970-01-01", "%F", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("2000-02-29", "%F", make_tm(2000, 2, 29, 23, 59, 59, 2, 59));
    EXPECT_STRFTIME_("2005-03-07", "%F", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_STRFTIME_("2024-12-31", "%F", make_tm(2024, 12, 31, 12, 0, 0, 2, 365));
    EXPECT_STRFTIME_("2026-11-19", "%F", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("9999-12-31", "%F", make_tm(9999, 12, 31, 23, 59, 59, 5, 364));
    EXPECT_STRFTIME_("1900-01-01", "%F", make_tm(1900, 1, 1, 0, 0, 0, 1, 0));
}

static void TEST_fast_strftime_WITH_SPECIFIER_n()
{
    EXPECT_STRFTIME_("\n",   "%n",   make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("\n\n", "%n%n", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("a\nb", "a%nb", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_SPECIFIER_R()
{
    EXPECT_STRFTIME_("00:00", "%R", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("23:59", "%R", make_tm(2000, 2, 29, 23, 59, 59, 2, 59));
    EXPECT_STRFTIME_("01:02", "%R", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_STRFTIME_("12:00", "%R", make_tm(2024, 12, 31, 12, 0, 0, 2, 365));
    EXPECT_STRFTIME_("13:45", "%R", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("23:59", "%R", make_tm(9999, 12, 31, 23, 59, 59, 5, 364));
}

static void TEST_fast_strftime_WITH_SPECIFIER_t()
{
    EXPECT_STRFTIME_("\t",   "%t",   make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("\t\t", "%t%t", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("a\tb", "a%tb", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_SPECIFIER_T()
{
    EXPECT_STRFTIME_("00:00:00", "%T", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("23:59:59", "%T", make_tm(2000, 2, 29, 23, 59, 59, 2, 59));
    EXPECT_STRFTIME_("01:02:03", "%T", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_STRFTIME_("12:00:00", "%T", make_tm(2024, 12, 31, 12, 0, 0, 2, 365));
    EXPECT_STRFTIME_("13:45:07", "%T", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("23:59:59", "%T", make_tm(9999, 12, 31, 23, 59, 59, 5, 364));
}

static void TEST_fast_strftime_WITH_SPECIFIER_u()
{
    EXPECT_STRFTIME_("7", "%u", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_STRFTIME_("1", "%u", make_tm(2026, 11, 16, 13, 45, 7, 1, 319));
    EXPECT_STRFTIME_("2", "%u", make_tm(2026, 11, 17, 13, 45, 7, 2, 320));
    EXPECT_STRFTIME_("3", "%u", make_tm(2026, 11, 18, 13, 45, 7, 3, 321));
    EXPECT_STRFTIME_("4", "%u", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("5", "%u", make_tm(2026, 11, 20, 13, 45, 7, 5, 323));
    EXPECT_STRFTIME_("6", "%u", make_tm(2026, 11, 21, 13, 45, 7, 6, 324));
}

static void TEST_fast_strftime_WITH_MULTIPLE_SPECIFIERS()
{
    EXPECT_STRFTIME_("2026-11-19 13:45:07",             "%Y-%m-%d %H:%M:%S",     make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("20261119134507",                  "%Y%m%d%H%M%S",          make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("Thu, 19 Nov 2026 13:45:07",       "%a, %d %b %Y %H:%M:%S", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("Thursday, November 19, 2026",     "%A, %B %e, %Y",         make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("[19/11/26]",                      "[%d/%m/%y]",            make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("323/46/46/4/4",                   "%j/%U/%W/%w/%u",        make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("1345",                            "%H%M",                  make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("191919",                          "%d%d%d",                make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("2026 2026",                       "%Y %Y",                 make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("  19  ",                          "  %d  ",                make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("%Y=2026",                         "%%Y=%Y",                make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("Date: 2026-11-19 Time: 13:45:07", "Date: %F Time: %T",     make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_HASH_MODIFIER_ON_NUMERIC_SPECIFIERS()
{
    EXPECT_STRFTIME_("1",  "%#d", make_tm(2026, 1, 1, 13, 45, 7, 4, 0));
    EXPECT_STRFTIME_("9",  "%#d", make_tm(2026, 1, 9, 13, 45, 7, 5, 8));
    EXPECT_STRFTIME_("10", "%#d", make_tm(2026, 1, 10, 13, 45, 7, 6, 9));
    EXPECT_STRFTIME_("31", "%#d", make_tm(2026, 1, 31, 13, 45, 7, 6, 30));
    EXPECT_STRFTIME_("0",  "%#H", make_tm(2026, 11, 19, 0, 45, 7, 4, 322));
    EXPECT_STRFTIME_("9",  "%#H", make_tm(2026, 11, 19, 9, 45, 7, 4, 322));
    EXPECT_STRFTIME_("10", "%#H", make_tm(2026, 11, 19, 10, 45, 7, 4, 322));
    EXPECT_STRFTIME_("23", "%#H", make_tm(2026, 11, 19, 23, 45, 7, 4, 322));
    EXPECT_STRFTIME_("12", "%#I", make_tm(2026, 11, 19, 0, 45, 7, 4, 322));
    EXPECT_STRFTIME_("1",  "%#I", make_tm(2026, 11, 19, 1, 45, 7, 4, 322));
    EXPECT_STRFTIME_("10", "%#I", make_tm(2026, 11, 19, 10, 45, 7, 4, 322));
    EXPECT_STRFTIME_("1",  "%#I", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("1",  "%#m", make_tm(2026, 1, 15, 13, 45, 7, 4, 14));
    EXPECT_STRFTIME_("9",  "%#m", make_tm(2026, 9, 15, 13, 45, 7, 2, 257));
    EXPECT_STRFTIME_("10", "%#m", make_tm(2026, 10, 15, 13, 45, 7, 4, 287));
    EXPECT_STRFTIME_("12", "%#m", make_tm(2026, 12, 15, 13, 45, 7, 2, 348));
    EXPECT_STRFTIME_("0",  "%#M", make_tm(2026, 11, 19, 13, 0, 7, 4, 322));
    EXPECT_STRFTIME_("9",  "%#M", make_tm(2026, 11, 19, 13, 9, 7, 4, 322));
    EXPECT_STRFTIME_("10", "%#M", make_tm(2026, 11, 19, 13, 10, 7, 4, 322));
    EXPECT_STRFTIME_("0",  "%#S", make_tm(2026, 11, 19, 13, 45, 0, 4, 322));
    EXPECT_STRFTIME_("9",  "%#S", make_tm(2026, 11, 19, 13, 45, 9, 4, 322));
    EXPECT_STRFTIME_("10", "%#S", make_tm(2026, 11, 19, 13, 45, 10, 4, 322));
    EXPECT_STRFTIME_("0",  "%#y", make_tm(2000, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("5",  "%#y", make_tm(2005, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_STRFTIME_("26", "%#y", make_tm(2026, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("0",  "%#U", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("9",  "%#U", make_tm(2000, 2, 29, 23, 59, 59, 2, 59));
    EXPECT_STRFTIME_("10", "%#U", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_STRFTIME_("1",  "%#e", make_tm(2026, 1, 1, 13, 45, 7, 4, 0));
    EXPECT_STRFTIME_("9",  "%#e", make_tm(2026, 1, 9, 13, 45, 7, 5, 8));
    EXPECT_STRFTIME_("10", "%#e", make_tm(2026, 1, 10, 13, 45, 7, 6, 9));
    EXPECT_STRFTIME_("31", "%#e", make_tm(2026, 1, 31, 13, 45, 7, 6, 30));
}

static void TEST_fast_strftime_WITH_HASH_MODIFIER_ON_SPECIFIER_j()
{
    EXPECT_STRFTIME_("1",   "%#j", make_tm(2026, 1, 1, 13, 45, 7, 4, 0));
    EXPECT_STRFTIME_("9",   "%#j", make_tm(2026, 1, 9, 13, 45, 7, 5, 8));
    EXPECT_STRFTIME_("11",  "%#j", make_tm(2026, 1, 11, 13, 45, 7, 0, 10));
    EXPECT_STRFTIME_("31",  "%#j", make_tm(2026, 1, 31, 13, 45, 7, 6, 30));
    EXPECT_STRFTIME_("99",  "%#j", make_tm(2026, 4, 9, 13, 45, 7, 4, 98));
    EXPECT_STRFTIME_("100", "%#j", make_tm(2026, 4, 10, 13, 45, 7, 5, 99));
    EXPECT_STRFTIME_("323", "%#j", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("366", "%#j", make_tm(2024, 12, 31, 13, 45, 7, 2, 365));
}

static void TEST_fast_strftime_WITH_HASH_MODIFIER_ON_COMPOSITE_SPECIFIERS()
{
    EXPECT_STRFTIME_("1970-1-1",   "%#F", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("2005-3-7",   "%#F", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_STRFTIME_("2026-11-19", "%#F", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("2024-12-31", "%#F", make_tm(2024, 12, 31, 12, 0, 0, 2, 365));
    EXPECT_STRFTIME_("0:0:0",    "%#T", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_STRFTIME_("1:2:3",    "%#T", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_STRFTIME_("13:45:7",  "%#T", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("23:59:59", "%#T", make_tm(2000, 2, 29, 23, 59, 59, 2, 59));
}

static void TEST_fast_strftime_WITH_HASH_MODIFIER_ON_UNAFFECTED_SPECIFIERS()
{
    EXPECT_STRFTIME_("Thu",      "%#a", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("Thursday", "%#A", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("Nov",      "%#b", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("November", "%#B", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("Nov",      "%#h", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("\n",       "%#n", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("\t",       "%#t", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("4",        "%#u", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("4",        "%#w", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_("2026",     "%#Y", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_BUFFER_OF_EXACT_FIT()
{
    EXPECT_STRFTIME_EXACT_FIT_("abc",        "abc",      make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("%",          "%%",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("Thu",        "%a",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("Wednesday",  "%A",       make_tm(2026, 11, 18, 13, 45, 7, 3, 321));
    EXPECT_STRFTIME_EXACT_FIT_("Nov",        "%b",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("September",  "%B",       make_tm(2026, 9, 15, 13, 45, 7, 2, 257));
    EXPECT_STRFTIME_EXACT_FIT_("20",         "%C",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("19",         "%d",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("11/19/26",   "%D",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("19",         "%e",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("2026-11-19", "%F",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("Nov",        "%h",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("13",         "%H",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("01",         "%I",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("323",        "%j",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("11",         "%m",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("45",         "%M",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("\n",         "%n",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("13:45",      "%R",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("07",         "%S",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("\t",         "%t",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("13:45:07",   "%T",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("4",          "%u",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("46",         "%U",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("4",          "%w",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("46",         "%W",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("26",         "%y",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("2026",       "%Y",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("2026-11-19", "%Y-%m-%d", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_EXACT_FIT_("13:45:07",   "%H:%M:%S", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_BUFFER_ONE_ELEMENT_TOO_SMALL()
{
    EXPECT_STRFTIME_ONE_TOO_SMALL_("abc",        "abc",      make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("%",          "%%",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("Thu",        "%a",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("Wednesday",  "%A",       make_tm(2026, 11, 18, 13, 45, 7, 3, 321));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("Nov",        "%b",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("September",  "%B",       make_tm(2026, 9, 15, 13, 45, 7, 2, 257));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("20",         "%C",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("19",         "%d",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("11/19/26",   "%D",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("19",         "%e",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("2026-11-19", "%F",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("Nov",        "%h",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("13",         "%H",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("01",         "%I",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("323",        "%j",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("11",         "%m",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("45",         "%M",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("\n",         "%n",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("13:45",      "%R",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("07",         "%S",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("\t",         "%t",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("13:45:07",   "%T",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("4",          "%u",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("46",         "%U",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("4",          "%w",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("46",         "%W",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("26",         "%y",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("2026",       "%Y",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("2026-11-19", "%Y-%m-%d", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_STRFTIME_ONE_TOO_SMALL_("13:45:07",   "%H:%M:%S", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_wcsftime_WITH_LITERAL_ONLY_FORMAT()
{
    EXPECT_WCSFTIME_(L"",    L"",    make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"abc", L"abc", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"a#b", L"a#b", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_wcsftime_WITH_SPECIFIER_percent()
{
    EXPECT_WCSFTIME_(L"%",    L"%%",    make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"100%", L"100%%", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"%d",   L"%%d",   make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_wcsftime_WITH_NAME_SPECIFIERS()
{
    EXPECT_WCSFTIME_(L"Sun",       L"%a", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_WCSFTIME_(L"Thu",       L"%a", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"Sunday",    L"%A", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_WCSFTIME_(L"Wednesday", L"%A", make_tm(2026, 11, 18, 13, 45, 7, 3, 321));
    EXPECT_WCSFTIME_(L"Saturday",  L"%A", make_tm(2026, 11, 21, 13, 45, 7, 6, 324));
    EXPECT_WCSFTIME_(L"Jan",       L"%b", make_tm(2026, 1, 15, 13, 45, 7, 4, 14));
    EXPECT_WCSFTIME_(L"Nov",       L"%b", make_tm(2026, 11, 15, 13, 45, 7, 0, 318));
    EXPECT_WCSFTIME_(L"February",  L"%B", make_tm(2026, 2, 15, 13, 45, 7, 0, 45));
    EXPECT_WCSFTIME_(L"September", L"%B", make_tm(2026, 9, 15, 13, 45, 7, 2, 257));
    EXPECT_WCSFTIME_(L"Dec",       L"%h", make_tm(2026, 12, 15, 13, 45, 7, 2, 348));
}

static void TEST_fast_wcsftime_WITH_NUMERIC_SPECIFIERS()
{
    EXPECT_WCSFTIME_(L"20",   L"%C", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"19",   L"%d", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"13",   L"%H", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"01",   L"%I", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"323",  L"%j", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"11",   L"%m", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"45",   L"%M", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"07",   L"%S", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"46",   L"%U", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"4",    L"%w", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"46",   L"%W", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"26",   L"%y", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"2026", L"%Y", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"366",  L"%j", make_tm(2024, 12, 31, 12, 0, 0, 2, 365));
    EXPECT_WCSFTIME_(L"12",   L"%I", make_tm(2026, 11, 19, 0, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"05",   L"%y", make_tm(2005, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_WCSFTIME_(L"01",   L"%U", make_tm(2023, 1, 1, 0, 0, 0, 0, 0));
    EXPECT_WCSFTIME_(L"53",   L"%W", make_tm(2024, 12, 31, 12, 0, 0, 2, 365));
}

static void TEST_fast_wcsftime_WITH_COMPOSITE_SPECIFIERS()
{
    EXPECT_WCSFTIME_(L"11/19/26",   L"%D", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"19",         L"%e", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"2026-11-19", L"%F", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"13:45",      L"%R", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"13:45:07",   L"%T", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"4",          L"%u", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"\n",         L"%n", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"\t",         L"%t", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"03/07/05",   L"%D", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_WCSFTIME_(L" 1",         L"%e", make_tm(2026, 1, 1, 13, 45, 7, 4, 0));
    EXPECT_WCSFTIME_(L"00:00:00",   L"%T", make_tm(1970, 1, 1, 0, 0, 0, 4, 0));
}

static void TEST_fast_wcsftime_WITH_MULTIPLE_SPECIFIERS()
{
    EXPECT_WCSFTIME_(L"2026-11-19 13:45:07",         L"%Y-%m-%d %H:%M:%S",     make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"Thu, 19 Nov 2026 13:45:07",   L"%a, %d %b %Y %H:%M:%S", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"Thursday, November 19, 2026", L"%A, %B %e, %Y",         make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"%Y=2026",                     L"%%Y=%Y",                make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_wcsftime_WITH_HASH_MODIFIER()
{
    EXPECT_WCSFTIME_(L"1",        L"%#d", make_tm(2026, 1, 1, 13, 45, 7, 4, 0));
    EXPECT_WCSFTIME_(L"1",        L"%#e", make_tm(2026, 1, 1, 13, 45, 7, 4, 0));
    EXPECT_WCSFTIME_(L"0",        L"%#H", make_tm(2026, 11, 19, 0, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"12",       L"%#I", make_tm(2026, 11, 19, 0, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"1",        L"%#m", make_tm(2026, 1, 15, 13, 45, 7, 4, 14));
    EXPECT_WCSFTIME_(L"5",        L"%#y", make_tm(2005, 1, 1, 0, 0, 0, 6, 0));
    EXPECT_WCSFTIME_(L"1",        L"%#j", make_tm(2026, 1, 1, 0, 0, 0, 4, 0));
    EXPECT_WCSFTIME_(L"323",      L"%#j", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_(L"2005-3-7", L"%#F", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_WCSFTIME_(L"1:2:3",    L"%#T", make_tm(2005, 3, 7, 1, 2, 3, 1, 65));
    EXPECT_WCSFTIME_(L"Thu",      L"%#a", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_wcsftime_WITH_BUFFER_OF_EXACT_FIT()
{
    EXPECT_WCSFTIME_EXACT_FIT_(L"abc",        L"abc",      make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_EXACT_FIT_(L"%",          L"%%",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_EXACT_FIT_(L"Thu",        L"%a",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_EXACT_FIT_(L"Wednesday",  L"%A",       make_tm(2026, 11, 18, 13, 45, 7, 3, 321));
    EXPECT_WCSFTIME_EXACT_FIT_(L"September",  L"%B",       make_tm(2026, 9, 15, 13, 45, 7, 2, 257));
    EXPECT_WCSFTIME_EXACT_FIT_(L"19",         L"%d",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_EXACT_FIT_(L"2026-11-19", L"%F",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_EXACT_FIT_(L"323",        L"%j",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_EXACT_FIT_(L"13:45:07",   L"%T",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_EXACT_FIT_(L"2026",       L"%Y",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_EXACT_FIT_(L"2026-11-19", L"%Y-%m-%d", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_wcsftime_WITH_BUFFER_ONE_ELEMENT_TOO_SMALL()
{
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"abc",        L"abc",      make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"%",          L"%%",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"Thu",        L"%a",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"Wednesday",  L"%A",       make_tm(2026, 11, 18, 13, 45, 7, 3, 321));
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"September",  L"%B",       make_tm(2026, 9, 15, 13, 45, 7, 2, 257));
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"19",         L"%d",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"2026-11-19", L"%F",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"323",        L"%j",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"13:45:07",   L"%T",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"2026",       L"%Y",       make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
    EXPECT_WCSFTIME_ONE_TOO_SMALL_(L"2026-11-19", L"%Y-%m-%d", make_tm(2026, 11, 19, 13, 45, 7, 4, 322));
}

static void TEST_fast_strftime_WITH_WIDE_OVERLOAD()
{
    struct tm const tm_nominal = make_tm(2026, 11, 19, 13, 45, 7, 4, 322);

    {
        wchar_t         buff[32];
        size_t const    n       =   stlsoft::fast_strftime(&buff[0], STLSOFT_NUM_ELEMENTS(buff), L"%Y-%m-%d", &tm_nominal);

        TEST_INT_EQ(static_cast<size_t>(10), n);
        TEST_WS_EQ(L"2026-11-19", &buff[0]);
    }

    {
        wchar_t         buff[32];
        size_t const    n       =   stlsoft::fast_strftime(&buff[0], STLSOFT_NUM_ELEMENTS(buff), L"%a, %d %b %Y", &tm_nominal);

        TEST_INT_EQ(static_cast<size_t>(16), n);
        TEST_WS_EQ(L"Thu, 19 Nov 2026", &buff[0]);
    }

    {
        wchar_t         buff[10];
        size_t const    n       =   stlsoft::fast_strftime(&buff[0], STLSOFT_NUM_ELEMENTS(buff), L"%Y-%m-%d", &tm_nominal);

        TEST_INT_EQ(static_cast<size_t>(0), n);
    }
}

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

static void TEST_fast_strftime_WITH_ARRAY_OVERLOAD()
{
    struct tm const tm_nominal = make_tm(2026, 11, 19, 13, 45, 7, 4, 322);

    {
        char            buff[32];
        size_t const    n       =   stlsoft::fast_strftime(buff, "%Y-%m-%d", &tm_nominal);

        TEST_INT_EQ(static_cast<size_t>(10), n);
        TEST_MS_EQ("2026-11-19", &buff[0]);
    }

    {
        char            buff[11];
        size_t const    n       =   stlsoft::fast_strftime(buff, "%Y-%m-%d", &tm_nominal);

        TEST_INT_EQ(static_cast<size_t>(10), n);
        TEST_MS_EQ("2026-11-19", &buff[0]);
    }

    {
        char            buff[10];
        size_t const    n       =   stlsoft::fast_strftime(buff, "%Y-%m-%d", &tm_nominal);

        TEST_INT_EQ(static_cast<size_t>(0), n);
    }
}

static void TEST_fast_strftime_WITH_WIDE_ARRAY_OVERLOAD()
{
    struct tm const tm_nominal = make_tm(2026, 11, 19, 13, 45, 7, 4, 322);

    {
        wchar_t         buff[32];
        size_t const    n       =   stlsoft::fast_strftime(buff, L"%Y-%m-%d", &tm_nominal);

        TEST_INT_EQ(static_cast<size_t>(10), n);
        TEST_WS_EQ(L"2026-11-19", &buff[0]);
    }

    {
        wchar_t         buff[11];
        size_t const    n       =   stlsoft::fast_strftime(buff, L"%Y-%m-%d", &tm_nominal);

        TEST_INT_EQ(static_cast<size_t>(10), n);
        TEST_WS_EQ(L"2026-11-19", &buff[0]);
    }

    {
        wchar_t         buff[10];
        size_t const    n       =   stlsoft::fast_strftime(buff, L"%Y-%m-%d", &tm_nominal);

        TEST_INT_EQ(static_cast<size_t>(0), n);
    }
}
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */

