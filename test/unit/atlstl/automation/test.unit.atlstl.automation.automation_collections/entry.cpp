/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atlstl.automation.automation_collections/entry.cpp
 *
 * Purpose: Unit-tests for `atlstl::generic_automation_collection`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <atlstl/automation/automation_collections.hpp>
#include <atlstl/automation/enumerators.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <atlbase.h>
#include <atlcom.h>
#include <objidl.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_supports_count_and_get_count(void);
    static void TEST_idispatch_count_property(void);
    static void TEST_idispatch_newenum(void);
    static void TEST_get_count_without_set_count(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atlstl.automation.automation_collections", verbosity))
    {
        XTESTS_RUN_CASE(TEST_supports_count_and_get_count);
        XTESTS_RUN_CASE(TEST_idispatch_count_property);
        XTESTS_RUN_CASE(TEST_idispatch_newenum);
        XTESTS_RUN_CASE(TEST_get_count_without_set_count);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

typedef atlstl::copy_enumerator<
    IEnumString
,   &IID_IEnumString
,   LPOLESTR
,   LPOLESTR
,   atlstl::copy_policy<LPOLESTR, LPOLESTR>
>                                           string_enumerator_t;
typedef atlstl::generic_automation_collection<
    string_enumerator_t
>                                           string_collection_t;

static HRESULT create_collection_with_items(
    string_collection_t**   ppColl
,   ULONG*                  pItemCount
)
{
    CComObject<string_enumerator_t>* pEnum = NULL;
    HRESULT                         hr = CComObject<string_enumerator_t>::CreateInstance(&pEnum);

    if (FAILED(hr))
    {
        return hr;
    }

    OLECHAR const* const items[] = { L"first", L"second", L"third" };
    ULONG const          cItems = static_cast<ULONG>(sizeof(items) / sizeof(items[0]));

    hr = pEnum->Init(items, items + cItems);

    if (FAILED(hr))
    {
        return hr;
    }

    CComObject<string_collection_t>* pColl = NULL;

    hr = CComObject<string_collection_t>::CreateInstance(&pColl);

    if (FAILED(hr))
    {
        return hr;
    }

    pColl->SetEnumerator(pEnum, true);
    pColl->SetCount(cItems);

    *ppColl = pColl;
    *pItemCount = cItems;

    return S_OK;
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_supports_count_and_get_count()
{
    string_collection_t*    pColl = NULL;
    ULONG                   cItems = 0;

    TEST_INT_EQ(S_OK, create_collection_with_items(&pColl, &cItems));

    CComPtr<string_collection_t> spColl(pColl);

    TEST_INT_EQ(S_OK, spColl->SupportsCount());

    long count = -1;

    TEST_INT_EQ(S_OK, spColl->get_Count(&count));
    TEST_INT_EQ(static_cast<long>(cItems), count);
}

static void TEST_idispatch_count_property()
{
    string_collection_t*    pColl = NULL;
    ULONG                   cItems = 0;

    TEST_INT_EQ(S_OK, create_collection_with_items(&pColl, &cItems));

    CComQIPtr<IDispatch> spDisp(pColl);

    OLECHAR*    name = const_cast<OLECHAR*>(L"Count");
    DISPID      dispid = 0;

    TEST_INT_EQ(S_OK, spDisp->GetIDsOfNames(IID_NULL, &name, 1, LOCALE_USER_DEFAULT, &dispid));

    VARIANT         varResult;
    DISPPARAMS      params = {};

    ::VariantInit(&varResult);

    TEST_INT_EQ(S_OK, spDisp->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &params, &varResult, NULL, NULL));
    TEST_INT_EQ(VT_I4, varResult.vt);
    TEST_INT_EQ(static_cast<long>(cItems), varResult.lVal);

    ::VariantClear(&varResult);
}

static void TEST_idispatch_newenum()
{
    string_collection_t*    pColl = NULL;
    ULONG                   cItems = 0;

    TEST_INT_EQ(S_OK, create_collection_with_items(&pColl, &cItems));

    CComQIPtr<IDispatch> spDisp(pColl);

    VARIANT         varResult;
    DISPPARAMS      params = {};

    ::VariantInit(&varResult);

    TEST_INT_EQ(S_OK, spDisp->Invoke(DISPID_NEWENUM, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, &varResult, NULL, NULL));
    TEST_INT_EQ(VT_UNKNOWN, varResult.vt);
    TEST_PTR_NE(NULL, varResult.punkVal);

    ::VariantClear(&varResult);
}

static void TEST_get_count_without_set_count()
{
    CComObject<string_enumerator_t>* pEnum = NULL;

    TEST_INT_EQ(S_OK, CComObject<string_enumerator_t>::CreateInstance(&pEnum));

    OLECHAR const* const items[] = { L"only" };

    TEST_INT_EQ(S_OK, pEnum->Init(items, items + 1));

    CComObject<string_collection_t>* pColl = NULL;

    TEST_INT_EQ(S_OK, CComObject<string_collection_t>::CreateInstance(&pColl));

    CComPtr<string_collection_t> spColl(pColl);

    pColl->SetEnumerator(pEnum, true);

    TEST_INT_EQ(S_FALSE, spColl->SupportsCount());

    long count = 0;

    TEST_INT_EQ(E_UNEXPECTED, spColl->get_Count(&count));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
