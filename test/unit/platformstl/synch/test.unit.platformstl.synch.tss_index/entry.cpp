#include <platformstl/synch/tss_index.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_allocate_set_get(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.platformstl.synch.tss_index", verbosity))
    {
        XTESTS_RUN_CASE(test_allocate_set_get);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_allocate_set_get(void)
{
    platformstl::tss_index idx;
    void* p = &idx;
    idx.set_value(p);
    TEST_PTR_EQ(p, idx.get_value());
    TEST_PASSED();
}

