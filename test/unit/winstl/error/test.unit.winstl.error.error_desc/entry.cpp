/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.error.error_desc/entry.cpp
 *
 * Purpose: Unit-tests for `error/error_desc`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */



#include <winstl/error/error_desc.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>

static void test_known_error(void);
static void test_success(void);

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;
    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);
    if (XTESTS_START_RUNNER("test.unit.winstl.error.error_desc", verbosity))
    {
        XTESTS_RUN_CASE(test_success);
        XTESTS_RUN_CASE(test_known_error);
        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }
    return retCode;
}

static void test_success(void)
{
    winstl::error_desc ed(ERROR_SUCCESS);
    TEST_PTR_NE(NULL, ed.get_description());
    TEST_UINT_NE(0u, stlsoft::c_str_len(ed));
}

static void test_known_error(void)
{
    winstl::error_desc ed(ERROR_FILE_NOT_FOUND);
    TEST_PTR_NE(NULL, ed.get_description());
    TEST_UINT_NE(0u, stlsoft::c_str_len(ed));
}
