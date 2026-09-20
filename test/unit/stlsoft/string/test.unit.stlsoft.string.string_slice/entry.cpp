/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.string.string_slice/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::basic_string_slice`.
 *
 * Created: 19th February 2010
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/string/string_slice.hpp>

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
#include <sstream>
#include <string>

/* Standard C header files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_type_exists();
    static void test_constructor_callable();
    static void test_constructed_state();
    static void test_constructed_subslice_1();
    static void test_constructed_from_c_string_1();
    static void test_copy_construction_1();
    static void test_assignment_1();
    static void test_string_access_shims_1();
    static void test_string_access_shims_multibyte_1();
    static void test_string_access_shims_2();
    static void test_string_access_shims_multibyte_2();
    static void test_string_access_shims_multibyte_3();
    static void test_equality_operator_1();
    static void test_less_than_operator_1();
    static void test_greater_than_operator_1();
    static void test_lessgreaterequal_operators_1();
    static void test_lessgreaterequal_operators_2();
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

    if (XTESTS_START_RUNNER("test.unit.stlsoft.string.string_slice", verbosity))
    {
        XTESTS_RUN_CASE(test_type_exists);
        XTESTS_RUN_CASE(test_constructor_callable);
        XTESTS_RUN_CASE(test_constructed_state);
        XTESTS_RUN_CASE(test_constructed_subslice_1);
        XTESTS_RUN_CASE(test_constructed_from_c_string_1);
        XTESTS_RUN_CASE(test_copy_construction_1);
        XTESTS_RUN_CASE(test_assignment_1);
        XTESTS_RUN_CASE(test_string_access_shims_1);
        XTESTS_RUN_CASE(test_string_access_shims_multibyte_1);
        XTESTS_RUN_CASE(test_string_access_shims_2);
        XTESTS_RUN_CASE(test_string_access_shims_multibyte_2);
        XTESTS_RUN_CASE(test_string_access_shims_multibyte_3);
        XTESTS_RUN_CASE(test_equality_operator_1);
        XTESTS_RUN_CASE(test_less_than_operator_1);
        XTESTS_RUN_CASE(test_greater_than_operator_1);
        XTESTS_RUN_CASE(test_lessgreaterequal_operators_1);
        XTESTS_RUN_CASE(test_lessgreaterequal_operators_2);
        XTESTS_RUN_CASE(test_insertion_1);
        XTESTS_RUN_CASE(test_insertion_2);
        XTESTS_RUN_CASE(test_insertion_3);
        XTESTS_RUN_CASE(test_insertion_4);

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


    static char const       alphabet[]      =    "abcdefghijklmnopqrstuvwxyz";
    static wchar_t const    alphabet_w[]    =   L"abcdefghijklmnopqrstuvwxyz";


static void test_type_exists()
{
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::string_slice<char>));
    STLSOFT_SUPPRESS_UNUSED(typeid(stlsoft::string_slice<wchar_t>));

    TEST_PASSED();
}

static void test_constructor_callable()
{
    stlsoft::string_slice<char>     slice;
    stlsoft::string_slice<wchar_t>  slice_w;

    STLSOFT_SUPPRESS_UNUSED(slice);
    STLSOFT_SUPPRESS_UNUSED(slice_w);

    TEST_PASSED();
}

static void test_constructed_state()
{
    stlsoft::string_slice<char>     slice;
    stlsoft::string_slice<wchar_t>  slice_w;

    TEST_INT_EQ(0u, slice.len);
    TEST_PTR_EQ(NULL, slice.ptr);
    TEST_INT_EQ(0u, slice_w.len);
    TEST_PTR_EQ(NULL, slice_w.ptr);

    TEST_INT_EQ(0u, ::stlsoft::c_str_len_a(slice));
    TEST_PTR_NE(NULL, ::stlsoft::c_str_data_a(slice));
    TEST_INT_EQ(0u, ::stlsoft::c_str_len_w(slice_w));
    TEST_PTR_NE(NULL, ::stlsoft::c_str_data_w(slice_w));

    TEST_INT_EQ(0u, ::stlsoft::c_str_len(slice));
    TEST_PTR_NE(NULL, ::stlsoft::c_str_data(slice));
    TEST_INT_EQ(0u, ::stlsoft::c_str_len(slice_w));
    TEST_PTR_NE(NULL, ::stlsoft::c_str_data(slice_w));

    TEST_INT_EQ(0u, ::stlsoft::c_str_len_a(&slice));
    TEST_PTR_NE(NULL, ::stlsoft::c_str_data_a(&slice));
    TEST_INT_EQ(0u, ::stlsoft::c_str_len_w(&slice_w));
    TEST_PTR_NE(NULL, ::stlsoft::c_str_data_w(&slice_w));

    TEST_INT_EQ(0u, ::stlsoft::c_str_len(&slice));
    TEST_PTR_NE(NULL, ::stlsoft::c_str_data(&slice));
    TEST_INT_EQ(0u, ::stlsoft::c_str_len(&slice_w));
    TEST_PTR_NE(NULL, ::stlsoft::c_str_data(&slice_w));
}

static void test_constructed_subslice_1()
{
    stlsoft::string_slice<char>     slice(alphabet, 3u);
    stlsoft::string_slice<wchar_t>  slice_w(alphabet_w, 3u);

    TEST_INT_EQ(3u, slice.len);
    TEST_PTR_EQ(alphabet, slice.ptr);
    TEST_INT_EQ(3u, slice_w.len);
    TEST_PTR_EQ(alphabet_w, slice_w.ptr);
}

static void test_constructed_from_c_string_1()
{
    stlsoft::string_slice<char>     slice(alphabet);
    stlsoft::string_slice<wchar_t>  slice_w(alphabet_w);

    TEST_INT_EQ(26u, slice.len);
    TEST_PTR_EQ(alphabet, slice.ptr);
    TEST_INT_EQ(26u, slice_w.len);
    TEST_PTR_EQ(alphabet_w, slice_w.ptr);
}

static void test_copy_construction_1()
{
    stlsoft::string_slice<char>     slice(alphabet, 3u);
    stlsoft::string_slice<char>     slice2(slice);
    stlsoft::string_slice<wchar_t>  slice_w(alphabet_w, 3u);
    stlsoft::string_slice<wchar_t>  slice2_w(slice_w);

    TEST_INT_EQ(3u, slice2.len);
    TEST_PTR_EQ(alphabet, slice2.ptr);
    TEST_INT_EQ(3u, slice2_w.len);
    TEST_PTR_EQ(alphabet_w, slice2_w.ptr);
}

static void test_assignment_1()
{
    stlsoft::string_slice<char>     slice(alphabet, 3u);
    stlsoft::string_slice<char>     slice2;
    stlsoft::string_slice<wchar_t>  slice_w(alphabet_w, 3u);
    stlsoft::string_slice<wchar_t>  slice2_w;

    slice2      =   slice;
    slice2_w    =   slice_w;

    TEST_INT_EQ(3u, slice2.len);
    TEST_PTR_EQ(alphabet, slice2.ptr);
    TEST_INT_EQ(3u, slice2_w.len);
    TEST_PTR_EQ(alphabet_w, slice2_w.ptr);
}

static void test_string_access_shims_1()
{
    stlsoft::string_slice<char>     slice(alphabet, 3u);
    stlsoft::string_slice<wchar_t>  slice_w(alphabet_w, 3u);

    size_t          len     =   stlsoft::c_str_len(slice);
    char const*     ptr     =   stlsoft::c_str_data(slice);
    size_t          len_w   =   stlsoft::c_str_len(slice_w);
    wchar_t const*  ptr_w   =   stlsoft::c_str_data(slice_w);

    TEST_INT_EQ(3u, len);
    TEST_PTR_EQ(alphabet, ptr);
    TEST_INT_EQ(3u, len_w);
    TEST_PTR_EQ(alphabet_w, ptr_w);
}

static void test_string_access_shims_multibyte_1()
{
    stlsoft::string_slice<char>     slice(alphabet, 3u);
    stlsoft::string_slice<wchar_t>  slice_w(alphabet_w, 3u);

    size_t          len     =   stlsoft::c_str_len_a(slice);
    char const*     ptr     =   stlsoft::c_str_data_a(slice);
    size_t          len_w   =   stlsoft::c_str_len_w(slice_w);
    wchar_t const*  ptr_w   =   stlsoft::c_str_data_w(slice_w);

    TEST_INT_EQ(3u, len);
    TEST_PTR_EQ(alphabet, ptr);
    TEST_INT_EQ(3u, len_w);
    TEST_PTR_EQ(alphabet_w, ptr_w);
}

static void test_string_access_shims_2()
{
    stlsoft::string_slice<char>     slice(alphabet, 3u);
    stlsoft::string_slice<wchar_t>  slice_w(alphabet_w, 3u);

    size_t          len     =   stlsoft::c_str_len(&slice);
    char const*     ptr     =   stlsoft::c_str_data(&slice);
    size_t          len_w   =   stlsoft::c_str_len(&slice_w);
    wchar_t const*  ptr_w   =   stlsoft::c_str_data(&slice_w);

    TEST_INT_EQ(3u, len);
    TEST_PTR_EQ(alphabet, ptr);
    TEST_INT_EQ(3u, len_w);
    TEST_PTR_EQ(alphabet_w, ptr_w);
}

static void test_string_access_shims_multibyte_2()
{
    stlsoft::string_slice<char>     slice(alphabet, 3u);
    stlsoft::string_slice<wchar_t>  slice_w(alphabet_w, 3u);

    size_t          len     =   stlsoft::c_str_len_a(&slice);
    char const*     ptr     =   stlsoft::c_str_data_a(&slice);
    size_t          len_w   =   stlsoft::c_str_len_w(&slice_w);
    wchar_t const*  ptr_w   =   stlsoft::c_str_data_w(&slice_w);

    TEST_INT_EQ(3u, len);
    TEST_PTR_EQ(alphabet, ptr);
    TEST_INT_EQ(3u, len_w);
    TEST_PTR_EQ(alphabet_w, ptr_w);
}

static void test_string_access_shims_multibyte_3()
{
    stlsoft::string_slice<char> const*      slice   =   NULL;
    stlsoft::string_slice<wchar_t> const*   slice_w =   NULL;

    size_t          len     =   stlsoft::c_str_len_a(slice);
    char const*     ptr     =   stlsoft::c_str_data_a(slice);
    size_t          len_w   =   stlsoft::c_str_len_w(slice_w);
    wchar_t const*  ptr_w   =   stlsoft::c_str_data_w(slice_w);

    TEST_INT_EQ(0u, len);
    TEST_PTR_NE(NULL, ptr);
    TEST_INT_EQ(0u, len_w);
    TEST_PTR_NE(NULL, ptr_w);
}

static void test_equality_operator_1()
{
    stlsoft::string_slice<char>     slice1(alphabet, 3u);
    stlsoft::string_slice<char>     slice2(alphabet, 3u);
    stlsoft::string_slice<wchar_t>  slice1_w(alphabet_w, 3u);
    stlsoft::string_slice<wchar_t>  slice2_w(alphabet_w, 3u);

    TEST_BOOLEAN_TRUE(slice1 == slice1);
    TEST_BOOLEAN_TRUE(slice1 == slice2);
    TEST_BOOLEAN_FALSE(slice1 != slice2);
    TEST_BOOLEAN_TRUE(slice1_w == slice1_w);
    TEST_BOOLEAN_TRUE(slice1_w == slice2_w);
    TEST_BOOLEAN_FALSE(slice1_w != slice2_w);
}

static void test_less_than_operator_1()
{
    stlsoft::string_slice<char>     slice1(alphabet, 3u);
    stlsoft::string_slice<char>     slice2(alphabet + 1, 3u);
    stlsoft::string_slice<wchar_t>  slice1_w(alphabet_w, 3u);
    stlsoft::string_slice<wchar_t>  slice2_w(alphabet_w + 1, 3u);

    TEST_BOOLEAN_TRUE(slice1 < slice2);
    TEST_BOOLEAN_FALSE(slice1 > slice2);
    TEST_BOOLEAN_TRUE(slice1_w < slice2_w);
    TEST_BOOLEAN_FALSE(slice1_w > slice2_w);
}

static void test_greater_than_operator_1()
{
    stlsoft::string_slice<char>     slice1(alphabet, 3u);
    stlsoft::string_slice<char>     slice2(alphabet, 4u);
    stlsoft::string_slice<wchar_t>  slice1_w(alphabet_w, 3u);
    stlsoft::string_slice<wchar_t>  slice2_w(alphabet_w, 4u);

    TEST_BOOLEAN_TRUE(slice1 < slice2);
    TEST_BOOLEAN_FALSE(slice1 > slice2);
    TEST_BOOLEAN_TRUE(slice1_w < slice2_w);
    TEST_BOOLEAN_FALSE(slice1_w > slice2_w);
}

static void test_lessgreaterequal_operators_1()
{
    stlsoft::string_slice<char>     slice1(alphabet, 3u);
    stlsoft::string_slice<char>     slice2(alphabet, 3u);
    stlsoft::string_slice<wchar_t>  slice1_w(alphabet_w, 3u);
    stlsoft::string_slice<wchar_t>  slice2_w(alphabet_w, 3u);

    TEST_BOOLEAN_TRUE(slice1 <= slice1);
    TEST_BOOLEAN_TRUE(slice1 >= slice1);
    TEST_BOOLEAN_TRUE(slice1 <= slice2);
    TEST_BOOLEAN_TRUE(slice1 >= slice2);
    TEST_BOOLEAN_TRUE(slice1_w <= slice1_w);
    TEST_BOOLEAN_TRUE(slice1_w >= slice1_w);
    TEST_BOOLEAN_TRUE(slice1_w <= slice2_w);
    TEST_BOOLEAN_TRUE(slice1_w >= slice2_w);
}

static void test_lessgreaterequal_operators_2()
{
    stlsoft::string_slice<char>     slice1(alphabet, 3u);
    stlsoft::string_slice<char>     slice2(alphabet + 1, 3u);
    stlsoft::string_slice<wchar_t>  slice1_w(alphabet_w, 3u);
    stlsoft::string_slice<wchar_t>  slice2_w(alphabet_w + 1, 3u);

    TEST_BOOLEAN_TRUE(slice1 <= slice2);
    TEST_BOOLEAN_TRUE(slice1_w <= slice2_w);
}

static void test_insertion_1()
{
    stlsoft::string_slice<char> const   s1;
    stlsoft::string_slice<char> const   s2("abc");
    stlsoft::string_slice<char> const   s3("def");

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
    stlsoft::string_slice<char> const   s2("abc");
    stlsoft::string_slice<char> const   s3("def");

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
    stlsoft::string_slice<char> const   s1;
    stlsoft::string_slice<char> const   s2("abc");
    stlsoft::string_slice<char> const   s3("def");

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

    stlsoft::string_slice<char> const   s1;
    stlsoft::string_slice<char> const   s2("abc");
    stlsoft::string_slice<char> const   s3("defg");

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
            stlsoft::string_slice<char> const&  s2
        ,   stlsoft::string_slice<char> const&  s3
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

