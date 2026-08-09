/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.containers.pod_vector/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::pod_vector`
 *
 * Created: 1st December 2008
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/containers/pod_vector.hpp>
// #include <stlsoft/container/pod_vector.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector> // for `std::begin()`, `std::end()`

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_default_ctor();
    static void test_ctor_size();
    static void test_ctor_size_and_value();
    static void test_ctor_begin_end();
    static void test_copy_ctor();
    static void test_copy_assign();

    static void test_assign();
    static void test_at_1();
    static void test_at_2();
    static void test_clear();
    static void test_erase();
    static void test_front_and_back();
    static void test_insert();
    static void test_pop_back();
    static void test_push_back();
    static void test_reserve();
    static void test_resize();
    static void test_subscript_operator();
    static void test_swap();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.containers.pod_vector", verbosity))
    {
        XTESTS_RUN_CASE(test_default_ctor);
        XTESTS_RUN_CASE(test_ctor_size);
        XTESTS_RUN_CASE(test_ctor_size_and_value);
        XTESTS_RUN_CASE(test_ctor_begin_end);
        XTESTS_RUN_CASE(test_copy_ctor);
        XTESTS_RUN_CASE(test_copy_assign);

        XTESTS_RUN_CASE(test_assign);
        XTESTS_RUN_CASE(test_at_1);
        XTESTS_RUN_CASE_THAT_THROWS(test_at_2, std::out_of_range);
        XTESTS_RUN_CASE(test_clear);
        XTESTS_RUN_CASE(test_erase);
        XTESTS_RUN_CASE(test_front_and_back);
        XTESTS_RUN_CASE(test_insert);
        XTESTS_RUN_CASE(test_pop_back);
        XTESTS_RUN_CASE(test_push_back);
        XTESTS_RUN_CASE(test_reserve);
        XTESTS_RUN_CASE(test_resize);
        XTESTS_RUN_CASE(test_subscript_operator);
        XTESTS_RUN_CASE(test_swap);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    typedef stlsoft::pod_vector<int>    int_vector_t;

static void test_default_ctor()
{
    int_vector_t        v;
    int_vector_t const& cv = v;

    TEST_INT_EQ(0u, v.size());
    TEST_BOOLEAN_TRUE(v.empty());
    TEST_INT_EQ(0, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(0, std::accumulate(cv.begin(), cv.end(), 0));
#ifdef STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT
    TEST_INT_EQ(0, std::accumulate(v.rbegin(), v.rend(), 0));
    TEST_INT_EQ(0, std::accumulate(cv.rbegin(), cv.rend(), 0));
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */
    TEST_INT_GE(v.size(), v.capacity());
}

static void test_ctor_size()
{
    int_vector_t        v(10);
    int_vector_t const& cv = v;

    TEST_INT_EQ(10u, v.size());
    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(0, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(0, std::accumulate(cv.begin(), cv.end(), 0));
#ifdef STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT
    TEST_INT_EQ(0, std::accumulate(v.rbegin(), v.rend(), 0));
    TEST_INT_EQ(0, std::accumulate(cv.rbegin(), cv.rend(), 0));
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */
    TEST_INT_GE(v.size(), v.capacity());
}

static void test_ctor_size_and_value()
{
    int_vector_t        v(10, -1);
    int_vector_t const& cv = v;

    TEST_INT_EQ(10u, v.size());
    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(-10, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(-10, std::accumulate(cv.begin(), cv.end(), 0));
#ifdef STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT
    TEST_INT_EQ(-10, std::accumulate(v.rbegin(), v.rend(), 0));
    TEST_INT_EQ(-10, std::accumulate(cv.rbegin(), cv.rend(), 0));
#endif /* STLSOFT_LF_BIDIRECTIONAL_ITERATOR_SUPPORT */
    TEST_INT_GE(v.size(), v.capacity());
}

static void test_ctor_begin_end()
{
    int const           ints[] = { -4, -3, -2, -1, 0, 1, 2, 3, 4 };
    int_vector_t const  v(ints, ints + STLSOFT_NUM_ELEMENTS(ints));

    TEST_INT_EQ(9u, v.size());
    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(0, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_GE(v.size(), v.capacity());
}

static void test_copy_ctor()
{
    int_vector_t    v1(10, -1);
    int_vector_t    v2(v1);

    TEST_INT_EQ(10u, v2.size());
    TEST_BOOLEAN_FALSE(v2.empty());
    TEST_INT_EQ(-10, std::accumulate(v2.begin(), v2.end(), 0));
    TEST_INT_GE(v2.size(), v2.capacity());
}

static void test_copy_assign()
{
    int_vector_t    v1(10, -1);
    int_vector_t    v2;

    v2 = v1;

    TEST_INT_EQ(10u, v2.size());
    TEST_BOOLEAN_FALSE(v2.empty());
    TEST_INT_EQ(-10, std::accumulate(v2.begin(), v2.end(), 0));
    TEST_INT_GE(v2.size(), v2.capacity());
}

static void test_assign()
{
    int const ints[] = { -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 };

    int_vector_t v;

    v.assign(0, -1);

    TEST_BOOLEAN_TRUE(v.empty());
    TEST_INT_EQ(0u, v.size());
    TEST_INT_EQ(0, std::accumulate(v.begin(), v.end(), 0));

    v.assign(7, -1);

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(7u, v.size());
    TEST_INT_EQ(-7, std::accumulate(v.begin(), v.end(), 0));

#if __cplusplus >= 201103L

    v.assign(std::begin(ints), std::end(ints));
#else

    v.assign(&ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints));
#endif

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(10u, v.size());
    TEST_INT_EQ(5, std::accumulate(v.begin(), v.end(), 0));
}

static void test_at_1()
{
    int const           ints[] = { -4, -3, -2, -1, 0, 1, 2, 3, 4 };
    int_vector_t        v(ints, ints + STLSOFT_NUM_ELEMENTS(ints));
    int_vector_t const& cv = v;

    TEST_INT_EQ(9u, v.size());

    TEST_INT_EQ(-4, v.at(0));
    TEST_INT_EQ(-2, v.at(2));
    TEST_INT_EQ( 0, v.at(4));
    TEST_INT_EQ(+2, v.at(6));
    TEST_INT_EQ(+4, v.at(8));

    TEST_INT_EQ(-4, cv.at(0));
    TEST_INT_EQ(-2, cv.at(2));
    TEST_INT_EQ( 0, cv.at(4));
    TEST_INT_EQ(+2, cv.at(6));
    TEST_INT_EQ(+4, cv.at(8));
}

static void test_at_2()
{
    int const           ints[] = { -4, -3, -2, -1, 0, 1, 2, 3, 4 };
    int_vector_t const  v(ints, ints + STLSOFT_NUM_ELEMENTS(ints));

    TEST_INT_EQ(9u, v.size());

    v.at(9);

    TEST_FAIL("should not get here");
}

static void test_clear()
{
    int_vector_t v(10, -1);

    v.clear();

    TEST_INT_EQ(0u, v.size());
    TEST_BOOLEAN_TRUE(v.empty());
    TEST_INT_GE(v.size(), v.capacity());
}

static void test_erase()
{
    int const ints[] = { -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 };


    // { -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 }

#if __cplusplus >= 201103L

    int_vector_t v(std::begin(ints), std::end(ints));
#else

    int_vector_t v(&ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints));
#endif

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(10u, v.size());
    TEST_INT_EQ(5, std::accumulate(v.begin(), v.end(), 0));


    // { -4, -3, -2, -1, 0, 1, 2, 3, 5 }

    v.erase(v.begin() + 8);

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(9u, v.size());
    TEST_INT_EQ(+1, std::accumulate(v.begin(), v.end(), 0));


    // { -4, 0, 1, 2, 3, 5 }

    v.erase(v.begin() + 1, v.begin() + 4);

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(6u, v.size());
    TEST_INT_EQ(+7, std::accumulate(v.begin(), v.end(), 0));


    // { -4, 0, 1, 2, 3, 5 }

    v.erase(v.end(), v.end());

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(6u, v.size());
    TEST_INT_EQ(+7, std::accumulate(v.begin(), v.end(), 0));


    // { -4, 0, 1, 2, 3 }

    v.erase(v.begin() + 5, v.end());

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(5u, v.size());
    TEST_INT_EQ(+2, std::accumulate(v.begin(), v.end(), 0));


    // { 1, 2, 3 }

    v.erase(v.begin(), v.begin() + 2);

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(3u, v.size());
    TEST_INT_EQ(+6, std::accumulate(v.begin(), v.end(), 0));


    // { }

    v.erase(v.begin(), v.end());

    TEST_BOOLEAN_TRUE(v.empty());
    TEST_INT_EQ(0u, v.size());
    TEST_INT_EQ(0, std::accumulate(v.begin(), v.end(), 0));
}

static void test_front_and_back()
{
    int const           ints[] = { -4, -3, -2, -1, 0, 1, 2, 3, 4 };
    int_vector_t        v(ints, ints + STLSOFT_NUM_ELEMENTS(ints));
    int_vector_t const& cv = v;

    TEST_INT_EQ(9u, v.size());

    TEST_INT_EQ(-4, v.front());
    TEST_INT_EQ(+4, v.back());

    TEST_INT_EQ(-4, cv.front());
    TEST_INT_EQ(+4, cv.back());
}

static void test_insert()
{
    int const ints_neg8_to_neg5[] = { -8, -7, -6, -5 };
    int const ints_neg3_to_neg1[] = { -3, -2, -1 };


    // { }

    int_vector_t    v;

    TEST_INT_EQ(0u, v.size());
    TEST_BOOLEAN_TRUE(v.empty());
    TEST_INT_EQ(0, std::accumulate(v.begin(), v.end(), 0));


    // { 1 }

    v.insert(v.end(), 1);

    TEST_INT_EQ(1u, v.size());
    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(1, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(1, v[0]);


    // { 1, 2 }

    v.insert(v.end(), 2);

    TEST_INT_EQ(2u, v.size());
    TEST_INT_EQ(3, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(1, v[0]);
    TEST_INT_EQ(2, v[1]);


    // { 0, 1, 2 }

    v.insert(v.begin(), 0);

    TEST_INT_EQ(3u, v.size());
    TEST_INT_EQ(3, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(0, v[0]);
    TEST_INT_EQ(1, v[1]);
    TEST_INT_EQ(2, v[2]);


    // { -8, -7, -6, -5, 0, 1, 2 }

#if __cplusplus >= 201103L

    v.insert(v.begin(), std::begin(ints_neg8_to_neg5), std::end(ints_neg8_to_neg5));
#else

    v.insert(v.begin(), &ints_neg8_to_neg5[0], &ints_neg8_to_neg5[0] + STLSOFT_NUM_ELEMENTS(ints_neg8_to_neg5));
#endif


    TEST_INT_EQ(7u, v.size());
    TEST_INT_EQ(-23, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(0, v[4]);
    TEST_INT_EQ(1, v[5]);
    TEST_INT_EQ(2, v[6]);


    // { -8, -7, -6, -5, -4, 0, 1, 2 }

    v.insert(v.begin() + 4, -4);

    TEST_INT_EQ(8u, v.size());
    TEST_INT_EQ(-27, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(0, v[5]);
    TEST_INT_EQ(1, v[6]);
    TEST_INT_EQ(2, v[7]);


    // { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2 }

#if __cplusplus >= 201103L

    v.insert(v.begin() + 5, std::begin(ints_neg3_to_neg1), std::end(ints_neg3_to_neg1));
#else

    v.insert(v.begin() + 5, &ints_neg3_to_neg1[0], &ints_neg3_to_neg1[0] + STLSOFT_NUM_ELEMENTS(ints_neg3_to_neg1));
#endif


    TEST_INT_EQ(11u, v.size());
    TEST_INT_EQ(-33, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(0, v[8]);
    TEST_INT_EQ(1, v[9]);
    TEST_INT_EQ(2, v[10]);


    // { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 4 }

    v.insert(v.begin() + 11, 1, 4);

    TEST_INT_EQ(12u, v.size());
    TEST_INT_EQ(-29, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(0, v[8]);
    TEST_INT_EQ(1, v[9]);
    TEST_INT_EQ(2, v[10]);


    // { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 3, 3, 4 }

    v.insert(v.begin() + 11, 4, 3);

    TEST_INT_EQ(16u, v.size());
    TEST_INT_EQ(-17, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(0, v[8]);
    TEST_INT_EQ(1, v[9]);
    TEST_INT_EQ(2, v[10]);
    TEST_INT_EQ(3, v[11]);
    TEST_INT_EQ(3, v[12]);
    TEST_INT_EQ(3, v[13]);
    TEST_INT_EQ(3, v[14]);
    TEST_INT_EQ(4, v[15]);
}

static void test_pop_back()
{
    int_vector_t v(10, 1);

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(10u, v.size());
    TEST_INT_EQ(10, std::accumulate(v.begin(), v.end(), 0));

    v.pop_back();

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(9u, v.size());
    TEST_INT_EQ(9, std::accumulate(v.begin(), v.end(), 0));

    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();
    v.pop_back();

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(1u, v.size());
    TEST_INT_EQ(1, std::accumulate(v.begin(), v.end(), 0));

    v.pop_back();

    TEST_BOOLEAN_TRUE(v.empty());
    TEST_INT_EQ(0u, v.size());
    TEST_INT_EQ(0, std::accumulate(v.begin(), v.end(), 0));
}

static void test_push_back()
{
    int_vector_t v;

    TEST_BOOLEAN_TRUE(v.empty());
    TEST_INT_EQ(0u, v.size());
    TEST_INT_EQ(0, std::accumulate(v.begin(), v.end(), 0));

    v.push_back(1);

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(1u, v.size());
    TEST_INT_EQ(1, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(1, v[0]);

    v.push_back(2);

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(2u, v.size());
    TEST_INT_EQ(3, std::accumulate(v.begin(), v.end(), 0));
    TEST_INT_EQ(1, v[0]);
    TEST_INT_EQ(2, v[1]);
}

static void test_reserve()
{
    int_vector_t v;

    TEST_BOOLEAN_TRUE(v.empty());
    TEST_INT_GE(0u, v.capacity());
    TEST_INT_LE(1024u, v.capacity());

    v.reserve(250);

    TEST_BOOLEAN_TRUE(v.empty());
    TEST_INT_GE(250u, v.capacity());
}

static void test_resize()
{
    int_vector_t v;

    TEST_BOOLEAN_TRUE(v.empty());
    TEST_INT_EQ(0u, v.size());
    TEST_INT_GE(0u, v.capacity());
    TEST_INT_EQ(0, std::accumulate(v.begin(), v.end(), 0));

    v.resize(10);

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(10u, v.size());
    TEST_INT_GE(10u, v.capacity());
    TEST_INT_EQ(0, std::accumulate(v.begin(), v.end(), 0));

    v.resize(12, 2);

    TEST_BOOLEAN_FALSE(v.empty());
    TEST_INT_EQ(12u, v.size());
    TEST_INT_GE(12u, v.capacity());
    TEST_INT_EQ(4, std::accumulate(v.begin(), v.end(), 0));
}

static void test_subscript_operator()
{
    int const           ints[] = { -4, -3, -2, -1, 0, 1, 2, 3, 4 };
    int_vector_t        v(ints, ints + STLSOFT_NUM_ELEMENTS(ints));
    int_vector_t const& cv = v;

    TEST_INT_EQ(9u, v.size());

    TEST_INT_EQ(-4, v[0]);
    TEST_INT_EQ(-2, v[2]);
    TEST_INT_EQ( 0, v[4]);
    TEST_INT_EQ(+2, v[6]);
    TEST_INT_EQ(+4, v[8]);

    TEST_INT_EQ(-4, cv[0]);
    TEST_INT_EQ(-2, cv[2]);
    TEST_INT_EQ( 0, cv[4]);
    TEST_INT_EQ(+2, cv[6]);
    TEST_INT_EQ(+4, cv[8]);
}

static void test_swap()
{
    int_vector_t    v1(10, -1);
    int_vector_t    v2;

    v1.swap(v2);

    TEST_INT_EQ(0u, v1.size());
    TEST_BOOLEAN_TRUE(v1.empty());
    TEST_INT_EQ(0, std::accumulate(v1.begin(), v1.end(), 0));

    TEST_INT_EQ(10u, v2.size());
    TEST_BOOLEAN_FALSE(v2.empty());
    TEST_INT_EQ(-10, std::accumulate(v2.begin(), v2.end(), 0));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

