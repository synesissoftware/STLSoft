/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.ptr_cast/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft/conversion/ptr_cast`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/conversion/ptr_cast.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_ptr_cast_pointer(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.ptr_cast", verbosity))
    {
        XTESTS_RUN_CASE(test_ptr_cast_pointer);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_ptr_cast_pointer()
{
    int x = 42;
    int* p = &x;
    int* q = stlsoft::ptr_cast<int*>(p);
    TEST_PTR_EQ(p, q);
    TEST_INTEGER_EQUAL(42, *q);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
