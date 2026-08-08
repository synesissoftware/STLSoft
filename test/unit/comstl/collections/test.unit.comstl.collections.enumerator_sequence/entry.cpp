/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.collections.enumerator_sequence/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::enumerator_sequence`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/collections/enumerator_sequence.hpp>
#include <comstl/collections/enumeration_policies.hpp>
#include <comstl/util/value_policies.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

struct mock_enum_guid
    : public IEnumGUID
{
    ULONG   m_ref;
    ULONG   m_index;
    GUID    m_items[2];

    mock_enum_guid()
        : m_ref(1)
        , m_index(0)
    {
        m_items[0] = IID_IUnknown;
        m_items[1] = IID_IDispatch;
    }

    STDMETHOD(QueryInterface)(REFIID riid, void** ppv)
    {
        if (NULL == ppv)
        {
            return E_POINTER;
        }

        if (riid == IID_IUnknown || riid == IID_IEnumGUID)
        {
            *ppv = static_cast<IEnumGUID*>(this);
            AddRef();
            return S_OK;
        }

        *ppv = NULL;
        return E_NOINTERFACE;
    }

    STDMETHOD_(ULONG, AddRef)()
    {
        return ++m_ref;
    }

    STDMETHOD_(ULONG, Release)()
    {
        ULONG const r = --m_ref;

        if (0 == r)
        {
            delete this;
        }

        return r;
    }

    STDMETHOD(Next)(ULONG celt, GUID* rgelt, ULONG* pceltFetched)
    {
        ULONG fetched = 0;

        while (fetched < celt && m_index < 2)
        {
            rgelt[fetched++] = m_items[m_index++];
        }

        if (NULL != pceltFetched)
        {
            *pceltFetched = fetched;
        }

        return (fetched < celt) ? S_FALSE : S_OK;
    }

    STDMETHOD(Skip)(ULONG)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(Reset)()
    {
        m_index = 0;
        return S_OK;
    }

    STDMETHOD(Clone)(IEnumGUID**)
    {
        return E_NOTIMPL;
    }
};

typedef comstl::enumerator_sequence<
    IEnumGUID
,   GUID
,   comstl::GUID_policy
,   GUID const&
,   comstl::input_cloning_policy<IEnumGUID>
,   1
>   enum_sequence_t;

static void test_iteration(void);

} // anonymous namespace

int main(int argc, char *argv[])
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
