/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/winstl/registry/reg_value/entry.cpp
 *
 * Purpose: Unit-tests for `winstl::reg_value`.
 *
 * Created: 23rd February 2009
 * Updated: 14th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/registry/reg_value.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/conversion/integer_to_string/integer_to_decimal_string.hpp>
#include <comstl/util/guid.hpp>
#include <winstl/registry/reg_key.hpp>

/* Standard C++ header files */
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

#if 0
    static void TEST_MISSING_VALUE();
#endif /* 0 */
    static void TEST_NONE_VALUE();
    static void TEST_0__DWORD();
    static void TEST_EMPTY_STRING();
    static void TEST_MANY_DWORDS();
    static void TEST_MANY_STRINGS();
    static void TEST_EMPTY_MULTISTRING();
    static void TEST_MULTISTRING_MULTIBYTE();
    static void TEST_MULTISTRING_WIDE();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace {

    static winstl::reg_key* rootKey;
}

static int setup(void* /* arg */)
{
    try
    {
        rootKey = new winstl::reg_key(winstl::reg_key::create_key(HKEY_CURRENT_USER, "SOFTWARE\\Synesis Software\\freelibs\\STLSoft\\test\\test.unit.winstl.registry.reg_value"));

        return 0;
    }
    catch (winstl::registry_exception& x)
    {
        fprintf(stderr, "setup() failed to create registry key: %s: %lu\n", x.what(), static_cast<DWORD>(x.status_code()));

        return -1;
    }
    catch (std::exception& x)
    {
        fprintf(stderr, "setup() failed to create registry key: %s\n", x.what());

        return -1;
    }
}

static int teardown(void* /* arg */)
{
    winstl::reg_traits<char>::reg_delete_tree(rootKey->get(), "");

    delete rootKey;
    rootKey = NULL;

    return 0;
}


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.component.winstl.registry.reg_value", verbosity, setup, teardown, NULL))
    {
#if 0
        XTESTS_RUN_CASE_THAT_THROWS(TEST_MISSING_VALUE, winstl::registry_exception);
#endif /* 0 */
        XTESTS_RUN_CASE(TEST_NONE_VALUE);
        XTESTS_RUN_CASE(TEST_0__DWORD);
        XTESTS_RUN_CASE(TEST_EMPTY_STRING);
        XTESTS_RUN_CASE(TEST_MANY_DWORDS);
        XTESTS_RUN_CASE(TEST_MANY_STRINGS);
        XTESTS_RUN_CASE(TEST_EMPTY_MULTISTRING);
        XTESTS_RUN_CASE(TEST_MULTISTRING_MULTIBYTE);
        XTESTS_RUN_CASE(TEST_MULTISTRING_WIDE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    std::string get_value_name(char const* root, size_t n)
    {
        char    buff[21];

        return std::string(root) + "-" + stlsoft::integer_to_decimal_string(&buff[0], STLSOFT_NUM_ELEMENTS(buff), n);
    }


#if 0
static void TEST_MISSING_VALUE()
{
#if 0
    {
        char    key_class[100];
        size_t  cch_key_class = STLSOFT_NUM_ELEMENTS(key_class);
        LONG    res;

        res = winstl::reg_traits<char>::reg_query_info(rootKey->get(), &key_class[0], &cch_key_class, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

        res = winstl::reg_traits<char>::reg_query_info(rootKey->get(), &key_class[0], NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    }
#endif /* 0 */

    const comstl::guid  guid;

    rootKey->get_value(guid).value_sz();
}
#endif /* 0 */

static void TEST_NONE_VALUE()
{
    const comstl::guid  guid;

    ::RegSetValueEx(rootKey->get(), stlsoft::c_str_ptr(guid), 0, REG_NONE, NULL, 0);

    TEST_INT_EQ(DWORD(REG_NONE), rootKey->get_value(guid).type());
}

static void TEST_0__DWORD()
{
    const comstl::guid  guid;
    const DWORD         value = 0u;

    rootKey->set_value(guid, value);

    TEST_INT_EQ(DWORD(REG_DWORD), rootKey->get_value(guid).type());
    TEST_INT_EQ(value, rootKey->get_value(guid).value_dword());
}

static void TEST_EMPTY_STRING()
{
    const comstl::guid  guid;
    char const* const   value = "";

    rootKey->set_value(guid, value);

    TEST_INT_EQ(DWORD(REG_SZ), rootKey->get_value(guid).type());
    TEST_MS_EQ(value, rootKey->get_value(guid).value_sz());
}

static void TEST_MANY_DWORDS()
{
    const DWORD values[] = { 0, 3, 10, 30, 100, 300, 1000, 3000, 10000, 30000, 100000, 300000, 1000000, 3000000, 10000000, 30000000, 100000000, 300000000, 1000000000, 3000000000u, };

    { for (unsigned i = 0; i != 10; ++i)
    {
        const comstl::guid  guid;

        { for (size_t j = 0; j != STLSOFT_NUM_ELEMENTS(values); ++j)
        {
            const DWORD value = values[j];

            rootKey->set_value(get_value_name(stlsoft::c_str_ptr(guid), j), value);
        }}

        { for (size_t j = 0; j != STLSOFT_NUM_ELEMENTS(values); ++j)
        {
            const DWORD value = values[j];

            TEST_INT_EQ(DWORD(REG_DWORD), rootKey->get_value(get_value_name(stlsoft::c_str_ptr(guid), j)).type());
            TEST_INT_EQ(value, rootKey->get_value(get_value_name(stlsoft::c_str_ptr(guid), j)).value_dword());
        }}
    }}
}

static void TEST_MANY_STRINGS()
{
    char const* values[] = { "0", "3", "10", "30", "100", "300", "1000", "3000", "10000", "30000", "100000", "300000", "1000000", "3000000", "10000000", "30000000", "100000000", "300000000", "1000000000", "3000000000", };

    { for (unsigned i = 0; i != 10; ++i)
    {
        const comstl::guid  guid;

        { for (size_t j = 0; j != STLSOFT_NUM_ELEMENTS(values); ++j)
        {
            char const* value = values[j];

            rootKey->set_value(get_value_name(stlsoft::c_str_ptr(guid), j), value);
        }}

        { for (size_t j = 0; j != STLSOFT_NUM_ELEMENTS(values); ++j)
        {
            char const* value = values[j];

            TEST_INT_EQ(DWORD(REG_SZ), rootKey->get_value(get_value_name(stlsoft::c_str_ptr(guid), j)).type());
            TEST_MS_EQ(value, rootKey->get_value(get_value_name(stlsoft::c_str_ptr(guid), j)).value_sz());
        }}
    }}
}


static void TEST_EMPTY_MULTISTRING()
{
    const comstl::guid  guid;
    char const**        value = NULL;

    rootKey->set_value(guid, value, 0);

    TEST_INT_EQ(DWORD(REG_MULTI_SZ), rootKey->get_value(guid).type());
    TEST_INT_EQ(0u, rootKey->get_value(guid).value_multi_sz().size());
}

static void TEST_MULTISTRING_MULTIBYTE()
{
    char const* values[] = { "0", "3", "10", "30", "100", "300", "1000", "3000", "10000", "30000", "100000", "300000", "1000000", "3000000", "10000000", "30000000", "100000000", "300000000", "1000000000", "3000000000", };

    const comstl::guid  guid;

    rootKey->set_value(guid, values, STLSOFT_NUM_ELEMENTS(values));

    TEST_INT_EQ(DWORD(REG_MULTI_SZ), rootKey->get_value(guid).type());
    XTESTS_REQUIRE(TEST_INT_EQ(STLSOFT_NUM_ELEMENTS(values), rootKey->get_value(guid).value_multi_sz().size()));
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(values); ++i)
    {
        TEST_MS_EQ(values[i], rootKey->get_value(guid).value_multi_sz()[i]);
    }}
}

static void TEST_MULTISTRING_WIDE()
{
    wchar_t const* values[] = { L"0", L"3", L"10", L"30", L"100", L"300", L"1000", L"3000", L"10000", L"30000", L"100000", L"300000", L"1000000", L"3000000", L"10000000", L"30000000", L"100000000", L"300000000", L"1000000000", L"3000000000", };

    const comstl::guid  guid;

    winstl::reg_key_w   key(rootKey->get(), L"");

    key.set_value(stlsoft::c_str_ptr_w(guid), values, STLSOFT_NUM_ELEMENTS(values));

    TEST_INT_EQ(DWORD(REG_MULTI_SZ), key.get_value(stlsoft::c_str_ptr_w(guid)).type());
    XTESTS_REQUIRE(TEST_INT_EQ(STLSOFT_NUM_ELEMENTS(values), key.get_value(stlsoft::c_str_ptr_w(guid)).value_multi_sz().size()));
    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(values); ++i)
    {
        TEST_WS_EQ(values[i], key.get_value(stlsoft::c_str_ptr_w(guid)).value_multi_sz()[i]);
    }}
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

