/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/atlstl/automation/enumerators/entry.cpp
 *
 * Purpose: Unit-tests for `atlstl::copy_enumerator`.
 *
 * Created: 9th August 2026
 * Updated: 14th November 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <atlstl/automation/enumerators.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <atlbase.h>
#include <atlcom.h>
#include <objidl.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_Init_AND_SIZE();
    static void TEST_Next_AND_Reset();
    static void TEST_Clone();
    static void TEST_Next_NULL_POINTER();
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
        XTESTS_RUN_CASE(TEST_Init_AND_SIZE);
        XTESTS_RUN_CASE(TEST_Next_AND_Reset);
        XTESTS_RUN_CASE(TEST_Clone);
        XTESTS_RUN_CASE(TEST_Next_NULL_POINTER);

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
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_Init_AND_SIZE()
{
    CComObject<string_enumerator_t>* pEnum = NULL;

    TEST_INT_EQ(S_OK, CComObject<string_enumerator_t>::CreateInstance(&pEnum));

    CComPtr<string_enumerator_t> spEnum(pEnum);

    OLECHAR const* const items[] = { L"alpha", L"beta", L"gamma" };

    TEST_INT_EQ(S_OK, spEnum->Init(items, items + 3));
    TEST_INT_EQ(3u, spEnum->size());
}

static void TEST_Next_AND_Reset()
{
    CComObject<string_enumerator_t>* pEnum = NULL;

    TEST_INT_EQ(S_OK, CComObject<string_enumerator_t>::CreateInstance(&pEnum));

    CComPtr<string_enumerator_t> spEnum(pEnum);

    OLECHAR const* const items[] = { L"one", L"two", L"three" };

    TEST_INT_EQ(S_OK, spEnum->Init(items, items + 3));

    LPOLESTR            rgelt[3] = {};
    ULONG               fetched = 0;
    CComPtr<IEnumString>  spIface(spEnum);

    TEST_INT_EQ(S_OK, spIface->Next(2, rgelt, &fetched));
    TEST_INT_EQ(2u, fetched);
    TEST_INT_EQ(0, ::wcscmp(L"one", rgelt[0]));
    TEST_INT_EQ(0, ::wcscmp(L"two", rgelt[1]));
    ::SysFreeString(rgelt[0]);
    ::SysFreeString(rgelt[1]);

    TEST_INT_EQ(S_OK, spIface->Reset());

    TEST_INT_EQ(S_OK, spIface->Next(3, rgelt, &fetched));
    TEST_INT_EQ(3u, fetched);
    TEST_INT_EQ(0, ::wcscmp(L"one", rgelt[0]));
    TEST_INT_EQ(0, ::wcscmp(L"two", rgelt[1]));
    TEST_INT_EQ(0, ::wcscmp(L"three", rgelt[2]));
    ::SysFreeString(rgelt[0]);
    ::SysFreeString(rgelt[1]);
    ::SysFreeString(rgelt[2]);
}

static void TEST_Clone()
{
    CComObject<string_enumerator_t>* pEnum = NULL;

    TEST_INT_EQ(S_OK, CComObject<string_enumerator_t>::CreateInstance(&pEnum));

    CComPtr<string_enumerator_t> spEnum(pEnum);

    OLECHAR const* const items[] = { L"x", L"y" };

    TEST_INT_EQ(S_OK, spEnum->Init(items, items + 2));

    CComPtr<IEnumString> spClone;
    CComPtr<IEnumString> spIface(spEnum);

    TEST_INT_EQ(S_OK, spIface->Clone(&spClone));

    LPOLESTR    rgelt = NULL;
    ULONG       fetched = 0;

    TEST_INT_EQ(S_OK, spClone->Next(1, &rgelt, &fetched));
    TEST_INT_EQ(1u, fetched);
    TEST_INT_EQ(0, ::wcscmp(L"x", rgelt));
    ::SysFreeString(rgelt);
}

static void TEST_Next_NULL_POINTER()
{
    CComObject<string_enumerator_t>* pEnum = NULL;

    TEST_INT_EQ(S_OK, CComObject<string_enumerator_t>::CreateInstance(&pEnum));

    CComPtr<IEnumString> spIface(pEnum);

    TEST_INT_EQ(E_POINTER, spIface->Next(1, NULL, NULL));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
