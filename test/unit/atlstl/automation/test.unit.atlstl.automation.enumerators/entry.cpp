/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.atlstl.automation.enumerators/entry.cpp
 *
 * Purpose: Unit-tests for `atlstl::copy_enumerator`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <atlstl/automation/enumerators.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* ATL / COM header files */
#include <atlbase.h>
#include <atlcom.h>
#include <objidl.h>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * test types
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
 * copy_policy specialisation
 */

namespace atlstl {

template <>
struct copy_policy<LPOLESTR, LPOLESTR>
{
    typedef LPOLESTR    external_value_type;
    typedef LPOLESTR    internal_value_type;

    static void init(external_value_type *xv)
    {
        *xv = NULL;
    }

    static HRESULT copy(external_value_type *xv, internal_value_type const& iv)
    {
        *xv = ::SysAllocString(iv);

        return (NULL != *xv) ? S_OK : E_OUTOFMEMORY;
    }

    static void clear(external_value_type *xv)
    {
        if (NULL != *xv)
        {
            ::SysFreeString(*xv);
        }

        *xv = NULL;
    }
};

} // namespace atlstl


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_init_and_size();
    static void TEST_next_and_reset();
    static void TEST_clone();
    static void TEST_next_null_pointer();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.atlstl.automation.enumerators", verbosity))
    {
        HRESULT const hrCoInit = ::CoInitialize(NULL);

        if (SUCCEEDED(hrCoInit))
        {
            XTESTS_RUN_CASE(TEST_init_and_size);
            XTESTS_RUN_CASE(TEST_next_and_reset);
            XTESTS_RUN_CASE(TEST_clone);
            XTESTS_RUN_CASE(TEST_next_null_pointer);

            ::CoUninitialize();
        }
        else
        {
            XTESTS_TEST_FAIL("CoInitialize() failed");
        }

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_init_and_size()
{
    CComObject<string_enumerator_t>* pEnum = NULL;

    TEST_INT_EQ(S_OK, CComObject<string_enumerator_t>::CreateInstance(&pEnum));

    CComPtr<string_enumerator_t> spEnum(pEnum);

    OLECHAR const* const items[] = { L"alpha", L"beta", L"gamma" };

    TEST_INT_EQ(S_OK, spEnum->Init(items, items + 3));
    TEST_INT_EQ(3u, spEnum->size());
}

static void TEST_next_and_reset()
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

static void TEST_clone()
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

static void TEST_next_null_pointer()
{
    CComObject<string_enumerator_t>* pEnum = NULL;

    TEST_INT_EQ(S_OK, CComObject<string_enumerator_t>::CreateInstance(&pEnum));

    CComPtr<IEnumString> spIface(pEnum);

    TEST_INT_EQ(E_POINTER, spIface->Next(1, NULL, NULL));
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
