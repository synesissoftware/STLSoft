/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/c_string/wcscpy/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft_C_wcscpy().
 *
 * Created: 1st November 2026
 * Updated: 1st November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/c_string/wcscpy.h>


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
    static wchar_t* call_wcscpy_(wchar_t* dest, wchar_t const* src);

    static void TEST_ZERO_CAPACITY_LEAVES_DEST();
    static void TEST_NULL_DEST_ZERO_CAPACITY();
    static void TEST_EMPTY_SOURCE();
    static void TEST_FITS_WITH_SPARE();
    static void TEST_EXACT_FIT();
    static void TEST_NON_ASCII();
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)
    static void TEST_SECURE_SHORT_BUFFER();
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */
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
        XTESTS_RUN_CASE(TEST_EMPTY_SOURCE);
        XTESTS_RUN_CASE(TEST_FITS_WITH_SPARE);
        XTESTS_RUN_CASE(TEST_EXACT_FIT);
        XTESTS_RUN_CASE(TEST_NON_ASCII);
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)
        XTESTS_RUN_CASE(TEST_SECURE_SHORT_BUFFER);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */
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

    static wchar_t* call_wcscpy_(wchar_t* dest, wchar_t const* src)
    {
#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif /* _MSC_VER */

        wchar_t* const r = ::wcscpy(dest, src);

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

    wchar_t* const r = stlsoft_C_wcscpy(dest, 0, L"ab");

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(L'#', dest[0]);
    TEST_WCHAR_EQ_(L'#', dest[1]);
    TEST_WCHAR_EQ_(L'#', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    wchar_t* const cr = call_wcscpy_(classic, L"ab");

    TEST_PTR_EQ(classic, cr);
    TEST_WS_EQ(L"ab", classic);
    TEST_WCHAR_EQ_(L'#', dest[0]);
    TEST_WCHAR_EQ_(L'a', classic[0]);
}

static void TEST_NULL_DEST_ZERO_CAPACITY()
{
    int const sentinel = 7;

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcscpy(NULL, 0, L"ab");

    TEST_PTR_EQ(NULL, r);
    TEST_INT_EQ(sentinel, errno);
}

static void TEST_EMPTY_SOURCE()
{
    wchar_t             dest[4];
    wchar_t             classic[4];
    int const           sentinel = 7;

    fill_(dest, 4, L'#');
    fill_(classic, 4, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcscpy(dest, 4, L"");

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WS_EQ(L"", dest);
    TEST_WCHAR_EQ_(L'#', dest[1]);
    TEST_WCHAR_EQ_(L'#', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    call_wcscpy_(classic, L"");

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 4));
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

    wchar_t secure[4];

    fill_(secure, 4, L'#');

    errno = sentinel;

    errno_t const se = ::wcscpy_s(secure, 4, L"");

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(sentinel, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 4));
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
}

static void TEST_FITS_WITH_SPARE()
{
    wchar_t             dest[8];
    wchar_t             classic[8];
    int const           sentinel = 7;

    fill_(dest, 8, L'#');
    fill_(classic, 8, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcscpy(dest, 8, L"ab");

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WS_EQ(L"ab", dest);
    TEST_WCHAR_EQ_(L'#', dest[3]);
    TEST_WCHAR_EQ_(L'#', dest[7]);

    call_wcscpy_(classic, L"ab");

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 8));
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

    wchar_t secure[8];

    fill_(secure, 8, L'#');

    errno = sentinel;

    errno_t const se = ::wcscpy_s(secure, 8, L"ab");

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(sentinel, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 8));
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
}

static void TEST_EXACT_FIT()
{
    wchar_t             dest[3];
    wchar_t             classic[3];
    int const           sentinel = 7;

    fill_(dest, 3, L'#');
    fill_(classic, 3, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcscpy(dest, 3, L"ab");

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(L'a', dest[0]);
    TEST_WCHAR_EQ_(L'b', dest[1]);
    TEST_WCHAR_EQ_(L'\0', dest[2]);

    call_wcscpy_(classic, L"ab");

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 3));
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

    wchar_t secure[3];

    fill_(secure, 3, L'#');

    errno = sentinel;

    errno_t const se = ::wcscpy_s(secure, 3, L"ab");

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(sentinel, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 3));
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

    wchar_t* const r = stlsoft_C_wcscpy(dest, 4, src);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WCHAR_EQ_(0x00E9, dest[0]);
    TEST_WCHAR_EQ_(L'x', dest[1]);
    TEST_WCHAR_EQ_(L'\0', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    call_wcscpy_(classic, src);

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 4));
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

    wchar_t secure[4];

    fill_(secure, 4, L'#');

    errno = sentinel;

    errno_t const se = ::wcscpy_s(secure, 4, src);

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(sentinel, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 4));
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
}
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

static void TEST_SECURE_SHORT_BUFFER()
{
    wchar_t             dest[4];
    wchar_t             secure[4];
    wchar_t             classic[4];
    int const           sentinel = 7;

    fill_(dest, 4, L'#');
    fill_(secure, 4, L'#');
    fill_(classic, 4, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcscpy(dest, 1, L"ab");

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(ERANGE, errno);
    TEST_WCHAR_EQ_(L'\0', dest[0]);
    TEST_WCHAR_EQ_(L'#', dest[1]);
    TEST_WCHAR_EQ_(L'#', dest[2]);
    TEST_WCHAR_EQ_(L'#', dest[3]);

    errno = sentinel;

    errno_t const se = ::wcscpy_s(secure, 1, L"ab");

    TEST_INT_EQ(ERANGE, se);
    TEST_INT_EQ(ERANGE, errno);
    TEST_INT_EQ(0, ::wmemcmp(secure, dest, 4));

    call_wcscpy_(classic, L"ab");

    TEST_WCHAR_EQ_(L'a', classic[0]);
    TEST_WCHAR_EQ_(L'\0', dest[0]);
}
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

static void TEST_CLASSIC_IGNORES_SHORT_CAPACITY()
{
    wchar_t             dest[8];
    wchar_t             classic[8];
    int const           sentinel = 7;

    fill_(dest, 8, L'#');
    fill_(classic, 8, L'#');

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcscpy(dest, 1, L"ab");

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(sentinel, errno);
    TEST_WS_EQ(L"ab", dest);
    TEST_WCHAR_EQ_(L'#', dest[3]);
    TEST_WCHAR_EQ_(L'#', dest[7]);

    call_wcscpy_(classic, L"ab");

    TEST_INT_EQ(0, ::wmemcmp(classic, dest, 8));
}
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
