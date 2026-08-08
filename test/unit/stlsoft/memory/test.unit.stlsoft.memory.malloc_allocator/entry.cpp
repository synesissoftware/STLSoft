/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.memory.malloc_allocator/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::malloc_allocator`.
 *
 * Created: 18th October 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/memory/malloc_allocator.hpp>

/* /////////////////////////////////////
 * general includes
 */


/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */

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

    if (XTESTS_START_RUNNER("test.unit.stlsoft.memory.malloc_allocator", verbosity))
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

static void test_alloc_0()
{

}

static void test_alloc_small()
{

}

static void test_alloc_medium()
{

}

static void test_alloc_large()
{

}

static void test_alloc_toolarge()
{

}

static void test_specialise_list()
{

}

static void test_specialise_vector()
{

}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

