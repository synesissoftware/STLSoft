/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/util/string.snprintf/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::snprintf`, `stlsoft::snwprintf`.
 *
 * Created: 23rd March 2025
 * Updated: 9th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/util/string/snprintf.h>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/util/dimensionof.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    /*
     * - stlsoft_C_snprintf(char*, size_t, char const*, ...);
     * - stlsoft_C_snprintf(char[N], char const*, ...);
     *
     * - stlsoft::snprintf(char*, size_t, char const*, ...);
     * - stlsoft::snprintf(char[N], char const*, ...);
     */

    static void TEST_stlsoft_C_snprintf_3();
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
    static void TEST_stlsoft_C_snprintf_2();
#endif
    static void TEST_snprintf_3();
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
    static void TEST_snprintf_2();
#endif
    static void TEST_stlsoft_C_snprintf_truncate();
    static void TEST_snprintf_truncate();
#ifdef STLSOFT_vsnwprintf_SUPPORT
    static void TEST_stlsoft_C_snwprintf();
    static void TEST_snwprintf();
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
    static void TEST_stlsoft_C_snwprintf_array();
    static void TEST_snwprintf_array();
# endif
#endif /* STLSOFT_vsnwprintf_SUPPORT */
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.string.snprintf", verbosity))
    {
        XTESTS_RUN_CASE(TEST_stlsoft_C_snprintf_3);
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
        XTESTS_RUN_CASE(TEST_stlsoft_C_snprintf_2);
#endif
        XTESTS_RUN_CASE(TEST_snprintf_3);
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
        XTESTS_RUN_CASE(TEST_snprintf_2);
#endif
        XTESTS_RUN_CASE(TEST_stlsoft_C_snprintf_truncate);
        XTESTS_RUN_CASE(TEST_snprintf_truncate);
#ifdef STLSOFT_vsnwprintf_SUPPORT
        XTESTS_RUN_CASE(TEST_stlsoft_C_snwprintf);
        XTESTS_RUN_CASE(TEST_snwprintf);
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
        XTESTS_RUN_CASE(TEST_stlsoft_C_snwprintf_array);
        XTESTS_RUN_CASE(TEST_snwprintf_array);
# endif
#endif /* STLSOFT_vsnwprintf_SUPPORT */

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::stlsoft_C_snprintf;


static void TEST_stlsoft_C_snprintf_3()
{
    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, dimensionof(buff), "");

        XTESTS_REQUIRE(TEST_INT_EQ(0, r));
        TEST_CHAR_EQ('\0', buff[0]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, dimensionof(buff), "%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, dimensionof(buff), "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }
}
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

static void TEST_stlsoft_C_snprintf_2()
{
    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, "");

        XTESTS_REQUIRE(TEST_INT_EQ(0, r));
        TEST_CHAR_EQ('\0', buff[0]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, "%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }
}
#endif

static void TEST_snprintf_3()
{
    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, dimensionof(buff), "");

        XTESTS_REQUIRE(TEST_INT_EQ(0, r));
        TEST_CHAR_EQ('\0', buff[0]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, dimensionof(buff), "%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, dimensionof(buff), "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }
}
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

static void TEST_snprintf_2()
{
    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, "");

        // fprintf(stderr, "%s:%d:%s: buff='%.*s'\n", __STLSOFT_FILE_LINE_FUNCTION__, r, buff);

        XTESTS_REQUIRE(TEST_INT_EQ(0, r));
        TEST_CHAR_EQ('\0', buff[0]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, "%d", 123);

        // fprintf(stderr, "%s:%d:%s: buff='%.*s'\n", __STLSOFT_FILE_LINE_FUNCTION__, r, buff);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, "%s", "123");

        // fprintf(stderr, "%s:%d:%s: buff='%.*s'\n", __STLSOFT_FILE_LINE_FUNCTION__, r, buff);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }
}
#endif

/*
 * Same truncation contract as stlsoft_C_vsnprintf: C99 reports the
 * would-be length; MSVC 14.00+ _TRUNCATE reports -1 and writes a NUL;
 * earlier MSVC _vsnprintf reports a negative value and need not write a
 * NUL.
 */

#if defined(STLSOFT_COMPILER_IS_MSVC) && _MSC_VER >= 1400

# define EXPECT_TRUNC_RETURN_(would_be, r)  TEST_INT_EQ(-1, (r))
# define EXPECT_TRUNC_NUL_(buf, n)          TEST_CHAR_EQ('\0', (buf)[(n) - 1])

#elif defined(STLSOFT_COMPILER_IS_MSVC)

# define EXPECT_TRUNC_RETURN_(would_be, r)  TEST_INT_LT(0, (r))
# define EXPECT_TRUNC_NUL_(buf, n)          ((void)(0))

#else /* ? compiler */

# define EXPECT_TRUNC_RETURN_(would_be, r)  TEST_INT_EQ((would_be), (r))
# define EXPECT_TRUNC_NUL_(buf, n)          TEST_CHAR_EQ('\0', (buf)[(n) - 1])

#endif /* compiler */


static void TEST_stlsoft_C_snprintf_truncate()
{
    {
        char        buff[4] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, 4, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[3] = { '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, 3, "%s", "123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
        EXPECT_TRUNC_NUL_(buff, 3);
#if !defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1400
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
#endif
    }

    {
        char        buff[1] = { '~', };
        int const   r = stlsoft_C_snprintf(buff, 1, "%s", "123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
        EXPECT_TRUNC_NUL_(buff, 1);
    }

#if !defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1400
    {
        int const   r = stlsoft_C_snprintf(NULL, 0, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    }
#else
    {
        char        buff[1] = { '~', };
        int const   r = stlsoft_C_snprintf(buff, 0, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_LT(0, r));
        TEST_CHAR_EQ('~', buff[0]);
    }
#endif
}

static void TEST_snprintf_truncate()
{
    {
        char        buff[3] = { '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, 3, "%d", 123);

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
        EXPECT_TRUNC_NUL_(buff, 3);
#if !defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1400
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
#endif
    }

    {
        char        buff[1] = { '~', };
        int const   r = stlsoft::snprintf(buff, 1, "%d", 123);

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
        EXPECT_TRUNC_NUL_(buff, 1);
    }

#if !defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1400
    {
        int const   r = stlsoft::snprintf(NULL, 0, "%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    }
#endif
}

#ifdef STLSOFT_vsnwprintf_SUPPORT

using stlsoft::stlsoft_C_snwprintf;


static void TEST_stlsoft_C_snwprintf()
{
    {
        wchar_t     buff[8] = { L'~', L'~', L'~', L'~', };
        int const   r = stlsoft_C_snwprintf(buff, 8, L"%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_INT_EQ(static_cast<int>(L'1'), static_cast<int>(buff[0]));
        TEST_INT_EQ(static_cast<int>(L'2'), static_cast<int>(buff[1]));
        TEST_INT_EQ(static_cast<int>(L'3'), static_cast<int>(buff[2]));
        TEST_INT_EQ(static_cast<int>(L'\0'), static_cast<int>(buff[3]));
    }

    {
        wchar_t     buff[4] = { L'~', L'~', L'~', L'~', };
        int const   r = stlsoft_C_snwprintf(buff, 4, L"%s", L"123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_INT_EQ(static_cast<int>(L'1'), static_cast<int>(buff[0]));
        TEST_INT_EQ(static_cast<int>(L'2'), static_cast<int>(buff[1]));
        TEST_INT_EQ(static_cast<int>(L'3'), static_cast<int>(buff[2]));
        TEST_INT_EQ(static_cast<int>(L'\0'), static_cast<int>(buff[3]));
    }

    {
        wchar_t     buff[3] = { L'~', L'~', L'~', };
        int const   r = stlsoft_C_snwprintf(buff, 3, L"%s", L"123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
#if _MSC_VER >= 1400
        TEST_INT_EQ(static_cast<int>(L'1'), static_cast<int>(buff[0]));
        TEST_INT_EQ(static_cast<int>(L'2'), static_cast<int>(buff[1]));
        TEST_INT_EQ(static_cast<int>(L'\0'), static_cast<int>(buff[2]));
#endif
    }

    {
        wchar_t     buff[1] = { L'~', };
        int const   r = stlsoft_C_snwprintf(buff, 1, L"%s", L"123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
#if _MSC_VER >= 1400
        TEST_INT_EQ(static_cast<int>(L'\0'), static_cast<int>(buff[0]));
#endif
    }

#if _MSC_VER >= 1400
    {
        int const   r = stlsoft_C_snwprintf(NULL, 0, L"%s", L"123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    }
#endif
}

static void TEST_snwprintf()
{
    {
        wchar_t     buff[8] = { L'~', L'~', L'~', L'~', };
        int const   r = stlsoft::snwprintf(buff, 8, L"%s", L"123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_INT_EQ(static_cast<int>(L'1'), static_cast<int>(buff[0]));
        TEST_INT_EQ(static_cast<int>(L'2'), static_cast<int>(buff[1]));
        TEST_INT_EQ(static_cast<int>(L'3'), static_cast<int>(buff[2]));
        TEST_INT_EQ(static_cast<int>(L'\0'), static_cast<int>(buff[3]));
    }

    {
        wchar_t     buff[3] = { L'~', L'~', L'~', };
        int const   r = stlsoft::snwprintf(buff, 3, L"%d", 123);

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
#if _MSC_VER >= 1400
        TEST_INT_EQ(static_cast<int>(L'1'), static_cast<int>(buff[0]));
        TEST_INT_EQ(static_cast<int>(L'2'), static_cast<int>(buff[1]));
        TEST_INT_EQ(static_cast<int>(L'\0'), static_cast<int>(buff[2]));
#endif
    }
}

# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

static void TEST_stlsoft_C_snwprintf_array()
{
    wchar_t     buff[8] = { L'~', L'~', L'~', L'~', };
    int const   r = stlsoft_C_snwprintf(buff, L"%d", 123);

    XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    TEST_INT_EQ(static_cast<int>(L'1'), static_cast<int>(buff[0]));
    TEST_INT_EQ(static_cast<int>(L'2'), static_cast<int>(buff[1]));
    TEST_INT_EQ(static_cast<int>(L'3'), static_cast<int>(buff[2]));
    TEST_INT_EQ(static_cast<int>(L'\0'), static_cast<int>(buff[3]));
}

static void TEST_snwprintf_array()
{
    wchar_t     buff[8] = { L'~', L'~', L'~', L'~', };
    int const   r = stlsoft::snwprintf(buff, L"%s", L"123");

    XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    TEST_INT_EQ(static_cast<int>(L'1'), static_cast<int>(buff[0]));
    TEST_INT_EQ(static_cast<int>(L'2'), static_cast<int>(buff[1]));
    TEST_INT_EQ(static_cast<int>(L'3'), static_cast<int>(buff[2]));
    TEST_INT_EQ(static_cast<int>(L'\0'), static_cast<int>(buff[3]));
}
# endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
#endif /* STLSOFT_vsnwprintf_SUPPORT */
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
