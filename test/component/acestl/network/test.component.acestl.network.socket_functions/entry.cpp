/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.acestl.network.socket_functions/entry.cpp
 *
 * Purpose: Component-tests for `acestl::close_and_deregister`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <acestl/network/socket_functions.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <ace/Reactor.h>
#include <ace/SOCK_Stream.h>

#include <stdlib.h>


namespace {

static void TEST_close_and_deregister_invalid_handle();
static void TEST_close_and_deregister_open_socket();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.acestl.network.socket_functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_close_and_deregister_invalid_handle);
        XTESTS_RUN_CASE(TEST_close_and_deregister_open_socket);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_close_and_deregister_invalid_handle()
{
    ACE_SOCK_Stream sk;

    TEST_BOOLEAN_FALSE(acestl::close_and_deregister(sk, NULL));
}

static void TEST_close_and_deregister_open_socket()
{
    ACE_SOCK_Stream sk;

    TEST_INT_EQ(0, sk.open());

    TEST_BOOLEAN_TRUE(acestl::close_and_deregister(sk, NULL));
    TEST_BOOLEAN_FALSE(acestl::close_and_deregister(sk, NULL));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
