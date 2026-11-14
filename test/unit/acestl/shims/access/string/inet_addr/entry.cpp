/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/acestl/shims/access/string/inet_addr/entry.cpp
 *
 * Purpose: Unit-tests for string-access-shims for `ACE_INET_Addr`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <acestl/shims/access/string/inet_addr.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <ace/INET_Addr.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CALLS_POSSIBLE();
    static void TEST_LOOPBACK_ADDR();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_CALLS_POSSIBLE);
        XTESTS_RUN_CASE(TEST_LOOPBACK_ADDR);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CALLS_POSSIBLE()
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

static void TEST_LOOPBACK_ADDR()
{
    ACE_INET_Addr addr;

    TEST_INT_EQ(0, addr.set(static_cast<u_short>(0), INADDR_LOOPBACK));

    stlsoft::basic_shim_string<char> const s = stlsoft::c_str_ptr_a(addr);

    TEST_BOOLEAN_TRUE(s.size() > 0u);
    TEST_BOOLEAN_TRUE(::strstr(s.data(), "127.0.0.1") != NULL);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
