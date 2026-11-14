/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/unixstl/dl/module/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/dl/module.hpp`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <unixstl/dl/module.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <dlfcn.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_LOAD_SELF_AND_LOOKUP_MAIN();
    static void TEST_RAII_MODULE_LOADS_LIBC();
    static void TEST_get_module_handle_SHIM();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_LOAD_SELF_AND_LOOKUP_MAIN);
        XTESTS_RUN_CASE(TEST_RAII_MODULE_LOADS_LIBC);
        XTESTS_RUN_CASE(TEST_get_module_handle_SHIM);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_LOAD_SELF_AND_LOOKUP_MAIN()
{
    void* h = ::dlopen(NULL, RTLD_LAZY);

    XTESTS_REQUIRE(TEST(NULL != h));

    /* A PIE executable does not export its own symbols. dlopen(NULL)
     * still searches shared objects loaded at startup, so malloc is
     * visible.
     */
    void* sym = unixstl::dl_module::get_symbol(h, "malloc");

    TEST_PTR_NE(NULL, sym);

    unixstl::dl_module::unload(h);
}

static void TEST_RAII_MODULE_LOADS_LIBC()
{
#if defined(UNIXSTL_OS_IS_MACOSX)
    char const* lib = "libSystem.B.dylib";
#elif defined(UNIXSTL_OS_IS_LINUX)
    char const* lib = "libc.so.6";
#else
    char const* lib = "libc.so";
#endif

    unixstl::dl_module m(lib, RTLD_LAZY);

    TEST_PTR_NE(NULL, m.get());

    void* sym = m.get_symbol("malloc");
    TEST_PTR_NE(NULL, sym);
}

static void TEST_get_module_handle_SHIM()
{
#if defined(UNIXSTL_OS_IS_MACOSX)
    char const* lib = "libSystem.B.dylib";
#elif defined(UNIXSTL_OS_IS_LINUX)
    char const* lib = "libc.so.6";
#else
    char const* lib = "libc.so";
#endif

    unixstl::dl_module m(lib, RTLD_LAZY);

    TEST_PTR_EQ(m.get(), unixstl::get_module_handle(m));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
