/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/unixstl/filesystem/path_classify/entry.cpp
 *
 * Purpose: Unit-tests for `unixstl_C_path_classify` /
 *          `numDotsDirectoryParts`.
 *
 * Created: 20th October 2026
 * Updated: 20th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <unixstl/filesystem/path_classify_functions.h>

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
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_numDotsDirectoryParts_EMPTY_AND_ENTRY_ONLY();
    static void TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_ENTRY();
    static void TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_DIRECTORY();
    static void TEST_numDotsDirectoryParts_MIXED_DIRECTORY_PARTS();
    static void TEST_numDotsDirectoryParts_NON_EXACT_DOT_NAMES();
    static void TEST_numDotsDirectoryParts_SLASH_ROOTED();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.unixstl.filesystem.path_classify", verbosity))
    {
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_EMPTY_AND_ENTRY_ONLY);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_ENTRY);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_DIRECTORY);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_MIXED_DIRECTORY_PARTS);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_NON_EXACT_DOT_NAMES);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_SLASH_ROOTED);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

/* Expands at the call site so assertion failures keep path/line context. */
#define CLASSIFY_EXPECT_DOTS_(path, expected_dots, expected_parts)          \
                                                                            \
    do                                                                      \
    {                                                                       \
        unixstl_C_path_classification_results_m_t   results_;               \
        char const* const                           path_   =   (path);     \
        size_t const                                cch_    =               \
            (ss_nullptr_k == path_) ? 0u : strlen(path_);                   \
        unixstl_C_path_classification_t const       pc_     =               \
            unixstl_C_path_classify(path_, cch_, 0, &results_);             \
                                                                            \
        TEST_INT_GE(unixstl_C_PathType_Empty, pc_);                         \
        TEST_INT_EQ((expected_dots), results_.numDotsDirectoryParts);       \
        TEST_INT_EQ((expected_parts), results_.numDirectoryParts);          \
    } while (0)


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

static void TEST_numDotsDirectoryParts_EMPTY_AND_ENTRY_ONLY()
{
    CLASSIFY_EXPECT_DOTS_("", 0u, 0u);
    CLASSIFY_EXPECT_DOTS_("file.txt", 0u, 0u);
    CLASSIFY_EXPECT_DOTS_("a/b/c", 0u, 2u);
}

static void TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_ENTRY()
{
    /* Entry is excluded from the dots-directory-parts count. */
    CLASSIFY_EXPECT_DOTS_(".", 0u, 0u);
    CLASSIFY_EXPECT_DOTS_("..", 0u, 0u);
    CLASSIFY_EXPECT_DOTS_("foo/.", 0u, 1u);
    CLASSIFY_EXPECT_DOTS_("foo/..", 0u, 1u);
}

static void TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_DIRECTORY()
{
    CLASSIFY_EXPECT_DOTS_("./file", 1u, 1u);
    CLASSIFY_EXPECT_DOTS_("../file", 1u, 1u);
    CLASSIFY_EXPECT_DOTS_("a/./", 1u, 2u);
    CLASSIFY_EXPECT_DOTS_("a/../", 1u, 2u);
}

static void TEST_numDotsDirectoryParts_MIXED_DIRECTORY_PARTS()
{
    CLASSIFY_EXPECT_DOTS_("a/./b", 1u, 2u);
    CLASSIFY_EXPECT_DOTS_("a/../b", 1u, 2u);
    CLASSIFY_EXPECT_DOTS_("a/./../b", 2u, 3u);
    CLASSIFY_EXPECT_DOTS_("./.././file", 3u, 3u);
}

static void TEST_numDotsDirectoryParts_NON_EXACT_DOT_NAMES()
{
    /* Only whole components that are exactly "." or ".." count. */
    CLASSIFY_EXPECT_DOTS_(".hidden/file", 0u, 1u);
    CLASSIFY_EXPECT_DOTS_(".../file", 0u, 1u);
    CLASSIFY_EXPECT_DOTS_("a/.b/c", 0u, 2u);
    CLASSIFY_EXPECT_DOTS_("a/..b/c", 0u, 2u);
}

static void TEST_numDotsDirectoryParts_SLASH_ROOTED()
{
    CLASSIFY_EXPECT_DOTS_("/a/b", 0u, 2u);
    CLASSIFY_EXPECT_DOTS_("/a/./b", 1u, 3u);
    CLASSIFY_EXPECT_DOTS_("/./a", 1u, 2u);
    CLASSIFY_EXPECT_DOTS_("/../a", 1u, 2u);
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
