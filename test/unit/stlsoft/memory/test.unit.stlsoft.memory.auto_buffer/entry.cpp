/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.memory.auto_buffer/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::auto_buffer`.
 *
 * Created: 25th February 2009
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/memory/auto_buffer.hpp>

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/memory/null_allocator.hpp>

/* Standard C++ header files */
#include <algorithm>
#include <list>
#include <numeric>
#include <vector>

/* Standard C header files */
#include <assert.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if 0
#elif defined(STLSOFT_COMPILER_IS_GCC)

  // We can't do in in GCC, as the mempcy() call (with count=1073741824) has UB
#else

# define ATTEMPT_ALLOCATOR_EXHAUSTION
#endif


/* /////////////////////////////////////////////////////////////////////////
 * helper classes
 */

class int_input_iterator
    : public STLSOFT_NS_QUAL(iterator_base)<
        STLSOFT_NS_QUAL_STD(input_iterator_tag)
    ,   int
    ,   std::ptrdiff_t
    ,   void    // By-Value Temporary reference
    ,   int     // By-Value Temporary reference
    >
{
public: // types
    typedef int_input_iterator                              class_type;

public: // construction
    explicit
    int_input_iterator(int const* pi)
        : m_pi(pi)
    {}
    int_input_iterator(class_type& rhs)
        : m_pi(rhs.m_pi)
    {
        rhs.m_pi = NULL;
    }
private:
    void operator =(class_type const&) STLSOFT_COPY_ASSIGNMENT_PROSCRIBED;

public: // operators
    class_type& operator ++()
    {
        ++m_pi;

        return *this;
    }

    value_type operator *() const
    {
        return *m_pi;
    }

    bool operator ==(class_type const& rhs) const
    {
        return m_pi == rhs.m_pi;
    }

    bool operator !=(class_type const& rhs) const
    {
        return !operator ==(rhs);
    }

/// Members
private:
    int const* m_pi;
};

class int_forward_iterator
    : public STLSOFT_NS_QUAL(iterator_base)<
        STLSOFT_NS_QUAL_STD(forward_iterator_tag)
    ,   int
    ,   std::ptrdiff_t
    ,   void    // By-Value Temporary reference
    ,   int     // By-Value Temporary reference
    >
{
public: // types
    typedef int_forward_iterator                            class_type;

public: // construction
    explicit
    int_forward_iterator(int const* pi)
        : m_pi(pi)
    {}
    int_forward_iterator(class_type& rhs)
        : m_pi(rhs.m_pi)
    {}
private:
    void operator =(class_type const&) STLSOFT_COPY_ASSIGNMENT_PROSCRIBED;

public: // operators
    class_type& operator ++()
    {
        ++m_pi;

        return *this;
    }

    value_type operator *() const
    {
        return *m_pi;
    }

    bool operator ==(class_type const& rhs) const
    {
        return m_pi == rhs.m_pi;
    }

    bool operator !=(class_type const& rhs) const
    {
        return !operator ==(rhs);
    }

/// Members
private:
    int const* m_pi;
};


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    // auto_buffer(size_t)
    static void test_ctor_n_1();
    static void test_ctor_n_2();
    static void test_ctor_n_3();
    // auto_buffer(size_t)
    static void test_ctor_n_v_1();
    static void test_ctor_n_v_2();
    static void test_ctor_n_v_3();
    static void test_ctor_n_v_4();
#if __cplusplus >= 201103L

    static void test_ctor_initlist_1();
    static void test_ctor_initlist_2();
    static void test_ctor_initlist_3();
#endif
#ifdef STLSOFT_CF_RVALUE_REFERENCES_SUPPORT

    static void test_ctor_move_1();
    static void test_ctor_move_2();
    static void test_ctor_move_3();
    static void test_ctor_move_4();
#endif /* STLSOFT_CF_RVALUE_REFERENCES_SUPPORT */
    static void test_ctor_range_pointers_1();
    static void test_ctor_range_pointers_2();
    static void test_ctor_range_pointers_3();
#if __cplusplus >= 201703L

    static void test_ctor_range_vec_iters_1();
    static void test_ctor_range_vec_iters_2();
    static void test_ctor_range_vec_iters_3();
    static void test_ctor_range_list_iters_1();
    static void test_ctor_range_list_iters_2();
    static void test_ctor_range_list_iters_3();
    static void test_ctor_range_input_iters_1();
    static void test_ctor_range_input_iters_2();
    static void test_ctor_range_input_iters_3();
    static void test_ctor_range_fwd_iters_1();
    static void test_ctor_range_fwd_iters_2();
    static void test_ctor_range_fwd_iters_3();
#endif

    // resize(size_t)
    static void test_resize();
    // resize(size_t, value)
    static void test_resize_n_v_1();
    static void test_resize_n_v_2();
    static void test_resize_n_v_3();

    static void test_allocator_null();
#ifdef ATTEMPT_ALLOCATOR_EXHAUSTION

    static void test_allocator_to_exhaustion();
#endif

    // copy_from(class_type const&)
    static void test_copy_from();

    // swap(class_type&&)
    static void test_swap_1();
    static void test_swap_2();
    static void test_swap_3();

    // operator [](size_t) {const}
    static void test_subscript();

    // data() {const}
    static void test_data();

    // front() {const}
    // back() {const}
    static void test_front_and_back();

    // begin() {const}
    // end() {const}
    static void test_begin_and_end();
    // rbegin() {const}
    // rend() {const}
    static void test_rbegin_and_rend();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.memory.auto_buffer", verbosity))
    {
        XTESTS_RUN_CASE(test_ctor_n_1);
        XTESTS_RUN_CASE(test_ctor_n_2);
        XTESTS_RUN_CASE(test_ctor_n_3);
        XTESTS_RUN_CASE(test_ctor_n_v_1);
        XTESTS_RUN_CASE(test_ctor_n_v_2);
        XTESTS_RUN_CASE(test_ctor_n_v_3);
        XTESTS_RUN_CASE(test_ctor_n_v_4);
#if __cplusplus >= 201103L

        XTESTS_RUN_CASE(test_ctor_initlist_1);
        XTESTS_RUN_CASE(test_ctor_initlist_2);
        XTESTS_RUN_CASE(test_ctor_initlist_3);
#endif
#ifdef STLSOFT_CF_RVALUE_REFERENCES_SUPPORT

        XTESTS_RUN_CASE(test_ctor_move_1);
        XTESTS_RUN_CASE(test_ctor_move_2);
        XTESTS_RUN_CASE(test_ctor_move_3);
        XTESTS_RUN_CASE(test_ctor_move_4);
#endif /* STLSOFT_CF_RVALUE_REFERENCES_SUPPORT */
        XTESTS_RUN_CASE(test_ctor_range_pointers_1);
        XTESTS_RUN_CASE(test_ctor_range_pointers_2);
        XTESTS_RUN_CASE(test_ctor_range_pointers_3);
#if __cplusplus >= 201703L

        XTESTS_RUN_CASE(test_ctor_range_vec_iters_1);
        XTESTS_RUN_CASE(test_ctor_range_vec_iters_2);
        XTESTS_RUN_CASE(test_ctor_range_vec_iters_3);
        XTESTS_RUN_CASE(test_ctor_range_list_iters_1);
        XTESTS_RUN_CASE(test_ctor_range_list_iters_2);
        XTESTS_RUN_CASE(test_ctor_range_list_iters_3);
        XTESTS_RUN_CASE(test_ctor_range_input_iters_1);
        XTESTS_RUN_CASE(test_ctor_range_input_iters_2);
        XTESTS_RUN_CASE(test_ctor_range_input_iters_3);
        XTESTS_RUN_CASE(test_ctor_range_fwd_iters_1);
        XTESTS_RUN_CASE(test_ctor_range_fwd_iters_2);
        XTESTS_RUN_CASE(test_ctor_range_fwd_iters_3);
#endif

        XTESTS_RUN_CASE(test_resize);
        XTESTS_RUN_CASE(test_resize_n_v_1);
        XTESTS_RUN_CASE(test_resize_n_v_2);
        XTESTS_RUN_CASE(test_resize_n_v_3);

        XTESTS_RUN_CASE(test_allocator_null);
#ifdef ATTEMPT_ALLOCATOR_EXHAUSTION

        XTESTS_RUN_CASE(test_allocator_to_exhaustion);
#endif

        XTESTS_RUN_CASE(test_copy_from);

        XTESTS_RUN_CASE(test_swap_1);
        XTESTS_RUN_CASE(test_swap_2);
        XTESTS_RUN_CASE(test_swap_3);

        XTESTS_RUN_CASE(test_subscript);

        XTESTS_RUN_CASE(test_data);

        XTESTS_RUN_CASE(test_front_and_back);

        XTESTS_RUN_CASE(test_begin_and_end);
        XTESTS_RUN_CASE(test_rbegin_and_rend);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    const int INTEGERS[] = {
         0,  1,  2,  3,  4,  5,  6,  7,  8,  9
    ,   10, 11, 12, 13, 14, 15, 16, 17, 18, 19
    ,   20, 21, 22, 23, 24, 25, 26, 27, 28, 29
    ,   30, 31, 32, 33, 34, 35, 36, 37, 38, 39
    ,   40, 41, 42, 43, 44, 45, 46, 47, 48, 49
    ,   50, 51, 52, 53, 54, 55, 56, 57, 58, 59
    ,   60, 61, 62, 63, 64, 65, 66, 67, 68, 69
    ,   70, 71, 72, 73, 74, 75, 76, 77, 78, 79
    ,   80, 81, 82, 83, 84, 85, 86, 87, 88, 89
    ,   90, 91, 92, 93, 94, 95, 96, 97, 98, 99
    };


static void test_ctor_n_1()
{
#if __cplusplus >= 202002L
    static
    ss_constexpr_2020_k
#endif
    stlsoft::auto_buffer<char> buff(0);

    TEST_INT_EQ(0u, buff.size());
    TEST_BOOLEAN_TRUE(buff.empty());
    TEST_INT_NE(0u, buff.internal_size());
}

static void test_ctor_n_2()
{
#if __cplusplus >= 202002L
    static
    ss_constexpr_2020_k
#endif
    stlsoft::auto_buffer<char, 10> buff(0);

    TEST_INT_EQ(0u, buff.size());
    TEST_BOOLEAN_TRUE(buff.empty());
    TEST_INT_EQ(10u, buff.internal_size());
}

static void test_ctor_n_3()
{
#if __cplusplus >= 202002L
    static
    ss_constexpr_2020_k
#endif
    stlsoft::auto_buffer<char, 10> buff(10);

    TEST_INT_EQ(10u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_INT_EQ(10u, buff.internal_size());
}

static void test_ctor_n_v_1()
{
#if __cplusplus >= 202002L
    static
    ss_constexpr_2020_k
#endif
    stlsoft::auto_buffer<char> buff(0, 'a');

    TEST_INT_EQ(0u, buff.size());
    TEST_BOOLEAN_TRUE(buff.empty());
    TEST_INT_NE(0u, buff.internal_size());
}

static void test_ctor_n_v_2()
{
#if __cplusplus >= 202002L
    static
    ss_constexpr_2020_k
#endif
    stlsoft::auto_buffer<char, 10> buff(0, 'a');

    TEST_INT_EQ(0u, buff.size());
    TEST_BOOLEAN_TRUE(buff.empty());
    TEST_INT_EQ(10u, buff.internal_size());
}

static void test_ctor_n_v_3()
{
#if __cplusplus >= 202002L
    static
    ss_constexpr_2020_k
#endif
    stlsoft::auto_buffer<char, 10> buff(10, 'a');

    TEST_INT_EQ(10u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_INT_EQ(10u, buff.internal_size());

    TEST_CHAR_EQ('a', buff[0]);
    TEST_CHAR_EQ('a', buff[9]);
}

static void test_ctor_n_v_4()
{
#if __cplusplus >= 202002L
    static
    ss_constexpr_2020_k
#endif
    stlsoft::auto_buffer<int, 10> buff(10u, 123);

    TEST_INT_EQ(10u, buff.size());
    TEST_INT_EQ(10u, buff.internal_size());

    TEST_INT_EQ(1230, std::accumulate(buff.begin(), buff.end(), 0));
    TEST_INT_EQ(1230, std::accumulate(buff.cbegin(), buff.cend(), 0));
}

#if __cplusplus >= 201103L

static void test_ctor_initlist_1()
{
    stlsoft::auto_buffer<int, 10> buff = {};

    TEST_INT_EQ(0u, buff.size());
    TEST_INT_EQ(10u, buff.internal_size());
}


static void test_ctor_initlist_2()
{
    stlsoft::auto_buffer<int, 10> buff = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    TEST_INT_EQ(10u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_INT_EQ(10u, buff.internal_size());

    TEST_INT_EQ(0, buff[0]);
    TEST_INT_EQ(9, buff[9]);
}

static void test_ctor_initlist_3()
{
    stlsoft::auto_buffer<int, 10> buff = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    TEST_INT_EQ(11u, buff.size());
    TEST_INT_EQ(10u, buff.internal_size());

    TEST_INT_EQ(0, buff[0]);
    TEST_INT_EQ(9, buff[9]);
    TEST_INT_EQ(10, buff[10]);
}
#endif
#ifdef STLSOFT_CF_RVALUE_REFERENCES_SUPPORT

static void test_ctor_move_1()
{
    stlsoft::auto_buffer<char> rhs(0, 'a');
    stlsoft::auto_buffer<char> buff(std::move(rhs));

    TEST_INT_EQ(0u, buff.size());
    TEST_BOOLEAN_TRUE(buff.empty());
    TEST_INT_NE(0u, buff.internal_size());
}

static void test_ctor_move_2()
{
    stlsoft::auto_buffer<char, 10> rhs(0, 'a');
    stlsoft::auto_buffer<char, 10> buff(std::move(rhs));

    TEST_INT_EQ(0u, buff.size());
    TEST_BOOLEAN_TRUE(buff.empty());
    TEST_INT_EQ(10u, buff.internal_size());
}

static void test_ctor_move_3()
{
    stlsoft::auto_buffer<char, 10> rhs(10, 'a');
    stlsoft::auto_buffer<char, 10> buff(std::move(rhs));

    TEST_INT_EQ(10u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_INT_EQ(10u, buff.internal_size());

    TEST_CHAR_EQ('a', buff[0]);
    TEST_CHAR_EQ('a', buff[9]);
}

static void test_ctor_move_4()
{
    stlsoft::auto_buffer<int, 10> buff(10u, 123);

    TEST_INT_EQ(10u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_INT_EQ(10u, buff.internal_size());

    TEST_INT_EQ(1230, std::accumulate(buff.begin(), buff.end(), 0));

    stlsoft::auto_buffer<int, 10> buff2(std::move(buff));

    TEST_INT_EQ(0u, buff.size());
    TEST_INT_EQ(10u, buff.internal_size());
    TEST_INT_EQ(0, std::accumulate(buff.begin(), buff.end(), 0));

    TEST_INT_EQ(10u, buff2.size());
    TEST_INT_EQ(10u, buff2.internal_size());

    TEST_INT_EQ(1230, std::accumulate(buff2.begin(), buff2.end(), 0));
}
#endif /* STLSOFT_CF_RVALUE_REFERENCES_SUPPORT */

static void test_ctor_range_pointers_1()
{
    stlsoft::auto_buffer<int> buff(&INTEGERS[0], &INTEGERS[0] + 0);

    TEST_INT_EQ(0u, buff.size());
    TEST_INT_NE(0u, buff.internal_size());
    TEST_INT_EQ(0, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_pointers_2()
{
    stlsoft::auto_buffer<int, 10> buff(&INTEGERS[0] + 0, &INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS));

    TEST_INT_EQ(100u, buff.size());
    TEST_INT_EQ(10u, buff.internal_size());
    TEST_INT_EQ(4950, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_pointers_3()
{
    stlsoft::auto_buffer<int, 100> buff(&INTEGERS[0], &INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS));

    TEST_INT_EQ(100u, buff.size());
    TEST_INT_EQ(100u, buff.internal_size());
    TEST_INT_EQ(4950, std::accumulate(buff.begin(), buff.end(), 0));
}

#if __cplusplus >= 201703L

static void test_ctor_range_vec_iters_1()
{
    std::vector<int>                src(&INTEGERS[0], &INTEGERS[0] + 0);
    stlsoft::auto_buffer<int, 10>   buff(src.begin(), src.end());

    TEST_INT_EQ(0u, buff.size());
    TEST_INT_NE(0u, buff.internal_size());
    TEST_INT_EQ(0, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_vec_iters_2()
{
    std::vector<int>                src(&INTEGERS[0], &INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS));
    stlsoft::auto_buffer<int, 10>   buff(src.begin(), src.end());

    TEST_INT_EQ(100u, buff.size());
    TEST_INT_EQ(10u, buff.internal_size());
    TEST_INT_EQ(4950, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_vec_iters_3()
{
    std::vector<int>                src(&INTEGERS[0], &INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS));
    stlsoft::auto_buffer<int, 100>  buff(src.begin(), src.end());

    TEST_INT_EQ(100u, buff.size());
    TEST_INT_EQ(100u, buff.internal_size());
    TEST_INT_EQ(4950, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_list_iters_1()
{
    std::list<int>                  src(&INTEGERS[0], &INTEGERS[0] + 0);
    stlsoft::auto_buffer<int, 10>   buff(src.begin(), src.end());

    TEST_INT_EQ(0u, buff.size());
    TEST_INT_NE(0u, buff.internal_size());
    TEST_INT_EQ(0, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_list_iters_2()
{
    std::list<int>                  src(&INTEGERS[0], &INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS));
    stlsoft::auto_buffer<int, 10>   buff(src.begin(), src.end());

    TEST_INT_EQ(100u, buff.size());
    TEST_INT_EQ(10u, buff.internal_size());
    TEST_INT_EQ(4950, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_list_iters_3()
{
    std::list<int>                  src(&INTEGERS[0], &INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS));
    stlsoft::auto_buffer<int, 100>  buff(src.begin(), src.end());

    TEST_INT_EQ(100u, buff.size());
    TEST_INT_EQ(100u, buff.internal_size());
    TEST_INT_EQ(4950, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_input_iters_1()
{
# if defined(STLSOFT_COMPILER_IS_MSVC) &&\
     __cplusplus >= 202002L

    auto from = int_input_iterator(&INTEGERS[0] + 0);
    auto to = int_input_iterator(&INTEGERS[0] + 0);

    stlsoft::auto_buffer<int, 10>   buff(from, to);
# else

    stlsoft::auto_buffer<int, 10>   buff(int_input_iterator(&INTEGERS[0] + 0), int_input_iterator(&INTEGERS[0] + 0));
# endif

    TEST_INT_EQ(0u, buff.size());
    TEST_INT_NE(0u, buff.internal_size());
    TEST_INT_EQ(0, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_input_iters_2()
{
# if defined(STLSOFT_COMPILER_IS_MSVC) &&\
     __cplusplus >= 202002L

    auto from = int_input_iterator(&INTEGERS[0] + 0);
    auto to = int_input_iterator(&INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS));

    stlsoft::auto_buffer<int, 10>   buff(from, to);
# else

    stlsoft::auto_buffer<int, 10>   buff(int_input_iterator(&INTEGERS[0] + 0), int_input_iterator(&INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS)));
# endif

    TEST_INT_EQ(100u, buff.size());
    TEST_INT_EQ(10u, buff.internal_size());
    TEST_INT_EQ(4950, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_input_iters_3()
{
# if defined(STLSOFT_COMPILER_IS_MSVC) &&\
     __cplusplus >= 202002L

    auto from = int_input_iterator(&INTEGERS[0] + 0);
    auto to = int_input_iterator(&INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS));

    stlsoft::auto_buffer<int, 100>   buff(from, to);
# else
    stlsoft::auto_buffer<int, 100>  buff(int_input_iterator(&INTEGERS[0] + 0), int_input_iterator(&INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS)));
# endif

    TEST_INT_EQ(100u, buff.size());
    TEST_INT_EQ(100u, buff.internal_size());
    TEST_INT_EQ(4950, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_fwd_iters_1()
{
# if defined(STLSOFT_COMPILER_IS_MSVC) &&\
     __cplusplus >= 202002L

    auto from = int_forward_iterator(&INTEGERS[0] + 0);
    auto to = int_forward_iterator(&INTEGERS[0] + 0);

    stlsoft::auto_buffer<int, 10>   buff(from, to);
# else

    stlsoft::auto_buffer<int, 10>   buff(int_forward_iterator(&INTEGERS[0] + 0), int_forward_iterator(&INTEGERS[0] + 0));
# endif

    TEST_INT_EQ(0u, buff.size());
    TEST_INT_NE(0u, buff.internal_size());
    TEST_INT_EQ(0, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_fwd_iters_2()
{
# if defined(STLSOFT_COMPILER_IS_MSVC) &&\
     __cplusplus >= 202002L

    auto from = int_forward_iterator(&INTEGERS[0] + 0);
    auto to = int_forward_iterator(&INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS));

    stlsoft::auto_buffer<int, 10>   buff(from, to);
# else

    stlsoft::auto_buffer<int, 10>   buff(int_forward_iterator(&INTEGERS[0] + 0), int_forward_iterator(&INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS)));
# endif

    TEST_INT_EQ(100u, buff.size());
    TEST_INT_EQ(10u, buff.internal_size());
    TEST_INT_EQ(4950, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_ctor_range_fwd_iters_3()
{
# if defined(STLSOFT_COMPILER_IS_MSVC) &&\
     __cplusplus >= 202002L

    auto from = int_forward_iterator(&INTEGERS[0] + 0);
    auto to = int_forward_iterator(&INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS));

    stlsoft::auto_buffer<int, 100>   buff(from, to);
# else

    stlsoft::auto_buffer<int, 100>  buff(int_forward_iterator(&INTEGERS[0] + 0), int_forward_iterator(&INTEGERS[0] + STLSOFT_NUM_ELEMENTS(INTEGERS)));
# endif

    TEST_INT_EQ(100u, buff.size());
    TEST_INT_EQ(100u, buff.internal_size());
    TEST_INT_EQ(4950, std::accumulate(buff.begin(), buff.end(), 0));
}
#endif

static void test_resize()
{
    stlsoft::auto_buffer<char, 10>      buff(1u);

    char* const first = buff.data();

    { for (size_t i = 0; i != buff.internal_size(); ++i)
    {
        buff.resize(i);

        TEST_INT_EQ(i, buff.size());
        TEST_PTR_EQ(first, buff.data());
    }}

    { for (size_t i = 1u + buff.internal_size(); i != 10000; ++i)
    {
        buff.resize(i);

        TEST_INT_EQ(i, buff.size());
        TEST_PTR_NE(first, buff.data());
    }}
}

static void test_resize_n_v_1()
{
    typedef stlsoft::auto_buffer<int, 10> ab_int_10_t;

    ab_int_10_t buff(0u, -9);

    TEST_INT_EQ(0u, buff.size());
    TEST_BOOLEAN_TRUE(buff.empty());
    TEST_INT_EQ(0, std::accumulate(buff.begin(), buff.end(), 0));

    int* const p0 = buff.data();

    buff.resize(4, 1);

    TEST_INT_EQ(4u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_PTR_EQ(p0, buff.data());
    TEST_INT_EQ(4, std::accumulate(buff.begin(), buff.end(), 0));

    buff.resize(8, 10);

    TEST_INT_EQ(8u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_PTR_EQ(p0, buff.data());
    TEST_INT_EQ(44, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_resize_n_v_2()
{
    typedef stlsoft::auto_buffer<int, 10> ab_int_10_t;

    ab_int_10_t buff(5u, -9);

    TEST_INT_EQ(5u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_INT_EQ(-45, std::accumulate(buff.begin(), buff.end(), 0));

    int* const p0 = buff.data();

    buff.resize(10, -5);

    TEST_INT_EQ(10u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_PTR_EQ(p0, buff.data());
    TEST_INT_EQ(-70, std::accumulate(buff.begin(), buff.end(), 0));

    buff.resize(5, 9999);

    TEST_INT_EQ(5u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_PTR_EQ(p0, buff.data());
    TEST_INT_EQ(-45, std::accumulate(buff.begin(), buff.end(), 0));

    buff.resize(11, 100);

    TEST_INT_EQ(11u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_PTR_NE(p0, buff.data());
    TEST_INT_EQ(555, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_resize_n_v_3()
{
    typedef stlsoft::auto_buffer<int, 10> ab_int_10_t;

    ab_int_10_t buff(100u, -9);

    TEST_INT_EQ(100u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_INT_EQ(-900, std::accumulate(buff.begin(), buff.end(), 0));

    int* const p0 = buff.data();

    buff.resize(10, 9999);

    TEST_INT_EQ(10u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_PTR_EQ(p0, buff.data());
    TEST_INT_EQ(-90, std::accumulate(buff.begin(), buff.end(), 0));

    buff.resize(5, 9999);

    TEST_INT_EQ(5u, buff.size());
    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_PTR_EQ(p0, buff.data());
    TEST_INT_EQ(-45, std::accumulate(buff.begin(), buff.end(), 0));

    buff.resize(0, 9999);

    TEST_INT_EQ(0u, buff.size());
    TEST_BOOLEAN_TRUE(buff.empty());
    TEST_PTR_NE(p0, buff.data());
    TEST_INT_EQ(0, std::accumulate(buff.begin(), buff.end(), 0));
}

static void test_allocator_null()
{
    typedef stlsoft::null_allocator<char>                   ator_t;
    typedef stlsoft::auto_buffer<char, 10, ator_t>          buff_10_t;
    typedef stlsoft::auto_buffer<char, 100, ator_t>         buff_100_t;
    typedef stlsoft::auto_buffer<char, 1000, ator_t>        buff_1000_t;

    size_t  size = 1;

    { for (size_t i = 0; i != 32; ++i, size <<= 1)
    {
        try
        {
            buff_10_t buff(size);

            TEST_INT_LE(buff_10_t::internal_size(), size);
        }
        catch (std::bad_alloc&)
        {
            TEST_INT_GT(buff_10_t::internal_size(), size);
        }

        try
        {
            buff_100_t buff(size);

            TEST_INT_LE(buff_100_t::internal_size(), size);
        }
        catch (std::bad_alloc&)
        {
            TEST_INT_GT(buff_100_t::internal_size(), size);
        }

        try
        {
            buff_1000_t buff(size);

            TEST_INT_LE(buff_1000_t::internal_size(), size);
        }
        catch (std::bad_alloc&)
        {
            TEST_INT_GT(buff_1000_t::internal_size(), size);
        }

    }}
}
#ifdef ATTEMPT_ALLOCATOR_EXHAUSTION

static void test_allocator_to_exhaustion()
{
    stlsoft::auto_buffer<char, 10>::allocator_type  ator;
    stlsoft::auto_buffer<char, 10>                  buff(0);

    std::vector<char*>  buffers;

    size_t  size = 1;

    { for (size_t i = 0; i != 32; ++i, size <<= 1)
    {
        try
        {
# ifdef STLSOFT_LF_ALLOCATOR_ALLOCATE_HAS_HINT
            char* p = ator.allocate(size, NULL);
# else /* ? STLSOFT_LF_ALLOCATOR_ALLOCATE_HAS_HINT */
            char* p = ator.allocate(size);
# endif /* STLSOFT_LF_ALLOCATOR_ALLOCATE_HAS_HINT */

            if (NULL != p)
            {
                buffers.push_back(p);
            }
        }
        catch (std::bad_alloc&)
        {}
    }}

    // Now we're close to exhaustion
    size = 1;

    { for (size_t i = 0; i != 32; ++i, size <<= 1)
    {
# ifdef STLSOFT_CF_THROW_BAD_ALLOC
        try
        {
            TEST_BOOLEAN_TRUE(buff.resize(size));
        }
        catch (std::bad_alloc&)
        {}
# endif /* !STLSOFT_CF_THROW_BAD_ALLOC */
    }}

    { for (std::vector<char*>::iterator b = buffers.begin(); b != buffers.end(); ++b)
    {
        ator.deallocate(*b, 0u);
    }}
}
#endif

static void test_copy_from()
{
    typedef stlsoft::auto_buffer<int, 8> ab_int_8_t;

    int const ints[] = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4 };

    ab_int_8_t          buff(STLSOFT_NUM_ELEMENTS(ints));
    ab_int_8_t const&   cbuff = buff;

    assert(buff.size() >= STLSOFT_NUM_ELEMENTS(ints));
    std::copy(
#if __cplusplus >= 201103L
        std::begin(ints), std::end(ints)
#else
        &ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints)
#endif
    ,   buff.begin()
    );

    TEST_BOOLEAN_FALSE(buff.empty());
    TEST_INT_EQ(10u, buff.size());
    TEST_INT_EQ(-5, std::accumulate(cbuff.begin(), cbuff.end(), 0));
    TEST_INT_EQ(-5, std::accumulate(cbuff.cbegin(), cbuff.cend(), 0));


    ab_int_8_t  buff2(0);

    TEST_BOOLEAN_TRUE(buff2.empty());
    TEST_INT_EQ(0u, buff2.size());
    TEST_INT_EQ(0, std::accumulate(buff2.rbegin(), buff2.rend(), 0));
    TEST_INT_EQ(0, std::accumulate(buff2.crbegin(), buff2.crend(), 0));

    buff2.copy_from(cbuff);

    TEST_BOOLEAN_FALSE(buff2.empty());
    TEST_INT_EQ(10u, buff2.size());
    TEST_INT_EQ(-5, std::accumulate(buff2.rbegin(), buff2.rend(), 0));
}

static void test_swap_1()
{
    // ab1.swap(ab2)
    {
        stlsoft::auto_buffer<int, 10>   ab1(10);
        stlsoft::auto_buffer<int, 10>   ab2(8);

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            ab1[i] = int(i);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            ab2[i] = -int(i);
        }}

        TEST_INT_EQ(10u, ab1.size());
        TEST_INT_EQ(8u,  ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab2[i]);
        }}


        ab1.swap(ab2);

        TEST_INT_EQ(8u, ab1.size());
        TEST_INT_EQ(10u,  ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab2[i]);
        }}
    }

    // ab2.swap(ab1)
    {
        stlsoft::auto_buffer<int, 10>   ab1(10);
        stlsoft::auto_buffer<int, 10>   ab2(8);

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            ab1[i] = int(i);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            ab2[i] = -int(i);
        }}

        TEST_INT_EQ(10u, ab1.size());
        TEST_INT_EQ(8u,  ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab2[i]);
        }}


        ab2.swap(ab1);

        TEST_INT_EQ(8u, ab1.size());
        TEST_INT_EQ(10u,  ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab2[i]);
        }}
    }
}

static void test_swap_2()
{
    // ab1.swap(ab2)
    {
        stlsoft::auto_buffer<int, 10>   ab1(50);
        stlsoft::auto_buffer<int, 10>   ab2(8);

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            ab1[i] = int(i);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            ab2[i] = -int(i);
        }}

        TEST_INT_EQ(50u, ab1.size());
        TEST_INT_EQ(8u,  ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab2[i]);
        }}


        ab1.swap(ab2);

        TEST_INT_EQ(8u, ab1.size());
        TEST_INT_EQ(50u,  ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab2[i]);
        }}
    }

    // ab2.swap(ab1)
    {
        stlsoft::auto_buffer<int, 10>   ab1(10);
        stlsoft::auto_buffer<int, 10>   ab2(8);

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            ab1[i] = int(i);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            ab2[i] = -int(i);
        }}

        TEST_INT_EQ(10u, ab1.size());
        TEST_INT_EQ(8u,  ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab2[i]);
        }}


        ab2.swap(ab1);

        TEST_INT_EQ(8u,  ab1.size());
        TEST_INT_EQ(10u, ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab2[i]);
        }}
    }
}

static void test_swap_3()
{
    // ab1.swap(ab2)
    {
        stlsoft::auto_buffer<int, 10>   ab1(50);
        stlsoft::auto_buffer<int, 10>   ab2(8);

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            ab1[i] = int(i);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            ab2[i] = -int(i);
        }}

        TEST_INT_EQ(50u, ab1.size());
        TEST_INT_EQ(8u,  ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab2[i]);
        }}


        ab1.swap(ab2);

        TEST_INT_EQ(8u,  ab1.size());
        TEST_INT_EQ(50u, ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab2[i]);
        }}
    }

    // ab2.swap(ab1)
    {
        stlsoft::auto_buffer<int, 10>   ab1(10);
        stlsoft::auto_buffer<int, 10>   ab2(18);

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            ab1[i] = int(i);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            ab2[i] = -int(i);
        }}

        TEST_INT_EQ(10u, ab1.size());
        TEST_INT_EQ(18u, ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab2[i]);
        }}


        ab2.swap(ab1);

        TEST_INT_EQ(18u, ab1.size());
        TEST_INT_EQ(10u, ab2.size());

        { for (size_t i = 0; i != ab1.size(); ++i)
        {
            TEST_INT_EQ(-int(i), ab1[i]);
        }}

        { for (size_t i = 0; i != ab2.size(); ++i)
        {
            TEST_INT_EQ(int(i), ab2[i]);
        }}
    }
}

static void test_subscript()
{
    typedef stlsoft::auto_buffer<int, 8> ab_int_8_t;

    int const ints[] = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4 };

    ab_int_8_t          buff(STLSOFT_NUM_ELEMENTS(ints));
    ab_int_8_t const&   cbuff = buff;

    assert(buff.size() >= STLSOFT_NUM_ELEMENTS(ints));
    std::copy(
#if __cplusplus >= 201103L
        std::begin(ints), std::end(ints)
#else
        &ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints)
#endif
    ,   buff.begin()
    );

    for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(ints); ++i)
    {
        TEST_INT_EQ(ints[i], buff[i]);
        TEST_INT_EQ(ints[i], cbuff[i]);
    }
}

static void test_data()
{
    typedef stlsoft::auto_buffer<int, 8> ab_int_8_t;

    int const ints[] = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4 };

    ab_int_8_t          buff(STLSOFT_NUM_ELEMENTS(ints));
    ab_int_8_t const&   cbuff = buff;

    assert(buff.size() >= STLSOFT_NUM_ELEMENTS(ints));
    std::copy(
#if __cplusplus >= 201103L
        std::begin(ints), std::end(ints)
#else
        &ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints)
#endif
    ,   buff.begin()
    );

    TEST(0 == memcmp(&ints[0], buff.data(), sizeof(ints)));
    TEST(0 == memcmp(&ints[0], cbuff.data(), sizeof(ints)));
}

static void test_front_and_back()
{
    typedef stlsoft::auto_buffer<int, 8> ab_int_8_t;

    int const ints[] = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4 };

    ab_int_8_t          buff(STLSOFT_NUM_ELEMENTS(ints));
    ab_int_8_t const&   cbuff = buff;

    assert(buff.size() >= STLSOFT_NUM_ELEMENTS(ints));
    std::copy(
#if __cplusplus >= 201103L
        std::begin(ints), std::end(ints)
#else
        &ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints)
#endif
    ,   buff.begin()
    );

    TEST_INT_EQ(-5, buff.front());
    TEST_INT_EQ(-5, cbuff.front());

    TEST_INT_EQ(4, buff.back());
    TEST_INT_EQ(4, cbuff.back());
}

static void test_begin_and_end()
{
    typedef stlsoft::auto_buffer<int, 8> ab_int_8_t;

    int const ints[] = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4 };

    ab_int_8_t          buff(STLSOFT_NUM_ELEMENTS(ints));
    ab_int_8_t const&   cbuff = buff;

    assert(buff.size() >= STLSOFT_NUM_ELEMENTS(ints));
    std::copy(
#if __cplusplus >= 201103L
        std::begin(ints), std::end(ints)
#else
        &ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints)
#endif
    ,   buff.begin()
    );

    TEST_INT_EQ(-5, std::accumulate(cbuff.begin(), cbuff.end(), 0));
    TEST_INT_EQ(4, std::accumulate(cbuff.begin() + 2, cbuff.end(), 0));
    TEST_INT_EQ(-9, std::accumulate(cbuff.begin(), cbuff.end() -1, 0));
}

static void test_rbegin_and_rend()
{
    typedef stlsoft::auto_buffer<int, 8> ab_int_8_t;

    int const ints[] = { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4 };

    ab_int_8_t          buff(STLSOFT_NUM_ELEMENTS(ints));
    ab_int_8_t const&   cbuff = buff;

    assert(buff.size() >= STLSOFT_NUM_ELEMENTS(ints));
    std::copy(
#if __cplusplus >= 201103L
        std::begin(ints), std::end(ints)
#else
        &ints[0], &ints[0] + STLSOFT_NUM_ELEMENTS(ints)
#endif
    ,   buff.begin()
    );

    TEST_INT_EQ(-5, std::accumulate(cbuff.rbegin(), cbuff.rend(), 0));
    TEST_INT_EQ(-5, std::accumulate(cbuff.rbegin() + 0, cbuff.rend() + 0, 0));
    TEST_INT_EQ(4, std::accumulate(cbuff.rbegin() + 0, cbuff.rend() - 2, 0));
    TEST_INT_EQ(-9, std::accumulate(cbuff.rbegin() + 1, cbuff.rend() - 0, 0));

    TEST_INT_EQ(-5, std::accumulate(cbuff.crbegin(), cbuff.crend(), 0));
    TEST_INT_EQ(-5, std::accumulate(cbuff.crbegin() + 0, cbuff.crend() + 0, 0));
    TEST_INT_EQ(4, std::accumulate(cbuff.crbegin() + 0, cbuff.crend() - 2, 0));
    TEST_INT_EQ(-9, std::accumulate(cbuff.crbegin() + 1, cbuff.crend() - 0, 0));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

