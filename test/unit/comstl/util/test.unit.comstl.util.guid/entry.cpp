/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.comstl.util.guid/entry.cpp
 *
 * Purpose: Unit-tests for `comstl::guid`.
 *
 * Created: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

#include <comstl/util/guid.hpp>

#include <xtests/xtests.h>
#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>
#include <stlsoft/shims/access/string.hpp>

#include <stdlib.h>
#include <string.h>

namespace {

static void test_construction_from_string(void);
static void test_equality(void);
static void test_string_shims(void);

} // anonymous namespace

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    OleInitialize(NULL);

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.comstl.util.guid", verbosity))
    {
        XTESTS_RUN_CASE(test_construction_from_string);
        XTESTS_RUN_CASE(test_equality);
        XTESTS_RUN_CASE(test_string_shims);

        XTESTS_PRINT_RESULTS();
        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

namespace {

static void test_construction_from_string(void)
{
    GUID const expected = { 0xf4864792, 0xd0d2, 0x4005, { 0xab, 0xca, 0xf6, 0x79, 0x94, 0xc2, 0xff, 0xa6 } };
    comstl::guid const  g("{F4864792-D0D2-4005-ABCA-F67994C2FFA6}");

    TEST_BOOLEAN_TRUE(g.equal(expected));
    TEST_BOOLEAN_FALSE(g.equal(GUID_NULL));
}

static void test_equality(void)
{
    comstl::guid        g1("{F4864792-D0D2-4005-ABCA-F67994C2FFA6}");
    comstl::guid        g2(g1);

    TEST_BOOLEAN_TRUE(g1 == g2);
    TEST_BOOLEAN_TRUE(g1.equal(g2.get()));
}

static void test_string_shims(void)
{
    comstl::guid const  g(IID_IUnknown);
    cs_char_a_t const*  s = stlsoft::c_str_ptr_a(g);

    TEST_PTR_NE(NULL, s);
    TEST_UINT_NE(0u, stlsoft::c_str_len(g));
}

} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */
