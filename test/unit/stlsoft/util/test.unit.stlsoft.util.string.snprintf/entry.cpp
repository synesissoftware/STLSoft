/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.string.snprintf/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::snprintf`, `stlsoft::snwprintf`.
 *
 * Created: 23rd March 2025
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/util/string/snprintf.h>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/util/dimensionof.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    /*
     * - stlsoft_C_snprintf(char*, size_t, char const*, ...);
     * - stlsoft_C_snprintf(char[N], char const*, ...);
     *
     * - stlsoft::snprintf(char*, size_t, char const*, ...);
     * - stlsoft::snprintf(char[N], char const*, ...);
     */

    static void TEST_stlsoft_C_snprintf_3();
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
    static void TEST_stlsoft_C_snprintf_2();
#endif
    static void TEST_snprintf_3();
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
    static void TEST_snprintf_2();
#endif
}


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.string.snprintf", verbosity))
    {
        XTESTS_RUN_CASE(TEST_stlsoft_C_snprintf_3);
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
        XTESTS_RUN_CASE(TEST_stlsoft_C_snprintf_2);
#endif
        XTESTS_RUN_CASE(TEST_snprintf_3);
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT
        XTESTS_RUN_CASE(TEST_snprintf_2);
#endif

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::stlsoft_C_snprintf;


static void TEST_stlsoft_C_snprintf_3()
{
    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, dimensionof(buff), "");

        XTESTS_REQUIRE(TEST_INT_EQ(0, r));
        TEST_CHAR_EQ('\0', buff[0]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, dimensionof(buff), "%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, dimensionof(buff), "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }
}
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

static void TEST_stlsoft_C_snprintf_2()
{
    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, "");

        XTESTS_REQUIRE(TEST_INT_EQ(0, r));
        TEST_CHAR_EQ('\0', buff[0]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, "%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft_C_snprintf(buff, "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }
}
#endif

static void TEST_snprintf_3()
{
    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, dimensionof(buff), "");

        XTESTS_REQUIRE(TEST_INT_EQ(0, r));
        TEST_CHAR_EQ('\0', buff[0]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, dimensionof(buff), "%d", 123);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, dimensionof(buff), "%s", "123");

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }
}
#ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

static void TEST_snprintf_2()
{
    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, "");

        // fprintf(stderr, "%s:%d:%s: buff='%.*s'\n", __STLSOFT_FILE_LINE_FUNCTION__, r, buff);

        XTESTS_REQUIRE(TEST_INT_EQ(0, r));
        TEST_CHAR_EQ('\0', buff[0]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, "%d", 123);

        // fprintf(stderr, "%s:%d:%s: buff='%.*s'\n", __STLSOFT_FILE_LINE_FUNCTION__, r, buff);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }

    {
        char        buff[101] = { '~', '~', '~', '~', };
        int const   r = stlsoft::snprintf(buff, "%s", "123");

        // fprintf(stderr, "%s:%d:%s: buff='%.*s'\n", __STLSOFT_FILE_LINE_FUNCTION__, r, buff);

        XTESTS_REQUIRE(TEST_INT_EQ(3, r));
        TEST_CHAR_EQ('1', buff[0]);
        TEST_CHAR_EQ('2', buff[1]);
        TEST_CHAR_EQ('3', buff[2]);
        TEST_CHAR_EQ('\0', buff[3]);
    }
}
#endif
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
