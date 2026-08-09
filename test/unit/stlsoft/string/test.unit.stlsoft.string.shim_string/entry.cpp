/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.string.shim_string/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::basic_shim_string`.
 *
 * Created: 9th November 2008
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/shim_string.hpp>

/* /////////////////////////////////////////////////////////////////////////
 * compiler compatibility
 */

#if defined(__BORLANDC__)
# pragma warn -8019
#endif /* compiler */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xCover header files */
#ifdef STLSOFT_USE_XCOVER
# include <xcover/xcover.h>
#endif /* STLSOFT_USE_XCOVER */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <iomanip>
#include <sstream>
#include <string>

/* Standard C header files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_sizes();
    static void test_construction();
    static void test_method_calls();
    static void test_constructor_c_string();
    static void test_constructor_range_string();
    static void test_constructor_length();
    static void test_write();
    static void test_truncate();
    static void test_swap();
    static void test_1_8();
    static void test_1_9();
    static void test_append_c_string();
    static void test_append_c_string_after_truncate();
    static void test_1_12();
    static void test_null_string();
    static void test_reserve();
    static void test_resize();
    static void test_1_16();
    static void test_1_17();
    static void test_1_18();
    static void test_1_19();
    static void test_insertion_1();
    static void test_insertion_2();
    static void test_insertion_3();
    static void test_insertion_4();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.shim_string", verbosity))
    {
        XTESTS_RUN_CASE(test_sizes);
        XTESTS_RUN_CASE(test_construction);
        XTESTS_RUN_CASE(test_method_calls);
        XTESTS_RUN_CASE(test_constructor_c_string);
        XTESTS_RUN_CASE(test_constructor_range_string);
        XTESTS_RUN_CASE(test_constructor_length);
        XTESTS_RUN_CASE(test_write);
        XTESTS_RUN_CASE(test_truncate);
        XTESTS_RUN_CASE(test_swap);
        XTESTS_RUN_CASE(test_1_8);
        XTESTS_RUN_CASE(test_1_9);
        XTESTS_RUN_CASE(test_append_c_string);
        XTESTS_RUN_CASE(test_append_c_string_after_truncate);
        XTESTS_RUN_CASE(test_1_12);
        XTESTS_RUN_CASE(test_null_string);
        XTESTS_RUN_CASE(test_reserve);
        XTESTS_RUN_CASE(test_resize);
        XTESTS_RUN_CASE(test_1_16);
        XTESTS_RUN_CASE(test_1_17);
        XTESTS_RUN_CASE(test_1_18);
        XTESTS_RUN_CASE(test_1_19);
        XTESTS_RUN_CASE(test_insertion_1);
        XTESTS_RUN_CASE(test_insertion_2);
        XTESTS_RUN_CASE(test_insertion_3);
        XTESTS_RUN_CASE(test_insertion_4);

#ifdef STLSOFT_USE_XCOVER
        XCOVER_REPORT_ALIAS_COVERAGE("shim_string", NULL);
#endif /* STLSOFT_USE_XCOVER */

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

    SimpleStream&
    operator <<(
        SimpleStream&       stm
    ,   std::string const&  s
    )
    {
        stm.write(s.data(), s.size());

        return stm;
    }


    char const alphabet[] = "abcdefghijklmnopqrstuvwxyz";


static void test_sizes()
{
    TEST_INT_LE(sizeof(void*) * 2 + sizeof(stlsoft::auto_buffer<char, 4>), sizeof(stlsoft::basic_shim_string<char, 4>));
    TEST_INT_LE(sizeof(void*) * 2 + sizeof(stlsoft::auto_buffer<char, 16>), sizeof(stlsoft::basic_shim_string<char, 16>));
    TEST_INT_LE(sizeof(void*) * 2 + sizeof(stlsoft::auto_buffer<char, 32>), sizeof(stlsoft::basic_shim_string<char, 32>));
    TEST_INT_LE(sizeof(void*) * 2 + sizeof(stlsoft::auto_buffer<char, 64>), sizeof(stlsoft::basic_shim_string<char, 64>));
    TEST_INT_LE(sizeof(void*) * 2 + sizeof(stlsoft::auto_buffer<char, 256>), sizeof(stlsoft::basic_shim_string<char, 256>));
}

static void test_construction()
{
    stlsoft::basic_shim_string<char> str0;

    TEST_BOOLEAN_TRUE(str0.empty());
    TEST_INT_EQ(0u, str0.size());
    TEST_INT_EQ(0u, static_cast<size_t>(str0));
    TEST_INT_NE(0u, str0.internal_size());
    TEST_PTR_NE(NULL, str0);
    TEST_MS_EQ("", str0);
    TEST_MS_EQ("", str0.data());

    stlsoft::basic_shim_string<char> str1(size_t(0u));

    TEST_BOOLEAN_TRUE(str1.empty());
    TEST_INT_EQ(0u, str1.size());
    TEST_INT_EQ(0u, static_cast<size_t>(str1));
    TEST_INT_NE(0u, str1.internal_size());
    TEST_PTR_NE(NULL, str1);
    TEST_MS_EQ("", str1);
    TEST_MS_EQ("", str1.data());

    stlsoft::basic_shim_string<char> const str2("");

    TEST_BOOLEAN_TRUE(str2.empty());
    TEST_INT_EQ(0u, str2.size());
    TEST_INT_EQ(0u, static_cast<size_t>(str2));
    TEST_INT_NE(0u, str2.internal_size());
    TEST_PTR_NE(NULL, str2);
    TEST_MS_EQ("", str2);
    TEST_MS_EQ("", str2.data());

    stlsoft::basic_shim_string<char> str3("", 0);

    TEST_BOOLEAN_TRUE(str3.empty());
    TEST_INT_EQ(0u, str3.size());
    TEST_INT_EQ(0u, static_cast<size_t>(str3));
    TEST_INT_NE(0u, str3.internal_size());
    TEST_PTR_NE(NULL, str3);
    TEST_MS_EQ("", str3);
    TEST_MS_EQ("", str3.data());

    stlsoft::basic_shim_string<char> str4(NULL, 0);

    TEST_BOOLEAN_TRUE(str4.empty());
    TEST_INT_EQ(0u, str4.size());
    TEST_INT_EQ(0u, static_cast<size_t>(str4));
    TEST_INT_NE(0u, str4.internal_size());
    TEST_PTR_NE(NULL, str4);
    TEST_MS_EQ("", str4);
    TEST_MS_EQ("", str4.data());

    stlsoft::basic_shim_string<char> str5(str1);

    TEST_BOOLEAN_TRUE(str5.empty());
    TEST_INT_EQ(0u, str5.size());
    TEST_INT_EQ(0u, static_cast<size_t>(str5));
    TEST_INT_NE(0u, str5.internal_size());
    TEST_PTR_NE(NULL, str5);
    TEST_MS_EQ("", str5);
    TEST_MS_EQ("", str5.data());
}

static void test_method_calls()
{
    stlsoft::basic_shim_string<char> str1(size_t(0u));

    str1.write("");
    str1.truncate(0);
    str1.size();
    str1.data();

    TEST_PASSED();
}

static void test_constructor_length()
{
    stlsoft::basic_shim_string<char> str(5u);

    TEST_BOOLEAN_FALSE(str.empty());
    TEST_INT_EQ(5u, str.size());
    TEST_INT_EQ(5u, static_cast<size_t>(str));
    TEST_PTR_NE(NULL, str);
    TEST_MS_EQ("", str);
    TEST_MS_EQ("", str.data());
}

static void test_constructor_c_string()
{
    stlsoft::basic_shim_string<char> str("a");

    TEST_BOOLEAN_FALSE(str.empty());
    TEST_INT_EQ(1u, str.size());
    TEST_INT_EQ(1u, static_cast<size_t>(str));
    TEST_PTR_NE(NULL, str);
    TEST_MS_EQ("a", str);
    TEST_MS_EQ("a", str.data());
}

static void test_constructor_range_string()
{
    stlsoft::basic_shim_string<char> str("abcdefghijkl", 3);

    TEST_BOOLEAN_FALSE(str.empty());
    TEST_INT_EQ(3u, str.size());
    TEST_INT_EQ(3u, static_cast<size_t>(str));
    TEST_PTR_NE(NULL, str);
    TEST_MS_EQ("abc", str);
    TEST_MS_EQ("abc", str.data());
}

static void test_write()
{
    stlsoft::basic_shim_string<char> str(3);

    str.write("abc");

    TEST_BOOLEAN_FALSE(str.empty());
    TEST_INT_EQ(3u, str.size());
    TEST_INT_EQ(3u, static_cast<size_t>(str));
    TEST_PTR_NE(NULL, str);
    TEST_MS_EQ("abc", str);
    TEST_MS_EQ("abc", str.data());
}

static void test_truncate()
{
    stlsoft::basic_shim_string<char> str("abcdefghijklmnopqrstuvwx");

    { for (size_t i = 0;; ++i)
    {
        size_t numTriplets = (8 - i);

        TEST_INT_EQ(3u * numTriplets, str.size());
        TEST_MS_EQ(std::string(alphabet, 3u * numTriplets), str);

        if (8 == i)
        {
            break;
        }

        str.truncate(3u * (numTriplets - 1));

        TEST_INT_EQ(3u * (numTriplets - 1), str.size());
        TEST_MS_EQ(std::string(alphabet, 3u * (numTriplets - 1)), str);
    }}
}

static void test_swap()
{
    {
        stlsoft::basic_shim_string<char>  s1("abc");
        stlsoft::basic_shim_string<char>  s2("defghi");

        TEST_INT_EQ(3u, s1.size());
        TEST_MS_EQ("abc", s1);
        TEST_INT_EQ(6u, s2.size());
        TEST_MS_EQ("defghi", s2);

        s1.swap(s2);

        TEST_INT_EQ(6u, s1.size());
        TEST_MS_EQ("defghi", s1);
        TEST_INT_EQ(3u, s2.size());
        TEST_MS_EQ("abc", s2);
    }

    {
        stlsoft::basic_shim_string<char>  s1("abcdefghijklmnopqrstuvwxyz");
        stlsoft::basic_shim_string<char>  s2("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        TEST_INT_EQ(26u, s1.size());
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", s1);
        TEST_INT_EQ(26u, s2.size());
        TEST_MS_EQ("ABCDEFGHIJKLMNOPQRSTUVWXYZ", s2);

        s1.swap(s2);

        TEST_INT_EQ(26u, s1.size());
        TEST_MS_EQ("ABCDEFGHIJKLMNOPQRSTUVWXYZ", s1);
        TEST_INT_EQ(26u, s2.size());
        TEST_MS_EQ("abcdefghijklmnopqrstuvwxyz", s2);
    }
}

static void test_1_8()
{
}

static void test_1_9()
{
}

static void test_append_c_string()
{
    char const* strings[] =
    {
            "abc"
        ,   "def"
        ,   "ghi"
        ,   "jkl"
        ,   "mno"
        ,   "pqr"
        ,   "stu"
        ,   "vwx"
    };

    stlsoft::basic_shim_string<char>    str(size_t(0u));

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(strings); ++i)
    {
        str.append(strings[i]);

        TEST_INT_EQ(3u * (i + 1), str.size());
        TEST_MS_EQ(std::string(alphabet, 3u * (i + 1)), str);
    }}
}

static void test_append_c_string_after_truncate()
{
    char const* strings[] =
    {
            "abc"
        ,   "def"
        ,   "ghi"
        ,   "jkl"
        ,   "mno"
        ,   "pqr"
        ,   "stu"
        ,   "vwx"
    };

    stlsoft::basic_shim_string<char>    str(24u);

    char const* const ptr = str;

    str.truncate(0u);

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(strings); ++i)
    {
        str.append(strings[i]);

        TEST_INT_EQ(3u * (i + 1), str.size());
        TEST_PTR_EQ(ptr, str);
        TEST_MS_EQ(std::string(alphabet, 3u * (i + 1)), str);
    }}
}

static void test_1_12()
{
}

static void test_null_string()
{
    {
        stlsoft::basic_shim_string<char, 64, true>  s(size_t(0u));

        TEST_INT_EQ(0u, s.size());
        TEST_INT_EQ(0u, static_cast<size_t>(s));
        TEST_INT_EQ(0u, s.size());
        TEST_PTR_EQ(NULL, s);
        TEST_INT_EQ(0u, static_cast<size_t>(s));
    }
}

static void test_reserve()
{
    {
        stlsoft::basic_shim_string<char>    s(size_t(0u));

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());

        s.reserve(0u);

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());

        s.reserve(1u);

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());

        s.reserve(0u);

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());

        s.reserve(100u);

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());

        s.reserve(0u);

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
    }

}

static void test_resize()
{
    {
        stlsoft::basic_shim_string<char>    s(size_t(0u));

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());

        s.resize(0u);

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());

        s.resize(1u);

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(1u, s.size());

        s.resize(0u);

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());

        s.resize(100u);

        TEST_BOOLEAN_FALSE(s.empty());
        TEST_INT_EQ(100u, s.size());

        s.resize(0u);

        TEST_BOOLEAN_TRUE(s.empty());
        TEST_INT_EQ(0u, s.size());
    }

}

static void test_1_16()
{
}

static void test_1_17()
{
}

static void test_1_18()
{
}

static void test_1_19()
{
}

static void test_insertion_1()
{
    // char const* (for reference)

    {
        char const* const   s1  =   "";
        char const* const   s2  =   "abc";
        char const* const   s3  =   "def";

        {
            std::stringstream   ss;

            ss
                << s1
                << std::left
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

    // std::string (for reference)

    {
        std::string const   s1;
        std::string const   s2("abc");
        std::string const   s3("def");

        {
            std::stringstream   ss;

            ss
                << s1
                << std::left
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

    // stlsoft::basic_shim_string<>

    {
        stlsoft::basic_shim_string<char> const  s1;
        stlsoft::basic_shim_string<char> const  s2("abc");
        stlsoft::basic_shim_string<char> const  s3("def");

        {
            std::stringstream   ss;

            ss
                << s1
                << std::left
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
}

static void test_insertion_2()
{
    // char const* (for reference)

    {
        char const* const   s2  =   "abc";
        char const* const   s3  =   "def";

        {
            std::stringstream ss;

            ss
                << std::setw(2) << std::left
                << s2
                << std::setw(2) << std::right
                << s3
                ;

            TEST_MS_EQ("abcdef", ss.str());
        }

        {
            std::stringstream ss;

            ss
                << '['
                << std::setw(2) << std::left
                << s2
                << std::setw(2) << std::right
                << s3
                << ']'
                ;

            TEST_MS_EQ("[abcdef]", ss.str());
        }
    }

    // std::string (for reference)

    {
        std::string const   s2("abc");
        std::string const   s3("def");

        {
            std::stringstream ss;

            ss
                << std::setw(2) << std::left
                << s2
                << std::setw(2) << std::right
                << s3
                ;

            TEST_MS_EQ("abcdef", ss.str());
        }

        {
            std::stringstream ss;

            ss
                << '['
                << std::setw(2) << std::left
                << s2
                << std::setw(2) << std::right
                << s3
                << ']'
                ;

            TEST_MS_EQ("[abcdef]", ss.str());
        }
    }

    // stlsoft::basic_shim_string<>

    {
        stlsoft::basic_shim_string<char> const  s2("abc");
        stlsoft::basic_shim_string<char> const  s3("def");

        {
            std::stringstream ss;

            ss
                << std::setw(2) << std::left
                << s2
                << std::setw(2) << std::right
                << s3
                ;

            TEST_MS_EQ("abcdef", ss.str());
        }

        {
            std::stringstream ss;

            ss
                << '['
                << std::setw(2) << std::left
                << s2
                << std::setw(2) << std::right
                << s3
                << ']'
                ;

            TEST_MS_EQ("[abcdef]", ss.str());
        }
    }
}

static void test_insertion_3()
{
    // char const* (for reference)

    {
        char const* const   s1  =   "";
        char const* const   s2  =   "abc";
        char const* const   s3  =   "def";

        std::stringstream ss;

        ss
            << '['
            << std::setfill('_')
            << std::setw(4)
            << s1
            << std::setw(4) << std::left
            << s2
            << std::setw(4) << std::right
            << s3
            << ']'
            ;

        TEST_MS_EQ("[____abc__def]", ss.str());
    }

    // std::string (for reference)

    {
        std::string const   s1;
        std::string const   s2("abc");
        std::string const   s3("def");

        std::stringstream ss;

        ss
            << '['
            << std::setfill('_')
            << std::setw(4)
            << s1
            << std::setw(4) << std::left
            << s2
            << std::setw(4) << std::right
            << s3
            << ']'
            ;

        TEST_MS_EQ("[____abc__def]", ss.str());
    }

    // stlsoft::basic_shim_string<>

    {
        stlsoft::basic_shim_string<char> const  s1;
        stlsoft::basic_shim_string<char> const  s2("abc");
        stlsoft::basic_shim_string<char> const  s3("def");

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

        {
            std::stringstream ss;

            ss
                << '['
                << std::setfill('_')
                << std::setw(4)
                << s1
                << std::setw(4) << std::left
                << s2
                << std::setw(4) << std::right
                << s3
                << std::setw(0)
                << ']'
                ;

            TEST_MS_EQ("[____abc__def]", ss.str());
        }
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

    stlsoft::basic_shim_string<char> const  s1;
    stlsoft::basic_shim_string<char> const  s2("abc");
    stlsoft::basic_shim_string<char> const  s3("defg");

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
            stlsoft::basic_shim_string<char> const& s2
        ,   stlsoft::basic_shim_string<char> const& s3
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
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

