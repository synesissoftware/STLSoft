/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.string.simple_string/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::basic_simple_string`.
 *
 * Created: 4th November 2008
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */

// #define USE_std_string


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#ifdef _DEBUG
# define _CRT_SECURE_NO_DEPRECATE
# define _SCL_SECURE_NO_WARNINGS
#endif

#ifndef USE_std_string
# include <stlsoft/string/simple_string.hpp>
#endif /* !USE_std_string */
#include <stlsoft/string/char_traits.hpp>
#include <stlsoft/string/string_traits.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <iomanip>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    // construction

    static void test_ctor_default();
    static void test_ctor_copy();
    static void test_ctor_s_pos();
    static void test_ctor_s_pos_n();
    static void test_ctor_ccs();
    static void test_ctor_ccs_n();
    static void test_ctor_n_ch();
    static void test_ctor_range();
#ifndef USE_std_string
    static void test_ctor_range_2();
#endif /* !USE_std_string */


    // `assign()`

    static void test_assign_1();
    static void test_assign_2();
    static void test_assign_3();
#ifndef USE_std_string
    static void test_assign_4();
#endif /* !USE_std_string */


    // `append()`

    static void test_append_1();
    static void test_append_2();
    static void test_append_3();
#ifndef USE_std_string
    static void test_push_back();
#endif /* !USE_std_string */
    static void test_pop_back();


    // modifiers

    static void test_reserve();
    static void test_swap_1();
    static void test_swap_2();
    static void test_swap_3();
    static void test_resize();
#ifndef USE_std_string
    static void test_clear();
#endif /* !USE_std_string */
#ifdef USE_std_string
    static void test_erase_0_param();
    static void test_erase_1_pos();
    static void test_erase_pos_and_cch();
#endif

    // attributes

    static void test_size();
    static void test_max_size();
    static void test_length();
    static void test_capacity();
    static void test_empty();


    // comparison

    static void test_compare_1();
    static void test_compare_2();
    static void test_compare_3();
    static void test_compare_4();
    static void test_equality_operators_1();
#ifndef USE_std_string
    static void test_equal_p_n_ccs_n();
    static void test_equal_p_n_ccs();
    static void test_equal_ccs();
    static void test_equal_p_n_scr_p_n();
    static void test_equal_p_n_scr();
    static void test_equal_scr();
#endif /* !USE_std_string */
#if !defined(USE_std_string) || \
    __cplusplus >= 202002L
    static void test_starts_with_1();
    static void test_starts_with_2();
    static void test_contains_1();
    static void test_contains_2();
    static void test_contains_3();
    static void test_ends_with_1();
    static void test_ends_with_2();
#endif


    // accessors

    static void test_at_1();
    static void test_at_2();
    static void test_at_3();
    static void test_at_4();
    static void test_index_1();
    static void test_index_2();
    static void test_copy();
    static void test_substr();
    static void test_substr_throw();


    // search

#ifdef USE_std_string
    static void test_find_char();
    static void test_find_c_string();
    static void test_find_string();
    static void test_rfind_char();
    static void test_rfind_c_string();
    static void test_rfind_string();
    static void test_find_first_of_char();
    static void test_find_first_of_c_string();
    static void test_find_first_of_string();
    static void test_find_last_of_char();
    static void test_find_last_of_c_string();
    static void test_find_last_of_string();
    static void test_find_first_not_of_char();
    static void test_find_first_not_of_c_string();
    static void test_find_first_not_of_string();
    static void test_find_last_not_of_char();
    static void test_find_last_not_of_c_string();
    static void test_find_last_not_of_string();
#endif


    // traits

    static void test_stlsoft_char_traits();

    static void test_string_traits();


    // operators : concatenation

    static void test_concatenation_1();
    static void test_concatenation_2();
#ifdef USE_std_string
    static void test_concatenation_3();
    static void test_concatenation_4();
    static void test_concatenation_5();
#endif
    static void test_concatenation_6();


    // operators : insertion

    static void test_insertion_1();
    static void test_insertion_2();
    static void test_insertion_3();
    static void test_insertion_4();


    // shims : sas

    static void test_string_access_shims();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.simple_string", verbosity))
    {
        // construction

        XTESTS_RUN_CASE(test_ctor_default);
        XTESTS_RUN_CASE(test_ctor_copy);
        XTESTS_RUN_CASE(test_ctor_s_pos);
        XTESTS_RUN_CASE(test_ctor_s_pos_n);
        XTESTS_RUN_CASE(test_ctor_ccs);
        XTESTS_RUN_CASE(test_ctor_ccs_n);
        XTESTS_RUN_CASE(test_ctor_n_ch);
        XTESTS_RUN_CASE(test_ctor_range);
#ifndef USE_std_string
        XTESTS_RUN_CASE(test_ctor_range_2);
#endif /* !USE_std_string */


        // `assign()`

        XTESTS_RUN_CASE(test_assign_1);
        XTESTS_RUN_CASE(test_assign_2);
        XTESTS_RUN_CASE(test_assign_3);
#ifndef USE_std_string
        XTESTS_RUN_CASE(test_assign_4);
#endif /* !USE_std_string */


        // `append()`

        XTESTS_RUN_CASE(test_append_1);
        XTESTS_RUN_CASE(test_append_2);
        XTESTS_RUN_CASE_THAT_THROWS(test_append_3, std::out_of_range);
#ifndef USE_std_string
        XTESTS_RUN_CASE(test_push_back);
#endif /* !USE_std_string */
        XTESTS_RUN_CASE(test_pop_back);


        // modifiers

        XTESTS_RUN_CASE(test_reserve);
        XTESTS_RUN_CASE(test_swap_1);
        XTESTS_RUN_CASE(test_swap_2);
        XTESTS_RUN_CASE(test_swap_3);
        XTESTS_RUN_CASE(test_resize);
#ifndef USE_std_string
        XTESTS_RUN_CASE(test_clear);
#endif /* !USE_std_string */
#ifdef USE_std_string
        XTESTS_RUN_CASE(test_erase_0_param);
        XTESTS_RUN_CASE(test_erase_1_pos);
        XTESTS_RUN_CASE(test_erase_pos_and_cch);
#endif

        // attributes

        XTESTS_RUN_CASE(test_size);
        XTESTS_RUN_CASE(test_max_size);
        XTESTS_RUN_CASE(test_length);
        XTESTS_RUN_CASE(test_capacity);
        XTESTS_RUN_CASE(test_empty);


        // comparison

        XTESTS_RUN_CASE(test_compare_1);
        XTESTS_RUN_CASE(test_compare_2);
        XTESTS_RUN_CASE(test_compare_3);
        XTESTS_RUN_CASE(test_compare_4);
        XTESTS_RUN_CASE(test_equality_operators_1);
#ifndef USE_std_string
        XTESTS_RUN_CASE(test_equal_p_n_ccs_n);
        XTESTS_RUN_CASE(test_equal_p_n_ccs);
        XTESTS_RUN_CASE(test_equal_ccs);
        XTESTS_RUN_CASE(test_equal_p_n_scr_p_n);
        XTESTS_RUN_CASE(test_equal_p_n_scr);
        XTESTS_RUN_CASE(test_equal_scr);
#endif /* !USE_std_string */

#if !defined(USE_std_string) || \
    __cplusplus >= 202002L
        XTESTS_RUN_CASE(test_starts_with_1);
        XTESTS_RUN_CASE(test_starts_with_2);
        XTESTS_RUN_CASE(test_contains_1);
        XTESTS_RUN_CASE(test_contains_2);
        XTESTS_RUN_CASE(test_contains_3);
        XTESTS_RUN_CASE(test_ends_with_1);
        XTESTS_RUN_CASE(test_ends_with_2);
#endif


        // accessors

        XTESTS_RUN_CASE(test_at_1);
        XTESTS_RUN_CASE(test_at_2);
        XTESTS_RUN_CASE_THAT_THROWS(test_at_3, std::out_of_range);
        XTESTS_RUN_CASE_THAT_THROWS(test_at_4, std::out_of_range);
        XTESTS_RUN_CASE(test_index_1);
        XTESTS_RUN_CASE(test_index_2);
        XTESTS_RUN_CASE(test_copy);
        XTESTS_RUN_CASE(test_substr);
        XTESTS_RUN_CASE_THAT_THROWS(test_substr_throw, std::out_of_range);


        // search

#ifdef USE_std_string
        XTESTS_RUN_CASE(test_find_char);
        XTESTS_RUN_CASE(test_find_c_string);
        XTESTS_RUN_CASE(test_find_string);
        XTESTS_RUN_CASE(test_rfind_char);
        XTESTS_RUN_CASE(test_rfind_c_string);
        XTESTS_RUN_CASE(test_rfind_string);
        XTESTS_RUN_CASE(test_find_first_of_char);
        XTESTS_RUN_CASE(test_find_first_of_c_string);
        XTESTS_RUN_CASE(test_find_first_of_string);
        XTESTS_RUN_CASE(test_find_last_of_char);
        XTESTS_RUN_CASE(test_find_last_of_c_string);
        XTESTS_RUN_CASE(test_find_last_of_string);
        XTESTS_RUN_CASE(test_find_first_not_of_char);
        XTESTS_RUN_CASE(test_find_first_not_of_c_string);
        XTESTS_RUN_CASE(test_find_first_not_of_string);
        XTESTS_RUN_CASE(test_find_last_not_of_char);
        XTESTS_RUN_CASE(test_find_last_not_of_c_string);
        XTESTS_RUN_CASE(test_find_last_not_of_string);
#endif

        // traits

        XTESTS_RUN_CASE(test_stlsoft_char_traits);

        XTESTS_RUN_CASE(test_string_traits);


        // operators : concatenation

        XTESTS_RUN_CASE(test_concatenation_1);
        XTESTS_RUN_CASE(test_concatenation_2);
#ifdef USE_std_string
        XTESTS_RUN_CASE(test_concatenation_3);
        XTESTS_RUN_CASE(test_concatenation_4);
        XTESTS_RUN_CASE(test_concatenation_5);
#endif
        XTESTS_RUN_CASE(test_concatenation_6);


        // operators : insertion

        XTESTS_RUN_CASE(test_insertion_1);
        XTESTS_RUN_CASE(test_insertion_2);
        XTESTS_RUN_CASE(test_insertion_3);
        XTESTS_RUN_CASE(test_insertion_4);


        // shims : sas

        XTESTS_RUN_CASE(test_string_access_shims);


        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

#ifndef USE_std_string
    typedef stlsoft::simple_string                          string_t;
    typedef stlsoft::simple_wstring                         wstring_t;
#else /* ? !USE_std_string */
    typedef std::string                                     string_t;
    typedef std::wstring                                    wstring_t;
#endif /* !USE_std_string */
    using stlsoft::ss_size_t;


    struct SimpleStream
    {
        std::string     contents;

        SimpleStream&
        write(
            char const*     s
        ,   std::streamsize n
        )
        {
            contents.append(s, static_cast<std::size_t>(n));

            return *this;
        }

        std::string
        str() const
        {
            return contents;
        }
    };

#if 0

    SimpleStream&
    operator <<(
        SimpleStream&       stm
    ,   char const*         s
    )
    {
        std::size_t const   len = ::strlen(s);

        stm.write(s, len);

        return stm;
    }
#endif
#ifdef USE_std_string

    SimpleStream&
    operator <<(
        SimpleStream&       stm
    ,   std::string const&  s
    )
    {
        stm.write(s.data(), s.size());

        return stm;
    }
#endif


    static char const       alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    static wchar_t const    alphabet_w[] = L"abcdefghijklmnopqrstuvwxyz";


// construction

static void test_ctor_default()
{
    {
        ss_constexpr_2020_k
        string_t s;

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
        TEST_INT_GE(0u, s.capacity());
        TEST_INT_NE(0u, s.max_size());
    }
}

static void test_ctor_copy()
{
    {
        string_t    s1;
        string_t    s2(s1);

        TEST_INT_EQ(s1.size(), s2.size());
        TEST_MS_EQ(s1, s2);
    }

    {
        string_t    s1("abc");
        string_t    s2(s1);

        TEST_INT_EQ(s1.size(), s2.size());
        TEST_MS_EQ(s1, s2);
    }
}

static void test_ctor_s_pos()
{
    {
        string_t    s1;
        string_t    s2(s1, 0);

        TEST_INT_EQ(s1.size(), s2.size());
        TEST_MS_EQ(s1, s2);
    }

    {
        string_t    s1("abc");
        string_t    s2(s1, 1);

        TEST_INT_EQ(2u, s2.size());
        TEST_MS_EQ("bc", s2);
    }
}

static void test_ctor_s_pos_n()
{
    {
        string_t    s1("abc");
        string_t    s2(s1, 0u, s1.size());

        TEST_INT_EQ(s1.size(), s2.size());
        TEST_MS_EQ(s1, s2);
    }

    {
        string_t    s1("abc");
        string_t    s2(s1, 1u, s1.size() - 1u);

        TEST_INT_EQ(2u, s2.size());
        TEST_MS_EQ("bc", s2);
    }

    // deliberately over-specify n
    {
        string_t    s1("abc");
        string_t    s2(s1, 1u, 500);

        TEST_INT_EQ(2u, s2.size());
        TEST_MS_EQ("bc", s2);
    }
}

static void test_ctor_ccs()
{
    {
        string_t    s("abc");

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(3u, s.size());
        TEST_MS_EQ("abc", s);
    }

#ifndef USE_std_string
    {
        string_t    s(static_cast<char const*>(NULL));

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
        TEST_INT_GE(0u, s.capacity());
        TEST_INT_NE(0u, s.max_size());
    }
#endif /* !USE_std_string */
}

static void test_ctor_ccs_n()
{
    {
        string_t    s(alphabet, 3);

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(3u, s.size());
        TEST_INT_GE(3u, s.capacity());
        TEST_INT_NE(0u, s.max_size());
    }

#ifndef USE_std_string
    {
        string_t    s(static_cast<char const*>(NULL), size_t(0));

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
        TEST_INT_GE(0u, s.capacity());
        TEST_INT_NE(0u, s.max_size());
    }
#endif /* !USE_std_string */
}

static void test_ctor_n_ch()
{
    {
        string_t    s(0, '~');

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
        TEST_INT_GE(0u, s.capacity());
    }

    {
        string_t    s(8, '~');

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(8u, s.size());
        TEST_INT_GE(8u, s.capacity());
#ifndef USE_std_string
        TEST_CHAR_EQ('~', s.front());
        TEST_CHAR_EQ('~', s.back());

        string_t const& cs = s;

        TEST_CHAR_EQ('~', cs.front());
        TEST_CHAR_EQ('~', cs.back());
#endif // !USE_std_string
    }

    {
        string_t    s(9, '~');

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(9u, s.size());
        TEST_INT_GE(9u, s.capacity());
        TEST_CHAR_EQ('~', s.front());
        TEST_CHAR_EQ('~', s.back());

        string_t const& cs = s;

        TEST_CHAR_EQ('~', cs.front());
        TEST_CHAR_EQ('~', cs.back());
    }

    {
        string_t    s(10, '~');

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(10u, s.size());
        TEST_INT_GE(10u, s.capacity());
        TEST_CHAR_EQ('~', s.front());
        TEST_CHAR_EQ('~', s.back());

        string_t const& cs = s;

        TEST_CHAR_EQ('~', cs.front());
        TEST_CHAR_EQ('~', cs.back());
    }
}

static void test_ctor_range()
{
    string_t        s1(alphabet);
    string_t        s2(&alphabet[0], &alphabet[0] + STLSOFT_NUM_ELEMENTS(alphabet) -1);
    string_t const  s3(s1.begin(), s1.end());
    string_t        s4(s3.begin(), s3.end());

    TEST_MS_EQ(alphabet, s1);
    TEST_MS_EQ(alphabet, s2);
    TEST_MS_EQ(alphabet, s3);
    TEST_MS_EQ(alphabet, s4);
}

#ifndef USE_std_string

static void test_ctor_range_2()
{
    string_t        s1(alphabet);
    string_t        s2(&alphabet[0], &alphabet[0] + STLSOFT_NUM_ELEMENTS(alphabet) -1);
# ifdef STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT
    string_t const  s3(s1.rbegin(), s1.rend());
    string_t        s4(s3.rbegin(), s3.rend());
# endif

    TEST_MS_EQ(alphabet, s1);
    TEST_MS_EQ(alphabet, s2);
# ifdef STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT
//  TEST_MS_EQ(alphabet, s3);
    TEST_MS_EQ(alphabet, s4);
# endif
}
#endif /* !USE_std_string */


// `assign()`

static void test_assign_1()
{
    {
        string_t    s;

        s.assign("");

        TEST_INT_EQ(0u, s.size());
        TEST_MS_EQ("", s);

        s = "";

        TEST_INT_EQ(0u, s.size());
        TEST_MS_EQ("", s);

        s = 'a';

        TEST_INT_EQ(1u, s.size());
        TEST_MS_EQ("a", s);

        s = string_t();

        TEST_INT_EQ(0u, s.size());
        TEST_MS_EQ("", s);

        s.assign("abc");

        TEST_INT_EQ(3u, s.size());
        TEST_MS_EQ("abc", s);

        s.assign(alphabet);

        TEST_INT_EQ(26u, s.size());
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", s);

        s.assign("");

        TEST_INT_EQ(0u, s.size());
        TEST_MS_EQ("", s);
    }

    {
        string_t s;

        s.assign("");

        TEST_INT_EQ(0u, s.size());
        TEST_MS_EQ("", s);

        s.assign(s.c_str(), 0);

        TEST_INT_EQ(0u, s.size());
        TEST_MS_EQ("", s);
    }

    {
        string_t s;

        s.assign(alphabet);

        TEST_INT_EQ(26u, s.size());
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", s);

        s.assign(s.c_str(), 26);

        TEST_INT_EQ(26u, s.size());
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", s);

        s.assign(s.c_str() + 13, 13);

        TEST_INT_EQ(13u, s.size());
        TEST_MS_EQ("nopqrstuvwxyz", s);
    }
}

static void test_assign_2()
{
    {
        string_t    s;

        s.assign("", size_t(0));

        TEST_INT_EQ(0u, s.size());
        TEST_MS_EQ("", s);

        s.assign("abc", 3);

        TEST_INT_EQ(3u, s.size());
        TEST_MS_EQ("abc", s);

        s.assign(alphabet, 26);

        TEST_INT_EQ(26u, s.size());
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", s);

        s.assign(alphabet, 3);

        TEST_INT_EQ(3u, s.size());
        TEST_MS_EQ("abc", s);

        s.assign("", size_t(0));

        TEST_INT_EQ(0u, s.size());
        TEST_MS_EQ("", s);
    }
}

static void test_assign_3()
{
    string_t const s_alphabet(alphabet);

    {
        string_t    s;

        s.assign(s_alphabet, 0, 0);

        TEST_INT_EQ(0u, s.size());
        TEST_MS_EQ("", s);

        s.assign(s_alphabet, 0, 3);

        TEST_INT_EQ(3u, s.size());
        TEST_MS_EQ("abc", s);

        s.assign(s_alphabet, 0, 26);

        TEST_INT_EQ(26u, s.size());
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", s);

        s.assign(s_alphabet.begin(), s_alphabet.end());

        TEST_INT_EQ(26u, s.size());
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", s);

        s.assign(s_alphabet, 25, 0);

        TEST_INT_EQ(0u, s.size());
        TEST_MS_EQ("", s);
    }
}

#ifndef USE_std_string

static void test_assign_4()
{
# ifdef STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT
    std::stringstream   ss("abc");

    string_t    s1 = string_t(std::istream_iterator<char>(ss), std::istream_iterator<char>());

    TEST_BOOLEAN_FALSE(s1.empty());
    TEST_INT_EQ(3u, s1.size());
    TEST_INT_GE(3u, s1.capacity());
    TEST_MS_EQ("abc", s1);
# endif
}
#endif /* !USE_std_string */


// `append()`

static void test_append_1()
{
    string_t        s1;
    string_t const  s2("abc");

    TEST_BOOLEAN_TRUE(s1.empty());
    TEST_INT_EQ(0u, s1.size());
    TEST_INT_GE(0u, s1.capacity());
    TEST_MS_EQ("", s1);

    s1.append(s1, 0, 0);

    TEST_BOOLEAN_TRUE(s1.empty());
    TEST_INT_EQ(0u, s1.size());
    TEST_INT_GE(0u, s1.capacity());
    TEST_MS_EQ("", s1);

    s1.append(s2, 3u, 0u);

    TEST_BOOLEAN_TRUE(s1.empty());
    TEST_INT_EQ(0u, s1.size());
    TEST_INT_GE(0u, s1.capacity());
    TEST_MS_EQ("", s1);

    s1.append(s2, 0, 3);

    TEST_BOOLEAN_FALSE(s1.empty());
    TEST_INT_EQ(3u, s1.size());
    TEST_INT_GE(3u, s1.capacity());
    TEST_MS_EQ("abc", s1);

#ifndef USE_std_string
    s1.clear();
#else /* ? !USE_std_string */
    s1.erase(s1.begin(), s1.end());
#endif /* !USE_std_string */
    s1.append(s2, 2, 3);

    TEST_BOOLEAN_FALSE(s1.empty());
    TEST_INT_EQ(1u, s1.size());
    TEST_INT_GE(1u, s1.capacity());
    TEST_MS_EQ("c", s1);

#ifndef USE_std_string
    s1.clear();
#else /* ? !USE_std_string */
    s1.erase(s1.begin(), s1.end());
#endif /* !USE_std_string */
    s1.append(s2.begin(), s2.end());

    TEST_BOOLEAN_FALSE(s1.empty());
    TEST_INT_EQ(3u, s1.size());
    TEST_INT_GE(3u, s1.capacity());
    TEST_MS_EQ("abc", s1);

    std::stringstream   ss("abc");

#ifndef USE_std_string
# ifdef STLSOFT_CF_MEMBER_TEMPLATE_RANGE_METHOD_SUPPORT
    s1.clear();
    s1.append(std::istream_iterator<char>(ss), std::istream_iterator<char>());

    TEST_BOOLEAN_FALSE(s1.empty());
    TEST_INT_EQ(3u, s1.size());
    TEST_INT_GE(3u, s1.capacity());
    TEST_MS_EQ("abc", s1);
# endif
#endif /* !USE_std_string */
}

static void test_append_2()
{
    string_t    s1;
    char const  s2[] = "abc";

    TEST_BOOLEAN_TRUE(s1.empty());
    TEST_INT_EQ(0u, s1.size());
    TEST_INT_GE(0u, s1.capacity());
    TEST_MS_EQ("", s1);

    s1.append(s1, 0u, 0);

    TEST_BOOLEAN_TRUE(s1.empty());
    TEST_INT_EQ(0u, s1.size());
    TEST_INT_GE(0u, s1.capacity());
    TEST_MS_EQ("", s1);

    s1.append(s2, 3);

    TEST_BOOLEAN_FALSE(s1.empty());
    TEST_INT_EQ(3u, s1.size());
    TEST_INT_GE(3u, s1.capacity());
    TEST_MS_EQ("abc", s1);

    s1.append(s2, size_t(0));

    TEST_BOOLEAN_FALSE(s1.empty());
    TEST_INT_EQ(3u, s1.size());
    TEST_INT_GE(3u, s1.capacity());
    TEST_MS_EQ("abc", s1);
}

static void test_append_3()
{
    string_t    s1;

    s1.append(s1, 1u, 0);

    TEST_FAIL("should not get here!");
}

#ifndef USE_std_string

static void test_push_back()
{
    string_t    s;

    TEST_BOOLEAN_TRUE(s.empty());
    TEST_INT_EQ(0u, s.size());
    TEST_INT_GE(0u, s.capacity());
    TEST_MS_EQ("", s);

    s.push_back('a');

    TEST_BOOLEAN_FALSE(s.empty());
    TEST_INT_EQ(1u, s.size());
    TEST_INT_GE(1u, s.capacity());
    TEST_MS_EQ("a", s);

    s.push_back('b');

    TEST_BOOLEAN_FALSE(s.empty());
    TEST_INT_EQ(2u, s.size());
    TEST_INT_GE(2u, s.capacity());
    TEST_MS_EQ("ab", s);

    s.push_back('c');

    TEST_BOOLEAN_FALSE(s.empty());
    TEST_INT_EQ(3u, s.size());
    TEST_INT_GE(3u, s.capacity());
    TEST_MS_EQ("abc", s);
}
#endif /* !USE_std_string */

static void test_pop_back()
{
    string_t s(alphabet, 10);

    TEST_MS_EQ("abcdefghij", s);

    s.pop_back();

    TEST_MS_EQ("abcdefghi", s);

    s.pop_back();
    s.pop_back();
    s.pop_back();

    TEST_INT_EQ(6u, s.size());
    TEST_MS_EQ("abcdef", s);

    s.pop_back();
    s.pop_back();
    s.pop_back();
    s.pop_back();

    TEST_MS_EQ("ab", s);

    s.pop_back();

    TEST_INT_EQ(1u, s.size());
    TEST_MS_EQ("a", s);

    s.pop_back();

    TEST_INT_EQ(0u, s.size());
    TEST_MS_EQ("", s);

    s.pop_back();

    TEST_INT_EQ(0u, s.size());
    TEST_MS_EQ("", s);
}


// modifiers

static void test_reserve()
{
    {
        string_t    s;

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
        TEST_INT_GE(0u, s.capacity());

        s.reserve(10u);

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
        TEST_INT_GE(10u, s.capacity());
    }

    {
        string_t    s("abc");

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(3u, s.size());
        TEST_INT_GE(3u, s.capacity());
        TEST_MS_EQ("abc", s);

        s.reserve(10u);

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(3u, s.size());
        TEST_INT_GE(10u, s.capacity());
        TEST_MS_EQ("abc", s);

        s.reserve(1000u);

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(3u, s.size());
        TEST_INT_GE(1000u, s.capacity());
        TEST_MS_EQ("abc", s);
    }
}

static void test_swap_1()
{
    {
        string_t    s1;
        string_t    s2;

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());

        s1.swap(s2);

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());
    }

    {
        string_t    s1("abc");
        string_t    s2;

        TEST_INT_EQ(3u, s1.size());
        TEST_MS_EQ("abc", s1);

        TEST_INT_EQ(0u, s2.size());
        TEST_MS_EQ("", s2);

        s1.swap(s2);

        TEST_INT_EQ(0u, s1.size());
        TEST_MS_EQ("", s1);

        TEST_INT_EQ(3u, s2.size());
        TEST_MS_EQ("abc", s2);
    }
}

static void test_swap_2()
{
    {
        string_t    s1;
        string_t    s2;

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());

        swap(s1, s2);

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());
    }

    {
        string_t    s1("abc");
        string_t    s2;

        TEST_INT_EQ(3u, s1.size());
        TEST_MS_EQ("abc", s1);

        TEST_INT_EQ(0u, s2.size());
        TEST_MS_EQ("", s2);

        swap(s1, s2);

        TEST_INT_EQ(0u, s1.size());
        TEST_MS_EQ("", s1);

        TEST_INT_EQ(3u, s2.size());
        TEST_MS_EQ("abc", s2);
    }
}

static void test_swap_3()
{
    {
        string_t    s1;
        string_t    s2;

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());

        std::swap(s1, s2);

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());
    }

    {
        string_t    s1("abc");
        string_t    s2;

        TEST_INT_EQ(3u, s1.size());
        TEST_MS_EQ("abc", s1);

        TEST_INT_EQ(0u, s2.size());
        TEST_MS_EQ("", s2);

        std::swap(s1, s2);

        TEST_INT_EQ(0u, s1.size());
        TEST_MS_EQ("", s1);

        TEST_INT_EQ(3u, s2.size());
        TEST_MS_EQ("abc", s2);
    }
}

static void test_resize()
{
    {
        string_t    s;

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());

        s.resize(0u);

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
    }

    {
        string_t    s;

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());

        s.resize(3u, '~');

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(3u, s.size());
        TEST_MS_EQ("~~~", s);
    }

    {
        string_t    s("abcdef");

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(6u, s.size());
        TEST_MS_EQ("abcdef", s);

        s.resize(3u, '~');

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(3u, s.size());
        TEST_MS_EQ("abc", s);
    }

    // Grow a non-empty string past its current capacity (exercises the
    // realloc path that previously over-read the source buffer).
    {
        string_t    s("abcdef");

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(6u, s.size());
        TEST_MS_EQ("abcdef", s);

        s.resize(1000u, '~');

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(1000u, s.size());
        TEST_MS_EQ_N("abcdef", s, 6);
        TEST_CHAR_EQ('~', s[6]);
        TEST_CHAR_EQ('~', s[999]);
    }
}

#ifndef USE_std_string

static void test_clear()
{
    {
        string_t    s;

        s.clear();

        TEST_INT_EQ(0u, s.size());
    }

    {
        string_t    s("abc");

        s.clear();

        TEST_INT_EQ(0u, s.size());
    }
}
#endif /* !USE_std_string */

#ifdef USE_std_string

static void test_erase_0_param()
{
    {
        string_t    s;

        s.erase();

        TEST_INT_EQ(0u, s.size());
    }

    {
        string_t    s("abc");

        s.erase();

        TEST_INT_EQ(0u, s.size());
    }
}

static void test_erase_1_pos()
{
    {
        string_t    s;

        s.erase(size_t(0u));

        TEST_INT_EQ(0u, s.size());
    }

    {
        string_t    s("abc");

        s.erase(size_t(0u));

        TEST_INT_EQ(0u, s.size());
    }
}

static void test_erase_pos_and_cch()
{
    {
        string_t    s;

        s.erase(0u, 10u);

        TEST_INT_EQ(0u, s.size());
    }

    {
        string_t    s("abc");

        s.erase(0u, 10u);

        TEST_INT_EQ(0u, s.size());
    }
}
#endif


// attributes

static void test_size()
{
    {

    }
}

static void test_max_size()
{
    string_t s;

    TEST_INT_GE(1000000u, s.max_size());
}

static void test_length()
{

}

static void test_capacity()
{
    string_t s;

    TEST_INT_GE(0u, s.capacity());

    s.resize(10u);

    TEST_INT_GE(10u, s.capacity());

    s.resize(1000u);

    TEST_INT_GE(1000u, s.capacity());
}

static void test_empty()
{

}


// comparison

static void test_compare_1()
{
    string_t    s1("abc");
    string_t    s2("def");

    TEST_BOOLEAN_TRUE(s1 != s2);
    TEST_BOOLEAN_TRUE(s1 != s2.c_str());
    TEST_BOOLEAN_TRUE(s1.c_str() != s2);
    TEST_MS_NE(s1, s2);

    TEST_BOOLEAN_TRUE(s1 < s2);
    TEST_BOOLEAN_TRUE(s1 < s2.c_str());
    TEST_BOOLEAN_TRUE(s1.c_str() < s2);
    TEST_BOOLEAN_TRUE(s1 <= s2);
    TEST_BOOLEAN_TRUE(s1 <= s2.c_str());
    TEST_BOOLEAN_TRUE(s1.c_str() <= s2);
    TEST_BOOLEAN_TRUE(s2 > s1);
    TEST_BOOLEAN_TRUE(s2 > s1.c_str());
    TEST_BOOLEAN_TRUE(s2.c_str() > s1);
    TEST_BOOLEAN_TRUE(s2 >= s1);
    TEST_BOOLEAN_TRUE(s2 >= s1.c_str());
    TEST_BOOLEAN_TRUE(s2.c_str() >= s1);

    TEST_BOOLEAN_TRUE(s1 == s1);
    TEST_BOOLEAN_TRUE(s1 == s1.c_str());
    TEST_BOOLEAN_TRUE(s1 == "abc");
    TEST_BOOLEAN_TRUE(s1.c_str() == s1);
    TEST_BOOLEAN_TRUE("abc" == s1);

    TEST_BOOLEAN_TRUE(s1 != s2);
    TEST_BOOLEAN_TRUE(s1 != s2.c_str());
    TEST_BOOLEAN_TRUE(s1 != "def");
    TEST_BOOLEAN_TRUE(s1.c_str() != s2);
    TEST_BOOLEAN_TRUE("abc" != s2);
}

static void test_compare_2()
{
    string_t    s1("abc");
    string_t    s2("def");

    TEST_INT_LT(0, s1.compare(s2));
    TEST_INT_LT(0, s1.compare(0u, 3u, s2));
    TEST_INT_LT(0, s1.compare(0u, 3u, s2.c_str()));
//  TEST_INT_LT(0, s1.compare(0u, 4u, s2.c_str()));
    TEST_INT_LT(0, s1.compare(0u, 3u, s2.c_str(), s2.size()));
}

static void test_compare_3()
{
    string_t    s1("def");

    TEST_INT_LT(0, s1.compare("ghi"));
    TEST_INT_LT(0, s1.compare(0u, 3u, "ghi"));
    TEST_INT_LT(0, s1.compare(3u, 0u, "ghi"));
    TEST_INT_LT(0, s1.compare(0u, 2u, "ghi"));
    TEST_INT_LT(0, s1.compare(0u, 2u, "ghi", 2u));
    TEST_INT_LT(0, s1.compare(3u, 2u, "ghi", 2u));
    TEST_INT_LT(0, s1.compare(3u, 2u, "ghi", 0u, 2u));
    TEST_INT_GT(0, s1.compare(0u, 2u, "abc", 0u, 2u));
    TEST_INT_LT(0, s1.compare(3u, 2u, "abc", 0u, 2u));
    TEST_INT_EQ(0, s1.compare(3u, 2u, "ghi", 3u, 0u));
    TEST_INT_EQ(0, s1.compare(3u, 2u, "ghi", 3u, 2u));


    TEST_INT_EQ(0, s1.compare(0u, 0u, "def", 0u, 0u));
    TEST_INT_EQ(0, s1.compare(1u, 0u, "def", 1u, 0u));
    TEST_INT_EQ(0, s1.compare(2u, 0u, "def", 2u, 0u));
    TEST_INT_EQ(0, s1.compare(3u, 0u, "def", 3u, 0u));

    TEST_INT_EQ(0, s1.compare(0u, 1u, "def", 0u, 1u));
    TEST_INT_EQ(0, s1.compare(1u, 1u, "def", 1u, 1u));
    TEST_INT_EQ(0, s1.compare(2u, 1u, "def", 2u, 1u));
    TEST_INT_EQ(0, s1.compare(3u, 1u, "def", 3u, 1u));

    TEST_INT_EQ(0, s1.compare(0u, 2u, "def", 0u, 2u));
    TEST_INT_EQ(0, s1.compare(1u, 2u, "def", 1u, 2u));
    TEST_INT_EQ(0, s1.compare(2u, 2u, "def", 2u, 2u));
    TEST_INT_EQ(0, s1.compare(3u, 2u, "def", 3u, 2u));

    TEST_INT_EQ(0, s1.compare(0u, 3u, "def", 0u, 3u));
    TEST_INT_EQ(0, s1.compare(1u, 3u, "def", 1u, 3u));
    TEST_INT_EQ(0, s1.compare(2u, 3u, "def", 2u, 3u));
    TEST_INT_EQ(0, s1.compare(3u, 3u, "def", 3u, 3u));


    TEST_INT_EQ(0, s1.compare(0u, 0u, "fed", 0u, 0u));
    TEST_INT_EQ(0, s1.compare(1u, 0u, "fed", 1u, 0u));
    TEST_INT_EQ(0, s1.compare(2u, 0u, "fed", 2u, 0u));
    TEST_INT_EQ(0, s1.compare(3u, 0u, "fed", 3u, 0u));

    TEST_INT_LT(0, s1.compare(0u, 1u, "fed", 0u, 1u));
    TEST_INT_EQ(0, s1.compare(1u, 1u, "fed", 1u, 1u));
    TEST_INT_GT(0, s1.compare(2u, 1u, "fed", 2u, 1u));
    TEST_INT_EQ(0, s1.compare(3u, 1u, "fed", 3u, 1u));

    TEST_INT_LT(0, s1.compare(0u, 2u, "fed", 0u, 2u));
    TEST_INT_GT(0, s1.compare(1u, 2u, "fed", 1u, 2u));
    TEST_INT_GT(0, s1.compare(2u, 2u, "fed", 2u, 2u));
    TEST_INT_EQ(0, s1.compare(3u, 2u, "fed", 3u, 2u));

    TEST_INT_LT(0, s1.compare(0u, 3u, "fed", 0u, 3u));
    TEST_INT_GT(0, s1.compare(1u, 3u, "fed", 1u, 3u));
    TEST_INT_GT(0, s1.compare(2u, 3u, "fed", 2u, 3u));
    TEST_INT_EQ(0, s1.compare(3u, 3u, "fed", 3u, 3u));
}

static void test_compare_4()
{
    {
        string_t    s1("mno");
        string_t    s2("mnopqr");

        TEST_INT_LT(0, s1.compare(s2));
        TEST_INT_LT(0, s1.compare(s2.c_str()));
        TEST_INT_LT(0, s1.compare(0u, s1.size(), s2));
    }
}

static void test_equality_operators_1()
{
    string_t    s1("abc");
    string_t    s2("def");
    string_t    s3("abc");
    string_t    s4("def");

    TEST_BOOLEAN_TRUE(s1 == s1);
    TEST_BOOLEAN_FALSE(s1 != s1);
    TEST_BOOLEAN_TRUE(s1 != s2);
    TEST_BOOLEAN_FALSE(s1 == s2);
    TEST_BOOLEAN_TRUE(s1 == s3);
    TEST_BOOLEAN_FALSE(s1 != s3);
    TEST_BOOLEAN_TRUE(s1 != s4);
    TEST_BOOLEAN_FALSE(s1 == s4);
}

#ifndef USE_std_string

static void test_equal_p_n_ccs_n()
{
    string_t    s1("abc");
    string_t    s2("def");
    string_t    s3("abc");
    string_t    s4("def");

    TEST_BOOLEAN_TRUE(s1.equal(0, 3, s1.c_str(), 3));
    TEST_BOOLEAN_FALSE(s1.equal(0, 3, s2.c_str(), 3));
    TEST_BOOLEAN_TRUE(s1.equal(0, 3, s3.c_str(), 3));
    TEST_BOOLEAN_FALSE(s1.equal(0, 3, s4.c_str(), 3));
}

static void test_equal_p_n_ccs()
{
    string_t    s1("abc");
    string_t    s2("def");
    string_t    s3("abc");
    string_t    s4("def");

    TEST_BOOLEAN_TRUE(s1.equal(0, 3, s1.c_str()));
    TEST_BOOLEAN_FALSE(s1.equal(0, 3, s2.c_str()));
    TEST_BOOLEAN_TRUE(s1.equal(0, 3, s3.c_str()));
    TEST_BOOLEAN_FALSE(s1.equal(0, 3, s4.c_str()));

    TEST_BOOLEAN_TRUE(s1.equal(0, 3, "abc"));
    TEST_BOOLEAN_TRUE(s1.equal(1, 2, "bc"));
    TEST_BOOLEAN_TRUE(s1.equal(2, 1, "c"));
    TEST_BOOLEAN_TRUE(s1.equal(3, 0, ""));

    TEST_BOOLEAN_TRUE(s1.equal(0, 4, "abc"));
    TEST_BOOLEAN_TRUE(s1.equal(0, 444, "abc"));

    TEST_BOOLEAN_TRUE(s1.equal(1, 3, "bc"));
    TEST_BOOLEAN_TRUE(s1.equal(1, 333, "bc"));

    TEST_BOOLEAN_TRUE(s1.equal(2, 2, "c"));
    TEST_BOOLEAN_TRUE(s1.equal(2, 222, "c"));
}

static void test_equal_ccs()
{
    string_t    s1("abc");
    string_t    s2("def");
    string_t    s3("abc");
    string_t    s4("def");

    TEST_BOOLEAN_TRUE(s1.equal(s1.c_str()));
    TEST_BOOLEAN_FALSE(s1.equal(s2.c_str()));
    TEST_BOOLEAN_TRUE(s1.equal(s3.c_str()));
    TEST_BOOLEAN_FALSE(s1.equal(s4.c_str()));
}

static void test_equal_p_n_scr_p_n()
{
    string_t    s0;
    string_t    s1("abc");
    string_t    s2("def");
    string_t    s3("abcd");
    string_t    s4("defg");

    TEST_BOOLEAN_TRUE(s0.equal(0, 0, s0, 0, 0));
    TEST_BOOLEAN_TRUE(s0.equal(0, 1, s0, 0, 0));
    TEST_BOOLEAN_FALSE(s0.equal(0, 0, s0, 0, 1));

    TEST_BOOLEAN_TRUE(s1.equal(0, 0, s0, 0, 0));
    TEST_BOOLEAN_TRUE(s1.equal(0, 1, s0, 0, 0));
    TEST_BOOLEAN_TRUE(s1.equal(0, 2, s0, 0, 0));
    TEST_BOOLEAN_TRUE(s1.equal(1, 0, s0, 0, 0));
    TEST_BOOLEAN_TRUE(s1.equal(1, 1, s0, 0, 0));
    TEST_BOOLEAN_TRUE(s1.equal(1, 2, s0, 0, 0));

    TEST_BOOLEAN_TRUE(s1.equal(0, 3, s1, 0, s1.size()));
    TEST_BOOLEAN_FALSE(s1.equal(0, 3, s2, 0, s2.size()));
    TEST_BOOLEAN_TRUE(s1.equal(0, 3, s1, 0, s1.size()));
    TEST_BOOLEAN_FALSE(s1.equal(0, 3, s3, 0, s3.size()));
    TEST_BOOLEAN_FALSE(s1.equal(0, 3, s4, 0, s4.size()));

    TEST_BOOLEAN_FALSE(s3.equal(0, 1, s1));
    TEST_BOOLEAN_FALSE(s3.equal(0, 2, s1));
    TEST_BOOLEAN_TRUE(s3.equal(0, 3, s1));
    TEST_BOOLEAN_FALSE(s3.equal(0, 4, s1));
}

static void test_equal_p_n_scr()
{
    string_t    s0;
    string_t    s1("abc");
    string_t    s2("def");
    string_t    s3("abcd");
    string_t    s4("defg");

    TEST_BOOLEAN_TRUE(s1.equal(0, 0, s0));
    TEST_BOOLEAN_TRUE(s1.equal(0, 1, s0));
    TEST_BOOLEAN_TRUE(s1.equal(0, 2, s0));
    TEST_BOOLEAN_TRUE(s1.equal(1, 0, s0));
    TEST_BOOLEAN_TRUE(s1.equal(1, 1, s0));
    TEST_BOOLEAN_TRUE(s1.equal(1, 2, s0));

    TEST_BOOLEAN_TRUE(s1.equal(0, 3, s1));
    TEST_BOOLEAN_FALSE(s1.equal(0, 3, s2));
    TEST_BOOLEAN_TRUE(s1.equal(0, 3, s1));
    TEST_BOOLEAN_FALSE(s1.equal(0, 3, s3));
    TEST_BOOLEAN_FALSE(s1.equal(0, 3, s4));

    TEST_BOOLEAN_FALSE(s3.equal(0, 1, s1));
    TEST_BOOLEAN_FALSE(s3.equal(0, 2, s1));
    TEST_BOOLEAN_TRUE(s3.equal(0, 3, s1));
    TEST_BOOLEAN_FALSE(s3.equal(0, 4, s1));
}

static void test_equal_scr()
{
    string_t    s0;
    string_t    s1("abc");
    string_t    s2("def");
    string_t    s3("abc");
    string_t    s4("def");

    TEST_BOOLEAN_TRUE(s0.equal(s0));
    TEST_BOOLEAN_FALSE(s0.equal(s1));
    TEST_BOOLEAN_TRUE(s1.equal(s1));
    TEST_BOOLEAN_FALSE(s1.equal(s2));
    TEST_BOOLEAN_TRUE(s1.equal(s3));
    TEST_BOOLEAN_FALSE(s1.equal(s4));
}
#endif /* !USE_std_string */

#if !defined(USE_std_string) || \
    __cplusplus >= 202002L

static void test_starts_with_1()
{
    string_t const s;

    {
        TEST_BOOLEAN_TRUE(s.starts_with(""));
        TEST_BOOLEAN_FALSE(s.starts_with("a"));
        TEST_BOOLEAN_FALSE(s.starts_with("b"));
        TEST_BOOLEAN_FALSE(s.starts_with("c"));
        TEST_BOOLEAN_FALSE(s.starts_with("d"));
        TEST_BOOLEAN_FALSE(s.starts_with("e"));
        TEST_BOOLEAN_FALSE(s.starts_with("i"));
        TEST_BOOLEAN_FALSE(s.starts_with("o"));
        TEST_BOOLEAN_FALSE(s.starts_with("u"));
        TEST_BOOLEAN_FALSE(s.starts_with("x"));
        TEST_BOOLEAN_FALSE(s.starts_with("y"));
        TEST_BOOLEAN_FALSE(s.starts_with("z"));

        TEST_BOOLEAN_FALSE(s.starts_with("ab"));
        TEST_BOOLEAN_FALSE(s.starts_with("abc"));
        TEST_BOOLEAN_FALSE(s.starts_with("abcd"));
        TEST_BOOLEAN_FALSE(s.starts_with("abcde"));

        TEST_BOOLEAN_FALSE(s.starts_with("aa"));
        TEST_BOOLEAN_FALSE(s.starts_with("bcde"));
        TEST_BOOLEAN_FALSE(s.starts_with("acde"));
        TEST_BOOLEAN_FALSE(s.starts_with("abde"));
        TEST_BOOLEAN_FALSE(s.starts_with("abce"));
    }

    {
        TEST_BOOLEAN_TRUE(s.starts_with(string_t("")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("a")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("b")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("c")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("d")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("e")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("i")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("o")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("u")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("x")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("y")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("z")));

        TEST_BOOLEAN_FALSE(s.starts_with(string_t("ab")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("abc")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("abcd")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("abcde")));

        TEST_BOOLEAN_FALSE(s.starts_with(string_t("aa")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("bcde")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("acde")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("abde")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("abce")));
    }

    {
        TEST_BOOLEAN_FALSE(s.starts_with('a'));
        TEST_BOOLEAN_FALSE(s.starts_with('b'));
        TEST_BOOLEAN_FALSE(s.starts_with('c'));
        TEST_BOOLEAN_FALSE(s.starts_with('d'));
        TEST_BOOLEAN_FALSE(s.starts_with('e'));
        TEST_BOOLEAN_FALSE(s.starts_with('i'));
        TEST_BOOLEAN_FALSE(s.starts_with('o'));
        TEST_BOOLEAN_FALSE(s.starts_with('u'));
        TEST_BOOLEAN_FALSE(s.starts_with('x'));
        TEST_BOOLEAN_FALSE(s.starts_with('y'));
        TEST_BOOLEAN_FALSE(s.starts_with('z'));
    }
}

static void test_starts_with_2()
{
    string_t const s(alphabet);

    {
        TEST_BOOLEAN_TRUE(s.starts_with(""));
        TEST_BOOLEAN_TRUE(s.starts_with("a"));
        TEST_BOOLEAN_FALSE(s.starts_with("b"));
        TEST_BOOLEAN_FALSE(s.starts_with("c"));
        TEST_BOOLEAN_FALSE(s.starts_with("d"));
        TEST_BOOLEAN_FALSE(s.starts_with("e"));
        TEST_BOOLEAN_FALSE(s.starts_with("i"));
        TEST_BOOLEAN_FALSE(s.starts_with("o"));
        TEST_BOOLEAN_FALSE(s.starts_with("u"));
        TEST_BOOLEAN_FALSE(s.starts_with("x"));
        TEST_BOOLEAN_FALSE(s.starts_with("y"));
        TEST_BOOLEAN_FALSE(s.starts_with("z"));

        TEST_BOOLEAN_TRUE(s.starts_with("ab"));
        TEST_BOOLEAN_TRUE(s.starts_with("abc"));
        TEST_BOOLEAN_TRUE(s.starts_with("abcd"));
        TEST_BOOLEAN_TRUE(s.starts_with("abcde"));

        TEST_BOOLEAN_FALSE(s.starts_with("aa"));
        TEST_BOOLEAN_FALSE(s.starts_with("bcde"));
        TEST_BOOLEAN_FALSE(s.starts_with("acde"));
        TEST_BOOLEAN_FALSE(s.starts_with("abde"));
        TEST_BOOLEAN_FALSE(s.starts_with("abce"));
    }

    {
        TEST_BOOLEAN_TRUE(s.starts_with(string_t("")));
        TEST_BOOLEAN_TRUE(s.starts_with(string_t("a")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("b")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("c")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("d")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("e")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("i")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("o")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("u")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("x")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("y")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("z")));

        TEST_BOOLEAN_TRUE(s.starts_with(string_t("ab")));
        TEST_BOOLEAN_TRUE(s.starts_with(string_t("abc")));
        TEST_BOOLEAN_TRUE(s.starts_with(string_t("abcd")));
        TEST_BOOLEAN_TRUE(s.starts_with(string_t("abcde")));

        TEST_BOOLEAN_FALSE(s.starts_with(string_t("aa")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("bcde")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("acde")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("abde")));
        TEST_BOOLEAN_FALSE(s.starts_with(string_t("abce")));
    }

    {
        TEST_BOOLEAN_TRUE(s.starts_with('a'));
        TEST_BOOLEAN_FALSE(s.starts_with('b'));
        TEST_BOOLEAN_FALSE(s.starts_with('c'));
        TEST_BOOLEAN_FALSE(s.starts_with('d'));
        TEST_BOOLEAN_FALSE(s.starts_with('e'));
        TEST_BOOLEAN_FALSE(s.starts_with('i'));
        TEST_BOOLEAN_FALSE(s.starts_with('o'));
        TEST_BOOLEAN_FALSE(s.starts_with('u'));
        TEST_BOOLEAN_FALSE(s.starts_with('x'));
        TEST_BOOLEAN_FALSE(s.starts_with('y'));
        TEST_BOOLEAN_FALSE(s.starts_with('z'));
    }
}

static void test_contains_1()
{
    string_t const s;

    {
        TEST_BOOLEAN_TRUE(s.contains(""));
        TEST_BOOLEAN_FALSE(s.contains("a"));
        TEST_BOOLEAN_FALSE(s.contains("b"));
        TEST_BOOLEAN_FALSE(s.contains("c"));
        TEST_BOOLEAN_FALSE(s.contains("d"));
        TEST_BOOLEAN_FALSE(s.contains("e"));
        TEST_BOOLEAN_FALSE(s.contains("i"));
        TEST_BOOLEAN_FALSE(s.contains("o"));
        TEST_BOOLEAN_FALSE(s.contains("u"));
        TEST_BOOLEAN_FALSE(s.contains("x"));
        TEST_BOOLEAN_FALSE(s.contains("y"));
        TEST_BOOLEAN_FALSE(s.contains("z"));

        TEST_BOOLEAN_FALSE(s.contains("ab"));
        TEST_BOOLEAN_FALSE(s.contains("abc"));
        TEST_BOOLEAN_FALSE(s.contains("abcd"));
        TEST_BOOLEAN_FALSE(s.contains("abcde"));

        TEST_BOOLEAN_FALSE(s.contains("aa"));
        TEST_BOOLEAN_FALSE(s.contains("bcde"));
        TEST_BOOLEAN_FALSE(s.contains("acde"));
        TEST_BOOLEAN_FALSE(s.contains("abde"));
        TEST_BOOLEAN_FALSE(s.contains("abce"));
    }

    {
        TEST_BOOLEAN_TRUE(s.contains(string_t("")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("a")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("b")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("c")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("d")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("e")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("i")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("o")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("u")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("x")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("y")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("z")));

        TEST_BOOLEAN_FALSE(s.contains(string_t("ab")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("abc")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("abcd")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("abcde")));

        TEST_BOOLEAN_FALSE(s.contains(string_t("aa")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("bcde")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("acde")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("abde")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("abce")));
    }

    {
        TEST_BOOLEAN_FALSE(s.contains('a'));
        TEST_BOOLEAN_FALSE(s.contains('b'));
        TEST_BOOLEAN_FALSE(s.contains('c'));
        TEST_BOOLEAN_FALSE(s.contains('d'));
        TEST_BOOLEAN_FALSE(s.contains('e'));
        TEST_BOOLEAN_FALSE(s.contains('i'));
        TEST_BOOLEAN_FALSE(s.contains('o'));
        TEST_BOOLEAN_FALSE(s.contains('u'));
        TEST_BOOLEAN_FALSE(s.contains('x'));
        TEST_BOOLEAN_FALSE(s.contains('y'));
        TEST_BOOLEAN_FALSE(s.contains('z'));
    }
}

static void test_contains_2()
{
    string_t const s(alphabet);

    {
        TEST_BOOLEAN_TRUE(s.contains(""));
        TEST_BOOLEAN_TRUE(s.contains("a"));
        TEST_BOOLEAN_TRUE(s.contains("b"));
        TEST_BOOLEAN_TRUE(s.contains("c"));
        TEST_BOOLEAN_TRUE(s.contains("d"));
        TEST_BOOLEAN_TRUE(s.contains("e"));
        TEST_BOOLEAN_TRUE(s.contains("i"));
        TEST_BOOLEAN_TRUE(s.contains("o"));
        TEST_BOOLEAN_TRUE(s.contains("u"));
        TEST_BOOLEAN_TRUE(s.contains("x"));
        TEST_BOOLEAN_TRUE(s.contains("y"));
        TEST_BOOLEAN_TRUE(s.contains("z"));

        TEST_BOOLEAN_TRUE(s.contains("ab"));
        TEST_BOOLEAN_TRUE(s.contains("abc"));
        TEST_BOOLEAN_TRUE(s.contains("abcd"));
        TEST_BOOLEAN_TRUE(s.contains("abcde"));

        TEST_BOOLEAN_FALSE(s.contains("aa"));
        TEST_BOOLEAN_TRUE(s.contains("bcde"));
        TEST_BOOLEAN_FALSE(s.contains("acde"));
        TEST_BOOLEAN_FALSE(s.contains("abde"));
        TEST_BOOLEAN_FALSE(s.contains("abce"));
    }

    {
        TEST_BOOLEAN_TRUE(s.contains(string_t("")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("a")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("b")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("c")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("d")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("e")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("i")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("o")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("u")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("x")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("y")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("z")));

        TEST_BOOLEAN_TRUE(s.contains(string_t("ab")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("abc")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("abcd")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("abcde")));

        TEST_BOOLEAN_FALSE(s.contains(string_t("aa")));
        TEST_BOOLEAN_TRUE(s.contains(string_t("bcde")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("acde")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("abde")));
        TEST_BOOLEAN_FALSE(s.contains(string_t("abce")));
    }

    {
        TEST_BOOLEAN_TRUE(s.contains('a'));
        TEST_BOOLEAN_TRUE(s.contains('b'));
        TEST_BOOLEAN_TRUE(s.contains('c'));
        TEST_BOOLEAN_TRUE(s.contains('d'));
        TEST_BOOLEAN_TRUE(s.contains('e'));
        TEST_BOOLEAN_TRUE(s.contains('i'));
        TEST_BOOLEAN_TRUE(s.contains('o'));
        TEST_BOOLEAN_TRUE(s.contains('u'));
        TEST_BOOLEAN_TRUE(s.contains('x'));
        TEST_BOOLEAN_TRUE(s.contains('y'));
        TEST_BOOLEAN_TRUE(s.contains('z'));

        TEST_BOOLEAN_FALSE(s.contains(' '));
        TEST_BOOLEAN_FALSE(s.contains('*'));
    }
}

static void test_contains_3()
{
    {
        string_t const s("abdabeabcab");

        {
            TEST_BOOLEAN_TRUE(s.contains("abc"));
        }
    }

    {
        string_t const s("abdabeabfab");

        {
            TEST_BOOLEAN_FALSE(s.contains("abc"));
        }
    }

    {
        string_t const s("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab");

        {
            TEST_BOOLEAN_TRUE(s.contains("ab"));
            TEST_BOOLEAN_FALSE(s.contains("ac"));
        }
    }
}

static void test_ends_with_1()
{
    string_t const s;

    {
        TEST_BOOLEAN_TRUE(s.ends_with(""));
        TEST_BOOLEAN_FALSE(s.ends_with("a"));
        TEST_BOOLEAN_FALSE(s.ends_with("b"));
        TEST_BOOLEAN_FALSE(s.ends_with("c"));
        TEST_BOOLEAN_FALSE(s.ends_with("d"));
        TEST_BOOLEAN_FALSE(s.ends_with("e"));
        TEST_BOOLEAN_FALSE(s.ends_with("i"));
        TEST_BOOLEAN_FALSE(s.ends_with("o"));
        TEST_BOOLEAN_FALSE(s.ends_with("u"));
        TEST_BOOLEAN_FALSE(s.ends_with("x"));
        TEST_BOOLEAN_FALSE(s.ends_with("y"));
        TEST_BOOLEAN_FALSE(s.ends_with("z"));

        TEST_BOOLEAN_FALSE(s.ends_with("yz"));
        TEST_BOOLEAN_FALSE(s.ends_with("xyz"));
        TEST_BOOLEAN_FALSE(s.ends_with("wxyz"));
        TEST_BOOLEAN_FALSE(s.ends_with("vwxyz"));

        TEST_BOOLEAN_FALSE(s.ends_with("aa"));
        TEST_BOOLEAN_FALSE(s.ends_with("bcde"));
        TEST_BOOLEAN_FALSE(s.ends_with("acde"));
        TEST_BOOLEAN_FALSE(s.ends_with("abde"));
        TEST_BOOLEAN_FALSE(s.ends_with("abce"));
    }

    {
        TEST_BOOLEAN_TRUE(s.ends_with(string_t("")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("a")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("b")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("c")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("d")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("e")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("i")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("o")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("u")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("x")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("y")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("z")));

        TEST_BOOLEAN_FALSE(s.ends_with(string_t("yz")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("xyz")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("wxyz")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("vwxyz")));

        TEST_BOOLEAN_FALSE(s.ends_with(string_t("aa")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("bcde")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("acde")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("abde")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("abce")));
    }


    {
        TEST_BOOLEAN_FALSE(s.ends_with('a'));
        TEST_BOOLEAN_FALSE(s.ends_with('b'));
        TEST_BOOLEAN_FALSE(s.ends_with('c'));
        TEST_BOOLEAN_FALSE(s.ends_with('d'));
        TEST_BOOLEAN_FALSE(s.ends_with('e'));
        TEST_BOOLEAN_FALSE(s.ends_with('i'));
        TEST_BOOLEAN_FALSE(s.ends_with('o'));
        TEST_BOOLEAN_FALSE(s.ends_with('u'));
        TEST_BOOLEAN_FALSE(s.ends_with('x'));
        TEST_BOOLEAN_FALSE(s.ends_with('y'));
        TEST_BOOLEAN_FALSE(s.ends_with('z'));
    }
}

static void test_ends_with_2()
{
    string_t const s(alphabet);

    {
        TEST_BOOLEAN_TRUE(s.ends_with(""));
        TEST_BOOLEAN_FALSE(s.ends_with("a"));
        TEST_BOOLEAN_FALSE(s.ends_with("b"));
        TEST_BOOLEAN_FALSE(s.ends_with("c"));
        TEST_BOOLEAN_FALSE(s.ends_with("d"));
        TEST_BOOLEAN_FALSE(s.ends_with("e"));
        TEST_BOOLEAN_FALSE(s.ends_with("i"));
        TEST_BOOLEAN_FALSE(s.ends_with("o"));
        TEST_BOOLEAN_FALSE(s.ends_with("u"));
        TEST_BOOLEAN_FALSE(s.ends_with("x"));
        TEST_BOOLEAN_FALSE(s.ends_with("y"));
        TEST_BOOLEAN_TRUE(s.ends_with("z"));

        TEST_BOOLEAN_TRUE(s.ends_with("yz"));
        TEST_BOOLEAN_TRUE(s.ends_with("xyz"));
        TEST_BOOLEAN_TRUE(s.ends_with("wxyz"));
        TEST_BOOLEAN_TRUE(s.ends_with("vwxyz"));

        TEST_BOOLEAN_FALSE(s.ends_with("aa"));
        TEST_BOOLEAN_FALSE(s.ends_with("bcde"));
        TEST_BOOLEAN_FALSE(s.ends_with("acde"));
        TEST_BOOLEAN_FALSE(s.ends_with("abde"));
        TEST_BOOLEAN_FALSE(s.ends_with("abce"));
    }

    {
        TEST_BOOLEAN_TRUE(s.ends_with(string_t("")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("a")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("b")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("c")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("d")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("e")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("i")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("o")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("u")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("x")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("y")));
        TEST_BOOLEAN_TRUE(s.ends_with(string_t("z")));

        TEST_BOOLEAN_TRUE(s.ends_with(string_t("yz")));
        TEST_BOOLEAN_TRUE(s.ends_with(string_t("xyz")));
        TEST_BOOLEAN_TRUE(s.ends_with(string_t("wxyz")));
        TEST_BOOLEAN_TRUE(s.ends_with(string_t("vwxyz")));

        TEST_BOOLEAN_FALSE(s.ends_with(string_t("aa")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("bcde")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("acde")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("abde")));
        TEST_BOOLEAN_FALSE(s.ends_with(string_t("abce")));
    }


    {
        TEST_BOOLEAN_FALSE(s.ends_with('a'));
        TEST_BOOLEAN_FALSE(s.ends_with('b'));
        TEST_BOOLEAN_FALSE(s.ends_with('c'));
        TEST_BOOLEAN_FALSE(s.ends_with('d'));
        TEST_BOOLEAN_FALSE(s.ends_with('e'));
        TEST_BOOLEAN_FALSE(s.ends_with('i'));
        TEST_BOOLEAN_FALSE(s.ends_with('o'));
        TEST_BOOLEAN_FALSE(s.ends_with('u'));
        TEST_BOOLEAN_FALSE(s.ends_with('x'));
        TEST_BOOLEAN_FALSE(s.ends_with('y'));
        TEST_BOOLEAN_TRUE(s.ends_with('z'));
    }
}
#endif


// accessors

static void test_at_1()
{
    string_t    s("abc");

    TEST_CHAR_EQ('a', s.at(0u));
    TEST_CHAR_EQ('b', s.at(1u));
    TEST_CHAR_EQ('c', s.at(2u));
}

static void test_at_2()
{
    string_t const s("abc");

    TEST_CHAR_EQ('a', s.at(0u));
    TEST_CHAR_EQ('b', s.at(1u));
    TEST_CHAR_EQ('c', s.at(2u));
}

static void test_at_3()
{
    string_t    s;

    s.at(0u);
}

static void test_at_4()
{
    string_t const s("abc");

    s.at(3u);
}

static void test_index_1()
{
    string_t    s("abc");

    TEST_CHAR_EQ('a', s[0u]);
    TEST_CHAR_EQ('b', s[1u]);
    TEST_CHAR_EQ('c', s[2u]);
}

static void test_index_2()
{
    string_t const s("abc");

    TEST_CHAR_EQ('a', s[0u]);
    TEST_CHAR_EQ('b', s[1u]);
    TEST_CHAR_EQ('c', s[2u]);
    TEST_CHAR_EQ('\0', s[3u]);
}

static void test_copy()
{
    string_t const s_alphabet(alphabet);

    TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", s_alphabet);

    {
        string_t    s;
        char        dest[101];
        size_t      cch = s.copy(&dest[0], STLSOFT_NUM_ELEMENTS(dest), 0);

        TEST_INT_EQ(0u, cch);
    }

#ifndef USE_std_string

    {
        string_t    s;
        char        dest[101];
        size_t      cch = s.copy(&dest[0], STLSOFT_NUM_ELEMENTS(dest), 10);

        TEST_INT_EQ(0u, cch);
    }
#endif

    {
        string_t    s("abc");
        char        dest[101];
        size_t      cch = s.copy(&dest[0], STLSOFT_NUM_ELEMENTS(dest), 0);

        TEST_INT_EQ(3u, cch);
    }

    {
        string_t    s("abc");
        char        dest[101];
        size_t      cch = s.copy(&dest[0], STLSOFT_NUM_ELEMENTS(dest), 2);

        TEST_INT_EQ(1u, cch);
    }

    {
        string_t    s("abc");
        char        dest[101];
        size_t      cch = s.copy(&dest[0], STLSOFT_NUM_ELEMENTS(dest), 3);

        TEST_INT_EQ(0u, cch);
    }

    {
        char dest[26 + 1] = { 0 };

        size_t n = s_alphabet.copy(&dest[0], 26);
        dest[26] = '\0';

        TEST_INT_EQ(26u, n);
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", dest);
    }

    {
        char dest[20 + 1] = { 0 };

        size_t n = s_alphabet.copy(&dest[0], 20);
        dest[20] = '\0';

        TEST_INT_EQ(20u, n);
        TEST_MS_EQ("abcdefghijklmnopqrst", dest);
    }

    {
        char dest[20 + 1] = { 0 };

        size_t n = s_alphabet.copy(&dest[0], 20, 6);
        dest[20] = '\0';

        TEST_INT_EQ(20u, n);
        TEST_MS_EQ("ghijklmnopqrstuvwxyz", dest);
    }

    {
        char dest[10 + 1] = { 0 };

        size_t n = s_alphabet.copy(&dest[0], 20, 16);
        dest[10] = '\0';

        TEST_INT_EQ(10u, n);
        TEST_MS_EQ("qrstuvwxyz", dest);
    }
}

static void test_substr()
{
    string_t const  s1("abcdefghi");
    string_t        s2 = s1.substr(0);
    string_t        s3 = s1.substr(0, s1.size());
    string_t        s4 = s1.substr(0, s1.size() * 2);
    string_t        s5 = s1.substr();

    TEST_MS_EQ(s1, s2);
    TEST_MS_EQ(s1, s3);
    TEST_MS_EQ(s1, s4);
    TEST_MS_EQ(s1, s5);
}

static void test_substr_throw()
{
    string_t const  s1("abcdefghi");
    string_t        s2 = s1.substr(s1.size() + 1);

    TEST_FAIL("should not get here");
}


// search

#ifdef USE_std_string

static void test_find_char()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find('\0'));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find('\0'));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(0u, s.find('a'));
        TEST_INT_EQ(1u, s.find('b', 0u));
        TEST_INT_EQ(1u, s.find('b', 1u));
        TEST_INT_EQ(25u, s.find('z'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find('A'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find('a', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find('\0'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find('\0', 1u));
    }
}

static void test_find_c_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find("abc"));
        TEST_INT_EQ(0u, s.find(""));
        TEST_INT_EQ(0u, s.find("", 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 2u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 3u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 4u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 5u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 6u));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find("abc"));
        TEST_INT_EQ(0u, s.find(""));
        TEST_INT_EQ(0u, s.find("", 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 2u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 3u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 4u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 5u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 6u));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(~string_t::size_type(0u), s.find("abc", 4u));
        TEST_INT_EQ(0u, s.find(""));
        TEST_INT_EQ(0u, s.find("", 0u));
        TEST_INT_EQ(1u, s.find("", 1u));
        TEST_INT_EQ(2u, s.find("", 2u));
        TEST_INT_EQ(3u, s.find("", 3u));
        TEST_INT_EQ(4u, s.find("", 4u));
        TEST_INT_EQ(5u, s.find("", 5u));
        TEST_INT_EQ(6u, s.find("", 6u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 7u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("", 8u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(0u, s.find("abc"));
        TEST_INT_EQ(1u, s.find("bcd", 0u));
        TEST_INT_EQ(1u, s.find("bcd", 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("bdc", 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("bdc", 1u));
        TEST_INT_EQ(25u, s.find("z"));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("A"));
        TEST_INT_EQ(~string_t::size_type(0u), s.find("a", 1u));
    }
}

static void test_find_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find(string_t("abc")));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find(string_t("abc")));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(~string_t::size_type(0u), s.find("abc", 4u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(0u, s.find(string_t("abc")));
        TEST_INT_EQ(1u, s.find(string_t("bcd"), 0u));
        TEST_INT_EQ(1u, s.find(string_t("bcd"), 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find(string_t("bdc"), 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find(string_t("bdc"), 1u));
        TEST_INT_EQ(25u, s.find(string_t("z")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find(string_t("A")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find(string_t("a"), 1u));
    }
}

static void test_rfind_char()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.rfind('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind('\0'));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.rfind('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind('\0'));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(3u, s.rfind('a'));
        TEST_INT_EQ(0u, s.rfind('a', 0u));
        TEST_INT_EQ(0u, s.rfind('a', 1u));
        TEST_INT_EQ(0u, s.rfind('a', 2u));
        TEST_INT_EQ(3u, s.rfind('a', 3u));
        TEST_INT_EQ(3u, s.rfind('a', 4u));
        TEST_INT_EQ(3u, s.rfind('a', 5u));
        TEST_INT_EQ(3u, s.rfind('a', 6u));
        TEST_INT_EQ(3u, s.rfind('a', 100u));

        TEST_INT_EQ(4u, s.rfind('b'));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind('b', 0u));
        TEST_INT_EQ(1u, s.rfind('b', 1u));
        TEST_INT_EQ(1u, s.rfind('b', 2u));
        TEST_INT_EQ(1u, s.rfind('b', 3u));
        TEST_INT_EQ(4u, s.rfind('b', 4u));
        TEST_INT_EQ(4u, s.rfind('b', 5u));
        TEST_INT_EQ(4u, s.rfind('b', 6u));
        TEST_INT_EQ(4u, s.rfind('b', 100u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(0u, s.rfind('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind('b', 0u));
        TEST_INT_EQ(1u, s.rfind('b', 1u));
        TEST_INT_EQ(1u, s.rfind('b', 1u));
        TEST_INT_EQ(25u, s.rfind('z'));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind('A'));
        TEST_INT_EQ(0u, s.rfind('a', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind('\0'));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind('\0', 1u));
    }
}

static void test_rfind_c_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.rfind("abc"));
        TEST_INT_EQ(0u, s.rfind(""));
        TEST_INT_EQ(0u, s.rfind("", 0u));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.rfind("abc"));
        TEST_INT_EQ(0u, s.rfind(""));
        TEST_INT_EQ(0u, s.rfind("", 0u));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(3u, s.rfind("abc"));
        TEST_INT_EQ(3u, s.rfind("abc", 7u));
        TEST_INT_EQ(3u, s.rfind("abc", 6u));
        TEST_INT_EQ(3u, s.rfind("abc", 5u));
        TEST_INT_EQ(3u, s.rfind("abc", 4u));
        TEST_INT_EQ(3u, s.rfind("abc", 3u));
        TEST_INT_EQ(0u, s.rfind("abc", 2u));
        TEST_INT_EQ(0u, s.rfind("abc", 1u));
        TEST_INT_EQ(0u, s.rfind("abc", 0u));
        TEST_INT_EQ(6u, s.rfind(""));
        TEST_INT_EQ(0u, s.rfind("", 0u));
        TEST_INT_EQ(1u, s.rfind("", 1u));
        TEST_INT_EQ(2u, s.rfind("", 2u));
        TEST_INT_EQ(3u, s.rfind("", 3u));
        TEST_INT_EQ(4u, s.rfind("", 4u));
        TEST_INT_EQ(5u, s.rfind("", 5u));
        TEST_INT_EQ(6u, s.rfind("", 6u));
        TEST_INT_EQ(6u, s.rfind("", 7u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(0u, s.rfind("abc"));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind("bcd", 0u));
        TEST_INT_EQ(1u, s.rfind("bcd", 1u));
        TEST_INT_EQ(1u, s.rfind("bcd", 2u));
        TEST_INT_EQ(1u, s.rfind("bcd", 3u));
        TEST_INT_EQ(1u, s.rfind("bcd", 4u));
        TEST_INT_EQ(1u, s.rfind("bcd", 5u));
        TEST_INT_EQ(1u, s.rfind("bcd", 6u));
        TEST_INT_EQ(1u, s.rfind("bcd", 7u));
        TEST_INT_EQ(1u, s.rfind("bcd", 100u));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind("bdc", 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind("bdc", 1u));
        TEST_INT_EQ(25u, s.rfind("z"));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind("A"));
        TEST_INT_EQ(0u, s.rfind("a", 1u));
    }
}

static void test_rfind_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.rfind(string_t("abc")));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.rfind(string_t("abc")));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(3u, s.rfind("abc"));
        TEST_INT_EQ(0u, s.rfind("abc", 0u));
        TEST_INT_EQ(0u, s.rfind("abc", 1u));
        TEST_INT_EQ(0u, s.rfind("abc", 2u));
        TEST_INT_EQ(3u, s.rfind("abc", 3u));
        TEST_INT_EQ(3u, s.rfind("abc", 4u));
        TEST_INT_EQ(3u, s.rfind("abc", 5u));
        TEST_INT_EQ(3u, s.rfind("abc", 6u));
        TEST_INT_EQ(3u, s.rfind("abc", 100u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(0u, s.rfind(string_t("abc")));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind(string_t("bcd"), 0u));
        TEST_INT_EQ(1u, s.rfind(string_t("bcd"), 1u));
        TEST_INT_EQ(1u, s.rfind(string_t("bcd"), 2u));
        TEST_INT_EQ(1u, s.rfind(string_t("bcd"), 3u));
        TEST_INT_EQ(1u, s.rfind(string_t("bcd"), 4u));
        TEST_INT_EQ(1u, s.rfind(string_t("bcd"), 5u));
        TEST_INT_EQ(1u, s.rfind(string_t("bcd"), 10u));
        TEST_INT_EQ(1u, s.rfind(string_t("bcd"), 20u));
        TEST_INT_EQ(1u, s.rfind(string_t("bcd"), 100u));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind(string_t("bdc"), 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind(string_t("bdc"), 1u));
        TEST_INT_EQ(25u, s.rfind(string_t("z")));
        TEST_INT_EQ(~string_t::size_type(0u), s.rfind(string_t("A")));
        TEST_INT_EQ(0u, s.rfind(string_t("a")));
        TEST_INT_EQ(0u, s.rfind(string_t("a"), 0u));
        TEST_INT_EQ(0u, s.rfind(string_t("a"), 1u));
    }
}

static void test_find_first_of_char()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of('\0'));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of('\0'));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(0u, s.find_first_of('a'));
        TEST_INT_EQ(1u, s.find_first_of('b', 0u));
        TEST_INT_EQ(1u, s.find_first_of('b', 1u));
        TEST_INT_EQ(25u, s.find_first_of('z'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of('A'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of('a', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of('\0'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of('\0', 1u));
    }
}

static void test_find_first_of_c_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of("abc"));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of("abc"));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of("defghijklmnopqrstuvwxyz", 4u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(0u, s.find_first_of("abc"));
        TEST_INT_EQ(1u, s.find_first_of("bcd", 0u));
        TEST_INT_EQ(1u, s.find_first_of("dcb", 0u));
        TEST_INT_EQ(1u, s.find_first_of("bcd", 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of("BDC", 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of("aBDC", 1u));
        TEST_INT_EQ(25u, s.find_first_of("z"));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of("A"));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of("a", 1u));
    }
}

static void test_find_first_of_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of(string_t("abc")));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of(string_t("abc")));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of(string_t("defghijklmnopqrstuvwxyz"), 4u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(0u, s.find_first_of(string_t("abc")));
        TEST_INT_EQ(1u, s.find_first_of(string_t("bcd"), 0u));
        TEST_INT_EQ(1u, s.find_first_of(string_t("dcb"), 0u));
        TEST_INT_EQ(1u, s.find_first_of(string_t("bcd"), 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of(string_t("BDC"), 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of(string_t("aBDC"), 1u));
        TEST_INT_EQ(25u, s.find_first_of(string_t("z")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of(string_t("A")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_of(string_t("a"), 1u));
    }
}

static void test_find_last_of_char()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('\0'));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('\0'));
    }

    {
        string_t    s("a");

        TEST_INT_EQ(0u, s.find_last_of('a'));
        TEST_INT_EQ(0u, s.find_last_of('a', 1u));
        TEST_INT_EQ(0u, s.find_last_of('a', 0u));
        TEST_INT_EQ(0u, s.find_last_of('a', 2u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('\0'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('\0', 1u));
    }

    {
        string_t    s("ab");

        TEST_INT_EQ(0u, s.find_last_of('a'));
        TEST_INT_EQ(0u, s.find_last_of('a', 4u));
        TEST_INT_EQ(0u, s.find_last_of('a', 3u));
        TEST_INT_EQ(0u, s.find_last_of('a', 2u));
        TEST_INT_EQ(0u, s.find_last_of('a', 1u));
        TEST_INT_EQ(0u, s.find_last_of('a', 0u));

        TEST_INT_EQ(1u, s.find_last_of('b'));
        TEST_INT_EQ(1u, s.find_last_of('b', 4u));
        TEST_INT_EQ(1u, s.find_last_of('b', 3u));
        TEST_INT_EQ(1u, s.find_last_of('b', 2u));
        TEST_INT_EQ(1u, s.find_last_of('b', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('b', 0u));
    }

    {
        string_t    s("abab");

        TEST_INT_EQ(2u, s.find_last_of('a'));
        TEST_INT_EQ(2u, s.find_last_of('a', 4u));
        TEST_INT_EQ(2u, s.find_last_of('a', 3u));
        TEST_INT_EQ(2u, s.find_last_of('a', 2u));
        TEST_INT_EQ(0u, s.find_last_of('a', 1u));
        TEST_INT_EQ(0u, s.find_last_of('a', 0u));

        TEST_INT_EQ(3u, s.find_last_of('b'));
        TEST_INT_EQ(3u, s.find_last_of('b', 4u));
        TEST_INT_EQ(3u, s.find_last_of('b', 3u));
        TEST_INT_EQ(1u, s.find_last_of('b', 2u));
        TEST_INT_EQ(1u, s.find_last_of('b', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('b', 0u));
    }

    {
        string_t    s("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");

        TEST_INT_EQ(26u, s.find_last_of('a'));
        TEST_INT_EQ(26u, s.find_last_of('a', 51u));
        TEST_INT_EQ(26u, s.find_last_of('a', 27u));
        TEST_INT_EQ(26u, s.find_last_of('a', 26u));
        TEST_INT_EQ(0u, s.find_last_of('a', 25u));
        TEST_INT_EQ(0u, s.find_last_of('a', 1u));
        TEST_INT_EQ(0u, s.find_last_of('a', 0u));

        TEST_INT_EQ(27u, s.find_last_of('b'));
        TEST_INT_EQ(27u, s.find_last_of('b', 51u));
        TEST_INT_EQ(27u, s.find_last_of('b', 50u));
        TEST_INT_EQ(27u, s.find_last_of('b', 28u));
        TEST_INT_EQ(27u, s.find_last_of('b', 27u));
        TEST_INT_EQ(1u, s.find_last_of('b', 26u));
        TEST_INT_EQ(1u, s.find_last_of('b', 10u));
        TEST_INT_EQ(1u, s.find_last_of('b', 2u));
        TEST_INT_EQ(1u, s.find_last_of('b', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('b', 0u));

        TEST_INT_EQ(51u, s.find_last_of('z'));
        TEST_INT_EQ(51u, s.find_last_of('z', 51u));
        TEST_INT_EQ(25u, s.find_last_of('z', 50u));
        TEST_INT_EQ(25u, s.find_last_of('z', 26u));
        TEST_INT_EQ(25u, s.find_last_of('z', 25u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('z', 24u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('z', 10u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('z', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of('z', 0u));
    }
}

static void test_find_last_of_c_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("abc"));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("abc"));
    }

    {
        string_t    s("abc");

        TEST_INT_EQ(2u, s.find_last_of("abc"));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("defghijklmnopqrstuvwxyz", 4u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(2u, s.find_last_of("abc"));
        TEST_INT_EQ(0u, s.find_last_of("abc", 0u));
        TEST_INT_EQ(1u, s.find_last_of("abc", 1u));
        TEST_INT_EQ(2u, s.find_last_of("abc", 2u));
        TEST_INT_EQ(2u, s.find_last_of("abc", 3u));
        TEST_INT_EQ(2u, s.find_last_of("abc", 4u));
        TEST_INT_EQ(2u, s.find_last_of("abc", 20u));

        TEST_INT_EQ(2u, s.find_last_of("bca"));
        TEST_INT_EQ(0u, s.find_last_of("bca", 0u));
        TEST_INT_EQ(1u, s.find_last_of("bca", 1u));
        TEST_INT_EQ(2u, s.find_last_of("bca", 2u));
        TEST_INT_EQ(2u, s.find_last_of("bca", 3u));
        TEST_INT_EQ(2u, s.find_last_of("bca", 4u));
        TEST_INT_EQ(2u, s.find_last_of("bca", 20u));

        TEST_INT_EQ(2u, s.find_last_of("cab"));
        TEST_INT_EQ(0u, s.find_last_of("cab", 0u));
        TEST_INT_EQ(1u, s.find_last_of("cab", 1u));
        TEST_INT_EQ(2u, s.find_last_of("cab", 2u));
        TEST_INT_EQ(2u, s.find_last_of("cab", 3u));
        TEST_INT_EQ(2u, s.find_last_of("cab", 4u));
        TEST_INT_EQ(2u, s.find_last_of("cab", 20u));

        TEST_INT_EQ(3u, s.find_last_of("dcb"));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("dcb", 0u));
        TEST_INT_EQ(1u, s.find_last_of("dcb", 1u));
        TEST_INT_EQ(2u, s.find_last_of("dcb", 2u));
        TEST_INT_EQ(3u, s.find_last_of("dcb", 3u));
        TEST_INT_EQ(3u, s.find_last_of("dcb", 4u));
        TEST_INT_EQ(3u, s.find_last_of("dcb", 20u));

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("BDC"));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("BDC", 0u));

        TEST_INT_EQ(0u, s.find_last_of("aBDC"));
        TEST_INT_EQ(0u, s.find_last_of("aBDC", 0u));
        TEST_INT_EQ(0u, s.find_last_of("aBDC", 1u));
        TEST_INT_EQ(0u, s.find_last_of("aBDC", 20u));

        TEST_INT_EQ(1u, s.find_last_of("AbDC"));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("AbDC", 0u));
        TEST_INT_EQ(1u, s.find_last_of("AbDC", 1u));
        TEST_INT_EQ(1u, s.find_last_of("AbDC", 20u));

        TEST_INT_EQ(0u, s.find_last_of("a"));
        TEST_INT_EQ(0u, s.find_last_of("a", 0u));
        TEST_INT_EQ(0u, s.find_last_of("a", 2u));
        TEST_INT_EQ(0u, s.find_last_of("a", 20u));

        TEST_INT_EQ(25u, s.find_last_of("z"));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("z", 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("z", 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("z", 20u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("z", 24u));
        TEST_INT_EQ(25u, s.find_last_of("z", 25u));

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of("A"));
    }
}

static void test_find_last_of_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("abc")));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("abc")));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("abc")));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("defghijklmnopqrstuvwxyz"), 4u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(2u, s.find_last_of(string_t("abc")));
        TEST_INT_EQ(0u, s.find_last_of(string_t("abc"), 0u));
        TEST_INT_EQ(1u, s.find_last_of(string_t("abc"), 1u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("abc"), 2u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("abc"), 3u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("abc"), 4u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("abc"), 20u));

        TEST_INT_EQ(2u, s.find_last_of(string_t("bca")));
        TEST_INT_EQ(0u, s.find_last_of(string_t("bca"), 0u));
        TEST_INT_EQ(1u, s.find_last_of(string_t("bca"), 1u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("bca"), 2u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("bca"), 3u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("bca"), 4u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("bca"), 20u));

        TEST_INT_EQ(2u, s.find_last_of(string_t("cab")));
        TEST_INT_EQ(0u, s.find_last_of(string_t("cab"), 0u));
        TEST_INT_EQ(1u, s.find_last_of(string_t("cab"), 1u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("cab"), 2u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("cab"), 3u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("cab"), 4u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("cab"), 20u));

        TEST_INT_EQ(3u, s.find_last_of(string_t("dcb")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("dcb"), 0u));
        TEST_INT_EQ(1u, s.find_last_of(string_t("dcb"), 1u));
        TEST_INT_EQ(2u, s.find_last_of(string_t("dcb"), 2u));
        TEST_INT_EQ(3u, s.find_last_of(string_t("dcb"), 3u));
        TEST_INT_EQ(3u, s.find_last_of(string_t("dcb"), 4u));
        TEST_INT_EQ(3u, s.find_last_of(string_t("dcb"), 20u));

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("BDC")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("BDC"), 0u));

        TEST_INT_EQ(0u, s.find_last_of(string_t("aBDC")));
        TEST_INT_EQ(0u, s.find_last_of(string_t("aBDC"), 0u));
        TEST_INT_EQ(0u, s.find_last_of(string_t("aBDC"), 1u));
        TEST_INT_EQ(0u, s.find_last_of(string_t("aBDC"), 20u));

        TEST_INT_EQ(1u, s.find_last_of(string_t("AbDC")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("AbDC"), 0u));
        TEST_INT_EQ(1u, s.find_last_of(string_t("AbDC"), 1u));
        TEST_INT_EQ(1u, s.find_last_of(string_t("AbDC"), 20u));

        TEST_INT_EQ(0u, s.find_last_of(string_t("a")));
        TEST_INT_EQ(0u, s.find_last_of(string_t("a"), 0u));
        TEST_INT_EQ(0u, s.find_last_of(string_t("a"), 2u));
        TEST_INT_EQ(0u, s.find_last_of(string_t("a"), 20u));

        TEST_INT_EQ(25u, s.find_last_of(string_t("z")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("z"), 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("z"), 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("z"), 20u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("z"), 24u));
        TEST_INT_EQ(25u, s.find_last_of(string_t("z"), 25u));

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_of(string_t("A")));
    }
}

static void test_find_first_not_of_char()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('a'));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('a'));
    }

    {
        string_t    s("a");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('a', 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('a', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('a', 2u));

        TEST_INT_EQ(0u, s.find_first_not_of('b'));
        TEST_INT_EQ(0u, s.find_first_not_of('b', 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('b', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('b', 2u));
    }

    {
        string_t    s("ab");

        TEST_INT_EQ(1u, s.find_first_not_of('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('a', 4u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('a', 3u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('a', 2u));
        TEST_INT_EQ(1u, s.find_first_not_of('a', 1u));
        TEST_INT_EQ(1u, s.find_first_not_of('a', 0u));

        TEST_INT_EQ(0u, s.find_first_not_of('b'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('b', 4u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('b', 3u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('b', 2u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('b', 1u));
        TEST_INT_EQ(0u, s.find_first_not_of('b', 0u));
    }

    {
        string_t    s("abab");

        TEST_INT_EQ(1u, s.find_first_not_of('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('a', 4u));
        TEST_INT_EQ(3u, s.find_first_not_of('a', 3u));
        TEST_INT_EQ(3u, s.find_first_not_of('a', 2u));
        TEST_INT_EQ(1u, s.find_first_not_of('a', 1u));
        TEST_INT_EQ(1u, s.find_first_not_of('a', 0u));

        TEST_INT_EQ(0u, s.find_first_not_of('b'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('b', 4u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('b', 3u));
        TEST_INT_EQ(2u, s.find_first_not_of('b', 2u));
        TEST_INT_EQ(2u, s.find_first_not_of('b', 1u));
        TEST_INT_EQ(0u, s.find_first_not_of('b', 0u));
    }

    {
        string_t    s("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");

        TEST_INT_EQ(1u, s.find_first_not_of('a'));
        TEST_INT_EQ(51u, s.find_first_not_of('a', 51u));
        TEST_INT_EQ(27u, s.find_first_not_of('a', 27u));
        TEST_INT_EQ(27u, s.find_first_not_of('a', 26u));
        TEST_INT_EQ(25u, s.find_first_not_of('a', 25u));
        TEST_INT_EQ(1u, s.find_first_not_of('a', 1u));
        TEST_INT_EQ(1u, s.find_first_not_of('a', 0u));

        TEST_INT_EQ(0u, s.find_first_not_of('b'));
        TEST_INT_EQ(51u, s.find_first_not_of('b', 51u));
        TEST_INT_EQ(50u, s.find_first_not_of('b', 50u));
        TEST_INT_EQ(28u, s.find_first_not_of('b', 28u));
        TEST_INT_EQ(28u, s.find_first_not_of('b', 27u));
        TEST_INT_EQ(26u, s.find_first_not_of('b', 26u));
        TEST_INT_EQ(10u, s.find_first_not_of('b', 10u));
        TEST_INT_EQ(2u, s.find_first_not_of('b', 2u));
        TEST_INT_EQ(2u, s.find_first_not_of('b', 1u));
        TEST_INT_EQ(0u, s.find_first_not_of('b', 0u));

        TEST_INT_EQ(0u, s.find_first_not_of('z'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of('z', 51u));
        TEST_INT_EQ(50u, s.find_first_not_of('z', 50u));
        TEST_INT_EQ(26u, s.find_first_not_of('z', 26u));
        TEST_INT_EQ(26u, s.find_first_not_of('z', 25u));
        TEST_INT_EQ(24u, s.find_first_not_of('z', 24u));
        TEST_INT_EQ(10u, s.find_first_not_of('z', 10u));
        TEST_INT_EQ(1u, s.find_first_not_of('z', 1u));
        TEST_INT_EQ(0u, s.find_first_not_of('z', 0u));
    }
}

static void test_find_first_not_of_c_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of(("abc")));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of(("abc")));
    }

    {
        string_t    s("xyz");

        TEST_INT_EQ(0u, s.find_first_not_of(("abc")));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(0u, s.find_first_not_of(("defghijklmnopqrstuvwxyz"), 0u));
        TEST_INT_EQ(1u, s.find_first_not_of(("defghijklmnopqrstuvwxyz"), 1u));
        TEST_INT_EQ(2u, s.find_first_not_of(("defghijklmnopqrstuvwxyz"), 2u));
        TEST_INT_EQ(3u, s.find_first_not_of(("defghijklmnopqrstuvwxyz"), 3u));
        TEST_INT_EQ(4u, s.find_first_not_of(("defghijklmnopqrstuvwxyz"), 4u));
        TEST_INT_EQ(5u, s.find_first_not_of(("defghijklmnopqrstuvwxyz"), 5u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of(("defghijklmnopqrstuvwxyz"), 6u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of(("defghijklmnopqrstuvwxyz"), 7u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(3u, s.find_first_not_of(("abc")));
        TEST_INT_EQ(3u, s.find_first_not_of(("abc"), 0u));
        TEST_INT_EQ(3u, s.find_first_not_of(("abc"), 1u));
        TEST_INT_EQ(3u, s.find_first_not_of(("abc"), 2u));
        TEST_INT_EQ(3u, s.find_first_not_of(("abc"), 3u));
        TEST_INT_EQ(4u, s.find_first_not_of(("abc"), 4u));
        TEST_INT_EQ(0u, s.find_first_not_of(("dcb"), 0u));
        TEST_INT_EQ(4u, s.find_first_not_of(("bcd"), 1u));
        TEST_INT_EQ(0u, s.find_first_not_of(("BDC")));
        TEST_INT_EQ(0u, s.find_first_not_of(("BDC"), 0u));
        TEST_INT_EQ(1u, s.find_first_not_of(("aBDC"), 1u));
        TEST_INT_EQ(0u, s.find_first_not_of(("z")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of(("z"), 25u));
        TEST_INT_EQ(24u, s.find_first_not_of(("z"), 24u));
        TEST_INT_EQ(23u, s.find_first_not_of(("z"), 23u));
        TEST_INT_EQ(0u, s.find_first_not_of(("A")));
        TEST_INT_EQ(1u, s.find_first_not_of(("a"), 1u));
    }
}

static void test_find_first_not_of_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of(string_t("abc")));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of(string_t("abc")));
    }

    {
        string_t    s("xyz");

        TEST_INT_EQ(0u, s.find_first_not_of(string_t("abc")));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(0u, s.find_first_not_of(string_t("defghijklmnopqrstuvwxyz"), 0u));
        TEST_INT_EQ(1u, s.find_first_not_of(string_t("defghijklmnopqrstuvwxyz"), 1u));
        TEST_INT_EQ(2u, s.find_first_not_of(string_t("defghijklmnopqrstuvwxyz"), 2u));
        TEST_INT_EQ(3u, s.find_first_not_of(string_t("defghijklmnopqrstuvwxyz"), 3u));
        TEST_INT_EQ(4u, s.find_first_not_of(string_t("defghijklmnopqrstuvwxyz"), 4u));
        TEST_INT_EQ(5u, s.find_first_not_of(string_t("defghijklmnopqrstuvwxyz"), 5u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of(string_t("defghijklmnopqrstuvwxyz"), 6u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of(string_t("defghijklmnopqrstuvwxyz"), 7u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(3u, s.find_first_not_of(string_t("abc")));
        TEST_INT_EQ(3u, s.find_first_not_of(string_t("abc"), 0u));
        TEST_INT_EQ(3u, s.find_first_not_of(string_t("abc"), 1u));
        TEST_INT_EQ(3u, s.find_first_not_of(string_t("abc"), 2u));
        TEST_INT_EQ(3u, s.find_first_not_of(string_t("abc"), 3u));
        TEST_INT_EQ(4u, s.find_first_not_of(string_t("abc"), 4u));
        TEST_INT_EQ(0u, s.find_first_not_of(string_t("dcb"), 0u));
        TEST_INT_EQ(4u, s.find_first_not_of(string_t("bcd"), 1u));
        TEST_INT_EQ(0u, s.find_first_not_of(string_t("BDC")));
        TEST_INT_EQ(0u, s.find_first_not_of(string_t("BDC"), 0u));
        TEST_INT_EQ(1u, s.find_first_not_of(string_t("aBDC"), 1u));
        TEST_INT_EQ(0u, s.find_first_not_of(string_t("z")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_first_not_of(string_t("z"), 25u));
        TEST_INT_EQ(24u, s.find_first_not_of(string_t("z"), 24u));
        TEST_INT_EQ(23u, s.find_first_not_of(string_t("z"), 23u));
        TEST_INT_EQ(0u, s.find_first_not_of(string_t("A")));
        TEST_INT_EQ(1u, s.find_first_not_of(string_t("a"), 1u));
    }
}

static void test_find_last_not_of_char()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of('a'));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of('a'));
    }

    {
        string_t    s("a");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of('a'));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of('a', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of('a', 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of('a', 2u));

        TEST_INT_EQ(0u, s.find_last_not_of('b'));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 1u));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 0u));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 2u));
    }

    {
        string_t    s("ab");

        TEST_INT_EQ(1u, s.find_last_not_of('a'));
        TEST_INT_EQ(1u, s.find_last_not_of('a', 4u));
        TEST_INT_EQ(1u, s.find_last_not_of('a', 3u));
        TEST_INT_EQ(1u, s.find_last_not_of('a', 2u));
        TEST_INT_EQ(1u, s.find_last_not_of('a', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of('a', 0u));

        TEST_INT_EQ(0u, s.find_last_not_of('b'));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 4u));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 3u));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 2u));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 1u));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 0u));
    }

    {
        string_t    s("abab");

        TEST_INT_EQ(3u, s.find_last_not_of('a'));
        TEST_INT_EQ(3u, s.find_last_not_of('a', 4u));
        TEST_INT_EQ(3u, s.find_last_not_of('a', 3u));
        TEST_INT_EQ(1u, s.find_last_not_of('a', 2u));
        TEST_INT_EQ(1u, s.find_last_not_of('a', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of('a', 0u));

        TEST_INT_EQ(2u, s.find_last_not_of('b'));
        TEST_INT_EQ(2u, s.find_last_not_of('b', 4u));
        TEST_INT_EQ(2u, s.find_last_not_of('b', 3u));
        TEST_INT_EQ(2u, s.find_last_not_of('b', 2u));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 1u));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 0u));
    }

    {
        string_t    s("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");

        TEST_INT_EQ(51u, s.find_last_not_of('a'));
        TEST_INT_EQ(51u, s.find_last_not_of('a', 51u));
        TEST_INT_EQ(27u, s.find_last_not_of('a', 27u));
        TEST_INT_EQ(25u, s.find_last_not_of('a', 26u));
        TEST_INT_EQ(25u, s.find_last_not_of('a', 25u));
        TEST_INT_EQ(1u, s.find_last_not_of('a', 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of('a', 0u));

        TEST_INT_EQ(51u, s.find_last_not_of('b'));
        TEST_INT_EQ(51u, s.find_last_not_of('b', 51u));
        TEST_INT_EQ(50u, s.find_last_not_of('b', 50u));
        TEST_INT_EQ(28u, s.find_last_not_of('b', 28u));
        TEST_INT_EQ(26u, s.find_last_not_of('b', 27u));
        TEST_INT_EQ(26u, s.find_last_not_of('b', 26u));
        TEST_INT_EQ(10u, s.find_last_not_of('b', 10u));
        TEST_INT_EQ(2u, s.find_last_not_of('b', 2u));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 1u));
        TEST_INT_EQ(0u, s.find_last_not_of('b', 0u));

        TEST_INT_EQ(50u, s.find_last_not_of('z'));
        TEST_INT_EQ(50u, s.find_last_not_of('z', 51u));
        TEST_INT_EQ(50u, s.find_last_not_of('z', 50u));
        TEST_INT_EQ(26u, s.find_last_not_of('z', 26u));
        TEST_INT_EQ(24u, s.find_last_not_of('z', 25u));
        TEST_INT_EQ(24u, s.find_last_not_of('z', 24u));
        TEST_INT_EQ(10u, s.find_last_not_of('z', 10u));
        TEST_INT_EQ(1u, s.find_last_not_of('z', 1u));
        TEST_INT_EQ(0u, s.find_last_not_of('z', 0u));
    }
}

static void test_find_last_not_of_c_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of(("abc")));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of(("abc")));
    }

    {
        string_t    s("xyz");

        TEST_INT_EQ(2u, s.find_last_not_of(("abc")));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(0u, s.find_last_not_of(("defghijklmnopqrstuvwxyz"), 0u));
        TEST_INT_EQ(1u, s.find_last_not_of(("defghijklmnopqrstuvwxyz"), 1u));
        TEST_INT_EQ(2u, s.find_last_not_of(("defghijklmnopqrstuvwxyz"), 2u));
        TEST_INT_EQ(3u, s.find_last_not_of(("defghijklmnopqrstuvwxyz"), 3u));
        TEST_INT_EQ(4u, s.find_last_not_of(("defghijklmnopqrstuvwxyz"), 4u));
        TEST_INT_EQ(5u, s.find_last_not_of(("defghijklmnopqrstuvwxyz"), 5u));
        TEST_INT_EQ(5u, s.find_last_not_of(("defghijklmnopqrstuvwxyz"), 6u));
        TEST_INT_EQ(5u, s.find_last_not_of(("defghijklmnopqrstuvwxyz"), 7u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(25u, s.find_last_not_of(("abc")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of(("abc"), 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of(("abc"), 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of(("abc"), 2u));
        TEST_INT_EQ(3u, s.find_last_not_of(("abc"), 3u));
        TEST_INT_EQ(4u, s.find_last_not_of(("abc"), 4u));
        TEST_INT_EQ(0u, s.find_last_not_of(("dcb"), 0u));
        TEST_INT_EQ(0u, s.find_last_not_of(("bcd"), 1u));
        TEST_INT_EQ(25u, s.find_last_not_of(("BDC")));
        TEST_INT_EQ(0u, s.find_last_not_of(("BDC"), 0u));
        TEST_INT_EQ(1u, s.find_last_not_of(("aBDC"), 1u));
        TEST_INT_EQ(24u, s.find_last_not_of(("z")));
        TEST_INT_EQ(24u, s.find_last_not_of(("z"), 25u));
        TEST_INT_EQ(24u, s.find_last_not_of(("z"), 24u));
        TEST_INT_EQ(23u, s.find_last_not_of(("z"), 23u));
        TEST_INT_EQ(25u, s.find_last_not_of(("A")));
        TEST_INT_EQ(1u, s.find_last_not_of(("a"), 1u));
    }
}

static void test_find_last_not_of_string()
{
    {
        string_t    s;

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of(string_t("abc")));
    }

    {
        string_t    s("");

        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of(string_t("abc")));
    }

    {
        string_t    s("xyz");

        TEST_INT_EQ(2u, s.find_last_not_of(string_t("abc")));
    }

    {
        string_t    s("abcabc");

        TEST_INT_EQ(0u, s.find_last_not_of(string_t("defghijklmnopqrstuvwxyz"), 0u));
        TEST_INT_EQ(1u, s.find_last_not_of(string_t("defghijklmnopqrstuvwxyz"), 1u));
        TEST_INT_EQ(2u, s.find_last_not_of(string_t("defghijklmnopqrstuvwxyz"), 2u));
        TEST_INT_EQ(3u, s.find_last_not_of(string_t("defghijklmnopqrstuvwxyz"), 3u));
        TEST_INT_EQ(4u, s.find_last_not_of(string_t("defghijklmnopqrstuvwxyz"), 4u));
        TEST_INT_EQ(5u, s.find_last_not_of(string_t("defghijklmnopqrstuvwxyz"), 5u));
        TEST_INT_EQ(5u, s.find_last_not_of(string_t("defghijklmnopqrstuvwxyz"), 6u));
        TEST_INT_EQ(5u, s.find_last_not_of(string_t("defghijklmnopqrstuvwxyz"), 7u));
    }

    {
        string_t    s(alphabet);

        TEST_INT_EQ(25u, s.find_last_not_of(string_t("abc")));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of(string_t("abc"), 0u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of(string_t("abc"), 1u));
        TEST_INT_EQ(~string_t::size_type(0u), s.find_last_not_of(string_t("abc"), 2u));
        TEST_INT_EQ(3u, s.find_last_not_of(string_t("abc"), 3u));
        TEST_INT_EQ(4u, s.find_last_not_of(string_t("abc"), 4u));
        TEST_INT_EQ(0u, s.find_last_not_of(string_t("dcb"), 0u));
        TEST_INT_EQ(0u, s.find_last_not_of(string_t("bcd"), 1u));
        TEST_INT_EQ(25u, s.find_last_not_of(string_t("BDC")));
        TEST_INT_EQ(0u, s.find_last_not_of(string_t("BDC"), 0u));
        TEST_INT_EQ(1u, s.find_last_not_of(string_t("aBDC"), 1u));
        TEST_INT_EQ(24u, s.find_last_not_of(string_t("z")));
        TEST_INT_EQ(24u, s.find_last_not_of(string_t("z"), 25u));
        TEST_INT_EQ(24u, s.find_last_not_of(string_t("z"), 24u));
        TEST_INT_EQ(23u, s.find_last_not_of(string_t("z"), 23u));
        TEST_INT_EQ(25u, s.find_last_not_of(string_t("A")));
        TEST_INT_EQ(1u, s.find_last_not_of(string_t("a"), 1u));
    }
}
#endif


// traits

static void test_stlsoft_char_traits()
{
    {
        typedef stlsoft::char_traits<char> traits_t;

        // assign
        {
            char        buff4[4] = { '1', '2', '3', '4' };

            traits_t::assign(buff4, 3, 'a');

            TEST_MS_EQ_N("aaa4", buff4, 4);
        }

        // compare
        {
            {
                int const r = traits_t::compare("abc", "abc", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare("abcd", "abce", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare("a\0cd", "a\0ce", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare("a\0d", "a\0e", 3);

                TEST_INT_NE(0, r);
            }
        }

        // compare_max
        {
            {
                int const r = traits_t::compare_max("abc", "abc", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare_max("abcd", "abce", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare_max("a\0cd", "a\0ce", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare_max("a\0d", "a\0e", 3);

                TEST_INT_EQ(0, r);
            }
        }

        // find
        {
            {
                char buff4[4] = { '1', '2', '3', '4' };

                char const* i = traits_t::find(buff4, 4, '3');

                TEST_INT_EQ(2, i - buff4);
            }

            {
                char const* i = traits_t::find(alphabet, 26, 'm');

                TEST_INT_EQ(12, i - alphabet);
            }

            {
                char const* i = traits_t::find(alphabet, 11, 'm');

                TEST_PTR_EQ(ss_nullptr_k, i);
            }
        }

        // length
        {
            {
                ss_size_t const r = traits_t::length("");

                TEST_INT_EQ(0u, r);
            }

            {
                ss_size_t const r = traits_t::length("abc");

                TEST_INT_EQ(3u, r);
            }

            {
                ss_size_t const r = traits_t::length(alphabet);

                TEST_INT_EQ(26u, r);
            }
        }

        // length_max
        {
            {
                ss_size_t const r = traits_t::length_max("", 0);

                TEST_INT_EQ(0u, r);
            }

            {
                ss_size_t const r = traits_t::length_max("", 10);

                TEST_INT_EQ(0u, r);
            }

            {
                ss_size_t const r = traits_t::length_max("abc", 3);

                TEST_INT_EQ(3u, r);
            }

            {
                ss_size_t const r = traits_t::length_max("abc", 2);

                TEST_INT_EQ(2u, r);
            }

            {
                ss_size_t const r = traits_t::length_max("abc", 22);

                TEST_INT_EQ(3u, r);
            }

            {
                ss_size_t const r = traits_t::length_max(alphabet, 1000);

                TEST_INT_EQ(26u, r);
            }
        }
    }

    {
        typedef stlsoft::char_traits<wchar_t> traits_t;

        // assign
        {
            wchar_t buff4[4] = { '1', '2', '3', '4' };

            traits_t::assign(buff4, 3, L'a');

            TEST_WS_EQ_N(L"aaa4", buff4, 4);
        }

        // compare
        {
            {
                int const r = traits_t::compare(L"abc", L"abc", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare(L"abcd", L"abce", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare(L"a\0cd", L"a\0ce", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare(L"a\0d", L"a\0e", 3);

                TEST_INT_NE(0, r);
            }
        }

        // compare_max
        {
            {
                int const r = traits_t::compare_max(L"abc", L"abc", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare_max(L"abcd", L"abce", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare_max(L"a\0cd", L"a\0ce", 3);

                TEST_INT_EQ(0, r);
            }

            {
                int const r = traits_t::compare_max(L"a\0d", L"a\0e", 3);

                TEST_INT_EQ(0, r);
            }
        }

        // find
        {
            {
                wchar_t buff4[4] = { '1', '2', '3', '4' };

                wchar_t const* i = traits_t::find(buff4, 4, '3');

                TEST_INT_EQ(2, i - buff4);
            }

            {
                wchar_t const* i = traits_t::find(alphabet_w, 26, 'm');

                TEST_INT_EQ(12, i - alphabet_w);
            }

            {
                wchar_t const* i = traits_t::find(alphabet_w, 11, 'm');

                TEST_PTR_EQ(ss_nullptr_k, i);
            }
        }

        // length
        {
            {
                ss_size_t const r = traits_t::length(L"");

                TEST_INT_EQ(0u, r);
            }

            {
                ss_size_t const r = traits_t::length(L"abc");

                TEST_INT_EQ(3u, r);
            }

            {
                ss_size_t const r = traits_t::length(alphabet_w);

                TEST_INT_EQ(26u, r);
            }
        }

        // length_max
        {
            {
                ss_size_t const r = traits_t::length_max(L"", 0);

                TEST_INT_EQ(0u, r);
            }

            {
                ss_size_t const r = traits_t::length_max(L"", 10);

                TEST_INT_EQ(0u, r);
            }

            {
                ss_size_t const r = traits_t::length_max(L"abc", 3);

                TEST_INT_EQ(3u, r);
            }

            {
                ss_size_t const r = traits_t::length_max(L"abc", 2);

                TEST_INT_EQ(2u, r);
            }

            {
                ss_size_t const r = traits_t::length_max(L"abc", 22);

                TEST_INT_EQ(3u, r);
            }

            {
                ss_size_t const r = traits_t::length_max(alphabet_w, 1000);

                TEST_INT_EQ(26u, r);
            }
        }
    }
}

static void test_string_traits()
{
    {
        string_t    s = stlsoft::string_traits<string_t>::empty_string();

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
        TEST_INT_GE(0u, s.capacity());
        TEST_INT_NE(0u, s.max_size());
    }

    {
        string_t    s1;
        string_t    s2("abc");
        string_t    s3("def");

        string_t    s4 = stlsoft::string_traits<string_t>::construct(s1, 0u, s1.size());
        string_t    s5 = stlsoft::string_traits<string_t>::construct(s2, 0u, s2.size());
        string_t    s6 = stlsoft::string_traits<string_t>::construct(s3, 0u, s3.size());

        TEST_MS_EQ(s1, s4);
        TEST_MS_EQ(s2, s5);
        TEST_MS_EQ(s3, s6);
    }

    {
        string_t    s1;
        string_t    s2("abc");

        stlsoft::string_traits<string_t>::assign_inplace(s1, s2.begin(), s2.end());

        TEST_MS_EQ(s1, s2);
    }
}


// operators : concatenation

static void test_concatenation_1()
{
    string_t    s1(alphabet);
    string_t    s2(s1, 0, 10);
    string_t    s3(s1, 10, 10);
    string_t    s4(s1, 20, 6);
    string_t    s5 = s2 + s3 + s4;

    TEST_MS_EQ(s1, s5);
}

static void test_concatenation_2()
{
    string_t    s1(alphabet);
    string_t    s2 = s1.substr(0, 10);
    string_t    s3 = s1.substr(10, 10);
    string_t    s4 = s1.substr(20, 6);
    string_t    s5 = s2 + s3 + s4;

    TEST_MS_EQ(s1, s5);
}

#ifdef USE_std_string

static void test_concatenation_3()
{
    string_t    s1(alphabet);
    string_t    s2 = s1.substr(0, 10);
    string_t    s3 = s1;
                s3.erase(0, 10);
                s3.erase(10);
    string_t    s4 = s1.substr(20, 6);
    string_t    s5 = s2 + s3 + s4;

    TEST_MS_EQ(s1, s5);
}

static void test_concatenation_4()
{
    string_t    s1(alphabet);
    string_t    s2 = s1.substr(0, 10);
    string_t    s3 = s1;
                s3.erase(s3.begin(), s3.begin() + 10);
                s3.erase(s3.begin() + 10, s3.end() - 1);
                s3.erase(s3.end() - 1);
    string_t    s4 = s1.substr(20, 6);
    string_t    s5 = s2 + s3 + s4;

    TEST_MS_EQ(s1, s5);
}

static void test_concatenation_5()
{
    string_t    s1(alphabet);
    string_t    s2 = s1.substr(0, 10);
    string_t    s3 = s1;
                s3.erase(s3.begin(), s3.begin() + 10);
                s3.erase(s3.begin() + 10, s3.end() - 1);
                s3.erase(s3.end() - 1);
    string_t    s4 = s1.substr(20, 6);
    string_t    s5 = s2 + s3.c_str() + s4;

    TEST_MS_EQ(s1, s5);
}
#endif

static void test_concatenation_6()
{
    string_t    s;

    TEST_BOOLEAN_TRUE(s.empty());
    TEST_INT_EQ(0u, s.size());
    TEST_INT_GE(0u, s.capacity());
    TEST_MS_EQ("", s);

    s += 'a';

    TEST_BOOLEAN_FALSE(s.empty());
    TEST_INT_EQ(1u, s.size());
    TEST_INT_GE(1u, s.capacity());
    TEST_MS_EQ("a", s);

    s = s + 'b';

    TEST_BOOLEAN_FALSE(s.empty());
    TEST_INT_EQ(2u, s.size());
    TEST_INT_GE(2u, s.capacity());
    TEST_MS_EQ("ab", s);

    s = 'c' + s;

    TEST_BOOLEAN_FALSE(s.empty());
    TEST_INT_EQ(3u, s.size());
    TEST_INT_GE(3u, s.capacity());
    TEST_MS_EQ("cab", s);

    s = "" + s;

    TEST_BOOLEAN_FALSE(s.empty());
    TEST_INT_EQ(3u, s.size());
    TEST_INT_GE(3u, s.capacity());
    TEST_MS_EQ("cab", s);
}


// operators : insertion

static void test_insertion_1()
{
    string_t const  s1;
    string_t const  s2("abc");
    string_t const  s3("def");

    {
        std::stringstream   ss;

        ss
            << std::left
            << s1
            << s2
            << std::right
            << s3
            ;

        TEST_MS_EQ("abcdef", ss.str());
    }

    {
        SimpleStream    ss;

        ss
            << s1
            << s2
            << s3
            ;

        TEST_MS_EQ("abcdef", ss.str());
    }
}

static void test_insertion_2()
{
    string_t const  s2("abc");
    string_t const  s3("def");

    {
        std::stringstream ss;

        ss
            << std::setw(2)
            << std::left
            << s2
            << std::right
            << s3
            ;

        TEST_MS_EQ("abcdef", ss.str());
    }
}

static void test_insertion_3()
{
    string_t const  s1;
    string_t const  s2("abc");
    string_t const  s3("def");

    {
        std::stringstream ss;

        ss
            << std::setfill('_')
            << std::setw(4)
            << s1
            << std::setw(4) << std::left
            << s2
            << std::setw(4) << std::right
            << s3
            ;

        TEST_MS_EQ("____abc__def", ss.str());
    }
}

static void test_insertion_4()
{
    const std::size_t FIELD_WIDTH = 2000;
#if defined(_MSC_VER) &&\
    _MSC_VER == 1700

    STLSOFT_SUPPRESS_UNUSED(&FIELD_WIDTH);
# define FIELD_WIDTH (2000)
#endif

    string_t const  s1;
    string_t const  s2("abc");
    string_t const  s3("defg");

    std::stringstream   ss;

    ss
        << std::setfill('_')
        << std::setw(FIELD_WIDTH)
        << s1
        << std::setw(FIELD_WIDTH) << std::left
        << s2
        << std::setw(FIELD_WIDTH) << std::right
        << s3
        ;


#if __cplusplus >= 201402L
    std::string expected = ([&s2, &s3, FIELD_WIDTH]() {
#else
    struct Expected
    {
        static
        std::string
        fn(
            string_t const& s2
        ,   string_t const& s3
        )
#endif

        {
            std::string r;

            r.append(FIELD_WIDTH, '_');

            r.append(s2.data(), s2.size());
            r.append(FIELD_WIDTH - s2.size(), '_');

            r.append(FIELD_WIDTH - s3.size(), '_');
            r.append(s3.data(), s3.size());

            return r;
        }
#if __cplusplus >= 201402L
    })();
#else
    };

    std::string const expected = Expected::fn(s2, s3);
#endif

    TEST_MS_EQ(
        expected
        , ss.str());

#ifdef FIELD_WIDTH
# undef FIELD_WIDTH
#endif
} // anonymous namespace


// shims : sas

static void test_string_access_shims()
{
    {
        string_t    s;

        TEST_INT_EQ(0u, stlsoft::c_str_len_a(s));
        TEST_INT_EQ(0u, stlsoft::c_str_len(s));

        TEST_PTR_NE(NULL, stlsoft::c_str_data_a(s));
        TEST_MS_EQ("", stlsoft::c_str_data_a(s));

        TEST_PTR_NE(NULL, stlsoft::c_str_data(s));
        TEST_MS_EQ("", stlsoft::c_str_data(s));

        TEST_PTR_NE(NULL, stlsoft::c_str_ptr_a(s));
        TEST_MS_EQ("", stlsoft::c_str_ptr_a(s));

        TEST_PTR_NE(NULL, stlsoft::c_str_ptr(s));
        TEST_MS_EQ("", stlsoft::c_str_ptr(s));

        TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_a(s));

        TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null(s));
    }

    {
        wstring_t   s;

        TEST_INT_EQ(0u, stlsoft::c_str_len_w(s));
//      TEST_INT_EQ(0u, stlsoft::c_str_len(s));

        TEST_PTR_NE(NULL, stlsoft::c_str_data_w(s));
        TEST_WS_EQ(L"", stlsoft::c_str_data_w(s));

//      TEST_PTR_NE(NULL, stlsoft::c_str_data(s));
//      TEST_WS_EQ(L"", stlsoft::c_str_data(s));

        TEST_PTR_NE(NULL, stlsoft::c_str_ptr_w(s));
        TEST_WS_EQ(L"", stlsoft::c_str_ptr_w(s));

//      TEST_PTR_NE(NULL, stlsoft::c_str_ptr(s));
//      TEST_WS_EQ(L"", stlsoft::c_str_ptr(s));

        TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_w(s));

//      TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null(s));
    }

}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

