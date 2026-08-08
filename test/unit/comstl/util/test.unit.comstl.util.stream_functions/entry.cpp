/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.stream_functions/entry.cpp
 *
 * Purpose: Unit-tests for COM stream helper functions.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/util/stream_functions.h>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <stdlib.h>

namespace {

static void test_get_stream_size(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.util.stream_functions", verbosity))
    {
        XTESTS_RUN_CASE(test_get_stream_size);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_get_stream_size(void)
{
    IStream*            pstm = NULL;
    ULARGE_INTEGER      size = { 0 };
    unsigned char const data[] = { 1, 2, 3, 4, 5 };

    TEST_INT_EQ((int)S_OK, (int)::CreateStreamOnHGlobal(NULL, TRUE, &pstm));
    TEST_PTR_NE(NULL, pstm);

    TEST_INT_EQ((int)S_OK, (int)pstm->Write(data, sizeof(data), NULL));
    TEST_INT_EQ((int)S_OK, (int)comstl::get_stream_size(pstm, &size));
    TEST_UINT_EQ((cs_uint32_t)sizeof(data), size.LowPart);

    pstm->Release();
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
