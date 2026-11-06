
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

#include <stdio.h>


#ifdef HAS_woad

# define VERSIONS_CLR_NAME_                                 WOAD_FG_BLUE_FOR(stdout)
# define VERSIONS_CLR_VERSION_                              WOAD_FG_GREEN_FOR(stdout)
# define VERSIONS_CLR_HEADING_                              WOAD_FG_MAGENTA_FOR(stdout)
# define VERSIONS_CLR_MACRO_                                WOAD_FG_CYAN_FOR(stdout)
# define VERSIONS_CLR_RESET_                                WOAD_RESET_FOR(stdout)
#else /* ? HAS_woad */

# define VERSIONS_CLR_NAME_                                 ""
# define VERSIONS_CLR_VERSION_                              ""
# define VERSIONS_CLR_HEADING_                              ""
# define VERSIONS_CLR_MACRO_                                ""
# define VERSIONS_CLR_RESET_                                ""
#endif /* HAS_woad */


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
    ,   (int)((libver >> 24) & 0xff)
    ,   (int)((libver >> 16) & 0xff)
    ,   (int)((libver >> 8) & 0xff)
    ,   (int)((libver >> 0) & 0xff)
    ,   &n
    );

    if (0 == r)
    {
        buffer[n] = '\0';

        fprintf(
            stm
        ,   "\t"
            "%s%s%s: %s%s%s (%s%s%s = %s0x%08x%s)\n"
        ,   VERSIONS_CLR_NAME_
        ,   name
        ,   VERSIONS_CLR_RESET_
        ,   VERSIONS_CLR_VERSION_
        ,   buffer
        ,   VERSIONS_CLR_RESET_
        ,   VERSIONS_CLR_MACRO_
        ,   macroname
        ,   VERSIONS_CLR_RESET_
        ,   VERSIONS_CLR_VERSION_
        ,   libver
        ,   VERSIONS_CLR_RESET_
        );

        return;
    }
#endif /* HAS_Diagnosticism */

    fprintf(
        stm
    ,   "\t"
        "%s%s%s: %sv%u.%u.%u.%u%s (%s%s%s = %s0x%08x%s)\n"
    ,   VERSIONS_CLR_NAME_
    ,   name
    ,   VERSIONS_CLR_RESET_
    ,   VERSIONS_CLR_VERSION_
    ,   (libver >> 24) & 0xff
    ,   (libver >> 16) & 0xff
    ,   (libver >> 8) & 0xff
    ,   (libver >> 0) & 0xff
    ,   VERSIONS_CLR_RESET_
    ,   VERSIONS_CLR_MACRO_
    ,   macroname
    ,   VERSIONS_CLR_RESET_
    ,   VERSIONS_CLR_VERSION_
    ,   libver
    ,   VERSIONS_CLR_RESET_
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
    ,   VERSIONS_CLR_NAME_
    ,   name
    ,   VERSIONS_CLR_RESET_
    );

    fprintf(
        stm
    ,   "\t\t"
        "%s%s%s = %s%d.%d.%d.%d%s"
        "\n"
    ,   VERSIONS_CLR_NAME_
    ,   name
    ,   VERSIONS_CLR_RESET_
    ,   VERSIONS_CLR_VERSION_
    ,   (int)((libver >> 24) & 0xff)
    ,   (int)((libver >> 16) & 0xff)
    ,   (int)((libver >> 8) & 0xff)
    ,   (int)((libver >> 0) & 0xff)
    ,   VERSIONS_CLR_RESET_
    );

    fprintf(
        stm
    ,   "\t\t"
        "%s%s%s = %s0x%04x%04x%s\n"
    ,   VERSIONS_CLR_MACRO_
    ,   macroName
    ,   VERSIONS_CLR_RESET_
    ,   VERSIONS_CLR_VERSION_
    ,   (unsigned int)((libver >> 16) & 0xffff)
    ,   (unsigned int)((libver >> 0) & 0xffff)
    ,   VERSIONS_CLR_RESET_
    );

    fprintf(
        stm
    ,   "\n"
    );
}


int main(int argc, char* argv[])
{
    STLSOFT_SUPPRESS_UNUSED(argc);
    STLSOFT_SUPPRESS_UNUSED(argv);

    fprintf(stdout, "\n");
    fprintf(
        stdout
    ,   "%s"
        "STLSoft libraries"
        "%s:\n"
    ,   VERSIONS_CLR_HEADING_
    ,   VERSIONS_CLR_RESET_
    );


    /* __STDC__ */
    {

#ifdef __STDC__

        fprintf(
            stdout
        ,   "\t"
            "%s__STDC__%s = %s%d%s\n"
        ,   VERSIONS_CLR_MACRO_
        ,   VERSIONS_CLR_RESET_
        ,   VERSIONS_CLR_VERSION_
        ,   __STDC__
        ,   VERSIONS_CLR_RESET_
        );
        fprintf(stdout, "\n");
#endif
    }

    {
        fprintf(
            stdout
        ,   "\t"
            "%sSTLSOFT_COMPILER_LABEL_STRING%s = %s%s%s\n"
        ,   VERSIONS_CLR_MACRO_
        ,   VERSIONS_CLR_RESET_
        ,   VERSIONS_CLR_VERSION_
        ,   STLSOFT_COMPILER_LABEL_STRING
        ,   VERSIONS_CLR_RESET_
        );

        fprintf(
            stdout
        ,   "\t"
            "%sSTLSOFT_COMPILER_VERSION_STRING%s = %s%s%s\n"
        ,   VERSIONS_CLR_MACRO_
        ,   VERSIONS_CLR_RESET_
        ,   VERSIONS_CLR_VERSION_
        ,   STLSOFT_COMPILER_VERSION_STRING
        ,   VERSIONS_CLR_RESET_
        );
    }


    {
        fprintf(stdout, "\n");
        fprintf(
            stdout
        ,   "%s"
            "Subprojects"
            "%s:\n"
        ,   VERSIONS_CLR_HEADING_
        ,   VERSIONS_CLR_RESET_
        );
        fprintf(stdout, "\n");


        /* _STLSOFT_VER */
        print_subproject_(stdout, "STLSoft", "_STLSOFT_VER", _STLSOFT_VER);


#ifdef STLSOFT_HAS_COM

        /* _COMSTL_VER */
        print_subproject_(stdout, "COMSTL", "_COMSTL_VER", _COMSTL_VER);
#endif


        /* _PLATFORMSTL_VER */
        print_subproject_(stdout, "PlatformSTL", "_PLATFORMSTL_VER", _PLATFORMSTL_VER);


#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX) || \
      defined(PLATFORMSTL_OS_IS_WINDOWS)

        /* _INETSTL_VER */
        print_subproject_(stdout, "InetSTL", "_INETSTL_VER", _INETSTL_VER);
#endif


#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

        /* _UNIXSTL_VER */
        print_subproject_(stdout, "UNIXSTL", "_UNIXSTL_VER", _UNIXSTL_VER);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

        /* _WINSTL_VER */
        print_subproject_(stdout, "WinSTL", "_WINSTL_VER", _WINSTL_VER);
#endif
    }


    {
        fprintf(
            stdout
        ,   "%s"
            "Efferent dependencies"
            "%s:\n"
        ,   VERSIONS_CLR_HEADING_
        ,   VERSIONS_CLR_RESET_
        );
        fprintf(stdout, "\n");


#ifdef HAS_cstring

        print_efferent_dependency_(stdout, "cstring", "CSTRING_VER", CSTRING_VER);
#endif

#ifdef HAS_Diagnosticism

        print_efferent_dependency_(stdout, "Diagnosticism", "DIAGNOSTICISM_VER", DIAGNOSTICISM_VER);
#endif


#ifdef HAS_shwild

        print_efferent_dependency_(stdout, "shwild", "SHWILD_VER", SHWILD_VER);
#endif

#ifdef HAS_UNIXem

        print_efferent_dependency_(stdout, "UNIXem", "UNIXEM_VER", UNIXEM_VER);
#endif

#ifdef HAS_woad

        print_efferent_dependency_(stdout, "woad", "WOAD_VER", WOAD_VER);
#endif

#ifdef HAS_xTests

        print_efferent_dependency_(stdout, "xTests", "XTESTS_VER", _XTESTS_VER);
#endif
    }

    return 0;
}

