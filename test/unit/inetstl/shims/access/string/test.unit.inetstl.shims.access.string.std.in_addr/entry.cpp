/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.inetstl.shims.access.string.std.in_addr/entry.cpp
 *
 * Purpose: Unit-tests for string-access-shims for `struct in_addr`.
 *
 * Created: ...
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#define STLSOFT_MINIMUM_SAS_INCLUDES

/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <inetstl/shims/access/string/std/in_addr.hpp>

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <platformstl/platformstl.h>

/* Standard C++ header files */
#include <string>

/* Standard C header files */
#include <stdlib.h>
#include <time.h>

/* internet header files */
#include <inetstl/internal/std/in_addr_.h>


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#ifdef PLATFORMSTL_OS_IS_WINDOWS

# ifdef UNICODE

#  define TEST_S_EQ                                         TEST_WS_EQ
# else

#  define TEST_S_EQ                                         TEST_MS_EQ
# endif
#endif


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_nullptr();
    static void TEST_127_0_0_1();
    static void TEST_254_120_99_7();
    static void TEST_255_255_255_255();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

 namespace {

    typedef std::basic_string<char>                         string_a_t;
    typedef std::basic_string<wchar_t>                      string_w_t;
#ifdef PLATFORMSTL_OS_IS_WINDOWS

    typedef std::basic_string<TCHAR>                        string_t;
#endif
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.inetstl.shims.access.string.std.in_addr", verbosity))
    {
        XTESTS_RUN_CASE(TEST_nullptr);
        XTESTS_RUN_CASE(TEST_127_0_0_1);
        XTESTS_RUN_CASE(TEST_254_120_99_7);
        XTESTS_RUN_CASE(TEST_255_255_255_255);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

inline
void ipv4_address_to_in_addr(
    char const*     ipv4_address
,   struct in_addr* addr
)
{
    STLSOFT_ASSERT(NULL != addr);

#ifdef _WIN32

    addr->s_addr = inet_addr(ipv4_address);
#else

    inet_aton(ipv4_address, addr);
#endif
}


static void TEST_nullptr()
{
    struct in_addr const* const addr = NULL;

    /* c_str_ptr(|_a|_w) */
    {
        TEST_MS_EQ("", stlsoft::c_str_ptr_a(stlsoft::c_str_ptr_a(addr)));
#ifdef PLATFORMSTL_OS_IS_WINDOWS

        TEST_WS_EQ(L"", stlsoft::c_str_ptr_w(stlsoft::c_str_ptr_w(addr)));
        TEST_S_EQ(TEXT(""), stlsoft::c_str_ptr(stlsoft::c_str_ptr(addr)));
#endif
    }

    #if 0
    /* c_str_ptr(|_a|_w) */
    {

        TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_a(stlsoft::c_str_ptr_null_a(addr)));
# ifdef PLATFORMSTL_OS_IS_WINDOWS

        TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_w(stlsoft::c_str_ptr_null_w(addr)));
        TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null(stlsoft::c_str_ptr_null(addr)));
# endif
    }
#endif

    /* c_str_len(|_a|_w) */
    {
        TEST_INT_EQ(0, stlsoft::c_str_len_a(addr));
#ifdef PLATFORMSTL_OS_IS_WINDOWS

        TEST_INT_EQ(0, stlsoft::c_str_len_w(addr));
        TEST_INT_EQ(0, stlsoft::c_str_len(addr));
#endif
    }
}

static void TEST_127_0_0_1()
{
    struct in_addr addr;

    ipv4_address_to_in_addr("127.0.0.1", &addr);

    /* c_str_ptr(|_a|_w) */
    {

        TEST_MS_EQ("127.0.0.1", stlsoft::c_str_ptr_a(stlsoft::c_str_ptr_a(addr)));
        TEST_MS_EQ("127.0.0.1", stlsoft::c_str_ptr_a(stlsoft::c_str_ptr_a(&addr)));
#ifdef PLATFORMSTL_OS_IS_WINDOWS

        TEST_WS_EQ(L"127.0.0.1", stlsoft::c_str_ptr_w(stlsoft::c_str_ptr_w(addr)));
        TEST_WS_EQ(L"127.0.0.1", stlsoft::c_str_ptr_w(stlsoft::c_str_ptr_w(&addr)));
        TEST_S_EQ(TEXT("127.0.0.1"), stlsoft::c_str_ptr(stlsoft::c_str_ptr(addr)));
        TEST_S_EQ(TEXT("127.0.0.1"), stlsoft::c_str_ptr(stlsoft::c_str_ptr(&addr)));
#endif
    }

    /* c_str_len(|_a|_w) */
    {
        TEST_INT_EQ(9, stlsoft::c_str_len_a(addr));
        TEST_INT_EQ(9, stlsoft::c_str_len_a(&addr));
#ifdef PLATFORMSTL_OS_IS_WINDOWS

        TEST_INT_EQ(9, stlsoft::c_str_len_w(addr));
        TEST_INT_EQ(9, stlsoft::c_str_len_w(&addr));
        TEST_INT_EQ(9, stlsoft::c_str_len(addr));
        TEST_INT_EQ(9, stlsoft::c_str_len(&addr));
#endif
    }
}

static void TEST_254_120_99_7()
{
    struct in_addr addr;

    ipv4_address_to_in_addr("254.120.99.7", &addr);

    TEST_MS_EQ("254.120.99.7", stlsoft::c_str_ptr_a(stlsoft::c_str_ptr_a(addr)));
    TEST_MS_EQ("254.120.99.7", stlsoft::c_str_ptr_a(stlsoft::c_str_ptr_a(&addr)));
#ifdef PLATFORMSTL_OS_IS_WINDOWS

    TEST_WS_EQ(L"254.120.99.7", stlsoft::c_str_ptr_w(stlsoft::c_str_ptr_w(addr)));
    TEST_WS_EQ(L"254.120.99.7", stlsoft::c_str_ptr_w(stlsoft::c_str_ptr_w(&addr)));
    TEST_S_EQ(TEXT("254.120.99.7"), stlsoft::c_str_ptr(stlsoft::c_str_ptr(addr)));
    TEST_S_EQ(TEXT("254.120.99.7"), stlsoft::c_str_ptr(stlsoft::c_str_ptr(&addr)));
#endif
}

static void TEST_255_255_255_255()
{
    struct in_addr addr;

    ipv4_address_to_in_addr("255.255.255.255", &addr);

    TEST_MS_EQ("255.255.255.255", stlsoft::c_str_ptr_a(stlsoft::c_str_ptr_a(addr)));
    TEST_MS_EQ("255.255.255.255", stlsoft::c_str_ptr_a(stlsoft::c_str_ptr_a(&addr)));
#ifdef PLATFORMSTL_OS_IS_WINDOWS

    TEST_WS_EQ(L"255.255.255.255", stlsoft::c_str_ptr_w(stlsoft::c_str_ptr_w(addr)));
    TEST_WS_EQ(L"255.255.255.255", stlsoft::c_str_ptr_w(stlsoft::c_str_ptr_w(&addr)));
    TEST_S_EQ(TEXT("255.255.255.255"), stlsoft::c_str_ptr(stlsoft::c_str_ptr(addr)));
    TEST_S_EQ(TEXT("255.255.255.255"), stlsoft::c_str_ptr(stlsoft::c_str_ptr(&addr)));
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

