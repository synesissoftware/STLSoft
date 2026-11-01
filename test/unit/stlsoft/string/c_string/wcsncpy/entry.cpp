/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/c_string/wcsncpy/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft_C_wcsncpy().
 *
 * Created: 1st November 2026
 * Updated: 1st November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/c_string/wcsncpy.h>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <xtests/terse-api.h>
#include <xtests/xtests.h>

#include <errno.h>
#include <stdlib.h>
#include <wchar.h>


#define TEST_WCHAR_EQ_(expected, actual)                                \
                                                                        \
    TEST_INT_EQ(static_cast<int>(expected), static_cast<int>(actual))


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void fill_(wchar_t* p, size_t n, wchar_t ch);
    static wchar_t* call_wcsncpy_(wchar_t* dest, wchar_t const* src, size_t cchSrc);

    static void TEST_ZERO_CAPACITY_LEAVES_DEST();
    static void TEST_NULL_DEST_ZERO_CAPACITY();
    static void TEST_COUNT_INCLUDES_NUL();
    static void TEST_NON_ASCII();
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)
    static void TEST_SECURE_COUNT_ZERO_STORES_NUL();
    static void TEST_SECURE_COUNT_EXCLUDES_NUL();
    static void TEST_SECURE_DOES_NOT_PAD();
    static void TEST_SECURE_SHORT_BUFFER();
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */
    static void TEST_CLASSIC_COUNT_ZERO_WRITES_NOTHING();
    static void TEST_CLASSIC_COUNT_EXCLUDES_NUL();
    static void TEST_CLASSIC_PADS();
    static void TEST_CLASSIC_IGNORES_SHORT_CAPACITY();
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
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
        XTESTS_RUN_CASE(TEST_ZERO_CAPACITY_LEAVES_DEST);
        XTESTS_RUN_CASE(TEST_NULL_DEST_ZERO_CAPACITY);
        XTESTS_RUN_CASE(TEST_COUNT_INCLUDES_NUL);
        XTESTS_RUN_CASE(TEST_NON_ASCII);
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)
        XTESTS_RUN_CASE(TEST_SECURE_COUNT_ZERO_STORES_NUL);
        XTESTS_RUN_CASE(TEST_SECURE_COUNT_EXCLUDES_NUL);
        XTESTS_RUN_CASE(TEST_SECURE_DOES_NOT_PAD);
        XTESTS_RUN_CASE(TEST_SECURE_SHORT_BUFFER);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */
        XTESTS_RUN_CASE(TEST_CLASSIC_COUNT_ZERO_WRITES_NOTHING);
        XTESTS_RUN_CASE(TEST_CLASSIC_COUNT_EXCLUDES_NUL);
        XTESTS_RUN_CASE(TEST_CLASSIC_PADS);
        XTESTS_RUN_CASE(TEST_CLASSIC_IGNORES_SHORT_CAPACITY);
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace
{

    static void fill_(wchar_t* p, size_t n, wchar_t ch)
    {
        for (size_t i = 0; i != n; ++i)
        {
            p[i] = ch;
        }
    }

    static wchar_t* call_wcsncpy_(wchar_t* dest, wchar_t const* src, size_t cchSrc)
    {
#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif /* _MSC_VER */

        wchar_t* const r = ::wcsncpy(dest, src, cchSrc);

#if defined(_MSC_VER)
# pragma warning(pop)
#endif /* _MSC_VER */

        return r;
    }
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{

static void TEST_ZERO_CAPACITY_LEAVES_DEST()
{
    wchar_t             dest[4];
    wchar_t             classic[4];
    int const           sentinel = 7;

    fill_(dest, 4, L'#');
    fill_(classic, 4, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 0, L"ab", 3);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(L'#', dest[0]);
    TEST_WCHAR_EQ_(L'#', dest[1]);
    TEST_WCHAR_EQ_(L'#', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    wchar_t* const cr = call_wcsncpy_(classic, L"ab", 3);

    TEST_PTR_EQ(classic, cr);
    TEST_WS_EQ(L"ab", classic);
    TEST_WCHAR_EQ_(L'#', dest[0]);
    TEST_WCHAR_EQ_(L'a', classic[0]);
}

static void TEST_NULL_DEST_ZERO_CAPACITY()
{
    int const sentinel = 7;

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(NULL, 0, L"ab", 3);

    TEST_PTR_EQ(NULL, r);
    TEST_INT_EQ(sentinel, errno);
}

static void TEST_COUNT_INCLUDES_NUL()
{
    wchar_t             dest[4];
    wchar_t             classic[4];
    int const           sentinel = 7;

    fill_(dest, 4, L'#');
    fill_(classic, 4, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 4, L"ab", 3);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WS_EQ(L"ab", dest);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    call_wcsncpy_(classic, L"ab", 3);

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 4));

#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

    wchar_t secure[4];

    fill_(secure, 4, L'#');

    errno = sentinel;

    errno_t const se = ::wcsncpy_s(secure, 4, L"ab", 3);

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(sentinel, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 4));
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
}

static void TEST_NON_ASCII()
{
    wchar_t const       src[] = { 0x00E9, L'x', L'\0' };
    wchar_t             dest[4];
    wchar_t             classic[4];
    int const           sentinel = 7;

    fill_(dest, 4, L'#');
    fill_(classic, 4, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 4, src, 3);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(0x00E9, dest[0]);
    TEST_WCHAR_EQ_(L'x', dest[1]);
    TEST_WCHAR_EQ_(L'\0', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    call_wcsncpy_(classic, src, 3);

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 4));

#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

    wchar_t secure[4];

    fill_(secure, 4, L'#');

    errno = sentinel;

    errno_t const se = ::wcsncpy_s(secure, 4, src, 3);

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(sentinel, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 4));
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
}

#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

static void TEST_SECURE_COUNT_ZERO_STORES_NUL()
{
    wchar_t             dest[4];
    wchar_t             secure[4];
    wchar_t             classic[4];
    int const           sentinel = 7;

    fill_(dest, 4, L'#');
    fill_(secure, 4, L'#');
    fill_(classic, 4, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 4, L"ab", 0);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(L'\0', dest[0]);
    TEST_WCHAR_EQ_(L'#', dest[1]);
    TEST_WCHAR_EQ_(L'#', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    errno = sentinel;

    errno_t const se = ::wcsncpy_s(secure, 4, L"ab", 0);

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(sentinel, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 4));

    call_wcsncpy_(classic, L"ab", 0);

    TEST_WCHAR_EQ_(L'#', classic[0]);
    TEST_WCHAR_EQ_(L'\0', dest[0]);
}

static void TEST_SECURE_COUNT_EXCLUDES_NUL()
{
    wchar_t             dest[4];
    wchar_t             secure[4];
    wchar_t             classic[4];
    int const           sentinel = 7;

    fill_(dest, 4, L'#');
    fill_(secure, 4, L'#');
    fill_(classic, 4, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 4, L"ab", 2);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(L'a', dest[0]);
    TEST_WCHAR_EQ_(L'b', dest[1]);
    TEST_WCHAR_EQ_(L'\0', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    errno = sentinel;

    errno_t const se = ::wcsncpy_s(secure, 4, L"ab", 2);

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(sentinel, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 4));

    call_wcsncpy_(classic, L"ab", 2);

    TEST_WCHAR_EQ_(L'a', classic[0]);
    TEST_WCHAR_EQ_(L'b', classic[1]);
    TEST_WCHAR_EQ_(L'#', classic[2]);
    TEST_WCHAR_EQ_(L'\0', dest[2]);
}

static void TEST_SECURE_DOES_NOT_PAD()
{
    wchar_t             dest[6];
    wchar_t             secure[6];
    wchar_t             classic[6];
    int const           sentinel = 7;

    fill_(dest, 6, L'#');
    fill_(secure, 6, L'#');
    fill_(classic, 6, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 6, L"ab", 5);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(L'a', dest[0]);
    TEST_WCHAR_EQ_(L'b', dest[1]);
    TEST_WCHAR_EQ_(L'\0', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);
    TEST_WCHAR_EQ_(L'#', dest[4]);
    TEST_WCHAR_EQ_(L'#', dest[5]);

    errno = sentinel;

    errno_t const se = ::wcsncpy_s(secure, 6, L"ab", 5);

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(sentinel, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 6));

    call_wcsncpy_(classic, L"ab", 5);

    TEST_WCHAR_EQ_(L'\0', classic[2]);
    TEST_WCHAR_EQ_(L'\0', classic[3]);
    TEST_WCHAR_EQ_(L'\0', classic[4]);
    TEST_WCHAR_EQ_(L'#', dest[3]);
}

static void TEST_SECURE_SHORT_BUFFER()
{
    wchar_t             dest[4];
    wchar_t             secure[4];
    int const           sentinel = 7;

    fill_(dest, 4, L'#');
    fill_(secure, 4, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 1, L"ab", 2);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(ERANGE, errno);
    TEST_WCHAR_EQ_(L'\0', dest[0]);
    TEST_WCHAR_EQ_(L'#', dest[1]);
    TEST_WCHAR_EQ_(L'#', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    errno = sentinel;

    errno_t const se = ::wcsncpy_s(secure, 1, L"ab", 2);

    TEST_INT_EQ(ERANGE, se);
    TEST_INT_EQ(ERANGE, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 4));
}

#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

static void TEST_CLASSIC_COUNT_ZERO_WRITES_NOTHING()
{
    wchar_t             dest[4];
    wchar_t             classic[4];
    int const           sentinel = 7;

    fill_(dest, 4, L'#');
    fill_(classic, 4, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 4, L"ab", 0);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(L'#', dest[0]);
    TEST_WCHAR_EQ_(L'#', dest[1]);
    TEST_WCHAR_EQ_(L'#', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    call_wcsncpy_(classic, L"ab", 0);

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 4));
}

static void TEST_CLASSIC_COUNT_EXCLUDES_NUL()
{
    wchar_t             dest[4];
    wchar_t             classic[4];
    int const           sentinel = 7;

    fill_(dest, 4, L'#');
    fill_(classic, 4, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 4, L"ab", 2);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(L'a', dest[0]);
    TEST_WCHAR_EQ_(L'b', dest[1]);
    TEST_WCHAR_EQ_(L'#', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    call_wcsncpy_(classic, L"ab", 2);

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 4));
}

static void TEST_CLASSIC_PADS()
{
    wchar_t             dest[6];
    wchar_t             classic[6];
    int const           sentinel = 7;

    fill_(dest, 6, L'#');
    fill_(classic, 6, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 6, L"ab", 5);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(L'a', dest[0]);
    TEST_WCHAR_EQ_(L'b', dest[1]);
    TEST_WCHAR_EQ_(L'\0', dest[2]);
    TEST_WCHAR_EQ_(L'\0', dest[3]);
    TEST_WCHAR_EQ_(L'\0', dest[4]);
    TEST_WCHAR_EQ_(L'#', dest[5]);

    call_wcsncpy_(classic, L"ab", 5);

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 6));
}

static void TEST_CLASSIC_IGNORES_SHORT_CAPACITY()
{
    wchar_t             dest[8];
    wchar_t             classic[8];
    int const           sentinel = 7;

    fill_(dest, 8, L'#');
    fill_(classic, 8, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsncpy(dest, 1, L"ab", 3);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WS_EQ(L"ab", dest);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    call_wcsncpy_(classic, L"ab", 3);

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 8));
}
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
