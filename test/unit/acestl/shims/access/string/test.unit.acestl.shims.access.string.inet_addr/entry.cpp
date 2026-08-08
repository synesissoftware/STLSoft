/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.acestl.shims.access.string.inet_addr/entry.cpp
 *
 * Purpose: Unit-tests for string-access-shims for `ACE_INET_Addr`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#define STLSOFT_MINIMUM_SAS_INCLUDES


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <acestl/shims/access/string/inet_addr.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <ace/INET_Addr.h>

#include <stdlib.h>
#include <string.h>


namespace {

static void TEST_calls_possible();
static void TEST_loopback_addr();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.acestl.shims.access.string.inet_addr", verbosity))
    {
        XTESTS_RUN_CASE(TEST_calls_possible);
        XTESTS_RUN_CASE(TEST_loopback_addr);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_calls_possible()
{
    ACE_INET_Addr const addr;

    stlsoft::c_str_data_a(addr);
    stlsoft::c_str_data(addr);

    stlsoft::c_str_len_a(addr);
    stlsoft::c_str_len(addr);

    stlsoft::c_str_ptr_a(addr);
    stlsoft::c_str_ptr(addr);

    stlsoft::c_str_ptr_null_a(addr);
    stlsoft::c_str_ptr_null(addr);

    TEST_PASSED();
}

static void TEST_loopback_addr()
{
    ACE_INET_Addr addr;

    TEST_INT_EQ(0, addr.set(static_cast<u_short>(0), INADDR_LOOPBACK));

    stlsoft::basic_shim_string<char> const s = stlsoft::c_str_ptr_a(addr);

    TEST_BOOLEAN_TRUE(s.size() > 0u);
    TEST_BOOLEAN_TRUE(::strstr(s.data(), "127.0.0.1") != NULL);
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
