/* /////////////////////////////////////////////////////////////////////////
 * File:    test/component/platformstl/filesystem/readonly_memory_mapped_file/entry.cpp
 *
 * Purpose: Component test for `platformstl::readonly_memory_mapped_file`.
 *
 * Created: sometime in 2010s
 * Updated: 14th November 2026
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

    static void TEST_TYPES_EXIST();

    namespace single_threaded {

        static void TEST_NONEXISTING_FILE();
        static void TEST_A_NEW_FILE_WITH_FIXED_CONTENT();
    } // namespace single_threaded
    namespace multi_threaded {

        static void TEST_NONEXISTING_FILE();
        static void TEST_A_NEW_FILE_WITH_FIXED_CONTENT();
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

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_TYPES_EXIST);
        XTESTS_RUN_CASE_THAT_THROWS(single_threaded::TEST_NONEXISTING_FILE, platformstl::filesystem_exception);
        XTESTS_RUN_CASE_THAT_THROWS(multi_threaded::TEST_NONEXISTING_FILE, platformstl::filesystem_exception);
        XTESTS_RUN_CASE(single_threaded::TEST_A_NEW_FILE_WITH_FIXED_CONTENT);
        XTESTS_RUN_CASE(multi_threaded::TEST_A_NEW_FILE_WITH_FIXED_CONTENT);

        // XTESTS_RUN_CASE(TEST_EMPTY_DIRECTORY);

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


static void TEST_TYPES_EXIST()
{
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::readonly_memory_mapped_file_base<stlsoft::refcount_policy_single_threaded>));
    STLSOFT_SUPPRESS_UNUSED(typeid(platformstl::readonly_memory_mapped_file_base<platformstl::refcount_policy_multi_threaded>));
}

namespace single_threaded {

    typedef platformstl::readonly_memory_mapped_file_base<stlsoft::refcount_policy_single_threaded> rommf_t;


    static void TEST_NONEXISTING_FILE()
    {
        temp_file f(temp_file::DeleteOnOpen | temp_file::DeleteOnClose);

        rommf_t mmf(f.c_str());

        TEST_FAIL("should not get here");

        STLSOFT_SUPPRESS_UNUSED(mmf);
    }

    static void TEST_A_NEW_FILE_WITH_FIXED_CONTENT()
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


    static void TEST_NONEXISTING_FILE()
    {
        temp_file f(temp_file::DeleteOnOpen | temp_file::DeleteOnClose);

        rommf_t mmf(f.c_str());

        TEST_FAIL("should not get here");

        STLSOFT_SUPPRESS_UNUSED(mmf);
    }

    static void TEST_A_NEW_FILE_WITH_FIXED_CONTENT()
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

