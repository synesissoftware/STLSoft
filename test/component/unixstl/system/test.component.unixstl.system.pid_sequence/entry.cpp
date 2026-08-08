/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.system.pid_sequence/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/system/pid_sequence.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/system/pid_sequence.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_pid_sequence_contains_self()
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


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.system.pid_sequence", verbosity))
    {
        XTESTS_RUN_CASE(test_pid_sequence_contains_self);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
