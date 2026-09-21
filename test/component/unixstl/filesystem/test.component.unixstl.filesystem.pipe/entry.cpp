/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.filesystem.pipe/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/filesystem/pipe.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/filesystem/pipe.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_anonymous_pipe_read_write(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.filesystem.pipe", verbosity))
    {
        XTESTS_RUN_CASE(test_anonymous_pipe_read_write);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_anonymous_pipe_read_write()
{
    unixstl::pipe pipe;

    char const msg[] = "pipe-data";
    ssize_t const written = ::write(pipe.write_handle(), msg, sizeof(msg));

    TEST_INT_EQ((ssize_t)sizeof(msg), written);

    char buf[32] = { 0 };
    ssize_t const readn = ::read(pipe.read_handle(), buf, sizeof(buf));

    TEST_INT_EQ((ssize_t)sizeof(msg), readn);
    TEST_MS_EQ(msg, buf);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
