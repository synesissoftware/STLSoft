/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/stlsoft/algorithms/pod/entry.cpp
 *
 * Purpose: Unit-tests for stlsoft::pod_copy(), pod_move(), and pod_fill_n().
 *
 * Created: 2nd November 2026
 * Updated: 7th November 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <stlsoft/algorithms/pod.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <xtests/terse-api.h>
#include <xtests/xtests.h>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void TEST_copy_n_0_NEITHER_READS_NOR_WRITES();
    static void TEST_copy_n_COPIES();
    static void TEST_copy_EMPTY_RANGE();
    static void TEST_copy_RANGE_COPIES();
    static void TEST_copy_INT_RANGE();
    static void TEST_copy_n_DIFFERENT_TYPE();
    static void TEST_move_n_0_NEITHER_READS_NOR_WRITES();
    static void TEST_move_n_OVERLAP();
    static void TEST_move_EMPTY_RANGE();
    static void TEST_fill_n_0_NEITHER_WRITES();
    static void TEST_fill_n_SETS_BYTES();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER(__FILE__, verbosity))
    {
        XTESTS_RUN_CASE(TEST_copy_n_0_NEITHER_READS_NOR_WRITES);
        XTESTS_RUN_CASE(TEST_copy_n_COPIES);
        XTESTS_RUN_CASE(TEST_copy_EMPTY_RANGE);
        XTESTS_RUN_CASE(TEST_copy_RANGE_COPIES);
        XTESTS_RUN_CASE(TEST_copy_INT_RANGE);
        XTESTS_RUN_CASE(TEST_copy_n_DIFFERENT_TYPE);
        XTESTS_RUN_CASE(TEST_move_n_0_NEITHER_READS_NOR_WRITES);
        XTESTS_RUN_CASE(TEST_move_n_OVERLAP);
        XTESTS_RUN_CASE(TEST_move_EMPTY_RANGE);
        XTESTS_RUN_CASE(TEST_fill_n_0_NEITHER_WRITES);
        XTESTS_RUN_CASE(TEST_fill_n_SETS_BYTES);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{

static void TEST_copy_n_0_NEITHER_READS_NOR_WRITES()
{
    int         idest[] = { 9, 8, 7 };
    int         isrc[] = { 1, 2, 3 };
    char        cdest[] = { 'X', 'Y' };

    stlsoft::pod_copy_n(idest, isrc, 0);

    TEST_INT_EQ(9, idest[0]);
    TEST_INT_EQ(8, idest[1]);
    TEST_INT_EQ(7, idest[2]);

    stlsoft::pod_copy_n(idest, static_cast<int const*>(NULL), 0);
    stlsoft::pod_copy_n(static_cast<int*>(NULL), static_cast<int const*>(NULL), 0);
    stlsoft::pod_copy_n(cdest, static_cast<char const*>(NULL), 0);

    TEST_CHAR_EQ('X', cdest[0]);
    TEST_CHAR_EQ('Y', cdest[1]);
}

static void TEST_copy_n_COPIES()
{
    int         src[] = { 1, 2, 3 };
    int         dest[] = { 9, 9, 9 };

    stlsoft::pod_copy_n(dest, src, 2);

    TEST_INT_EQ(1, dest[0]);
    TEST_INT_EQ(2, dest[1]);
    TEST_INT_EQ(9, dest[2]);
}

static void TEST_copy_EMPTY_RANGE()
{
    char const  src[] = { 'a', 'b' };
    char        dest[] = { 'X', 'Y' };

    stlsoft::pod_copy(src, src, dest);

    TEST_CHAR_EQ('X', dest[0]);
    TEST_CHAR_EQ('Y', dest[1]);

    stlsoft::pod_copy(src, src, static_cast<char*>(NULL));
}

static void TEST_copy_RANGE_COPIES()
{
    char const  src[] = { 'a', 'b' };
    char        dest[] = { 'X', 'Y' };

    stlsoft::pod_copy(src, src + 2, dest);

    TEST_CHAR_EQ('a', dest[0]);
    TEST_CHAR_EQ('b', dest[1]);
}

static void TEST_copy_INT_RANGE()
{
    int const   src[] = { 10, 20, 30 };
    int         dest[3] = { 0, 0, 0 };

    stlsoft::pod_copy(&src[0], &src[3], &dest[0]);

    TEST_INT_EQ(10, dest[0]);
    TEST_INT_EQ(20, dest[1]);
    TEST_INT_EQ(30, dest[2]);
}

static void TEST_copy_n_DIFFERENT_TYPE()
{
    char const      src[] = { 'a', 'b', 'c' };
    unsigned char   dest[] = { 1, 2, 3 };

    stlsoft::pod_copy_n(dest, src, 0);

    TEST_INT_EQ(1, static_cast<int>(dest[0]));
    TEST_INT_EQ(2, static_cast<int>(dest[1]));
    TEST_INT_EQ(3, static_cast<int>(dest[2]));

    stlsoft::pod_copy_n(dest, src, 2);

    TEST_INT_EQ(static_cast<int>('a'), static_cast<int>(dest[0]));
    TEST_INT_EQ(static_cast<int>('b'), static_cast<int>(dest[1]));
    TEST_INT_EQ(3, static_cast<int>(dest[2]));

    stlsoft::pod_copy_n(static_cast<unsigned char*>(NULL), static_cast<char const*>(NULL), 0);
}

static void TEST_move_n_0_NEITHER_READS_NOR_WRITES()
{
    int         dest[] = { 9, 8 };
    int         src[] = { 1, 2 };

    stlsoft::pod_move_n(dest, src, 0);

    TEST_INT_EQ(9, dest[0]);
    TEST_INT_EQ(8, dest[1]);

    stlsoft::pod_move_n(static_cast<int*>(NULL), static_cast<int const*>(NULL), 0);

    unsigned char   udest[] = { 1, 2 };
    char const      usrc[] = { 'a', 'b' };

    stlsoft::pod_move_n(udest, usrc, 0);

    TEST_INT_EQ(1, static_cast<int>(udest[0]));
    TEST_INT_EQ(2, static_cast<int>(udest[1]));

    stlsoft::pod_move_n(static_cast<unsigned char*>(NULL), static_cast<char const*>(NULL), 0);
}

static void TEST_move_n_OVERLAP()
{
    char buf[] = { 'a', 'b', 'c', 'd' };

    stlsoft::pod_move_n(buf + 1, buf, 3);

    TEST_CHAR_EQ('a', buf[0]);
    TEST_CHAR_EQ('a', buf[1]);
    TEST_CHAR_EQ('b', buf[2]);
    TEST_CHAR_EQ('c', buf[3]);

    char const      src[] = { 'a', 'b', 'c' };
    unsigned char   dest[] = { 1, 2, 3 };

    stlsoft::pod_move_n(dest, src, 2);

    TEST_INT_EQ(static_cast<int>('a'), static_cast<int>(dest[0]));
    TEST_INT_EQ(static_cast<int>('b'), static_cast<int>(dest[1]));
    TEST_INT_EQ(3, static_cast<int>(dest[2]));
}

static void TEST_move_EMPTY_RANGE()
{
    char const  src[] = { 'a', 'b' };
    char        dest[] = { 'X', 'Y' };

    stlsoft::pod_move(src, src, dest);

    TEST_CHAR_EQ('X', dest[0]);
    TEST_CHAR_EQ('Y', dest[1]);

    stlsoft::pod_move(src, src, static_cast<char*>(NULL));
}

static void TEST_fill_n_0_NEITHER_WRITES()
{
    char            buf[] = { 'X', 'Y', 'Z' };
    signed char     sbuf[] = { 'X', 'Y' };
    unsigned char   ubuf[] = { 'X', 'Y' };

    stlsoft::pod_fill_n(buf, 0, 'a');
    stlsoft::pod_fill_n(sbuf, 0, 'a');
    stlsoft::pod_fill_n(ubuf, 0, 'a');

    TEST_CHAR_EQ('X', buf[0]);
    TEST_CHAR_EQ('Y', buf[1]);
    TEST_CHAR_EQ('Z', buf[2]);
    TEST_INT_EQ(static_cast<int>('X'), static_cast<int>(sbuf[0]));
    TEST_INT_EQ(static_cast<int>('Y'), static_cast<int>(sbuf[1]));
    TEST_INT_EQ(static_cast<int>('X'), static_cast<int>(ubuf[0]));
    TEST_INT_EQ(static_cast<int>('Y'), static_cast<int>(ubuf[1]));

    stlsoft::pod_fill_n(static_cast<char*>(NULL), 0, 'a');
    stlsoft::pod_fill_n(static_cast<signed char*>(NULL), 0, 'a');
    stlsoft::pod_fill_n(static_cast<unsigned char*>(NULL), 0, 'a');
}

static void TEST_fill_n_SETS_BYTES()
{
    char            buf[] = { 'X', 'Y', 'Z' };
    signed char     sbuf[] = { 'X', 'Y', 'Z' };
    unsigned char   ubuf[] = { 'X', 'Y', 'Z' };

    stlsoft::pod_fill_n(buf, 2, 'a');
    stlsoft::pod_fill_n(sbuf, 2, 'b');
    stlsoft::pod_fill_n(ubuf, 2, 'c');

    TEST_CHAR_EQ('a', buf[0]);
    TEST_CHAR_EQ('a', buf[1]);
    TEST_CHAR_EQ('Z', buf[2]);
    TEST_INT_EQ(static_cast<int>('b'), static_cast<int>(sbuf[0]));
    TEST_INT_EQ(static_cast<int>('b'), static_cast<int>(sbuf[1]));
    TEST_INT_EQ(static_cast<int>('Z'), static_cast<int>(sbuf[2]));
    TEST_INT_EQ(static_cast<int>('c'), static_cast<int>(ubuf[0]));
    TEST_INT_EQ(static_cast<int>('c'), static_cast<int>(ubuf[1]));
    TEST_INT_EQ(static_cast<int>('Z'), static_cast<int>(ubuf[2]));
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

