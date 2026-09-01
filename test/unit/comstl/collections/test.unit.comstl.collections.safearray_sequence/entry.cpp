/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.collections.safearray_sequence/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::safearray_sequence`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/collections/safearray_sequence.hpp>
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

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.collections.safearray_sequence", verbosity))
    {
        XTESTS_RUN_CASE(test_iteration);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_iteration(void)
{
    SAFEARRAYBOUND  bound = { 3, 0 };
    SAFEARRAY*      psa   = ::SafeArrayCreate(VT_I4, 1, &bound);
    LONG            indices[1];
    LONG            values[] = { 10, 20, 30 };

    TEST_PTR_NE(NULL, psa);

    for (LONG i = 0; i < 3; ++i)
    {
        indices[0] = i;
        TEST_INT_EQ((int)S_OK, (int)::SafeArrayPutElement(psa, indices, &values[i]));
    }

    comstl::safearray_sequence<LONG>  seq(psa);

    TEST_UINT_EQ(3u, seq.size());
    TEST_BOOLEAN_FALSE(seq.empty());

    comstl::safearray_sequence<LONG>::const_iterator  it  = seq.begin();
    comstl::safearray_sequence<LONG>::const_iterator  end = seq.end();

    TEST_INT_EQ(10, *it++);
    TEST_INT_EQ(20, *it++);
    TEST_INT_EQ(30, *it++);
    TEST_BOOLEAN_TRUE(it == end);

    ::SafeArrayDestroy(psa);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
