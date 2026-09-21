/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.filesystem.readonly_memory_mapped_file/entry.cpp
 *
 * Purpose: Component test for `platformstl::readonly_memory_mapped_file`.
 *
 * Created: sometime in 2010s
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <platformstl/filesystem/readonly_memory_mapped_file.hpp>
#include <platformstl/exception/filesystem_exception.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>

/* STLSoft header files */
#include <stlsoft/synch/refcount_policies/refcount_policy_single_threaded.hpp>
#include <platformstl/synch/refcount_policies/refcount_policy_multi_threaded.hpp>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_types_exist();

    namespace single_threaded {

        static void test_nonexisting_file();
        static void test_a_new_file_with_fixed_content();
    } // namespace single_threaded
    namespace multi_threaded {

        static void test_nonexisting_file();
        static void test_a_new_file_with_fixed_content();
    } // namespace multi_threaded
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.platformstl.filesystem.readonly_memory_mapped_file", verbosity))
    {
        XTESTS_RUN_CASE(test_types_exist);
        XTESTS_RUN_CASE_THAT_THROWS(single_threaded::test_nonexisting_file, platformstl::filesystem_exception);
        XTESTS_RUN_CASE_THAT_THROWS(multi_threaded::test_nonexisting_file, platformstl::filesystem_exception);
        XTESTS_RUN_CASE(single_threaded::test_a_new_file_with_fixed_content);
        XTESTS_RUN_CASE(multi_threaded::test_a_new_file_with_fixed_content);

        // XTESTS_RUN_CASE(test_empty_directory);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using ::xtests::cpp::util::temp_file;


static void test_types_exist()
{
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::readonly_memory_mapped_file_base<stlsoft::refcount_policy_single_threaded>));
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::readonly_memory_mapped_file_base<platformstl::refcount_policy_multi_threaded>));
}

namespace single_threaded {

    typedef platformstl::readonly_memory_mapped_file_base<stlsoft::refcount_policy_single_threaded> rommf_t;


    static void test_nonexisting_file()
    {
        temp_file f(temp_file::DeleteOnOpen | temp_file::DeleteOnClose);

        rommf_t mmf(f.c_str());

        TEST_FAIL("should not get here");

        STLSOFT_SUPPRESS_UNUSED(mmf);
    }

    static void test_a_new_file_with_fixed_content()
    {
        stlsoft::byte_t bytes[4 * 1024];

        std::fill_n(&bytes[0], STLSOFT_NUM_ELEMENTS(bytes), stlsoft::byte_t(123));

        temp_file       f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen, &bytes[0], STLSOFT_NUM_ELEMENTS(bytes));

        rommf_t mmf(f.c_str());

        TEST_INT_GE(sizeof(bytes), mmf.size());
        TEST_BOOLEAN_TRUE(0 == ::memcmp(bytes, mmf.memory(), sizeof(bytes)));
    }
} // namespace single_threaded
namespace multi_threaded {

    typedef platformstl::readonly_memory_mapped_file_base<platformstl::refcount_policy_multi_threaded> rommf_t;


    static void test_nonexisting_file()
    {
        temp_file f(temp_file::DeleteOnOpen | temp_file::DeleteOnClose);

        rommf_t mmf(f.c_str());

        TEST_FAIL("should not get here");

        STLSOFT_SUPPRESS_UNUSED(mmf);
    }

    static void test_a_new_file_with_fixed_content()
    {
        stlsoft::byte_t bytes[4 * 1024];

        std::fill_n(&bytes[0], STLSOFT_NUM_ELEMENTS(bytes), stlsoft::byte_t(123));

        temp_file       f(temp_file::DeleteOnClose | temp_file::EmptyOnOpen | temp_file::CloseOnOpen, &bytes[0], STLSOFT_NUM_ELEMENTS(bytes));

        rommf_t mmf(f.c_str());

        TEST_INT_GE(sizeof(bytes), mmf.size());
        TEST_BOOLEAN_TRUE(0 == ::memcmp(bytes, mmf.memory(), sizeof(bytes)));
    }
} // namespace multi_threaded
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

