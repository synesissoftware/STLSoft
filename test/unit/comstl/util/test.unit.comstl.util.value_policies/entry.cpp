/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.value_policies/entry.cpp
 *
 * Purpose: Unit-tests for COM value policies.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <comstl/util/value_policies.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_guid_policy(void);
    static void test_bstr_policy(void);
    static void test_variant_policy(void);
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

    if (XTESTS_START_RUNNER("test.unit.comstl.util.value_policies", verbosity))
    {
        XTESTS_RUN_CASE(test_guid_policy);
        XTESTS_RUN_CASE(test_bstr_policy);
        XTESTS_RUN_CASE(test_variant_policy);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_guid_policy(void)
{
    GUID lhs;
    GUID rhs = IID_IUnknown;

    comstl::GUID_policy::init(&lhs);
    comstl::GUID_policy::copy(&lhs, &rhs);
    TEST_BOOLEAN_TRUE(IsEqualGUID(lhs, IID_IUnknown));
    comstl::GUID_policy::clear(&lhs);
}

static void test_bstr_policy(void)
{
    BSTR value = NULL;
    BSTR src   = ::SysAllocString(L"x");

    comstl::BSTR_policy::init(&value);
    TEST_PTR_EQ(NULL, value);

    comstl::BSTR_policy::copy(&value, &src);
    TEST_PTR_NE(NULL, value);
    TEST_INT_EQ(0, ::wcscmp(L"x", value));

    comstl::BSTR_policy::clear(&value);
    TEST_PTR_EQ(NULL, value);

    ::SysFreeString(src);
}

static void test_variant_policy(void)
{
    VARIANT v;

    comstl::VARIANT_policy::init(&v);
    TEST_INT_EQ((int)VT_EMPTY, (int)v.vt);

    VARIANT src;
    ::VariantInit(&src);
    src.vt = VT_I4;
    src.lVal = 99;

    comstl::VARIANT_policy::copy(&v, &src);
    TEST_INT_EQ(99, v.lVal);

    comstl::VARIANT_policy::clear(&v);
    TEST_INT_EQ((int)VT_EMPTY, (int)v.vt);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
