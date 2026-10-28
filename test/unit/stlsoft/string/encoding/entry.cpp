/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.string.encoding/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft_C_mbstowcs()` and
 *          `stlsoft_C_wcstombs()`.
 *
 * Created: 28th October 2026
 * Updated: 28th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/encoding/mbstowcs.h>
#include <stlsoft/string/encoding/wcstombs.h>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_ASCII();
    static void TEST_PROBE();
    static void TEST_EXACT_FIT();
    static void TEST_COUNTED();
    static void TEST_ZERO_CAPACITY();
    static void TEST_SHORT_BUFFER();
    static void TEST_COUNT_EXCLUDES_NUL();
    static void TEST_MULTIBYTE_REJECTION();
    static void TEST_WIDE_REJECTION();
    static void TEST_CXX_FORWARDS();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.encoding", verbosity))
    {
        XTESTS_RUN_CASE(TEST_ASCII);
        XTESTS_RUN_CASE(TEST_PROBE);
        XTESTS_RUN_CASE(TEST_EXACT_FIT);
        XTESTS_RUN_CASE(TEST_COUNTED);
        XTESTS_RUN_CASE(TEST_ZERO_CAPACITY);
        XTESTS_RUN_CASE(TEST_SHORT_BUFFER);
        XTESTS_RUN_CASE(TEST_COUNT_EXCLUDES_NUL);
        XTESTS_RUN_CASE(TEST_MULTIBYTE_REJECTION);
        XTESTS_RUN_CASE(TEST_WIDE_REJECTION);
        XTESTS_RUN_CASE(TEST_CXX_FORWARDS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_ASCII()
{
    wchar_t wide[32];
    char    narrow[32];

    TEST_INT_EQ(5u, stlsoft_C_mbstowcs(wide, STLSOFT_NUM_ELEMENTS(wide), "hello", 100u));
    TEST_WS_EQ(L"hello", wide);

    TEST_INT_EQ(5u, stlsoft_C_wcstombs(narrow, STLSOFT_NUM_ELEMENTS(narrow), L"hello", 100u));
    TEST_MS_EQ("hello", narrow);
}

static void TEST_PROBE()
{
    TEST_INT_EQ(5u, stlsoft_C_mbstowcs(NULL, 0u, "hello", 0u));
    TEST_INT_EQ(0u, stlsoft_C_mbstowcs(NULL, 0u, "", 0u));

    TEST_INT_EQ(5u, stlsoft_C_wcstombs(NULL, 0u, L"hello", 0u));
    TEST_INT_EQ(0u, stlsoft_C_wcstombs(NULL, 0u, L"", 0u));
}

static void TEST_EXACT_FIT()
{
    wchar_t wide[6];
    char    narrow[6];

    TEST_INT_EQ(5u, stlsoft_C_mbstowcs(wide, STLSOFT_NUM_ELEMENTS(wide), "hello", 5u));
    TEST_WS_EQ(L"hello", wide);

    TEST_INT_EQ(5u, stlsoft_C_wcstombs(narrow, STLSOFT_NUM_ELEMENTS(narrow), L"hello", 5u));
    TEST_MS_EQ("hello", narrow);
}

static void TEST_COUNTED()
{
    wchar_t wide[8];
    char    narrow[8];

    TEST_INT_EQ(2u, stlsoft_C_mbstowcs(wide, STLSOFT_NUM_ELEMENTS(wide), "hello", 2u));
    TEST_WS_EQ(L"he", wide);

    TEST_INT_EQ(2u, stlsoft_C_wcstombs(narrow, STLSOFT_NUM_ELEMENTS(narrow), L"hello", 2u));
    TEST_MS_EQ("he", narrow);
}

static void TEST_ZERO_CAPACITY()
{
    wchar_t wide[8];
    char    narrow[8];

    wide[0] = L'Z';
    narrow[0] = 'Z';

    TEST_INT_EQ(0u, stlsoft_C_mbstowcs(wide, 0u, "hello", 5u));
    TEST_INT_EQ(static_cast<int>(L'Z'), static_cast<int>(wide[0]));

    TEST_INT_EQ(0u, stlsoft_C_wcstombs(narrow, 0u, L"hello", 5u));
    TEST_INT_EQ(static_cast<int>('Z'), static_cast<int>(narrow[0]));

    TEST_INT_EQ(0u, stlsoft_C_mbstowcs(wide, STLSOFT_NUM_ELEMENTS(wide), "hello", 0u));
    TEST_WS_EQ(L"", wide);

    TEST_INT_EQ(0u, stlsoft_C_wcstombs(narrow, STLSOFT_NUM_ELEMENTS(narrow), L"hello", 0u));
    TEST_MS_EQ("", narrow);
}

static void TEST_SHORT_BUFFER()
{
    /* The destination has no spare slot. The classic CRT fills every
     * element and does not write a NUL. The secure CRT keeps a NUL in the
     * last slot, so the count is one smaller.
     */
    wchar_t const   sentinel_w = static_cast<wchar_t>(0xABCDu);
    char const      sentinel_m = '\x7e';
    wchar_t         wide[4];
    char            narrow[4];
    size_t          n;

    wide[3] = sentinel_w;
    narrow[3] = sentinel_m;

    n = stlsoft_C_mbstowcs(wide, 3u, "hello", 5u);

#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

    TEST_INT_EQ(2u, n);
    TEST_WS_EQ(L"he", wide);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

    TEST_INT_EQ(3u, n);
    TEST_INT_EQ(static_cast<int>(L'h'), static_cast<int>(wide[0]));
    TEST_INT_EQ(static_cast<int>(L'e'), static_cast<int>(wide[1]));
    TEST_INT_EQ(static_cast<int>(L'l'), static_cast<int>(wide[2]));
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */

    TEST_INT_EQ(static_cast<int>(sentinel_w), static_cast<int>(wide[3]));

    n = stlsoft_C_wcstombs(narrow, 3u, L"hello", 5u);

#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

    TEST_INT_EQ(2u, n);
    TEST_MS_EQ("he", narrow);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

    TEST_INT_EQ(3u, n);
    TEST_INT_EQ(static_cast<int>('h'), static_cast<int>(narrow[0]));
    TEST_INT_EQ(static_cast<int>('e'), static_cast<int>(narrow[1]));
    TEST_INT_EQ(static_cast<int>('l'), static_cast<int>(narrow[2]));
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */

    TEST_INT_EQ(static_cast<int>(sentinel_m), static_cast<int>(narrow[3]));
}

static void TEST_COUNT_EXCLUDES_NUL()
{
    wchar_t wide[8];
    char    narrow[8];
    size_t  n;

    n = stlsoft_C_mbstowcs(wide, STLSOFT_NUM_ELEMENTS(wide), "hello", 5u);

    TEST_INT_EQ(5u, n);
    TEST_BOOLEAN_TRUE(6u != n);
    TEST_INT_EQ(static_cast<int>(L'\0'), static_cast<int>(wide[5]));

    n = stlsoft_C_wcstombs(narrow, STLSOFT_NUM_ELEMENTS(narrow), L"hello", 5u);

    TEST_INT_EQ(5u, n);
    TEST_BOOLEAN_TRUE(6u != n);
    TEST_INT_EQ(static_cast<int>('\0'), static_cast<int>(narrow[5]));
}

static void TEST_MULTIBYTE_REJECTION()
{
    char const  bad[] = "\xff";
    wchar_t     scratch[8];
    size_t      oracle;

#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

    size_t  numConverted = 0;
    int     err;

    err = ::mbstowcs_s(&numConverted, scratch, STLSOFT_NUM_ELEMENTS(scratch), bad, 1u);
    oracle = (0 == err) ? numConverted - ((0 != numConverted) ? 1u : 0u) : static_cast<size_t>(-1);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

    oracle = ::mbstowcs(scratch, bad, STLSOFT_NUM_ELEMENTS(scratch));
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */

    errno = 0;

    if (static_cast<size_t>(-1) == oracle)
    {
        size_t const n = stlsoft_C_mbstowcs(scratch, STLSOFT_NUM_ELEMENTS(scratch), bad, 1u);

        TEST_BOOLEAN_TRUE(static_cast<size_t>(-1) == n);
        TEST_INT_EQ(EILSEQ, errno);
    }
    else
    {
        wchar_t         actual[8];
        size_t const    n = stlsoft_C_mbstowcs(actual, STLSOFT_NUM_ELEMENTS(actual), bad, 1u);

        TEST_INT_EQ(oracle, n);
        TEST_WS_EQ(scratch, actual);
    }
}

static void TEST_WIDE_REJECTION()
{
    wchar_t const   bad[] = { static_cast<wchar_t>(0xDC00), L'\0' };
    char            scratch[8];
    size_t          oracle;

#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

    size_t  numConverted = 0;
    int     err;

    err = ::wcstombs_s(&numConverted, scratch, STLSOFT_NUM_ELEMENTS(scratch), bad, 1u);
    oracle = (0 == err) ? numConverted - ((0 != numConverted) ? 1u : 0u) : static_cast<size_t>(-1);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

    oracle = ::wcstombs(scratch, bad, STLSOFT_NUM_ELEMENTS(scratch));
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */

    errno = 0;

    if (static_cast<size_t>(-1) == oracle)
    {
        size_t const n = stlsoft_C_wcstombs(scratch, STLSOFT_NUM_ELEMENTS(scratch), bad, 1u);

        TEST_BOOLEAN_TRUE(static_cast<size_t>(-1) == n);
        TEST_INT_EQ(EILSEQ, errno);
    }
    else
    {
        char            actual[8];
        size_t const    n = stlsoft_C_wcstombs(actual, STLSOFT_NUM_ELEMENTS(actual), bad, 1u);

        if (n < STLSOFT_NUM_ELEMENTS(scratch))
        {
            scratch[n] = '\0';
        }

        TEST_INT_EQ(oracle, n);
        TEST_MS_EQ(scratch, actual);
    }
}

static void TEST_CXX_FORWARDS()
{
    wchar_t wide[8];
    char    narrow[8];

    TEST_INT_EQ(5u, stlsoft::encoding::mbstowcs(wide, STLSOFT_NUM_ELEMENTS(wide), "hello", 5u));
    TEST_WS_EQ(L"hello", wide);
    TEST_INT_EQ(5u, stlsoft::encoding::mbstowcs(NULL, 0u, "hello", 0u));

    TEST_INT_EQ(5u, stlsoft::encoding::wcstombs(narrow, STLSOFT_NUM_ELEMENTS(narrow), L"hello", 5u));
    TEST_MS_EQ("hello", narrow);
    TEST_INT_EQ(5u, stlsoft::encoding::wcstombs(NULL, 0u, L"hello", 0u));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

