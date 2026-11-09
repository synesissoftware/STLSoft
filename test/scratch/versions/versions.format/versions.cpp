
/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stlsoft/stlsoft.h>
#ifdef STLSOFT_HAS_ACE
# include <acestl/acestl.hpp>
#endif
#ifdef STLSOFT_HAS_ATL
# include <atlstl/atlstl.hpp>
#endif
#ifdef STLSOFT_HAS_COM
# include <comstl/comstl.h>
#endif
#ifdef STLSOFT_HAS_MFC
# include <mfcstl/mfcstl.hpp>
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


/* /////////////////////////////////////////////////////////
 * Third-party
 */

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
# include <woad/iostreams.hpp>
#endif

#ifdef HAS_xTests
# include <xtests/xtests.h>
#endif


/* /////////////////////////////////////////////////////////
 * standard
 */

#include <version> // required before doing feature tests

#include <cstdint>
#include <format>
#ifdef __cpp_lib_print
# include <print>
#endif
#include <iostream>
#include <string>


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

#ifdef HAS_woad

# define VERSIONS_CLR_NAME_(stm)                            WOAD_FG_BLUE_FOR(stm)
# define VERSIONS_CLR_VERSION_(stm)                         WOAD_FG_GREEN_FOR(stm)
# define VERSIONS_CLR_HEADING_(stm)                         WOAD_FG_MAGENTA_FOR(stm)
# define VERSIONS_CLR_MACRO_(stm)                           WOAD_FG_CYAN_FOR(stm)
# define VERSIONS_CLR_FRAMEWORK_(stm)                       WOAD_FG_YELLOW_FOR(stm)
# define VERSIONS_CLR_RESET_(stm)                           WOAD_RESET_FOR(stm)
#else /* ? HAS_woad */

# define VERSIONS_CLR_NAME_(stm)                            ""
# define VERSIONS_CLR_VERSION_(stm)                         ""
# define VERSIONS_CLR_HEADING_(stm)                         ""
# define VERSIONS_CLR_MACRO_(stm)                           ""
# define VERSIONS_CLR_FRAMEWORK_(stm)                       ""
# define VERSIONS_CLR_RESET_(stm)                           ""
#endif /* HAS_woad */

#define VER_MAJOR_(t, v)                                    ((t) (((v) >> 24) & 0xFF))
#define VER_MINOR_(t, v)                                    ((t) (((v) >> 16) & 0xFF))
#define VER_PATCH_(t, v)                                    ((t) (((v) >>  8) & 0xFF))
#define VER_RELST_(t, v)                                    ((t) (((v) >>  0) & 0xFF))


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

namespace {

void
print_version(
    std::ostream&   stm
,   char const*     name
,   char const*     macro_name
,   std::uint32_t   ver
)
{
    auto clr_macro      =   VERSIONS_CLR_MACRO_(stm);
    auto clr_name       =   VERSIONS_CLR_NAME_(stm);
    auto clr_reset      =   VERSIONS_CLR_RESET_(stm);
    auto clr_version    =   VERSIONS_CLR_VERSION_(stm);

#ifdef __cpp_lib_print

    std::println(
        "\t{8}{0}{7}: {9}v{1}.{2}.{3}.{4}{7} ({10}{5}{7} = {9}0x{6:08x}{7})"
    ,   name
    ,   VER_MAJOR_(int, ver)
    ,   VER_MINOR_(int, ver)
    ,   VER_PATCH_(int, ver)
    ,   VER_RELST_(int, ver)
    ,   macro_name
    ,   ver
    ,   clr_reset
    ,   clr_name
    ,   clr_version
    ,   clr_macro
    );

    STLSOFT_SUPPRESS_UNUSED(stm);
#else

    stm
        << std::format(
            "\t{8}{0}{7}: {9}v{1}.{2}.{3}.{4}{7} ({10}{5}{7} = {9}0x{6:08x}{7})"
        ,   name
        ,   VER_MAJOR_(int, ver)
        ,   VER_MINOR_(int, ver)
        ,   VER_PATCH_(int, ver)
        ,   VER_RELST_(int, ver)
        ,   macro_name
        ,   ver
        ,   clr_reset
        ,   clr_name
        ,   clr_version
        ,   clr_macro
        )
        << std::endl
        ;
#endif
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int /* argc */, char* /* argv */[])
{
    std::ostream &stm = std::cout;

    {
        auto clr_framework  =   VERSIONS_CLR_FRAMEWORK_(stm);
        auto clr_heading    =   VERSIONS_CLR_HEADING_(stm);
        auto clr_reset      =   VERSIONS_CLR_RESET_(stm);

#ifdef __cpp_lib_print

        std::println(
            "{1}STLSoft libraries{0} (C++, using {2}std::format{0}):"
        ,   clr_reset
        ,   clr_heading
        ,   clr_framework
        );
#else

        stm <<
            std::format(
                "{1}STLSoft libraries{0} (C++, using {2}std::format{0}):"
            ,   clr_reset
            ,   clr_heading
            ,   clr_framework
            )
            << std::endl
        ;
#endif
        stm << std::endl;


        // __cplusplus
        {
            auto clr_macro      =   VERSIONS_CLR_MACRO_(stm);
            auto clr_version    =   VERSIONS_CLR_VERSION_(stm);
#ifdef __cpp_lib_print

            std::println(
                "\t{2}__cplusplus{1} = {3}{0}{1}\n"
            ,   __cplusplus
            ,   clr_reset
            ,   clr_macro
            ,   clr_version
            );
#else

            std::cout
                << "\t"
                << std::format(
                        "{2}__cplusplus{1} = {3}{0}{1}"
                    ,   __cplusplus
                    ,   clr_reset
                    ,   clr_macro
                    ,   clr_version
                    )
                << std::endl
                ;
            stm << std::endl;
#endif
        }

        /* compiler strings */
        {
            auto clr_macro      =   VERSIONS_CLR_MACRO_(stm);
            auto clr_version    =   VERSIONS_CLR_VERSION_(stm);
#ifdef __cpp_lib_print

            std::println(
                "\t{2}STLSOFT_COMPILER_LABEL_STRING{1} = {3}{0}{1}"
            ,   STLSOFT_COMPILER_LABEL_STRING
            ,   clr_reset
            ,   clr_macro
            ,   clr_version
            );
            std::println(
                "\t{2}STLSOFT_COMPILER_VERSION_STRING{1} = {3}{0}{1}"
            ,   STLSOFT_COMPILER_VERSION_STRING
            ,   clr_reset
            ,   clr_macro
            ,   clr_version
            );
#else

            stm
                << "\t"
                << std::format(
                        "{2}STLSOFT_COMPILER_LABEL_STRING{1} = {3}{0}{1}"
                    ,   STLSOFT_COMPILER_LABEL_STRING
                    ,   clr_reset
                    ,   clr_macro
                    ,   clr_version
                    )
                << std::endl
                ;
            stm
                << "\t"
                << std::format(
                        "{2}STLSOFT_COMPILER_VERSION_STRING{1} = {3}{0}{1}"
                    ,   STLSOFT_COMPILER_VERSION_STRING
                    ,   clr_reset
                    ,   clr_macro
                    ,   clr_version
                    )
                << std::endl
                ;
#endif
        }

        stm << std::endl;
    }


    {
        auto clr_heading    =   VERSIONS_CLR_HEADING_(stm);
        auto clr_reset      =   VERSIONS_CLR_RESET_(stm);

#ifdef __cpp_lib_print

        std::println(
            "{0}Subprojects{1}:"
        ,   clr_heading
        ,   clr_reset
        );
#else

        stm <<
            std::format(
                "{0}Subprojects{1}:"
            ,   clr_heading
            ,   clr_reset
            )
            << std::endl
        ;
#endif
        stm << std::endl;

        // _STLSOFT_VER
        print_version(stm, "STLSoft", "_STLSOFT_VER", _STLSOFT_VER);
#ifdef STLSOFT_HAS_ACE

        // _ACESTL_VER
        print_version(stm, "ACESTL", "_ACESTL_VER", _ACESTL_VER);
#endif /* STLSOFT_HAS_ACE */
#ifdef STLSOFT_HAS_ATL

        // _ATLSTL_VER
        print_version(stm, "ATLSTL", "_ATLSTL_VER", _ATLSTL_VER);
#endif /* STLSOFT_HAS_ATL */
#ifdef STLSOFT_HAS_COM

        // _COMSTL_VER
        print_version(stm, "COMSTL", "_COMSTL_VER", _COMSTL_VER);
#endif /* STLSOFT_HAS_COM */
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX) || \
      defined(PLATFORMSTL_OS_IS_WINDOWS)

        // _INETSTL_VER
        print_version(stm, "InetSTL", "_INETSTL_VER", _INETSTL_VER);
#endif
#ifdef STLSOFT_HAS_MFC

        /* _MFCSTL_VER */
        print_version(stm, "MFCSTL", "_MFCSTL_VER", _MFCSTL_VER);
#endif

        // _PLATFORMSTL_VER
        print_version(stm, "PlatformSTL", "_PLATFORMSTL_VER", _PLATFORMSTL_VER);
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

        // _UNIXSTL_VER
        print_version(stm, "UNIXSTL", "_UNIXSTL_VER", _UNIXSTL_VER);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

        // _WINSTL_VER
        print_version(stm, "WinSTL", "_WINSTL_VER", _WINSTL_VER);
#endif

        stm << std::endl;
    }


    {
        auto clr_heading    =   VERSIONS_CLR_HEADING_(stm);
        auto clr_reset      =   VERSIONS_CLR_RESET_(stm);

#ifdef __cpp_lib_print

        std::println(
            "{0}Efferent dependencies{1}:"
        ,   clr_heading
        ,   clr_reset
        );
#else

        stm <<
            std::format(
                "{0}Efferent dependencies{1}:"
            ,   clr_heading
            ,   clr_reset
            )
            << std::endl
        ;
#endif
        stm << std::endl;


#ifdef HAS_cstring

        print_version(stm, "cstring", "CSTRING_VER", CSTRING_VER);
#endif
#ifdef HAS_Diagnosticism

        print_version(stm, "Diagnosticism", "DIAGNOSTICISM_VER", DIAGNOSTICISM_VER);
#endif
#ifdef HAS_shwild

        print_version(stm, "shwild", "SHWILD_VER", SHWILD_VER);
#endif
#ifdef HAS_UNIXem

        print_version(stm, "UNIXem", "UNIXEM_VER", UNIXEM_VER);
#endif
#ifdef HAS_woad

        print_version(stm, "woad", "WOAD_VER", WOAD_VER);
#endif
#ifdef HAS_xTests

        print_version(stm, "xTests", "_XTESTS_VER", _XTESTS_VER);
#endif

        stm << std::endl;
    }


    return EXIT_SUCCESS;
}

/* ///////////////////////////// end of file //////////////////////////// */

