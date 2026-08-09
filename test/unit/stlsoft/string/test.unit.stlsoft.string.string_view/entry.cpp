/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.string.string_view/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::basic_string_view`.
 *
 * Created: 4th November 2008
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#ifdef _DEBUG
# define _CRT_SECURE_NO_DEPRECATE
# define _SCL_SECURE_NO_WARNINGS
#endif

#include <stlsoft/string/string_view.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
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
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if STLSOFT_VER_STLSOFT_STRING_HPP_STRING_VIEW_MAJOR > 3 || \
    (   STLSOFT_VER_STLSOFT_STRING_HPP_STRING_VIEW_MAJOR == 3 && \
        STLSOFT_VER_STLSOFT_STRING_HPP_STRING_VIEW_MINOR >= 4)

# define HAS_substr_                                        (1)
#endif /* 3.4+ */

#ifdef STLSOFT_STRING_VIEW_PROVIDE_c_str

# define HAS_c_str_
#endif /* STLSOFT_STRING_VIEW_PROVIDE_c_str */


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_types_exist();
    static void test_type_sizes();
    static void test_ctor_default();
    static void test_ctor_copy();
    static void test_ctor_range_1();
    static void test_ctor_range_2();
    static void test_ctor_range_3();
    static void test_swap_1();
    static void test_swap_2();
    static void test_swap_3();
    static void test_clear();
    static void test_get_allocator();
    static void test_front();
    static void test_back();
#ifdef HAS_c_str_
    static void test_refresh();
#endif /* HAS_c_str_ */
    static void test_reverse_iterators();
    static void test_copy();
#ifdef HAS_substr_

    static void test_substr();
    static void test_substr_2();
    static void test_substr_throw();
    static void test_substr_throw_2();
#endif /* HAS_substr_ */
    static void test_compare_1();
    static void test_compare_2();
    static void test_compare_3();
    static void test_compare_4();
    static void test_at_1();
    static void test_at_2();
    static void test_at_3();
    static void test_at_4();
    static void test_index_1();
    static void test_index_2();
    static void test_string_access_shims();
    static void test_insertion_1();
    static void test_insertion_2();
    static void test_insertion_3();
    static void test_insertion_4();
    static void test_string_traits();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSE_HELP_OR_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.string_view", verbosity))
    {
        XTESTS_RUN_CASE(test_types_exist);
        XTESTS_RUN_CASE(test_type_sizes);
        XTESTS_RUN_CASE(test_ctor_default);
        XTESTS_RUN_CASE(test_ctor_copy);
        XTESTS_RUN_CASE(test_ctor_range_1);
        XTESTS_RUN_CASE(test_ctor_range_2);
        XTESTS_RUN_CASE(test_ctor_range_3);
        XTESTS_RUN_CASE(test_swap_1);
        XTESTS_RUN_CASE(test_swap_2);
        XTESTS_RUN_CASE(test_swap_3);
        XTESTS_RUN_CASE(test_clear);
        XTESTS_RUN_CASE(test_get_allocator);
        XTESTS_RUN_CASE(test_front);
        XTESTS_RUN_CASE(test_back);
#ifdef HAS_c_str_
        XTESTS_RUN_CASE(test_refresh);
#endif /* HAS_c_str_ */
        XTESTS_RUN_CASE(test_reverse_iterators);
        XTESTS_RUN_CASE(test_copy);
#ifdef HAS_substr_

        XTESTS_RUN_CASE(test_substr);
        XTESTS_RUN_CASE(test_substr_2);
        XTESTS_RUN_CASE_THAT_THROWS(test_substr_throw, std::out_of_range);
        XTESTS_RUN_CASE_THAT_THROWS(test_substr_throw_2, std::out_of_range);
#endif /* HAS_substr_ */
        XTESTS_RUN_CASE(test_compare_1);
        XTESTS_RUN_CASE(test_compare_2);
        XTESTS_RUN_CASE(test_compare_3);
        XTESTS_RUN_CASE(test_compare_4);
        XTESTS_RUN_CASE(test_at_1);
        XTESTS_RUN_CASE(test_at_2);
        XTESTS_RUN_CASE_THAT_THROWS(test_at_3, std::out_of_range);
        XTESTS_RUN_CASE_THAT_THROWS(test_at_4, std::out_of_range);
        XTESTS_RUN_CASE(test_index_1);
        XTESTS_RUN_CASE(test_index_2);
        XTESTS_RUN_CASE(test_string_access_shims);
        XTESTS_RUN_CASE(test_insertion_1);
        XTESTS_RUN_CASE(test_insertion_2);
        XTESTS_RUN_CASE(test_insertion_3);
        XTESTS_RUN_CASE(test_insertion_4);
        XTESTS_RUN_CASE(test_string_traits);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

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


static void test_types_exist()
{
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::basic_string_view<char>));
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::basic_string_view<wchar_t>));
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::string_view));
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::wstring_view));

    TEST_PASSED();
}

    typedef stlsoft::string_view            string_v_t;
    typedef stlsoft::wstring_view           wstring_v_t;
    typedef stlsoft::basic_string_view<
        char
    ,   stlsoft::stlsoft_char_traits_safe<char>
    >                                       string_v_null_t;


static void test_type_sizes()
{
#ifdef HAS_c_str_

    STLSOFT_STATIC_ASSERT(sizeof(stlsoft::string_view) >= 3 * sizeof(void*));
    STLSOFT_STATIC_ASSERT(sizeof(stlsoft::wstring_view) >= 3 * sizeof(void*));
#else /* ? HAS_c_str_ */

    STLSOFT_STATIC_ASSERT(sizeof(stlsoft::string_view) >= 2 * sizeof(void*));
    STLSOFT_STATIC_ASSERT(sizeof(stlsoft::wstring_view) >= 2 * sizeof(void*));
#endif /* HAS_c_str_ */
}

static void test_ctor_default()
{
    {
        string_v_t  s;

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
        TEST_INT_GE(0u, s.capacity());
        TEST_INT_NE(0u, s.max_size());
    }

    {
        string_v_null_t s(static_cast<char const*>(NULL));

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
        TEST_INT_GE(0u, s.capacity());
        TEST_INT_NE(0u, s.max_size());
    }
}

static void test_ctor_copy()
{
    {
        string_v_t  s1;
        string_v_t  s2(s1);

        TEST_INT_EQ(s1.size(), s2.size());
        TEST_MS_EQ_N(s1, s2, s1.size());
    }

    {
        string_v_t  s1("abc");
        string_v_t  s2(s1);

        TEST_INT_EQ(s1.size(), s2.size());
        TEST_MS_EQ_N(s1, s2, s1.size());
    }

    {
        string_v_t  s1("abc");
        string_v_t  s2(s1, 0u, s1.size());

        TEST_INT_EQ(s1.size(), s2.size());
        TEST_MS_EQ_N(s1, s2, s1.size());
    }

    {
        string_v_t  s1("abc");
        string_v_t  s2(s1, 1u, s1.size() - 1u);

        TEST_INT_EQ(2u, s2.size());
        TEST_MS_EQ_N("bc", s2, s2.size());
    }
}

static void test_ctor_range_1()
{
    static const char   alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    string_v_t          s1(alphabet);
    string_v_t          s2(&alphabet[0], &alphabet[0] + STLSOFT_NUM_ELEMENTS(alphabet) -1);
    string_v_t const    s3(s1.begin(), s1.end());
    string_v_t          s4(s3.begin(), s3.end());

    TEST_MS_EQ_N(alphabet, s1, s1.size());
    TEST_MS_EQ_N(alphabet, s2, s2.size());
    TEST_MS_EQ_N(alphabet, s3, s3.size());
    TEST_MS_EQ_N(alphabet, s4, s4.size());

    TEST_PTR_EQ(alphabet, s1.base());
    TEST_PTR_EQ(alphabet, s2.base());
    TEST_PTR_EQ(alphabet, s3.base());
    TEST_PTR_EQ(alphabet, s4.base());
}

static void test_ctor_range_2()
{
    static const char   alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    string_v_t      s1(alphabet);
    string_v_t      s2(&alphabet[0], &alphabet[0] + STLSOFT_NUM_ELEMENTS(alphabet) -1);

    TEST_MS_EQ_N(alphabet, s1, s1.size());
    TEST_MS_EQ_N(alphabet, s2, s2.size());
}

static void test_ctor_range_3()
{
    static const char   alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    string_v_t      s1(alphabet);
    string_v_t      s2(s1, 0);
    string_v_t      s3(s1, 13);

    TEST_MS_EQ_N(alphabet, s2, s2.size());
    TEST_MS_EQ_N("nopqrstuvwxyz", s3, s3.size());
}

static void test_swap_1()
{
    {
        string_v_t  s1;
        string_v_t  s2;

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());

        s1.swap(s2);

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());
    }

    {
        string_v_t  s1("abc");
        string_v_t  s2;

        TEST_BOOLEAN_FALSE(s1.empty());
        TEST_INT_EQ(3u, s1.size());
        TEST_MS_EQ_N("abc", s1, s1.size());
        TEST_BOOLEAN_TRUE(s2.empty());

        s1.swap(s2);

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_FALSE(s2.empty());
        TEST_INT_EQ(3u, s2.size());
        TEST_MS_EQ_N("abc", s2, s2.size());
    }
}

static void test_swap_2()
{
    {
        string_v_t  s1;
        string_v_t  s2;

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());

        std::swap(s1, s2);

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());
    }

    {
        string_v_t  s1("abc");
        string_v_t  s2;

        TEST_BOOLEAN_FALSE(s1.empty());
        TEST_INT_EQ(3u, s1.size());
        TEST_MS_EQ_N("abc", s1, s1.size());
        TEST_BOOLEAN_TRUE(s2.empty());

        std::swap(s1, s2);

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_FALSE(s2.empty());
        TEST_INT_EQ(3u, s2.size());
        TEST_MS_EQ_N("abc", s2, s2.size());
    }
}

static void test_swap_3()
{
#if defined(STLSOFT_COMPILER_IS_MSVC) && \
    _MSC_VER < 1310
    using stlsoft::swap;
#endif

    {
        string_v_t  s1;
        string_v_t  s2;

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());

        swap(s1, s2);

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_TRUE(s2.empty());
    }

    {
        string_v_t  s1("abc");
        string_v_t  s2;

        TEST_BOOLEAN_FALSE(s1.empty());
        TEST_INT_EQ(3u, s1.size());
        TEST_MS_EQ_N("abc", s1, s1.size());
        TEST_BOOLEAN_TRUE(s2.empty());

        swap(s1, s2);

        TEST_BOOLEAN_TRUE(s1.empty());
        TEST_BOOLEAN_FALSE(s2.empty());
        TEST_INT_EQ(3u, s2.size());
        TEST_MS_EQ_N("abc", s2, s2.size());
    }
}

static void test_clear()
{
    {
        string_v_t  s;

        s.clear();

        TEST_INT_EQ(0u, s.size());
    }

    {
        string_v_t  s("abc");

        s.clear();

        TEST_INT_EQ(0u, s.size());
    }
}

static void test_get_allocator()
{
    string_v_t s;

    TEST(s.get_allocator() == string_v_t::allocator_type());
}

static void test_front()
{
    {
        string_v_t s1("abc");
        string_v_t s2(s1, 2);

        TEST_CHAR_EQ('a', s1.front());
        TEST_CHAR_EQ('c', s2.front());
    }
}

static void test_back()
{
    {
        string_v_t s1("abc");
        string_v_t s2(s1, 2);

        TEST_CHAR_EQ('c', s1.back());
        TEST_CHAR_EQ('c', s2.back());
    }
}

#ifdef HAS_c_str_

static void test_refresh()
{
    {
        string_v_t          s1("abcdefghijklmnopqrstuvwxyz");
        string_v_t          s2("abcdefghijklmnopqrstuvwxyz");

        char const* const   p1a =   s1.c_str();

        s1.refresh();

        char const* const   p2a =   s2.c_str();

        char const* const   p1b =   s1.c_str();

        if (p2a == p1a)
        {
            TEST_PTR_NE(p1a, p1b);
        }
    }
}
#endif /* HAS_c_str_ */

static void test_reverse_iterators()
{
    {
        string_v_t s("abcd");

        string_v_t::const_reverse_iterator ri = s.rbegin();

        TEST(s.rend() != ri);
        TEST_CHAR_EQ('d', *ri);

        ++ri;
        TEST(s.rend() != ri);
        TEST_CHAR_EQ('c', *ri);

        ri++;
        TEST(s.rend() != ri);
        TEST_CHAR_EQ('b', *ri);

        ++ri;
        TEST(s.rend() != ri);
        TEST_CHAR_EQ('a', *ri);

        ++ri;
        TEST(s.rend() == ri);
    }
}

static void test_copy()
{
    {
        string_v_t  s;
        char        buff[101];
        size_t      cch = s.copy(&buff[0], STLSOFT_NUM_ELEMENTS(buff), 0);

        TEST_INT_EQ(0u, cch);
    }

    {
        string_v_t  s("abc");
        char        buff[101];
        size_t      cch = s.copy(&buff[0], STLSOFT_NUM_ELEMENTS(buff), 0);

        TEST_INT_EQ(3u, cch);
    }

    {
        string_v_t  s("abc");
        char        buff[101];
        size_t      cch = s.copy(&buff[0], STLSOFT_NUM_ELEMENTS(buff), 2);

        TEST_INT_EQ(1u, cch);
    }

    {
        string_v_t  s("abc");
        char        buff[101];
        size_t      cch = s.copy(&buff[0], STLSOFT_NUM_ELEMENTS(buff), 3);

        TEST_INT_EQ(0u, cch);
    }

}

#ifdef HAS_substr_

static void test_substr()
{
    string_v_t const    s1("abcdefghi");
    string_v_t          s2 = s1.substr(0);
    string_v_t          s3 = s1.substr(0, s1.size());
    string_v_t          s4 = s1.substr(0, s1.size() * 2);
    string_v_t          s5 = s1.substr();

    TEST_MS_EQ_N(s1, s2, s2.size());
    TEST_MS_EQ_N(s1, s3, s3.size());
    TEST_MS_EQ_N(s1, s4, s4.size());
    TEST_MS_EQ_N(s1, s5, s5.size());
}

static void test_substr_2()
{
    string_v_t const    s1("abcdefghi");
    string_v_t          s2 = s1.substr(1);
    string_v_t          s3 = s1.substr(1, 3);
    string_v_t          s4 = s1.substr(7, 2);
    string_v_t          s5 = s1.substr(7, 50);

    TEST_MS_EQ_N("bcdefghi", s2, s2.size());
    TEST_MS_EQ_N("bcd", s3, s3.size());
    TEST_MS_EQ_N("hi", s4, s4.size());
    TEST_MS_EQ_N("hi", s5, s5.size());
}

static void test_substr_throw()
{
    string_v_t const    s1("abcdefghi");
    string_v_t          s2 = s1.substr(s1.size() + 1);

    TEST_FAIL("should not get here");
}

static void test_substr_throw_2()
{
    string_v_t const    s1("abcdefghi");
    string_v_t          s2 = s1.substr(s1.size() + 1, 1);

    TEST_FAIL("should not get here");
}
#endif /* HAS_substr_ */

static void test_compare_1()
{
    string_v_t  s1("abc");
    string_v_t  s2("def");

    TEST_BOOLEAN_TRUE(s1 != s2);
#ifdef HAS_c_str_
    TEST_BOOLEAN_TRUE(s1 != s2.c_str());
    TEST_BOOLEAN_TRUE(s1.c_str() != s2);
#endif /* HAS_c_str_ */
    TEST_MS_NE_N(s1, s2, s2.size());

    TEST_BOOLEAN_TRUE(s1 < s2);
#ifdef HAS_c_str_
    TEST_BOOLEAN_TRUE(s1 < s2.c_str());
    TEST_BOOLEAN_TRUE(s1.c_str() < s2);
#endif /* HAS_c_str_ */
    TEST_BOOLEAN_TRUE(s1 <= s2);
#ifdef HAS_c_str_
    TEST_BOOLEAN_TRUE(s1 <= s2.c_str());
    TEST_BOOLEAN_TRUE(s1.c_str() <= s2);
#endif /* HAS_c_str_ */
    TEST_BOOLEAN_TRUE(s2 > s1);
#ifdef HAS_c_str_
    TEST_BOOLEAN_TRUE(s2 > s1.c_str());
    TEST_BOOLEAN_TRUE(s2.c_str() > s1);
#endif /* HAS_c_str_ */
    TEST_BOOLEAN_TRUE(s2 >= s1);
#ifdef HAS_c_str_
    TEST_BOOLEAN_TRUE(s2 >= s1.c_str());
    TEST_BOOLEAN_TRUE(s2.c_str() >= s1);
#endif /* HAS_c_str_ */

    TEST_BOOLEAN_TRUE(s1 == s1);
#ifdef HAS_c_str_
    TEST_BOOLEAN_TRUE(s1 == s1.c_str());
    TEST_BOOLEAN_TRUE(s1.c_str() == s1);
#endif /* HAS_c_str_ */
}

static void test_compare_2()
{
    string_v_t  s1("abc");
    string_v_t  s2("def");

    TEST_INT_EQ(0, s1.compare(s1));
    TEST_INT_LT(0, s1.compare(s2));
    TEST_INT_GT(0, s2.compare(s1));


    TEST_INT_LT(0, s1.compare(0u, 2u, s2));
    TEST_INT_LT(0, s1.compare(0u, 3u, s2));
#ifdef HAS_c_str_
    TEST_INT_LT(0, s1.compare(0u, 3u, s2.c_str()));
//  TEST_INT_LT(0, s1.compare(0u, 4u, s2.c_str()));
    TEST_INT_LT(0, s1.compare(0u, 3u, s2.c_str(), s2.size()));
#endif /* HAS_c_str_ */

    string_v_t  s3("c");

    TEST_INT_EQ(0, s1.compare(3u, 0u, s2.substr(s2.size())));
    TEST_INT_EQ(0, s1.compare(2u, 2u, s3));
    TEST_INT_EQ(0, s1.compare(2u, 2u, s3));
    TEST_INT_EQ(0, s1.compare(2u, 3u, s3));
    TEST_INT_EQ(0, s1.compare(2u, 333u, s3));
}

static void test_compare_3()
{
    string_v_t  s1("def");

    TEST_INT_LT(0, s1.compare("ghi"));
    TEST_INT_LT(0, s1.compare(0u, s1.size(), "ghi", 3));
    TEST_INT_LT(0, s1.compare(0u, s1.size(), "ghi", 2));
    TEST_INT_LT(0, s1.compare(0u, s1.size(), "ghi", 1));
    TEST_INT_LT(0, s1.compare(0u, 2u, "ghi"));
    TEST_INT_LT(0, s1.compare(0u, 2u, "ghi", 3));
    TEST_INT_LT(0, s1.compare(0u, 2u, "ghi", 2));
    TEST_INT_LT(0, s1.compare(0u, 2u, "ghi", 1));
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
        string_v_t  s1("mno");
        string_v_t  s2("mnopqr");

        TEST_INT_LT(0, s1.compare(s2));
#ifdef HAS_c_str_
        TEST_INT_LT(0, s1.compare(s2.c_str()));
#endif /* HAS_c_str_ */
        TEST_INT_LT(0, s1.compare(0u, s1.size(), s2));
    }
}


static void test_at_1()
{
    string_v_t  s("abc");

    TEST_CHAR_EQ('a', s.at(0u));
    TEST_CHAR_EQ('b', s.at(1u));
    TEST_CHAR_EQ('c', s.at(2u));
}

static void test_at_2()
{
    string_v_t const    s("abc");

    TEST_CHAR_EQ('a', s.at(0u));
    TEST_CHAR_EQ('b', s.at(1u));
    TEST_CHAR_EQ('c', s.at(2u));
}

static void test_at_3()
{
    string_v_t  s;

    s.at(0u);
}

static void test_at_4()
{
    string_v_t const    s("abc");

    s.at(3u);
}


static void test_index_1()
{
    string_v_t  s("abc");

    TEST_CHAR_EQ('a', s[0u]);
    TEST_CHAR_EQ('b', s[1u]);
    TEST_CHAR_EQ('c', s[2u]);
}

static void test_index_2()
{
    string_v_t const    s("abc");

    TEST_CHAR_EQ('a', s[0u]);
    TEST_CHAR_EQ('b', s[1u]);
    TEST_CHAR_EQ('c', s[2u]);
    TEST_CHAR_EQ('\0', s[3u]);
}


static void test_string_access_shims()
{
    {
        string_v_t  s;

        TEST_INT_EQ(0u, stlsoft::c_str_len_a(s));
        TEST_INT_EQ(0u, stlsoft::c_str_len(s));

        TEST_PTR_NE(NULL, stlsoft::c_str_data_a(s));
        TEST_MS_EQ("", stlsoft::c_str_data_a(s));

        TEST_PTR_NE(NULL, stlsoft::c_str_data(s));
        TEST_MS_EQ("", stlsoft::c_str_data(s));

#ifdef HAS_c_str_

        TEST_PTR_NE(NULL, stlsoft::c_str_ptr_a(s));
        TEST_MS_EQ("", stlsoft::c_str_ptr_a(s));

        TEST_PTR_NE(NULL, stlsoft::c_str_ptr(s));
        TEST_MS_EQ("", stlsoft::c_str_ptr(s));

        TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_a(s));

        TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null(s));
#endif /* HAS_c_str_ */
    }

    {
        wstring_v_t s;

        TEST_INT_EQ(0u, stlsoft::c_str_len_w(s));
//      TEST_INT_EQ(0u, stlsoft::c_str_len(s));

        TEST_PTR_NE(NULL, stlsoft::c_str_data_w(s));
        TEST_WS_EQ(L"", stlsoft::c_str_data_w(s));

//      TEST_PTR_NE(NULL, stlsoft::c_str_data(s));
//      TEST_WS_EQ(L"", stlsoft::c_str_data(s));

#ifdef HAS_c_str_

        TEST_PTR_NE(NULL, stlsoft::c_str_ptr_w(s));
        TEST_WS_EQ(L"", stlsoft::c_str_ptr_w(s));

//      TEST_PTR_NE(NULL, stlsoft::c_str_ptr(s));
//      TEST_WS_EQ(L"", stlsoft::c_str_ptr(s));

        TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null_w(s));

//      TEST_PTR_EQ(NULL, stlsoft::c_str_ptr_null(s));
#endif /* HAS_c_str_ */
    }

}

static void test_insertion_1()
{
    string_v_t  s1;
    string_v_t  s2("abc");
    string_v_t  s3("def");

    {
        std::stringstream ss;

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
        SimpleStream ss;

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
    string_v_t  s2("abc");
    string_v_t  s3("def");

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
    string_v_t  s1;
    string_v_t  s2("abc");
    string_v_t  s3("def");

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

    string_v_t const    s1;
    string_v_t const    s2("abc");
    string_v_t const    s3("defg");

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
            string_v_t const&   s2
        ,   string_v_t const&   s3
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
}

static void test_string_traits()
{
    {
        string_v_t  s = stlsoft::string_traits<string_v_t>::empty_string();

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
        TEST_INT_GE(0u, s.capacity());
        TEST_INT_NE(0u, s.max_size());
    }

    {
        string_v_t  s1;
        string_v_t  s2("abc");
        string_v_t  s3("def");

        string_v_t  s4 = stlsoft::string_traits<string_v_t>::construct(s1, 0u, s1.size());
        string_v_t  s5 = stlsoft::string_traits<string_v_t>::construct(s2, 0u, s2.size());
        string_v_t  s6 = stlsoft::string_traits<string_v_t>::construct(s3, 0u, s3.size());

        TEST_MS_EQ_N(s1, s4, s4.size());
        TEST_MS_EQ_N(s2, s5, s5.size());
        TEST_MS_EQ_N(s3, s6, s6.size());
    }

    {
        string_v_t  s1;
        string_v_t  s2("abc");

        stlsoft::string_traits<string_v_t>::assign_inplace(s1, s2.begin(), s2.end());

        TEST_MS_EQ_N(s1, s2, s2.size());
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
