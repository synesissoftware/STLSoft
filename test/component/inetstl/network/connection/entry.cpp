/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/inetstl/network/connection/entry.cpp
 *
 * Purpose: Component-tests for `inetstl::basic_connection`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <inetstl/network/connection.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/exception/throw_policies.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_DEFAULT_CONNECTION();
    static void TEST_FAILED_CONNECT_WITH_NULL_POLICY();
    static void TEST_CLOSE_ON_UNCONNECTED();
    static void TEST_get_handle();
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
        XTESTS_RUN_CASE(TEST_DEFAULT_CONNECTION);
        XTESTS_RUN_CASE(TEST_FAILED_CONNECT_WITH_NULL_POLICY);
        XTESTS_RUN_CASE(TEST_CLOSE_ON_UNCONNECTED);
        XTESTS_RUN_CASE(TEST_get_handle);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

typedef inetstl::basic_session<char, stlsoft::null_exception_policy>    session_null_x_t;
    typedef inetstl::basic_connection<char, stlsoft::null_exception_policy> connection_null_x_t;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_DEFAULT_CONNECTION()
{
    connection_null_x_t conn;

    TEST_BOOLEAN_FALSE(conn.is_connected());
    TEST_PTR_EQ(NULL, conn.get());
    TEST_INT_EQ(ERROR_SUCCESS, conn.last_error());
}

static void TEST_FAILED_CONNECT_WITH_NULL_POLICY()
{
    session_null_x_t    sess;
    connection_null_x_t conn;

    TEST_BOOLEAN_TRUE(sess.is_open());

    stlsoft::ss_bool_t const r = conn.connect(
            sess.get()
        ,   "invalid-host-that-does-not-exist.invalid"
        ,   21
        ,   NULL
        ,   NULL
        ,   INTERNET_SERVICE_FTP
        ,   0
        ,   0
        );

    TEST_BOOLEAN_FALSE(r);
    TEST_BOOLEAN_FALSE(conn.is_connected());
    TEST_PTR_EQ(NULL, conn.get());
    TEST_INT_NE(ERROR_SUCCESS, conn.last_error());
}

static void TEST_CLOSE_ON_UNCONNECTED()
{
    connection_null_x_t conn;

    conn.close();

    TEST_BOOLEAN_FALSE(conn.is_connected());
    TEST_PTR_EQ(NULL, conn.get());
}

static void TEST_get_handle()
{
    connection_null_x_t conn;

    TEST_PTR_EQ(conn.get(), get_handle(conn));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
