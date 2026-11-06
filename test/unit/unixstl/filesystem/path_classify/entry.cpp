/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/unixstl/filesystem/path_classify/entry.cpp
 *
 * Purpose: Unit-tests for `unixstl_C_path_classify` (Remediation-4 matrix
 *          rows: portable core, dots/parts, flags; R13 root / absolute).
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

    static void TEST_matrix_PORTABLE_CORE();
    static void TEST_matrix_PORTABLE_HOME();
    static void TEST_matrix_PORTABLE_FLAGS();
    static void TEST_matrix_BACKSLASH_ORTHOGRAPHY();
    static void TEST_path_classify_root_AND_ABSOLUTE();
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
        XTESTS_RUN_CASE(TEST_matrix_PORTABLE_CORE);
        XTESTS_RUN_CASE(TEST_matrix_PORTABLE_HOME);
        XTESTS_RUN_CASE(TEST_matrix_PORTABLE_FLAGS);
        XTESTS_RUN_CASE(TEST_matrix_BACKSLASH_ORTHOGRAPHY);
        XTESTS_RUN_CASE(TEST_path_classify_root_AND_ABSOLUTE);
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
 *
 * Expand at the call site so assertion failures keep path/line context
 * (see test-standards → Assertion Failure Location).
 */

#define CLASSIFY_EXPECT_KIND_(                                                  \
    path                                                                        \
,   flags                                                                       \
,   expected_kind                                                               \
,   expect_rooted                                                               \
)                                                                               \
                                                                                \
    do                                                                          \
    {                                                                           \
        unixstl_C_path_classification_results_m_t   results_;                   \
        char const* const                           path_   =   (path);         \
        size_t const                                cch_    =                   \
            (ss_nullptr_k == path_) ? 0u : strlen(path_);                       \
        unixstl_C_path_classification_t const       pc_     =                   \
            unixstl_C_path_classify(path_, cch_, (flags), &results_);           \
                                                                                \
        TEST_INT_EQ(int(expected_kind), int(pc_));                              \
        TEST_INT_EQ(                                                            \
            (expect_rooted) ? 1 : 0                                             \
        ,   int(unixstl_C_path_is_rooted(pc_))                                  \
        );                                                                      \
        TEST_INT_EQ(                                                            \
            (expect_rooted) ? 1 : 0                                             \
        ,   int(unixstl_C_path_is_absolute(pc_))                                \
        );                                                                      \
        STLSOFT_SUPPRESS_UNUSED(results_);                                      \
    } while (0)

#define CLASSIFY_EXPECT_ROOT_(                                                  \
    path                                                                        \
,   flags                                                                       \
,   expected_kind                                                               \
,   expect_rooted                                                               \
,   expected_root_len                                                           \
)                                                                               \
                                                                                \
    do                                                                          \
    {                                                                           \
        stlsoft_C_string_slice_m_t              root_;                          \
        char const* const                       path_   =   (path);             \
        size_t const                            cch_    =                       \
            (ss_nullptr_k == path_) ? 0u : strlen(path_);                       \
        unixstl_C_path_classification_t const   pc_     =                       \
            unixstl_C_path_classify_root(path_, cch_, (flags), &root_);         \
                                                                                \
        TEST_INT_EQ(int(expected_kind), int(pc_));                              \
        TEST_INT_EQ(                                                            \
            (expect_rooted) ? 1 : 0                                             \
        ,   int(unixstl_C_path_is_rooted(pc_))                                  \
        );                                                                      \
        TEST_INT_EQ(                                                            \
            (expect_rooted) ? 1 : 0                                             \
        ,   int(unixstl_C_path_is_absolute(pc_))                                \
        );                                                                      \
        TEST_INT_EQ((expected_root_len), int(root_.len));                       \
    } while (0)

#define CLASSIFY_EXPECT_DOTS_(path, expected_dots, expected_parts)              \
                                                                                \
    do                                                                          \
    {                                                                           \
        unixstl_C_path_classification_results_m_t   results_;                   \
        char const* const                           path_   =   (path);         \
        size_t const                                cch_    =                   \
            (ss_nullptr_k == path_) ? 0u : strlen(path_);                       \
        unixstl_C_path_classification_t const       pc_     =                   \
            unixstl_C_path_classify(path_, cch_, 0, &results_);                 \
                                                                                \
        TEST_INT_GE(int(unixstl_C_PathType_Empty), int(pc_));                   \
        TEST_INT_EQ((expected_dots), results_.numDotsDirectoryParts);           \
        TEST_INT_EQ((expected_parts), results_.numDirectoryParts);              \
    } while (0)


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

/* Matrix section A — portable core (Unix: absolute ≡ rooted via is_rooted). */

static void TEST_matrix_PORTABLE_CORE()
{
    CLASSIFY_EXPECT_KIND_("", 0, unixstl_C_PathType_Empty, 0);
    CLASSIFY_EXPECT_KIND_("file.txt", 0, unixstl_C_PathType_Relative, 0);
    CLASSIFY_EXPECT_KIND_("a/b/c", 0, unixstl_C_PathType_Relative, 0);
    CLASSIFY_EXPECT_KIND_("./file", 0, unixstl_C_PathType_Relative, 0);
    CLASSIFY_EXPECT_KIND_("../file", 0, unixstl_C_PathType_Relative, 0);
    CLASSIFY_EXPECT_KIND_(".", 0, unixstl_C_PathType_Relative, 0);
    CLASSIFY_EXPECT_KIND_("..", 0, unixstl_C_PathType_Relative, 0);
    CLASSIFY_EXPECT_KIND_("/", 0, unixstl_C_PathType_SlashRooted, 1);
    CLASSIFY_EXPECT_KIND_("/a/b", 0, unixstl_C_PathType_SlashRooted, 1);
}

static void TEST_matrix_PORTABLE_HOME()
{
    CLASSIFY_EXPECT_KIND_("~", 0, unixstl_C_PathType_Relative, 0);
    CLASSIFY_EXPECT_KIND_(
        "~"
    ,   UNIXSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME
    ,   unixstl_C_PathType_HomeRooted
    ,   1
    );
    CLASSIFY_EXPECT_KIND_(
        "~/a"
    ,   UNIXSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME
    ,   unixstl_C_PathType_HomeRooted
    ,   1
    );
}

static void TEST_matrix_PORTABLE_FLAGS()
{
    CLASSIFY_EXPECT_KIND_(
        "a//b"
    ,   0
    ,   unixstl_C_PathType_InvalidSlashRuns
    ,   0
    );
    CLASSIFY_EXPECT_KIND_(
        "a//b"
    ,   UNIXSTL_PATH_CLASSIFY_F_IGNORESLASHRUNS
    ,   unixstl_C_PathType_Relative
    ,   0
    );

#ifdef _WIN32
    /* UNIXem: Windows invalid-char rules (Bite 5). */
    CLASSIFY_EXPECT_KIND_("a:b", 0, unixstl_C_PathType_InvalidChars, 0);
    CLASSIFY_EXPECT_KIND_("a?b", 0, unixstl_C_PathType_InvalidChars, 0);
    CLASSIFY_EXPECT_KIND_(
        "a?b"
    ,   UNIXSTL_PATH_CLASSIFY_F_IGNOREINVALIDCHARS
    ,   unixstl_C_PathType_Relative
    ,   0
    );
#else /* ? _WIN32 */
    /* Native Unix: ':' and '?' are ordinary name characters. */
    CLASSIFY_EXPECT_KIND_("a:b", 0, unixstl_C_PathType_Relative, 0);
    CLASSIFY_EXPECT_KIND_("a?b", 0, unixstl_C_PathType_Relative, 0);
#endif /* _WIN32 */
}

static void TEST_matrix_BACKSLASH_ORTHOGRAPHY()
{
#ifdef _WIN32
    /* UNIXem: '\\' is a separator → slash-rooted. */
    CLASSIFY_EXPECT_KIND_("\\a\\b", 0, unixstl_C_PathType_SlashRooted, 1);
#else /* ? _WIN32 */
    /* Native Unix: '\\' is an ordinary character → relative. */
    CLASSIFY_EXPECT_KIND_("\\a\\b", 0, unixstl_C_PathType_Relative, 0);
#endif /* _WIN32 */
}

/* R13 — public path_classify_root; absolute(pc) ≡ rooted(pc). */

static void TEST_path_classify_root_AND_ABSOLUTE()
{
    CLASSIFY_EXPECT_ROOT_("", 0, unixstl_C_PathType_Empty, 0, 0);
    CLASSIFY_EXPECT_ROOT_("file.txt", 0, unixstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_ROOT_("/", 0, unixstl_C_PathType_SlashRooted, 1, 0);
    CLASSIFY_EXPECT_ROOT_("/a/b", 0, unixstl_C_PathType_SlashRooted, 1, 0);
    CLASSIFY_EXPECT_ROOT_("~", 0, unixstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_ROOT_(
        "~"
    ,   UNIXSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME
    ,   unixstl_C_PathType_HomeRooted
    ,   1
    ,   1
    );
    CLASSIFY_EXPECT_ROOT_(
        "~/a"
    ,   UNIXSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME
    ,   unixstl_C_PathType_HomeRooted
    ,   1
    ,   1
    );

#ifdef _WIN32
    CLASSIFY_EXPECT_ROOT_("\\a\\b", 0, unixstl_C_PathType_SlashRooted, 1, 0);
#else /* ? _WIN32 */
    CLASSIFY_EXPECT_ROOT_("\\a\\b", 0, unixstl_C_PathType_Relative, 0, 0);
#endif /* _WIN32 */
}

/* Matrix section B — dots / parts (Bite 3). */

static void TEST_numDotsDirectoryParts_EMPTY_AND_ENTRY_ONLY()
{
    CLASSIFY_EXPECT_DOTS_("", 0u, 0u);
    CLASSIFY_EXPECT_DOTS_("file.txt", 0u, 0u);
    CLASSIFY_EXPECT_DOTS_("a/b/c", 0u, 2u);
}

static void TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_ENTRY()
{
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
