/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.inetstl.network.session/entry.cpp
 *
 * Purpose: Component-tests for `inetstl::basic_session`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <inetstl/network/session.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/exception/throw_policies.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_default_session(void);
    static void TEST_session_with_agent(void);
    static void TEST_session_open_close(void);
    static void TEST_session_detach(void);
    static void TEST_get_handle(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.inetstl.network.session", verbosity))
    {
        XTESTS_RUN_CASE(TEST_default_session);
        XTESTS_RUN_CASE(TEST_session_with_agent);
        XTESTS_RUN_CASE(TEST_session_open_close);
        XTESTS_RUN_CASE(TEST_session_detach);
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

typedef inetstl::basic_session<char, stlsoft::null_exception_policy> session_null_x_t;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_default_session()
{
    inetstl::session_a sess;

    TEST_BOOLEAN_TRUE(sess.is_open());
    TEST_PTR_NE(NULL, sess.get());
}

static void TEST_session_with_agent()
{
    inetstl::session_a sess("InetSTL test agent");

    TEST_BOOLEAN_TRUE(sess.is_open());
    TEST_PTR_NE(NULL, sess.get());
}

static void TEST_session_open_close()
{
    session_null_x_t sess;

    TEST_BOOLEAN_TRUE(sess.is_open());

    sess.close();

    TEST_BOOLEAN_FALSE(sess.is_open());
    TEST_PTR_EQ(NULL, sess.get());

    TEST_BOOLEAN_TRUE(sess.open("InetSTL test agent", INTERNET_OPEN_TYPE_DIRECT));
    TEST_BOOLEAN_TRUE(sess.is_open());
    TEST_PTR_NE(NULL, sess.get());

    sess.close();
    TEST_BOOLEAN_FALSE(sess.is_open());
}

static void TEST_session_detach()
{
    inetstl::session_a sess("InetSTL test agent");
    HINTERNET const    h = sess.get();

    TEST_BOOLEAN_TRUE(sess.is_open());

    HINTERNET const hDetached = sess.detach();

    TEST_PTR_EQ(h, hDetached);
    TEST_BOOLEAN_FALSE(sess.is_open());
    TEST_PTR_EQ(NULL, sess.get());

    ::InternetCloseHandle(hDetached);
}

static void TEST_get_handle()
{
    inetstl::session_a sess;

    TEST_PTR_EQ(sess.get(), get_handle(sess));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
