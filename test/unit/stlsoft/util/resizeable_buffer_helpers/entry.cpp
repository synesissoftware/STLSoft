/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/util/resizeable_buffer_helpers/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::resizeable_buffer_resize`.
 *
 * Created: 15th October 2026
 * Updated: 15th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/util/resizeable_buffer_helpers.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/memory/auto_buffer.hpp>
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <vector>

/* Standard C header files */
#include <stddef.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_WITH_auto_buffer_GROW();
    static void TEST_WITH_auto_buffer_SHRINK();
    static void TEST_WITH_auto_buffer_TO_ZERO();
    static void TEST_WITH_bool_returning_stub_FAILURE();
    static void TEST_WITH_bool_returning_stub_SUCCESS();
    static void TEST_WITH_vector_GROW();
    static void TEST_WITH_vector_SHRINK();
    static void TEST_WITH_vector_TO_ZERO();
    static void TEST_WITH_void_returning_stub_SUCCESS();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.resizeable_buffer_helpers", verbosity))
    {
        XTESTS_RUN_CASE(TEST_WITH_auto_buffer_GROW);
        XTESTS_RUN_CASE(TEST_WITH_auto_buffer_SHRINK);
        XTESTS_RUN_CASE(TEST_WITH_auto_buffer_TO_ZERO);
        XTESTS_RUN_CASE(TEST_WITH_bool_returning_stub_FAILURE);
        XTESTS_RUN_CASE(TEST_WITH_bool_returning_stub_SUCCESS);
        XTESTS_RUN_CASE(TEST_WITH_vector_GROW);
        XTESTS_RUN_CASE(TEST_WITH_vector_SHRINK);
        XTESTS_RUN_CASE(TEST_WITH_vector_TO_ZERO);
        XTESTS_RUN_CASE(TEST_WITH_void_returning_stub_SUCCESS);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

/** Minimal resizeable-buffer stub whose <code>resize()</code> returns
 *  <code>bool</code>, optionally failing.
 */
class bool_returning_stub
{
public: // types
    typedef char                                            value_type;
    typedef size_t                                          size_type;

public: // construction
    bool_returning_stub()
        : m_size(0)
        , m_fail(false)
    {}

public: // accessors
    size_type size() const
    {
        return m_size;
    }

public: // operations
    void set_fail(bool fail)
    {
        m_fail = fail;
    }

    bool resize(size_type newSize)
    {
        if (m_fail)
        {
            return false;
        }

        m_size = newSize;

        return true;
    }

private: // fields
    size_type   m_size;
    bool        m_fail;
};

/** Minimal resizeable-buffer stub whose <code>resize()</code> returns
 *  <code>void</code>.
 */
class void_returning_stub
{
public: // types
    typedef char                                            value_type;
    typedef size_t                                          size_type;

public: // construction
    void_returning_stub()
        : m_size(0)
    {}

public: // accessors
    size_type size() const
    {
        return m_size;
    }

public: // operations
    void resize(size_type newSize)
    {
        m_size = newSize;
    }

private: // fields
    size_type m_size;
};


static void TEST_WITH_auto_buffer_GROW()
{
    stlsoft::auto_buffer<char> rb(1);

    TEST_BOOLEAN_TRUE(stlsoft::resizeable_buffer_resize(rb, 32));
    TEST_INT_EQ(32, rb.size());
}

static void TEST_WITH_auto_buffer_SHRINK()
{
    stlsoft::auto_buffer<char> rb(64);

    TEST_BOOLEAN_TRUE(stlsoft::resizeable_buffer_resize(rb, 8));
    TEST_INT_EQ(8, rb.size());
}

static void TEST_WITH_auto_buffer_TO_ZERO()
{
    stlsoft::auto_buffer<char> rb(16);

    TEST_BOOLEAN_TRUE(stlsoft::resizeable_buffer_resize(rb, 0));
    TEST_INT_EQ(0, rb.size());
}

static void TEST_WITH_vector_GROW()
{
    std::vector<char> rb(1, 'x');

    TEST_BOOLEAN_TRUE(stlsoft::resizeable_buffer_resize(rb, 32));
    TEST_INT_EQ(32, rb.size());
}

static void TEST_WITH_vector_SHRINK()
{
    std::vector<char> rb(64, 'x');

    TEST_BOOLEAN_TRUE(stlsoft::resizeable_buffer_resize(rb, 8));
    TEST_INT_EQ(8, rb.size());
}

static void TEST_WITH_vector_TO_ZERO()
{
    std::vector<char> rb(16, 'x');

    TEST_BOOLEAN_TRUE(stlsoft::resizeable_buffer_resize(rb, 0));
    TEST_INT_EQ(0, rb.size());
}

static void TEST_WITH_bool_returning_stub_SUCCESS()
{
    bool_returning_stub rb;

    TEST_BOOLEAN_TRUE(stlsoft::resizeable_buffer_resize(rb, 10));
    TEST_INT_EQ(10, rb.size());
}

static void TEST_WITH_bool_returning_stub_FAILURE()
{
    bool_returning_stub rb;

    rb.set_fail(true);

    TEST_BOOLEAN_FALSE(stlsoft::resizeable_buffer_resize(rb, 10));
    TEST_INT_EQ(0, rb.size());
}

static void TEST_WITH_void_returning_stub_SUCCESS()
{
    void_returning_stub rb;

    TEST_BOOLEAN_TRUE(stlsoft::resizeable_buffer_resize(rb, 10));
    TEST_INT_EQ(10, rb.size());
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

