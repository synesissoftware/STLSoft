/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.error.error_desc/entry.cpp
 *
 * Purpose: Unit-tests for the `stlsoft::error_desc_w` multibyte fallback.
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

/* Standard C header files */
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

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

    if (XTESTS_START_RUNNER("test.unit.stlsoft.error.error_desc", verbosity))
    {
        XTESTS_RUN_CASE(TEST_error_desc_WIDE_FALLBACK_MATCHES_NARROW);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


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

namespace {

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

