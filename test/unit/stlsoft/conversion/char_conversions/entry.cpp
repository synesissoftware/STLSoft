/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/conversion/char_conversions/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::multibyte2wide` and
 *          `stlsoft::wide2multibyte`.
 *
 * Created: 28th October 2026
 * Updated: 29th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/conversion/char_conversions.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/error/conversion_error.hpp>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_ASCII();
    static void TEST_EMPTY();
    static void TEST_COUNTED();
    static void TEST_ROUND_TRIP();
    static void TEST_LONGER_THAN_INTERNAL_BUFFER();
    static void TEST_MULTIBYTE_REJECTION();
    static void TEST_WIDE_REJECTION();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.char_conversions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_ASCII);
        XTESTS_RUN_CASE(TEST_EMPTY);
        XTESTS_RUN_CASE(TEST_COUNTED);
        XTESTS_RUN_CASE(TEST_ROUND_TRIP);
        XTESTS_RUN_CASE(TEST_LONGER_THAN_INTERNAL_BUFFER);
        XTESTS_RUN_CASE(TEST_MULTIBYTE_REJECTION);
        XTESTS_RUN_CASE(TEST_WIDE_REJECTION);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static size_t crt_mbstowcs_(wchar_t* dest, char const* src, size_t n)
{
#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

    size_t  numConverted = 0;
    int     err;

    err = ::mbstowcs_s(&numConverted, dest, n, src, _TRUNCATE);

    if (0 != err)
    {
        return static_cast<size_t>(-1);
    }

    if (0 != numConverted)
    {
        --numConverted;
    }

    return numConverted;
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

    return ::mbstowcs(dest, src, n);
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
}

static size_t crt_wcstombs_(char* dest, wchar_t const* src, size_t n)
{
#ifdef STLSOFT_USING_SAFE_STR_FUNCTIONS

    size_t  numConverted = 0;
    int     err;

    err = ::wcstombs_s(&numConverted, dest, n, src, _TRUNCATE);

    if (0 != err)
    {
        return static_cast<size_t>(-1);
    }

    if (0 != numConverted)
    {
        --numConverted;
    }

    return numConverted;
#else /* ? STLSOFT_USING_SAFE_STR_FUNCTIONS */

    return ::wcstombs(dest, src, n);
#endif /* STLSOFT_USING_SAFE_STR_FUNCTIONS */
}

static void TEST_ASCII()
{
    stlsoft::multibyte2wide<64> const wide("hello");
    stlsoft::wide2multibyte<64> const narrow(L"hello");

    TEST_WS_EQ(L"hello", wide.c_str());
    TEST_INT_EQ(5u, wide.size());
    TEST_WS_EQ(L"hello", stlsoft::c_str_data_w(wide));
    TEST_WS_EQ(L"hello", stlsoft::c_str_ptr_w(wide));
    TEST_INT_EQ(5u, stlsoft::c_str_len_w(wide));

    TEST_MS_EQ("hello", narrow.c_str());
    TEST_INT_EQ(5u, narrow.size());
    TEST_MS_EQ("hello", stlsoft::c_str_data_a(narrow));
    TEST_MS_EQ("hello", stlsoft::c_str_ptr_a(narrow));
    TEST_INT_EQ(5u, stlsoft::c_str_len_a(narrow));
}

static void TEST_EMPTY()
{
    stlsoft::multibyte2wide<64> const wide("");
    stlsoft::wide2multibyte<64> const narrow(L"");

    TEST_WS_EQ(L"", wide.c_str());
    TEST_INT_EQ(0u, wide.size());
    TEST_MS_EQ("", narrow.c_str());
    TEST_INT_EQ(0u, narrow.size());
}

static void TEST_COUNTED()
{
    stlsoft::multibyte2wide<64> const wide("hello", 2u);
    stlsoft::wide2multibyte<64> const narrow(L"hello", 2u);

    TEST_WS_EQ(L"he", wide.c_str());
    TEST_INT_EQ(2u, wide.size());
    TEST_MS_EQ("he", narrow.c_str());
    TEST_INT_EQ(2u, narrow.size());
}

static void TEST_ROUND_TRIP()
{
    stlsoft::multibyte2wide<64> const wide("hello");
    stlsoft::wide2multibyte<64> const back(wide.c_str());

    TEST_MS_EQ("hello", back.c_str());
    TEST_INT_EQ(5u, back.size());
}

static void TEST_LONGER_THAN_INTERNAL_BUFFER()
{
    char const src_m[] =
        "0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123";
    wchar_t const src_w[] =
        L"0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123";

    stlsoft::multibyte2wide<64> const wide(src_m);
    stlsoft::wide2multibyte<64> const narrow(src_w);

    TEST_INT_EQ(::strlen(src_m), wide.size());
    TEST_WS_EQ(src_w, wide.c_str());
    TEST_INT_EQ(::wcslen(src_w), narrow.size());
    TEST_MS_EQ(src_m, narrow.c_str());
}

static void TEST_MULTIBYTE_REJECTION()
{
    char const bad[] = "\xff";
    wchar_t scratch[8];
    size_t const n = crt_mbstowcs_(scratch, bad, STLSOFT_NUM_ELEMENTS(scratch));

    if (static_cast<size_t>(-1) == n)
    {
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT

        bool threw = true;

        try
        {
            stlsoft::multibyte2wide<16> const conv(bad);

            threw = false;

            STLSOFT_SUPPRESS_UNUSED(conv);
        }
        catch (stlsoft::conversion_error const&)
        {}

        TEST_BOOLEAN_TRUE(threw);
#else /* ? STLSOFT_CF_EXCEPTION_SUPPORT */

        stlsoft::multibyte2wide<16> const conv(bad);

        TEST_WS_EQ(L"", conv.c_str());
        TEST_INT_EQ(0u, conv.size());
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
    }
    else
    {
        stlsoft::multibyte2wide<16> const conv(bad);

        if (n < STLSOFT_NUM_ELEMENTS(scratch))
        {
            scratch[n] = L'\0';
        }

        TEST_WS_EQ(scratch, conv.c_str());
    }
}

static void TEST_WIDE_REJECTION()
{
    wchar_t const bad[] = { static_cast<wchar_t>(0xDC00), L'\0' };
    char scratch[8];
    size_t const n = crt_wcstombs_(scratch, bad, STLSOFT_NUM_ELEMENTS(scratch));

    if (static_cast<size_t>(-1) == n)
    {
#ifdef STLSOFT_CF_EXCEPTION_SUPPORT

        bool threw = true;

        try
        {
            stlsoft::wide2multibyte<16> const conv(bad);

            threw = false;

            STLSOFT_SUPPRESS_UNUSED(conv);
        }
        catch (stlsoft::conversion_error const&)
        {}

        TEST_BOOLEAN_TRUE(threw);
#else /* ? STLSOFT_CF_EXCEPTION_SUPPORT */

        stlsoft::wide2multibyte<16> const conv(bad);

        TEST_MS_EQ("", conv.c_str());
        TEST_INT_EQ(0u, conv.size());
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
    }
    else
    {
        stlsoft::wide2multibyte<16> const conv(bad);

        if (n < STLSOFT_NUM_ELEMENTS(scratch))
        {
            scratch[n] = '\0';
        }

        TEST_MS_EQ(scratch, conv.c_str());
    }
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

