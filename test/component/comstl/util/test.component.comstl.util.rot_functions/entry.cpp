/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.comstl.util.rot_functions/entry.cpp
 *
 * Purpose: Component tests for COM Running Object Table helpers.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/util/rot_functions.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_register_is_running_revoke(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.comstl.util.rot_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_register_is_running_revoke);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_register_is_running_revoke(void)
{
    IUnknown*   punk = NULL;
    IMoniker*   pmk  = NULL;
    DWORD       dwReg = 0;

    TEST_INT_EQ((int)S_OK, (int)::CoCreateInstance(CLSID_StdGlobalInterfaceTable, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, reinterpret_cast<void**>(&punk)));
    TEST_INT_EQ((int)S_OK, (int)::CreateItemMoniker(L"!", L"STLSoft.COMSTL.ROT.Test", &pmk));

    TEST_INT_EQ((int)S_OK, (int)comstl::Rot_Register(ROTFLAGS_REGISTRATIONKEEPSALIVE, punk, pmk, &dwReg));
    TEST_INT_EQ((int)S_OK, (int)comstl::Rot_IsRunning(pmk));
    TEST_INT_EQ((int)S_OK, (int)comstl::Rot_Revoke(dwReg));

    pmk->Release();
    punk->Release();
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
