
/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////////////////////////
 * STLSoft
 */

#include <stlsoft/stlsoft.h>
#ifdef STLSOFT_HAS_COM
# include <comstl/comstl.h>
#endif
#include <platformstl/platformstl.h>
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)
# include <inetstl/inetstl.h>
# include <unixstl/unixstl.h>
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)
# include <inetstl/inetstl.h>
# include <winstl/winstl.h>
#endif

#ifdef HAS_cstring
# include <cstring/cstring.h>
#endif

#ifdef HAS_Diagnosticism
# include <diagnosticism/diagnosticism.h>
# include <diagnosticism/version_string.h>
#endif

#ifdef HAS_shwild
# include <shwild/shwild.h>
#endif

#ifdef HAS_UNIXem
# include <unixem/unixem.h>
#endif

#ifdef HAS_woad
# include <woad/woad.h>
#endif

#ifdef HAS_xTests
# include <xtests/xtests.h>
#endif


/* /////////////////////////////////////////////////////////
 * Third-party
 */


/* /////////////////////////////////////////////////////////
 * standard
 */

#include <stdio.h>


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

#ifdef HAS_woad

# define VERSIONS_CLR_NAME_(stm)                            WOAD_FG_BLUE_FOR(stm)
# define VERSIONS_CLR_VERSION_(stm)                         WOAD_FG_GREEN_FOR(stm)
# define VERSIONS_CLR_HEADING_(stm)                         WOAD_FG_MAGENTA_FOR(stm)
# define VERSIONS_CLR_MACRO_(stm)                           WOAD_FG_CYAN_FOR(stm)
# define VERSIONS_CLR_RESET_(stm)                           WOAD_RESET_FOR(stm)
#else /* ? HAS_woad */

# define VERSIONS_CLR_NAME_(stm)                            ""
# define VERSIONS_CLR_VERSION_(stm)                         ""
# define VERSIONS_CLR_HEADING_(stm)                         ""
# define VERSIONS_CLR_MACRO_(stm)                           ""
# define VERSIONS_CLR_RESET_(stm)                           ""
#endif /* HAS_woad */

#define VER_MAJOR_(t, v)                                    ((t) (((v) >> 24) & 0xFF))
#define VER_MINOR_(t, v)                                    ((t) (((v) >> 16) & 0xFF))
#define VER_PATCH_(t, v)                                    ((t) (((v) >>  8) & 0xFF))
#define VER_RELST_(t, v)                                    ((t) (((v) >>  0) & 0xFF))


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

static
void
print_efferent_dependency_(
    FILE*       stm
,   char const* name
,   char const* macroname
,   unsigned    libver
)
{
#ifdef HAS_Diagnosticism

    char        buffer[101];
    size_t      n;
    int const   r = diagnosticism_calc_version_string(
        buffer
    ,   sizeof(buffer) / sizeof(buffer[0])
    ,   VER_MAJOR_(int, libver)
    ,   VER_MINOR_(int, libver)
    ,   VER_PATCH_(int, libver)
    ,   VER_RELST_(int, libver)
    ,   &n
    );

    if (0 == r)
    {
        buffer[n] = '\0';

        fprintf(
            stm
        ,   "\t"
            "%s%s%s: %s%s%s (%s%s%s = %s0x%08x%s)\n"
        ,   VERSIONS_CLR_NAME_(stm)
        ,   name
        ,   VERSIONS_CLR_RESET_(stm)
        ,   VERSIONS_CLR_VERSION_(stm)
        ,   buffer
        ,   VERSIONS_CLR_RESET_(stm)
        ,   VERSIONS_CLR_MACRO_(stm)
        ,   macroname
        ,   VERSIONS_CLR_RESET_(stm)
        ,   VERSIONS_CLR_VERSION_(stm)
        ,   libver
        ,   VERSIONS_CLR_RESET_(stm)
        );

        return;
    }
#endif /* HAS_Diagnosticism */

    fprintf(
        stm
    ,   "\t"
        "%s%s%s: %sv%u.%u.%u.%u%s (%s%s%s = %s0x%08x%s)\n"
    ,   VERSIONS_CLR_NAME_(stm)
    ,   name
    ,   VERSIONS_CLR_RESET_(stm)
    ,   VERSIONS_CLR_VERSION_(stm)
    ,   VER_MAJOR_(int, libver)
    ,   VER_MINOR_(int, libver)
    ,   VER_PATCH_(int, libver)
    ,   VER_RELST_(int, libver)
    ,   VERSIONS_CLR_RESET_(stm)
    ,   VERSIONS_CLR_MACRO_(stm)
    ,   macroname
    ,   VERSIONS_CLR_RESET_(stm)
    ,   VERSIONS_CLR_VERSION_(stm)
    ,   libver
    ,   VERSIONS_CLR_RESET_(stm)
    );
}

void
print_subproject_(
    FILE*           stm
,   char const*     name
,   char const*     macroName
,   unsigned long   libver
)
{
    fprintf(
        stm
    ,   "\t"
        "%s%s%s"
        ":\n"
        "\n"
    ,   VERSIONS_CLR_NAME_(stm)
    ,   name
    ,   VERSIONS_CLR_RESET_(stm)
    );

    fprintf(
        stm
    ,   "\t\t"
        "%s%s%s = %s%d.%d.%d.%d%s"
        "\n"
    ,   VERSIONS_CLR_NAME_(stm)
    ,   name
    ,   VERSIONS_CLR_RESET_(stm)
    ,   VERSIONS_CLR_VERSION_(stm)
    ,   VER_MAJOR_(int, libver)
    ,   VER_MINOR_(int, libver)
    ,   VER_PATCH_(int, libver)
    ,   VER_RELST_(int, libver)
    ,   VERSIONS_CLR_RESET_(stm)
    );

    fprintf(
        stm
    ,   "\t\t"
        "%s%s%s = %s0x%04x%04x%s\n"
    ,   VERSIONS_CLR_MACRO_(stm)
    ,   macroName
    ,   VERSIONS_CLR_RESET_(stm)
    ,   VERSIONS_CLR_VERSION_(stm)
    ,   (unsigned int)((libver >> 16) & 0xffff)
    ,   (unsigned int)((libver >> 0) & 0xffff)
    ,   VERSIONS_CLR_RESET_(stm)
    );

    fprintf(
        stm
    ,   "\n"
    );
}


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char* argv[])
{
    FILE* const stm = stdout;

    STLSOFT_SUPPRESS_UNUSED(argc);
    STLSOFT_SUPPRESS_UNUSED(argv);

    {

        fprintf(
            stm
        ,   "%s"
            "STLSoft libraries"
            "%s (C):\n"
        ,   VERSIONS_CLR_HEADING_(stm)
        ,   VERSIONS_CLR_RESET_(stm)
        );
        fprintf(stm, "\n");


        /* __STDC__ */
        {

#ifdef __STDC__

            fprintf(
                stm
            ,   "\t"
                "%s__STDC__%s = %s%d%s\n"
            ,   VERSIONS_CLR_MACRO_(stm)
            ,   VERSIONS_CLR_RESET_(stm)
            ,   VERSIONS_CLR_VERSION_(stm)
            ,   __STDC__
            ,   VERSIONS_CLR_RESET_(stm)
            );
            fprintf(stm, "\n");
#endif
        }

        /* compiler strings */
        {
            fprintf(
                stm
            ,   "\t"
                "%sSTLSOFT_COMPILER_LABEL_STRING%s = %s%s%s\n"
            ,   VERSIONS_CLR_MACRO_(stm)
            ,   VERSIONS_CLR_RESET_(stm)
            ,   VERSIONS_CLR_VERSION_(stm)
            ,   STLSOFT_COMPILER_LABEL_STRING
            ,   VERSIONS_CLR_RESET_(stm)
            );

            fprintf(
                stm
            ,   "\t"
                "%sSTLSOFT_COMPILER_VERSION_STRING%s = %s%s%s\n"
            ,   VERSIONS_CLR_MACRO_(stm)
            ,   VERSIONS_CLR_RESET_(stm)
            ,   VERSIONS_CLR_VERSION_(stm)
            ,   STLSOFT_COMPILER_VERSION_STRING
            ,   VERSIONS_CLR_RESET_(stm)
            );
        }
    }


    {
        fprintf(stm, "\n");
        fprintf(
            stm
        ,   "%s"
            "Subprojects"
            "%s:\n"
        ,   VERSIONS_CLR_HEADING_(stm)
        ,   VERSIONS_CLR_RESET_(stm)
        );
        fprintf(stm, "\n");


        /* _STLSOFT_VER */
        print_subproject_(stm, "STLSoft", "_STLSOFT_VER", _STLSOFT_VER);
#ifdef STLSOFT_HAS_COM

        /* _COMSTL_VER */
        print_subproject_(stm, "COMSTL", "_COMSTL_VER", _COMSTL_VER);
#endif
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX) ||\
      defined(PLATFORMSTL_OS_IS_WINDOWS)

        /* _INETSTL_VER */
        print_subproject_(stm, "InetSTL", "_INETSTL_VER", _INETSTL_VER);
#endif

        /* _PLATFORMSTL_VER */
        print_subproject_(stm, "PlatformSTL", "_PLATFORMSTL_VER", _PLATFORMSTL_VER);
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

        /* _UNIXSTL_VER */
        print_subproject_(stm, "UNIXSTL", "_UNIXSTL_VER", _UNIXSTL_VER);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

        /* _WINSTL_VER */
        print_subproject_(stm, "WinSTL", "_WINSTL_VER", _WINSTL_VER);
#endif
    }


    {
        fprintf(
            stm
        ,   "%s"
            "Efferent dependencies"
            "%s:\n"
        ,   VERSIONS_CLR_HEADING_(stm)
        ,   VERSIONS_CLR_RESET_(stm)
        );
        fprintf(stm, "\n");


#ifdef HAS_cstring

        print_efferent_dependency_(stm, "cstring", "CSTRING_VER", CSTRING_VER);
#endif

#ifdef HAS_Diagnosticism

        print_efferent_dependency_(stm, "Diagnosticism", "DIAGNOSTICISM_VER", DIAGNOSTICISM_VER);
#endif


#ifdef HAS_shwild

        print_efferent_dependency_(stm, "shwild", "SHWILD_VER", SHWILD_VER);
#endif

#ifdef HAS_UNIXem

        print_efferent_dependency_(stm, "UNIXem", "UNIXEM_VER", UNIXEM_VER);
#endif

#ifdef HAS_woad

        print_efferent_dependency_(stm, "woad", "WOAD_VER", WOAD_VER);
#endif

#ifdef HAS_xTests

        print_efferent_dependency_(stm, "xTests", "XTESTS_VER", _XTESTS_VER);
#endif
    }


    return 0;
}

/* ///////////////////////////// end of file //////////////////////////// */

