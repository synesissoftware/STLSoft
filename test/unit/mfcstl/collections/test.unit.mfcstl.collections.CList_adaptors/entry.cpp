/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.mfcstl.collections.CList_adaptors/entry.cpp
 *
 * Purpose: Unit-tests for `mfcstl::CList_iadaptor`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <mfcstl/collections/CList_adaptors.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_iadaptor_default_empty(void);
    static void TEST_iadaptor_push_back_and_iterate(void);
    static void TEST_iadaptor_clear(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.mfcstl.collections.CList_adaptors", verbosity))
    {
        XTESTS_RUN_CASE(TEST_iadaptor_default_empty);
        XTESTS_RUN_CASE(TEST_iadaptor_push_back_and_iterate);
        XTESTS_RUN_CASE(TEST_iadaptor_clear);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_iadaptor_default_empty()
{
    CPtrList                          raw;
    mfcstl::CList_iadaptor<CPtrList>  lip(raw);

    TEST_BOOLEAN_TRUE(lip.empty());
    TEST_INT_EQ(0, lip.size());
}

static void TEST_iadaptor_push_back_and_iterate()
{
    CPtrList                          raw;
    mfcstl::CList_iadaptor<CPtrList>  lip(raw);

    lip.push_back(reinterpret_cast<void*>(1));
    lip.push_back(reinterpret_cast<void*>(2));

    TEST_INT_EQ(2, raw.GetCount());
    TEST_INT_EQ(2, lip.size());
    TEST_PTR_EQ(reinterpret_cast<void*>(1), raw.GetHead());
    TEST_PTR_EQ(reinterpret_cast<void*>(2), raw.GetTail());
}

static void TEST_iadaptor_clear()
{
    CPtrList                          raw;
    mfcstl::CList_iadaptor<CPtrList>  lip(raw);

    lip.push_back(reinterpret_cast<void*>(1));
    lip.clear();

    TEST_BOOLEAN_TRUE(lip.empty());
    TEST_INT_EQ(0, raw.GetCount());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
