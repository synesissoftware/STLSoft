/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.acestl.memory.message_block_functions/entry.cpp
 *
 * Purpose: Unit-tests for `acestl::make_copied_Message_Block`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <acestl/memory/message_block_functions.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <ace/Message_Block.h>

#include <stdlib.h>
#include <string.h>


namespace {

static void TEST_make_copied_Message_Block_with_data();
static void TEST_make_copied_Message_Block_nullptr();
static void TEST_make_copied_Message_Block_array();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.acestl.memory.message_block_functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_make_copied_Message_Block_with_data);
        XTESTS_RUN_CASE(TEST_make_copied_Message_Block_nullptr);
        XTESTS_RUN_CASE(TEST_make_copied_Message_Block_array);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

static void TEST_make_copied_Message_Block_with_data()
{
    char const contents[] = "Contents";
    ACE_Message_Block *pmb = acestl::make_copied_Message_Block(contents, STLSOFT_NUM_ELEMENTS(contents) - 1);

    TEST_PTR_NE(NULL, pmb);
    TEST_INT_EQ(STLSOFT_NUM_ELEMENTS(contents) - 1, pmb->length());
    TEST_MS_EQ(contents, pmb->rd_ptr());

    pmb->release();
}

static void TEST_make_copied_Message_Block_nullptr()
{
    ACE_Message_Block *pmb = acestl::make_copied_Message_Block(static_cast<char const*>(NULL), 16);

    TEST_PTR_NE(NULL, pmb);
    TEST_INT_EQ(16, pmb->length());

    pmb->release();
}

static void TEST_make_copied_Message_Block_array()
{
    char const contents[] = "array";

    ACE_Message_Block *pmb = acestl::make_copied_Message_Block(contents);

    TEST_PTR_NE(NULL, pmb);
    TEST_INT_EQ(STLSOFT_NUM_ELEMENTS(contents) - 1, pmb->length());
    TEST_MS_EQ(contents, pmb->rd_ptr());

    pmb->release();
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
