/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.api.external.string/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/api/external/string.h` case-insensitive
 *          aliases (`STLSOFT_API_EXTERNAL_string_stricmp` and kin).
 *
 * Created: 17th September 2026
 * Updated: 17th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/api/external/string.h>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static bool is_required_case_insensitive_alias_host_();

    static void TEST_stricmp_IS_DEFINED_ON_REQUIRED_HOSTS();
    static void TEST_wcsicmp_IS_DEFINED_ON_REQUIRED_HOSTS();
    static void TEST_strnicmp_IS_DEFINED();
    static void TEST_wcsnicmp_IS_DEFINED();

    static void TEST_stricmp_BEHAVIOUR();
    static void TEST_wcsicmp_BEHAVIOUR();
    static void TEST_strnicmp_BEHAVIOUR();
    static void TEST_wcsnicmp_BEHAVIOUR();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.api.external.string", verbosity))
    {
        XTESTS_RUN_CASE(TEST_stricmp_IS_DEFINED_ON_REQUIRED_HOSTS);
        XTESTS_RUN_CASE(TEST_wcsicmp_IS_DEFINED_ON_REQUIRED_HOSTS);
        XTESTS_RUN_CASE(TEST_strnicmp_IS_DEFINED);
        XTESTS_RUN_CASE(TEST_wcsnicmp_IS_DEFINED);

        XTESTS_RUN_CASE(TEST_stricmp_BEHAVIOUR);
        XTESTS_RUN_CASE(TEST_wcsicmp_BEHAVIOUR);
        XTESTS_RUN_CASE(TEST_strnicmp_BEHAVIOUR);
        XTESTS_RUN_CASE(TEST_wcsnicmp_BEHAVIOUR);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

/* The supported matrix for which case-insensitive full-string aliases must
 * be defined: Linux, macOS, and Windows; with Clang, GCC, MSVC, or MinGW.
 *
 * Notes:
 * - Apple Clang and LLVM Clang set STLSOFT_COMPILER_IS_CLANG;
 * - MinGW is recognised as STLSOFT_COMPILER_IS_GCC (+ STLSOFT_MINGW);
 * - MSVC sets STLSOFT_COMPILER_IS_MSVC.
 */
static bool
is_required_case_insensitive_alias_host_()
{
#if 0
#elif defined(STLSOFT_COMPILER_IS_CLANG) ||\
      defined(STLSOFT_COMPILER_IS_GCC) ||\
      defined(STLSOFT_COMPILER_IS_MSVC)

# if 0
# elif defined(_WIN32) ||\
       defined(__APPLE__) ||\
       defined(__linux__) ||\
       defined(__linux) ||\
       defined(linux)

    return true;
# else

    return false;
# endif
#else

    return false;
#endif
}


static void TEST_stricmp_IS_DEFINED_ON_REQUIRED_HOSTS()
{
    if (!is_required_case_insensitive_alias_host_())
    {
        TEST_PASSED();
        return;
    }

#if 0
#elif defined(STLSOFT_API_EXTERNAL_string_stricmp)

    TEST_PASSED();
#else

    TEST_FAIL_WITH_QUALIFIER(
        "required case-insensitive string alias is not defined on this host (Linux/macOS/Windows with Clang, GCC, MSVC, or MinGW)"
    ,   "STLSOFT_API_EXTERNAL_string_stricmp"
    );
#endif
}

static void TEST_wcsicmp_IS_DEFINED_ON_REQUIRED_HOSTS()
{
    if (!is_required_case_insensitive_alias_host_())
    {
        TEST_PASSED();
        return;
    }

#if 0
#elif defined(STLSOFT_API_EXTERNAL_string_wcsicmp)

    TEST_PASSED();
#else

    TEST_FAIL_WITH_QUALIFIER(
        "required case-insensitive string alias is not defined on this host (Linux/macOS/Windows with Clang, GCC, MSVC, or MinGW)"
    ,   "STLSOFT_API_EXTERNAL_string_wcsicmp"
    );
#endif
}

static void TEST_strnicmp_IS_DEFINED()
{
    /* Always required: either a native alias or the stlsoft_C_strnicmp
     * software fallback in stlsoft/api/external/string.h.
     */

#if 0
#elif defined(STLSOFT_API_EXTERNAL_string_strnicmp)

    TEST_PASSED();
#else

    TEST_FAIL("STLSOFT_API_EXTERNAL_string_strnicmp must always be defined");
#endif
}

static void TEST_wcsnicmp_IS_DEFINED()
{
#if 0
#elif defined(STLSOFT_API_EXTERNAL_string_wcsnicmp)

    TEST_PASSED();
#else

    TEST_FAIL("STLSOFT_API_EXTERNAL_string_wcsnicmp must always be defined");
#endif
}


static void TEST_stricmp_BEHAVIOUR()
{
#if 0
#elif defined(STLSOFT_API_EXTERNAL_string_stricmp)

    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_stricmp("abc", "abc"));
    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_stricmp("ABC", "abc"));
    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_stricmp("aBc", "AbC"));
    TEST_INT_NE(0, STLSOFT_API_EXTERNAL_string_stricmp("abc", "abd"));
    TEST_INT_NE(0, STLSOFT_API_EXTERNAL_string_stricmp("abc", "ab"));
#else

    if (is_required_case_insensitive_alias_host_())
    {
        TEST_FAIL_WITH_QUALIFIER(
            "required case-insensitive string alias is not defined on this host (Linux/macOS/Windows with Clang, GCC, MSVC, or MinGW)"
        ,   "STLSOFT_API_EXTERNAL_string_stricmp"
        );
    }
    else
    {
        TEST_PASSED();
    }
#endif
}

static void TEST_wcsicmp_BEHAVIOUR()
{
#if 0
#elif defined(STLSOFT_API_EXTERNAL_string_wcsicmp)

    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_wcsicmp(L"abc", L"abc"));
    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_wcsicmp(L"ABC", L"abc"));
    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_wcsicmp(L"aBc", L"AbC"));
    TEST_INT_NE(0, STLSOFT_API_EXTERNAL_string_wcsicmp(L"abc", L"abd"));
    TEST_INT_NE(0, STLSOFT_API_EXTERNAL_string_wcsicmp(L"abc", L"ab"));
#else

    if (is_required_case_insensitive_alias_host_())
    {
        TEST_FAIL_WITH_QUALIFIER(
            "required case-insensitive string alias is not defined on this host (Linux/macOS/Windows with Clang, GCC, MSVC, or MinGW)"
        ,   "STLSOFT_API_EXTERNAL_string_wcsicmp"
        );
    }
    else
    {
        TEST_PASSED();
    }
#endif
}

static void TEST_strnicmp_BEHAVIOUR()
{
#if 0
#elif defined(STLSOFT_API_EXTERNAL_string_strnicmp)

    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_strnicmp("abc", "abc", 3));
    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_strnicmp("ABC", "abc", 3));
    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_strnicmp("aBcXY", "AbCzw", 3));
    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_strnicmp("abc", "abd", 2));
    TEST_INT_NE(0, STLSOFT_API_EXTERNAL_string_strnicmp("abc", "abd", 3));
#else

    TEST_FAIL("STLSOFT_API_EXTERNAL_string_strnicmp must always be defined");
#endif
}

static void TEST_wcsnicmp_BEHAVIOUR()
{
#if 0
#elif defined(STLSOFT_API_EXTERNAL_string_wcsnicmp)

    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_wcsnicmp(L"abc", L"abc", 3));
    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_wcsnicmp(L"ABC", L"abc", 3));
    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_wcsnicmp(L"aBcXY", L"AbCzw", 3));
    TEST_INT_EQ(0, STLSOFT_API_EXTERNAL_string_wcsnicmp(L"abc", L"abd", 2));
    TEST_INT_NE(0, STLSOFT_API_EXTERNAL_string_wcsnicmp(L"abc", L"abd", 3));
#else

    TEST_FAIL("STLSOFT_API_EXTERNAL_string_wcsnicmp must always be defined");
#endif
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
