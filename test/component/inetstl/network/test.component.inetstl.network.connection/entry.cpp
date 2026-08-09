/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.inetstl.network.connection/entry.cpp
 *
 * Purpose: Component-tests for `inetstl::basic_connection`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <inetstl/network/connection.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/exception/throw_policies.hpp>
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_default_connection();
    static void TEST_failed_connect_with_null_policy();
    static void TEST_close_on_unconnected();
    static void TEST_get_handle();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.inetstl.network.connection", verbosity))
    {
        XTESTS_RUN_CASE(TEST_default_connection);
        XTESTS_RUN_CASE(TEST_failed_connect_with_null_policy);
        XTESTS_RUN_CASE(TEST_close_on_unconnected);
        XTESTS_RUN_CASE(TEST_get_handle);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    typedef inetstl::basic_session<char, stlsoft::null_exception_policy>    session_null_x_t;
    typedef inetstl::basic_connection<char, stlsoft::null_exception_policy> connection_null_x_t;


static void TEST_default_connection()
{
    connection_null_x_t conn;

    TEST_BOOLEAN_FALSE(conn.is_connected());
    TEST_PTR_EQ(NULL, conn.get());
    TEST_INT_EQ(ERROR_SUCCESS, conn.last_error());
}

static void TEST_failed_connect_with_null_policy()
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

static void TEST_close_on_unconnected()
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
