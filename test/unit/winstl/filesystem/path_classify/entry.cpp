/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/winstl/filesystem/path_classify/entry.cpp
 *
 * Purpose: Unit-tests for `winstl_C_path_classify` (Remediation-4 matrix
 *          rows: portable core, dots/parts, flags, Windows host-only).
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

#include <winstl/filesystem/path_classify_functions.h>

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
#include <wchar.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace {

    static void TEST_matrix_PORTABLE_CORE();
    static void TEST_matrix_PORTABLE_HOME();
    static void TEST_matrix_PORTABLE_FLAGS();
    static void TEST_matrix_PORTABLE_CORE_wchar();
    static void TEST_matrix_WINDOWS_DRIVE();
    static void TEST_matrix_WINDOWS_UNC();
    static void TEST_matrix_WINDOWS_SLASH_ROOTED();
    static void TEST_numDotsDirectoryParts_EMPTY_AND_ENTRY_ONLY();
    static void TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_ENTRY();
    static void TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_DIRECTORY();
    static void TEST_numDotsDirectoryParts_MIXED_DIRECTORY_PARTS();
    static void TEST_numDotsDirectoryParts_NON_EXACT_DOT_NAMES();
    static void TEST_numDotsDirectoryParts_BACKSLASH_SEPARATORS();
    static void TEST_numDotsDirectoryParts_DRIVE_ROOTED();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.winstl.filesystem.path_classify", verbosity))
    {
        XTESTS_RUN_CASE(TEST_matrix_PORTABLE_CORE);
        XTESTS_RUN_CASE(TEST_matrix_PORTABLE_HOME);
        XTESTS_RUN_CASE(TEST_matrix_PORTABLE_FLAGS);
        XTESTS_RUN_CASE(TEST_matrix_PORTABLE_CORE_wchar);
        XTESTS_RUN_CASE(TEST_matrix_WINDOWS_DRIVE);
        XTESTS_RUN_CASE(TEST_matrix_WINDOWS_UNC);
        XTESTS_RUN_CASE(TEST_matrix_WINDOWS_SLASH_ROOTED);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_EMPTY_AND_ENTRY_ONLY);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_ENTRY);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_DOT_AND_DOTDOT_AS_DIRECTORY);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_MIXED_DIRECTORY_PARTS);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_NON_EXACT_DOT_NAMES);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_BACKSLASH_SEPARATORS);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_DRIVE_ROOTED);

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
,   expect_absolute                                                             \
)                                                                               \
                                                                                \
    do                                                                          \
    {                                                                           \
        winstl_C_path_classification_results_m_t    results_;                   \
        char const* const                           path_   =   (path);         \
        size_t const                                cch_    =                   \
            (ss_nullptr_k == path_) ? 0u : strlen(path_);                       \
        winstl_C_path_classification_t const        pc_     =                   \
            winstl_C_path_classify(path_, cch_, (flags), &results_);            \
                                                                                \
        TEST_INT_EQ(int(expected_kind), int(pc_));                              \
        TEST_INT_EQ(                                                            \
            (expect_rooted) ? 1 : 0                                             \
        ,   int(winstl_C_path_is_rooted(pc_))                                   \
        );                                                                      \
        TEST_INT_EQ(                                                            \
            (expect_absolute) ? 1 : 0                                           \
        ,   int(winstl_C_path_is_absolute(pc_))                                 \
        );                                                                      \
        STLSOFT_SUPPRESS_UNUSED(results_);                                      \
    } while (0)

#define CLASSIFY_EXPECT_KIND_W_(                                                \
    path                                                                        \
,   flags                                                                       \
,   expected_kind                                                               \
,   expect_rooted                                                               \
,   expect_absolute                                                             \
)                                                                               \
                                                                                \
    do                                                                          \
    {                                                                           \
        winstl_C_path_classification_results_w_t    results_;                   \
        wchar_t const* const                        path_   =   (path);         \
        size_t const                                cch_    =                   \
            (ss_nullptr_k == path_) ? 0u : wcslen(path_);                       \
        winstl_C_path_classification_t const        pc_     =                   \
            winstl_C_path_classify(path_, cch_, (flags), &results_);            \
                                                                                \
        TEST_INT_EQ(int(expected_kind), int(pc_));                              \
        TEST_INT_EQ(                                                            \
            (expect_rooted) ? 1 : 0                                             \
        ,   int(winstl_C_path_is_rooted(pc_))                                   \
        );                                                                      \
        TEST_INT_EQ(                                                            \
            (expect_absolute) ? 1 : 0                                           \
        ,   int(winstl_C_path_is_absolute(pc_))                                 \
        );                                                                      \
        STLSOFT_SUPPRESS_UNUSED(results_);                                      \
    } while (0)

#define CLASSIFY_EXPECT_DOTS_(path, expected_dots, expected_parts)              \
                                                                                \
    do                                                                          \
    {                                                                           \
        winstl_C_path_classification_results_m_t    results_;                   \
        char const* const                           path_   =   (path);         \
        size_t const                                cch_    =                   \
            (ss_nullptr_k == path_) ? 0u : strlen(path_);                       \
        winstl_C_path_classification_t const        pc_     =                   \
            winstl_C_path_classify(path_, cch_, 0, &results_);                  \
                                                                                \
        TEST_INT_GE(int(winstl_C_PathType_Empty), int(pc_));                    \
        TEST_INT_EQ((expected_dots), results_.numDotsDirectoryParts);           \
        TEST_INT_EQ((expected_parts), results_.numDirectoryParts);              \
    } while (0)


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

/* Matrix section A — portable core (Win: slash-rooted ≠ absolute). */

static void TEST_matrix_PORTABLE_CORE()
{
    CLASSIFY_EXPECT_KIND_("", 0, winstl_C_PathType_Empty, 0, 0);
    CLASSIFY_EXPECT_KIND_("file.txt", 0, winstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_("a/b/c", 0, winstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_("./file", 0, winstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_("../file", 0, winstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_(".", 0, winstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_("..", 0, winstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_("/", 0, winstl_C_PathType_SlashRooted, 1, 0);
    CLASSIFY_EXPECT_KIND_("/a/b", 0, winstl_C_PathType_SlashRooted, 1, 0);
    CLASSIFY_EXPECT_KIND_("\\a\\b", 0, winstl_C_PathType_SlashRooted, 1, 0);
}

static void TEST_matrix_PORTABLE_HOME()
{
    CLASSIFY_EXPECT_KIND_("~", 0, winstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_(
        "~"
    ,   WINSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME
    ,   winstl_C_PathType_HomeRooted
    ,   1
    ,   1
    );
    CLASSIFY_EXPECT_KIND_(
        "~/a"
    ,   WINSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME
    ,   winstl_C_PathType_HomeRooted
    ,   1
    ,   1
    );
}

static void TEST_matrix_PORTABLE_FLAGS()
{
    CLASSIFY_EXPECT_KIND_(
        "a//b"
    ,   0
    ,   winstl_C_PathType_InvalidSlashRuns
    ,   0
    ,   0
    );
    CLASSIFY_EXPECT_KIND_(
        "a//b"
    ,   WINSTL_PATH_CLASSIFY_F_IGNORESLASHRUNS
    ,   winstl_C_PathType_Relative
    ,   0
    ,   0
    );
    /* "a:b" is DriveLetterRelative (letter + ':' + non-separator). */
    CLASSIFY_EXPECT_KIND_("a:b", 0, winstl_C_PathType_DriveLetterRelative, 0, 0);
    /* Colon mid-component (not X: form) → InvalidChars. */
    CLASSIFY_EXPECT_KIND_("ab:c", 0, winstl_C_PathType_InvalidChars, 0, 0);
    CLASSIFY_EXPECT_KIND_("a?b", 0, winstl_C_PathType_InvalidChars, 0, 0);
    CLASSIFY_EXPECT_KIND_(
        "a?b"
    ,   WINSTL_PATH_CLASSIFY_F_IGNOREINVALIDCHARS
    ,   winstl_C_PathType_Relative
    ,   0
    ,   0
    );
}

static void TEST_matrix_PORTABLE_CORE_wchar()
{
    CLASSIFY_EXPECT_KIND_W_(L"", 0, winstl_C_PathType_Empty, 0, 0);
    CLASSIFY_EXPECT_KIND_W_(L"file.txt", 0, winstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_W_(L"/a/b", 0, winstl_C_PathType_SlashRooted, 1, 0);
    CLASSIFY_EXPECT_KIND_W_(L"\\foo", 0, winstl_C_PathType_SlashRooted, 1, 0);
}

/* Matrix section D — Windows host-only. */

static void TEST_matrix_WINDOWS_DRIVE()
{
    CLASSIFY_EXPECT_KIND_("C:foo", 0, winstl_C_PathType_DriveLetterRelative, 0, 0);
    CLASSIFY_EXPECT_KIND_("C:", 0, winstl_C_PathType_DriveLetterRelative, 0, 0);
    CLASSIFY_EXPECT_KIND_("C:\\", 0, winstl_C_PathType_DriveLetterRooted, 1, 1);
    CLASSIFY_EXPECT_KIND_("C:\\a\\b", 0, winstl_C_PathType_DriveLetterRooted, 1, 1);
    CLASSIFY_EXPECT_KIND_("C:/a/./b", 0, winstl_C_PathType_DriveLetterRooted, 1, 1);
}

static void TEST_matrix_WINDOWS_UNC()
{
    /* W-unc-share: complete root, no trailing separator (R7 / R1). */
    CLASSIFY_EXPECT_KIND_("\\\\svr\\share", 0, winstl_C_PathType_UncRooted, 1, 1);

    /* W-unc-share-sep / W-unc-child: trailing sep or further path. */
    CLASSIFY_EXPECT_KIND_("\\\\svr\\share\\", 0, winstl_C_PathType_UncRooted, 1, 1);
    CLASSIFY_EXPECT_KIND_("\\\\svr\\share\\a", 0, winstl_C_PathType_UncRooted, 1, 1);

    /* W-unc-host: incomplete (no share). */
    CLASSIFY_EXPECT_KIND_("\\\\svr", 0, winstl_C_PathType_UncIncomplete, 0, 0);

    /* Empty share after host separator. */
    CLASSIFY_EXPECT_KIND_("\\\\svr\\", 0, winstl_C_PathType_UncIncomplete, 0, 0);

    /* Empty host (extra slash after UNC prefix). */
    CLASSIFY_EXPECT_KIND_("\\\\\\share", 0, winstl_C_PathType_UncIncomplete, 0, 0);

    /* Invalid character in UNC host. */
    CLASSIFY_EXPECT_KIND_("\\\\sv|r\\share", 0, winstl_C_PathType_InvalidChars, 0, 0);

    /* Invalid character in UNC share. */
    CLASSIFY_EXPECT_KIND_("\\\\svr\\sha?re", 0, winstl_C_PathType_InvalidChars, 0, 0);

    /* W-unc-only: too short for UNC parse → Invalid. */
    CLASSIFY_EXPECT_KIND_("\\\\", 0, winstl_C_PathType_Invalid, 0, 0);
}

static void TEST_matrix_WINDOWS_SLASH_ROOTED()
{
    CLASSIFY_EXPECT_KIND_("\\foo", 0, winstl_C_PathType_SlashRooted, 1, 0);
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

static void TEST_numDotsDirectoryParts_BACKSLASH_SEPARATORS()
{
    CLASSIFY_EXPECT_DOTS_("a\\.\\b", 1u, 2u);
    CLASSIFY_EXPECT_DOTS_("a\\..\\b", 1u, 2u);
    CLASSIFY_EXPECT_DOTS_(".\\..\\.\\file", 3u, 3u);
    CLASSIFY_EXPECT_DOTS_("foo\\.", 0u, 1u);
}

static void TEST_numDotsDirectoryParts_DRIVE_ROOTED()
{
    CLASSIFY_EXPECT_DOTS_("C:\\a\\b", 0u, 2u);
    CLASSIFY_EXPECT_DOTS_("C:\\a\\.\\b", 1u, 3u);
    CLASSIFY_EXPECT_DOTS_("C:/a/./b", 1u, 3u);
    CLASSIFY_EXPECT_DOTS_("C:a\\.\\b", 1u, 2u);
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
