#include <platformstl/filesystem/current_directory_scope.hpp>
#include <platformstl/filesystem/current_directory.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_scope_restores(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.current_directory_scope", verbosity))
    {
        XTESTS_RUN_CASE(test_scope_restores);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_scope_restores(void)
{
    using ::xtests::cpp::util::temp_directory;
    platformstl::current_directory_a const original;
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);
    {
        platformstl::current_directory_scope scope(td.c_str());
        platformstl::current_directory_a const changed;
        TEST_MS_EQ(td.c_str(), stlsoft::c_str_ptr_a(changed));
    }
    platformstl::current_directory_a const restored;
    TEST_MS_EQ(stlsoft::c_str_ptr_a(original), stlsoft::c_str_ptr_a(restored));
}
} // anonymous namespace
