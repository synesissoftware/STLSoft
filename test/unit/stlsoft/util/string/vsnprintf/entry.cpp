/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/util/string/vsnprintf/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft_C_vsnprintf` and `stlsoft::vsnprintf`.
 *
 * Created: 9th August 2026
 * Updated: 9th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/util/string/vsnprintf.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>

#include <stdarg.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_stlsoft_C_vsnprintf();
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
    static void TEST_stlsoft_C_vsnprintf_array();
#endif
    static void TEST_vsnprintf();
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
    static void TEST_vsnprintf_array();
#endif
#ifdef STLSOFT_vsnwprintf_SUPPORT
    static void TEST_stlsoft_C_vsnwprintf();
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
    static void TEST_stlsoft_C_vsnwprintf_array();
# endif
    static void TEST_vsnwprintf();
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
    static void TEST_vsnwprintf_array();
# endif
#endif /* STLSOFT_vsnwprintf_SUPPORT */
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
        XTESTS_RUN_CASE(TEST_stlsoft_C_vsnprintf);
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
        XTESTS_RUN_CASE(TEST_stlsoft_C_vsnprintf_array);
#endif
        XTESTS_RUN_CASE(TEST_vsnprintf);
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
        XTESTS_RUN_CASE(TEST_vsnprintf_array);
#endif
#ifdef STLSOFT_vsnwprintf_SUPPORT
        XTESTS_RUN_CASE(TEST_stlsoft_C_vsnwprintf);
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
        XTESTS_RUN_CASE(TEST_stlsoft_C_vsnwprintf_array);
# endif
        XTESTS_RUN_CASE(TEST_vsnwprintf);
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
        XTESTS_RUN_CASE(TEST_vsnwprintf_array);
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

using stlsoft::stlsoft_C_vsnprintf;
#ifdef STLSOFT_vsnwprintf_SUPPORT
using stlsoft::stlsoft_C_vsnwprintf;
#endif

/*
 * Truncation return:
 * - C99 vsnprintf: the length that would have been written, excluding NUL;
 * - MSVC _vsnprintf_s(..., _TRUNCATE, ...): -1, and the buffer is
 *   NUL-terminated when cchBuf > 0;
 * - MSVC _vsnprintf (before 14.00): a negative value, and the buffer is
 *   not required to be NUL-terminated.
 *
 * A zero count with a NULL buffer is the C99 / _vsnprintf_s length query.
 * Pre-14.00 _vsnprintf is not asked to do that.
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


static int call_stlsoft_C_vsnprintf(char* buf, size_t n, char const* fmt, ...)
{
    va_list args;
    int     r;

    va_start(args, fmt);

    r = stlsoft_C_vsnprintf(buf, n, fmt, args);

    va_end(args);

    return r;
}

static int call_vsnprintf(char* buf, size_t n, char const* fmt, ...)
{
    va_list args;
    int     r;

    va_start(args, fmt);

    r = stlsoft::vsnprintf(buf, n, fmt, args);

    va_end(args);

    return r;
}

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

template <size_t N>
static int call_stlsoft_C_vsnprintf_n(char (&buf)[N], char const* fmt, ...)
{
    va_list args;
    int     r;

    va_start(args, fmt);

    r = stlsoft_C_vsnprintf(buf, fmt, args);

    va_end(args);

    return r;
}

template <size_t N>
static int call_vsnprintf_n(char (&buf)[N], char const* fmt, ...)
{
    va_list args;
    int     r;

    va_start(args, fmt);

    r = stlsoft::vsnprintf(buf, fmt, args);

    va_end(args);

    return r;
}
#endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */

#ifdef STLSOFT_vsnwprintf_SUPPORT

static int call_stlsoft_C_vsnwprintf(wchar_t* buf, size_t n, wchar_t const* fmt, ...)
{
    va_list args;
    int     r;

    va_start(args, fmt);

    r = stlsoft_C_vsnwprintf(buf, n, fmt, args);

    va_end(args);

    return r;
}

static int call_vsnwprintf(wchar_t* buf, size_t n, wchar_t const* fmt, ...)
{
    va_list args;
    int     r;

    va_start(args, fmt);

    r = stlsoft::vsnwprintf(buf, n, fmt, args);

    va_end(args);

    return r;
}

# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

template <size_t N>
static int call_stlsoft_C_vsnwprintf_n(wchar_t (&buf)[N], wchar_t const* fmt, ...)
{
    va_list args;
    int     r;

    va_start(args, fmt);

    r = stlsoft_C_vsnwprintf(buf, fmt, args);

    va_end(args);

    return r;
}

template <size_t N>
static int call_vsnwprintf_n(wchar_t (&buf)[N], wchar_t const* fmt, ...)
{
    va_list args;
    int     r;

    va_start(args, fmt);

    r = stlsoft::vsnwprintf(buf, fmt, args);

    va_end(args);

    return r;
}
# endif /* STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
#endif /* STLSOFT_vsnwprintf_SUPPORT */


static void TEST_stlsoft_C_vsnprintf()
{
    {
        char        buff[8] = { '~', '~', '~', '~', };
        int const   r = call_stlsoft_C_vsnprintf(buff, 8, "");

        XTESTS_REQUIRE(TEST_INT_EQ(0, r));
        TEST_CHAR_EQ('\0', buff[0]);
    }

    {
        char        buff[8] = { '~', '~', '~', '~', };
        int const   r = call_stlsoft_C_vsnprintf(buff, 8, "%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[4] = { '~', '~', '~', '~', };
        int const   r = call_stlsoft_C_vsnprintf(buff, 4, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[3] = { '~', '~', '~', };
        int const   r = call_stlsoft_C_vsnprintf(buff, 3, "%s", "123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
        EXPECT_TRUNC_NUL_(buff, 3);
#if !defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1400
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
#endif
    }

    {
        char        buff[1] = { '~', };
        int const   r = call_stlsoft_C_vsnprintf(buff, 1, "%s", "123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
        EXPECT_TRUNC_NUL_(buff, 1);
    }

#if !defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1400
    {
        int const   r = call_stlsoft_C_vsnprintf(NULL, 0, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    }
#else
    {
        char        buff[1] = { '~', };
        int const   r = call_stlsoft_C_vsnprintf(buff, 0, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_LT(0, r));
        TEST_CHAR_EQ('~', buff[0]);
    }
#endif
}

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

static void TEST_stlsoft_C_vsnprintf_array()
{
    char        buff[8] = { '~', '~', '~', '~', };
    int const   r = call_stlsoft_C_vsnprintf_n(buff, "%s", "123");

    XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    TEST_CHAR_EQ('1', buff[0]);
    TEST_CHAR_EQ('2', buff[1]);
    TEST_CHAR_EQ('3', buff[2]);
    TEST_CHAR_EQ('\0', buff[3]);
}
#endif

static void TEST_vsnprintf()
{
    {
        char        buff[8] = { '~', '~', '~', '~', };
        int const   r = call_vsnprintf(buff, 8, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[3] = { '~', '~', '~', };
        int const   r = call_vsnprintf(buff, 3, "%s", "123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
        EXPECT_TRUNC_NUL_(buff, 3);
#if !defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1400
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
#endif
    }

#if !defined(STLSOFT_COMPILER_IS_MSVC) || _MSC_VER >= 1400
    {
        int const   r = call_vsnprintf(NULL, 0, "%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    }
#endif
}

#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

static void TEST_vsnprintf_array()
{
    char        buff[8] = { '~', '~', '~', '~', };
    int const   r = call_vsnprintf_n(buff, "%d", 123);

    XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    TEST_CHAR_EQ('1', buff[0]);
    TEST_CHAR_EQ('2', buff[1]);
    TEST_CHAR_EQ('3', buff[2]);
    TEST_CHAR_EQ('\0', buff[3]);
}
#endif

#ifdef STLSOFT_vsnwprintf_SUPPORT

static void TEST_stlsoft_C_vsnwprintf()
{
    {
        wchar_t     buff[8] = { L'~', L'~', L'~', L'~', };
        int const   r = call_stlsoft_C_vsnwprintf(buff, 8, L"%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_INT_EQ(L'1', buff[0]);
        TEST_INT_EQ(L'2', buff[1]);
        TEST_INT_EQ(L'3', buff[2]);
        TEST_INT_EQ(L'\0', buff[3]);
    }

    {
        wchar_t     buff[4] = { L'~', L'~', L'~', L'~', };
        int const   r = call_stlsoft_C_vsnwprintf(buff, 4, L"%s", L"123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_INT_EQ(L'1', buff[0]);
        TEST_INT_EQ(L'2', buff[1]);
        TEST_INT_EQ(L'3', buff[2]);
        TEST_INT_EQ(L'\0', buff[3]);
    }

    {
        wchar_t     buff[3] = { L'~', L'~', L'~', };
        int const   r = call_stlsoft_C_vsnwprintf(buff, 3, L"%s", L"123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
#if _MSC_VER >= 1400
        TEST_INT_EQ(L'\0', buff[2]);
        TEST_INT_EQ(L'1', buff[0]);
        TEST_INT_EQ(L'2', buff[1]);
#endif
    }

    {
        wchar_t     buff[1] = { L'~', };
        int const   r = call_stlsoft_C_vsnwprintf(buff, 1, L"%s", L"123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
#if _MSC_VER >= 1400
        TEST_INT_EQ(L'\0', buff[0]);
#endif
    }

#if _MSC_VER >= 1400
    {
        int const   r = call_stlsoft_C_vsnwprintf(NULL, 0, L"%s", L"123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    }
#endif
}

# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

static void TEST_stlsoft_C_vsnwprintf_array()
{
    wchar_t     buff[8] = { L'~', L'~', L'~', L'~', };
    int const   r = call_stlsoft_C_vsnwprintf_n(buff, L"%d", 123);

    XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    TEST_INT_EQ(L'1', buff[0]);
    TEST_INT_EQ(L'2', buff[1]);
    TEST_INT_EQ(L'3', buff[2]);
    TEST_INT_EQ(L'\0', buff[3]);
}
# endif

static void TEST_vsnwprintf()
{
    {
        wchar_t     buff[8] = { L'~', L'~', L'~', L'~', };
        int const   r = call_vsnwprintf(buff, 8, L"%s", L"123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_INT_EQ(L'1', buff[0]);
        TEST_INT_EQ(L'2', buff[1]);
        TEST_INT_EQ(L'3', buff[2]);
        TEST_INT_EQ(L'\0', buff[3]);
    }

    {
        wchar_t     buff[3] = { L'~', L'~', L'~', };
        int const   r = call_vsnwprintf(buff, 3, L"%s", L"123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
#if _MSC_VER >= 1400
        TEST_INT_EQ(L'\0', buff[2]);
        TEST_INT_EQ(L'1', buff[0]);
        TEST_INT_EQ(L'2', buff[1]);
#endif
    }
}

# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

static void TEST_vsnwprintf_array()
{
    wchar_t     buff[8] = { L'~', L'~', L'~', L'~', };
    int const   r = call_vsnwprintf_n(buff, L"%d", 123);

    XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    TEST_INT_EQ(L'1', buff[0]);
    TEST_INT_EQ(L'2', buff[1]);
    TEST_INT_EQ(L'3', buff[2]);
    TEST_INT_EQ(L'\0', buff[3]);
}
# endif
#endif /* STLSOFT_vsnwprintf_SUPPORT */
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
