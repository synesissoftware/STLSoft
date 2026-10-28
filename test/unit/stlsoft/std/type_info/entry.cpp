/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.std.type_info/entry.cpp
 *
 * Purpose: Unit-tests for the `std::type_info` string-access shims.
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

#include <stlsoft/shims/access/string/std/type_info.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <typeinfo>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_NARROW_SHIMS_ARE_NAME();
    static void TEST_c_str_data_w_MATCHES_NAME();
    static void TEST_c_str_len_w_MATCHES_NAME();
    static void TEST_c_str_ptr_w_MATCHES_DATA_W();
    static void TEST_c_str_ptr_null_w_MATCHES_DATA_W();

    struct type_info_subject
    {};

    static void widen_ascii_(wchar_t* dest, size_t cchDest, char const* src, size_t cchSrc)
    {
        size_t const n = (cchSrc < cchDest) ? cchSrc : (cchDest - 1);

        for (size_t i = 0; i != n; ++i)
        {
            dest[i] = static_cast<wchar_t>(static_cast<unsigned char>(src[i]));
        }

        dest[n] = L'\0';
    }
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.std.type_info", verbosity))
    {
        XTESTS_RUN_CASE(TEST_NARROW_SHIMS_ARE_NAME);
        XTESTS_RUN_CASE(TEST_c_str_data_w_MATCHES_NAME);
        XTESTS_RUN_CASE(TEST_c_str_len_w_MATCHES_NAME);
        XTESTS_RUN_CASE(TEST_c_str_ptr_w_MATCHES_DATA_W);
        XTESTS_RUN_CASE(TEST_c_str_ptr_null_w_MATCHES_DATA_W);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_NARROW_SHIMS_ARE_NAME()
{
    std::type_info const&   ti      =   typeid(type_info_subject);
    char const* const       name    =   ti.name();
    size_t const            len     =   ::strlen(name);

    TEST_MS_EQ(name, stlsoft::c_str_data_a(ti));
    TEST_MS_EQ(name, stlsoft::c_str_ptr_a(ti));
    TEST_MS_EQ(name, stlsoft::c_str_ptr_null_a(ti));
    TEST_INT_EQ(len, stlsoft::c_str_len_a(ti));

    TEST_MS_EQ(name, stlsoft::c_str_data(ti));
    TEST_MS_EQ(name, stlsoft::c_str_ptr(ti));
    TEST_MS_EQ(name, stlsoft::c_str_ptr_null(ti));
    TEST_INT_EQ(len, stlsoft::c_str_len(ti));
}

static void TEST_c_str_data_w_MATCHES_NAME()
{
    /* An ASCII type name widens one byte to one wchar_t, so the check does
     * not call mbstowcs().
     */
    std::type_info const&   ti      =   typeid(type_info_subject);
    char const* const       name    =   ti.name();
    size_t const            len     =   ::strlen(name);
    wchar_t                 expected[256];

    TEST_BOOLEAN_TRUE(len < STLSOFT_NUM_ELEMENTS(expected));

    widen_ascii_(expected, STLSOFT_NUM_ELEMENTS(expected), name, len);

    TEST_WS_EQ(expected, stlsoft::c_str_data_w(ti).data());
    TEST_INT_EQ(len, stlsoft::c_str_data_w(ti).size());
}

static void TEST_c_str_len_w_MATCHES_NAME()
{
    std::type_info const&   ti      =   typeid(type_info_subject);
    size_t const            len     =   ::strlen(ti.name());

    TEST_INT_EQ(len, stlsoft::c_str_len_w(ti));
}

static void TEST_c_str_ptr_w_MATCHES_DATA_W()
{
    std::type_info const& ti = typeid(type_info_subject);

    TEST_WS_EQ(stlsoft::c_str_data_w(ti).data(), stlsoft::c_str_ptr_w(ti).data());
    TEST_INT_EQ(stlsoft::c_str_data_w(ti).size(), stlsoft::c_str_ptr_w(ti).size());
}

static void TEST_c_str_ptr_null_w_MATCHES_DATA_W()
{
    std::type_info const& ti = typeid(type_info_subject);

    TEST_WS_EQ(stlsoft::c_str_data_w(ti).data(), stlsoft::c_str_ptr_null_w(ti).data());
    TEST_INT_EQ(stlsoft::c_str_data_w(ti).size(), stlsoft::c_str_ptr_null_w(ti).size());
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

