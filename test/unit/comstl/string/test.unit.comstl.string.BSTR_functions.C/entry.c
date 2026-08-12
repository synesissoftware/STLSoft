/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.string.BSTR_functions.C/entry.c
 *
 * Purpose: Scratch test for BSTR functions.
 *
 * Created: 31st May 2010
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <comstl/string/BSTR_functions.h>

/* /////////////////////////////////////////////////////////////////////////
 * includes
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

static void test_comstl_C_BSTR_create_w_1(void);
static void test_comstl_C_BSTR_create_w_2(void);
static void test_comstl_C_BSTR_create_a_1(void);
static void test_comstl_C_BSTR_create_a_2(void);
static void test_comstl_C_BSTR_create_len_w(void);
static void test_comstl_C_BSTR_create_len_a(void);
static void test_comstl_C_BSTR_compare(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.string.C.BSTR_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_comstl_C_BSTR_create_w_1);
        XTESTS_RUN_CASE(test_comstl_C_BSTR_create_w_2);
        XTESTS_RUN_CASE(test_comstl_C_BSTR_create_a_1);
        XTESTS_RUN_CASE(test_comstl_C_BSTR_create_a_2);
        XTESTS_RUN_CASE(test_comstl_C_BSTR_create_len_w);
        XTESTS_RUN_CASE(test_comstl_C_BSTR_create_len_a);
        XTESTS_RUN_CASE(test_comstl_C_BSTR_compare);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static wchar_t const* m2w(char const* s)
{
    static wchar_t w[1001];

    MultiByteToWideChar(0, 0, s, -1, w, dimensionof(w));

    return w;
}



// NOTE: These are not true unit-tests, since we could be out of memory
// to allocate the BSTR. In practice, however, this'll never happen
// (unless we drive the system in/close to out-of-memory conditions).

static void test_comstl_C_BSTR_create_w_1()
{
    {
        BSTR s = comstl_C_BSTR_create_w(NULL);

        TEST_PTR_EQ(NULL, s);
        TEST_INT_EQ(0u, SysStringLen(s));
        TEST_INT_EQ(SysStringLen(s), comstl_C_BSTR_len(s));
    }

    {
        BSTR s = comstl_C_BSTR_create_w(L"");

        TEST_PTR_NE(NULL, s);
        TEST_INT_EQ(0u, SysStringLen(s));
        TEST_INT_EQ(SysStringLen(s), comstl_C_BSTR_len(s));

        comstl_C_BSTR_destroy(s);
    }
}

static void test_comstl_C_BSTR_create_w_2()
{
    wchar_t const* const strings[] =
    {
            L""
        ,   L"a"
        ,   L"abc"
        ,   L"abcdefghijklmnopqrstuvwxyz"
        ,   L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    };

    { size_t i; for (i = 0; i != dimensionof(strings); ++i)
    {
        BSTR const s = comstl_C_BSTR_create_w(strings[i]);

        TEST_WS_EQ(strings[i], s);
        TEST_INT_EQ(wcslen(strings[i]), SysStringLen(s));
        TEST_INT_EQ(SysStringLen(s), comstl_C_BSTR_len(s));

        comstl_C_BSTR_destroy(s);
    }}
}

static void test_comstl_C_BSTR_create_a_1()
{
    {
        BSTR s = comstl_C_BSTR_create_a(NULL);

        TEST_PTR_EQ(NULL, s);
    }

    {
        BSTR s = comstl_C_BSTR_create_a("");

        TEST_PTR_NE(NULL, s);
        TEST_INT_EQ(0u, SysStringLen(s));

        comstl_C_BSTR_destroy(s);
    }
}

static void test_comstl_C_BSTR_create_a_2()
{
    char const* const strings[] =
    {
            ""
        ,   "a"
        ,   "abc"
        ,   "abcdefghijklmnopqrstuvwxyz"
        ,   "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    };

    { size_t i; for (i = 0; i != dimensionof(strings); ++i)
    {
        BSTR const s = comstl_C_BSTR_create_a(strings[i]);

        TEST_WS_EQ(m2w(strings[i]), s);
        TEST_INT_EQ(strlen(strings[i]), SysStringLen(s));
        TEST_INT_EQ(SysStringLen(s), comstl_C_BSTR_len(s));

        comstl_C_BSTR_destroy(s);
    }}
}

static void test_comstl_C_BSTR_create_len_w(void)
{
    wchar_t const alphabet[] = L"abcdefghijklmnopqrstuvwxyz";

    { size_t i; for (i = 0; i != dimensionof(alphabet); ++i)
    {
        BSTR const s = comstl_C_BSTR_create_len_w(alphabet, i);

        TEST_WS_EQ_N(alphabet, s, (int)i);
        TEST_INT_EQ(i, SysStringLen(s));
        TEST_INT_EQ(SysStringLen(s), comstl_C_BSTR_len(s));

        comstl_C_BSTR_destroy(s);
    }}
}

static void test_comstl_C_BSTR_create_len_a(void)
{
    char const alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    { size_t i; for (i = 0; i != dimensionof(alphabet); ++i)
    {
        BSTR const s = comstl_C_BSTR_create_len_a(alphabet, i);

        TEST_WS_EQ_N(m2w(alphabet), s, (int)i);
        TEST_INT_EQ(i, SysStringLen(s));
        TEST_INT_EQ(SysStringLen(s), comstl_C_BSTR_len(s));

        comstl_C_BSTR_destroy(s);
    }}
}

static void test_comstl_C_BSTR_compare()
{
    BSTR    abc =   SysAllocString(L"abc");
    BSTR    def =   SysAllocString(L"def");

    TEST_INT_EQ(0, comstl_C_BSTR_compare(NULL, NULL));
    TEST_INT_EQ(0, comstl_C_BSTR_compare(abc, abc));
    TEST_INT_NE(0, comstl_C_BSTR_compare(abc, def));
    TEST_INT_NE(0, comstl_C_BSTR_compare(def, abc));

    TEST_INT_LT(0, comstl_C_BSTR_compare(NULL, abc));
    TEST_INT_GT(0, comstl_C_BSTR_compare(abc, NULL));
    TEST_INT_LT(0, comstl_C_BSTR_compare(NULL, def));
    TEST_INT_GT(0, comstl_C_BSTR_compare(def, NULL));
    TEST_INT_LT(0, comstl_C_BSTR_compare(abc, def));
    TEST_INT_GT(0, comstl_C_BSTR_compare(def, abc));

    comstl_C_BSTR_destroy(abc);
    comstl_C_BSTR_destroy(def);
}


/* ///////////////////////////// end of file //////////////////////////// */
