/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/string/error/strerror/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft_C_strerror().
 *
 * Created: 1st November 2026
 * Updated: 1st November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/error/strerror.h>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <xtests/terse-api.h>
#include <xtests/xtests.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>


#define TEST_CHAR_EQ_(expected, actual)                                 \
                                                                        \
    TEST_INT_EQ(static_cast<int>(expected), static_cast<int>(actual))


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void fill_(char* p, size_t n, char ch);
    static char const* call_strerror_(int e);

#if !defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)
    static void TEST_RETURNS_STRERROR();
    static void TEST_REQUIRED_IS_STRLEN();
    static void TEST_STORES_LEADING_NUL();
    static void TEST_ZERO_CAPACITY_REPORTS_SIZE_INCLUDING_NUL();
    static void TEST_NULL_REQUIRED_POINTER();
    static void TEST_NULL_DEST_ZERO_CAPACITY();
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */
    static void TEST_SECURE_ZERO_CAPACITY_REPORTS_SIZE_INCLUDING_NUL();
    static void TEST_SECURE_NULL_DEST_ZERO_CAPACITY();
    static void TEST_SECURE_FIT_REPORTS_STRLEN();
    static void TEST_SECURE_TRUNCATION_REPORTS_FULL_STRLEN();
    static void TEST_SECURE_NULL_REQUIRED_STILL_TRUNCATION();
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
#if !defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)
        XTESTS_RUN_CASE(TEST_RETURNS_STRERROR);
        XTESTS_RUN_CASE(TEST_REQUIRED_IS_STRLEN);
        XTESTS_RUN_CASE(TEST_STORES_LEADING_NUL);
        XTESTS_RUN_CASE(TEST_ZERO_CAPACITY_REPORTS_SIZE_INCLUDING_NUL);
        XTESTS_RUN_CASE(TEST_NULL_REQUIRED_POINTER);
        XTESTS_RUN_CASE(TEST_NULL_DEST_ZERO_CAPACITY);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */
        XTESTS_RUN_CASE(TEST_SECURE_ZERO_CAPACITY_REPORTS_SIZE_INCLUDING_NUL);
        XTESTS_RUN_CASE(TEST_SECURE_NULL_DEST_ZERO_CAPACITY);
        XTESTS_RUN_CASE(TEST_SECURE_FIT_REPORTS_STRLEN);
        XTESTS_RUN_CASE(TEST_SECURE_TRUNCATION_REPORTS_FULL_STRLEN);
        XTESTS_RUN_CASE(TEST_SECURE_NULL_REQUIRED_STILL_TRUNCATION);
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */

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

    static void fill_(char* p, size_t n, char ch)
    {
        for (size_t i = 0; i != n; ++i)
        {
            p[i] = ch;
        }
    }

    static char const* call_strerror_(int e)
    {
#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4996)
#endif /* _MSC_VER */

        char const* const r = ::strerror(e);

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

#if !defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)
static void TEST_RETURNS_STRERROR()
{
    char                dest[8];
    size_t              required = 99;

    fill_(dest, 8, '#');

    char const* const r = stlsoft_C_strerror(EINVAL, 8, dest, &required);
    char const* const expected = call_strerror_(EINVAL);

    TEST_PTR_EQ(expected, r);
    TEST_MS_EQ("Invalid argument", r);
}

static void TEST_REQUIRED_IS_STRLEN()
{
    char                dest[8];
    size_t              required = 99;

    fill_(dest, 8, '#');

    char const* const r = stlsoft_C_strerror(ENOENT, 8, dest, &required);

    TEST_PTR_EQ(call_strerror_(ENOENT), r);
    TEST_MS_EQ("No such file or directory", r);
    TEST_INT_EQ(static_cast<int>(::strlen(r)), static_cast<int>(required));
}

static void TEST_STORES_LEADING_NUL()
{
    char                dest[4];
    size_t              required = 99;

    fill_(dest, 4, '#');

    char const* const r = stlsoft_C_strerror(EINVAL, 4, dest, &required);

    TEST_PTR_NE(dest, r);
    TEST_CHAR_EQ_(0, dest[0]);
    TEST_CHAR_EQ_('#', dest[1]);
    TEST_CHAR_EQ_('#', dest[2]);
    TEST_CHAR_EQ_('#', dest[3]);
    TEST_INT_EQ(static_cast<int>(::strlen(r)), static_cast<int>(required));
}

static void TEST_ZERO_CAPACITY_REPORTS_SIZE_INCLUDING_NUL()
{
    char                dest[4];
    size_t              required = 99;

    fill_(dest, 4, '#');

    char const* const r = stlsoft_C_strerror(EINVAL, 0, dest, &required);

    TEST_PTR_EQ(call_strerror_(EINVAL), r);
    TEST_MS_EQ("Invalid argument", r);
    TEST_INT_EQ(static_cast<int>(::strlen(r) + 1), static_cast<int>(required));
    TEST_CHAR_EQ_('#', dest[0]);
    TEST_CHAR_EQ_('#', dest[1]);
    TEST_CHAR_EQ_('#', dest[2]);
    TEST_CHAR_EQ_('#', dest[3]);
}

static void TEST_NULL_REQUIRED_POINTER()
{
    char                dest[4];

    fill_(dest, 4, '#');

    char const* const r = stlsoft_C_strerror(EINVAL, 4, dest, NULL);

    TEST_PTR_EQ(call_strerror_(EINVAL), r);
    TEST_CHAR_EQ_(0, dest[0]);
    TEST_CHAR_EQ_('#', dest[1]);
}

static void TEST_NULL_DEST_ZERO_CAPACITY()
{
    size_t              required = 99;

    char const* const r = stlsoft_C_strerror(EINVAL, 0, NULL, &required);

    TEST_PTR_EQ(call_strerror_(EINVAL), r);
    TEST_MS_EQ("Invalid argument", r);
    TEST_INT_EQ(static_cast<int>(::strlen(r) + 1), static_cast<int>(required));
}

#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

static void TEST_SECURE_ZERO_CAPACITY_REPORTS_SIZE_INCLUDING_NUL()
{
    char                dest[4];
    size_t              required = 99;
    char const* const   expected = call_strerror_(EINVAL);

    fill_(dest, 4, '#');

    char const* const r = stlsoft_C_strerror(EINVAL, 0, dest, &required);

    TEST_PTR_NOT_NULL(r);
    TEST_MS_EQ("", r);
    TEST_MS_EQ("Invalid argument", expected);
    TEST_INT_EQ(static_cast<int>(::strlen(expected) + 1), static_cast<int>(required));
    TEST_CHAR_EQ_('#', dest[0]);
    TEST_CHAR_EQ_('#', dest[1]);
    TEST_CHAR_EQ_('#', dest[2]);
    TEST_CHAR_EQ_('#', dest[3]);
}

static void TEST_SECURE_NULL_DEST_ZERO_CAPACITY()
{
    size_t              required = 99;
    char const* const   expected = call_strerror_(EINVAL);

    char const* const r = stlsoft_C_strerror(EINVAL, 0, NULL, &required);

    TEST_PTR_NOT_NULL(r);
    TEST_MS_EQ("", r);
    TEST_INT_EQ(static_cast<int>(::strlen(expected) + 1), static_cast<int>(required));
}

static void TEST_SECURE_FIT_REPORTS_STRLEN()
{
    char                dest[256];
    char                oracle[256];
    size_t              required = 0;
    char const* const   expected = call_strerror_(EINVAL);

    fill_(dest, 256, '#');
    fill_(oracle, 256, '#');

    char const* const r = stlsoft_C_strerror(EINVAL, 256, dest, &required);

    TEST_PTR_EQ(dest, r);
    TEST_MS_EQ(expected, dest);

    int const length = static_cast<int>(::strlen(expected));

    TEST_INT_EQ(length, static_cast<int>(required));
    TEST_CHAR_EQ_('#', dest[length + 1]);

    errno_t const se = ::strerror_s(oracle, 256, EINVAL);

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(0, ::memcmp(oracle, dest, 256));
}

static void TEST_SECURE_TRUNCATION_REPORTS_FULL_STRLEN()
{
    char                dest[4];
    char                oracle[4];
    size_t              required = 0;
    char const* const   expected = call_strerror_(EINVAL);

    fill_(dest, 4, '#');
    fill_(oracle, 4, '#');

    char const* const r = stlsoft_C_strerror(EINVAL, 4, dest, &required);

    TEST_PTR_EQ(dest, r);
    TEST_INT_EQ(static_cast<int>(::strlen(expected)), static_cast<int>(required));
    TEST_CHAR_EQ_(0, dest[3]);
    TEST_CHAR_EQ_(expected[0], dest[0]);
    TEST_CHAR_EQ_(expected[1], dest[1]);
    TEST_CHAR_EQ_(expected[2], dest[2]);

    errno_t const se = ::strerror_s(oracle, 4, EINVAL);

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(0, ::memcmp(oracle, dest, 4));
}

static void TEST_SECURE_NULL_REQUIRED_STILL_TRUNCATION()
{
    char                dest[4];
    char                oracle[4];
    char const* const   expected = call_strerror_(EINVAL);

    fill_(dest, 4, '#');
    fill_(oracle, 4, '#');

    char const* const r = stlsoft_C_strerror(EINVAL, 4, dest, NULL);

    TEST_PTR_EQ(dest, r);
    TEST_CHAR_EQ_(0, dest[3]);
    TEST_CHAR_EQ_(expected[0], dest[0]);
    TEST_CHAR_EQ_(expected[1], dest[1]);
    TEST_CHAR_EQ_(expected[2], dest[2]);

    errno_t const se = ::strerror_s(oracle, 4, EINVAL);

    TEST_INT_EQ(0, se);
    TEST_INT_EQ(0, ::memcmp(oracle, dest, 4));
}
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
