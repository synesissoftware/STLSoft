
/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.platformstl.system.pid_sequence/entry.cpp
 *
 * Purpose: Unit-tests for `platformstl::pid_sequence`.
 *
 * Created: 22nd August 2025
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <platformstl/system/pid_sequence.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <algorithm>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CONTAINS_SYSTEM_PIDS();
    static void TEST_NOT_CONTAINS_SYSTEM_PIDS();
    static void TEST_CONTAINS_THIS_PROCESS_PID();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.platformstl.system.pid_sequence", verbosity))
    {
        XTESTS_RUN_CASE(TEST_CONTAINS_SYSTEM_PIDS);
        XTESTS_RUN_CASE(TEST_NOT_CONTAINS_SYSTEM_PIDS);
        XTESTS_RUN_CASE(TEST_CONTAINS_THIS_PROCESS_PID);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

    using platformstl::pid_sequence;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CONTAINS_SYSTEM_PIDS()
{
    pid_sequence pids(0);

#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

# if 0
# elif defined(UNIXSTL_OS_IS_LINUX)

# elif defined(UNIXSTL_OS_IS_MACOSX)

    TEST(pids.end() != std::find(pids.cbegin(), pids.cend(), pid_sequence::schedProcessId()));
# else

#  error Operating system not currently supported
# endif
    TEST(pids.end() != std::find(pids.cbegin(), pids.cend(), pid_sequence::initProcessId()));
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    TEST(pids.end() != std::find(pids.cbegin(), pids.cend(), pid_sequence::idleProcessId()));
    TEST(pids.end() != std::find(pids.cbegin(), pids.cend(), pid_sequence::systemProcessId()));
#else
#endif

    TEST(pids.end() == std::find(pids.cbegin(), pids.cend(), std::numeric_limits<pid_sequence::value_type>::max()));
}

static void TEST_NOT_CONTAINS_SYSTEM_PIDS()
{
    pid_sequence pids;

#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

# if 0
# elif defined(UNIXSTL_OS_IS_LINUX)

# elif defined(UNIXSTL_OS_IS_MACOSX)

    TEST(pids.end() == std::find(pids.cbegin(), pids.cend(), pid_sequence::schedProcessId()));
# else

#  error Operating system not currently supported
# endif
    TEST(pids.end() == std::find(pids.cbegin(), pids.cend(), pid_sequence::initProcessId()));
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    TEST(pids.end() == std::find(pids.cbegin(), pids.cend(), pid_sequence::idleProcessId()));
    TEST(pids.end() == std::find(pids.cbegin(), pids.cend(), pid_sequence::systemProcessId()));
#else
#endif

    TEST(pids.end() == std::find(pids.cbegin(), pids.cend(), std::numeric_limits<pid_sequence::value_type>::max()));
}

static void TEST_CONTAINS_THIS_PROCESS_PID()
{
    pid_sequence pids;

#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

    pid_t const pid = ::getpid();

    TEST(pids.end() != std::find(pids.cbegin(), pids.cend(), pid));
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    DWORD const pid = ::GetCurrentProcessId();

    TEST(pids.end() != std::find(pids.cbegin(), pids.cend(), pid));
#else
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

