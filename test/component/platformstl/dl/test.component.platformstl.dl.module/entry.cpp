#include <platformstl/dl/module.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#if defined(PLATFORMSTL_OS_IS_UNIX)
# include <dlfcn.h>
#endif

static void test_load_system_library(void); // anonymous namespace

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.component.platformstl.dl.module", verbosity))
    {
        XTESTS_RUN_CASE(test_load_system_library);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_load_system_library(void)
{
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
    platformstl::dl_module mod("kernel32.dll");
    TEST_PTR_NE(NULL, mod.get());
#elif defined(PLATFORMSTL_OS_IS_UNIX)
# if defined(UNIXSTL_OS_IS_MACOSX)
    char const* lib = "libSystem.B.dylib";
# elif defined(UNIXSTL_OS_IS_LINUX)
    char const* lib = "libc.so.6";
# else
    char const* lib = "libc.so";
# endif
    platformstl::dl_module mod(lib, RTLD_LAZY);
    TEST_PTR_NE(NULL, mod.get());
    TEST_PTR_NE(NULL, mod.get_symbol("malloc"));
#endif
}
