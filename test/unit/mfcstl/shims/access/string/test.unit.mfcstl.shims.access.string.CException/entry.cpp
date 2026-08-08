/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.shims.access.string.CException/entry.cpp
 *
 * Purpose: Unit-tests for CException string-access shims.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <mfcstl/shims/access/string/CException.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void TEST_memory_exception_message();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.shims.access.string.CException", verbosity))
    {
        XTESTS_RUN_CASE(TEST_memory_exception_message);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_memory_exception_message()
{
    try
    {
        AfxThrowMemoryException();
    }
    catch (CException* px)
    {
        LPCTSTR const msg = stlsoft::c_str_ptr(*px);

        TEST_PTR_NE(NULL, msg);
        TEST_INT_NE(0u, stlsoft::c_str_len(*px).size());
        TEST_INT_EQ(stlsoft::c_str_len(*px).size(), _tcslen(msg));

        px->Delete();
    }
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
