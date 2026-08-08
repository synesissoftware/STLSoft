/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.shims.attribute.get_ptr/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/shims/attribute/get_ptr`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/shims/attribute/get_ptr.hpp>

#include <stlsoft/shims/access/string.hpp>
#include <memory>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void test_get_ptr_shared();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.shims.attribute.get_ptr", verbosity))
    {
        XTESTS_RUN_CASE(test_get_ptr_shared);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {


static void test_get_ptr_shared()
{
    std::shared_ptr<int> sp(new int(5));
    TEST_PTR_EQ(sp.get(), stlsoft::get_ptr(sp));
}


} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
