/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.variant/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::variant`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/util/variant.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_default_construction(void);
    static void test_integer_construction(void);
    static void test_copy(void);
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

    if (XTESTS_START_RUNNER("test.unit.comstl.util.variant", verbosity))
    {
        XTESTS_RUN_CASE(test_default_construction);
        XTESTS_RUN_CASE(test_integer_construction);
        XTESTS_RUN_CASE(test_copy);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_default_construction(void)
{
    comstl::variant  v;

    TEST_INT_EQ((int)VT_EMPTY, (int)v.vt);
}

static void test_integer_construction(void)
{
    comstl::variant  v(stlsoft::sint32_t(-42));

    TEST_INT_EQ((int)VT_I4, (int)v.vt);
    TEST_INT_EQ(-42, v.lVal);
}

static void test_copy(void)
{
    comstl::variant  v1(stlsoft::sint32_t(7));
    comstl::variant  v2(v1);

    TEST_BOOLEAN_TRUE(comstl::VARIANT_equal(&v1, &v2));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
