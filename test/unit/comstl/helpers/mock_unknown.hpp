/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/comstl/helpers/mock_unknown.hpp
 *
 * Purpose: Minimal in-memory IUnknown implementation for COMSTL unit tests.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#ifndef TEST_COMSTL_HELPERS_MOCK_UNKNOWN_HPP
#define TEST_COMSTL_HELPERS_MOCK_UNKNOWN_HPP

#include <comstl/comstl.h>

#include <objbase.h>

namespace test_comstl {

struct mock_unknown
    : public IUnknown
{
    ULONG m_ref;

    mock_unknown()
        : m_ref(1)
    {}

    STDMETHOD(QueryInterface)(REFIID riid, void** ppv)
    {
        if (NULL == ppv)
        {
            return E_POINTER;
        }

        if (riid == IID_IUnknown)
        {
            *ppv = static_cast<IUnknown*>(this);
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
};

} // namespace test_comstl

#endif /* TEST_COMSTL_HELPERS_MOCK_UNKNOWN_HPP */

/* ///////////////////////////// end of file //////////////////////////// */
