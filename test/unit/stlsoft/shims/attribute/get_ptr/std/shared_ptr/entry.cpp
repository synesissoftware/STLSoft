/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/shims/attribute/get_ptr/std/shared_ptr/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/shims/attribute/get_ptr/std/shared_ptr`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/shims/attribute/get_ptr/std/shared_ptr.hpp>
#include <stlsoft/shims/access/string.hpp>
#include <memory>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_get_ptr_SHARED();
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
        XTESTS_RUN_CASE(TEST_get_ptr_SHARED);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_get_ptr_SHARED()
{
    std::shared_ptr<int> sp(new int(5));
    TEST_PTR_EQ(sp.get(), stlsoft::get_ptr(sp));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
