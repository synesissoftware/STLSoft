/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.util.memory_exception_translation_policies/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl` memory exception translation policies.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <mfcstl/util/memory_exception_translation_policies.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/exception/out_of_memory_exception.hpp>
#include <stlsoft/stlsoft.h>

#include <new>
#include <stdlib.h>


namespace {

static void TEST_bad_alloc_policy_rethrows_bad_alloc();
static void TEST_bad_alloc_policy_translates_memory_exception();
static void TEST_cmemory_exception_policy_rethrows_memory_exception();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.util.memory_exception_translation_policies", verbosity))
    {
        XTESTS_RUN_CASE(TEST_bad_alloc_policy_rethrows_bad_alloc);
        XTESTS_RUN_CASE(TEST_bad_alloc_policy_translates_memory_exception);
        XTESTS_RUN_CASE(TEST_cmemory_exception_policy_rethrows_memory_exception);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_bad_alloc_policy_rethrows_bad_alloc()
{
    std::bad_alloc x;

    try
    {
        mfcstl::bad_alloc_throwing_policy::handle(x);

        TEST_FAIL("expected std::bad_alloc to be rethrown");
    }
    catch (std::bad_alloc const&)
    {
        TEST_PASSED();
    }
    catch (...)
    {
        TEST_FAIL("unexpected exception type");
    }
}

static void TEST_bad_alloc_policy_translates_memory_exception()
{
    try
    {
        AfxThrowMemoryException();
    }
    catch (CMemoryException* px)
    {
        try
        {
            mfcstl::bad_alloc_throwing_policy::handle(px);

            TEST_FAIL("expected out_of_memory_exception");
        }
        catch (stlsoft::out_of_memory_exception const&)
        {
            TEST_PASSED();
        }
        catch (...)
        {
            TEST_FAIL("unexpected exception type");
        }

        px->Delete();
    }
}

static void TEST_cmemory_exception_policy_rethrows_memory_exception()
{
    try
    {
        AfxThrowMemoryException();
    }
    catch (CMemoryException* px)
    {
        try
        {
            mfcstl::CMemoryException_throwing_policy::handle(px);

            TEST_FAIL("expected CMemoryException to be rethrown");
        }
        catch (CMemoryException*)
        {
            TEST_PASSED();
        }
        catch (...)
        {
            TEST_FAIL("unexpected exception type");
        }

        px->Delete();
    }
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
