/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.acestl.reactor.custom_event_handler/entry.cpp
 *
 * Purpose: Component-tests for `acestl::custom_event_handler`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 * Note:    Auto-generated on 9th August 2026 (test initiative); regenerate via test/scripts/ rather than hand-editing layout.
 *
 * ////////////////////////////////////////////////////////////////////// */



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <acestl/reactor/custom_event_handler.hpp>
#include <xtests/xtests.h>
#include <xtests/terse-api.h>
#include <stlsoft/stlsoft.h>
#include <ace/Reactor.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_schedule_and_has_custom_events(void);
    static void TEST_cancel_custom_event(void);
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.component.acestl.reactor.custom_event_handler", verbosity))
    {
        XTESTS_RUN_CASE(TEST_schedule_and_has_custom_events);
        XTESTS_RUN_CASE(TEST_cancel_custom_event);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_schedule_and_has_custom_events()
{
    test_handler handler;

    TEST_PTR_NE(NULL, handler.schedule_custom_event(100));
    TEST_BOOLEAN_TRUE(handler.has_custom_events(100));
    TEST_BOOLEAN_FALSE(handler.has_custom_events(200));
}

static void TEST_cancel_custom_event()
{
    test_handler handler;

    acestl::custom_event_handler::event_id const id = handler.schedule_custom_event(200);

    TEST_PTR_NE(NULL, id);
    TEST_BOOLEAN_TRUE(handler.has_custom_events(200));

    handler.cancel_custom_event(id);

    TEST_BOOLEAN_FALSE(handler.has_custom_events(200));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
