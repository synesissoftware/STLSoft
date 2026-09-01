/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.acestl.shims.access.string.string_base/entry.cpp
 *
 * Purpose: Unit-tests for string-access-shims for `ACE_String_Base`.
 *
 * Created: 7th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#define STLSOFT_MINIMUM_SAS_INCLUDES


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <acestl/shims/access/string/string_base.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* ACE header files */
#include <ace/SString.h>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_calls_possible();
    static void TEST_empty_string();
    static void TEST_non_empty_string();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.acestl.shims.access.string.string_base", verbosity))
    {
        XTESTS_RUN_CASE(TEST_calls_possible);
        XTESTS_RUN_CASE(TEST_empty_string);
        XTESTS_RUN_CASE(TEST_non_empty_string);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_calls_possible()
{
    ACE_CString const s("acestl");

    stlsoft::c_str_data_a(s);
    stlsoft::c_str_data(s);

    stlsoft::c_str_len_a(s);
    stlsoft::c_str_len(s);

    stlsoft::c_str_ptr_a(s);
    stlsoft::c_str_ptr(s);

    stlsoft::c_str_ptr_null_a(s);
    stlsoft::c_str_ptr_null(s);

    TEST_PASSED();
}

static void TEST_empty_string()
{
    ACE_CString const s;

    TEST_INT_EQ(0u, stlsoft::c_str_len_a(s));
    TEST_INT_EQ(0u, stlsoft::c_str_len(s));

    TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_a(s));
    TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null(s));

    TEST_MS_EQ("", stlsoft::c_str_ptr_a(s));
    TEST_MS_EQ("", stlsoft::c_str_ptr(s));
}

static void TEST_non_empty_string()
{
    char const* const expected = "ACE STL";
    ACE_CString const s(expected);

    TEST_INT_EQ(::strlen(expected), stlsoft::c_str_len_a(s));
    TEST_INT_EQ(::strlen(expected), stlsoft::c_str_len(s));

    TEST_MS_EQ(expected, stlsoft::c_str_ptr_a(s));
    TEST_MS_EQ(expected, stlsoft::c_str_ptr(s));

    TEST_MS_EQ(expected, stlsoft::c_str_data_a(s));
    TEST_MS_EQ(expected, stlsoft::c_str_data(s));

    TEST_PTR_NE(NULL, stlsoft::c_str_ptr_null_a(s));
    TEST_MS_EQ(expected, stlsoft::c_str_ptr_null_a(s));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
