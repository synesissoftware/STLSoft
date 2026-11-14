/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/atlstl/automation/property_method_helpers/entry.cpp
 *
 * Purpose: Unit-tests for `atlstl::get_MemberValue`, `atlstl::put_MemberValue`
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <atlstl/automation/property_method_helpers.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <atlbase.h>
#include <atlcom.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_get_Member_VALUE_INTEGRAL();
    static void TEST_get_Member_VALUE_BSTR();
    static void TEST_get_Member_VALUE_VARIANT();
    static void TEST_get_Member_VALUE_bool();
    static void TEST_get_Member_VALUE_size_t_OVERFLOW();
    static void TEST_get_Member_VALUE_METHOD();
    static void TEST_put_Member_VALUE();
    static void TEST_GET_CONSTANT_VALUE();
    static void TEST_NULL_POINTER_RETURNS();
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
        XTESTS_RUN_CASE(TEST_get_Member_VALUE_INTEGRAL);
        XTESTS_RUN_CASE(TEST_get_Member_VALUE_BSTR);
        XTESTS_RUN_CASE(TEST_get_Member_VALUE_VARIANT);
        XTESTS_RUN_CASE(TEST_get_Member_VALUE_bool);
        XTESTS_RUN_CASE(TEST_get_Member_VALUE_size_t_OVERFLOW);
        XTESTS_RUN_CASE(TEST_get_Member_VALUE_METHOD);
        XTESTS_RUN_CASE(TEST_put_Member_VALUE);
        XTESTS_RUN_CASE(TEST_GET_CONSTANT_VALUE);
        XTESTS_RUN_CASE(TEST_NULL_POINTER_RETURNS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_get_Member_VALUE_INTEGRAL()
{
    test_object obj = {};

    obj.m_long = 42;

    long value = 0;

    TEST_INT_EQ(S_OK, atlstl::get_MemberValue(&obj, &value, &test_object::m_long));
    TEST_INT_EQ(42, value);
}

static void TEST_get_Member_VALUE_BSTR()
{
    test_object obj = {};

    obj.m_bstr = L"atlstl";

    BSTR value = NULL;

    TEST_INT_EQ(S_OK, atlstl::get_MemberValue(&obj, &value, &test_object::m_bstr));
    TEST_INT_EQ(0, ::wcscmp(L"atlstl", value));
    ::SysFreeString(value);
}

static void TEST_get_Member_VALUE_VARIANT()
{
    test_object obj = {};

    obj.m_variant = 7L;

    VARIANT value;

    ::VariantInit(&value);

    TEST_INT_EQ(S_OK, atlstl::get_MemberValue(&obj, &value, &test_object::m_variant));
    TEST_INT_EQ(VT_I4, value.vt);
    TEST_INT_EQ(7, value.lVal);

    ::VariantClear(&value);
}

static void TEST_get_Member_VALUE_bool()
{
    test_object obj = {};

    obj.m_bool = true;

    BOOL value = FALSE;

    TEST_INT_EQ(S_OK, atlstl::get_MemberValue(&obj, &value, &test_object::m_bool));
    TEST_BOOLEAN_EQ(TRUE, value);

    VARIANT_BOOL vbool = VARIANT_FALSE;

    TEST_INT_EQ(S_OK, atlstl::get_MemberValue(&obj, &vbool, &test_object::m_bool));
    TEST_BOOLEAN_EQ(VARIANT_TRUE, vbool);
}

static void TEST_get_Member_VALUE_size_t_OVERFLOW()
{
    test_object obj = {};

    obj.m_size = static_cast<size_t>(LONG_MAX) + 1u;

    long value = 0;

    TEST_INT_EQ(DISP_E_OVERFLOW, atlstl::get_MemberValue(&obj, &value, &test_object::m_size));
}

static void TEST_get_Member_VALUE_METHOD()
{
    test_object obj = {};

    obj.m_size = 99;

    long value = 0;

    TEST_INT_EQ(S_OK, atlstl::get_MemberValue(&obj, &value, &test_object::get_size));
    TEST_INT_EQ(99, value);
}

static void TEST_put_Member_VALUE()
{
    test_object obj = {};

    TEST_INT_EQ(S_OK, atlstl::put_MemberValue(&obj, 17L, &test_object::m_long));
    TEST_INT_EQ(17, obj.m_long);

    TEST_INT_EQ(S_OK, atlstl::put_MemberValue(&obj, L"new", &test_object::m_bstr));
    TEST_INT_EQ(0, ::wcscmp(L"new", obj.m_bstr));

    VARIANT newVal;

    ::VariantInit(&newVal);
    newVal.vt = VT_I4;
    newVal.lVal = 3;

    TEST_INT_EQ(S_OK, atlstl::put_MemberValue(&obj, newVal, &test_object::m_variant));
    TEST_INT_EQ(VT_I4, obj.m_variant.vt);
    TEST_INT_EQ(3, obj.m_variant.lVal);

    TEST_INT_EQ(S_OK, atlstl::put_MemberValue(&obj, TRUE, &test_object::m_bool));
    TEST_BOOLEAN_EQ(true, obj.m_bool);

    TEST_INT_EQ(S_OK, atlstl::put_MemberValue(&obj, VARIANT_TRUE, &test_object::m_bool));
    TEST_BOOLEAN_EQ(true, obj.m_bool);
}

static void TEST_GET_CONSTANT_VALUE()
{
    long value = 0;

    TEST_INT_EQ(S_OK, atlstl::get_ConstantValue(&value, 123L));
    TEST_INT_EQ(123, value);
}

static void TEST_NULL_POINTER_RETURNS()
{
    test_object obj = {};

    TEST_INT_EQ(E_POINTER, atlstl::get_MemberValue(&obj, static_cast<long*>(NULL), &test_object::m_long));
    TEST_INT_EQ(E_POINTER, atlstl::get_ConstantValue(static_cast<long*>(NULL), 1L));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
