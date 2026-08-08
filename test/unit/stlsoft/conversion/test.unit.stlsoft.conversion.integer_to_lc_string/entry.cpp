/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.conversion.integer_to_lc_string/entry.cpp
 *
 * Purpose: Unit-tests for `stlsoft::integer_to_lc_string`.
 *
 * Created: 1st November 2011
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * feature control
 */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/conversion/integer_to_string/integer_to_lc_string.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <limits>

/* Standard C header files */
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */


namespace {

    static void test_987654321();

    static void test_1_0();
    static void test_1_1();
    static void test_1_2();
    static void test_1_3();
    static void test_1_4();
    static void test_1_5();
    static void test_1_6();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.conversion.integer_to_lc_string", verbosity))
    {
        XTESTS_RUN_CASE(test_987654321);

        XTESTS_RUN_CASE(test_1_0);
        XTESTS_RUN_CASE(test_1_1);
        XTESTS_RUN_CASE(test_1_2);
        XTESTS_RUN_CASE(test_1_3);
        XTESTS_RUN_CASE(test_1_4);
        XTESTS_RUN_CASE(test_1_5);
        XTESTS_RUN_CASE(test_1_6);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    struct mapping_t
    {
        int            value;
        char const*    result;
    };


static void test_987654321()
{
    char        sz[101];
    size_t      n;
    char const* s;

    s = stlsoft::integer_to_lc_string("\3\3", ',', &sz[0], STLSOFT_NUM_ELEMENTS(sz), 987654321, &n);

    TEST_INT_EQ(11u, n);
    TEST_MS_EQ("987,654,321", s);

    s = stlsoft::integer_to_lc_string("\3\2", ',', &sz[0], STLSOFT_NUM_ELEMENTS(sz), 987654321, &n);

    TEST_INT_EQ(12u, n);
    TEST_MS_EQ("98,76,54,321", s);

    s = stlsoft::integer_to_lc_string("\10", ',', &sz[0], STLSOFT_NUM_ELEMENTS(sz), 987654321, &n);

    TEST_INT_EQ(10u, n);
    TEST_MS_EQ("9,87654321", s);

    s = stlsoft::integer_to_lc_string("\x8", ',', &sz[0], STLSOFT_NUM_ELEMENTS(sz), 987654321, &n);

    TEST_INT_EQ(10u, n);
    TEST_MS_EQ("9,87654321", s);
}

static void test_1_0()
{
    static mapping_t const  mappings[] =
    {
        {    0              ,   "0"             },
        {    1              ,   "1"             },
        {    10             ,   "10"            },
        {    100            ,   "100"           },
        {    1000           ,   "1000"          },
        {    10000          ,   "10000"         },
        {    100000         ,   "100000"        },
        {    1000000        ,   "1000000"       },
        {    10000000       ,   "10000000"      },
        {    100000000      ,   "100000000"     },
        {    1000000000     ,   "1000000000"    },
    };

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(mappings); ++i)
    {
        char                sz[41];
        char const* const   s = stlsoft::integer_to_decimal_string(&sz[0], STLSOFT_NUM_ELEMENTS(sz), mappings[i].value);

        TEST_MS_EQ(mappings[i].result, s);
    }}
}

static void test_1_1()
{
    static char const       grouping[]        =    "\0";
    static char const       thousands_sep[]    =    ",";
    static mapping_t const  mappings[] =
    {
        {    0              ,   "0"             },
        {    1              ,   "1"             },
        {    10             ,   "10"            },
        {    100            ,   "100"           },
        {    1000           ,   "1000"          },
        {    10000          ,   "10000"         },
        {    100000         ,   "100000"        },
        {    1000000        ,   "1000000"       },
        {    10000000       ,   "10000000"      },
        {    100000000      ,   "100000000"     },
        {    1000000000     ,   "1000000000"    },
    };

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(mappings); ++i)
    {
        char        sz[41];
        char const* const   s = stlsoft::integer_to_lc_string(grouping, *thousands_sep, &sz[0], STLSOFT_NUM_ELEMENTS(sz), mappings[i].value);

        TEST_MS_EQ(mappings[i].result, s);
    }}
}

static void test_1_2()
{
    // Australia, UK, US, ...
    static char const    grouping[]        =    "\3";
    static char const    thousands_sep[]    =    ",";
    static mapping_t const    mappings[] =
    {
        {    0              ,   "0"             },
        {    1              ,   "1"             },
        {    10             ,   "10"            },
        {    100            ,   "100"           },
        {    1000           ,   "1,000"         },
        {    10000          ,   "10,000"        },
        {    100000         ,   "100,000"       },
        {    1000000        ,   "1,000,000"     },
        {    10000000       ,   "10,000,000"    },
        {    100000000      ,   "100,000,000"   },
        {    1000000000     ,   "1,000,000,000" },
    };

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(mappings); ++i)
    {
        char        sz[41];
        char const* const   s = stlsoft::integer_to_lc_string(grouping, *thousands_sep, &sz[0], STLSOFT_NUM_ELEMENTS(sz), mappings[i].value);

        TEST_MS_EQ(mappings[i].result, s);
    }}
}

static void test_1_3()
{
    static char const    grouping[]        =    { char(3), char(CHAR_MAX), char(0) };
    static char const    thousands_sep[]    =    ",";
    static mapping_t const    mappings[] =
    {
        {    0              ,   "0"             },
        {    1              ,   "1"             },
        {    10             ,   "10"            },
        {    100            ,   "100"           },
        {    1000           ,   "1,000"         },
        {    10000          ,   "10,000"        },
        {    100000         ,   "100,000"       },
        {    1000000        ,   "1000,000"      },
        {    10000000       ,   "10000,000"     },
        {    100000000      ,   "100000,000"    },
        {    1000000000     ,   "1000000,000"   },
    };

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(mappings); ++i)
    {
        char        sz[41];
        char const* const   s = stlsoft::integer_to_lc_string(grouping, *thousands_sep, &sz[0], STLSOFT_NUM_ELEMENTS(sz), mappings[i].value);

        TEST_MS_EQ(mappings[i].result, s);
    }}
}

static void test_1_4()
{
    static char const    grouping[]        =    { char(2), char(3), char(0) };
    static char const    thousands_sep[]    =    ",";
    static mapping_t const    mappings[] =
    {
        {    0              ,   "0"             },
        {    1              ,   "1"             },
        {    10             ,   "10"            },
        {    100            ,   "1,00"          },
        {    1000           ,   "10,00"         },
        {    10000          ,   "100,00"        },
        {    100000         ,   "1,000,00"      },
        {    1000000        ,   "10,000,00"     },
        {    10000000       ,   "100,000,00"    },
        {    100000000      ,   "1,000,000,00"  },
        {    1000000000     ,   "10,000,000,00" },
    };

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(mappings); ++i)
    {
        char        sz[41];
        char const* const   s = stlsoft::integer_to_lc_string(grouping, *thousands_sep, &sz[0], STLSOFT_NUM_ELEMENTS(sz), mappings[i].value);

        TEST_MS_EQ(mappings[i].result, s);
    }}
}

static void test_1_5()
{
    static char const    grouping[]        =    { char(2), char(3), char(CHAR_MAX), char(0) };
    static char const    thousands_sep[]    =    ",";
    static mapping_t const    mappings[] =
    {
        {    0              ,   "0"             },
        {    1              ,   "1"             },
        {    10             ,   "10"            },
        {    100            ,   "1,00"          },
        {    1000           ,   "10,00"         },
        {    10000          ,   "100,00"        },
        {    100000         ,   "1,000,00"      },
        {    1000000        ,   "10,000,00"     },
        {    10000000       ,   "100,000,00"    },
        {    100000000      ,   "1000,000,00"   },
        {    1000000000     ,   "10000,000,00"  },
    };

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(mappings); ++i)
    {
        char        sz[41];
        char const* const   s = stlsoft::integer_to_lc_string(grouping, *thousands_sep, &sz[0], STLSOFT_NUM_ELEMENTS(sz), mappings[i].value);

        TEST_MS_EQ(mappings[i].result, s);
    }}
}

static void test_1_6()
{
    // Nepal
    static char const    grouping[]        =    { char(3), char(2), char(0) };
    static char const    thousands_sep[]    =    ",";
    static mapping_t const    mappings[] =
    {
        {    0              ,   "0"                 },
        {    1              ,   "1"                 },
        {    10             ,   "10"                },
        {    100            ,   "100"               },
        {    1000           ,   "1,000"             },
        {    10000          ,   "10,000"            },
        {    100000         ,   "1,00,000"          },
        {    1000000        ,   "10,00,000"         },
        {    10000000       ,   "1,00,00,000"       },
        {    100000000      ,   "10,00,00,000"      },
        {    1000000000     ,   "1,00,00,00,000"    },
    };

    { for (size_t i = 0; i != STLSOFT_NUM_ELEMENTS(mappings); ++i)
    {
        char                sz[41];
        char const* const   s = stlsoft::integer_to_lc_string(grouping, *thousands_sep, &sz[0], STLSOFT_NUM_ELEMENTS(sz), mappings[i].value);

        TEST_MS_EQ(mappings[i].result, s);
    }}
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

