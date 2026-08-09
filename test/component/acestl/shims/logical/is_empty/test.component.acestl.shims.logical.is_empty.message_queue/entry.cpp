/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.acestl.shims.logical.is_empty.message_queue/entry.cpp
 *
 * Purpose: Component-tests for is_empty shims for `ACE_Message_Queue`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <acestl/shims/logical/is_empty/message_queue.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <ace/Message_Queue.h>
#include <ace/Synch_Traits.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_empty_queue(void);
    static void TEST_non_empty_queue(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.acestl.shims.logical.is_empty.message_queue", verbosity))
    {
        XTESTS_RUN_CASE(TEST_empty_queue);
        XTESTS_RUN_CASE(TEST_non_empty_queue);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

typedef ACE_Message_Queue<ACE_SYNCH> queue_type;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_empty_queue()
{
    queue_type q;

    TEST_BOOLEAN_TRUE(stlsoft::is_empty(q));
    TEST_BOOLEAN_TRUE(stlsoft::is_empty(q, stlsoft::is_empty_type()));
}

static void TEST_non_empty_queue()
{
    queue_type q;
    ACE_Message_Block mb(16);

    TEST_INT_EQ(0, q.enqueue(&mb));

    TEST_BOOLEAN_FALSE(stlsoft::is_empty(q));
    TEST_BOOLEAN_FALSE(stlsoft::is_empty(q, stlsoft::is_empty_type()));

    ACE_Message_Block *pmb = NULL;

    TEST_INT_EQ(0, q.dequeue(pmb));
    TEST_PTR_NE(NULL, pmb);

    pmb->release();
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
