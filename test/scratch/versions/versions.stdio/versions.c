
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
            "%s: %s (%s = 0x%08x)\n"
        ,   name
        ,   buffer
        ,   macroname
        ,   libver
        );

        return;
    }
#endif /* HAS_Diagnosticism */

    fprintf(
        stm
    ,   "\t"
        "%s: v%u.%u.%u.%u (%s = 0x%08x)\n"
    ,   name
    ,   (libver >> 24) & 0xff
    ,   (libver >> 16) & 0xff
    ,   (libver >> 8) & 0xff
    ,   (libver >> 0) & 0xff
    ,   macroname
    ,   libver
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
        "%s"
        ":\n"
        "\n"
    ,   name
    );

    fprintf(
        stm
    ,   "\t\t"
        "%s = %d.%d.%d.%d"
        "\n"
    ,   name
    ,   (int)((libver >> 24) & 0xff)
    ,   (int)((libver >> 16) & 0xff)
    ,   (int)((libver >> 8) & 0xff)
    ,   (int)((libver >> 0) & 0xff)
    );

    fprintf(
        stm
    ,   "\t\t"
        "%s = 0x%04x%04x\n"
    ,   macroName
    ,   (unsigned int)((libver >> 16) & 0xffff)
    ,   (unsigned int)((libver >> 0) & 0xffff)
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
    fprintf(stdout, "STLSoft libraries:\n");


    /* __STDC__ */
    {

#ifdef __STDC__

        fprintf(
            stdout
        ,   "\t"
            "__STDC__ = %d\n"
        ,   __STDC__
        );
        fprintf(stdout, "\n");
#endif
    }

    {
        fprintf(
            stdout
        ,   "\t"
            "STLSOFT_COMPILER_LABEL_STRING = %s\n"
        ,   STLSOFT_COMPILER_LABEL_STRING
        );

        fprintf(
            stdout
        ,   "\t"
            "STLSOFT_COMPILER_VERSION_STRING = %s\n"
        ,   STLSOFT_COMPILER_VERSION_STRING
        );
    }


    {
        fprintf(stdout, "\n");
        fprintf(stdout, "Subprojects:\n");
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
        fprintf(stdout, "Efferent dependencies:\n");
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

