/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.util.struct_comparers/entry.cpp
 *
 * Purpose: Component test for `winstl::struct_comparers`.
 *
 * Created: 9th October 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/util/struct_comparers.hpp>

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <winstl/util/struct_initialisers.hpp>

/* Standard C header files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_FILETIME();
    static void test_SYSTEMTIME();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.util.struct_comparers", verbosity))
    {
        XTESTS_RUN_CASE(test_FILETIME);
        XTESTS_RUN_CASE(test_SYSTEMTIME);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::ss_size_t;

static void test_FILETIME()
{
    {
        FILETIME ft1 = {0, 0};
        FILETIME ft2 = {0, 0};

        TEST_BOOLEAN_TRUE(winstl::equal_struct(ft1, ft2));
    }

    {
        FILETIME ft1 = {0, 0};
        FILETIME ft2 = {0, 1};

        TEST_BOOLEAN_FALSE(winstl::equal_struct(ft1, ft2));
    }
}

static void test_SYSTEMTIME()
{
    {
        SYSTEMTIME st1;
        SYSTEMTIME st2;

        winstl::init_struct(st1);
        winstl::init_struct(st2);

        TEST_BOOLEAN_TRUE(winstl::equal_struct(st1, st2));
    }

    {
        SYSTEMTIME st1;
        SYSTEMTIME st2;

        winstl::init_struct(st1);
        winstl::init_struct(st2);

        st1.wDayOfWeek = 1;
        st2.wDayOfWeek = 2;

        TEST_BOOLEAN_TRUE(winstl::equal_struct(st1, st2));
    }

#if __cplusplus >= 202002L

    {
        SYSTEMTIME st1 = {
            .wYear = 2024,
            .wMonth = 10,
            .wDayOfWeek = 3,
            .wDay = 9,
            .wHour = 19,
            .wMinute = 59,
            .wSecond = 33,
            .wMilliseconds = 1001,
        };
        SYSTEMTIME st2 = {
            .wYear = 2024,
            .wMonth = 10,
            .wDayOfWeek = 13,
            .wDay = 9,
            .wHour = 19,
            .wMinute = 59,
            .wSecond = 33,
            .wMilliseconds = 1001,
        };

        TEST_BOOLEAN_TRUE(winstl::equal_struct(st1, st2));
    }
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
