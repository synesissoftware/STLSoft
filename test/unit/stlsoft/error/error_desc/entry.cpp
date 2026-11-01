/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/error/error_desc/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::error_desc.
 *
 * Created: 28th October 2026
 * Updated: 1st November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/error/error_desc.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/memory/auto_buffer.hpp>

/* Standard C++ header files */
#include <string>

/* Standard C header files */
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_NARROW_ERRNO_0();
    static void TEST_NARROW_EACCES();
    static void TEST_NARROW_EEXIST();
    static void TEST_NARROW_EINVAL();
    static void TEST_NARROW_EIO();
    static void TEST_NARROW_ENOENT();
    static void TEST_NARROW_ENOMEM();
    static void TEST_NARROW_EPERM();
    static void TEST_NARROW_ERANGE();
    static void TEST_NARROW_UNKNOWN();
    static void TEST_NARROW_NEGATIVE();
    static void TEST_NARROW_DEFAULT_USES_ERRNO();
    static void TEST_NARROW_OWNS_COPY();
    static void TEST_NARROW_EQUAL();
#if defined(STLSOFT_COMPILER_IS_CLANG) || \
    defined(STLSOFT_COMPILER_IS_GCC)
    static void TEST_NARROW_COPY();
#endif /* compiler */
    static void TEST_error_desc_WIDE_FALLBACK_MATCHES_NARROW();
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
        XTESTS_RUN_CASE(TEST_NARROW_ERRNO_0);
        XTESTS_RUN_CASE(TEST_NARROW_EACCES);
        XTESTS_RUN_CASE(TEST_NARROW_EEXIST);
        XTESTS_RUN_CASE(TEST_NARROW_EINVAL);
        XTESTS_RUN_CASE(TEST_NARROW_EIO);
        XTESTS_RUN_CASE(TEST_NARROW_ENOENT);
        XTESTS_RUN_CASE(TEST_NARROW_ENOMEM);
        XTESTS_RUN_CASE(TEST_NARROW_EPERM);
        XTESTS_RUN_CASE(TEST_NARROW_ERANGE);
        XTESTS_RUN_CASE(TEST_NARROW_UNKNOWN);
        XTESTS_RUN_CASE(TEST_NARROW_NEGATIVE);
        XTESTS_RUN_CASE(TEST_NARROW_DEFAULT_USES_ERRNO);
        XTESTS_RUN_CASE(TEST_NARROW_OWNS_COPY);
        XTESTS_RUN_CASE(TEST_NARROW_EQUAL);
#if defined(STLSOFT_COMPILER_IS_CLANG) || \
    defined(STLSOFT_COMPILER_IS_GCC)
        XTESTS_RUN_CASE(TEST_NARROW_COPY);
#endif /* compiler */
        XTESTS_RUN_CASE(TEST_error_desc_WIDE_FALLBACK_MATCHES_NARROW);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace {

    static std::string crt_message_(int e)
    {
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS)

        char        buff[1001];
        int const   err = ::strerror_s(buff, STLSOFT_NUM_ELEMENTS(buff), e);

        if (0 != err)
        {
            return std::string();
        }

        return std::string(buff);
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

# if defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 4996)
# endif /* _MSC_VER */

        return std::string(::strerror(e));

# if defined(_MSC_VER)
#  pragma warning(pop)
# endif /* _MSC_VER */
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
    }
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

#if !defined(STLSOFT_USING_SAFE_STR_FUNCTIONS) && \
    !defined(STLSOFT_ERROR_DESC_wcserror)

# define EXPECT_WIDE_ERRNO_(code) \
\
    do \
    { \
        stlsoft::error_desc_a const     narrow_((code)); \
        stlsoft::error_desc_w const     wide_((code)); \
        char const* const               mb_     =   narrow_.c_str(); \
        size_t const                    cch_    =   ::mbstowcs(NULL, mb_, 0); \
\
        TEST_MS_EQ(::strerror((code)), mb_); \
\
        if (static_cast<size_t>(-1) == cch_) \
        { \
            TEST_WS_EQ(L"could not determine error", wide_.c_str()); \
        } \
        else \
        { \
            stlsoft::auto_buffer<wchar_t> expected_(cch_ + 1u); \
\
            TEST_INT_EQ(cch_, ::mbstowcs(expected_.data(), mb_, expected_.size())); \
            TEST_WS_EQ(expected_.data(), wide_.c_str()); \
            TEST_INT_EQ(cch_, wide_.length()); \
        } \
    } while (0)

#endif /* !STLSOFT_USING_SAFE_STR_FUNCTIONS && !STLSOFT_ERROR_DESC_wcserror */

#define EXPECT_NARROW_(code) \
\
    do \
    { \
        stlsoft::error_desc const   ed_((code)); \
        std::string const           crt_(crt_message_((code))); \
\
        TEST_PTR_NOT_NULL(ed_.c_str()); \
        TEST_PTR_EQ(ed_.c_str(), ed_.get_description()); \
        TEST_MS_EQ(crt_.c_str(), ed_.c_str()); \
        TEST_INT_EQ( \
            static_cast<int>(::strlen(ed_.c_str())) \
        ,   static_cast<int>(ed_.length()) \
        ); \
        TEST_INT_EQ( \
            static_cast<int>(ed_.length()) \
        ,   static_cast<int>(ed_.size()) \
        ); \
        TEST_PTR_EQ(ed_.c_str(), stlsoft::c_str_ptr(ed_)); \
        TEST_INT_EQ( \
            static_cast<int>(ed_.length()) \
        ,   static_cast<int>(stlsoft::c_str_len(ed_)) \
        ); \
        TEST_PTR_EQ(ed_.c_str(), stlsoft::c_str_ptr_null(ed_)); \
    } while (0)

namespace {

static void TEST_NARROW_ERRNO_0()
{
    char const* const expecteds[] =
    {
        "No error",
        "Success",
        "Undefined error: 0",
    };

    EXPECT_NARROW_(0);
    TEST_MS_EQ_ANY_OF(expecteds, STLSOFT_NUM_ELEMENTS(expecteds), stlsoft::error_desc(0).c_str());
}

static void TEST_NARROW_EACCES()
{
    EXPECT_NARROW_(EACCES);
    TEST_MS_MATCHES("*ermission denied*", stlsoft::error_desc(EACCES).c_str());
}

static void TEST_NARROW_EEXIST()
{
    EXPECT_NARROW_(EEXIST);
    TEST_MS_MATCHES("*File exists*", stlsoft::error_desc(EEXIST).c_str());
}

static void TEST_NARROW_EINVAL()
{
    EXPECT_NARROW_(EINVAL);
    TEST_MS_MATCHES("*nvalid argument*", stlsoft::error_desc(EINVAL).c_str());
}

static void TEST_NARROW_EIO()
{
    EXPECT_NARROW_(EIO);
    TEST_MS_EQ_ANY_OF2("I/O error", "Input/output error", stlsoft::error_desc(EIO).c_str());
}

static void TEST_NARROW_ENOENT()
{
    EXPECT_NARROW_(ENOENT);
    TEST_MS_MATCHES("*No such file*", stlsoft::error_desc(ENOENT).c_str());
}

static void TEST_NARROW_ENOMEM()
{
    char const* const expecteds[] =
    {
        "Cannot allocate memory",
        "Not enough memory",
        "Not enough space",
    };

    EXPECT_NARROW_(ENOMEM);
    TEST_MS_EQ_ANY_OF(expecteds, STLSOFT_NUM_ELEMENTS(expecteds), stlsoft::error_desc(ENOMEM).c_str());
}

static void TEST_NARROW_EPERM()
{
    EXPECT_NARROW_(EPERM);
    TEST_MS_EQ_ANY_OF2("Not owner", "Operation not permitted", stlsoft::error_desc(EPERM).c_str());
}

static void TEST_NARROW_ERANGE()
{
    EXPECT_NARROW_(ERANGE);
    TEST_MS_EQ_ANY_OF2(
        "Numerical result out of range"
    ,   "Result too large"
    ,   stlsoft::error_desc(ERANGE).c_str()
    );
}

static void TEST_NARROW_UNKNOWN()
{
    int const e = 99999;

    EXPECT_NARROW_(e);
    TEST_MS_MATCHES("*rror*", stlsoft::error_desc(e).c_str());
    TEST_MS_DOES_NOT_MATCH("Success", stlsoft::error_desc(e).c_str());
}

static void TEST_NARROW_NEGATIVE()
{
    EXPECT_NARROW_(-1);
    TEST_MS_MATCHES("*rror*", stlsoft::error_desc(-1).c_str());
}

static void TEST_NARROW_DEFAULT_USES_ERRNO()
{
    errno = ENOENT;

    stlsoft::error_desc const ed;

    TEST_MS_EQ(crt_message_(ENOENT).c_str(), ed.c_str());
    TEST_MS_MATCHES("*No such file*", ed.c_str());
}

static void TEST_NARROW_OWNS_COPY()
{
    std::string const           crt(crt_message_(EINVAL));
    stlsoft::error_desc const   ed(EINVAL);

    TEST_MS_EQ(crt.c_str(), ed.c_str());
    TEST_PTR_NE(crt.c_str(), ed.c_str());
}

static void TEST_NARROW_EQUAL()
{
    stlsoft::error_desc const   ed(ENOENT);
    char const* const           text = ed.c_str();

    TEST_BOOLEAN_TRUE(ed.equal(text));
    TEST_BOOLEAN_FALSE(ed.equal(NULL));
    TEST_BOOLEAN_FALSE(ed.equal("not the message"));
    TEST_BOOLEAN_TRUE(ed == text);
    TEST_BOOLEAN_TRUE(text == ed);
    TEST_BOOLEAN_TRUE(ed != "not the message");
    TEST_BOOLEAN_TRUE("not the message" != ed);
}

#if defined(STLSOFT_COMPILER_IS_CLANG) || \
    defined(STLSOFT_COMPILER_IS_GCC)
static void TEST_NARROW_COPY()
{
    stlsoft::error_desc const   original(ENOENT);
    stlsoft::error_desc const   copy(original);

    TEST_MS_EQ(original.c_str(), copy.c_str());
    TEST_PTR_NE(original.c_str(), copy.c_str());
    TEST_INT_EQ(static_cast<int>(original.length()), static_cast<int>(copy.length()));
}
#endif /* compiler */

static void TEST_error_desc_WIDE_FALLBACK_MATCHES_NARROW()
{
#if defined(STLSOFT_USING_SAFE_STR_FUNCTIONS) || \
    defined(STLSOFT_ERROR_DESC_wcserror)

    /* This build uses _wcserror / _wcserror_s. */
    TEST_PASSED();
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS || STLSOFT_ERROR_DESC_wcserror */

    EXPECT_WIDE_ERRNO_(ENOENT);
    EXPECT_WIDE_ERRNO_(EINVAL);
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS || STLSOFT_ERROR_DESC_wcserror */
}
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
