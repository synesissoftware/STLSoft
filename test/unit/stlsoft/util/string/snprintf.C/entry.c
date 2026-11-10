/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/util/string/snprintf.C/entry.c
 *
 * Purpose: C unit-tests for `stlsoft_C_snprintf` and `stlsoft_C_snwprintf`.
 *
 * Created: 9th August 2026
 * Updated: 9th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/util/string/snprintf.h>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void TEST_stlsoft_C_snprintf(void);
#ifdef STLSOFT_vsnwprintf_SUPPORT
static void TEST_stlsoft_C_snwprintf(void);
#endif /* STLSOFT_vsnwprintf_SUPPORT */


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
        XTESTS_RUN_CASE(TEST_stlsoft_C_snprintf);
#ifdef STLSOFT_vsnwprintf_SUPPORT
        XTESTS_RUN_CASE(TEST_stlsoft_C_snwprintf);
#endif /* STLSOFT_vsnwprintf_SUPPORT */

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
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


static void TEST_stlsoft_C_snprintf(void)
{
    {
        char        buff[8] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, 8, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[4] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, 4, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
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

#ifdef STLSOFT_vsnwprintf_SUPPORT

static void TEST_stlsoft_C_snwprintf(void)
{
    {
        wchar_t     buff[8] = { L'~', L'~', L'~', L'~', };
        int const   r = stlsoft_C_snwprintf(buff, 8, L"%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_INT_EQ(L'1', buff[0]);
        TEST_INT_EQ(L'2', buff[1]);
        TEST_INT_EQ(L'3', buff[2]);
        TEST_INT_EQ(L'\0', buff[3]);
    }

    {
        wchar_t     buff[3] = { L'~', L'~', L'~', };
        int const   r = stlsoft_C_snwprintf(buff, 3, L"%s", L"123");

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
#if _MSC_VER >= 1400
        TEST_INT_EQ(L'1', buff[0]);
        TEST_INT_EQ(L'2', buff[1]);
        TEST_INT_EQ(L'\0', buff[2]);
#endif
    }

    {
        wchar_t     buff[1] = { L'~', };
        int const   r = stlsoft_C_snwprintf(buff, 1, L"%d", 123);

        XTESTS_REQUIRE(EXPECT_TRUNC_RETURN_(3, r));
#if _MSC_VER >= 1400
        TEST_INT_EQ(L'\0', buff[0]);
#endif
    }

#if _MSC_VER >= 1400
    {
        int const   r = stlsoft_C_snwprintf(NULL, 0, L"%s", L"123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
    }
#endif
}
#endif /* STLSOFT_vsnwprintf_SUPPORT */


/* ///////////////////////////// end of file //////////////////////////// */
