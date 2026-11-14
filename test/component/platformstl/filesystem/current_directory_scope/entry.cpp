#include <platformstl/filesystem/current_directory_scope.hpp>
#include <platformstl/filesystem/current_directory.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif

static void TEST_SCOPE_RESTORES();

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_SCOPE_RESTORES);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void TEST_SCOPE_RESTORES()
{
    using ::xtests::cpp::util::temp_directory;
    platformstl::current_directory_a const original;
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);
    {
        platformstl::current_directory_scope scope(td.c_str());
        platformstl::current_directory_a const changed;

#ifndef _WIN32
        char resolved_td[PATH_MAX];
        char resolved_cwd[PATH_MAX];
        XTESTS_REQUIRE(TEST(NULL != realpath(td.c_str(), resolved_td)));
        XTESTS_REQUIRE(TEST(NULL != realpath(stlsoft::c_str_ptr_a(changed), resolved_cwd)));
        TEST_MS_EQ(resolved_td, resolved_cwd);
#else
        TEST_MS_EQ(stlsoft::c_str_ptr_a(td), stlsoft::c_str_ptr_a(changed));
#endif
    }
    platformstl::current_directory_a const restored;
    TEST_MS_EQ(stlsoft::c_str_ptr_a(original), stlsoft::c_str_ptr_a(restored));
}
