#include <platformstl/exception/filesystem_exception.hpp>
#include <platformstl/filesystem/memory_mapped_file.hpp>
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_missing_file_throws(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.exception.filesystem_exception", verbosity))
    {
        XTESTS_RUN_CASE_THAT_THROWS(test_missing_file_throws, platformstl::filesystem_exception);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_missing_file_throws(void)
{
    using ::xtests::cpp::util::temp_file;
    temp_file f(temp_file::DeleteOnOpen | temp_file::DeleteOnClose);
    platformstl::memory_mapped_file mmf(f.c_str());
    TEST_FAIL("should not get here");
}
} // anonymous namespace

