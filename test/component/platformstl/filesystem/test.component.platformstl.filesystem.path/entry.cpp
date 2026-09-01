#include <platformstl/filesystem/path.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

namespace { static void test_join(void); static void test_construct_filename(void); }

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.path", verbosity))
    {
        XTESTS_RUN_CASE(test_join);
        XTESTS_RUN_CASE(test_construct_filename);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

namespace {

static void test_join(void)
{
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
    platformstl::path_a p("C:/temp");
    p /= "file.txt";
    TEST_MS_EQ("C:/temp/file.txt", stlsoft::c_str_ptr_a(p));
#else
    platformstl::path_a p("dir-1");
    p /= "file.txt";
    TEST_MS_EQ("dir-1/file.txt", stlsoft::c_str_ptr_a(p));
#endif
}

static void test_construct_filename(void)
{
    platformstl::path_a p("file.ext");
    TEST_BOOLEAN_FALSE(p.empty());
    TEST_MS_EQ("file.ext", stlsoft::c_str_ptr_a(p));
}
} // anonymous namespace

