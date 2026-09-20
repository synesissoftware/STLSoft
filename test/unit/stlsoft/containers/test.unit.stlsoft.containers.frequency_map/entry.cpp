/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.containers.frequency_map/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::frequency_map`.
 *
 * Created: 12th February 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* ///////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/containers/frequency_map.hpp>


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
#include <string>
#if __cplusplus >= 201103L
# include <type_traits>
#endif
#include <vector>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_ctor_default();
#if __cplusplus >= 201103L

    static void test_ctor_initializer_list_1();
    static void test_ctor_initializer_list_2();
#endif
    static void test_ctor_range_pointers_1();
#if __cplusplus >= 201103L

    static void test_ctor_range_list_iters_1();
#endif
    static void test_clear();
    static void test_merge();
    static void test_op_addassign();
    static void test_op_add();
    static void test_push();
    static void test_swap();
    static void test_swap_std();
    static void test_iteration_order_1();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.containers.frequency_map", verbosity))
    {
        XTESTS_RUN_CASE(test_ctor_default);
#if __cplusplus >= 201103L

        XTESTS_RUN_CASE(test_ctor_initializer_list_1);
        XTESTS_RUN_CASE(test_ctor_initializer_list_2);
#endif
        XTESTS_RUN_CASE(test_ctor_range_pointers_1);
#if __cplusplus >= 201103L

        XTESTS_RUN_CASE(test_ctor_range_list_iters_1);
#endif
        XTESTS_RUN_CASE(test_clear);
        XTESTS_RUN_CASE(test_merge);
        XTESTS_RUN_CASE(test_op_addassign);
        XTESTS_RUN_CASE(test_op_add);
        XTESTS_RUN_CASE(test_push);
        XTESTS_RUN_CASE(test_swap);
        XTESTS_RUN_CASE(test_swap_std);
        XTESTS_RUN_CASE(test_iteration_order_1);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * utility functions
 */

namespace {

    template<
        ss_typename_param_k C
    ,   ss_typename_param_k F
    >
    C
    to_ordered(
        C const&    c
    ,   F           f
    )
    {
        C r(c);

        std::sort(r.begin(), r.end(), f);

        return r;
    }
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::ss_uintptr_t;

    typedef stlsoft::frequency_map<
        int
    ,   stlsoft::frequency_map_traits_ordered<int>
    >                                                       fm_ordered_int_t;
#if __cplusplus >= 201103L

    typedef stlsoft::frequency_map<
        int
    ,   stlsoft::frequency_map_traits_unordered<int>
    >                                                       fm_unordered_int_t;
#endif /* C++ */
    typedef std::pair<
        int
    ,   ss_uintptr_t
    >                                                       pair_t;
    typedef std::vector<pair_t>                             pairs_t;

    struct compare_value_type
    {
    public:
        bool operator ()(
            pair_t const&   lhs
        ,   pair_t const&   rhs
        ) const
        {
            if (lhs.first < rhs.first)
            {
                return true;
            }

            if (rhs.first < lhs.first)
            {
                return false;
            }

            if (lhs.second < rhs.second)
            {
                return true;
            }

            if (rhs.second < lhs.second)
            {
                return false;
            }

            return false;
        }
    };

#if __cplusplus >= 201103L

    template <
        typename I
    ,   typename V = typename std::remove_const<typename std::iterator_traits<I>::value_type::first_type>::type
    >
    inline
    std::vector<std::pair<V, std::uint32_t>>
    fmi_to_list(
        I   from
    ,   I   to
    )
    {
        std::vector<std::pair<V, std::uint32_t>> v;

        v.reserve(std::distance(from, to));

        for (I i = from; to != i; ++i)
        {
            v.push_back(std::make_pair((*i).first, static_cast<std::uint32_t>((*i).second)));
        }

        std::sort(v.begin(), v.end());

        return v;
    }

    template <
        typename T_value
    ,   typename T_traits
    >
    inline
    std::vector<std::pair<T_value, std::uint32_t>>
    fm_to_list(
        stlsoft::frequency_map<T_value, T_traits> const& fm
    )
    {
        std::vector<std::pair<T_value, std::uint32_t>> v;

        v.reserve(fm.size());

        for (typename stlsoft::frequency_map<T_value, T_traits>::const_iterator i = fm.begin(); fm.end() != i; ++i)
        {
            v.push_back(std::make_pair((*i).first, static_cast<std::uint32_t>((*i).second)));
        }

        std::sort(v.begin(), v.end());

        return v;
    }
#endif /* C++ */



static void test_ctor_default()
{
    {
        fm_ordered_int_t fm;

        TEST_BOOLEAN_TRUE(fm.empty());
        TEST_INT_EQ(0u, fm.size());
        TEST_INT_EQ(0u, fm.total());

        TEST_INT_EQ(0u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(0u, fm.count(1));
        TEST_INT_EQ(0u, fm.count(2));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(0u, fm[1]);
        TEST_INT_EQ(0u, fm[2]);
        TEST_INT_EQ(0u, fm[-2]);
    }

#if __cplusplus >= 201103L

    {
        fm_unordered_int_t fm;

        TEST_BOOLEAN_TRUE(fm.empty());
        TEST_INT_EQ(0u, fm.size());
        TEST_INT_EQ(0u, fm.total());

        TEST_INT_EQ(0u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(0u, fm.count(1));
        TEST_INT_EQ(0u, fm.count(2));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(0u, fm[1]);
        TEST_INT_EQ(0u, fm[2]);
        TEST_INT_EQ(0u, fm[-2]);
    }
#endif
}

#if __cplusplus >= 201103L

static void test_ctor_initializer_list_1()
{
    {
        fm_ordered_int_t fm = {};

        TEST_BOOLEAN_TRUE(fm.empty());
        TEST_INT_EQ(0u, fm.size());
        TEST_INT_EQ(0u, fm.total());

        TEST_BOOLEAN_FALSE(fm.contains(-1));
        TEST_BOOLEAN_FALSE(fm.contains(0));
        TEST_BOOLEAN_FALSE(fm.contains(1));
        TEST_BOOLEAN_FALSE(fm.contains(2));
        TEST_BOOLEAN_FALSE(fm.contains(3));
        TEST_BOOLEAN_FALSE(fm.contains(4));
        TEST_BOOLEAN_FALSE(fm.contains(5));
        TEST_BOOLEAN_FALSE(fm.contains(6));
        TEST_BOOLEAN_FALSE(fm.contains(7));
        TEST_BOOLEAN_FALSE(fm.contains(8));
        TEST_BOOLEAN_FALSE(fm.contains(9));
        TEST_BOOLEAN_FALSE(fm.contains(10));
        TEST_BOOLEAN_FALSE(fm.contains(11));
        TEST_BOOLEAN_FALSE(fm.contains(12));
        TEST_BOOLEAN_FALSE(fm.contains(13));
        TEST_BOOLEAN_FALSE(fm.contains(14));
        TEST_BOOLEAN_FALSE(fm.contains(15));
        TEST_BOOLEAN_FALSE(fm.contains(16));
        TEST_BOOLEAN_FALSE(fm.contains(17));
        TEST_BOOLEAN_FALSE(fm.contains(18));
        TEST_BOOLEAN_FALSE(fm.contains(19));
        TEST_BOOLEAN_FALSE(fm.contains(20));
        TEST_BOOLEAN_FALSE(fm.contains(21));

        TEST_INT_EQ(0u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(0u, fm.count(1));
        TEST_INT_EQ(0u, fm.count(2));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(0u, fm[1]);
        TEST_INT_EQ(0u, fm[2]);
        TEST_INT_EQ(0u, fm[-2]);
    }

    {
        fm_ordered_int_t fm = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, };

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(20u, fm.size());
        TEST_INT_EQ(20u, fm.total());

        TEST_BOOLEAN_FALSE(fm.contains(-1));
        TEST_BOOLEAN_TRUE(fm.contains(0));
        TEST_BOOLEAN_TRUE(fm.contains(1));
        TEST_BOOLEAN_TRUE(fm.contains(2));
        TEST_BOOLEAN_TRUE(fm.contains(3));
        TEST_BOOLEAN_TRUE(fm.contains(4));
        TEST_BOOLEAN_TRUE(fm.contains(5));
        TEST_BOOLEAN_TRUE(fm.contains(6));
        TEST_BOOLEAN_TRUE(fm.contains(7));
        TEST_BOOLEAN_TRUE(fm.contains(8));
        TEST_BOOLEAN_TRUE(fm.contains(9));
        TEST_BOOLEAN_TRUE(fm.contains(10));
        TEST_BOOLEAN_TRUE(fm.contains(11));
        TEST_BOOLEAN_TRUE(fm.contains(12));
        TEST_BOOLEAN_TRUE(fm.contains(13));
        TEST_BOOLEAN_TRUE(fm.contains(14));
        TEST_BOOLEAN_TRUE(fm.contains(15));
        TEST_BOOLEAN_TRUE(fm.contains(16));
        TEST_BOOLEAN_TRUE(fm.contains(17));
        TEST_BOOLEAN_TRUE(fm.contains(18));
        TEST_BOOLEAN_TRUE(fm.contains(19));
        TEST_BOOLEAN_FALSE(fm.contains(20));
        TEST_BOOLEAN_FALSE(fm.contains(21));

        TEST_INT_EQ(1u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(1u, fm.count(1));
        TEST_INT_EQ(1u, fm.count(2));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(1u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(1u, fm[1]);
        TEST_INT_EQ(1u, fm[2]);
        TEST_INT_EQ(0u, fm[-2]);
    }

    {
        fm_ordered_int_t fm = { 2, 2 };

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(1u, fm.size());
        TEST_INT_EQ(2u, fm.total());

        TEST_BOOLEAN_FALSE(fm.contains(-1));
        TEST_BOOLEAN_FALSE(fm.contains(0));
        TEST_BOOLEAN_FALSE(fm.contains(1));
        TEST_BOOLEAN_TRUE(fm.contains(2));
        TEST_BOOLEAN_FALSE(fm.contains(3));
        TEST_BOOLEAN_FALSE(fm.contains(4));
        TEST_BOOLEAN_FALSE(fm.contains(5));
        TEST_BOOLEAN_FALSE(fm.contains(6));
        TEST_BOOLEAN_FALSE(fm.contains(7));
        TEST_BOOLEAN_FALSE(fm.contains(8));
        TEST_BOOLEAN_FALSE(fm.contains(9));
        TEST_BOOLEAN_FALSE(fm.contains(10));
        TEST_BOOLEAN_FALSE(fm.contains(11));
        TEST_BOOLEAN_FALSE(fm.contains(12));
        TEST_BOOLEAN_FALSE(fm.contains(13));
        TEST_BOOLEAN_FALSE(fm.contains(14));
        TEST_BOOLEAN_FALSE(fm.contains(15));
        TEST_BOOLEAN_FALSE(fm.contains(16));
        TEST_BOOLEAN_FALSE(fm.contains(17));
        TEST_BOOLEAN_FALSE(fm.contains(18));
        TEST_BOOLEAN_FALSE(fm.contains(19));
        TEST_BOOLEAN_FALSE(fm.contains(20));
        TEST_BOOLEAN_FALSE(fm.contains(21));

        TEST_INT_EQ(0u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(0u, fm.count(1));
        TEST_INT_EQ(2u, fm.count(2));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(0u, fm[1]);
        TEST_INT_EQ(2u, fm[2]);
        TEST_INT_EQ(0u, fm[-2]);
    }
}

static void test_ctor_initializer_list_2()
{
    {
        fm_ordered_int_t fm = { { 2, 2 }, { 3, 1 } };

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(2u, fm.size());
        TEST_INT_EQ(3u, fm.total());

        TEST_BOOLEAN_FALSE(fm.contains(-1));
        TEST_BOOLEAN_FALSE(fm.contains(0));
        TEST_BOOLEAN_FALSE(fm.contains(1));
        TEST_BOOLEAN_TRUE(fm.contains(2));
        TEST_BOOLEAN_TRUE(fm.contains(3));
        TEST_BOOLEAN_FALSE(fm.contains(4));
        TEST_BOOLEAN_FALSE(fm.contains(5));
        TEST_BOOLEAN_FALSE(fm.contains(6));
        TEST_BOOLEAN_FALSE(fm.contains(7));
        TEST_BOOLEAN_FALSE(fm.contains(8));
        TEST_BOOLEAN_FALSE(fm.contains(9));
        TEST_BOOLEAN_FALSE(fm.contains(10));
        TEST_BOOLEAN_FALSE(fm.contains(11));
        TEST_BOOLEAN_FALSE(fm.contains(12));
        TEST_BOOLEAN_FALSE(fm.contains(13));
        TEST_BOOLEAN_FALSE(fm.contains(14));
        TEST_BOOLEAN_FALSE(fm.contains(15));
        TEST_BOOLEAN_FALSE(fm.contains(16));
        TEST_BOOLEAN_FALSE(fm.contains(17));
        TEST_BOOLEAN_FALSE(fm.contains(18));
        TEST_BOOLEAN_FALSE(fm.contains(19));
        TEST_BOOLEAN_FALSE(fm.contains(20));
        TEST_BOOLEAN_FALSE(fm.contains(21));

        TEST_INT_EQ(0u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(0u, fm.count(1));
        TEST_INT_EQ(2u, fm.count(2));
        TEST_INT_EQ(1u, fm.count(3));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(0u, fm[1]);
        TEST_INT_EQ(2u, fm[2]);
        TEST_INT_EQ(1u, fm[3]);
        TEST_INT_EQ(0u, fm[-2]);
    }

    {
        fm_ordered_int_t fm = { { 1, 1 }, { 2, 1 }, { 3, 3 }, { 4, 4 } };

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(4u, fm.size());
        TEST_INT_EQ(9u, fm.total());

        TEST_BOOLEAN_FALSE(fm.contains(-1));
        TEST_BOOLEAN_FALSE(fm.contains(0));
        TEST_BOOLEAN_TRUE(fm.contains(1));
        TEST_BOOLEAN_TRUE(fm.contains(2));
        TEST_BOOLEAN_TRUE(fm.contains(3));
        TEST_BOOLEAN_TRUE(fm.contains(4));
        TEST_BOOLEAN_FALSE(fm.contains(5));
        TEST_BOOLEAN_FALSE(fm.contains(6));
        TEST_BOOLEAN_FALSE(fm.contains(7));
        TEST_BOOLEAN_FALSE(fm.contains(8));
        TEST_BOOLEAN_FALSE(fm.contains(9));
        TEST_BOOLEAN_FALSE(fm.contains(10));
        TEST_BOOLEAN_FALSE(fm.contains(11));
        TEST_BOOLEAN_FALSE(fm.contains(12));
        TEST_BOOLEAN_FALSE(fm.contains(13));
        TEST_BOOLEAN_FALSE(fm.contains(14));
        TEST_BOOLEAN_FALSE(fm.contains(15));
        TEST_BOOLEAN_FALSE(fm.contains(16));
        TEST_BOOLEAN_FALSE(fm.contains(17));
        TEST_BOOLEAN_FALSE(fm.contains(18));
        TEST_BOOLEAN_FALSE(fm.contains(19));
        TEST_BOOLEAN_FALSE(fm.contains(20));
        TEST_BOOLEAN_FALSE(fm.contains(21));

        TEST_INT_EQ(0u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(1u, fm.count(1));
        TEST_INT_EQ(1u, fm.count(2));
        TEST_INT_EQ(3u, fm.count(3));
        TEST_INT_EQ(4u, fm.count(4));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(1u, fm[1]);
        TEST_INT_EQ(1u, fm[2]);
        TEST_INT_EQ(3u, fm[3]);
        TEST_INT_EQ(4u, fm[4]);
        TEST_INT_EQ(0u, fm[-2]);
    }
}
#endif

static void test_ctor_range_pointers_1()
{
    const int VALUES[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, };

    {
#if __cplusplus >= 201103L

        fm_ordered_int_t fm = { std::begin(VALUES), std::end(VALUES) };
#else

        fm_ordered_int_t fm(&VALUES[0] + 0, &VALUES[0] + STLSOFT_NUM_ELEMENTS(VALUES));
#endif

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(20u, fm.size());
        TEST_INT_EQ(20u, fm.total());

        TEST_BOOLEAN_FALSE(fm.contains(-1));
        TEST_BOOLEAN_TRUE(fm.contains(0));
        TEST_BOOLEAN_TRUE(fm.contains(1));
        TEST_BOOLEAN_TRUE(fm.contains(2));
        TEST_BOOLEAN_TRUE(fm.contains(3));
        TEST_BOOLEAN_TRUE(fm.contains(4));
        TEST_BOOLEAN_TRUE(fm.contains(5));
        TEST_BOOLEAN_TRUE(fm.contains(6));
        TEST_BOOLEAN_TRUE(fm.contains(7));
        TEST_BOOLEAN_TRUE(fm.contains(8));
        TEST_BOOLEAN_TRUE(fm.contains(9));
        TEST_BOOLEAN_TRUE(fm.contains(10));
        TEST_BOOLEAN_TRUE(fm.contains(11));
        TEST_BOOLEAN_TRUE(fm.contains(12));
        TEST_BOOLEAN_TRUE(fm.contains(13));
        TEST_BOOLEAN_TRUE(fm.contains(14));
        TEST_BOOLEAN_TRUE(fm.contains(15));
        TEST_BOOLEAN_TRUE(fm.contains(16));
        TEST_BOOLEAN_TRUE(fm.contains(17));
        TEST_BOOLEAN_TRUE(fm.contains(18));
        TEST_BOOLEAN_TRUE(fm.contains(19));
        TEST_BOOLEAN_FALSE(fm.contains(20));
        TEST_BOOLEAN_FALSE(fm.contains(21));

        TEST_INT_EQ(1u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(1u, fm.count(1));
        TEST_INT_EQ(1u, fm.count(2));
        TEST_INT_EQ(1u, fm.count(3));
        TEST_INT_EQ(1u, fm.count(4));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[-1]);
        TEST_INT_EQ(1u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(1u, fm[1]);
        TEST_INT_EQ(1u, fm[2]);
        TEST_INT_EQ(1u, fm[3]);
        TEST_INT_EQ(1u, fm[4]);
        TEST_INT_EQ(0u, fm[-2]);
    }

#if __cplusplus >= 201103L

    {
        fm_unordered_int_t fm = { std::begin(VALUES), std::end(VALUES) };

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(20u, fm.size());
        TEST_INT_EQ(20u, fm.total());

        TEST_BOOLEAN_FALSE(fm.contains(-1));
        TEST_BOOLEAN_TRUE(fm.contains(0));
        TEST_BOOLEAN_TRUE(fm.contains(1));
        TEST_BOOLEAN_TRUE(fm.contains(2));
        TEST_BOOLEAN_TRUE(fm.contains(3));
        TEST_BOOLEAN_TRUE(fm.contains(4));
        TEST_BOOLEAN_TRUE(fm.contains(5));
        TEST_BOOLEAN_TRUE(fm.contains(6));
        TEST_BOOLEAN_TRUE(fm.contains(7));
        TEST_BOOLEAN_TRUE(fm.contains(8));
        TEST_BOOLEAN_TRUE(fm.contains(9));
        TEST_BOOLEAN_TRUE(fm.contains(10));
        TEST_BOOLEAN_TRUE(fm.contains(11));
        TEST_BOOLEAN_TRUE(fm.contains(12));
        TEST_BOOLEAN_TRUE(fm.contains(13));
        TEST_BOOLEAN_TRUE(fm.contains(14));
        TEST_BOOLEAN_TRUE(fm.contains(15));
        TEST_BOOLEAN_TRUE(fm.contains(16));
        TEST_BOOLEAN_TRUE(fm.contains(17));
        TEST_BOOLEAN_TRUE(fm.contains(18));
        TEST_BOOLEAN_TRUE(fm.contains(19));
        TEST_BOOLEAN_FALSE(fm.contains(20));
        TEST_BOOLEAN_FALSE(fm.contains(21));

        TEST_INT_EQ(1u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(1u, fm.count(1));
        TEST_INT_EQ(1u, fm.count(2));
        TEST_INT_EQ(1u, fm.count(3));
        TEST_INT_EQ(1u, fm.count(4));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[-1]);
        TEST_INT_EQ(1u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(1u, fm[1]);
        TEST_INT_EQ(1u, fm[2]);
        TEST_INT_EQ(1u, fm[3]);
        TEST_INT_EQ(1u, fm[4]);
        TEST_INT_EQ(0u, fm[-2]);
    }
#endif
}

#if __cplusplus >= 201103L

static void test_ctor_range_list_iters_1()
{
    std::list<int> VALUES = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, };

    {
        fm_ordered_int_t fm(VALUES.begin(), VALUES.end());

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(20u, fm.size());
        TEST_INT_EQ(20u, fm.total());

        TEST_BOOLEAN_FALSE(fm.contains(-1));
        TEST_BOOLEAN_TRUE(fm.contains(0));
        TEST_BOOLEAN_TRUE(fm.contains(1));
        TEST_BOOLEAN_TRUE(fm.contains(2));
        TEST_BOOLEAN_TRUE(fm.contains(3));
        TEST_BOOLEAN_TRUE(fm.contains(4));
        TEST_BOOLEAN_TRUE(fm.contains(5));
        TEST_BOOLEAN_TRUE(fm.contains(6));
        TEST_BOOLEAN_TRUE(fm.contains(7));
        TEST_BOOLEAN_TRUE(fm.contains(8));
        TEST_BOOLEAN_TRUE(fm.contains(9));
        TEST_BOOLEAN_TRUE(fm.contains(10));
        TEST_BOOLEAN_TRUE(fm.contains(11));
        TEST_BOOLEAN_TRUE(fm.contains(12));
        TEST_BOOLEAN_TRUE(fm.contains(13));
        TEST_BOOLEAN_TRUE(fm.contains(14));
        TEST_BOOLEAN_TRUE(fm.contains(15));
        TEST_BOOLEAN_TRUE(fm.contains(16));
        TEST_BOOLEAN_TRUE(fm.contains(17));
        TEST_BOOLEAN_TRUE(fm.contains(18));
        TEST_BOOLEAN_TRUE(fm.contains(19));
        TEST_BOOLEAN_FALSE(fm.contains(20));
        TEST_BOOLEAN_FALSE(fm.contains(21));

        TEST_INT_EQ(1u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(1u, fm.count(1));
        TEST_INT_EQ(1u, fm.count(2));
        TEST_INT_EQ(1u, fm.count(3));
        TEST_INT_EQ(1u, fm.count(4));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[-1]);
        TEST_INT_EQ(1u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(1u, fm[1]);
        TEST_INT_EQ(1u, fm[2]);
        TEST_INT_EQ(1u, fm[3]);
        TEST_INT_EQ(1u, fm[4]);
        TEST_INT_EQ(0u, fm[-2]);
    }

    {
        fm_unordered_int_t fm(VALUES.begin(), VALUES.end());

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(20u, fm.size());
        TEST_INT_EQ(20u, fm.total());

        TEST_BOOLEAN_FALSE(fm.contains(-1));
        TEST_BOOLEAN_TRUE(fm.contains(0));
        TEST_BOOLEAN_TRUE(fm.contains(1));
        TEST_BOOLEAN_TRUE(fm.contains(2));
        TEST_BOOLEAN_TRUE(fm.contains(3));
        TEST_BOOLEAN_TRUE(fm.contains(4));
        TEST_BOOLEAN_TRUE(fm.contains(5));
        TEST_BOOLEAN_TRUE(fm.contains(6));
        TEST_BOOLEAN_TRUE(fm.contains(7));
        TEST_BOOLEAN_TRUE(fm.contains(8));
        TEST_BOOLEAN_TRUE(fm.contains(9));
        TEST_BOOLEAN_TRUE(fm.contains(10));
        TEST_BOOLEAN_TRUE(fm.contains(11));
        TEST_BOOLEAN_TRUE(fm.contains(12));
        TEST_BOOLEAN_TRUE(fm.contains(13));
        TEST_BOOLEAN_TRUE(fm.contains(14));
        TEST_BOOLEAN_TRUE(fm.contains(15));
        TEST_BOOLEAN_TRUE(fm.contains(16));
        TEST_BOOLEAN_TRUE(fm.contains(17));
        TEST_BOOLEAN_TRUE(fm.contains(18));
        TEST_BOOLEAN_TRUE(fm.contains(19));
        TEST_BOOLEAN_FALSE(fm.contains(20));
        TEST_BOOLEAN_FALSE(fm.contains(21));

        TEST_INT_EQ(1u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(1u, fm.count(1));
        TEST_INT_EQ(1u, fm.count(2));
        TEST_INT_EQ(1u, fm.count(3));
        TEST_INT_EQ(1u, fm.count(4));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[-1]);
        TEST_INT_EQ(1u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(1u, fm[1]);
        TEST_INT_EQ(1u, fm[2]);
        TEST_INT_EQ(1u, fm[3]);
        TEST_INT_EQ(1u, fm[4]);
        TEST_INT_EQ(0u, fm[-2]);
    }
}
#endif

static void test_clear()
{
    {
        fm_ordered_int_t    fm;

        TEST_BOOLEAN_TRUE(fm.empty());
        TEST_INT_EQ(0u, fm.size());
        TEST_INT_EQ(0u, fm.total());

        TEST_INT_EQ(0u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(0u, fm.count(1));
        TEST_INT_EQ(0u, fm.count(2));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(0u, fm[1]);
        TEST_INT_EQ(0u, fm[2]);
        TEST_INT_EQ(0u, fm[-2]);

        fm.clear();

        TEST_BOOLEAN_TRUE(fm.empty());
        TEST_INT_EQ(0u, fm.size());
        TEST_INT_EQ(0u, fm.total());

        TEST_INT_EQ(0u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(0u, fm.count(1));
        TEST_INT_EQ(0u, fm.count(2));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(0u, fm[1]);
        TEST_INT_EQ(0u, fm[2]);
        TEST_INT_EQ(0u, fm[-2]);
    }

    {
        fm_ordered_int_t    fm;

        fm.push_n(1, 3);
        fm.push(2);

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(2u, fm.size());
        TEST_INT_EQ(4u, fm.total());

        TEST_INT_EQ(0u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(3u, fm.count(1));
        TEST_INT_EQ(1u, fm.count(2));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(3u, fm[1]);
        TEST_INT_EQ(1u, fm[2]);
        TEST_INT_EQ(0u, fm[-2]);

        fm.clear();

        TEST_BOOLEAN_TRUE(fm.empty());
        TEST_INT_EQ(0u, fm.size());
        TEST_INT_EQ(0u, fm.total());

        TEST_INT_EQ(0u, fm.count(0));
        TEST_INT_EQ(0u, fm.count(100));
        TEST_INT_EQ(0u, fm.count(1));
        TEST_INT_EQ(0u, fm.count(2));
        TEST_INT_EQ(0u, fm.count(-2));

        TEST_INT_EQ(0u, fm[0]);
        TEST_INT_EQ(0u, fm[100]);
        TEST_INT_EQ(0u, fm[1]);
        TEST_INT_EQ(0u, fm[2]);
        TEST_INT_EQ(0u, fm[-2]);
    }
}

static void test_merge()
{
    {
        fm_ordered_int_t    fm1;
        fm_ordered_int_t    fm2;

        TEST_BOOLEAN_TRUE(fm1.empty());
        TEST_BOOLEAN_TRUE(fm2.empty());
        TEST_INT_EQ(0u, fm1.size());
        TEST_INT_EQ(0u, fm1.total());
        TEST_INT_EQ(0u, fm2.size());
        TEST_INT_EQ(0u, fm2.total());

        fm1.merge(fm2);

        TEST_BOOLEAN_TRUE(fm1.empty());
        TEST_BOOLEAN_TRUE(fm2.empty());
        TEST_INT_EQ(0u, fm1.size());
        TEST_INT_EQ(0u, fm1.total());
        TEST_INT_EQ(0u, fm2.size());
        TEST_INT_EQ(0u, fm2.total());
    }

    {
        fm_ordered_int_t    fm1;
        fm_ordered_int_t    fm2;

        fm1.push_n(1, 3);
        fm1.push(2);
        fm2.push_n(-2, 7);

        TEST_BOOLEAN_FALSE(fm1.empty());
        TEST_BOOLEAN_FALSE(fm2.empty());
        TEST_INT_EQ(2u, fm1.size());
        TEST_INT_EQ(4u, fm1.total());
        TEST_INT_EQ(1u, fm2.size());
        TEST_INT_EQ(7u, fm2.total());

        TEST_INT_EQ(0u, fm1.count(0));
        TEST_INT_EQ(0u, fm2.count(0));
        TEST_INT_EQ(0u, fm1.count(100));
        TEST_INT_EQ(0u, fm2.count(100));
        TEST_INT_EQ(3u, fm1.count(1));
        TEST_INT_EQ(0u, fm2.count(1));
        TEST_INT_EQ(1u, fm1.count(2));
        TEST_INT_EQ(0u, fm2.count(2));
        TEST_INT_EQ(0u, fm1.count(-2));
        TEST_INT_EQ(7u, fm2.count(-2));

        TEST_INT_EQ(0u, fm1[0]);
        TEST_INT_EQ(0u, fm2[0]);
        TEST_INT_EQ(0u, fm1[100]);
        TEST_INT_EQ(0u, fm2[100]);
        TEST_INT_EQ(3u, fm1[1]);
        TEST_INT_EQ(0u, fm2[1]);
        TEST_INT_EQ(1u, fm1[2]);
        TEST_INT_EQ(0u, fm2[2]);
        TEST_INT_EQ(0u, fm1[-2]);
        TEST_INT_EQ(7u, fm2[-2]);

        fm1.merge(fm2);

        TEST_BOOLEAN_FALSE(fm1.empty());
        TEST_BOOLEAN_FALSE(fm2.empty());
        TEST_INT_EQ(3u, fm1.size());
        TEST_INT_EQ(11u, fm1.total());
        TEST_INT_EQ(1u, fm2.size());
        TEST_INT_EQ(7u, fm2.total());

        TEST_INT_EQ(0u, fm1.count(0));
        TEST_INT_EQ(0u, fm2.count(0));
        TEST_INT_EQ(0u, fm1.count(100));
        TEST_INT_EQ(0u, fm2.count(100));
        TEST_INT_EQ(3u, fm1.count(1));
        TEST_INT_EQ(0u, fm2.count(1));
        TEST_INT_EQ(1u, fm1.count(2));
        TEST_INT_EQ(0u, fm2.count(2));
        TEST_INT_EQ(7u, fm1.count(-2));
        TEST_INT_EQ(7u, fm2.count(-2));

        TEST_INT_EQ(0u, fm1[0]);
        TEST_INT_EQ(0u, fm2[0]);
        TEST_INT_EQ(0u, fm1[100]);
        TEST_INT_EQ(0u, fm2[100]);
        TEST_INT_EQ(3u, fm1[1]);
        TEST_INT_EQ(0u, fm2[1]);
        TEST_INT_EQ(1u, fm1[2]);
        TEST_INT_EQ(0u, fm2[2]);
        TEST_INT_EQ(7u, fm1[-2]);
        TEST_INT_EQ(7u, fm2[-2]);
    }
#if __cplusplus >= 201103L

    {
        fm_unordered_int_t  fm1;
        fm_unordered_int_t  fm2;

        TEST_BOOLEAN_TRUE(fm1.empty());
        TEST_BOOLEAN_TRUE(fm2.empty());
        TEST_INT_EQ(0u, fm1.size());
        TEST_INT_EQ(0u, fm1.total());
        TEST_INT_EQ(0u, fm2.size());
        TEST_INT_EQ(0u, fm2.total());

        fm1.merge(fm2);

        TEST_BOOLEAN_TRUE(fm1.empty());
        TEST_BOOLEAN_TRUE(fm2.empty());
        TEST_INT_EQ(0u, fm1.size());
        TEST_INT_EQ(0u, fm1.total());
        TEST_INT_EQ(0u, fm2.size());
        TEST_INT_EQ(0u, fm2.total());
    }

    {
        fm_unordered_int_t  fm1;
        fm_unordered_int_t  fm2;

        fm1.push_n(1, 3);
        fm1.push(2);
        fm2.push_n(-2, 7);

        TEST_BOOLEAN_FALSE(fm1.empty());
        TEST_BOOLEAN_FALSE(fm2.empty());
        TEST_INT_EQ(2u, fm1.size());
        TEST_INT_EQ(4u, fm1.total());
        TEST_INT_EQ(1u, fm2.size());
        TEST_INT_EQ(7u, fm2.total());

        TEST_INT_EQ(0u, fm1.count(0));
        TEST_INT_EQ(0u, fm2.count(0));
        TEST_INT_EQ(0u, fm1.count(100));
        TEST_INT_EQ(0u, fm2.count(100));
        TEST_INT_EQ(3u, fm1.count(1));
        TEST_INT_EQ(0u, fm2.count(1));
        TEST_INT_EQ(1u, fm1.count(2));
        TEST_INT_EQ(0u, fm2.count(2));
        TEST_INT_EQ(0u, fm1.count(-2));
        TEST_INT_EQ(7u, fm2.count(-2));

        TEST_INT_EQ(0u, fm1[0]);
        TEST_INT_EQ(0u, fm2[0]);
        TEST_INT_EQ(0u, fm1[100]);
        TEST_INT_EQ(0u, fm2[100]);
        TEST_INT_EQ(3u, fm1[1]);
        TEST_INT_EQ(0u, fm2[1]);
        TEST_INT_EQ(1u, fm1[2]);
        TEST_INT_EQ(0u, fm2[2]);
        TEST_INT_EQ(0u, fm1[-2]);
        TEST_INT_EQ(7u, fm2[-2]);

        fm1.merge(fm2);

        TEST_BOOLEAN_FALSE(fm1.empty());
        TEST_BOOLEAN_FALSE(fm2.empty());
        TEST_INT_EQ(3u, fm1.size());
        TEST_INT_EQ(11u, fm1.total());
        TEST_INT_EQ(1u, fm2.size());
        TEST_INT_EQ(7u, fm2.total());

        TEST_INT_EQ(0u, fm1.count(0));
        TEST_INT_EQ(0u, fm2.count(0));
        TEST_INT_EQ(0u, fm1.count(100));
        TEST_INT_EQ(0u, fm2.count(100));
        TEST_INT_EQ(3u, fm1.count(1));
        TEST_INT_EQ(0u, fm2.count(1));
        TEST_INT_EQ(1u, fm1.count(2));
        TEST_INT_EQ(0u, fm2.count(2));
        TEST_INT_EQ(7u, fm1.count(-2));
        TEST_INT_EQ(7u, fm2.count(-2));

        TEST_INT_EQ(0u, fm1[0]);
        TEST_INT_EQ(0u, fm2[0]);
        TEST_INT_EQ(0u, fm1[100]);
        TEST_INT_EQ(0u, fm2[100]);
        TEST_INT_EQ(3u, fm1[1]);
        TEST_INT_EQ(0u, fm2[1]);
        TEST_INT_EQ(1u, fm1[2]);
        TEST_INT_EQ(0u, fm2[2]);
        TEST_INT_EQ(7u, fm1[-2]);
        TEST_INT_EQ(7u, fm2[-2]);
    }
#endif /* C++ */
}

static void test_op_addassign()
{
    {

        {
            fm_ordered_int_t    fm1;
            fm_ordered_int_t    fm2;

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());

            fm1 += fm2;

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());
        }

        {
            fm_ordered_int_t    fm1;
            fm_ordered_int_t    fm2;

            fm1.push_n(1, 3);
            fm1.push(2);
            fm2.push_n(-2, 7);

            TEST_BOOLEAN_FALSE(fm1.empty());
            TEST_BOOLEAN_FALSE(fm2.empty());
            TEST_INT_EQ(2u, fm1.size());
            TEST_INT_EQ(4u, fm1.total());
            TEST_INT_EQ(1u, fm2.size());
            TEST_INT_EQ(7u, fm2.total());

            TEST_INT_EQ(0u, fm1.count(0));
            TEST_INT_EQ(0u, fm2.count(0));
            TEST_INT_EQ(0u, fm1.count(100));
            TEST_INT_EQ(0u, fm2.count(100));
            TEST_INT_EQ(3u, fm1.count(1));
            TEST_INT_EQ(0u, fm2.count(1));
            TEST_INT_EQ(1u, fm1.count(2));
            TEST_INT_EQ(0u, fm2.count(2));
            TEST_INT_EQ(0u, fm1.count(-2));
            TEST_INT_EQ(7u, fm2.count(-2));

            TEST_INT_EQ(0u, fm1[0]);
            TEST_INT_EQ(0u, fm2[0]);
            TEST_INT_EQ(0u, fm1[100]);
            TEST_INT_EQ(0u, fm2[100]);
            TEST_INT_EQ(3u, fm1[1]);
            TEST_INT_EQ(0u, fm2[1]);
            TEST_INT_EQ(1u, fm1[2]);
            TEST_INT_EQ(0u, fm2[2]);
            TEST_INT_EQ(0u, fm1[-2]);
            TEST_INT_EQ(7u, fm2[-2]);

            fm1 += fm2;

            TEST_BOOLEAN_FALSE(fm1.empty());
            TEST_BOOLEAN_FALSE(fm2.empty());
            TEST_INT_EQ(3u, fm1.size());
            TEST_INT_EQ(11u, fm1.total());
            TEST_INT_EQ(1u, fm2.size());
            TEST_INT_EQ(7u, fm2.total());

            TEST_INT_EQ(0u, fm1.count(0));
            TEST_INT_EQ(0u, fm2.count(0));
            TEST_INT_EQ(0u, fm1.count(100));
            TEST_INT_EQ(0u, fm2.count(100));
            TEST_INT_EQ(3u, fm1.count(1));
            TEST_INT_EQ(0u, fm2.count(1));
            TEST_INT_EQ(1u, fm1.count(2));
            TEST_INT_EQ(0u, fm2.count(2));
            TEST_INT_EQ(7u, fm1.count(-2));
            TEST_INT_EQ(7u, fm2.count(-2));

            TEST_INT_EQ(0u, fm1[0]);
            TEST_INT_EQ(0u, fm2[0]);
            TEST_INT_EQ(0u, fm1[100]);
            TEST_INT_EQ(0u, fm2[100]);
            TEST_INT_EQ(3u, fm1[1]);
            TEST_INT_EQ(0u, fm2[1]);
            TEST_INT_EQ(1u, fm1[2]);
            TEST_INT_EQ(0u, fm2[2]);
            TEST_INT_EQ(7u, fm1[-2]);
            TEST_INT_EQ(7u, fm2[-2]);
        }
    }
#if __cplusplus >= 201103L

    {

        {
            fm_unordered_int_t  fm1;
            fm_unordered_int_t  fm2;

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());

            fm1 += fm2;

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());
        }

        {
            fm_unordered_int_t  fm1;
            fm_unordered_int_t  fm2;

            fm1.push_n(1, 3);
            fm1.push(2);
            fm2.push_n(-2, 7);

            TEST_BOOLEAN_FALSE(fm1.empty());
            TEST_BOOLEAN_FALSE(fm2.empty());
            TEST_INT_EQ(2u, fm1.size());
            TEST_INT_EQ(4u, fm1.total());
            TEST_INT_EQ(1u, fm2.size());
            TEST_INT_EQ(7u, fm2.total());

            TEST_INT_EQ(0u, fm1.count(0));
            TEST_INT_EQ(0u, fm2.count(0));
            TEST_INT_EQ(0u, fm1.count(100));
            TEST_INT_EQ(0u, fm2.count(100));
            TEST_INT_EQ(3u, fm1.count(1));
            TEST_INT_EQ(0u, fm2.count(1));
            TEST_INT_EQ(1u, fm1.count(2));
            TEST_INT_EQ(0u, fm2.count(2));
            TEST_INT_EQ(0u, fm1.count(-2));
            TEST_INT_EQ(7u, fm2.count(-2));

            TEST_INT_EQ(0u, fm1[0]);
            TEST_INT_EQ(0u, fm2[0]);
            TEST_INT_EQ(0u, fm1[100]);
            TEST_INT_EQ(0u, fm2[100]);
            TEST_INT_EQ(3u, fm1[1]);
            TEST_INT_EQ(0u, fm2[1]);
            TEST_INT_EQ(1u, fm1[2]);
            TEST_INT_EQ(0u, fm2[2]);
            TEST_INT_EQ(0u, fm1[-2]);
            TEST_INT_EQ(7u, fm2[-2]);

            fm1 += fm2;

            TEST_BOOLEAN_FALSE(fm1.empty());
            TEST_BOOLEAN_FALSE(fm2.empty());
            TEST_INT_EQ(3u, fm1.size());
            TEST_INT_EQ(11u, fm1.total());
            TEST_INT_EQ(1u, fm2.size());
            TEST_INT_EQ(7u, fm2.total());

            TEST_INT_EQ(0u, fm1.count(0));
            TEST_INT_EQ(0u, fm2.count(0));
            TEST_INT_EQ(0u, fm1.count(100));
            TEST_INT_EQ(0u, fm2.count(100));
            TEST_INT_EQ(3u, fm1.count(1));
            TEST_INT_EQ(0u, fm2.count(1));
            TEST_INT_EQ(1u, fm1.count(2));
            TEST_INT_EQ(0u, fm2.count(2));
            TEST_INT_EQ(7u, fm1.count(-2));
            TEST_INT_EQ(7u, fm2.count(-2));

            TEST_INT_EQ(0u, fm1[0]);
            TEST_INT_EQ(0u, fm2[0]);
            TEST_INT_EQ(0u, fm1[100]);
            TEST_INT_EQ(0u, fm2[100]);
            TEST_INT_EQ(3u, fm1[1]);
            TEST_INT_EQ(0u, fm2[1]);
            TEST_INT_EQ(1u, fm1[2]);
            TEST_INT_EQ(0u, fm2[2]);
            TEST_INT_EQ(7u, fm1[-2]);
            TEST_INT_EQ(7u, fm2[-2]);
        }
    }
#endif
}

static void test_op_add()
{
    {
        {
            fm_ordered_int_t    fm1;
            fm_ordered_int_t    fm2;

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());

            fm_ordered_int_t    fm3 = fm1 + fm2;

            TEST_BOOLEAN_TRUE(fm3.empty());
            TEST_INT_EQ(0u, fm3.size());
            TEST_INT_EQ(0u, fm3.size());
        }

        {
            fm_ordered_int_t    fm1;
            fm_ordered_int_t    fm2;

            fm1.push_n(1, 3);
            fm1.push(2);
            fm2.push_n(-2, 7);

            fm_ordered_int_t    fm3 = fm1 + fm2;

            TEST_BOOLEAN_FALSE(fm3.empty());
            TEST_INT_EQ(3u, fm3.size());
            TEST_INT_EQ(11u, fm3.total());

            TEST_INT_EQ(0u, fm3.count(0));
            TEST_INT_EQ(0u, fm3.count(100));
            TEST_INT_EQ(3u, fm3.count(1));
            TEST_INT_EQ(1u, fm3.count(2));
            TEST_INT_EQ(7u, fm3.count(-2));

            TEST_INT_EQ(0u, fm3[0]);
            TEST_INT_EQ(0u, fm3[100]);
            TEST_INT_EQ(3u, fm3[1]);
            TEST_INT_EQ(1u, fm3[2]);
            TEST_INT_EQ(7u, fm3[-2]);
        }
    }
#if __cplusplus >= 201103L

    {
        {
            fm_unordered_int_t  fm1;
            fm_unordered_int_t  fm2;

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());

            fm_unordered_int_t  fm3 = fm1 + fm2;

            TEST_BOOLEAN_TRUE(fm3.empty());
            TEST_INT_EQ(0u, fm3.size());
            TEST_INT_EQ(0u, fm3.size());
        }

        {
            fm_unordered_int_t  fm1;
            fm_unordered_int_t  fm2;

            fm1.push_n(1, 3);
            fm1.push(2);
            fm2.push_n(-2, 7);

            fm_unordered_int_t  fm3 = fm1 + fm2;

            TEST_BOOLEAN_FALSE(fm3.empty());
            TEST_INT_EQ(3u, fm3.size());
            TEST_INT_EQ(11u, fm3.total());

            TEST_INT_EQ(0u, fm3.count(0));
            TEST_INT_EQ(0u, fm3.count(100));
            TEST_INT_EQ(3u, fm3.count(1));
            TEST_INT_EQ(1u, fm3.count(2));
            TEST_INT_EQ(7u, fm3.count(-2));

            TEST_INT_EQ(0u, fm3[0]);
            TEST_INT_EQ(0u, fm3[100]);
            TEST_INT_EQ(3u, fm3[1]);
            TEST_INT_EQ(1u, fm3[2]);
            TEST_INT_EQ(7u, fm3[-2]);
        }
    }
#endif
}

static void test_push()
{
    {
        fm_ordered_int_t        fm;
        fm_ordered_int_t const& fmc = fm;

        TEST_BOOLEAN_TRUE(fm.empty());
        TEST_INT_EQ(0u, fm.size());
        TEST_INT_EQ(0u, fm.total());

        TEST_INT_EQ(0u, fm.count(101));
        TEST_INT_EQ(0u, fm.count(102));
        TEST_INT_EQ(0u, fm.count(103));
        TEST_INT_EQ(0u, fm.count(104));
        TEST_INT_EQ(0u, fm.count(105));

        TEST(fm.end() == fm.find(101));
        TEST(fm.end() == fm.find(102));
        TEST(fm.end() == fm.find(103));
        TEST(fm.end() == fm.find(104));
        TEST(fm.end() == fm.find(105));

        TEST(fm.end() == fm.begin());
        TEST(fmc.end() == fmc.begin());
#if __cplusplus >= 201103L

        {
            auto l = fm_to_list(fmc);

            TEST_BOOLEAN_TRUE(l.empty());
        }
#endif /* C++ */

        fm.push(101);

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(1u, fm.size());
        TEST_INT_EQ(1u, fm.total());

        TEST_INT_EQ(1u, fm.count(101));
        TEST_INT_EQ(0u, fm.count(102));
        TEST_INT_EQ(0u, fm.count(103));
        TEST_INT_EQ(0u, fm.count(104));
        TEST_INT_EQ(0u, fm.count(105));

        TEST(fm.end() != fm.find(101));
        TEST(fm.end() == fm.find(102));
        TEST(fm.end() == fm.find(103));
        TEST(fm.end() == fm.find(104));
        TEST(fm.end() == fm.find(105));

        TEST(fm.end() != fm.begin());
        TEST(fmc.end() != fmc.begin());
#if __cplusplus >= 201103L

        {
            auto l = fm_to_list(fmc);

            TEST_INT_EQ(1u, l.size());

            TEST(std::make_pair(101, 1u) == l[0]);
        }
#endif /* C++ */

        fm.push(105);

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(2u, fm.size());
        TEST_INT_EQ(2u, fm.total());

        TEST_INT_EQ(1u, fm.count(101));
        TEST_INT_EQ(0u, fm.count(102));
        TEST_INT_EQ(0u, fm.count(103));
        TEST_INT_EQ(0u, fm.count(104));
        TEST_INT_EQ(1u, fm.count(105));

        TEST(fm.end() != fm.find(101));
        TEST(fm.end() == fm.find(102));
        TEST(fm.end() == fm.find(103));
        TEST(fm.end() == fm.find(104));
        TEST(fm.end() != fm.find(105));

        TEST(fm.end() != fm.begin());
        TEST(fmc.end() != fmc.begin());
#if __cplusplus >= 201103L

        {
            auto l = fm_to_list(fmc);

            TEST_INT_EQ(2u, l.size());

            TEST(std::make_pair(101, 1u) == l[0]);
            TEST(std::make_pair(105, 1u) == l[1]);
        }
#endif /* C++ */

        fm.push(101);

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(2u, fm.size());
        TEST_INT_EQ(3u, fm.total());

        TEST_INT_EQ(2u, fm.count(101));
        TEST_INT_EQ(0u, fm.count(102));
        TEST_INT_EQ(0u, fm.count(103));
        TEST_INT_EQ(0u, fm.count(104));
        TEST_INT_EQ(1u, fm.count(105));

        TEST(fm.end() != fm.find(101));
        TEST(fm.end() == fm.find(102));
        TEST(fm.end() == fm.find(103));
        TEST(fm.end() == fm.find(104));
        TEST(fm.end() != fm.find(105));

        TEST(fm.end() != fm.begin());
        TEST(fmc.end() != fmc.begin());
#if __cplusplus >= 201103L

        {
            auto l = fmi_to_list(fmc.crbegin(), fmc.crend());

            TEST_INT_EQ(2u, l.size());

            TEST(std::make_pair(101, 2u) == l[0]);
            TEST(std::make_pair(105, 1u) == l[1]);
        }
#endif /* C++ */
    }
#if __cplusplus >= 201103L

    {
        fm_unordered_int_t          fm;
        fm_unordered_int_t const&   fmc = fm;

        TEST_BOOLEAN_TRUE(fm.empty());
        TEST_INT_EQ(0u, fm.size());
        TEST_INT_EQ(0u, fm.total());

        TEST_INT_EQ(0u, fm.count(101));
        TEST_INT_EQ(0u, fm.count(102));
        TEST_INT_EQ(0u, fm.count(103));
        TEST_INT_EQ(0u, fm.count(104));
        TEST_INT_EQ(0u, fm.count(105));

        TEST(fm.end() == fm.find(101));
        TEST(fm.end() == fm.find(102));
        TEST(fm.end() == fm.find(103));
        TEST(fm.end() == fm.find(104));
        TEST(fm.end() == fm.find(105));

        TEST(fm.end() == fm.begin());
        TEST(fmc.end() == fmc.begin());

        {
            auto l = fm_to_list(fmc);

            TEST_BOOLEAN_TRUE(l.empty());
        }

        fm.push(101);

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(1u, fm.size());
        TEST_INT_EQ(1u, fm.total());

        TEST_INT_EQ(1u, fm.count(101));
        TEST_INT_EQ(0u, fm.count(102));
        TEST_INT_EQ(0u, fm.count(103));
        TEST_INT_EQ(0u, fm.count(104));
        TEST_INT_EQ(0u, fm.count(105));

        TEST(fm.end() != fm.find(101));
        TEST(fm.end() == fm.find(102));
        TEST(fm.end() == fm.find(103));
        TEST(fm.end() == fm.find(104));
        TEST(fm.end() == fm.find(105));

        TEST(fm.end() != fm.begin());
        TEST(fmc.end() != fmc.begin());

        {
            auto l = fm_to_list(fmc);

            TEST_INT_EQ(1u, l.size());

            TEST(std::make_pair(101, 1u) == l[0]);
        }

        fm.push(105);

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(2u, fm.size());
        TEST_INT_EQ(2u, fm.total());

        TEST_INT_EQ(1u, fm.count(101));
        TEST_INT_EQ(0u, fm.count(102));
        TEST_INT_EQ(0u, fm.count(103));
        TEST_INT_EQ(0u, fm.count(104));
        TEST_INT_EQ(1u, fm.count(105));

        TEST(fm.end() != fm.find(101));
        TEST(fm.end() == fm.find(102));
        TEST(fm.end() == fm.find(103));
        TEST(fm.end() == fm.find(104));
        TEST(fm.end() != fm.find(105));

        TEST(fm.end() != fm.begin());
        TEST(fmc.end() != fmc.begin());

        {
            auto l = fm_to_list(fmc);

            TEST_INT_EQ(2u, l.size());

            TEST(std::make_pair(101, 1u) == l[0]);
            TEST(std::make_pair(105, 1u) == l[1]);
        }

        fm.push(101);

        TEST_BOOLEAN_FALSE(fm.empty());
        TEST_INT_EQ(2u, fm.size());
        TEST_INT_EQ(3u, fm.total());

        TEST_INT_EQ(2u, fm.count(101));
        TEST_INT_EQ(0u, fm.count(102));
        TEST_INT_EQ(0u, fm.count(103));
        TEST_INT_EQ(0u, fm.count(104));
        TEST_INT_EQ(1u, fm.count(105));

        TEST(fm.end() != fm.find(101));
        TEST(fm.end() == fm.find(102));
        TEST(fm.end() == fm.find(103));
        TEST(fm.end() == fm.find(104));
        TEST(fm.end() != fm.find(105));

        TEST(fm.end() != fm.begin());
        TEST(fmc.end() != fmc.begin());

        {
            auto l = fmi_to_list(fmc.cbegin(), fmc.cend());

            TEST_INT_EQ(2u, l.size());

            TEST(std::make_pair(101, 2u) == l[0]);
            TEST(std::make_pair(105, 1u) == l[1]);
        }
    }
#endif /* C++ */
}

static void test_swap()
{
    {
        fm_ordered_int_t    fm1;
        fm_ordered_int_t    fm2;

        TEST_BOOLEAN_TRUE(fm1.empty());
        TEST_BOOLEAN_TRUE(fm2.empty());
        TEST_INT_EQ(0u, fm1.size());
        TEST_INT_EQ(0u, fm1.total());
        TEST_INT_EQ(0u, fm2.size());
        TEST_INT_EQ(0u, fm2.total());

        fm1.swap(fm2);

        TEST_BOOLEAN_TRUE(fm1.empty());
        TEST_BOOLEAN_TRUE(fm2.empty());
        TEST_INT_EQ(0u, fm1.size());
        TEST_INT_EQ(0u, fm1.total());
        TEST_INT_EQ(0u, fm2.size());
        TEST_INT_EQ(0u, fm2.total());

        fm2.swap(fm1);

        TEST_BOOLEAN_TRUE(fm1.empty());
        TEST_BOOLEAN_TRUE(fm2.empty());
        TEST_INT_EQ(0u, fm1.size());
        TEST_INT_EQ(0u, fm1.total());
        TEST_INT_EQ(0u, fm2.size());
        TEST_INT_EQ(0u, fm2.total());
    }

    {
        fm_ordered_int_t    fm1;
        fm_ordered_int_t    fm2;

        fm1.push_n(1, 3);
        fm1.push(2);
        fm2.push_n(-2, 7);

        TEST_BOOLEAN_FALSE(fm1.empty());
        TEST_BOOLEAN_FALSE(fm2.empty());
        TEST_INT_EQ(2u, fm1.size());
        TEST_INT_EQ(4u, fm1.total());
        TEST_INT_EQ(1u, fm2.size());
        TEST_INT_EQ(7u, fm2.total());

        TEST_INT_EQ(0u, fm1.count(0));
        TEST_INT_EQ(0u, fm2.count(100));
        TEST_INT_EQ(3u, fm1.count(1));
        TEST_INT_EQ(1u, fm1.count(2));
        TEST_INT_EQ(7u, fm2.count(-2));

        TEST_INT_EQ(0u, fm1[0]);
        TEST_INT_EQ(0u, fm2[100]);
        TEST_INT_EQ(3u, fm1[1]);
        TEST_INT_EQ(1u, fm1[2]);
        TEST_INT_EQ(7u, fm2[-2]);

        fm1.swap(fm2);

        TEST_BOOLEAN_FALSE(fm1.empty());
        TEST_BOOLEAN_FALSE(fm2.empty());
        TEST_INT_EQ(1u, fm1.size());
        TEST_INT_EQ(7u, fm1.total());
        TEST_INT_EQ(2u, fm2.size());
        TEST_INT_EQ(4u, fm2.total());

        TEST_INT_EQ(0u, fm1.count(0));
        TEST_INT_EQ(0u, fm2.count(100));
        TEST_INT_EQ(7u, fm1.count(-2));
        TEST_INT_EQ(3u, fm2.count(1));
        TEST_INT_EQ(1u, fm2.count(2));

        TEST_INT_EQ(0u, fm1[0]);
        TEST_INT_EQ(0u, fm2[100]);
        TEST_INT_EQ(7u, fm1[-2]);
        TEST_INT_EQ(3u, fm2[1]);
        TEST_INT_EQ(1u, fm2[2]);

        fm2.swap(fm1);

        TEST_BOOLEAN_FALSE(fm1.empty());
        TEST_BOOLEAN_FALSE(fm2.empty());
        TEST_INT_EQ(2u, fm1.size());
        TEST_INT_EQ(4u, fm1.total());
        TEST_INT_EQ(1u, fm2.size());
        TEST_INT_EQ(7u, fm2.total());

        TEST_INT_EQ(0u, fm1.count(0));
        TEST_INT_EQ(0u, fm2.count(100));
        TEST_INT_EQ(3u, fm1.count(1));
        TEST_INT_EQ(1u, fm1.count(2));
        TEST_INT_EQ(7u, fm2.count(-2));

        TEST_INT_EQ(0u, fm1[0]);
        TEST_INT_EQ(0u, fm2[100]);
        TEST_INT_EQ(3u, fm1[1]);
        TEST_INT_EQ(1u, fm1[2]);
        TEST_INT_EQ(7u, fm2[-2]);
    }
}

static void test_swap_std()
{
    {
        {
            fm_ordered_int_t    fm1;
            fm_ordered_int_t    fm2;

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());

            std::swap(fm1, fm2);

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());

            std::swap(fm2, fm1);

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());
        }

        {
            fm_ordered_int_t    fm1;
            fm_ordered_int_t    fm2;

            fm1.push_n(1, 3);
            fm1.push(2);
            fm2.push_n(-2, 7);

            TEST_BOOLEAN_FALSE(fm1.empty());
            TEST_BOOLEAN_FALSE(fm2.empty());
            TEST_INT_EQ(2u, fm1.size());
            TEST_INT_EQ(4u, fm1.total());
            TEST_INT_EQ(1u, fm2.size());
            TEST_INT_EQ(7u, fm2.total());

            TEST_INT_EQ(0u, fm1.count(0));
            TEST_INT_EQ(0u, fm2.count(100));
            TEST_INT_EQ(3u, fm1.count(1));
            TEST_INT_EQ(1u, fm1.count(2));
            TEST_INT_EQ(7u, fm2.count(-2));

            TEST_INT_EQ(0u, fm1[0]);
            TEST_INT_EQ(0u, fm2[100]);
            TEST_INT_EQ(3u, fm1[1]);
            TEST_INT_EQ(1u, fm1[2]);
            TEST_INT_EQ(7u, fm2[-2]);

            std::swap(fm1, fm2);

            TEST_BOOLEAN_FALSE(fm1.empty());
            TEST_BOOLEAN_FALSE(fm2.empty());
            TEST_INT_EQ(1u, fm1.size());
            TEST_INT_EQ(7u, fm1.total());
            TEST_INT_EQ(2u, fm2.size());
            TEST_INT_EQ(4u, fm2.total());

            TEST_INT_EQ(0u, fm1.count(0));
            TEST_INT_EQ(0u, fm2.count(100));
            TEST_INT_EQ(7u, fm1.count(-2));
            TEST_INT_EQ(3u, fm2.count(1));
            TEST_INT_EQ(1u, fm2.count(2));

            TEST_INT_EQ(0u, fm1[0]);
            TEST_INT_EQ(0u, fm2[100]);
            TEST_INT_EQ(7u, fm1[-2]);
            TEST_INT_EQ(3u, fm2[1]);
            TEST_INT_EQ(1u, fm2[2]);

            std::swap(fm2, fm1);

            TEST_BOOLEAN_FALSE(fm1.empty());
            TEST_BOOLEAN_FALSE(fm2.empty());
            TEST_INT_EQ(2u, fm1.size());
            TEST_INT_EQ(4u, fm1.total());
            TEST_INT_EQ(1u, fm2.size());
            TEST_INT_EQ(7u, fm2.total());

            TEST_INT_EQ(0u, fm1.count(0));
            TEST_INT_EQ(0u, fm2.count(100));
            TEST_INT_EQ(3u, fm1.count(1));
            TEST_INT_EQ(1u, fm1.count(2));
            TEST_INT_EQ(7u, fm2.count(-2));

            TEST_INT_EQ(0u, fm1[0]);
            TEST_INT_EQ(0u, fm2[100]);
            TEST_INT_EQ(3u, fm1[1]);
            TEST_INT_EQ(1u, fm1[2]);
            TEST_INT_EQ(7u, fm2[-2]);
        }
    }
#if __cplusplus >= 201103L

    {
        {
            fm_unordered_int_t  fm1;
            fm_unordered_int_t  fm2;

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());

            std::swap(fm1, fm2);

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());

            std::swap(fm2, fm1);

            TEST_BOOLEAN_TRUE(fm1.empty());
            TEST_BOOLEAN_TRUE(fm2.empty());
            TEST_INT_EQ(0u, fm1.size());
            TEST_INT_EQ(0u, fm1.total());
            TEST_INT_EQ(0u, fm2.size());
            TEST_INT_EQ(0u, fm2.total());
        }

        {
            fm_unordered_int_t  fm1;
            fm_unordered_int_t  fm2;

            fm1.push_n(1, 3);
            fm1.push(2);
            fm2.push_n(-2, 7);

            TEST_BOOLEAN_FALSE(fm1.empty());
            TEST_BOOLEAN_FALSE(fm2.empty());
            TEST_INT_EQ(2u, fm1.size());
            TEST_INT_EQ(4u, fm1.total());
            TEST_INT_EQ(1u, fm2.size());
            TEST_INT_EQ(7u, fm2.total());

            TEST_INT_EQ(0u, fm1.count(0));
            TEST_INT_EQ(0u, fm2.count(100));
            TEST_INT_EQ(3u, fm1.count(1));
            TEST_INT_EQ(1u, fm1.count(2));
            TEST_INT_EQ(7u, fm2.count(-2));

            TEST_INT_EQ(0u, fm1[0]);
            TEST_INT_EQ(0u, fm2[100]);
            TEST_INT_EQ(3u, fm1[1]);
            TEST_INT_EQ(1u, fm1[2]);
            TEST_INT_EQ(7u, fm2[-2]);

            std::swap(fm1, fm2);

            TEST_BOOLEAN_FALSE(fm1.empty());
            TEST_BOOLEAN_FALSE(fm2.empty());
            TEST_INT_EQ(1u, fm1.size());
            TEST_INT_EQ(7u, fm1.total());
            TEST_INT_EQ(2u, fm2.size());
            TEST_INT_EQ(4u, fm2.total());

            TEST_INT_EQ(0u, fm1.count(0));
            TEST_INT_EQ(0u, fm2.count(100));
            TEST_INT_EQ(7u, fm1.count(-2));
            TEST_INT_EQ(3u, fm2.count(1));
            TEST_INT_EQ(1u, fm2.count(2));

            TEST_INT_EQ(0u, fm1[0]);
            TEST_INT_EQ(0u, fm2[100]);
            TEST_INT_EQ(7u, fm1[-2]);
            TEST_INT_EQ(3u, fm2[1]);
            TEST_INT_EQ(1u, fm2[2]);

            std::swap(fm2, fm1);

            TEST_BOOLEAN_FALSE(fm1.empty());
            TEST_BOOLEAN_FALSE(fm2.empty());
            TEST_INT_EQ(2u, fm1.size());
            TEST_INT_EQ(4u, fm1.total());
            TEST_INT_EQ(1u, fm2.size());
            TEST_INT_EQ(7u, fm2.total());

            TEST_INT_EQ(0u, fm1.count(0));
            TEST_INT_EQ(0u, fm2.count(100));
            TEST_INT_EQ(3u, fm1.count(1));
            TEST_INT_EQ(1u, fm1.count(2));
            TEST_INT_EQ(7u, fm2.count(-2));

            TEST_INT_EQ(0u, fm1[0]);
            TEST_INT_EQ(0u, fm2[100]);
            TEST_INT_EQ(3u, fm1[1]);
            TEST_INT_EQ(1u, fm1[2]);
            TEST_INT_EQ(7u, fm2[-2]);
        }
    }
#endif
}

static void test_iteration_order_1()
{
#if __cplusplus >= 201103L

    {
        fm_ordered_int_t fm = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };

        pairs_t const actual(fm.begin(), fm.end());
        pairs_t const actual_ordered = to_ordered(actual, compare_value_type());

        pairs_t const expected = { { 1, 2 }, { 2, 2 }, { 3, 2 }, { 4, 2 }, { 5, 1 }};
        pairs_t const expected_ordered = to_ordered(expected, compare_value_type());

        TEST(expected_ordered == actual_ordered);
        TEST(expected == actual);
    }

    {
        fm_unordered_int_t fm = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };

        pairs_t const actual(fm.begin(), fm.end());

        pairs_t const actual_ordered = to_ordered(actual, compare_value_type());

        pairs_t const expected = { { 1, 2 }, { 2, 2 }, { 3, 2 }, { 4, 2 }, { 5, 1 }};

        pairs_t const expected_ordered = to_ordered(expected, compare_value_type());

        TEST(expected_ordered == actual_ordered);
    }
#endif
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

