/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/std/exception/entry.cpp
 *
 * Purpose: Unit-tests for the `std::exception` string-access shims.
 *
 * Created: 28th October 2026
 * Updated: 29th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/shims/access/string/std/exception.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <exception>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_NARROW_SHIMS_ARE_WHAT();
    static void TEST_c_str_data_w_MATCHES_WHAT();
    static void TEST_c_str_len_w_MATCHES_WHAT();
    static void TEST_c_str_ptr_w_MATCHES_DATA_W();
    static void TEST_c_str_ptr_null_w_MATCHES_DATA_W();
    static void TEST_EMPTY_WHAT();

    struct exception_subject
        : public std::exception
    {
    public:
        explicit exception_subject(char const* message)
            : m_message(message)
        {}

        virtual char const* what() const STLSOFT_NOEXCEPT_STDOVR
        {
            return m_message;
        }

    private:
        char const* m_message;
    };

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

    if (XTESTS_START_RUNNER("test.unit.stlsoft.std.exception", verbosity))
    {
        XTESTS_RUN_CASE(TEST_NARROW_SHIMS_ARE_WHAT);
        XTESTS_RUN_CASE(TEST_c_str_data_w_MATCHES_WHAT);
        XTESTS_RUN_CASE(TEST_c_str_len_w_MATCHES_WHAT);
        XTESTS_RUN_CASE(TEST_c_str_ptr_w_MATCHES_DATA_W);
        XTESTS_RUN_CASE(TEST_c_str_ptr_null_w_MATCHES_DATA_W);
        XTESTS_RUN_CASE(TEST_EMPTY_WHAT);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_NARROW_SHIMS_ARE_WHAT()
{
    char const                  message[]   =   "wide-shim-subject";
    exception_subject const     x(message);
    size_t const                len         =   ::strlen(message);

    TEST_MS_EQ(message, stlsoft::c_str_data_a(x));
    TEST_MS_EQ(message, stlsoft::c_str_ptr_a(x));
    TEST_MS_EQ(message, stlsoft::c_str_ptr_null_a(x));
    TEST_INT_EQ(len, stlsoft::c_str_len_a(x));

    TEST_MS_EQ(message, stlsoft::c_str_data(x));
    TEST_MS_EQ(message, stlsoft::c_str_ptr(x));
    TEST_MS_EQ(message, stlsoft::c_str_ptr_null(x));
    TEST_INT_EQ(len, stlsoft::c_str_len(x));
}

static void TEST_c_str_data_w_MATCHES_WHAT()
{
    /* An ASCII what() widens one byte to one wchar_t, so the check does not
     * call mbstowcs().
     */
    char const                  message[]   =   "wide-shim-subject";
    exception_subject const     x(message);
    size_t const                len         =   ::strlen(message);
    wchar_t                     expected[64];

    TEST_BOOLEAN_TRUE(len < STLSOFT_NUM_ELEMENTS(expected));

    widen_ascii_(expected, STLSOFT_NUM_ELEMENTS(expected), message, len);

    TEST_WS_EQ(expected, stlsoft::c_str_data_w(x).data());
    TEST_INT_EQ(len, stlsoft::c_str_data_w(x).size());
}

static void TEST_c_str_len_w_MATCHES_WHAT()
{
    char const                  message[]   =   "wide-shim-subject";
    exception_subject const     x(message);

    TEST_INT_EQ(::strlen(message), stlsoft::c_str_len_w(x));
}

static void TEST_c_str_ptr_w_MATCHES_DATA_W()
{
    exception_subject const x("wide-shim-subject");

    TEST_WS_EQ(stlsoft::c_str_data_w(x).data(), stlsoft::c_str_ptr_w(x).data());
    TEST_INT_EQ(stlsoft::c_str_data_w(x).size(), stlsoft::c_str_ptr_w(x).size());
}

static void TEST_c_str_ptr_null_w_MATCHES_DATA_W()
{
    exception_subject const x("wide-shim-subject");

    TEST_WS_EQ(stlsoft::c_str_data_w(x).data(), stlsoft::c_str_ptr_null_w(x).data());
    TEST_INT_EQ(stlsoft::c_str_data_w(x).size(), stlsoft::c_str_ptr_null_w(x).size());
}

static void TEST_EMPTY_WHAT()
{
    exception_subject const x("");

    TEST_MS_EQ("", stlsoft::c_str_data_a(x));
    TEST_PTR_EQ(ss_nullptr_k, stlsoft::c_str_ptr_null_a(x));
    TEST_INT_EQ(0u, stlsoft::c_str_len_a(x));

    TEST_WS_EQ(L"", stlsoft::c_str_data_w(x).data());
    TEST_INT_EQ(0u, stlsoft::c_str_data_w(x).size());
    TEST_INT_EQ(0u, stlsoft::c_str_len_w(x));

    wchar_t const* const wide_null = stlsoft::c_str_ptr_null_w(x);

    TEST_PTR_EQ(ss_nullptr_k, wide_null);
}
} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */

