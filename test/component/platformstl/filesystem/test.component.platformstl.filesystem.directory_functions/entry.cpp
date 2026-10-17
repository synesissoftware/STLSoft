#include <platformstl/filesystem/directory_functions.hpp>
#include <platformstl/filesystem/filesystem_traits.hpp>
#include <platformstl/filesystem/path.hpp>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_create_and_remove(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.directory_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_create_and_remove);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_create_and_remove(void)
{
    using ::xtests::cpp::util::temp_directory;
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);
    platformstl::path_a sub(td.c_str());
    sub /= "subdir";
    TEST_BOOLEAN_TRUE(platformstl::create_directory_recurse(sub.c_str()));
    TEST_BOOLEAN_TRUE(platformstl::filesystem_traits<char>::is_directory(sub.c_str()));
    TEST_BOOLEAN_TRUE(platformstl::remove_directory_recurse(sub.c_str()));
}

