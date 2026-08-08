/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.acestl.reactor.custom_event_handler/entry.cpp
 *
 * Purpose: Component-tests for `acestl::custom_event_handler`.
 *
 * Created: 9th August 2026
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <acestl/reactor/custom_event_handler.hpp>

#include <xtests/terse-api.h>

#include <stlsoft/stlsoft.h>

#include <ace/Reactor.h>

#include <stdlib.h>


namespace {

class test_handler
    : public acestl::custom_event_handler
{
public:
    test_handler()
        : m_lastCode(0)
        , m_lastArg(NULL)
        , m_eventCount(0)
    {}

    int handle_custom_event(ACE_Time_Value const& /*current_time*/, long code, void* arg)
    {
        m_lastCode = code;
        m_lastArg = arg;
        ++m_eventCount;

        return 0;
    }

    int handle_timeout(ACE_Time_Value const& /*current_time*/, void const* /*arg*/)
    {
        return 0;
    }

    long lastCode() const
    {
        return m_lastCode;
    }

    void* lastArg() const
    {
        return m_lastArg;
    }

    int eventCount() const
    {
        return m_eventCount;
    }

private:
    long m_lastCode;
    void* m_lastArg;
    int m_eventCount;
};

static void TEST_schedule_and_has_custom_events();
static void TEST_cancel_custom_event();

} // anonymous namespace


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
