/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.filesystem.memory_map_functions/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/filesystem/memory_map_functions.h`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/filesystem/memory_map_functions.h>
#include <unixstl/filesystem/path.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <xtests/util/temp_directory.hpp>

#include <stlsoft/stlsoft.h>

#include <fcntl.h>
#include <sys/mman.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdlib.h>


namespace {

using xtests::cpp::util::temp_directory;

static void test_unmap_view_of_file()
{
    temp_directory td(temp_directory::EmptyOnOpen | temp_directory::RemoveOnClose);

    unixstl::path_a file(td.c_str());
    file /= "maptest.bin";

    int fd = ::open(file.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    XTESTS_REQUIRE(TEST(-1 != fd));

    char const payload[] = "mmap-payload";
    XTESTS_REQUIRE(TEST((ssize_t)sizeof(payload) == ::write(fd, payload, sizeof(payload))));

    void* p = ::mmap(NULL, sizeof(payload), PROT_READ, MAP_SHARED, fd, 0);
    XTESTS_REQUIRE(TEST(MAP_FAILED != p));

    TEST_MS_EQ(payload, static_cast<char const*>(p));

    unixstl::unmap_view_of_file(p, sizeof(payload));
    ::close(fd);
}

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.filesystem.memory_map_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_unmap_view_of_file);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
