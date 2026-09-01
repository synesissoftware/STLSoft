/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.unixstl.filesystem.path/entry.cpp
 *
 * Purpose: Unit-tests for `unixstl::basic_path`.
 *
 * Created: 16th February 2024
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <unixstl/filesystem/path.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/conversion/sas_to_string.hpp>
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
// #include <numeric>
// #include <vector>
#include <iomanip>
#include <sstream>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_construct_default();
    static void test_construct_filename();
    static void test_construct_relative_directory_and_file();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.path", verbosity))
    {
        XTESTS_RUN_CASE(test_construct_default);
        XTESTS_RUN_CASE(test_construct_filename);
        XTESTS_RUN_CASE(test_construct_relative_directory_and_file);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * names
 */

namespace {

    // using xtests::cpp::util::temp_directory;

    typedef unixstl::path_a                                 path_a_t;
    typedef unixstl::path_a                                 path_t;
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void test_construct_default()
{
    char    buffer[1001];

    path_a_t p1;

    TEST_BOOLEAN_TRUE(p1.empty());
    TEST_INT_EQ(0, p1.size());
    TEST_INT_EQ(0, p1.length());
#if 0

    TEST(p1.end() == p1.begin());
    TEST(p1.rend() == p1.rbegin());
#endif
    XTESTS_REQUIRE(TEST(ss_nullptr_k != p1.c_str()));
    TEST('\0' == *p1.c_str());
    TEST_INT_EQ(0, ::strcmp("", p1.c_str()));
    XTESTS_REQUIRE(TEST(ss_nullptr_k != p1.data()));
    TEST('\0' == *p1.data());

    buffer[0] = '~';
    TEST_INT_EQ(0, p1.copy(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer)));
    TEST('\0' == buffer[0]);
    TEST_INT_EQ(0, ::strcmp("", buffer));

    TEST_MS_EQ("", stlsoft::sas_to_string(p1));
    TEST_MS_EQ("", stlsoft::sas_to_string_m(p1));
    TEST_PTR_EQ(ss_nullptr_k, stlsoft::c_str_ptr_null(buffer));
    TEST_PTR_EQ(ss_nullptr_k, stlsoft::c_str_ptr_null_a(buffer));

    TEST_INT_EQ(0, p1.get_location().len);
    TEST_INT_EQ(0, p1.get_file().len);
    TEST_INT_EQ(0, p1.get_ext().len);

    {
        std::stringstream stm;

        stm
            << "["
            << p1
            << "]"
            ;

        TEST_MS_EQ("[]", stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(10)
            << p1
            << "]"
            ;

        TEST_MS_EQ("[**********]", stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(10) << std::left
            << p1
            << "]"
            ;

        TEST_MS_EQ("[**********]", stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(10) << std::right
            << p1
            << "]"
            ;

        TEST_MS_EQ("[**********]", stm.str());
    }



    path_a_t p2;

    TEST_BOOLEAN_TRUE(p1.equal(""));
    TEST("" == p1);
    TEST(p1 == "");

    TEST_BOOLEAN_TRUE(p1.equal(p2));
    TEST(p1 == p2);
    TEST_BOOLEAN_FALSE(p1 != p2);

    path_a_t p3(p1);

    TEST_BOOLEAN_TRUE(p3.empty());
    TEST_INT_EQ(0, p3.size());
    TEST_INT_EQ(0, p3.length());
}

static void test_construct_filename()
{
    char    buffer[1001];

    path_a_t p1("file.ext");

    TEST_BOOLEAN_FALSE(p1.empty());
    TEST(8 == p1.size());
    TEST(8 == p1.length());
#if 0

    TEST(p1.end() == p1.begin());
    TEST(p1.rend() == p1.rbegin());
#endif
    TEST_PTR_NE(ss_nullptr_k, p1.c_str());
    TEST('\0' != *p1.c_str());
    TEST(0 == ::strcmp("file.ext", p1.c_str()));
    TEST_PTR_NE(ss_nullptr_k, p1.data());
    TEST('\0' != *p1.data());

    buffer[0] = '~';
    TEST(8 == p1.copy(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer)));
    TEST('\0' != buffer[0]);
    TEST(0 == ::strcmp("file.ext", buffer));

    TEST_MS_EQ("file.ext", stlsoft::sas_to_string(p1));
    TEST_MS_EQ("file.ext", stlsoft::sas_to_string_m(p1));
    TEST_PTR_NE(ss_nullptr_k, stlsoft::c_str_ptr_null(buffer));
    TEST_PTR_NE(ss_nullptr_k, stlsoft::c_str_ptr_null_a(buffer));

    TEST(0 == p1.get_location().len);
    TEST("file.ext" == p1.get_file());
    TEST(".ext" == p1.get_ext());

    {
        std::stringstream stm;

        stm
            << "["
            << p1
            << "]"
            ;

        TEST_MS_EQ("[file.ext]", stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(10) << std::left
            << p1
            << "]"
            ;

        TEST_MS_EQ("[file.ext**]", stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(10) << std::right
            << p1
            << "]"
            ;

        TEST_MS_EQ("[**file.ext]", stm.str());
    }


    TEST(p1.equal(p1));
    TEST(p1 == p1);
    TEST(p1.equivalent(p1));


    path_a_t p2;

    TEST(p1.equal("file.ext"));
    TEST("file.ext" == p1);
    TEST(p1 == "file.ext");

#ifdef _WIN32

    TEST(      p1.equivalent("FILE.EXT"));
#else

    TEST_BOOLEAN_FALSE(p1.equivalent("FILE.EXT"));
#endif
    TEST_BOOLEAN_FALSE(p1.equivalent("life.ext"));

    TEST_BOOLEAN_FALSE(p1.equal(p2));
    TEST_BOOLEAN_FALSE(p1 == p2);
    TEST(p1 != p2);

    path_a_t p3(p1);

    TEST_BOOLEAN_FALSE(p3.empty());
    TEST(8 == p3.size());
    TEST(8 == p3.length());

    TEST(p1.equal(p3));
    TEST(p3 == p1);
    TEST(p1 == p3);

    TEST(p1.equivalent(p3));
    TEST(p3.equivalent(p1));
}

static void test_construct_relative_directory_and_file()
{
    char    buffer[1001];

    path_a_t p1("dir-1/file.ext");

    TEST_BOOLEAN_FALSE(p1.empty());
    TEST(14 == p1.size());
    TEST(14 == p1.length());
#if 0

    TEST(p1.end() == p1.begin());
    TEST(p1.rend() == p1.rbegin());
#endif
    TEST_PTR_NE(ss_nullptr_k, p1.c_str());
    TEST('\0' != *p1.c_str());
    TEST(0 == ::strcmp("dir-1/file.ext", p1.c_str()));
    TEST_PTR_NE(ss_nullptr_k, p1.data());
    TEST('\0' != *p1.data());

    buffer[0] = '~';
    TEST(14 == p1.copy(&buffer[0], STLSOFT_NUM_ELEMENTS(buffer)));
    TEST('\0' != buffer[0]);
    TEST(0 == ::strcmp("dir-1/file.ext", buffer));

    TEST(14 == stlsoft::c_str_len(p1));
    TEST(14 == stlsoft::c_str_len_a(p1));
    TEST(0 == ::strcmp("dir-1/file.ext", stlsoft::c_str_ptr(buffer)));
    TEST(0 == ::strcmp("dir-1/file.ext", stlsoft::c_str_ptr_a(buffer)));
    TEST_PTR_NE(ss_nullptr_k, stlsoft::c_str_ptr_null(buffer));
    TEST_PTR_NE(ss_nullptr_k, stlsoft::c_str_ptr_null_a(buffer));

    TEST("dir-1/" == p1.get_location());
    TEST("file.ext" == p1.get_file());
    TEST(".ext" == p1.get_ext());

    {
        std::stringstream stm;

        stm
            << "["
            << p1
            << "]"
            ;

        TEST_MS_EQ("[dir-1/file.ext]",  stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(10)
            << p1
            << "]"
            ;

        TEST_MS_EQ("[dir-1/file.ext]", stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(10) << std::left
            << p1
            << "]"
            ;

        TEST_MS_EQ("[dir-1/file.ext]", stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(10) << std::right
            << p1
            << "]"
            ;

        TEST_MS_EQ("[dir-1/file.ext]", stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(20)
            << p1
            << "]"
            ;

        TEST_MS_EQ("[dir-1/file.ext******]", stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(20) << std::left
            << p1
            << "]"
            ;

        TEST_MS_EQ("[dir-1/file.ext******]", stm.str());
    }

    {
        std::stringstream stm;

        stm
            << "["
            << std::setfill('*')
            << std::setw(20) << std::right
            << p1
            << "]"
            ;

        TEST_MS_EQ("[******dir-1/file.ext]", stm.str());
    }


    TEST(p1.equal(p1));
    TEST(p1 == p1);
    TEST(p1.equivalent(p1));


    path_a_t p2;

    TEST(p1.equal("dir-1/file.ext"));
    TEST("dir-1/file.ext" == p1);
    TEST(p1 == "dir-1/file.ext");

#ifdef _WIN32

    TEST(      p1.equivalent("dir-1/FILE.EXT"));
#else

    TEST_BOOLEAN_FALSE(p1.equivalent("dir-1/FILE.EXT"));
#endif
    TEST_BOOLEAN_FALSE(p1.equivalent("dir-1/life.ext"));

    TEST_BOOLEAN_FALSE(p1.equal(p2));
    TEST_BOOLEAN_FALSE(p1 == p2);
    TEST(p1 != p2);

    path_a_t p3(p1);

    TEST_BOOLEAN_FALSE(p3.empty());
    TEST(14 == p3.size());
    TEST(14 == p3.length());

    TEST(p1.equal(p3));
    TEST(p3 == p1);
    TEST(p1 == p3);

    TEST(p1.equivalent(p3));
    TEST(p3.equivalent(p1));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

