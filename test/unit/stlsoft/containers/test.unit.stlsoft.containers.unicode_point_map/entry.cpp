/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.containers.unicode_point_map/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::unicode_point_map`.
 *
 * Created: 5th November 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* ///////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/containers/unicode_point_map.hpp>


/* ///////////////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#if __cplusplus >= 201103L
# include <list>
#endif
#include <numeric>
#include <stdexcept>
#if __cplusplus >= 201103L
# include <type_traits>
#endif
#include <string>
#include <vector>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_ctor_default_1();
    static void test_ctor_default_2();
#if __cplusplus >= 201103L

    static void test_ctor_initializer_list_1();
    static void test_ctor_initializer_list_2();
#endif
    static void test_push_1();
    static void test_push_2();
    static void test_push_n_1();
    static void test_push_n_2();
    static void test_clear();
//     static void test_merge();
//     static void test_op_addassign();
//     static void test_op_add();
    static void test_swap();
    static void test_swap_std();
    static void test_iteration_1();
//     static void test_iteration_order_1();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.containers.unicode_point_map", verbosity))
    {
        XTESTS_RUN_CASE(test_ctor_default_1);
        XTESTS_RUN_CASE(test_ctor_default_2);
#if __cplusplus >= 201103L

        XTESTS_RUN_CASE(test_ctor_initializer_list_1);
        XTESTS_RUN_CASE(test_ctor_initializer_list_2);
#endif
        XTESTS_RUN_CASE(test_push_1);
        XTESTS_RUN_CASE(test_push_2);
        XTESTS_RUN_CASE(test_push_n_1);
        XTESTS_RUN_CASE(test_push_n_2);
        XTESTS_RUN_CASE(test_clear);
        XTESTS_RUN_CASE(test_swap);
        XTESTS_RUN_CASE(test_swap_std);
        XTESTS_RUN_CASE(test_iteration_1);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * utility functions
 */


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::unicode_point_map;


static void test_ctor_default_1()
{
    unicode_point_map const upm;

    TEST_BOOLEAN_TRUE(upm.empty());
    TEST_INT_EQ(0u, upm.size());
    TEST_INT_EQ(0, upm.total());

    TEST_INT_EQ(0, upm[' ']);
    TEST_INT_EQ(0, upm['A']);
    TEST_INT_EQ(0, upm['a']);
    TEST_INT_EQ(0, upm['b']);
    TEST_INT_EQ(0, upm['c']);
    TEST_INT_EQ(0, upm['d']);
    TEST_INT_EQ(0, upm['e']);
    TEST_INT_EQ(0, upm['f']);
}

static void test_ctor_default_2()
{
    unicode_point_map const upm(0x64); // 'd'

    TEST_BOOLEAN_TRUE(upm.empty());
    TEST_INT_EQ(0u, upm.size());
    TEST_INT_EQ(0, upm.total());

    TEST_INT_EQ(0, upm[' ']);
    TEST_INT_EQ(0, upm['A']);
    TEST_INT_EQ(0, upm['a']);
    TEST_INT_EQ(0, upm['b']);
    TEST_INT_EQ(0, upm['c']);
    TEST_INT_EQ(0, upm['d']);
    TEST_INT_EQ(0, upm['e']);
    TEST_INT_EQ(0, upm['f']);
}

#if __cplusplus >= 201103L

static void test_ctor_initializer_list_1()
{
    unicode_point_map upm = { 'a', 'b', 'c', 'd', 'd', 'd', 'a' };

    TEST_INT_EQ(0, upm[' ']);
    TEST_INT_EQ(0, upm['A']);
    TEST_INT_EQ(2, upm['a']);
    TEST_INT_EQ(1, upm['b']);
    TEST_INT_EQ(1, upm['c']);
    TEST_INT_EQ(3, upm['d']);
    TEST_INT_EQ(0, upm['e']);
    TEST_INT_EQ(0, upm['f']);
}

static void test_ctor_initializer_list_2()
{
    unicode_point_map upm(0x64, { 'a', 'b', 'c', 'd', 'd', 'd', 'a' });

    TEST_INT_EQ(0, upm[' ']);
    TEST_INT_EQ(0, upm['A']);
    TEST_INT_EQ(2, upm['a']);
    TEST_INT_EQ(1, upm['b']);
    TEST_INT_EQ(1, upm['c']);
    TEST_INT_EQ(3, upm['d']);
    TEST_INT_EQ(0, upm['e']);
    TEST_INT_EQ(0, upm['f']);
}
#endif

static void test_push_1()
{
    unicode_point_map upm;

    TEST_BOOLEAN_TRUE(upm.empty());
    TEST_INT_EQ(0u, upm.size());
    TEST_INT_EQ(0, upm.total());

    upm.push('a');
    upm.push('b');
    upm.push('a');
    upm.push('c');
    upm.push('d');
    upm.push('d');
    upm.push('d');

    TEST_INT_EQ(0, upm[' ']);
    TEST_INT_EQ(0, upm['A']);
    TEST_INT_EQ(2, upm['a']);
    TEST_INT_EQ(1, upm['b']);
    TEST_INT_EQ(1, upm['c']);
    TEST_INT_EQ(3, upm['d']);
    TEST_INT_EQ(0, upm['e']);
    TEST_INT_EQ(0, upm['f']);
}

static void test_push_2()
{
    unicode_point_map upm(0x64); // 'd'

    TEST_BOOLEAN_TRUE(upm.empty());
    TEST_INT_EQ(0u, upm.size());
    TEST_INT_EQ(0, upm.total());

    upm.push('a');
    upm.push('b');
    upm.push('a');
    upm.push('c');
    upm.push('d');
    upm.push('d');
    upm.push('d');

    TEST_INT_EQ(0, upm[' ']);
    TEST_INT_EQ(0, upm['A']);
    TEST_INT_EQ(2, upm['a']);
    TEST_INT_EQ(1, upm['b']);
    TEST_INT_EQ(1, upm['c']);
    TEST_INT_EQ(3, upm['d']);
    TEST_INT_EQ(0, upm['e']);
    TEST_INT_EQ(0, upm['f']);
}

static void test_push_n_1()
{
    unicode_point_map upm;

    TEST_BOOLEAN_TRUE(upm.empty());
    TEST_INT_EQ(0u, upm.size());
    TEST_INT_EQ(0, upm.total());

    upm.push_n('a', 2);
    upm.push_n('b', -1);
    upm.push_n('c', 0);
    upm.push_n('d', 3);
    upm.push_n('e', 1);
    upm.push_n('e', 1);
    upm.push_n('e', -2);

    TEST_INT_EQ(0, upm[' ']);
    TEST_INT_EQ(0, upm['A']);
    TEST_INT_EQ(2, upm['a']);
    TEST_INT_EQ(-1, upm['b']);
    TEST_INT_EQ(0, upm['c']);
    TEST_INT_EQ(3, upm['d']);
    TEST_INT_EQ(0, upm['e']);
    TEST_INT_EQ(0, upm['f']);
}

static void test_push_n_2()
{
    unicode_point_map upm(0x64); // 'd'

    TEST_BOOLEAN_TRUE(upm.empty());
    TEST_INT_EQ(0u, upm.size());
    TEST_INT_EQ(0, upm.total());

    upm.push_n('a', 2);
    upm.push_n('b', -1);
    upm.push_n('c', 0);
    upm.push_n('d', 3);
    upm.push_n('e', 1);
    upm.push_n('e', 1);
    upm.push_n('e', -2);

    TEST_INT_EQ(0, upm[' ']);
    TEST_INT_EQ(0, upm['A']);
    TEST_INT_EQ(2, upm['a']);
    TEST_INT_EQ(-1, upm['b']);
    TEST_INT_EQ(0, upm['c']);
    TEST_INT_EQ(3, upm['d']);
    TEST_INT_EQ(0, upm['e']);
    TEST_INT_EQ(0, upm['f']);
}

static void test_clear()
{
    unicode_point_map upm;

    TEST_BOOLEAN_TRUE(upm.empty());
    TEST_INT_EQ(0u, upm.size());
    TEST_INT_EQ(0, upm.total());

    upm.push_n('a', 2);
    upm.push_n('b', -1);
    upm.push_n('c', 0);
    upm.push_n('d', 1);
    upm.push_n('d', 1);
    upm.push_n('d', -2);

    TEST_INT_EQ(0, upm[' ']);
    TEST_INT_EQ(0, upm['A']);
    TEST_INT_EQ(2, upm['a']);
    TEST_INT_EQ(-1, upm['b']);
    TEST_INT_EQ(0, upm['c']);
    TEST_INT_EQ(0, upm['d']);
    TEST_INT_EQ(0, upm['e']);
    TEST_INT_EQ(0, upm['f']);

    upm.clear();

    TEST_INT_EQ(0, upm[' ']);
    TEST_INT_EQ(0, upm['A']);
    TEST_INT_EQ(0, upm['a']);
    TEST_INT_EQ(0, upm['b']);
    TEST_INT_EQ(0, upm['c']);
    TEST_INT_EQ(0, upm['d']);
    TEST_INT_EQ(0, upm['e']);
    TEST_INT_EQ(0, upm['f']);
}

static void test_swap()
{
    {
        unicode_point_map upm1;
        unicode_point_map upm2;

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());

        upm1.swap(upm2);

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());
    }

    {
        unicode_point_map upm1;
        unicode_point_map upm2;

        upm1.push('A');
        upm1.push('a');
        upm1.push('1');

        upm2.push('B');
        upm2.push('b');
        upm2.push('2');
        upm2.push_n('3', 10);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(3u, upm1.size());
        TEST_INT_EQ(3, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(1, upm1['A']);
        TEST_INT_EQ(0, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(1, upm1['a']);
        TEST_INT_EQ(0, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(1, upm1['1']);
        TEST_INT_EQ(0, upm1['2']);
        TEST_INT_EQ(0, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(4u, upm2.size());
        TEST_INT_EQ(13, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(0, upm2['A']);
        TEST_INT_EQ(1, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(0, upm2['a']);
        TEST_INT_EQ(1, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(0, upm2['1']);
        TEST_INT_EQ(1, upm2['2']);
        TEST_INT_EQ(10, upm2['3']);

        upm1.swap(upm2);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(4u, upm1.size());
        TEST_INT_EQ(13, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(0, upm1['A']);
        TEST_INT_EQ(1, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(0, upm1['a']);
        TEST_INT_EQ(1, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(0, upm1['1']);
        TEST_INT_EQ(1, upm1['2']);
        TEST_INT_EQ(10, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(3u, upm2.size());
        TEST_INT_EQ(3, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(1, upm2['A']);
        TEST_INT_EQ(0, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(1, upm2['a']);
        TEST_INT_EQ(0, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(1, upm2['1']);
        TEST_INT_EQ(0, upm2['2']);
        TEST_INT_EQ(0, upm2['3']);
    }

    {
        unicode_point_map upm1(0x60);
        unicode_point_map upm2(0x60);

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());

        upm1.swap(upm2);

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());
    }

    {
        unicode_point_map upm1(0x60);
        unicode_point_map upm2(0x60);

        upm1.push('A');
        upm1.push('a');
        upm1.push('1');

        upm2.push('B');
        upm2.push('b');
        upm2.push('2');
        upm2.push_n('3', 10);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(3u, upm1.size());
        TEST_INT_EQ(3, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(1, upm1['A']);
        TEST_INT_EQ(0, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(1, upm1['a']);
        TEST_INT_EQ(0, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(1, upm1['1']);
        TEST_INT_EQ(0, upm1['2']);
        TEST_INT_EQ(0, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(4u, upm2.size());
        TEST_INT_EQ(13, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(0, upm2['A']);
        TEST_INT_EQ(1, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(0, upm2['a']);
        TEST_INT_EQ(1, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(0, upm2['1']);
        TEST_INT_EQ(1, upm2['2']);
        TEST_INT_EQ(10, upm2['3']);

        upm1.swap(upm2);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(4u, upm1.size());
        TEST_INT_EQ(13, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(0, upm1['A']);
        TEST_INT_EQ(1, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(0, upm1['a']);
        TEST_INT_EQ(1, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(0, upm1['1']);
        TEST_INT_EQ(1, upm1['2']);
        TEST_INT_EQ(10, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(3u, upm2.size());
        TEST_INT_EQ(3, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(1, upm2['A']);
        TEST_INT_EQ(0, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(1, upm2['a']);
        TEST_INT_EQ(0, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(1, upm2['1']);
        TEST_INT_EQ(0, upm2['2']);
        TEST_INT_EQ(0, upm2['3']);
    }

    {
        unicode_point_map upm1(0);
        unicode_point_map upm2(0x60);

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());

        upm1.swap(upm2);

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());
    }

    {
        unicode_point_map upm1(0);
        unicode_point_map upm2(0x60);

        upm1.push('A');
        upm1.push('a');
        upm1.push('1');

        upm2.push('B');
        upm2.push('b');
        upm2.push('2');
        upm2.push_n('3', 10);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(3u, upm1.size());
        TEST_INT_EQ(3, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(1, upm1['A']);
        TEST_INT_EQ(0, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(1, upm1['a']);
        TEST_INT_EQ(0, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(1, upm1['1']);
        TEST_INT_EQ(0, upm1['2']);
        TEST_INT_EQ(0, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(4u, upm2.size());
        TEST_INT_EQ(13, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(0, upm2['A']);
        TEST_INT_EQ(1, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(0, upm2['a']);
        TEST_INT_EQ(1, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(0, upm2['1']);
        TEST_INT_EQ(1, upm2['2']);
        TEST_INT_EQ(10, upm2['3']);

        upm1.swap(upm2);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(4u, upm1.size());
        TEST_INT_EQ(13, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(0, upm1['A']);
        TEST_INT_EQ(1, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(0, upm1['a']);
        TEST_INT_EQ(1, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(0, upm1['1']);
        TEST_INT_EQ(1, upm1['2']);
        TEST_INT_EQ(10, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(3u, upm2.size());
        TEST_INT_EQ(3, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(1, upm2['A']);
        TEST_INT_EQ(0, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(1, upm2['a']);
        TEST_INT_EQ(0, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(1, upm2['1']);
        TEST_INT_EQ(0, upm2['2']);
        TEST_INT_EQ(0, upm2['3']);
    }
}

static void test_swap_std()
{
    {
        unicode_point_map upm1;
        unicode_point_map upm2;

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());

        std::swap(upm1, upm2);

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());
    }

    {
        unicode_point_map upm1;
        unicode_point_map upm2;

        upm1.push('A');
        upm1.push('a');
        upm1.push('1');

        upm2.push('B');
        upm2.push('b');
        upm2.push('2');
        upm2.push_n('3', 10);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(3u, upm1.size());
        TEST_INT_EQ(3, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(1, upm1['A']);
        TEST_INT_EQ(0, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(1, upm1['a']);
        TEST_INT_EQ(0, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(1, upm1['1']);
        TEST_INT_EQ(0, upm1['2']);
        TEST_INT_EQ(0, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(4u, upm2.size());
        TEST_INT_EQ(13, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(0, upm2['A']);
        TEST_INT_EQ(1, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(0, upm2['a']);
        TEST_INT_EQ(1, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(0, upm2['1']);
        TEST_INT_EQ(1, upm2['2']);
        TEST_INT_EQ(10, upm2['3']);

        std::swap(upm1, upm2);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(4u, upm1.size());
        TEST_INT_EQ(13, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(0, upm1['A']);
        TEST_INT_EQ(1, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(0, upm1['a']);
        TEST_INT_EQ(1, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(0, upm1['1']);
        TEST_INT_EQ(1, upm1['2']);
        TEST_INT_EQ(10, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(3u, upm2.size());
        TEST_INT_EQ(3, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(1, upm2['A']);
        TEST_INT_EQ(0, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(1, upm2['a']);
        TEST_INT_EQ(0, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(1, upm2['1']);
        TEST_INT_EQ(0, upm2['2']);
        TEST_INT_EQ(0, upm2['3']);
    }

    {
        unicode_point_map upm1(0x60);
        unicode_point_map upm2(0x60);

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());

        std::swap(upm1, upm2);

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());
    }

    {
        unicode_point_map upm1(0x60);
        unicode_point_map upm2(0x60);

        upm1.push('A');
        upm1.push('a');
        upm1.push('1');

        upm2.push('B');
        upm2.push('b');
        upm2.push('2');
        upm2.push_n('3', 10);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(3u, upm1.size());
        TEST_INT_EQ(3, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(1, upm1['A']);
        TEST_INT_EQ(0, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(1, upm1['a']);
        TEST_INT_EQ(0, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(1, upm1['1']);
        TEST_INT_EQ(0, upm1['2']);
        TEST_INT_EQ(0, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(4u, upm2.size());
        TEST_INT_EQ(13, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(0, upm2['A']);
        TEST_INT_EQ(1, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(0, upm2['a']);
        TEST_INT_EQ(1, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(0, upm2['1']);
        TEST_INT_EQ(1, upm2['2']);
        TEST_INT_EQ(10, upm2['3']);

        std::swap(upm1, upm2);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(4u, upm1.size());
        TEST_INT_EQ(13, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(0, upm1['A']);
        TEST_INT_EQ(1, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(0, upm1['a']);
        TEST_INT_EQ(1, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(0, upm1['1']);
        TEST_INT_EQ(1, upm1['2']);
        TEST_INT_EQ(10, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(3u, upm2.size());
        TEST_INT_EQ(3, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(1, upm2['A']);
        TEST_INT_EQ(0, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(1, upm2['a']);
        TEST_INT_EQ(0, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(1, upm2['1']);
        TEST_INT_EQ(0, upm2['2']);
        TEST_INT_EQ(0, upm2['3']);
    }

    {
        unicode_point_map upm1(0);
        unicode_point_map upm2(0x60);

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());

        std::swap(upm1, upm2);

        TEST_BOOLEAN_TRUE(upm1.empty());
        TEST_INT_EQ(0u, upm1.size());
        TEST_INT_EQ(0, upm1.total());

        TEST_BOOLEAN_TRUE(upm2.empty());
        TEST_INT_EQ(0u, upm2.size());
        TEST_INT_EQ(0, upm2.total());
    }

    {
        unicode_point_map upm1(0);
        unicode_point_map upm2(0x60);

        upm1.push('A');
        upm1.push('a');
        upm1.push('1');

        upm2.push('B');
        upm2.push('b');
        upm2.push('2');
        upm2.push_n('3', 10);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(3u, upm1.size());
        TEST_INT_EQ(3, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(1, upm1['A']);
        TEST_INT_EQ(0, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(1, upm1['a']);
        TEST_INT_EQ(0, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(1, upm1['1']);
        TEST_INT_EQ(0, upm1['2']);
        TEST_INT_EQ(0, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(4u, upm2.size());
        TEST_INT_EQ(13, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(0, upm2['A']);
        TEST_INT_EQ(1, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(0, upm2['a']);
        TEST_INT_EQ(1, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(0, upm2['1']);
        TEST_INT_EQ(1, upm2['2']);
        TEST_INT_EQ(10, upm2['3']);

        std::swap(upm1, upm2);

        TEST_BOOLEAN_FALSE(upm1.empty());
        TEST_INT_EQ(4u, upm1.size());
        TEST_INT_EQ(13, upm1.total());

        TEST_INT_EQ(0, upm1[' ']);
        TEST_INT_EQ(0, upm1['A']);
        TEST_INT_EQ(1, upm1['B']);
        TEST_INT_EQ(0, upm1['C']);
        TEST_INT_EQ(0, upm1['a']);
        TEST_INT_EQ(1, upm1['b']);
        TEST_INT_EQ(0, upm1['c']);
        TEST_INT_EQ(0, upm1['0']);
        TEST_INT_EQ(0, upm1['1']);
        TEST_INT_EQ(1, upm1['2']);
        TEST_INT_EQ(10, upm1['3']);

        TEST_BOOLEAN_FALSE(upm2.empty());
        TEST_INT_EQ(3u, upm2.size());
        TEST_INT_EQ(3, upm2.total());

        TEST_INT_EQ(0, upm2[' ']);
        TEST_INT_EQ(1, upm2['A']);
        TEST_INT_EQ(0, upm2['B']);
        TEST_INT_EQ(0, upm2['C']);
        TEST_INT_EQ(1, upm2['a']);
        TEST_INT_EQ(0, upm2['b']);
        TEST_INT_EQ(0, upm2['c']);
        TEST_INT_EQ(0, upm2['0']);
        TEST_INT_EQ(1, upm2['1']);
        TEST_INT_EQ(0, upm2['2']);
        TEST_INT_EQ(0, upm2['3']);
    }
}

static void test_iteration_1()
{
    {
        unicode_point_map const upm;

        TEST(upm.end() == upm.begin());
        TEST(upm.cend() == upm.cbegin());
    }

    {
        unicode_point_map upm;

        upm.push_n('a', -97);

        TEST(upm.end() != upm.begin());
        TEST(upm.cend() != upm.cbegin());

        unicode_point_map::value_type const v = *upm.cbegin();

        TEST_INT_EQ(97u, v.first);
        TEST_INT_EQ(-97, v.second);
    }

    {
        unicode_point_map upm(1000); // set large ceiling to be assured of order

        upm.push_n('a', -97);
        upm.push_n('b', -98);
        upm.push_n('c', -99);

        TEST(upm.end() != upm.begin());
        TEST(upm.cend() != upm.cbegin());

        unicode_point_map::const_iterator i;

        i = upm.begin();

        {
            unicode_point_map::value_type const v = *i++;

            TEST_INT_EQ(97u, v.first);
            TEST_INT_EQ(-97, v.second);
        }

        {
            unicode_point_map::value_type const v = *i;

            TEST_INT_EQ(98u, v.first);
            TEST_INT_EQ(-98, v.second);

            ++i;
        }

        {
            unicode_point_map::value_type const v = *i++;

            TEST_INT_EQ(99u, v.first);
            TEST_INT_EQ(-99, v.second);
        }

        TEST(upm.end() == i);
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

