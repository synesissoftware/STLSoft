/* /////////////////////////////////////////////////////////////////////////
 * File:    null_allocator/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::null_allocator`.
 *
 * Created: 18th October 2024
 * Updated: 30th September 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/memory/null_allocator.hpp>

/* /////////////////////////////////////
 * general includes
 */


/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/exception/out_of_memory_exception.hpp>
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <list>
#include <vector>

/* Standard C header files */
#include <assert.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_alloc_0();
    static void test_alloc_small();
    static void test_alloc_medium();
    static void test_alloc_large();
    static void test_alloc_toolarge();

    static void test_specialise_list();
    static void test_specialise_vector();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.memory.null_allocator", verbosity))
    {
        XTESTS_RUN_CASE(test_alloc_0);
        XTESTS_RUN_CASE(test_alloc_small);
        XTESTS_RUN_CASE(test_alloc_medium);
        XTESTS_RUN_CASE(test_alloc_large);
        XTESTS_RUN_CASE(test_alloc_toolarge);

        XTESTS_RUN_CASE(test_specialise_list);
        XTESTS_RUN_CASE(test_specialise_vector);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

typedef stlsoft::null_allocator<int> allocator_t;

static void expect_out_of_memory(allocator_t& ator, allocator_t::size_type n)
{
    int threw = 0;

    try
    {
        static_cast<void>(ator.allocate(n));
    }
    catch (stlsoft::out_of_memory_exception&)
    {
        threw = 1;
    }

    TEST_INT_EQ(1, threw);
}

static void test_alloc_0()
{
    allocator_t a1;
    allocator_t a2;

    TEST_BOOLEAN_TRUE(a1 == a2);
    TEST_BOOLEAN_FALSE(a1 != a2);

    expect_out_of_memory(a1, 0);
}

static void test_alloc_small()
{
    allocator_t ator;

    expect_out_of_memory(ator, 4);
}

static void test_alloc_medium()
{
    allocator_t ator;

    expect_out_of_memory(ator, 256);
}

static void test_alloc_large()
{
    allocator_t ator;

    expect_out_of_memory(ator, 4096);
}

static void test_alloc_toolarge()
{
    allocator_t                     ator;
    allocator_t::size_type const    too_large = ator.max_size() + 1;

    expect_out_of_memory(ator, too_large);
}

static void test_specialise_list()
{
    try
    {
        std::list<int, allocator_t> items;

        items.push_back(1);

        TEST_FAIL("should not get here");
    }
    catch (stlsoft::out_of_memory_exception&)
    {
        TEST_PASSED();
    }
}

static void test_specialise_vector()
{
    try
    {
        std::vector<int, allocator_t> v;

        v.push_back(1);

        TEST_FAIL("should not get here");
    }
    catch (stlsoft::out_of_memory_exception&)
    {
        TEST_PASSED();
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

