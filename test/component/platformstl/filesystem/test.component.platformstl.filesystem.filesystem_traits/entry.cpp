#include <platformstl/filesystem/filesystem_traits.hpp>
#include <platformstl/filesystem/path.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_file_exists(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.filesystem_traits", verbosity))
    {
        XTESTS_RUN_CASE(test_file_exists);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_file_exists(void)
{
    typedef platformstl::filesystem_traits<char> fs_traits_t;
    using ::xtests::cpp::util::temp_directory;

    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::EmptyOnClose | temp_directory::RemoveOnClose);

    TEST_BOOLEAN_TRUE(fs_traits_t::file_exists(td.c_str()));
    TEST_BOOLEAN_TRUE(fs_traits_t::is_directory(td.c_str()));

    platformstl::path_a missing(td.c_str());
    missing /= "does-not-exist";

    TEST_BOOLEAN_FALSE(fs_traits_t::file_exists(missing.c_str()));
}
