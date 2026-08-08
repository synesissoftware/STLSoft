/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.acestl.collections.message_queue_sequence/entry.cpp
 *
 * Purpose: Component-tests for `acestl::message_queue_sequence`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <acestl/collections/message_queue_sequence.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/memory/auto_buffer.hpp>
#include <stlsoft/stlsoft.h>

#include <ace/Message_Queue.h>
#include <ace/Synch_Traits.h>

#include <algorithm>
#include <stdlib.h>
#include <string.h>


namespace {

static void TEST_empty_sequence();
static void TEST_copy_sequence();

} // anonymous namespace


int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.acestl.collections.message_queue_sequence", verbosity))
    {
        XTESTS_RUN_CASE(TEST_empty_sequence);
        XTESTS_RUN_CASE(TEST_copy_sequence);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


namespace {

typedef ACE_Message_Queue<ACE_SYNCH> queue_type;
typedef acestl::message_queue_sequence<ACE_SYNCH> sequence_type;

static void TEST_empty_sequence()
{
    queue_type q;
    sequence_type mqs(q);

    TEST_INT_EQ(0u, mqs.size());
    TEST_BOOLEAN_TRUE(mqs.empty());
    TEST_BOOLEAN_TRUE(mqs.begin() == mqs.end());
}

static void TEST_copy_sequence()
{
    char const payload[] = "message-queue-sequence";
    queue_type q;
    ACE_Message_Block *pmb = new ACE_Message_Block(STLSOFT_NUM_ELEMENTS(payload));

    STLSOFT_API_EXTERNAL_memfns_memcpy(pmb->wr_ptr(), payload, STLSOFT_NUM_ELEMENTS(payload));
    pmb->wr_ptr(STLSOFT_NUM_ELEMENTS(payload));

    TEST_INT_EQ(0, q.enqueue(pmb));

    sequence_type mqs(q);

    TEST_INT_EQ(STLSOFT_NUM_ELEMENTS(payload), mqs.size());
    TEST_BOOLEAN_FALSE(mqs.empty());

    stlsoft::auto_buffer<char> buff(mqs.size());

    std::copy(mqs.begin(), mqs.end(), &buff[0]);

    TEST_MS_EQ(payload, &buff[0]);

    ACE_Message_Block *pdeq = NULL;

    TEST_INT_EQ(0, q.dequeue(pdeq));
    TEST_PTR_NE(NULL, pdeq);

    pdeq->release();
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
