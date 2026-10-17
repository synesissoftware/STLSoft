/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.collections.enumerator_sequence/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::enumerator_sequence`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/collections/enumerator_sequence.hpp>
#include <objbase.h>
#include <initguid.h>
#include <comstl/collections/enumeration_policies.hpp>
#include <comstl/util/value_policies.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_iteration(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.collections.enumerator_sequence", verbosity))
    {
        XTESTS_RUN_CASE(test_iteration);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

typedef comstl::enumerator_sequence<
    IEnumGUID
,   GUID
,   comstl::GUID_policy
,   GUID const&
,   comstl::input_cloning_policy<IEnumGUID>
,   1
>   enum_sequence_t;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_iteration(void)
{
    mock_enum_guid*     penum = new mock_enum_guid();
    enum_sequence_t     seq(penum, false);

    enum_sequence_t::const_iterator  it  = seq.begin();
    enum_sequence_t::const_iterator  end = seq.end();

    TEST_BOOLEAN_TRUE(IsEqualGUID(IID_IUnknown, *it++));
    TEST_BOOLEAN_TRUE(IsEqualGUID(IID_IDispatch, *it++));
    TEST_BOOLEAN_TRUE(it == end);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
