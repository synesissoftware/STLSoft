/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/system/pid_sequence/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/system/pid_sequence.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/system/pid_sequence.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_pid_sequence_CONTAINS_SELF();
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
        XTESTS_RUN_CASE(TEST_pid_sequence_CONTAINS_SELF);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_pid_sequence_CONTAINS_SELF()
{
    unixstl::pid_sequence pids;

    TEST_BOOLEAN_FALSE(pids.empty());

    pid_t const self = ::getpid();
    bool found = false;

    for (unixstl::pid_sequence::const_iterator i = pids.begin(); i != pids.end(); ++i)
    {
        if (*i == self)
        {
            found = true;
            break;
        }
    }

    TEST_BOOLEAN_TRUE(found);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
