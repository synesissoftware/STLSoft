/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/winstl/memory/global_allocator/entry.cpp
 *
 * Purpose: Unit-tests for `winstl::global_allocator`.
 *
 * Created: 18th October 2024
 * Updated: 14th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/memory/global_allocator.hpp>

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

    static void TEST_ALLOC_0();
    static void TEST_ALLOC_SMALL();
    static void TEST_ALLOC_MEDIUM();
    static void TEST_ALLOC_LARGE();
    static void TEST_ALLOC_TOOLARGE();

    static void TEST_SPECIALISE_LIST();
    static void TEST_SPECIALISE_VECTOR();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.memory.global_allocator", verbosity))
    {
        XTESTS_RUN_CASE(TEST_ALLOC_0);
        XTESTS_RUN_CASE(TEST_ALLOC_SMALL);
        XTESTS_RUN_CASE(TEST_ALLOC_MEDIUM);
        XTESTS_RUN_CASE(TEST_ALLOC_LARGE);
        XTESTS_RUN_CASE(TEST_ALLOC_TOOLARGE);

        XTESTS_RUN_CASE(TEST_SPECIALISE_LIST);
        XTESTS_RUN_CASE(TEST_SPECIALISE_VECTOR);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

typedef winstl::global_allocator<int> allocator_t;

static void exercise_allocate(allocator_t::size_type n)
{
    allocator_t             ator;
    allocator_t::pointer    p = ator.allocate(n);

    TEST_PTR_NOT_NULL(p);

    for (allocator_t::size_type i = 0; i != n; ++i)
    {
        ator.construct(&p[i], static_cast<int>(i));
    }

    for (allocator_t::size_type i = 0; i != n; ++i)
    {
        TEST_INT_EQ(static_cast<int>(i), p[i]);

        ator.destroy(&p[i]);
    }

    ator.deallocate(p, n);
}

static void TEST_ALLOC_0()
{
    allocator_t a1;
    allocator_t a2;

    TEST_BOOLEAN_TRUE(a1 == a2);
    TEST_BOOLEAN_FALSE(a1 != a2);

    allocator_t::pointer p = a1.allocate(0);

    TEST_PTR_NOT_NULL(p);

    a1.deallocate(p);
}

static void TEST_ALLOC_SMALL()
{
    exercise_allocate(4);
}

static void TEST_ALLOC_MEDIUM()
{
    exercise_allocate(256);
}

static void TEST_ALLOC_LARGE()
{
    exercise_allocate(4096);
}

static void TEST_ALLOC_TOOLARGE()
{
    allocator_t                     ator;
    allocator_t::size_type const    too_large = ator.max_size() + 1;

    try
    {
        static_cast<void>(ator.allocate(too_large));

        TEST_FAIL("should not get here");
    }
    catch (stlsoft::out_of_memory_exception&)
    {
        TEST_PASSED();
    }
}

static void TEST_SPECIALISE_LIST()
{
    typedef std::list<int, allocator_t>     list_t;

    list_t  items;

    items.push_back(10);
    items.push_back(20);
    items.push_back(30);

    TEST_INT_EQ(3u, items.size());

    list_t::const_iterator it = items.begin();

    TEST_INT_EQ(10, *it);
    ++it;
    TEST_INT_EQ(20, *it);
    ++it;
    TEST_INT_EQ(30, *it);
}

static void TEST_SPECIALISE_VECTOR()
{
    typedef std::vector<int, allocator_t>   vector_t;

    vector_t    v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    TEST_INT_EQ(3u, v.size());
    TEST_INT_EQ(10, v[0]);
    TEST_INT_EQ(20, v[1]);
    TEST_INT_EQ(30, v[2]);

    v.resize(1);

    TEST_INT_EQ(1u, v.size());
    TEST_INT_EQ(10, v[0]);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

