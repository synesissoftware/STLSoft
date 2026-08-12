/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.VARIANT_functions.C/entry.c
 *
 * Purpose: Scratch test for VARIANT functions.
 *
 * Created: 26th October 2008
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <comstl/util/VARIANT_functions.h>

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <comstl/auto/dispatch_functions.h>

/* Standard C header files */
#include <math.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void test_VARIANT_equal_VT_EMPTY(void);
static void test_VARIANT_equal_VT_NULL(void);
static void test_VARIANT_equal_VT_I4(void);
static void test_VARIANT_equal_VT_BSTR(void);
static void test_VARIANT_equal_VT_R8(void);
static void test_VARIANT_equal_VT_DECIMAL(void);

static void test_VARIANT_change_type_VT_I4(void);
static void test_VARIANT_change_type_VT_R8(void);
static void test_VARIANT_change_type_VT_BSTR(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.util.C.VARIANT_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_VARIANT_equal_VT_EMPTY);
        XTESTS_RUN_CASE(test_VARIANT_equal_VT_NULL);
        XTESTS_RUN_CASE(test_VARIANT_equal_VT_I4);
        XTESTS_RUN_CASE(test_VARIANT_equal_VT_BSTR);
        XTESTS_RUN_CASE(test_VARIANT_equal_VT_R8);
        XTESTS_RUN_CASE(test_VARIANT_equal_VT_DECIMAL);

        XTESTS_RUN_CASE(test_VARIANT_change_type_VT_I4);
        XTESTS_RUN_CASE(test_VARIANT_change_type_VT_R8);
        XTESTS_RUN_CASE(test_VARIANT_change_type_VT_BSTR);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * Constants
 */

const CLSID clsidSynesisValue = { 0xE79E9900, 0x59DB, 0x4B94, { 0xAF, 0xE6, 0xD8, 0x8E, 0x23, 0x4D, 0xDD, 0xDA } };

#define VT_I4_VALUE             -123
#define VT_BSTR_VALUE           L"-123.456"
#define VT_R8_VALUE             -123.456
#define VT_DECIMAL_VALUE        12345
#define VT_DISPATCH_VALUE       -10101
#define VT_UNKNOWN_VALUE        L"-20202"


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

void init_VARIANTS(VARIANT* pvarEMPTY, VARIANT* pvarNULL, VARIANT* pvarI4, VARIANT* pvarBSTR, VARIANT* pvarR8, VARIANT* pvarDECIMAL, VARIANT* pvarDISPATCH, VARIANT* pvarUNKNOWN);
HRESULT setup_VARIANTs(VARIANT* pvarEMPTY, VARIANT* pvarNULL, VARIANT* pvarI4, VARIANT* pvarBSTR, VARIANT* pvarR8, VARIANT* pvarDECIMAL, VARIANT* pvarDISPATCH, VARIANT* pvarUNKNOWN);
void release_VARIANTS(VARIANT* pvarEMPTY, VARIANT* pvarNULL, VARIANT* pvarI4, VARIANT* pvarBSTR, VARIANT* pvarR8, VARIANT* pvarDECIMAL, VARIANT* pvarDISPATCH, VARIANT* pvarUNKNOWN);

void init_VARIANTS(VARIANT* pvarEMPTY, VARIANT* pvarNULL, VARIANT* pvarI4, VARIANT* pvarBSTR, VARIANT* pvarR8, VARIANT* pvarDECIMAL, VARIANT* pvarDISPATCH, VARIANT* pvarUNKNOWN)
{
    VariantInit(pvarEMPTY);
    VariantInit(pvarNULL);
    VariantInit(pvarI4);
    VariantInit(pvarBSTR);
    VariantInit(pvarR8);
    VariantInit(pvarDECIMAL);
    VariantInit(pvarDISPATCH);
    VariantInit(pvarUNKNOWN);
}

HRESULT setup_VARIANTs(VARIANT* pvarEMPTY, VARIANT* pvarNULL, VARIANT* pvarI4, VARIANT* pvarBSTR, VARIANT* pvarR8, VARIANT* pvarDECIMAL, VARIANT* pvarDISPATCH, VARIANT* pvarUNKNOWN)
{
    HRESULT hr;

    init_VARIANTS(pvarEMPTY, pvarNULL, pvarI4, pvarBSTR, pvarR8, pvarDECIMAL, pvarDISPATCH, pvarUNKNOWN);

    COMSTL_ACCESS_VARIANT_vt_BYPTR(pvarNULL)            =   VT_NULL;

    COMSTL_ACCESS_VARIANT_vt_BYPTR(pvarI4)              =   VT_I4;
    COMSTL_ACCESS_VARIANT_MEM_BYPTR(pvarI4, lVal)       =   VT_I4_VALUE;

    COMSTL_ACCESS_VARIANT_vt_BYPTR(pvarBSTR)            =   VT_BSTR;
    COMSTL_ACCESS_VARIANT_MEM_BYPTR(pvarBSTR, bstrVal)  =   SysAllocString(VT_BSTR_VALUE);

    if (NULL == COMSTL_ACCESS_VARIANT_MEM_BYPTR(pvarBSTR, bstrVal))
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
        VARIANT varDecimal_;

        VariantInit(&varDecimal_);
        COMSTL_ACCESS_VARIANT_vt_BYREF(varDecimal_)         =   VT_I4;
        COMSTL_ACCESS_VARIANT_MEM_BYREF(varDecimal_, lVal)  =   VT_DECIMAL_VALUE;

        COMSTL_ACCESS_VARIANT_vt_BYPTR(pvarR8)          =   VT_R8;
        COMSTL_ACCESS_VARIANT_MEM_BYPTR(pvarR8, dblVal) =   VT_R8_VALUE;

        hr = VariantChangeType(pvarDECIMAL, &varDecimal_, 0, VT_DECIMAL);

        if (SUCCEEDED(hr))
        {
            hr = CoCreateInstance(&clsidSynesisValue, NULL, CLSCTX_ALL, &IID_IDispatch, (void**)&COMSTL_ACCESS_VARIANT_MEM_BYPTR(pvarDISPATCH, pdispVal));

            if (FAILED(hr))
            {
                hr = S_FALSE;
            }
            else
            {
                VARIANT varDISPATCH_;

                VariantInit(&varDISPATCH_);

                COMSTL_ACCESS_VARIANT_vt_BYREF(varDISPATCH_)        =   VT_I4;
                COMSTL_ACCESS_VARIANT_MEM_BYREF(varDISPATCH_, lVal) =   VT_DISPATCH_VALUE;

                hr = comstl_C_IDispatch_put_property(COMSTL_ACCESS_VARIANT_MEM_BYPTR(pvarDISPATCH, pdispVal), 1, 1, &varDISPATCH_, NULL, NULL, LOCALE_USER_DEFAULT);

                if (SUCCEEDED(hr))
                {
                    COMSTL_ACCESS_VARIANT_vt_BYPTR(pvarDISPATCH) = VT_DISPATCH;

                    if (SUCCEEDED(hr))
                    {
                        LPDISPATCH  pdispUnk;

                        hr = CoCreateInstance(&clsidSynesisValue, NULL, CLSCTX_ALL, &IID_IUnknown, (void**)&pdispUnk);

                        if (FAILED(hr))
                        {
                            hr = S_FALSE;
                        }
                        else
                        {
                            VARIANT varUNKNOWN_;

                            VariantInit(&varUNKNOWN_);

                            COMSTL_ACCESS_VARIANT_vt_BYREF(varUNKNOWN_)             =   VT_BSTR;
                            COMSTL_ACCESS_VARIANT_MEM_BYREF(varUNKNOWN_, bstrVal)   =   SysAllocString(VT_UNKNOWN_VALUE);

                            COMSTL_ACCESS_VARIANT_MEM_BYPTR(pvarUNKNOWN, punkVal)   =   (LPUNKNOWN)pdispUnk;

                            if (NULL == COMSTL_ACCESS_VARIANT_MEM_BYREF(varUNKNOWN_, bstrVal))
                            {
                                hr = E_OUTOFMEMORY;
                            }
                            else
                            {
                                hr = comstl_C_IDispatch_put_property(pdispUnk, 1, 1, &varUNKNOWN_, NULL, NULL, LOCALE_USER_DEFAULT);

                                VariantClear(&varUNKNOWN_);

                                COMSTL_ACCESS_VARIANT_vt_BYPTR(pvarUNKNOWN) = VT_UNKNOWN;
                            }
                        }
                    }
                }
            }
        }
    }

    if (FAILED(hr))
    {
        VariantClear(pvarEMPTY);
        VariantClear(pvarNULL);
        VariantClear(pvarI4);
        VariantClear(pvarBSTR);
        VariantClear(pvarR8);
        VariantClear(pvarDECIMAL);
        VariantClear(pvarDISPATCH);
        VariantClear(pvarUNKNOWN);
    }

    return hr;
}

void release_VARIANTS(VARIANT* pvarEMPTY, VARIANT* pvarNULL, VARIANT* pvarI4, VARIANT* pvarBSTR, VARIANT* pvarR8, VARIANT* pvarDECIMAL, VARIANT* pvarDISPATCH, VARIANT* pvarUNKNOWN)
{
    VariantClear(pvarEMPTY);
    VariantClear(pvarNULL);
    VariantClear(pvarI4);
    VariantClear(pvarBSTR);
    VariantClear(pvarR8);
    VariantClear(pvarDECIMAL);
    VariantClear(pvarDISPATCH);
    VariantClear(pvarUNKNOWN);
}

static void test_VARIANT_equal_VT_EMPTY()
{
    VARIANT varEMPTY;
    VARIANT varNULL;
    VARIANT varI4;
    VARIANT varBSTR;
    VARIANT varR8;
    VARIANT varDECIMAL;
    VARIANT varDISPATCH;
    VARIANT varUNKNOWN;
    HRESULT hr = setup_VARIANTs(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);

    if (FAILED(hr))
    {
        ; /* Issue warning */
    }
    else
    {
        TEST_BOOLEAN_EQ(1, comstl_C_VARIANT_equal(&varEMPTY, &varEMPTY, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varNULL, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varI4, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varBSTR, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varR8, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varDECIMAL, NULL));
        if (VT_DISPATCH == COMSTL_ACCESS_VARIANT_vt_BYREF(varDISPATCH))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varDISPATCH, NULL));
        }
        if (VT_UNKNOWN == COMSTL_ACCESS_VARIANT_vt_BYREF(varUNKNOWN))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varUNKNOWN, NULL));
        }

        release_VARIANTS(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);
    }
}

static void test_VARIANT_equal_VT_NULL()
{
    VARIANT varEMPTY;
    VARIANT varNULL;
    VARIANT varI4;
    VARIANT varBSTR;
    VARIANT varR8;
    VARIANT varDECIMAL;
    VARIANT varDISPATCH;
    VARIANT varUNKNOWN;
    HRESULT hr = setup_VARIANTs(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);

    if (FAILED(hr))
    {
        ; /* Issue warning */
    }
    else
    {
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varNULL, &varEMPTY, NULL));
        TEST_BOOLEAN_EQ(1, comstl_C_VARIANT_equal(&varNULL, &varNULL, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varNULL, &varI4, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varNULL, &varBSTR, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varNULL, &varR8, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varNULL, &varDECIMAL, NULL));
        if (VT_DISPATCH == COMSTL_ACCESS_VARIANT_vt_BYREF(varDISPATCH))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varDISPATCH, NULL));
        }
        if (VT_UNKNOWN == COMSTL_ACCESS_VARIANT_vt_BYREF(varUNKNOWN))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varUNKNOWN, NULL));
        }

        release_VARIANTS(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);
    }
}

static void test_VARIANT_equal_VT_I4()
{
    VARIANT varEMPTY;
    VARIANT varNULL;
    VARIANT varI4;
    VARIANT varBSTR;
    VARIANT varR8;
    VARIANT varDECIMAL;
    VARIANT varDISPATCH;
    VARIANT varUNKNOWN;
    HRESULT hr = setup_VARIANTs(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);

    if (FAILED(hr))
    {
        ; /* Issue warning */
    }
    else
    {
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varI4, &varEMPTY, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varI4, &varNULL, NULL));
        TEST_BOOLEAN_EQ(1, comstl_C_VARIANT_equal(&varI4, &varI4, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varI4, &varBSTR, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varI4, &varR8, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varI4, &varDECIMAL, NULL));
        if (VT_DISPATCH == COMSTL_ACCESS_VARIANT_vt_BYREF(varDISPATCH))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varDISPATCH, NULL));
        }
        if (VT_UNKNOWN == COMSTL_ACCESS_VARIANT_vt_BYREF(varUNKNOWN))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varUNKNOWN, NULL));
        }

        release_VARIANTS(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);
    }
}

static void test_VARIANT_equal_VT_BSTR()
{
    VARIANT varEMPTY;
    VARIANT varNULL;
    VARIANT varI4;
    VARIANT varBSTR;
    VARIANT varR8;
    VARIANT varDECIMAL;
    VARIANT varDISPATCH;
    VARIANT varUNKNOWN;
    HRESULT hr = setup_VARIANTs(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);

    if (FAILED(hr))
    {
        ; /* Issue warning */
    }
    else
    {
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varBSTR, &varEMPTY, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varBSTR, &varNULL, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varBSTR, &varI4, NULL));
        TEST_BOOLEAN_EQ(1, comstl_C_VARIANT_equal(&varBSTR, &varBSTR, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varBSTR, &varR8, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varBSTR, &varDECIMAL, NULL));
        if (VT_DISPATCH == COMSTL_ACCESS_VARIANT_vt_BYREF(varDISPATCH))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varDISPATCH, NULL));
        }
        if (VT_UNKNOWN == COMSTL_ACCESS_VARIANT_vt_BYREF(varUNKNOWN))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varUNKNOWN, NULL));
        }

        release_VARIANTS(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);
    }
}

static void test_VARIANT_equal_VT_R8()
{
    VARIANT varEMPTY;
    VARIANT varNULL;
    VARIANT varI4;
    VARIANT varBSTR;
    VARIANT varR8;
    VARIANT varDECIMAL;
    VARIANT varDISPATCH;
    VARIANT varUNKNOWN;
    HRESULT hr = setup_VARIANTs(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);

    if (FAILED(hr))
    {
        ; /* Issue warning */
    }
    else
    {
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varR8, &varEMPTY, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varR8, &varNULL, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varR8, &varI4, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varR8, &varBSTR, NULL));
        TEST_BOOLEAN_EQ(1, comstl_C_VARIANT_equal(&varR8, &varR8, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varR8, &varDECIMAL, NULL));
        if (VT_DISPATCH == COMSTL_ACCESS_VARIANT_vt_BYREF(varDISPATCH))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varDISPATCH, NULL));
        }
        if (VT_UNKNOWN == COMSTL_ACCESS_VARIANT_vt_BYREF(varUNKNOWN))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varUNKNOWN, NULL));
        }

        release_VARIANTS(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);
    }
}

static void test_VARIANT_equal_VT_DECIMAL()
{
    VARIANT varEMPTY;
    VARIANT varNULL;
    VARIANT varI4;
    VARIANT varBSTR;
    VARIANT varR8;
    VARIANT varDECIMAL;
    VARIANT varDISPATCH;
    VARIANT varUNKNOWN;
    HRESULT hr = setup_VARIANTs(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);

    if (FAILED(hr))
    {
        ; /* Issue warning */
    }
    else
    {
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varDECIMAL, &varEMPTY, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varDECIMAL, &varNULL, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varDECIMAL, &varI4, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varDECIMAL, &varBSTR, NULL));
        TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varDECIMAL, &varR8, NULL));
        TEST_BOOLEAN_EQ(1, comstl_C_VARIANT_equal(&varDECIMAL, &varDECIMAL, NULL));
        if (VT_DISPATCH == COMSTL_ACCESS_VARIANT_vt_BYREF(varDISPATCH))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varDISPATCH, NULL));
        }
        if (VT_UNKNOWN == COMSTL_ACCESS_VARIANT_vt_BYREF(varUNKNOWN))
        {
            TEST_BOOLEAN_EQ(0, comstl_C_VARIANT_equal(&varEMPTY, &varUNKNOWN, NULL));
        }

        release_VARIANTS(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);
    }
}

static void test_VARIANT_change_type_VT_I4(void)
{
    VARIANT varEMPTY;
    VARIANT varNULL;
    VARIANT varI4;
    VARIANT varBSTR;
    VARIANT varR8;
    VARIANT varDECIMAL;
    VARIANT varDISPATCH;
    VARIANT varUNKNOWN;
    HRESULT hr = setup_VARIANTs(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);

    if (FAILED(hr))
    {
        ; /* Issue warning */
    }
    else
    {
        VARIANT varEMPTYX;
        VARIANT varNULLX;
        VARIANT varI4X;
        VARIANT varBSTRX;
        VARIANT varR8X;
        VARIANT varDECIMALX;
        VARIANT varDISPATCHX;
        VARIANT varUNKNOWNX;

        init_VARIANTS(&varEMPTYX, &varNULLX, &varI4X, &varBSTRX, &varR8X, &varDECIMALX, &varDISPATCHX, &varUNKNOWNX);

        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varEMPTYX, &varEMPTY, LOCALE_USER_DEFAULT, 0, VT_I4)));
        TEST_BOOLEAN_EQ(1, FAILED(comstl_C_VARIANT_change_type(&varNULLX, &varNULL, LOCALE_USER_DEFAULT, 0, VT_I4)));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varI4X, &varI4, LOCALE_USER_DEFAULT, 0, VT_I4)));
        TEST_INT_EQ(VT_I4_VALUE, COMSTL_ACCESS_VARIANT_MEM_BYREF(varI4X, lVal));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varBSTRX, &varBSTR, LOCALE_USER_DEFAULT, 0, VT_I4)));
        TEST_INT_EQ(wcstol(VT_BSTR_VALUE, NULL, 0), COMSTL_ACCESS_VARIANT_MEM_BYREF(varBSTRX, lVal));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varR8X, &varR8, LOCALE_USER_DEFAULT, 0, VT_I4)));
        TEST_INT_EQ(ceil(VT_R8_VALUE), COMSTL_ACCESS_VARIANT_MEM_BYREF(varR8X, lVal));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varDECIMALX, &varDECIMAL, LOCALE_USER_DEFAULT, 0, VT_I4)));
        TEST_INT_EQ(VT_DECIMAL_VALUE, COMSTL_ACCESS_VARIANT_MEM_BYREF(varDECIMALX, lVal));
        if (VT_DISPATCH == COMSTL_ACCESS_VARIANT_vt_BYREF(varDISPATCH))
        {
            TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varDISPATCHX, &varDISPATCH, LOCALE_USER_DEFAULT, 0, VT_I4)));
            TEST_INT_EQ(VT_DISPATCH_VALUE, COMSTL_ACCESS_VARIANT_MEM_BYREF(varDISPATCHX, lVal));
        }
        if (VT_UNKNOWN == COMSTL_ACCESS_VARIANT_vt_BYREF(varUNKNOWN))
        {
            TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varUNKNOWNX, &varUNKNOWN, LOCALE_USER_DEFAULT, 0, VT_I4)));
            TEST_INT_EQ(wcstol(VT_UNKNOWN_VALUE, NULL, 0), COMSTL_ACCESS_VARIANT_MEM_BYREF(varUNKNOWNX, lVal));
        }

        release_VARIANTS(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);
    }
}

static void test_VARIANT_change_type_VT_R8(void)
{
    VARIANT varEMPTY;
    VARIANT varNULL;
    VARIANT varI4;
    VARIANT varBSTR;
    VARIANT varR8;
    VARIANT varDECIMAL;
    VARIANT varDISPATCH;
    VARIANT varUNKNOWN;
    HRESULT hr = setup_VARIANTs(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);

    if (FAILED(hr))
    {
        ; /* Issue warning */
    }
    else
    {
        VARIANT varEMPTYX;
        VARIANT varNULLX;
        VARIANT varI4X;
        VARIANT varBSTRX;
        VARIANT varR8X;
        VARIANT varDECIMALX;
        VARIANT varDISPATCHX;
        VARIANT varUNKNOWNX;

        init_VARIANTS(&varEMPTYX, &varNULLX, &varI4X, &varBSTRX, &varR8X, &varDECIMALX, &varDISPATCHX, &varUNKNOWNX);

        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varEMPTYX, &varEMPTY, LOCALE_USER_DEFAULT, 0, VT_R8)));
        TEST_BOOLEAN_EQ(1, FAILED(comstl_C_VARIANT_change_type(&varNULLX, &varNULL, LOCALE_USER_DEFAULT, 0, VT_R8)));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varI4X, &varI4, LOCALE_USER_DEFAULT, 0, VT_R8)));
        TEST_FP_EQ(ceil(VT_I4_VALUE), ceil(COMSTL_ACCESS_VARIANT_MEM_BYREF(varI4X, dblVal)));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varBSTRX, &varBSTR, LOCALE_USER_DEFAULT, 0, VT_R8)));
        TEST_FP_EQ(wcstod(VT_BSTR_VALUE, NULL), COMSTL_ACCESS_VARIANT_MEM_BYREF(varBSTRX, dblVal));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varR8X, &varR8, LOCALE_USER_DEFAULT, 0, VT_R8)));
        TEST_FP_EQ(VT_R8_VALUE, COMSTL_ACCESS_VARIANT_MEM_BYREF(varR8X, dblVal));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varDECIMALX, &varDECIMAL, LOCALE_USER_DEFAULT, 0, VT_R8)));
        TEST_FP_EQ((double)VT_DECIMAL_VALUE, COMSTL_ACCESS_VARIANT_MEM_BYREF(varDECIMALX, dblVal));
        if (VT_DISPATCH == COMSTL_ACCESS_VARIANT_vt_BYREF(varDISPATCH))
        {
            TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varDISPATCHX, &varDISPATCH, LOCALE_USER_DEFAULT, 0, VT_R8)));
            TEST_FP_EQ((double)VT_DISPATCH_VALUE, COMSTL_ACCESS_VARIANT_MEM_BYREF(varDISPATCHX, dblVal));
        }
        if (VT_UNKNOWN == COMSTL_ACCESS_VARIANT_vt_BYREF(varUNKNOWN))
        {
            TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varUNKNOWNX, &varUNKNOWN, LOCALE_USER_DEFAULT, 0, VT_R8)));
            TEST_FP_EQ((double)wcstol(VT_UNKNOWN_VALUE, NULL, 0), COMSTL_ACCESS_VARIANT_MEM_BYREF(varUNKNOWNX, dblVal));
        }

        release_VARIANTS(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);
    }
}

static void test_VARIANT_change_type_VT_BSTR(void)
{
    VARIANT varEMPTY;
    VARIANT varNULL;
    VARIANT varI4;
    VARIANT varBSTR;
    VARIANT varR8;
    VARIANT varDECIMAL;
    VARIANT varDISPATCH;
    VARIANT varUNKNOWN;
    HRESULT hr = setup_VARIANTs(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);

    if (FAILED(hr))
    {
        ; /* Issue warning */
    }
    else
    {
        VARIANT varEMPTYX;
        VARIANT varNULLX;
        VARIANT varI4X;
        VARIANT varBSTRX;
        VARIANT varR8X;
        VARIANT varDECIMALX;
        VARIANT varDISPATCHX;
        VARIANT varUNKNOWNX;

        init_VARIANTS(&varEMPTYX, &varNULLX, &varI4X, &varBSTRX, &varR8X, &varDECIMALX, &varDISPATCHX, &varUNKNOWNX);

        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varEMPTYX, &varEMPTY, LOCALE_USER_DEFAULT, 0, VT_BSTR)));
        TEST_BOOLEAN_EQ(1, FAILED(comstl_C_VARIANT_change_type(&varNULLX, &varNULL, LOCALE_USER_DEFAULT, 0, VT_BSTR)));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varI4X, &varI4, LOCALE_USER_DEFAULT, 0, VT_BSTR)));
        TEST_WS_EQ(STLSOFT_STRINGIZE_w(VT_I4_VALUE), COMSTL_ACCESS_VARIANT_MEM_BYREF(varI4X, bstrVal));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varBSTRX, &varBSTR, LOCALE_USER_DEFAULT, 0, VT_BSTR)));
        TEST_WS_EQ(VT_BSTR_VALUE, COMSTL_ACCESS_VARIANT_MEM_BYREF(varBSTRX, bstrVal));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varR8X, &varR8, LOCALE_USER_DEFAULT, 0, VT_BSTR)));
        TEST_WS_EQ(STLSOFT_STRINGIZE_w(VT_R8_VALUE), COMSTL_ACCESS_VARIANT_MEM_BYREF(varBSTRX, bstrVal));
        TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varDECIMALX, &varDECIMAL, LOCALE_USER_DEFAULT, 0, VT_BSTR)));
        TEST_WS_EQ(STLSOFT_STRINGIZE_w(VT_DECIMAL_VALUE), COMSTL_ACCESS_VARIANT_MEM_BYREF(varDECIMALX, bstrVal));
        if (VT_DISPATCH == COMSTL_ACCESS_VARIANT_vt_BYREF(varDISPATCH))
        {
            TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varDISPATCHX, &varDISPATCH, LOCALE_USER_DEFAULT, 0, VT_BSTR)));
            TEST_WS_EQ(STLSOFT_STRINGIZE_w(VT_DISPATCH_VALUE), COMSTL_ACCESS_VARIANT_MEM_BYREF(varDISPATCHX, bstrVal));
        }
        if (VT_UNKNOWN == COMSTL_ACCESS_VARIANT_vt_BYREF(varUNKNOWN))
        {
            TEST_BOOLEAN_EQ(1, SUCCEEDED(comstl_C_VARIANT_change_type(&varUNKNOWNX, &varUNKNOWN, LOCALE_USER_DEFAULT, 0, VT_BSTR)));
            TEST_WS_EQ(VT_UNKNOWN_VALUE, COMSTL_ACCESS_VARIANT_MEM_BYREF(varUNKNOWNX, bstrVal));
        }

        release_VARIANTS(&varEMPTY, &varNULL, &varI4, &varBSTR, &varR8, &varDECIMAL, &varDISPATCH, &varUNKNOWN);
    }
}


/* ///////////////////////////// end of file //////////////////////////// */

