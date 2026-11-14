/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/util/guid/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::guid`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/util/guid.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stlsoft/shims/access/string.hpp>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_CONSTRUCTION_FROM_STRING();
    static void TEST_EQUALITY();
    static void TEST_STRING_SHIMS();
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

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_CONSTRUCTION_FROM_STRING);
        XTESTS_RUN_CASE(TEST_EQUALITY);
        XTESTS_RUN_CASE(TEST_STRING_SHIMS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_CONSTRUCTION_FROM_STRING()
{
    GUID const expected = { 0xf4864792, 0xd0d2, 0x4005, { 0xab, 0xca, 0xf6, 0x79, 0x94, 0xc2, 0xff, 0xa6 } };
    comstl::guid const  g("{F4864792-D0D2-4005-ABCA-F67994C2FFA6}");

    TEST_BOOLEAN_TRUE(g.equal(expected));
    TEST_BOOLEAN_FALSE(g.equal(GUID_NULL));
}

static void TEST_EQUALITY()
{
    comstl::guid        g1("{F4864792-D0D2-4005-ABCA-F67994C2FFA6}");
    comstl::guid        g2(g1);

    TEST_BOOLEAN_TRUE(g1 == g2);
    TEST_BOOLEAN_TRUE(g1.equal(g2.get()));
}

static void TEST_STRING_SHIMS()
{
    comstl::guid const  g(IID_IUnknown);
    comstl::cs_char_a_t const*  s = stlsoft::c_str_ptr_a(g);

    TEST_PTR_NE(NULL, s);
    TEST_INT_NE(0u, stlsoft::c_str_len(g));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
