/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.dl.dl_call/entry.cpp
 *
 * Purpose: Component test for `unixstl::dl_call`.
 *
 * Created: 9th October 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <unixstl/dl/dl_call.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/smartptr/scoped_handle.hpp>
#include <stlsoft/smartptr/scoped_lambda.hpp>
#include <stlsoft/std/cstring.hpp>
#include <unixstl/dl/module.hpp>
#include <unixstl/filesystem/path.hpp>

/* Standard C++ header files */
#include <memory>
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * types
 */

namespace {

    typedef unixstl::dl_module                              unixstl_module_t;
    typedef unixstl_module_t::module_handle_type            h_module_t;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_1_00();
    static void test_example_so_abs1();
    static void test_example_so_add2();
    static void test_example_so_add3();
    static void test_example_so_add10();

    static char*        s_cwd;
    static h_module_t   h_example_so;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace {

    static
    std::unique_ptr<unixstl_module_t>
    load_example_so(char const* /* argv0 */)
    {
#if 0
#elif defined(UNIXSTL_OS_IS_LINUX)

        char const* ModuleBasename = "libexample_so.so";
#elif defined(UNIXSTL_OS_IS_MACOSX)

        char const* ModuleBasename = "libexample_so.dylib";
#else

# error Specified only for Linux and macOS
#endif

        // strategy for looking (UNIX):
        //
        // 1. Program directory;
        // 2. Assume built with CMake and so in the project build tree;
        // 3. Try looking in /usr/local/lib;
        // N. Try process dy-load paths

        // 1. Program directory;
        {
            UNIXSTL_ASSERT(NULL != s_cwd);

            unixstl::path module_path(s_cwd);

            module_path /= ModuleBasename;

            h_module_t hm = unixstl_module_t::load(module_path.c_str());

            if (NULL != hm)
            {
                return std::unique_ptr<unixstl_module_t>(new unixstl_module_t(hm));
            }
        }

        // 2. Assume built with CMake and so in the project build tree;
        {
            UNIXSTL_ASSERT(NULL != s_cwd);

            unixstl::path module_path(s_cwd);

            // char const* Path = ". . ./STLSoft/STLSoft-1.11/_build/test/fixtures/example_so/libexample_so.dylib";
            // char const* Path = ". . ./STLSoft/STLSoft-1.11/_build/test/component/unixstl/dl/test.component.unixstl.dl.dl_call"

            module_path /= "../../../..";
            module_path /= "fixtures/example_so/";
            module_path /= ModuleBasename;

            h_module_t hm = unixstl_module_t::load(module_path.c_str());

            if (NULL != hm)
            {
                return std::unique_ptr<unixstl_module_t>(new unixstl_module_t(hm));
            }
        }

        // 3. Try looking in /usr/local/lib;
        {
            unixstl::path module_path("/usr/local/lib/");

            module_path /= ModuleBasename;

            h_module_t hm = unixstl_module_t::load(module_path.c_str());

            if (NULL != hm)
            {
                return std::unique_ptr<unixstl_module_t>(new unixstl_module_t(hm));
            }
        }

        // N. Try process dy-load paths
        {
            h_module_t hm = unixstl_module_t::load(ModuleBasename);

            if (NULL != hm)
            {
                return std::unique_ptr<unixstl_module_t>(new unixstl_module_t(hm));
            }
        }

        return ss_nullptr_k;
    }
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    {
        unixstl::path p(argv[0]);

        p.pop();

        s_cwd = stlsoft::strdup(p.c_str());

        if (NULL == s_cwd)
        {
            throw std::bad_alloc();
        }
    }

    stlsoft::scoped_handle<void*> scoper1(s_cwd, ::free);


    if (XTESTS_START_RUNNER("test.component.unixstl.dl.dl_call", verbosity))
    {
        XTESTS_RUN_CASE(test_1_00);

        std::unique_ptr<unixstl_module_t> module = load_example_so(argv[0]);

        if (module)
        {
            h_example_so = unixstl::get_module_handle(*module);

#if __cplusplus >= 201103L

            stlsoft::scoped_lambda scoper2([] {

                h_example_so = NULL;
            });
#endif

            XTESTS_RUN_CASE(test_example_so_abs1);
            XTESTS_RUN_CASE(test_example_so_add2);
            XTESTS_RUN_CASE(test_example_so_add3);
            XTESTS_RUN_CASE(test_example_so_add10);

#if __cplusplus < 201103L

            h_example_so = NULL;
#endif
        }

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_1_00()
{
}

static void test_example_so_abs1()
{
    try
    {
        UNIXSTL_ASSERT(NULL != h_example_so);

        int const r = unixstl::dl_call<int>(h_example_so, "abs1", -123);

        TEST_INT_EQ(123, r);
    }
    catch (unixstl::missing_entry_point_exception& x)
    {
        TEST_FAIL_WITH_QUALIFIER("failed to load function", x.what());
    }
}

static void test_example_so_add2()
{
    try
    {
        UNIXSTL_ASSERT(NULL != h_example_so);

        int const r = unixstl::dl_call<int>(h_example_so, "add2", 101, 22);

        TEST_INT_EQ(123, r);
    }
    catch (unixstl::missing_entry_point_exception& x)
    {
        TEST_FAIL_WITH_QUALIFIER("failed to load function", x.what());
    }
}

static void test_example_so_add3()
{
    try
    {
        UNIXSTL_ASSERT(NULL != h_example_so);

        int const r = unixstl::dl_call<int>(h_example_so, "add3", 101, 2, 20);

        TEST_INT_EQ(123, r);
    }
    catch (unixstl::missing_entry_point_exception& x)
    {
        TEST_FAIL_WITH_QUALIFIER("failed to load function", x.what());
    }
}

static void test_example_so_add10()
{
    try
    {
        UNIXSTL_ASSERT(NULL != h_example_so);

        int const r = unixstl::dl_call<int>(h_example_so, "add10", 1, 2, 10, 20, 30, 6, 7, 8, 9, 30);

        TEST_INT_EQ(123, r);
    }
    catch (unixstl::missing_entry_point_exception& x)
    {
        TEST_FAIL_WITH_QUALIFIER("failed to load function", x.what());
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

