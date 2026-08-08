/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.acyclic_connector/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::acyclic_connector`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/util/acyclic_connector.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>
#include <stlsoft/synch/null_mutex.hpp>

#include "../../helpers/mock_unknown.hpp"

#include <stdlib.h>

namespace {

using test_comstl::mock_unknown;

typedef comstl::acyclic_connector<stlsoft::null_mutex> connector_t;

static void test_query_peer(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.util.acyclic_connector", verbosity))
    {
        XTESTS_RUN_CASE(test_query_peer);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_query_peer(void)
{
    mock_unknown    left;
    mock_unknown    right;
    IAcyclicSide*   leftSide  = NULL;
    IAcyclicSide*   rightSide = NULL;
    connector_t*    conn = new connector_t(&left, &leftSide, &right, &rightSide);
    STLSOFT_SUPPRESS_UNUSED(conn);
    IUnknown*       peer      = NULL;

    TEST_PTR_NE(NULL, leftSide);
    TEST_PTR_NE(NULL, rightSide);

    TEST_INT_EQ((int)S_OK, (int)leftSide->QueryPeer(IID_IUnknown, reinterpret_cast<void**>(&peer)));
    TEST_PTR_NE(NULL, peer);

    peer->Release();
    leftSide->Release();
    rightSide->Release();
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
