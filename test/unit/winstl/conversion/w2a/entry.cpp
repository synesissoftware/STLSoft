/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/winstl/conversion/w2a/entry.cpp
 *
 * Purpose: Unit-tests for `conversion`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <winstl/conversion/char_conversions.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_MULTIBYTE2WIDE_ROUNDTRIP();
    static void TEST_WIDE2MULTIBYTE_ROUNDTRIP();
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
        XTESTS_RUN_CASE(TEST_MULTIBYTE2WIDE_ROUNDTRIP);
        XTESTS_RUN_CASE(TEST_WIDE2MULTIBYTE_ROUNDTRIP);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_MULTIBYTE2WIDE_ROUNDTRIP()
{
    char const mb[] = "hello";
    winstl::multibyte2wide<64> conv(mb);

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(conv));
    TEST_INT_EQ(5, static_cast<int>(stlsoft::c_str_len(conv)));
    TEST_BOOLEAN_TRUE(0 == ::wcscmp(L"hello", stlsoft::c_str_ptr_w(conv)));
}

static void TEST_WIDE2MULTIBYTE_ROUNDTRIP()
{
    wchar_t const w[] = L"world";
    winstl::wide2multibyte<64> conv(w);

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr(conv));
    TEST_INT_EQ(5, static_cast<int>(stlsoft::c_str_len(conv)));
    TEST_MS_EQ("world", stlsoft::c_str_ptr_a(conv));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
