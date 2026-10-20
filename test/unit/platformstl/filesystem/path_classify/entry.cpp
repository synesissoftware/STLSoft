/* /////////////////////////////////////////////////////////////////////////
 * File:    test/unit/platformstl/filesystem/path_classify/entry.cpp
 *
 * Purpose: Unit-tests for PlatformSTL intersecting `path_classify` (R16 /
 *          Remediation-2 portable rows; host-only Windows → Invalid).
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

#include <platformstl/filesystem/path_classify_functions.h>

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
    static void TEST_path_classify_root();
    static void TEST_numDotsDirectoryParts_PORTABLE();
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
    static void TEST_host_only_maps_to_Invalid();
#endif /* PLATFORMSTL_OS_IS_WINDOWS */
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.platformstl.filesystem.path_classify", verbosity))
    {
        XTESTS_RUN_CASE(TEST_matrix_PORTABLE_CORE);
        XTESTS_RUN_CASE(TEST_matrix_PORTABLE_HOME);
        XTESTS_RUN_CASE(TEST_matrix_PORTABLE_FLAGS);
        XTESTS_RUN_CASE(TEST_matrix_BACKSLASH_ORTHOGRAPHY);
        XTESTS_RUN_CASE(TEST_path_classify_root);
        XTESTS_RUN_CASE(TEST_numDotsDirectoryParts_PORTABLE);
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
        XTESTS_RUN_CASE(TEST_host_only_maps_to_Invalid);
#endif /* PLATFORMSTL_OS_IS_WINDOWS */

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
 *
 * expect_rooted / expect_absolute are separate: on Windows SlashRooted is
 * rooted but not absolute (R1 / R2 / R14).
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
        platformstl_C_path_classification_results_m_t   results_;               \
        char const* const                               path_   =   (path);     \
        size_t const                                    cch_    =               \
            (ss_nullptr_k == path_) ? 0u : strlen(path_);                       \
        platformstl_C_path_classification_t const       pc_     =               \
            platformstl_C_path_classify(path_, cch_, (flags), &results_);       \
                                                                                \
        TEST_INT_EQ(int(expected_kind), int(pc_));                              \
        TEST_INT_EQ(                                                            \
            (expect_rooted) ? 1 : 0                                             \
        ,   int(platformstl_C_path_is_rooted(pc_))                              \
        );                                                                      \
        TEST_INT_EQ(                                                            \
            (expect_absolute) ? 1 : 0                                           \
        ,   int(platformstl_C_path_is_absolute(pc_))                            \
        );                                                                      \
        STLSOFT_SUPPRESS_UNUSED(results_);                                      \
    } while (0)

#define CLASSIFY_EXPECT_ROOT_(                                                  \
    path                                                                        \
,   flags                                                                       \
,   expected_kind                                                               \
,   expect_rooted                                                               \
,   expect_absolute                                                             \
,   expected_root_len                                                           \
)                                                                               \
                                                                                \
    do                                                                          \
    {                                                                           \
        stlsoft_C_string_slice_m_t                  root_;                      \
        char const* const                           path_   =   (path);         \
        size_t const                                cch_    =                   \
            (ss_nullptr_k == path_) ? 0u : strlen(path_);                       \
        platformstl_C_path_classification_t const   pc_     =                   \
            platformstl_C_path_classify_root(path_, cch_, (flags), &root_);     \
                                                                                \
        TEST_INT_EQ(int(expected_kind), int(pc_));                              \
        TEST_INT_EQ(                                                            \
            (expect_rooted) ? 1 : 0                                             \
        ,   int(platformstl_C_path_is_rooted(pc_))                              \
        );                                                                      \
        TEST_INT_EQ(                                                            \
            (expect_absolute) ? 1 : 0                                           \
        ,   int(platformstl_C_path_is_absolute(pc_))                            \
        );                                                                      \
        TEST_INT_EQ((expected_root_len), int(root_.len));                       \
    } while (0)

#define CLASSIFY_EXPECT_DOTS_(path, expected_dots, expected_parts)              \
                                                                                \
    do                                                                          \
    {                                                                           \
        platformstl_C_path_classification_results_m_t   results_;               \
        char const* const                               path_   =   (path);     \
        size_t const                                    cch_    =               \
            (ss_nullptr_k == path_) ? 0u : strlen(path_);                       \
        platformstl_C_path_classification_t const       pc_     =               \
            platformstl_C_path_classify(path_, cch_, 0, &results_);             \
                                                                                \
        TEST_INT_GE(int(platformstl_C_PathType_Empty), int(pc_));               \
        TEST_INT_EQ((expected_dots), results_.numDotsDirectoryParts);           \
        TEST_INT_EQ((expected_parts), results_.numDirectoryParts);              \
    } while (0)


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace {

/* Slash-rooted absolute differs by host (R2 side-by-side). */
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
# define ABS_IF_SLASH_ROOTED_                               0
#else /* ? PLATFORMSTL_OS_IS_WINDOWS */
# define ABS_IF_SLASH_ROOTED_                               1
#endif /* PLATFORMSTL_OS_IS_WINDOWS */

static void TEST_matrix_PORTABLE_CORE()
{
    CLASSIFY_EXPECT_KIND_("", 0, platformstl_C_PathType_Empty, 0, 0);
    CLASSIFY_EXPECT_KIND_("file.txt", 0, platformstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_("a/b/c", 0, platformstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_("./file", 0, platformstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_("../file", 0, platformstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_(".", 0, platformstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_("..", 0, platformstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_(
        "/"
    ,   0
    ,   platformstl_C_PathType_SlashRooted
    ,   1
    ,   ABS_IF_SLASH_ROOTED_
    );
    CLASSIFY_EXPECT_KIND_(
        "/a/b"
    ,   0
    ,   platformstl_C_PathType_SlashRooted
    ,   1
    ,   ABS_IF_SLASH_ROOTED_
    );
}

static void TEST_matrix_PORTABLE_HOME()
{
    CLASSIFY_EXPECT_KIND_("~", 0, platformstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_(
        "~"
    ,   PLATFORMSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME
    ,   platformstl_C_PathType_HomeRooted
    ,   1
    ,   1
    );
    CLASSIFY_EXPECT_KIND_(
        "~/a"
    ,   PLATFORMSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME
    ,   platformstl_C_PathType_HomeRooted
    ,   1
    ,   1
    );
}

static void TEST_matrix_PORTABLE_FLAGS()
{
    CLASSIFY_EXPECT_KIND_(
        "a//b"
    ,   0
    ,   platformstl_C_PathType_InvalidSlashRuns
    ,   0
    ,   0
    );
    CLASSIFY_EXPECT_KIND_(
        "a//b"
    ,   PLATFORMSTL_PATH_CLASSIFY_F_IGNORESLASHRUNS
    ,   platformstl_C_PathType_Relative
    ,   0
    ,   0
    );

#if defined(PLATFORMSTL_OS_IS_WINDOWS)

    /* WinSTL: "a:b" is drive-relative (host-only) → portable Invalid. */
    CLASSIFY_EXPECT_KIND_("a:b", 0, platformstl_C_PathType_Invalid, 0, 0);
    CLASSIFY_EXPECT_KIND_("a?b", 0, platformstl_C_PathType_InvalidChars, 0, 0);
    CLASSIFY_EXPECT_KIND_(
        "a?b"
    ,   PLATFORMSTL_PATH_CLASSIFY_F_IGNOREINVALIDCHARS
    ,   platformstl_C_PathType_Relative
    ,   0
    ,   0
    );
#else /* ? PLATFORMSTL_OS_IS_WINDOWS */

# ifdef _WIN32
    /* UNIXem under PlatformSTL Unix arm: Windows invalid-char rules. */
    CLASSIFY_EXPECT_KIND_("a:b", 0, platformstl_C_PathType_InvalidChars, 0, 0);
    CLASSIFY_EXPECT_KIND_("a?b", 0, platformstl_C_PathType_InvalidChars, 0, 0);
# else /* ? _WIN32 */
    /* Native Unix: ':' and '?' are ordinary name characters. */
    CLASSIFY_EXPECT_KIND_("a:b", 0, platformstl_C_PathType_Relative, 0, 0);
    CLASSIFY_EXPECT_KIND_("a?b", 0, platformstl_C_PathType_Relative, 0, 0);
# endif /* _WIN32 */
#endif /* PLATFORMSTL_OS_IS_WINDOWS */
}

static void TEST_matrix_BACKSLASH_ORTHOGRAPHY()
{
#if defined(PLATFORMSTL_OS_IS_WINDOWS)
    /* Windows: '\\' is a separator → SlashRooted, not absolute. */
    CLASSIFY_EXPECT_KIND_(
        "\\a\\b"
    ,   0
    ,   platformstl_C_PathType_SlashRooted
    ,   1
    ,   0
    );
#else /* ? PLATFORMSTL_OS_IS_WINDOWS */

# ifdef _WIN32
    /* UNIXem Unix arm: '\\' separator → SlashRooted; absolute ≡ rooted. */
    CLASSIFY_EXPECT_KIND_(
        "\\a\\b"
    ,   0
    ,   platformstl_C_PathType_SlashRooted
    ,   1
    ,   1
    );
# else /* ? _WIN32 */

    /* Native Unix: '\\' is an ordinary character → relative. */
    CLASSIFY_EXPECT_KIND_("\\a\\b", 0, platformstl_C_PathType_Relative, 0, 0);
# endif /* _WIN32 */
#endif /* PLATFORMSTL_OS_IS_WINDOWS */
}

static void TEST_path_classify_root()
{
    CLASSIFY_EXPECT_ROOT_("", 0, platformstl_C_PathType_Empty, 0, 0, 0);
    CLASSIFY_EXPECT_ROOT_("file.txt", 0, platformstl_C_PathType_Relative, 0, 0, 0);
    CLASSIFY_EXPECT_ROOT_(
        "/"
    ,   0
    ,   platformstl_C_PathType_SlashRooted
    ,   1
    ,   ABS_IF_SLASH_ROOTED_
    ,   0
    );
    CLASSIFY_EXPECT_ROOT_(
        "/a/b"
    ,   0
    ,   platformstl_C_PathType_SlashRooted
    ,   1
    ,   ABS_IF_SLASH_ROOTED_
    ,   0
    );
    CLASSIFY_EXPECT_ROOT_(
        "~"
    ,   PLATFORMSTL_PATH_CLASSIFY_F_RECOGNISETILDEHOME
    ,   platformstl_C_PathType_HomeRooted
    ,   1
    ,   1
    ,   1
    );
}

static void TEST_numDotsDirectoryParts_PORTABLE()
{
    CLASSIFY_EXPECT_DOTS_("", 0u, 0u);
    CLASSIFY_EXPECT_DOTS_("file.txt", 0u, 0u);
    CLASSIFY_EXPECT_DOTS_("a/b/c", 0u, 2u);
    CLASSIFY_EXPECT_DOTS_("./file", 1u, 1u);
    CLASSIFY_EXPECT_DOTS_("a/./b", 1u, 2u);
    CLASSIFY_EXPECT_DOTS_("/a/b", 0u, 2u);
    CLASSIFY_EXPECT_DOTS_("/a/./b", 1u, 3u);
}

#if defined(PLATFORMSTL_OS_IS_WINDOWS)

/* Host-only Windows inputs must not surface Drive* / Unc* through the
 * portable type — they map to Invalid (R2 / R14).
 */

static void TEST_host_only_maps_to_Invalid()
{
    CLASSIFY_EXPECT_KIND_("C:", 0, platformstl_C_PathType_Invalid, 0, 0);
    CLASSIFY_EXPECT_KIND_("C:foo", 0, platformstl_C_PathType_Invalid, 0, 0);
    CLASSIFY_EXPECT_KIND_("C:\\", 0, platformstl_C_PathType_Invalid, 0, 0);
    CLASSIFY_EXPECT_KIND_("C:\\a\\b", 0, platformstl_C_PathType_Invalid, 0, 0);
    CLASSIFY_EXPECT_KIND_("\\\\svr\\share", 0, platformstl_C_PathType_Invalid, 0, 0);
    CLASSIFY_EXPECT_KIND_("\\\\svr\\share\\a", 0, platformstl_C_PathType_Invalid, 0, 0);
    CLASSIFY_EXPECT_KIND_("\\\\svr", 0, platformstl_C_PathType_Invalid, 0, 0);
    CLASSIFY_EXPECT_KIND_("\\\\?\\C:\\a", 0, platformstl_C_PathType_Invalid, 0, 0);
    CLASSIFY_EXPECT_KIND_("\\\\?\\UNC\\h\\s", 0, platformstl_C_PathType_Invalid, 0, 0);
    CLASSIFY_EXPECT_KIND_("\\\\.\\PhysicalDrive0", 0, platformstl_C_PathType_Invalid, 0, 0);
}
#endif /* PLATFORMSTL_OS_IS_WINDOWS */
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */
