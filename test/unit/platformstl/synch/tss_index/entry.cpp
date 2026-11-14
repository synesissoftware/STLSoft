#include <platformstl/synch/tss_index.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void TEST_ALLOCATE_SET_GET();

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_ALLOCATE_SET_GET);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void TEST_ALLOCATE_SET_GET()
{
    platformstl::tss_index idx;
    void* p = &idx;
    idx.set_value(p);
    TEST_PTR_EQ(p, idx.get_value());
    TEST_PASSED();
}

