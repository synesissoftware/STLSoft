/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.shims.logical.is_empty.cstring/entry.cpp
 *
 * Purpose: Unit-tests for is_empty shims for `CString`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <mfcstl/shims/logical/is_empty/cstring.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void TEST_empty_string();
static void TEST_non_empty_string();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.shims.logical.is_empty.cstring", verbosity))
    {
        XTESTS_RUN_CASE(TEST_empty_string);
        XTESTS_RUN_CASE(TEST_non_empty_string);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_empty_string()
{
    CString const s;

    TEST_BOOLEAN_TRUE(stlsoft::is_empty(s));
}

static void TEST_non_empty_string()
{
    CString const s(_T("mfcstl"));

    TEST_BOOLEAN_FALSE(stlsoft::is_empty(s));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
