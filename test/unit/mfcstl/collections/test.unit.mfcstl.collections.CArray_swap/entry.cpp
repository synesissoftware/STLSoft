/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.collections.CArray_swap/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::CArray_swap`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/collections/CArray_swap.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_swap_exchanges_contents(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.collections.CArray_swap", verbosity))
    {
        XTESTS_RUN_CASE(TEST_swap_exchanges_contents);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_swap_exchanges_contents()
{
#ifdef MFCSTL_CARRAY_SWAP_MEMBERS_SUPPORT
    CUIntArray lhs;
    CUIntArray rhs;

    lhs.Add(1);
    lhs.Add(2);
    rhs.Add(10);
    rhs.Add(20);
    rhs.Add(30);

    mfcstl::CArray_swap(lhs, rhs);

    TEST_INT_EQ(3, lhs.GetSize());
    TEST_INT_EQ(2, rhs.GetSize());
    TEST_INT_EQ(10u, lhs[0]);
    TEST_INT_EQ(30u, lhs[2]);
    TEST_INT_EQ(1u, rhs[0]);
    TEST_INT_EQ(2u, rhs[1]);
#else /* ? MFCSTL_CARRAY_SWAP_MEMBERS_SUPPORT */
    TEST_PASSED();
#endif /* MFCSTL_CARRAY_SWAP_MEMBERS_SUPPORT */
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
