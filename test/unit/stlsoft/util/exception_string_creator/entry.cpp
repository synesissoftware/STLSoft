/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.exception_string_creator/entry.cpp
 *
 * Purpose: Unit-tests for wide append on `stlsoft::exception_string_creator`.
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

#include <stlsoft/util/exception_string_creator.hpp>

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
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_APPEND_WIDE_STRING();
    static void TEST_APPEND_WIDE_AFTER_NARROW();
    static void TEST_APPEND_WIDE_CHARACTER();
    static void TEST_APPEND_WIDE_COUNTED();
    static void TEST_CREATE_FROM_WIDE();
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

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.exception_string_creator", verbosity))
    {
        XTESTS_RUN_CASE(TEST_APPEND_WIDE_STRING);
        XTESTS_RUN_CASE(TEST_APPEND_WIDE_AFTER_NARROW);
        XTESTS_RUN_CASE(TEST_APPEND_WIDE_CHARACTER);
        XTESTS_RUN_CASE(TEST_APPEND_WIDE_COUNTED);
        XTESTS_RUN_CASE(TEST_CREATE_FROM_WIDE);
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

static void TEST_APPEND_WIDE_STRING()
{
    stlsoft::exception_string_creator creator;

    creator.append(L"wide");

    TEST_MS_EQ("wide", creator.c_str());
    TEST_INT_EQ(4u, creator.size());
}

static void TEST_APPEND_WIDE_AFTER_NARROW()
{
    stlsoft::exception_string_creator creator;

    creator.append("pre-");
    creator.append(L"wide");

    TEST_MS_EQ("pre-wide", creator.c_str());
    TEST_INT_EQ(8u, creator.size());
}

static void TEST_APPEND_WIDE_CHARACTER()
{
    stlsoft::exception_string_creator creator;

    creator.append(L'Q');

    TEST_MS_EQ("Q", creator.c_str());
    TEST_INT_EQ(1u, creator.size());
}

static void TEST_APPEND_WIDE_COUNTED()
{
    stlsoft::exception_string_creator creator;

    creator.append(L"abcd", 2u);

    TEST_MS_EQ("ab", creator.c_str());
    TEST_INT_EQ(2u, creator.size());
}

static void TEST_CREATE_FROM_WIDE()
{
    stlsoft::exception_string_creator creator;

    creator.append(L"wide");

    stlsoft::exception_string const xs = creator.create();

    TEST_MS_EQ("wide", xs.c_str());
    TEST_INT_EQ(4u, xs.size());
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
            stlsoft::exception_string_creator creator;

            creator.append(bad);

            threw = false;
        }
        catch (stlsoft::conversion_error const&)
        {}

        TEST_BOOLEAN_TRUE(threw);
#else /* ? STLSOFT_CF_EXCEPTION_SUPPORT */

        stlsoft::exception_string_creator creator;

        creator.append(bad);

        TEST_INT_EQ(0u, creator.size());
#endif /* STLSOFT_CF_EXCEPTION_SUPPORT */
    }
    else
    {
        stlsoft::exception_string_creator creator;

        if (n < STLSOFT_NUM_ELEMENTS(scratch))
        {
            scratch[n] = '\0';
        }

        creator.append(bad);

        TEST_MS_EQ(scratch, creator.c_str());
    }
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

