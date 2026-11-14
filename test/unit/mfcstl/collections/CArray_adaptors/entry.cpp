/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/mfcstl/collections/CArray_adaptors/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::CArray_cadaptor` and `mfcstl::CArray_iadaptor`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/collections/CArray_adaptors.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <algorithm>
#include <numeric>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CADAPTOR_DEFAULT_EMPTY();
    static void TEST_CADAPTOR_push_back_AND_ITERATE();
    static void TEST_CADAPTOR_ASSIGN_AND_COMPARE();
    static void TEST_IADAPTOR_WRAPS_UNDERLYING_ARRAY();
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
        XTESTS_RUN_CASE(TEST_CADAPTOR_DEFAULT_EMPTY);
        XTESTS_RUN_CASE(TEST_CADAPTOR_push_back_AND_ITERATE);
        XTESTS_RUN_CASE(TEST_CADAPTOR_ASSIGN_AND_COMPARE);
        XTESTS_RUN_CASE(TEST_IADAPTOR_WRAPS_UNDERLYING_ARRAY);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CADAPTOR_DEFAULT_EMPTY()
{
    mfcstl::CArray_cadaptor<CUIntArray> ar;

    TEST_BOOLEAN_TRUE(ar.empty());
    TEST_INT_EQ(0, ar.size());
}

static void TEST_CADAPTOR_push_back_AND_ITERATE()
{
    mfcstl::CArray_cadaptor<CUIntArray> ar;

    ar.push_back(1);
    ar.push_back(2);
    ar.push_back(3);

    TEST_INT_EQ(3, ar.size());
    TEST_INT_EQ(1u, ar[0]);
    TEST_INT_EQ(3u, ar.back());

    TEST_INT_EQ(6u, std::accumulate(ar.begin(), ar.end(), 0u));
}

static void TEST_CADAPTOR_ASSIGN_AND_COMPARE()
{
    mfcstl::CArray_cadaptor<CUIntArray> ar1;
    mfcstl::CArray_cadaptor<CUIntArray> ar2;

    ar1.assign(3, 7u);

    TEST_INT_EQ(3, ar1.size());
    TEST_BOOLEAN_TRUE(ar1 == ar1);
    TEST_BOOLEAN_FALSE(ar1 == ar2);

    ar2 = ar1;

    TEST_BOOLEAN_TRUE(ar1 == ar2);
    TEST_BOOLEAN_FALSE(ar1 < ar2);
}

static void TEST_IADAPTOR_WRAPS_UNDERLYING_ARRAY()
{
    CUIntArray                          raw;
    mfcstl::CArray_iadaptor<CUIntArray> arp(raw);

    arp.push_back(4);
    arp.push_back(5);

    TEST_INT_EQ(2, raw.GetSize());
    TEST_INT_EQ(2, arp.size());
    TEST_INT_EQ(4u, raw[0]);
    TEST_INT_EQ(5u, arp[1]);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
