/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.stlsoft.filesystem.io_functions.read_line/entry.cpp
 *
 * Purpose: Unit-test
 *
 * Created: 11th August 2008
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/filesystem/io_functions/read_line.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <string>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    // LF-only
    static void test_1_0();
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
    static void test_1_12();
    static void test_1_13();
    static void test_1_14();
    static void test_1_15();
    static void test_1_16();
    static void test_1_17();
    static void test_1_18();
    static void test_1_19();

    // CR-only
    static void test_2_0();
    static void test_2_1();
    static void test_2_2();
    static void test_2_3();
    static void test_2_4();
    static void test_2_5();
    static void test_2_6();
    static void test_2_7();
    static void test_2_8();
    static void test_2_9();
    static void test_2_10();
    static void test_2_11();
    static void test_2_12();
    static void test_2_13();
    static void test_2_14();
    static void test_2_15();
    static void test_2_16();
    static void test_2_17();
    static void test_2_18();
    static void test_2_19();

    // CRLF-only
    static void test_3_0();
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
    static void test_3_12();
    static void test_3_13();
    static void test_3_14();
    static void test_3_15();
    static void test_3_16();
    static void test_3_17();
    static void test_3_18();
    static void test_3_19();

    // LF or CR (but not CRLF)
    static void test_4_0();
    static void test_4_1();
    static void test_4_2();
    static void test_4_3();
    static void test_4_4();
    static void test_4_5();
    static void test_4_6();
    static void test_4_7();
    static void test_4_8();
    static void test_4_9();
    static void test_4_10();
    static void test_4_11();
    static void test_4_12();
    static void test_4_13();
    static void test_4_14();
    static void test_4_15();
    static void test_4_16();
    static void test_4_17();
    static void test_4_18();
    static void test_4_19();

    // LF or CRLF
    static void test_5_0();
    static void test_5_1();
    static void test_5_2();
    static void test_5_3();
    static void test_5_4();
    static void test_5_5();
    static void test_5_6();
    static void test_5_7();
    static void test_5_8();
    static void test_5_9();
    static void test_5_10();
    static void test_5_11();
    static void test_5_12();
    static void test_5_13();
    static void test_5_14();
    static void test_5_15();
    static void test_5_16();
    static void test_5_17();
    static void test_5_18();
    static void test_5_19();

    // CR or CRLF
    static void test_6_0();
    static void test_6_1();
    static void test_6_2();
    static void test_6_3();
    static void test_6_4();
    static void test_6_5();
    static void test_6_6();
    static void test_6_7();
    static void test_6_8();
    static void test_6_9();
    static void test_6_10();
    static void test_6_11();
    static void test_6_12();
    static void test_6_13();
    static void test_6_14();
    static void test_6_15();
    static void test_6_16();
    static void test_6_17();
    static void test_6_18();
    static void test_6_19();

    // 0 === (LF or CR or CRLF)
    static void test_7_0();
    static void test_7_1();
    static void test_7_2();
    static void test_7_3();
    static void test_7_4();
    static void test_7_5();
    static void test_7_6();
    static void test_7_7();
    static void test_7_8();
    static void test_7_9();
    static void test_7_10();
    static void test_7_11();
    static void test_7_12();
    static void test_7_13();
    static void test_7_14();
    static void test_7_15();
    static void test_7_16();
    static void test_7_17();
    static void test_7_18();
    static void test_7_19();


    // LF-only
    static void test_8_0();
    static void test_8_1();
    static void test_8_2();
    static void test_8_3();
    static void test_8_4();
    static void test_8_5();
    static void test_8_6();
    static void test_8_7();
    static void test_8_8();
    static void test_8_9();
    static void test_8_10();
    static void test_8_11();
    static void test_8_12();
    static void test_8_13();
    static void test_8_14();
    static void test_8_15();
    static void test_8_16();
    static void test_8_17();
    static void test_8_18();
    static void test_8_19();

    // CR-only
    static void test_9_0();
    static void test_9_1();
    static void test_9_2();
    static void test_9_3();
    static void test_9_4();
    static void test_9_5();
    static void test_9_6();
    static void test_9_7();
    static void test_9_8();
    static void test_9_9();
    static void test_9_10();
    static void test_9_11();
    static void test_9_12();
    static void test_9_13();
    static void test_9_14();
    static void test_9_15();
    static void test_9_16();
    static void test_9_17();
    static void test_9_18();
    static void test_9_19();

    // CRLF-only
    static void test_10_0();
    static void test_10_1();
    static void test_10_2();
    static void test_10_3();
    static void test_10_4();
    static void test_10_5();
    static void test_10_6();
    static void test_10_7();
    static void test_10_8();
    static void test_10_9();
    static void test_10_10();
    static void test_10_11();
    static void test_10_12();
    static void test_10_13();
    static void test_10_14();
    static void test_10_15();
    static void test_10_16();
    static void test_10_17();
    static void test_10_18();
    static void test_10_19();

    // LF or CR (but not CRLF)
    static void test_11_0();
    static void test_11_1();
    static void test_11_2();
    static void test_11_3();
    static void test_11_4();
    static void test_11_5();
    static void test_11_6();
    static void test_11_7();
    static void test_11_8();
    static void test_11_9();
    static void test_11_10();
    static void test_11_11();
    static void test_11_12();
    static void test_11_13();
    static void test_11_14();
    static void test_11_15();
    static void test_11_16();
    static void test_11_17();
    static void test_11_18();
    static void test_11_19();

    // LF or CRLF
    static void test_12_0();
    static void test_12_1();
    static void test_12_2();
    static void test_12_3();
    static void test_12_4();
    static void test_12_5();
    static void test_12_6();
    static void test_12_7();
    static void test_12_8();
    static void test_12_9();
    static void test_12_10();
    static void test_12_11();
    static void test_12_12();
    static void test_12_13();
    static void test_12_14();
    static void test_12_15();
    static void test_12_16();
    static void test_12_17();
    static void test_12_18();
    static void test_12_19();

    // CR or CRLF
    static void test_13_0();
    static void test_13_1();
    static void test_13_2();
    static void test_13_3();
    static void test_13_4();
    static void test_13_5();
    static void test_13_6();
    static void test_13_7();
    static void test_13_8();
    static void test_13_9();
    static void test_13_10();
    static void test_13_11();
    static void test_13_12();
    static void test_13_13();
    static void test_13_14();
    static void test_13_15();
    static void test_13_16();
    static void test_13_17();
    static void test_13_18();
    static void test_13_19();

    // 0 === (LF or CR or CRLF)
    static void test_14_0();
    static void test_14_1();
    static void test_14_2();
    static void test_14_3();
    static void test_14_4();
    static void test_14_5();
    static void test_14_6();
    static void test_14_7();
    static void test_14_8();
    static void test_14_9();
    static void test_14_10();
    static void test_14_11();
    static void test_14_12();
    static void test_14_13();
    static void test_14_14();
    static void test_14_15();
    static void test_14_16();
    static void test_14_17();
    static void test_14_18();
    static void test_14_19();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.stlsoft.filesystem.io_functions.read_line", verbosity))
    {
        XTESTS_RUN_CASE(test_1_0);
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
        XTESTS_RUN_CASE(test_1_12);
        XTESTS_RUN_CASE(test_1_13);
        XTESTS_RUN_CASE(test_1_14);
        XTESTS_RUN_CASE(test_1_15);
        XTESTS_RUN_CASE(test_1_16);
        XTESTS_RUN_CASE(test_1_17);
        XTESTS_RUN_CASE(test_1_18);
        XTESTS_RUN_CASE(test_1_19);

        XTESTS_RUN_CASE(test_2_0);
        XTESTS_RUN_CASE(test_2_1);
        XTESTS_RUN_CASE(test_2_2);
        XTESTS_RUN_CASE(test_2_3);
        XTESTS_RUN_CASE(test_2_4);
        XTESTS_RUN_CASE(test_2_5);
        XTESTS_RUN_CASE(test_2_6);
        XTESTS_RUN_CASE(test_2_7);
        XTESTS_RUN_CASE(test_2_8);
        XTESTS_RUN_CASE(test_2_9);
        XTESTS_RUN_CASE(test_2_10);
        XTESTS_RUN_CASE(test_2_11);
        XTESTS_RUN_CASE(test_2_12);
        XTESTS_RUN_CASE(test_2_13);
        XTESTS_RUN_CASE(test_2_14);
        XTESTS_RUN_CASE(test_2_15);
        XTESTS_RUN_CASE(test_2_16);
        XTESTS_RUN_CASE(test_2_17);
        XTESTS_RUN_CASE(test_2_18);
        XTESTS_RUN_CASE(test_2_19);

        XTESTS_RUN_CASE(test_3_0);
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
        XTESTS_RUN_CASE(test_3_12);
        XTESTS_RUN_CASE(test_3_13);
        XTESTS_RUN_CASE(test_3_14);
        XTESTS_RUN_CASE(test_3_15);
        XTESTS_RUN_CASE(test_3_16);
        XTESTS_RUN_CASE(test_3_17);
        XTESTS_RUN_CASE(test_3_18);
        XTESTS_RUN_CASE(test_3_19);

        XTESTS_RUN_CASE(test_4_0);
        XTESTS_RUN_CASE(test_4_1);
        XTESTS_RUN_CASE(test_4_2);
        XTESTS_RUN_CASE(test_4_3);
        XTESTS_RUN_CASE(test_4_4);
        XTESTS_RUN_CASE(test_4_5);
        XTESTS_RUN_CASE(test_4_6);
        XTESTS_RUN_CASE(test_4_7);
        XTESTS_RUN_CASE(test_4_8);
        XTESTS_RUN_CASE(test_4_9);
        XTESTS_RUN_CASE(test_4_10);
        XTESTS_RUN_CASE(test_4_11);
        XTESTS_RUN_CASE(test_4_12);
        XTESTS_RUN_CASE(test_4_13);
        XTESTS_RUN_CASE(test_4_14);
        XTESTS_RUN_CASE(test_4_15);
        XTESTS_RUN_CASE(test_4_16);
        XTESTS_RUN_CASE(test_4_17);
        XTESTS_RUN_CASE(test_4_18);
        XTESTS_RUN_CASE(test_4_19);

        XTESTS_RUN_CASE(test_5_0);
        XTESTS_RUN_CASE(test_5_1);
        XTESTS_RUN_CASE(test_5_2);
        XTESTS_RUN_CASE(test_5_3);
        XTESTS_RUN_CASE(test_5_4);
        XTESTS_RUN_CASE(test_5_5);
        XTESTS_RUN_CASE(test_5_6);
        XTESTS_RUN_CASE(test_5_7);
        XTESTS_RUN_CASE(test_5_8);
        XTESTS_RUN_CASE(test_5_9);
        XTESTS_RUN_CASE(test_5_10);
        XTESTS_RUN_CASE(test_5_11);
        XTESTS_RUN_CASE(test_5_12);
        XTESTS_RUN_CASE(test_5_13);
        XTESTS_RUN_CASE(test_5_14);
        XTESTS_RUN_CASE(test_5_15);
        XTESTS_RUN_CASE(test_5_16);
        XTESTS_RUN_CASE(test_5_17);
        XTESTS_RUN_CASE(test_5_18);
        XTESTS_RUN_CASE(test_5_19);

        XTESTS_RUN_CASE(test_6_0);
        XTESTS_RUN_CASE(test_6_1);
        XTESTS_RUN_CASE(test_6_2);
        XTESTS_RUN_CASE(test_6_3);
        XTESTS_RUN_CASE(test_6_4);
        XTESTS_RUN_CASE(test_6_5);
        XTESTS_RUN_CASE(test_6_6);
        XTESTS_RUN_CASE(test_6_7);
        XTESTS_RUN_CASE(test_6_8);
        XTESTS_RUN_CASE(test_6_9);
        XTESTS_RUN_CASE(test_6_10);
        XTESTS_RUN_CASE(test_6_11);
        XTESTS_RUN_CASE(test_6_12);
        XTESTS_RUN_CASE(test_6_13);
        XTESTS_RUN_CASE(test_6_14);
        XTESTS_RUN_CASE(test_6_15);
        XTESTS_RUN_CASE(test_6_16);
        XTESTS_RUN_CASE(test_6_17);
        XTESTS_RUN_CASE(test_6_18);
        XTESTS_RUN_CASE(test_6_19);

        XTESTS_RUN_CASE(test_7_0);
        XTESTS_RUN_CASE(test_7_1);
        XTESTS_RUN_CASE(test_7_2);
        XTESTS_RUN_CASE(test_7_3);
        XTESTS_RUN_CASE(test_7_4);
        XTESTS_RUN_CASE(test_7_5);
        XTESTS_RUN_CASE(test_7_6);
        XTESTS_RUN_CASE(test_7_7);
        XTESTS_RUN_CASE(test_7_8);
        XTESTS_RUN_CASE(test_7_9);
        XTESTS_RUN_CASE(test_7_10);
        XTESTS_RUN_CASE(test_7_11);
        XTESTS_RUN_CASE(test_7_12);
        XTESTS_RUN_CASE(test_7_13);
        XTESTS_RUN_CASE(test_7_14);
        XTESTS_RUN_CASE(test_7_15);
        XTESTS_RUN_CASE(test_7_16);
        XTESTS_RUN_CASE(test_7_17);
        XTESTS_RUN_CASE(test_7_18);
        XTESTS_RUN_CASE(test_7_19);

        XTESTS_RUN_CASE(test_8_0);
        XTESTS_RUN_CASE(test_8_1);
        XTESTS_RUN_CASE(test_8_2);
        XTESTS_RUN_CASE(test_8_3);
        XTESTS_RUN_CASE(test_8_4);
        XTESTS_RUN_CASE(test_8_5);
        XTESTS_RUN_CASE(test_8_6);
        XTESTS_RUN_CASE(test_8_7);
        XTESTS_RUN_CASE(test_8_8);
        XTESTS_RUN_CASE(test_8_9);
        XTESTS_RUN_CASE(test_8_10);
        XTESTS_RUN_CASE(test_8_11);
        XTESTS_RUN_CASE(test_8_12);
        XTESTS_RUN_CASE(test_8_13);
        XTESTS_RUN_CASE(test_8_14);
        XTESTS_RUN_CASE(test_8_15);
        XTESTS_RUN_CASE(test_8_16);
        XTESTS_RUN_CASE(test_8_17);
        XTESTS_RUN_CASE(test_8_18);
        XTESTS_RUN_CASE(test_8_19);

        XTESTS_RUN_CASE(test_9_0);
        XTESTS_RUN_CASE(test_9_1);
        XTESTS_RUN_CASE(test_9_2);
        XTESTS_RUN_CASE(test_9_3);
        XTESTS_RUN_CASE(test_9_4);
        XTESTS_RUN_CASE(test_9_5);
        XTESTS_RUN_CASE(test_9_6);
        XTESTS_RUN_CASE(test_9_7);
        XTESTS_RUN_CASE(test_9_8);
        XTESTS_RUN_CASE(test_9_9);
        XTESTS_RUN_CASE(test_9_10);
        XTESTS_RUN_CASE(test_9_11);
        XTESTS_RUN_CASE(test_9_12);
        XTESTS_RUN_CASE(test_9_13);
        XTESTS_RUN_CASE(test_9_14);
        XTESTS_RUN_CASE(test_9_15);
        XTESTS_RUN_CASE(test_9_16);
        XTESTS_RUN_CASE(test_9_17);
        XTESTS_RUN_CASE(test_9_18);
        XTESTS_RUN_CASE(test_9_19);

        XTESTS_RUN_CASE(test_10_0);
        XTESTS_RUN_CASE(test_10_1);
        XTESTS_RUN_CASE(test_10_2);
        XTESTS_RUN_CASE(test_10_3);
        XTESTS_RUN_CASE(test_10_4);
        XTESTS_RUN_CASE(test_10_5);
        XTESTS_RUN_CASE(test_10_6);
        XTESTS_RUN_CASE(test_10_7);
        XTESTS_RUN_CASE(test_10_8);
        XTESTS_RUN_CASE(test_10_9);
        XTESTS_RUN_CASE(test_10_10);
        XTESTS_RUN_CASE(test_10_11);
        XTESTS_RUN_CASE(test_10_12);
        XTESTS_RUN_CASE(test_10_13);
        XTESTS_RUN_CASE(test_10_14);
        XTESTS_RUN_CASE(test_10_15);
        XTESTS_RUN_CASE(test_10_16);
        XTESTS_RUN_CASE(test_10_17);
        XTESTS_RUN_CASE(test_10_18);
        XTESTS_RUN_CASE(test_10_19);

        XTESTS_RUN_CASE(test_11_0);
        XTESTS_RUN_CASE(test_11_1);
        XTESTS_RUN_CASE(test_11_2);
        XTESTS_RUN_CASE(test_11_3);
        XTESTS_RUN_CASE(test_11_4);
        XTESTS_RUN_CASE(test_11_5);
        XTESTS_RUN_CASE(test_11_6);
        XTESTS_RUN_CASE(test_11_7);
        XTESTS_RUN_CASE(test_11_8);
        XTESTS_RUN_CASE(test_11_9);
        XTESTS_RUN_CASE(test_11_10);
        XTESTS_RUN_CASE(test_11_11);
        XTESTS_RUN_CASE(test_11_12);
        XTESTS_RUN_CASE(test_11_13);
        XTESTS_RUN_CASE(test_11_14);
        XTESTS_RUN_CASE(test_11_15);
        XTESTS_RUN_CASE(test_11_16);
        XTESTS_RUN_CASE(test_11_17);
        XTESTS_RUN_CASE(test_11_18);
        XTESTS_RUN_CASE(test_11_19);

        XTESTS_RUN_CASE(test_12_0);
        XTESTS_RUN_CASE(test_12_1);
        XTESTS_RUN_CASE(test_12_2);
        XTESTS_RUN_CASE(test_12_3);
        XTESTS_RUN_CASE(test_12_4);
        XTESTS_RUN_CASE(test_12_5);
        XTESTS_RUN_CASE(test_12_6);
        XTESTS_RUN_CASE(test_12_7);
        XTESTS_RUN_CASE(test_12_8);
        XTESTS_RUN_CASE(test_12_9);
        XTESTS_RUN_CASE(test_12_10);
        XTESTS_RUN_CASE(test_12_11);
        XTESTS_RUN_CASE(test_12_12);
        XTESTS_RUN_CASE(test_12_13);
        XTESTS_RUN_CASE(test_12_14);
        XTESTS_RUN_CASE(test_12_15);
        XTESTS_RUN_CASE(test_12_16);
        XTESTS_RUN_CASE(test_12_17);
        XTESTS_RUN_CASE(test_12_18);
        XTESTS_RUN_CASE(test_12_19);

        XTESTS_RUN_CASE(test_13_0);
        XTESTS_RUN_CASE(test_13_1);
        XTESTS_RUN_CASE(test_13_2);
        XTESTS_RUN_CASE(test_13_3);
        XTESTS_RUN_CASE(test_13_4);
        XTESTS_RUN_CASE(test_13_5);
        XTESTS_RUN_CASE(test_13_6);
        XTESTS_RUN_CASE(test_13_7);
        XTESTS_RUN_CASE(test_13_8);
        XTESTS_RUN_CASE(test_13_9);
        XTESTS_RUN_CASE(test_13_10);
        XTESTS_RUN_CASE(test_13_11);
        XTESTS_RUN_CASE(test_13_12);
        XTESTS_RUN_CASE(test_13_13);
        XTESTS_RUN_CASE(test_13_14);
        XTESTS_RUN_CASE(test_13_15);
        XTESTS_RUN_CASE(test_13_16);
        XTESTS_RUN_CASE(test_13_17);
        XTESTS_RUN_CASE(test_13_18);
        XTESTS_RUN_CASE(test_13_19);

        XTESTS_RUN_CASE(test_14_0);
        XTESTS_RUN_CASE(test_14_1);
        XTESTS_RUN_CASE(test_14_2);
        XTESTS_RUN_CASE(test_14_3);
        XTESTS_RUN_CASE(test_14_4);
        XTESTS_RUN_CASE(test_14_5);
        XTESTS_RUN_CASE(test_14_6);
        XTESTS_RUN_CASE(test_14_7);
        XTESTS_RUN_CASE(test_14_8);
        XTESTS_RUN_CASE(test_14_9);
        XTESTS_RUN_CASE(test_14_10);
        XTESTS_RUN_CASE(test_14_11);
        XTESTS_RUN_CASE(test_14_12);
        XTESTS_RUN_CASE(test_14_13);
        XTESTS_RUN_CASE(test_14_14);
        XTESTS_RUN_CASE(test_14_15);
        XTESTS_RUN_CASE(test_14_16);
        XTESTS_RUN_CASE(test_14_17);
        XTESTS_RUN_CASE(test_14_18);
        XTESTS_RUN_CASE(test_14_19);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

    using stlsoft::readers::read_from_char_buffer;
    using stlsoft::readers::read_from_iterator_range;
    using stlsoft::read_line_flags;

#if 0
    template <typename S>
    bool read_line(char const* buffer, int cchBuffer, S& line, stlsoft::read_line_flags::flags_t flags)
    {
        stlsoft::read_line_impl::read_from_char_buffer  policy(buffer, (cchBuffer < 0) ? ::strlen(buffer) : cchBuffer);

        return stlsoft::read_line_impl::read_line(policy, line, flags);
    }
#endif /* 0 */

    template<   typename P
            ,   typename S
            >
    bool read_line_from_policy(P& policy, S& line, stlsoft::read_line_flags::flags_t flags)
    {
        return stlsoft::read_line_impl::read_line(policy, line, flags);
    }


static void test_1_0()
{
    read_from_char_buffer   policy("", 0);
    std::string             line0;

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_1()
{
    read_from_char_buffer   policy("a", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_2()
{
    read_from_char_buffer   policy("abcdefghijklmnopqrstuvwxyz", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_3()
{
    read_from_char_buffer   policy("\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_4()
{
    read_from_char_buffer   policy("\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_5()
{
    read_from_char_buffer   policy("\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_6()
{
    read_from_char_buffer   policy("\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_7()
{
    read_from_char_buffer   policy("\r\r\r\r\r\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(10u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_8()
{
    read_from_char_buffer   policy("\r\r\r\r\r\n\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_9()
{
    read_from_char_buffer   policy("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("a\rb", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("c\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("d\re", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("f\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("g\rh", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("i\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("j\rk", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("l\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_10()
{
    read_from_char_buffer   policy("abc\rdef\nghi\r\njkl", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(7u, line0.size());
    TEST_MS_EQ_APPROX("abc\rdef", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(4u, line0.size());
    TEST_MS_EQ_APPROX("ghi\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_1_11()
{
}

static void test_1_12()
{
}

static void test_1_13()
{
}

static void test_1_14()
{
}

static void test_1_15()
{
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




static void test_2_0()
{
    read_from_char_buffer   policy("", 0);
    std::string             line0;

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_1()
{
    read_from_char_buffer   policy("a", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_2()
{
    read_from_char_buffer   policy("abcdefghijklmnopqrstuvwxyz", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_3()
{
    read_from_char_buffer   policy("\r", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_4()
{
    read_from_char_buffer   policy("\n\r", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_5()
{
    read_from_char_buffer   policy("\n\n\r", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\n\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_6()
{
    read_from_char_buffer   policy("\n\n\n\r", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("\n\n\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_7()
{
    read_from_char_buffer   policy("\n\n\n\n\n\n\n\n\n\n\r", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(10u, line0.size());
    TEST_MS_EQ_APPROX("\n\n\n\n\n\n\n\n\n\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_8()
{
    read_from_char_buffer   policy("\n\n\n\n\n\r\n\n\n\n\n\r", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\n\n\n\n\n", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\n\n\n\n\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_9()
{
    read_from_char_buffer   policy("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("b\nc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\nd", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("e\nf", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\ng", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("h\ni", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\nj", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("k\nl", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_10()
{
    read_from_char_buffer   policy("abc\rdef\nghi\r\njkl", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("abc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(7u, line0.size());
    TEST_MS_EQ_APPROX("def\nghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(4u, line0.size());
    TEST_MS_EQ_APPROX("\njkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_2_11()
{
}

static void test_2_12()
{
}

static void test_2_13()
{
}

static void test_2_14()
{
}

static void test_2_15()
{
}

static void test_2_16()
{
}

static void test_2_17()
{
}

static void test_2_18()
{
}

static void test_2_19()
{
}



static void test_3_0()
{
    read_from_char_buffer   policy("", 0);
    std::string             line0;

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_1()
{
    read_from_char_buffer   policy("a", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_2()
{
    read_from_char_buffer   policy("abcdefghijklmnopqrstuvwxyz", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_3()
{
    read_from_char_buffer   policy("\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_4()
{
    read_from_char_buffer   policy("\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_5()
{
    read_from_char_buffer   policy("\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_6()
{
    read_from_char_buffer   policy("\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_7()
{
    read_from_char_buffer   policy("\r\r\r\r\r\r\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(10u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_8()
{
    read_from_char_buffer   policy("\r\r\r\r\r\r\n\r\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_9()
{
    read_from_char_buffer   policy("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("a\rb\nc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("d\re\nf", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("g\rh\ni", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("j\rk\nl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_10()
{
    read_from_char_buffer   policy("abc\rdef\nghi\r\njkl", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(11u, line0.size());
    TEST_MS_EQ_APPROX("abc\rdef\nghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_3_11()
{
}

static void test_3_12()
{
}

static void test_3_13()
{
}

static void test_3_14()
{
}

static void test_3_15()
{
}

static void test_3_16()
{
}

static void test_3_17()
{
}

static void test_3_18()
{
}

static void test_3_19()
{
}




static void test_4_0()
{
    read_from_char_buffer   policy("", 0);
    std::string             line0;

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_1()
{
    read_from_char_buffer   policy("a", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_2()
{
    read_from_char_buffer   policy("abcdefghijklmnopqrstuvwxyz", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_3()
{
    read_from_char_buffer   policy("\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_4()
{
    read_from_char_buffer   policy("\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_5()
{
    read_from_char_buffer   policy("\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_6()
{
    read_from_char_buffer   policy("\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_7()
{
    read_from_char_buffer   policy("\r\r\r\r\r\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_8()
{
    read_from_char_buffer   policy("\r\r\r\r\r\n\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_9()
{
    read_from_char_buffer   policy("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("b", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("c", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("d", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("e", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("f", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("g", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("h", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("i", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("j", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("k", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("l", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_10()
{
    read_from_char_buffer   policy("abc\rdef\nghi\r\njkl", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("abc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("def", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("ghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_4_11()
{
}

static void test_4_12()
{
}

static void test_4_13()
{
}

static void test_4_14()
{
}

static void test_4_15()
{
}

static void test_4_16()
{
}

static void test_4_17()
{
}

static void test_4_18()
{
}

static void test_4_19()
{
}



static void test_5_0()
{
    read_from_char_buffer   policy("", 0);
    std::string             line0;

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_1()
{
    read_from_char_buffer   policy("a", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_2()
{
    read_from_char_buffer   policy("abcdefghijklmnopqrstuvwxyz", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_3()
{
    read_from_char_buffer   policy("\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_4()
{
    read_from_char_buffer   policy("\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_5()
{
    read_from_char_buffer   policy("\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_6()
{
    read_from_char_buffer   policy("\r\n\n\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_7()
{
    read_from_char_buffer   policy("\r\r\r\r\r\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(9u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_8()
{
    read_from_char_buffer   policy("\r\r\r\r\r\n\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(4u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(4u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_9()
{
    read_from_char_buffer   policy("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("a\rb", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("c", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("d\re", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("f", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("g\rh", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("i", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("j\rk", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("l", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_10()
{
    read_from_char_buffer   policy("abc\rdef\nghi\r\njkl", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(7u, line0.size());
    TEST_MS_EQ_APPROX("abc\rdef", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("ghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_5_11()
{
}

static void test_5_12()
{
}

static void test_5_13()
{
}

static void test_5_14()
{
}

static void test_5_15()
{
}

static void test_5_16()
{
}

static void test_5_17()
{
}

static void test_5_18()
{
}

static void test_5_19()
{
}



static void test_6_0()
{
    read_from_char_buffer   policy("", 0);
    std::string             line0;

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_1()
{
    read_from_char_buffer   policy("a", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_2()
{
    read_from_char_buffer   policy("abcdefghijklmnopqrstuvwxyz", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_3()
{
    read_from_char_buffer   policy("\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_4()
{
    read_from_char_buffer   policy("\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_5()
{
    read_from_char_buffer   policy("\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_6()
{
    read_from_char_buffer   policy("\r\n\n\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\n", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_7()
{
    read_from_char_buffer   policy("\r\r\r\r\r\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_8()
{
    read_from_char_buffer   policy("\r\r\r\r\r\n\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_9()
{
    read_from_char_buffer   policy("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("b\nc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("d", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("e\nf", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("g", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("h\ni", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("j", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("k\nl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_10()
{
    read_from_char_buffer   policy("abc\rdef\nghi\r\njkl", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("abc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(7u, line0.size());
    TEST_MS_EQ_APPROX("def\nghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_6_11()
{
}

static void test_6_12()
{
}

static void test_6_13()
{
}

static void test_6_14()
{
}

static void test_6_15()
{
}

static void test_6_16()
{
}

static void test_6_17()
{
}

static void test_6_18()
{
}

static void test_6_19()
{
}



static void test_7_0()
{
    read_from_char_buffer   policy("", 0);
    std::string             line0;

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_1()
{
    read_from_char_buffer   policy("a", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_2()
{
    read_from_char_buffer   policy("abcdefghijklmnopqrstuvwxyz", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_3()
{
    read_from_char_buffer   policy("\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_4()
{
    read_from_char_buffer   policy("\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_5()
{
    read_from_char_buffer   policy("\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_6()
{
    read_from_char_buffer   policy("\r\n\n\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_7()
{
    read_from_char_buffer   policy("\r\r\r\r\r\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_8()
{
    read_from_char_buffer   policy("\r\r\r\r\r\n\r\r\r\r\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_9()
{
    read_from_char_buffer   policy("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("b", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("c", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("d", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("e", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("f", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("g", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("h", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("i", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("j", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("k", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("l", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_10()
{
    read_from_char_buffer   policy("abc\rdef\nghi\r\njkl", -1);
    std::string             line0;

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("abc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("def", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("ghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_7_11()
{
}

static void test_7_12()
{
}

static void test_7_13()
{
}

static void test_7_14()
{
}

static void test_7_15()
{
}

static void test_7_16()
{
}

static void test_7_17()
{
}

static void test_7_18()
{
}

static void test_7_19()
{
}







static void test_8_0()
{
    std::string const   input("");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_1()
{
    std::string const   input("a");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_2()
{
    std::string const   input("abcdefghijklmnopqrstuvwxyz");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_3()
{
    std::string const   input("\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_4()
{
    std::string const   input("\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_5()
{
    std::string const   input("\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_6()
{
    std::string const   input("\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_7()
{
    std::string const   input("\r\r\r\r\r\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(10u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_8()
{
    std::string const   input("\r\r\r\r\r\n\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_9()
{
    std::string const   input("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("a\rb", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("c\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("d\re", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("f\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("g\rh", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("i\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("j\rk", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("l\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_10()
{
    std::string const   input("abc\rdef\nghi\r\njkl");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(7u, line0.size());
    TEST_MS_EQ_APPROX("abc\rdef", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(4u, line0.size());
    TEST_MS_EQ_APPROX("ghi\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_8_11()
{
}

static void test_8_12()
{
}

static void test_8_13()
{
}

static void test_8_14()
{
}

static void test_8_15()
{
}

static void test_8_16()
{
}

static void test_8_17()
{
}

static void test_8_18()
{
}

static void test_8_19()
{
}




static void test_9_0()
{
    std::string const   input("");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_1()
{
    std::string const   input("a");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_2()
{
    std::string const   input("abcdefghijklmnopqrstuvwxyz");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_3()
{
    std::string const   input("\r");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_4()
{
    std::string const   input("\n\r");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_5()
{
    std::string const   input("\n\n\r");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\n\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_6()
{
    std::string const   input("\n\n\n\r");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("\n\n\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_7()
{
    std::string const   input("\n\n\n\n\n\n\n\n\n\n\r");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(10u, line0.size());
    TEST_MS_EQ_APPROX("\n\n\n\n\n\n\n\n\n\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_8()
{
    std::string const   input("\n\n\n\n\n\r\n\n\n\n\n\r");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\n\n\n\n\n", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\n\n\n\n\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_9()
{
    std::string const   input("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("b\nc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\nd", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("e\nf", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\ng", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("h\ni", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\nj", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("k\nl", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_10()
{
    std::string const   input("abc\rdef\nghi\r\njkl");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("abc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(7u, line0.size());
    TEST_MS_EQ_APPROX("def\nghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(4u, line0.size());
    TEST_MS_EQ_APPROX("\njkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_9_11()
{
}

static void test_9_12()
{
}

static void test_9_13()
{
}

static void test_9_14()
{
}

static void test_9_15()
{
}

static void test_9_16()
{
}

static void test_9_17()
{
}

static void test_9_18()
{
}

static void test_9_19()
{
}



static void test_10_0()
{
    std::string const   input("");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_1()
{
    std::string const   input("a");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_2()
{
    std::string const   input("abcdefghijklmnopqrstuvwxyz");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_3()
{
    std::string const   input("\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_4()
{
    std::string const   input("\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_5()
{
    std::string const   input("\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(2u, line0.size());
    TEST_MS_EQ_APPROX("\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_6()
{
    std::string const   input("\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_7()
{
    std::string const   input("\r\r\r\r\r\r\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(10u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_8()
{
    std::string const   input("\r\r\r\r\r\r\n\r\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_9()
{
    std::string const   input("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("a\rb\nc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("d\re\nf", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("g\rh\ni", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(5u, line0.size());
    TEST_MS_EQ_APPROX("j\rk\nl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_10()
{
    std::string const   input("abc\rdef\nghi\r\njkl");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(11u, line0.size());
    TEST_MS_EQ_APPROX("abc\rdef\nghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_10_11()
{
}

static void test_10_12()
{
}

static void test_10_13()
{
}

static void test_10_14()
{
}

static void test_10_15()
{
}

static void test_10_16()
{
}

static void test_10_17()
{
}

static void test_10_18()
{
}

static void test_10_19()
{
}




static void test_11_0()
{
    std::string const   input("");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_1()
{
    std::string const   input("a");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_2()
{
    std::string const   input("abcdefghijklmnopqrstuvwxyz");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_3()
{
    std::string const   input("\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_4()
{
    std::string const   input("\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_5()
{
    std::string const   input("\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_6()
{
    std::string const   input("\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_7()
{
    std::string const   input("\r\r\r\r\r\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_8()
{
    std::string const   input("\r\r\r\r\r\n\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_9()
{
    std::string const   input("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("b", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("c", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("d", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("e", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("f", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("g", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("h", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("i", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("j", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("k", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("l", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_10()
{
    std::string const   input("abc\rdef\nghi\r\njkl");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("abc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("def", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("ghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_11_11()
{
}

static void test_11_12()
{
}

static void test_11_13()
{
}

static void test_11_14()
{
}

static void test_11_15()
{
}

static void test_11_16()
{
}

static void test_11_17()
{
}

static void test_11_18()
{
}

static void test_11_19()
{
}



static void test_12_0()
{
    std::string const   input("");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_1()
{
    std::string const   input("a");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_2()
{
    std::string const   input("abcdefghijklmnopqrstuvwxyz");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_3()
{
    std::string const   input("\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_4()
{
    std::string const   input("\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_5()
{
    std::string const   input("\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_6()
{
    std::string const   input("\r\n\n\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_7()
{
    std::string const   input("\r\r\r\r\r\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(9u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r\r\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_8()
{
    std::string const   input("\r\r\r\r\r\n\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(4u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(4u, line0.size());
    TEST_MS_EQ_APPROX("\r\r\r\r", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_9()
{
    std::string const   input("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("a\rb", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("c", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("d\re", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("f", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("g\rh", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("i", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("j\rk", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("l", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_10()
{
    std::string const   input("abc\rdef\nghi\r\njkl");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(7u, line0.size());
    TEST_MS_EQ_APPROX("abc\rdef", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("ghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseLfAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_12_11()
{
}

static void test_12_12()
{
}

static void test_12_13()
{
}

static void test_12_14()
{
}

static void test_12_15()
{
}

static void test_12_16()
{
}

static void test_12_17()
{
}

static void test_12_18()
{
}

static void test_12_19()
{
}



static void test_13_0()
{
    std::string const   input("");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_1()
{
    std::string const   input("a");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_2()
{
    std::string const   input("abcdefghijklmnopqrstuvwxyz");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_3()
{
    std::string const   input("\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\n", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_4()
{
    std::string const   input("\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_5()
{
    std::string const   input("\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_6()
{
    std::string const   input("\r\n\n\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("\n", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_7()
{
    std::string const   input("\r\r\r\r\r\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_8()
{
    std::string const   input("\r\r\r\r\r\n\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_9()
{
    std::string const   input("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("b\nc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("d", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("e\nf", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("g", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("h\ni", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("j", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("k\nl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_10()
{
    std::string const   input("abc\rdef\nghi\r\njkl");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("abc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(7u, line0.size());
    TEST_MS_EQ_APPROX("def\nghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::recogniseCrAsEOL | read_line_flags::recogniseCrLfAsEOL));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_13_11()
{
}

static void test_13_12()
{
}

static void test_13_13()
{
}

static void test_13_14()
{
}

static void test_13_15()
{
}

static void test_13_16()
{
}

static void test_13_17()
{
}

static void test_13_18()
{
}

static void test_13_19()
{
}



static void test_14_0()
{
    std::string const   input("");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_1()
{
    std::string const   input("a");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_2()
{
    std::string const   input("abcdefghijklmnopqrstuvwxyz");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(26u, line0.size());
    TEST_MS_EQ_APPROX("abcdefghijklmnopqrstuvwxyz", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_3()
{
    std::string const   input("\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_4()
{
    std::string const   input("\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_5()
{
    std::string const   input("\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_6()
{
    std::string const   input("\r\n\n\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_7()
{
    std::string const   input("\r\r\r\r\r\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_8()
{
    std::string const   input("\r\r\r\r\r\n\r\r\r\r\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_9()
{
    std::string const   input("a\rb\nc\r\nd\re\nf\r\ng\rh\ni\r\nj\rk\nl\r\n");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("a", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("b", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("c", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("d", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("e", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("f", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("g", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("h", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("i", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("j", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("k", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(1u, line0.size());
    TEST_MS_EQ_APPROX("l", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_10()
{
    std::string const   input("abc\rdef\nghi\r\njkl");
    std::string         line0;

    read_from_iterator_range<std::string::const_iterator> policy(input.begin(), input.end());

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("abc", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("def", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("ghi", line0);

    TEST_BOOLEAN_EQ(true, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(3u, line0.size());
    TEST_MS_EQ_APPROX("jkl", line0);

    TEST_BOOLEAN_EQ(false, read_line_from_policy(policy, line0, read_line_flags::flags_t(0)));
    TEST_INT_EQ(0u, line0.size());
    TEST_MS_EQ_APPROX("", line0);
}

static void test_14_11()
{
}

static void test_14_12()
{
}

static void test_14_13()
{
}

static void test_14_14()
{
}

static void test_14_15()
{
}

static void test_14_16()
{
}

static void test_14_17()
{
}

static void test_14_18()
{
}

static void test_14_19()
{
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

