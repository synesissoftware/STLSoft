/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/util/memory_exception_translation_policies/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl` memory exception translation policies.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/util/memory_exception_translation_policies.hpp>
#include <xtests/terse-api.h>
#include <stlsoft/exception/out_of_memory_exception.hpp>
#include <stlsoft/stlsoft.h>
#include <new>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_BAD_ALLOC_POLICY_RETHROWS_BAD_ALLOC();
    static void TEST_BAD_ALLOC_POLICY_TRANSLATES_MEMORY_EXCEPTION();
    static void TEST_CMEMORY_EXCEPTION_POLICY_RETHROWS_MEMORY_EXCEPTION();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_BAD_ALLOC_POLICY_RETHROWS_BAD_ALLOC);
        XTESTS_RUN_CASE(TEST_BAD_ALLOC_POLICY_TRANSLATES_MEMORY_EXCEPTION);
        XTESTS_RUN_CASE(TEST_CMEMORY_EXCEPTION_POLICY_RETHROWS_MEMORY_EXCEPTION);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_BAD_ALLOC_POLICY_RETHROWS_BAD_ALLOC()
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

static void TEST_BAD_ALLOC_POLICY_TRANSLATES_MEMORY_EXCEPTION()
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

static void TEST_CMEMORY_EXCEPTION_POLICY_RETHROWS_MEMORY_EXCEPTION()
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
