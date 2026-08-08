/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.collections.CList_swap/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::CList_swap`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


#include <mfcstl/collections/CList_swap.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>


namespace {

static void TEST_swap_exchanges_contents();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.collections.CList_swap", verbosity))
    {
        XTESTS_RUN_CASE(TEST_swap_exchanges_contents);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_swap_exchanges_contents()
{
#ifdef MFCSTL_CLIST_SWAP_MEMBERS_SUPPORT
    CPtrList lhs;
    CPtrList rhs;

    lhs.AddTail(reinterpret_cast<void*>(1));
    lhs.AddTail(reinterpret_cast<void*>(2));
    rhs.AddTail(reinterpret_cast<void*>(10));

    mfcstl::CList_swap(lhs, rhs);

    TEST_INT_EQ(1, lhs.GetCount());
    TEST_INT_EQ(2, rhs.GetCount());
    TEST_PTR_EQ(reinterpret_cast<void*>(10), lhs.GetHead());
    TEST_PTR_EQ(reinterpret_cast<void*>(1), rhs.GetHead());
#else /* ? MFCSTL_CLIST_SWAP_MEMBERS_SUPPORT */
    TEST_PASSED();
#endif /* MFCSTL_CLIST_SWAP_MEMBERS_SUPPORT */
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
