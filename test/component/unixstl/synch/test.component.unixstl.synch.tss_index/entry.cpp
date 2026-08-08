/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.unixstl.synch.tss_index/entry.cpp
 *
 * Purpose: Component-tests for UnixSTL `unixstl/synch/tss_index.hpp`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <unixstl/synch/tss_index.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {


static void test_tss_index_set_get()
{
    unixstl::tss_index idx;

    idx.set_value(reinterpret_cast<void*>(0x1234));
    TEST_PTR_EQ(reinterpret_cast<void*>(0x1234), idx.get_value());
}


} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.unixstl.synch.tss_index", verbosity))
    {
        XTESTS_RUN_CASE(test_tss_index_set_get);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* ///////////////////////////// end of file //////////////////////////// */
