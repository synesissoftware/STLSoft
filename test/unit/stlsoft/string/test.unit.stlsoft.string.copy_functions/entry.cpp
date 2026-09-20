/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.string.copy_functions/entry.cpp
 *
 * Purpose: Scratch test for string copy functions.
 *
 * Created: 29th September 2016
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


 /* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/copy_functions.h>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/util/dimensionof.h>

/* Standard C++ header files */
#include <algorithm>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    void test_string_copy_with_toolarge_destination();
    void test_string_copy_with_exactlysufficient_destination();
    void test_string_copy_with_insufficient_destination();
    void test_string_copy_with_nul_with_toolarge_destination();
    void test_string_copy_with_nul_with_exactlysufficient_destination();
    void test_string_copy_with_nul_with_insufficient_destination();
    void test_string_copy_with_different_lengths();
    void test_string_copy_with_nul_with_different_lengths();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.copy_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_string_copy_with_toolarge_destination);
        XTESTS_RUN_CASE(test_string_copy_with_exactlysufficient_destination);
        XTESTS_RUN_CASE(test_string_copy_with_insufficient_destination);
        XTESTS_RUN_CASE(test_string_copy_with_nul_with_toolarge_destination);
        XTESTS_RUN_CASE(test_string_copy_with_nul_with_exactlysufficient_destination);
        XTESTS_RUN_CASE(test_string_copy_with_nul_with_insufficient_destination);
        XTESTS_RUN_CASE(test_string_copy_with_different_lengths);
        XTESTS_RUN_CASE(test_string_copy_with_nul_with_different_lengths);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{

void test_string_copy_with_toolarge_destination()
{
    char        dest[10];
    char const  src[]   =   "source";
    size_t      n;

    ::memset(dest, '~', sizeof(dest));
    strcpy(dest, src);

    TEST_MS_EQ("source", dest);
    TEST_CHAR_EQ('~', dest[7]);

    ::memset(dest, '~', sizeof(dest));
    memcpy(dest, src, sizeof(char) * (1 + strlen(src)));

    TEST_MS_EQ("source", dest);
    TEST_CHAR_EQ('~', dest[7]);

    ::memset(dest, '~', sizeof(dest));
    n = stlsoft::string_copy(dest, dimensionof(dest), src, strlen(src));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);
    TEST_CHAR_EQ('~', dest[7]);

    ::memset(dest, '~', sizeof(dest));
    n = stlsoft::string_copy(dest, dimensionof(dest), stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);
    TEST_CHAR_EQ('~', dest[7]);
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

    ::memset(dest, '~', sizeof(dest));
    n = stlsoft::string_copy(dest, stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);
    TEST_CHAR_EQ('~', dest[7]);

    ::memset(dest, '~', sizeof(dest));
    n = stlsoft::string_copy(dest, src);

    TEST_INT_EQ(7u, n);
    TEST_MS_EQ("source", dest);
    TEST_CHAR_EQ('\0', dest[7]);
    TEST_CHAR_EQ('~', dest[8]);
# endif /* !STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
}

void test_string_copy_with_exactlysufficient_destination()
{
    char        dest[7];
    char const  src[]   =   "source";
    size_t      n;

    strcpy(dest, src);

    TEST_MS_EQ("source", dest);

    memcpy(dest, src, sizeof(char) * (1 + strlen(src)));

    TEST_MS_EQ("source", dest);

    n = stlsoft::string_copy(dest, dimensionof(dest), src, strlen(src));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);

    n = stlsoft::string_copy(dest, dimensionof(dest), stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

    n = stlsoft::string_copy(dest, stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);

    n = stlsoft::string_copy(dest, src);

    TEST_INT_EQ(7u, n);
    TEST_MS_EQ("source", dest);
# endif /* !STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
}

void test_string_copy_with_insufficient_destination()
{
    char        dest[5];
    char const  src[]   =   "source";
    size_t      n;

    n = stlsoft::string_copy(dest, dimensionof(dest), src, strlen(src));

    TEST_INT_EQ(5u, n);
    TEST_MS_EQ_N("sourc", dest, 5);

    n = stlsoft::string_copy(dest, dimensionof(dest), stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(5u, n);
    TEST_MS_EQ_N("sourc", dest, 5);
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

    n = stlsoft::string_copy(dest, stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(5u, n);
    TEST_MS_EQ_N("sourc", dest, 5);

    n = stlsoft::string_copy(dest, src);

    TEST_INT_EQ(5u, n);
    TEST_MS_EQ_N("sourc", dest, 5);
# endif /* !STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
}

void test_string_copy_with_nul_with_toolarge_destination()
{
    char        dest[10];
    char const  src[]   =   "source";
    size_t      n;

    ::memset(dest, '~', sizeof(dest));
    n = stlsoft::string_copy_with_nul(dest, dimensionof(dest), src, strlen(src));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);
    TEST_CHAR_EQ('~', dest[7]);

    ::memset(dest, '~', sizeof(dest));
    n = stlsoft::string_copy_with_nul(dest, dimensionof(dest), stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);
    TEST_CHAR_EQ('~', dest[7]);
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

    ::memset(dest, '~', sizeof(dest));
    n = stlsoft::string_copy_with_nul(dest, stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);
    TEST_CHAR_EQ('~', dest[7]);

    ::memset(dest, '~', sizeof(dest));
    n = stlsoft::string_copy_with_nul(dest, src);

    TEST_INT_EQ(7u, n);
    TEST_MS_EQ("source", dest);
    TEST_CHAR_EQ('\0', dest[7]);
    TEST_CHAR_EQ('~', dest[8]);
# endif /* !STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
}

void test_string_copy_with_nul_with_exactlysufficient_destination()
{
    char        dest[7];
    char const  src[]   =   "source";
    size_t      n;

    n = stlsoft::string_copy_with_nul(dest, dimensionof(dest), src, strlen(src));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);

    n = stlsoft::string_copy_with_nul(dest, dimensionof(dest), stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

    n = stlsoft::string_copy_with_nul(dest, stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);

    n = stlsoft::string_copy_with_nul(dest, src);

    TEST_INT_EQ(6u, n);
    TEST_MS_EQ("source", dest);
# endif /* !STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
}

void test_string_copy_with_nul_with_insufficient_destination()
{
    char        dest[5];
    char const  src[]   =   "source";
    size_t      n;

    n = stlsoft::string_copy_with_nul(dest, dimensionof(dest), src, strlen(src));

    TEST_INT_EQ(4u, n);
    TEST_MS_EQ("sour", dest);

    n = stlsoft::string_copy_with_nul(dest, dimensionof(dest), stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(4u, n);
    TEST_MS_EQ("sour", dest);
# ifdef STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT

    n = stlsoft::string_copy_with_nul(dest, stlsoft::string_slice_m_t::create(src, strlen(src)));

    TEST_INT_EQ(4u, n);
    TEST_MS_EQ("sour", dest);

    n = stlsoft::string_copy_with_nul(dest, src);

    TEST_INT_EQ(4u, n);
    TEST_MS_EQ("sour", dest);
# endif /* !STLSOFT_CF_STATIC_ARRAY_SIZE_DETERMINATION_SUPPORT */
}

void test_string_copy_with_different_lengths()
{
    wchar_t         dest[10];
    wchar_t const*  src =   L"source";
    size_t          n;


    // 0:0

    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 0, src, 0);

    TEST_INT_EQ(0u, n);
    TEST_CHAR_EQ(L'~', dest[0]);


    // 1:[012]

    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 1, src, 0);

    TEST_INT_EQ(0u, n);
    TEST_CHAR_EQ(L'\0', dest[0]);
    TEST_CHAR_EQ(L'~', dest[1]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 1, src, 1);

    TEST_INT_EQ(1u, n);
    TEST_CHAR_EQ(L's', dest[0]);
    TEST_CHAR_EQ(L'~', dest[1]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 1, src, 2);

    TEST_INT_EQ(1u, n);
    TEST_CHAR_EQ(L's', dest[0]);
    TEST_CHAR_EQ(L'~', dest[1]);


    // 2:[0123]

    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 2, src, 0);

    TEST_INT_EQ(0u, n);
    TEST_CHAR_EQ(L'\0', dest[0]);
    TEST_CHAR_EQ(L'~', dest[1]);
    TEST_CHAR_EQ(L'~', dest[2]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 2, src, 1);

    TEST_INT_EQ(1u, n);
    TEST_CHAR_EQ(L's', dest[0]);
    TEST_CHAR_EQ(L'\0', dest[1]);
    TEST_CHAR_EQ(L'~', dest[2]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 2, src, 2);

    TEST_INT_EQ(2u, n);
    TEST_CHAR_EQ(L's', dest[0]);
    TEST_CHAR_EQ(L'o', dest[1]);
    TEST_CHAR_EQ(L'~', dest[2]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 2, src, 3);

    TEST_INT_EQ(2u, n);
    TEST_CHAR_EQ(L's', dest[0]);
    TEST_CHAR_EQ(L'o', dest[1]);
    TEST_CHAR_EQ(L'~', dest[2]);


    // 6:[4567]

    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 6, src, 4);

    TEST_INT_EQ(4u, n);
    TEST_WS_EQ(L"sour", dest);
    TEST_CHAR_EQ(L'\0', dest[4]);
    TEST_CHAR_EQ(L'~', dest[5]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 6, src, 5);

    TEST_INT_EQ(5u, n);
    TEST_WS_EQ(L"sourc", dest);
    TEST_CHAR_EQ(L'\0', dest[5]);
    TEST_CHAR_EQ(L'~', dest[6]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 6, src, 6);

    TEST_INT_EQ(6u, n);
    TEST_WS_EQ_N(L"source", dest, 6);
    TEST_CHAR_EQ(L'~', dest[6]);
    TEST_CHAR_EQ(L'~', dest[7]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 6, src, 7);

    TEST_INT_EQ(6u, n);
    TEST_WS_EQ_N(L"source", dest, 6);
    TEST_CHAR_EQ(L'~', dest[6]);
    TEST_CHAR_EQ(L'~', dest[7]);


    // 7:[5678]

    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 7, src, 5);

    TEST_INT_EQ(5u, n);
    TEST_WS_EQ(L"sourc", dest);
    TEST_CHAR_EQ(L'\0', dest[5]);
    TEST_CHAR_EQ(L'~', dest[6]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 7, src, 6);

    TEST_INT_EQ(6u, n);
    TEST_WS_EQ(L"source", dest);
    TEST_CHAR_EQ(L'\0', dest[6]);
    TEST_CHAR_EQ(L'~', dest[7]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 7, src, 7);

    TEST_INT_EQ(7u, n);
    TEST_WS_EQ_N(L"source", dest, 6);
    TEST_CHAR_EQ(L'\0', dest[6]);
    TEST_CHAR_EQ(L'~', dest[7]);
    TEST_CHAR_EQ(L'~', dest[8]);
    TEST_CHAR_EQ(L'~', dest[9]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy(dest, 7, src, 8);

    TEST_INT_EQ(7u, n);
    TEST_WS_EQ_N(L"source", dest, 6);
    TEST_CHAR_EQ(L'\0', dest[6]);
    TEST_CHAR_EQ(L'~', dest[7]);
    TEST_CHAR_EQ(L'~', dest[8]);
}

void test_string_copy_with_nul_with_different_lengths()
{
    wchar_t         dest[10];
    wchar_t const*  src =   L"source";
    size_t          n;


    // 0:0

    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 0, src, 0);

    TEST_INT_EQ(0u, n);
    TEST_CHAR_EQ(L'~', dest[0]);


    // 1:[012]

    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 1, src, 0);

    TEST_INT_EQ(0u, n);
    TEST_CHAR_EQ(L'\0', dest[0]);
    TEST_CHAR_EQ(L'~', dest[1]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 1, src, 1);

    TEST_INT_EQ(0u, n);
    TEST_CHAR_EQ(L'\0', dest[0]);
    TEST_CHAR_EQ(L'~', dest[1]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 1, src, 2);

    TEST_INT_EQ(0u, n);
    TEST_CHAR_EQ(L'\0', dest[0]);
    TEST_CHAR_EQ(L'~', dest[1]);


    // 2:[0123]

    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 2, src, 0);

    TEST_INT_EQ(0u, n);
    TEST_CHAR_EQ(L'\0', dest[0]);
    TEST_CHAR_EQ(L'~', dest[1]);
    TEST_CHAR_EQ(L'~', dest[2]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 2, src, 1);

    TEST_INT_EQ(1u, n);
    TEST_CHAR_EQ(L's', dest[0]);
    TEST_CHAR_EQ(L'\0', dest[1]);
    TEST_CHAR_EQ(L'~', dest[2]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 2, src, 2);

    TEST_INT_EQ(1u, n);
    TEST_CHAR_EQ(L's', dest[0]);
    TEST_CHAR_EQ(L'\0', dest[1]);
    TEST_CHAR_EQ(L'~', dest[2]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 2, src, 3);

    TEST_INT_EQ(1u, n);
    TEST_CHAR_EQ(L's', dest[0]);
    TEST_CHAR_EQ(L'\0', dest[1]);
    TEST_CHAR_EQ(L'~', dest[2]);


    // 6:[4567]

    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 6, src, 4);

    TEST_INT_EQ(4u, n);
    TEST_WS_EQ(L"sour", dest);
    TEST_CHAR_EQ(L'\0', dest[4]);
    TEST_CHAR_EQ(L'~', dest[5]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 6, src, 5);

    TEST_INT_EQ(5u, n);
    TEST_WS_EQ(L"sourc", dest);
    TEST_CHAR_EQ(L'\0', dest[5]);
    TEST_CHAR_EQ(L'~', dest[6]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 6, src, 6);

    TEST_INT_EQ(5u, n);
    TEST_WS_EQ(L"sourc", dest);
    TEST_CHAR_EQ(L'\0', dest[5]);
    TEST_CHAR_EQ(L'~', dest[7]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 6, src, 7);

    TEST_INT_EQ(5u, n);
    TEST_WS_EQ(L"sourc", dest);
    TEST_CHAR_EQ(L'~', dest[6]);
    TEST_CHAR_EQ(L'~', dest[7]);


    // 7:[5678]

    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 7, src, 5);

    TEST_INT_EQ(5u, n);
    TEST_WS_EQ(L"sourc", dest);
    TEST_CHAR_EQ(L'\0', dest[5]);
    TEST_CHAR_EQ(L'~', dest[6]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 7, src, 6);

    TEST_INT_EQ(6u, n);
    TEST_WS_EQ(L"source", dest);
    TEST_CHAR_EQ(L'\0', dest[6]);
    TEST_CHAR_EQ(L'~', dest[7]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 7, src, 7);

    TEST_INT_EQ(6u, n);
    TEST_WS_EQ(L"source", dest);
    TEST_CHAR_EQ(L'\0', dest[6]);
    TEST_CHAR_EQ(L'~', dest[7]);
    TEST_CHAR_EQ(L'~', dest[8]);
    TEST_CHAR_EQ(L'~', dest[9]);


    std::fill_n(dest, dimensionof(dest), L'~');
    n = stlsoft::string_copy_with_nul(dest, 7, src, 8);

    TEST_INT_EQ(6u, n);
    TEST_WS_EQ(L"source", dest);
    TEST_CHAR_EQ(L'\0', dest[6]);
    TEST_CHAR_EQ(L'~', dest[7]);
    TEST_CHAR_EQ(L'~', dest[8]);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

