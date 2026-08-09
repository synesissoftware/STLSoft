/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.filesystem.handles.memory_mapped_file_view_handle/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/filesystem/handles/memory_mapped_file_view_handle.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/handles/memory_mapped_file_view_handle.hpp>
#include <unixstl/filesystem/path.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>

#include <stlsoft/stlsoft.h>
#include <stlsoft/synch/refcount_policies/refcount_policy_single_threaded.hpp>

#include <fcntl.h>
#include <sys/mman.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdlib.h>


namespace {

using xtests::cpp::util::temp_directory;

typedef unixstl::memory_mapped_file_view_handle<stlsoft::refcount_policy_single_threaded> view_handle_t;

static void test_view_handle_create_and_destroy()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);

    unixstl::path_a file(td.c_str());
    file /= "view.bin";

    int fd = ::open(file.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    XTESTS_REQUIRE(TEST(-1 != fd));

    char const data[] = "view-handle";
    XTESTS_REQUIRE(TEST((ssize_t)sizeof(data) == ::write(fd, data, sizeof(data))));

    void* p = ::mmap(NULL, sizeof(data), PROT_READ, MAP_SHARED, fd, 0);
    XTESTS_REQUIRE(TEST(MAP_FAILED != p));

    {
        view_handle_t::Ref ref = view_handle_t::create(p, sizeof(data));

        TEST_PTR_EQ(p, ref->handle.memory);
        TEST_INT_EQ(sizeof(data), ref->handle.size);
    }

    ::close(fd);
}

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.filesystem.handles.memory_mapped_file_view_handle", verbosity))
    {
        XTESTS_RUN_CASE(test_view_handle_create_and_destroy);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
