/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.security.security_initialisers/entry.cpp
 *
 * Purpose: Unit-tests for COM security initialiser helpers.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/security/security_initialisers.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

static void test_CoInitSecurity_appid(void); // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.security.security_initialisers", verbosity))
    {
        XTESTS_RUN_CASE(test_CoInitSecurity_appid);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

static void test_CoInitSecurity_appid(void)
{
    GUID const  appid = GUID_NULL;
    HRESULT     hr    = comstl::CoInitSecurity(appid, -1, NULL, RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IDENTIFY, NULL, EOAC_NONE);

    /* CoInitializeSecurity may only succeed before the first CoInitialize/OleInitialize
     * in a process, or may return RPC_E_TOO_LATE thereafter. Either outcome is acceptable
     * for this smoke test; we only require a definite HRESULT. */
    TEST_BOOLEAN_TRUE(SUCCEEDED(hr) || RPC_E_TOO_LATE == hr);
}


/* ///////////////////////////// end of file //////////////////////////// */
