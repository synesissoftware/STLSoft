#include <platformstl/filesystem/handles/memory_mapped_file_view_handle.hpp>
#include <platformstl/filesystem/memory_mapped_file.hpp>
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>

namespace { static void test_map_view(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.handles.memory_mapped_file_view_handle", verbosity))
    {
        XTESTS_RUN_CASE(test_map_view);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_map_view(void)
{
    using ::xtests::cpp::util::temp_file;
    char const content[] = "testdata";
    temp_file f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen,
                content, sizeof(content) - 1);
    platformstl::memory_mapped_file mmf(f.c_str());
    TEST_PTR_NE(NULL, mmf.memory());
    TEST_INT_GE(sizeof(content) - 1, mmf.size());
    TEST_BOOLEAN_TRUE(0 == ::memcmp(content, mmf.memory(), sizeof(content) - 1));
}
} // anonymous namespace

