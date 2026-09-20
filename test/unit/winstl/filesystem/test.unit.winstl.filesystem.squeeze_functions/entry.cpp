/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.winstl.filesystem.squeeze_functions/entry.cpp
 *
 * Purpose: Unit-tests for `winstl::squeeze_path`.
 *
 * Created: 29th October 2016
 * Updated: 9th August 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <winstl/filesystem/squeeze_functions.hpp>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_NULL_BUFFER();
    static void TEST_SUFFICIENT_SPACE();
    static void TEST_EXACT_SPACE();
    static void TEST_INSUFFICIENT_SPACE();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char *argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSE_HELP_OR_VERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.filesystem.squeeze_functions", verbosity))
    {
        XTESTS_RUN_CASE(TEST_NULL_BUFFER);
        XTESTS_RUN_CASE(TEST_SUFFICIENT_SPACE);
        XTESTS_RUN_CASE(TEST_EXACT_SPACE);
        XTESTS_RUN_CASE(TEST_INSUFFICIENT_SPACE);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_NULL_BUFFER()
{
    // stem only
    {
        char const* const input = "abcdef";

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 0);

            TEST_INT_EQ(7, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 4);

            TEST_INT_EQ(7, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 10);

            TEST_INT_EQ(7, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 11);

            TEST_INT_EQ(7, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 12);

            TEST_INT_EQ(7, cch);
        }
    }

    // basename
    {
        char const* const input = "remove_cmake_artefacts.sh";

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 0);

            TEST_INT_EQ(26, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 4);

            TEST_INT_EQ(26, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 10);

            TEST_INT_EQ(26, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 11);

            TEST_INT_EQ(26, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 12);

            TEST_INT_EQ(26, cch);
        }
    }

    // slash-rooted path
    {
        char const* const input = "/_/xyz/mno/abcdef.ghi";

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 0);

            TEST_INT_EQ(22, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 4);

            TEST_INT_EQ(22, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 10);

            TEST_INT_EQ(22, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 11);

            TEST_INT_EQ(22, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 12);

            TEST_INT_EQ(22, cch);
        }
    }

    // drive-rooted path
    {
        char const* const input = "C:/_/xyz/mno/abcdef.ghi";

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 0);

            TEST_INT_EQ(24, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 4);

            TEST_INT_EQ(24, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 10);

            TEST_INT_EQ(24, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 11);

            TEST_INT_EQ(24, cch);
        }

        {
            size_t const cch = winstl::path_squeeze(input, static_cast<char*>(NULL), 12);

            TEST_INT_EQ(24, cch);
        }
    }
}

static void TEST_SUFFICIENT_SPACE()
{
    // stem only
    {
        char const* const input = "abcdef";

        {
            char            buff[101];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(7, cch);
            TEST_MS_EQ("abcdef", buff);
        }

        {
            char            buff[8];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(7, cch);
            TEST_MS_EQ("abcdef", buff);
        }
    }

    // stem only (short)
    {
        char const* const input = "abc";

        {
            char            buff[101];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(4, cch);
            TEST_MS_EQ("abc", buff);
        }
    }

    // basename
    {
        char const* const input = "remove_cmake_artefacts.sh";

        {
            char            buff[101];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(26, cch);
            TEST_MS_EQ("remove_cmake_artefacts.sh", buff);
        }

        {
            char            buff[27];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(26, cch);
            TEST_MS_EQ("remove_cmake_artefacts.sh", buff);
        }

        {
            char            buff[28];
            size_t const    cch = (buff[25] = buff[26] = buff[27] = '#', winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff)));

            TEST_INT_EQ(26, cch);
            TEST_CHAR_EQ('#', buff[27]);
            TEST_MS_EQ("remove_cmake_artefacts.sh", buff);
        }

        {
            char            buff[29];
            size_t const    cch = (buff[25] = buff[26] = buff[27] = buff[28] = '#', winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff)));

            TEST_INT_EQ(26, cch);
            TEST_CHAR_EQ('#', buff[28]);
            TEST_MS_EQ("remove_cmake_artefacts.sh", buff);
        }
    }


    // slash-rooted path
    {
        char const* const input = "/_/xyz/mno/abcdef.ghi";

        {
            char            buff[23];
            size_t const    cch = (buff[22] = '#', winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff)));

            TEST_INT_EQ(22, cch);
            TEST_CHAR_EQ('#', buff[22]);
            TEST_MS_EQ("/_/xyz/mno/abcdef.ghi", buff);
        }
    }

    // slash-rooted path (short basename)
    {
        char const* const input = "/_/xyz/mno/a.b";

        {
            char            buff[23];
            size_t const    cch = (buff[14] = buff[15] = '#', winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff)));

            TEST_INT_EQ(15, cch);
            TEST_CHAR_EQ('#', buff[15]);
            TEST_MS_EQ("/_/xyz/mno/a.b", buff);
        }
    }
}

static void TEST_EXACT_SPACE()
{
    // stem only
    {
        char const* const input = "abcdef";

        {
            char            buff[7];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(7, cch);
            TEST_MS_EQ("abcdef", buff);
        }
    }

    // stem only (short)
    {
        char const* const input = "abc";

        {
            char            buff[4];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(4, cch);
            TEST_MS_EQ("abc", buff);
        }
    }

    // basename
    {
        char const* const input = "remove_cmake_artefacts.sh";

        {
            char            buff[26];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(26, cch);
            TEST_MS_EQ("remove_cmake_artefacts.sh", buff);
        }
    }

    // slash-rooted path
    {
        char const* const input = "/_/xyz/mno/abcdef.ghi";

        {
            char            buff[22];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(22, cch);
            TEST_MS_EQ("/_/xyz/mno/abcdef.ghi", buff);
        }
    }

    // slash-rooted path (short basename)
    {
        char const* const input = "/_/xyz/mno/a.b";

        {
            char            buff[22];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(15, cch);
            TEST_MS_EQ("/_/xyz/mno/a.b", buff);
        }
    }

    // drive-rooted path
    {
        char const* const input = "C:/_/xyz/mno/abcdef.ghi";

        {
            char            buff[24];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(24, cch);
            TEST_MS_EQ("C:/_/xyz/mno/abcdef.ghi", buff);
        }
    }
}

static void TEST_INSUFFICIENT_SPACE()
{
    // stem only
    {
        char const* const input = "abcdef";

        {
            char            buff[6] = { '\0', '\1', '\2', '\3', '\4', '\5' };
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(6, cch);
            TEST_CHAR_EQ('\0', buff[5]);
            TEST_MS_EQ("a...f", buff);
        }

        {
            char            buff[7] = { '\0', '\1', '\2', '\3', '\4', '\5', '\6' };
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff) - 1);

            TEST_INT_EQ(6, cch);
            TEST_CHAR_EQ('\6', buff[6]);
            TEST_CHAR_EQ('\0', buff[5]);
            TEST_MS_EQ("a...f", buff);
        }

        {
            char            buff[5];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(5, cch);
            TEST_MS_EQ("abcd", buff);
        }

        {
            char            buff[4];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(4, cch);
            TEST_MS_EQ("abc", buff);
        }

        {
            char            buff[3];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(3, cch);
            TEST_MS_EQ("ab", buff);
        }
    }

    // stem only (short)
    {
        char const* const input = "abc";

        {
            char            buff[3];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(3, cch);
            TEST_MS_EQ("ab", buff);
        }
    }

    // basename
    {
        char const* const input = "remove_cmake_artefacts.sh";

        {
            char            buff[25];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(25, cch);
            TEST_MS_EQ("remove_cma...rtefacts.sh", buff);
        }

        {
            char            buff[24];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(24, cch);
            TEST_MS_EQ("remove_cma...tefacts.sh", buff);
        }

        {
            char            buff[20];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(20, cch);
            TEST_MS_EQ("remove_c...facts.sh", buff);
        }

        {
            char            buff[16];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(16, cch);
            TEST_MS_EQ("remove...cts.sh", buff);
        }

        {
            char            buff[12];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(12, cch);
            TEST_MS_EQ("remo...s.sh", buff);
        }

        {
            char            buff[9];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(9, cch);
            TEST_MS_EQ("re....sh", buff);
        }
    }

    // slash-rooted path
    {
        char const* const input = "/_/xyz/mno/abcdef.ghi";

        {
            char            buff[21];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(21, cch);
            TEST_MS_EQ("/_/xyz.../abcdef.ghi", buff);
        }

        {
            char            buff[20];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(20, cch);
            TEST_MS_EQ("/_/xy.../abcdef.ghi", buff);
        }

        {
            char            buff[19];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(19, cch);
            TEST_MS_EQ("/_/x.../abcdef.ghi", buff);
        }

        {
            char            buff[18];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(18, cch);
            TEST_MS_EQ("/_/.../abcdef.ghi", buff);
        }

        {
            char            buff[17];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(17, cch);
            TEST_MS_EQ("/_.../abcdef.ghi", buff);
        }

        {
            char            buff[16];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(16, cch);
            TEST_MS_EQ("/.../abcdef.ghi", buff);
        }

        {
            char            buff[15];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("abcdef.ghi", buff);
        }

        {
            char            buff[12];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("abcdef.ghi", buff);
        }

        {
            char            buff[11];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("abcdef.ghi", buff);
        }

        {
            char            buff[10];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(10, cch);
            TEST_MS_EQ("abc...ghi", buff);
        }

        {
            char            buff[9];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(9, cch);
            TEST_MS_EQ("ab...ghi", buff);
        }

        {
            char            buff[7];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(7, cch);
            TEST_MS_EQ("a...hi", buff);
        }

        {
            char            buff[6];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(6, cch);
            TEST_MS_EQ("a...i", buff);
        }

        {
            char            buff[5];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(5, cch);
            TEST_MS_EQ("abcd", buff);
        }

        {
            char            buff[4];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(4, cch);
            TEST_MS_EQ("abc", buff);
        }

        {
            char            buff[3];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(3, cch);
            TEST_MS_EQ("ab", buff);
        }

        {
            char            buff[2];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(2, cch);
            TEST_MS_EQ("a", buff);
        }
    }

    // slash-rooted path (short basename)
    {
        char const* const input = "/_/xyz/mno/a.b";

        {
            char            buff[15];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(15, cch);
            TEST_MS_EQ("/_/xyz/mno/a.b", buff);
        }

        {
            char            buff[14];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(14, cch);
            TEST_MS_EQ("/_/xyz.../a.b", buff);
        }

        {
            char            buff[12];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(12, cch);
            TEST_MS_EQ("/_/x.../a.b", buff);
        }

        {
            char            buff[11];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("/_/.../a.b", buff);
        }

        {
            char            buff[10];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(10, cch);
            TEST_MS_EQ("/_.../a.b", buff);
        }

        {
            char            buff[9];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(9, cch);
            TEST_MS_EQ("/.../a.b", buff);
        }

        {
            char            buff[7];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(4, cch);
            TEST_MS_EQ("a.b", buff);
        }

        {
            char            buff[6];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(4, cch);
            TEST_MS_EQ("a.b", buff);
        }

        {
            char            buff[5];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(4, cch);
            TEST_MS_EQ("a.b", buff);
        }

        {
            char            buff[4];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(4, cch);
            TEST_MS_EQ("a.b", buff);
        }

        {
            char            buff[3];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(3, cch);
            TEST_MS_EQ("a.", buff);
        }

        {
            char            buff[2];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(2, cch);
            TEST_MS_EQ("a", buff);
        }
    }

    // drive-rooted path
    {
        char const* const input = "C:/_/xyz/mno/abcdef.ghi";

        {
            char            buff[23];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(23, cch);
            TEST_MS_EQ("C:/_/xyz.../abcdef.ghi", buff);
        }

        {
            char            buff[22];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(22, cch);
            TEST_MS_EQ("C:/_/xy.../abcdef.ghi", buff);
        }

        {
            char            buff[21];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(21, cch);
            TEST_MS_EQ("C:/_/x.../abcdef.ghi", buff);
        }

        {
            char            buff[20];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(20, cch);
            TEST_MS_EQ("C:/_/.../abcdef.ghi", buff);
        }

        {
            char            buff[19];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(19, cch);
            TEST_MS_EQ("C:/_.../abcdef.ghi", buff);
        }

        {
            char            buff[18];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(18, cch);
            TEST_MS_EQ("C:/.../abcdef.ghi", buff);
        }

        {
            char            buff[17];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("abcdef.ghi", buff);
        }

        {
            char            buff[16];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("abcdef.ghi", buff);
        }

        {
            char            buff[15];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("abcdef.ghi", buff);
        }

        {
            char            buff[12];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("abcdef.ghi", buff);
        }

        {
            char            buff[11];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(11, cch);
            TEST_MS_EQ("abcdef.ghi", buff);
        }

        {
            char            buff[10];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(10, cch);
            TEST_MS_EQ("abc...ghi", buff);
        }

        {
            char            buff[9];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(9, cch);
            TEST_MS_EQ("ab...ghi", buff);
        }

        {
            char            buff[7];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(7, cch);
            TEST_MS_EQ("a...hi", buff);
        }

        {
            char            buff[6];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(6, cch);
            TEST_MS_EQ("a...i", buff);
        }

        {
            char            buff[5];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(5, cch);
            TEST_MS_EQ("abcd", buff);
        }

        {
            char            buff[4];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(4, cch);
            TEST_MS_EQ("abc", buff);
        }

        {
            char            buff[3];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(3, cch);
            TEST_MS_EQ("ab", buff);
        }

        {
            char            buff[2];
            size_t const    cch = winstl::path_squeeze(input, &buff[0], STLSOFT_NUM_ELEMENTS(buff));

            TEST_INT_EQ(2, cch);
            TEST_MS_EQ("a", buff);
        }
    }
}
} /* anonymous namespace */


/* ///////////////////////////// end of file //////////////////////////// */

