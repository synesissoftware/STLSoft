/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.util.string_switch/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::count_hexadecimal_digits`.
 *
 * Created: 9th June 2010
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/util/string_switch.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/util/dimensionof.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void test_1_1();
    static void test_1_2();
    static void test_1_3();
    static void test_1_4();
    static void test_1_5();
    static void test_1_6();
    static void test_1_7();
    static void test_1_8();
    static void test_1_9();
    static void test_1_10();

    static void test_1_11();

    static void test_2_1();
    static void test_2_2();

    static void test_3_1();
    static void test_3_2();
    static void test_3_3();
    static void test_3_4();
    static void test_3_5();
    static void test_3_6();
    static void test_3_7();
    static void test_3_8();
    static void test_3_9();
    static void test_3_10();
    static void test_3_11();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.util.string_switch", verbosity))
    {
        XTESTS_RUN_CASE(test_1_1);
        XTESTS_RUN_CASE(test_1_2);
        XTESTS_RUN_CASE(test_1_3);
        XTESTS_RUN_CASE(test_1_4);
        XTESTS_RUN_CASE(test_1_5);
        XTESTS_RUN_CASE(test_1_6);
        XTESTS_RUN_CASE(test_1_7);
        XTESTS_RUN_CASE(test_1_8);
        XTESTS_RUN_CASE(test_1_9);
        XTESTS_RUN_CASE(test_1_10);

        XTESTS_RUN_CASE(test_1_11);

        XTESTS_RUN_CASE(test_2_1);
        XTESTS_RUN_CASE(test_2_2);

        XTESTS_RUN_CASE(test_3_1);
        XTESTS_RUN_CASE(test_3_2);
        XTESTS_RUN_CASE(test_3_3);
        XTESTS_RUN_CASE(test_3_4);
        XTESTS_RUN_CASE(test_3_5);
        XTESTS_RUN_CASE(test_3_6);
        XTESTS_RUN_CASE(test_3_7);
        XTESTS_RUN_CASE(test_3_8);
        XTESTS_RUN_CASE(test_3_9);
        XTESTS_RUN_CASE(test_3_10);
        XTESTS_RUN_CASE(test_3_11);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace stlsoft {

    template<
        typename Name
    ,   typename Value
    >
    struct enum_map
    {
        Name    name;
        Value   value;
    };

#if 0
    template<
        ss_typename_param_k C
    ,   ss_typename_param_k E
    ,   ss_typename_param_k Name
    ,   ss_typename_param_k Value
    >
    inline
    bool
    string_switch2(
        C const*                      s
    ,   E*                            result
    ,   enum_map<Name, Value> const*  cases
    ,   size_t                        numCases
    )
#else /* ? 0 */
    template<
        ss_typename_param_k C
    ,   ss_typename_param_k E
    ,   ss_typename_param_k A
    >
    inline
    bool
    string_switch2(
        C const*                      s
    ,   E*                            result
    ,   A const*                      cases
    ,   size_t                        numCases
    )
#endif /* 0 */
    {
        typedef stlsoft_char_traits<C> char_traits_t;

        size_t const len = char_traits_t::length(s);

      { for (ss_size_t i = 0; i != numCases; ++i)
      {
#if 0
          enum_map<Name, Value> const&  case_   =   cases[i];
#else /* ? 0 */
          A const&                      case_   =   cases[i];
#endif /* 0 */
            size_t const                caselen =   char_traits_t::length(case_.name);

            if (caselen == len &&
                0 == char_traits_t::compare(case_.name, s, len))
            {
                *result = case_.value;
                return true;
            }
        }}

        return false;
    }
} // namespace stlsoft


namespace {

/* /////////////////////////////////////////////////////////////////////////
 * 1_x
 */

static void test_1_1()
{
    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_FALSE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  10
                )
            )
        )
    );

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "B",  11
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_1_2()
{
    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  10
                ,   "B",  11
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_1_3()
{
    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  10
                ,   "B",  11
                ,   "C",  12
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_1_4()
{
    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  10
                ,   "B",  11
                ,   "C",  12
                ,   "D",  13
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_1_5()
{
    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  10
                ,   "B",  11
                ,   "C",  12
                ,   "D",  13
                ,   "E",  14
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_1_6()
{
    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  10
                ,   "B",  11
                ,   "C",  12
                ,   "D",  13
                ,   "E",  14
                ,   "F",  15
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_1_7()
{
    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  10
                ,   "B",  11
                ,   "C",  12
                ,   "D",  13
                ,   "E",  14
                ,   "F",  15
                ,   "G",  16
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_1_8()
{
    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  10
                ,   "B",  11
                ,   "C",  12
                ,   "D",  13
                ,   "E",  14
                ,   "F",  15
                ,   "G",  16
                ,   "H",  17
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_1_9()
{
    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  10
                ,   "B",  11
                ,   "C",  12
                ,   "D",  13
                ,   "E",  14
                ,   "F",  15
                ,   "G",  16
                ,   "H",  17
                ,   "I",  18
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_1_10()
{
    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  10
                ,   "B",  11
                ,   "C",  12
                ,   "D",  13
                ,   "E",  14
                ,   "F",  15
                ,   "G",  16
                ,   "H",  17
                ,   "I",  18
                ,   "J",  19
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_1_11()
{
    static const stlsoft::enum_map<const char*, int> cases[] =
    {
            {"A",  10}
        ,   {"B",  11}
        ,   {"C",  12}
        ,   {"D",  13}
        ,   {"E",  14}
        ,   {"F",  15}
        ,   {"G",  16}
        ,   {"H",  17}
        ,   {"I",  18}
        ,   {"J",  19}
    };

    char const  VAR[] = "B";
    int         var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch2(
                VAR
            ,   &var
            ,   cases
            ,   dimensionof(cases)
            )
        )
    );

    TEST_INT_EQ(11, var);
}


/* /////////////////////////////////////////////////////////////////////////
 * 2_x
 */

static void test_2_1()
{
    char const  VAR[] = "B";
    int         var       =   0x00;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_FALSE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "A",  0x01
                )
            ,   var
            )
        )
    );

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    "B",  0x02
                )
            ,   var
            )
        )
    );

    TEST_INT_EQ(0x02, var);
}

static void test_2_2()
{
    char const  VAR[] = "B";
    int         var       =   0x10;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                "A",  0x01
            ,   "B",  0x02
            )
            ,   var
            )
        )
    );

    TEST_INT_EQ(0x12, var);
}


/* /////////////////////////////////////////////////////////////////////////
 * 3_x
 */

static void test_3_1()
{
    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_FALSE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"A",  10
                )
            )
        )
    );

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"B",  11
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_3_2()
{
    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"A",  10
                ,   L"B",  11
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_3_3()
{
    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"A",  10
                ,   L"B",  11
                ,   L"C",  12
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_3_4()
{
    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"A",  10
                ,   L"B",  11
                ,   L"C",  12
                ,   L"D",  13
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_3_5()
{
    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"A",  10
                ,   L"B",  11
                ,   L"C",  12
                ,   L"D",  13
                ,   L"E",  14
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_3_6()
{
    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"A",  10
                ,   L"B",  11
                ,   L"C",  12
                ,   L"D",  13
                ,   L"E",  14
                ,   L"F",  15
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_3_7()
{
    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"A",  10
                ,   L"B",  11
                ,   L"C",  12
                ,   L"D",  13
                ,   L"E",  14
                ,   L"F",  15
                ,   L"G",  16
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_3_8()
{
    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"A",  10
                ,   L"B",  11
                ,   L"C",  12
                ,   L"D",  13
                ,   L"E",  14
                ,   L"F",  15
                ,   L"G",  16
                ,   L"H",  17
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_3_9()
{
    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"A",  10
                ,   L"B",  11
                ,   L"C",  12
                ,   L"D",  13
                ,   L"E",  14
                ,   L"F",  15
                ,   L"G",  16
                ,   L"H",  17
                ,   L"I",  18
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_3_10()
{
    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch(
                VAR
            ,   &var
            ,   stlsoft::string_cases(
                    L"A",  10
                ,   L"B",  11
                ,   L"C",  12
                ,   L"D",  13
                ,   L"E",  14
                ,   L"F",  15
                ,   L"G",  16
                ,   L"H",  17
                ,   L"I",  18
                ,   L"J",  19
                )
            )
        )
    );

    TEST_INT_EQ(11, var);
}

static void test_3_11()
{
    static const stlsoft::enum_map<const wchar_t*, int> cases[] =
    {
        {L"A",  10}
    ,   {L"B",  11}
    ,   {L"C",  12}
    ,   {L"D",  13}
    ,   {L"E",  14}
    ,   {L"F",  15}
    ,   {L"G",  16}
    ,   {L"H",  17}
    ,   {L"I",  18}
    ,   {L"J",  19}
    };

    wchar_t const   VAR[] = L"B";
    int             var = -1;

    XTESTS_REQUIRE(
        TEST_BOOLEAN_TRUE(
            stlsoft::string_switch2(
                VAR
            ,   &var
            ,   cases
            ,   dimensionof(cases)
            )
        )
    );

    TEST_INT_EQ(11, var);
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
