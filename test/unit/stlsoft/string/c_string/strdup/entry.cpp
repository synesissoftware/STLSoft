/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/c_string/strdup/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft_C_strdup() and stlsoft_C_wcsdup().
 *
 * Created: 1st November 2026
 * Updated: 1st November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/c_string/strdup.h>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <xtests/terse-api.h>
#include <xtests/xtests.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static char* call_strdup_(char const* src);
    static wchar_t* call_wcsdup_(wchar_t const* src);

    static void TEST_NULL_NARROW();
    static void TEST_NULL_WIDE();
    static void TEST_EMPTY_NARROW();
    static void TEST_EMPTY_WIDE();
    static void TEST_COPIES_NARROW();
    static void TEST_COPIES_WIDE();
    static void TEST_COPY_IS_INDEPENDENT();

    static char* call_strdup_(char const* src)
    {
#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif /* _MSC_VER */

        char* const r = ::strdup(src);

#if defined(_MSC_VER)
# pragma warning(pop)
#endif /* _MSC_VER */

        return r;
    }

    static wchar_t* call_wcsdup_(wchar_t const* src)
    {
#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif /* _MSC_VER */

        wchar_t* const r = ::wcsdup(src);

#if defined(_MSC_VER)
# pragma warning(pop)
#endif /* _MSC_VER */

        return r;
    }
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
        XTESTS_RUN_CASE(TEST_NULL_NARROW);
        XTESTS_RUN_CASE(TEST_NULL_WIDE);
        XTESTS_RUN_CASE(TEST_EMPTY_NARROW);
        XTESTS_RUN_CASE(TEST_EMPTY_WIDE);
        XTESTS_RUN_CASE(TEST_COPIES_NARROW);
        XTESTS_RUN_CASE(TEST_COPIES_WIDE);
        XTESTS_RUN_CASE(TEST_COPY_IS_INDEPENDENT);

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

static void TEST_NULL_NARROW()
{
    int const sentinel = 7;

    errno = sentinel;

    char* const r = stlsoft_C_strdup(NULL);

    TEST_PTR_EQ(NULL, r);
    TEST_INT_EQ(sentinel, errno);
}

static void TEST_NULL_WIDE()
{
    int const sentinel = 7;

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsdup(NULL);

    TEST_PTR_EQ(NULL, r);
    TEST_INT_EQ(sentinel, errno);
}

static void TEST_EMPTY_NARROW()
{
    int const   sentinel = 7;
    char*       oracle = NULL;

    errno = sentinel;

    char* const r = stlsoft_C_strdup("");

    TEST_PTR_NOT_NULL(r);
    TEST_MS_EQ("", r);
    TEST_INT_EQ(sentinel, errno);

    oracle = call_strdup_("");

    TEST_PTR_NOT_NULL(oracle);
    TEST_MS_EQ(oracle, r);

    ::free(oracle);
    ::free(r);
}

static void TEST_EMPTY_WIDE()
{
    int const       sentinel = 7;
    wchar_t*        oracle = NULL;

    errno = sentinel;

    wchar_t* const r = stlsoft_C_wcsdup(L"");

    TEST_PTR_NOT_NULL(r);
    TEST_WS_EQ(L"", r);
    TEST_INT_EQ(sentinel, errno);

    oracle = call_wcsdup_(L"");

    TEST_PTR_NOT_NULL(oracle);
    TEST_WS_EQ(oracle, r);

    ::free(oracle);
    ::free(r);
}

static void TEST_COPIES_NARROW()
{
    char* const r = stlsoft_C_strdup("ab");
    char* const oracle = call_strdup_("ab");

    TEST_PTR_NOT_NULL(r);
    TEST_PTR_NE("ab", r);
    TEST_MS_EQ("ab", r);
    TEST_PTR_NOT_NULL(oracle);
    TEST_MS_EQ(oracle, r);

    ::free(oracle);
    ::free(r);
}

static void TEST_COPIES_WIDE()
{
    wchar_t const   src[] = { 0x00E9, L'x', L'\0' };
    wchar_t* const  r = stlsoft_C_wcsdup(src);
    wchar_t* const  oracle = call_wcsdup_(src);

    TEST_PTR_NOT_NULL(r);
    TEST_PTR_NE(src, r);
    TEST_WS_EQ(src, r);
    TEST_PTR_NOT_NULL(oracle);
    TEST_INT_EQ(0, ::wmemcmp(oracle, r, 3));

    ::free(oracle);
    ::free(r);
}

static void TEST_COPY_IS_INDEPENDENT()
{
    char        src[] = "ab";
    char* const r = stlsoft_C_strdup(src);

    TEST_PTR_NOT_NULL(r);

    src[0] = 'z';

    TEST_MS_EQ("ab", r);
    TEST_MS_EQ("zb", src);

    ::free(r);
}
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
