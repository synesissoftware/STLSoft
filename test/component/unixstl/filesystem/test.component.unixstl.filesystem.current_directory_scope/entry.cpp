/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.filesystem.current_directory_scope/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/filesystem/current_directory_scope.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/current_directory_scope.hpp>
#include <unixstl/filesystem/path.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>

#include <stlsoft/stlsoft.h>

#include <string>
#include <unistd.h>
#include <stdlib.h>


namespace {

using xtests::cpp::util::temp_directory;

static void test_scope_restores_directory()
{
    char original[PATH_MAX];
    XTESTS_REQUIRE(TEST(NULL != getcwd(original, sizeof(original))));

    std::string const saved(original);

    {
        temp_directory td(temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);
        unixstl::current_directory_scope_a scope(td.c_str());

        char now[PATH_MAX];
        XTESTS_REQUIRE(TEST(NULL != getcwd(now, sizeof(now))));

        char resolved_td[PATH_MAX];
        char resolved_now[PATH_MAX];
        XTESTS_REQUIRE(TEST(NULL != realpath(td.c_str(), resolved_td)));
        XTESTS_REQUIRE(TEST(NULL != realpath(now, resolved_now)));
        TEST_MS_EQ(resolved_td, resolved_now);
    }

    char restored[PATH_MAX];
    XTESTS_REQUIRE(TEST(NULL != getcwd(restored, sizeof(restored))));
    TEST_MS_EQ(saved, restored);
}

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.filesystem.current_directory_scope", verbosity))
    {
        XTESTS_RUN_CASE(test_scope_restores_directory);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
