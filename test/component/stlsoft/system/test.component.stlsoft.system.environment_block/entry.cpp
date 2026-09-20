/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.stlsoft.system.environment_block/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::environment_block`.
 *
 * Created: 11th August 2010
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */


// TODO: move stlsoft/containers/environment_block.hpp to stlsoft/system/environment_block.hpp
#include <stlsoft/containers/environment_block.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_empty();
    static void test_1_element();
    static void test_2_elements();
    static void test_clear();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.stlsoft.system.environment_block", verbosity))
    {
        XTESTS_RUN_CASE(test_empty);
        XTESTS_RUN_CASE(test_1_element);
        XTESTS_RUN_CASE(test_2_elements);
        XTESTS_RUN_CASE(test_clear);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_empty()
{
    stlsoft::environment_block_a block;

    TEST_INT_EQ(0u, block.size());
}

static void test_1_element()
{
    stlsoft::environment_block_a block;

    block.push_back("key-1", "value-1");

    TEST_INT_EQ(1u, block.size());
    TEST_MS_EQ("key-1=value-1", block.base()[0]);
}

static void test_2_elements()
{
    stlsoft::environment_block_a block;

    block.push_back("key-1", "value-1");
    block.push_back("key-0", "value-0");

    TEST_INT_EQ(2u, block.size());
    TEST_MS_EQ("key-1=value-1", block.base()[0]);
    TEST_MS_EQ("key-0=value-0", block.base()[1]);
}

static void test_clear()
{
    stlsoft::environment_block_a block;

    block.push_back("key-0", "value-0");
    block.push_back("key-1", "value-1");
    block.push_back("key-3", "value-3");

    TEST_INT_EQ(3u, block.size());

    block.clear();

    TEST_INT_EQ(0u, block.size());
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

