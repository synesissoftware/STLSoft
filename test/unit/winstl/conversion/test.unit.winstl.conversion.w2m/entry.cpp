/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.conversion.w2m/entry.cpp
 *
 * Purpose: Unit-tests for `conversion`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/conversion/char_conversions.hpp>

#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>

namespace {

static void test_multibyte2wide_roundtrip(void);
static void test_wide2multibyte_roundtrip(void);

} // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.conversion.w2m", verbosity))
    {
        XTESTS_RUN_CASE(test_multibyte2wide_roundtrip);
        XTESTS_RUN_CASE(test_wide2multibyte_roundtrip);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_multibyte2wide_roundtrip(void)
{
    char const mb[] = "hello";
    winstl::multibyte2wide<64> conv(mb);

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(conv));
    TEST_INT_EQ(5, static_cast<int>(stlsoft::c_str_len(conv)));
    TEST_MS_EQ("hello", stlsoft::c_str_ptr_a(conv));
}

static void test_wide2multibyte_roundtrip(void)
{
    wchar_t const w[] = L"world";
    winstl::wide2multibyte<64> conv(w);

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(conv));
    TEST_INT_EQ(5, static_cast<int>(stlsoft::c_str_len(conv)));
    TEST_MS_EQ("world", stlsoft::c_str_ptr_a(conv));
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
