
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

#include <iomanip>
#include <iostream>

#include <stdio.h>


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
,   char const*     macroname
,   unsigned        libver
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

        std::ios::fmtflags const    flags   =   stm.flags();
        char const                  fill    =   stm.fill();

        stm
            << "\t"
            << VERSIONS_CLR_NAME_(stm)
            << name
            << VERSIONS_CLR_RESET_(stm)
            << ": "
            << VERSIONS_CLR_VERSION_(stm)
            << buffer
            << VERSIONS_CLR_RESET_(stm)
            << " ("
            << VERSIONS_CLR_MACRO_(stm)
            << macroname
            << VERSIONS_CLR_RESET_(stm)
            << " = "
            << VERSIONS_CLR_VERSION_(stm)
            << "0x"
            << std::hex
            << std::setfill('0')
            << std::setw(8)
            << libver
            << VERSIONS_CLR_RESET_(stm)
            << ")"
            << std::endl
            ;

        stm.flags(flags);
        stm.fill(fill);

        return;
    }
#endif /* HAS_Diagnosticism */

    std::ios::fmtflags const    flags   =   stm.flags();
    char const                  fill    =   stm.fill();

    stm
        << "\t"
        << VERSIONS_CLR_NAME_(stm)
        << name
        << VERSIONS_CLR_RESET_(stm)
        << ": "
        << VERSIONS_CLR_VERSION_(stm)
        << 'v'
        << VER_MAJOR_(int, libver)
        << '.'
        << VER_MINOR_(int, libver)
        << '.'
        << VER_PATCH_(int, libver)
        << '.'
        << VER_RELST_(int, libver)
        << VERSIONS_CLR_RESET_(stm)
        << " ("
        << VERSIONS_CLR_MACRO_(stm)
        << macroname
        << VERSIONS_CLR_RESET_(stm)
        << " = "
        << VERSIONS_CLR_VERSION_(stm)
        << "0x"
        << std::hex
        << std::setfill('0')
        << std::setw(8)
        << libver
        << VERSIONS_CLR_RESET_(stm)
        << ")"
        << std::endl
        ;

    stm.flags(flags);
    stm.fill(fill);
}
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int /* argc */, char* /* argv */[])
{
    std::ostream &stm = std::cout;

    {
        stm
            << VERSIONS_CLR_HEADING_(stm)
            << "STLSoft libraries"
            << VERSIONS_CLR_RESET_(stm)
            << " (C++, using "
            << VERSIONS_CLR_FRAMEWORK_(stm)
            << "IOStreams"
            << VERSIONS_CLR_RESET_(stm)
            << "):"
            << std::endl
            ;
        stm << std::endl;


        // __cplusplus
        {
            stm
                << "\t"
                << VERSIONS_CLR_MACRO_(stm)
                << "__cplusplus"
                << VERSIONS_CLR_RESET_(stm)
                << " = "
                << VERSIONS_CLR_VERSION_(stm)
                << __cplusplus
                << VERSIONS_CLR_RESET_(stm)
                << std::endl
                ;
            stm << std::endl;
        }

        /* compiler strings */
        {
            stm
                << "\t"
                << VERSIONS_CLR_MACRO_(stm)
                << "STLSOFT_COMPILER_LABEL_STRING"
                << VERSIONS_CLR_RESET_(stm)
                << " = "
                << VERSIONS_CLR_VERSION_(stm)
                << STLSOFT_COMPILER_LABEL_STRING
                << VERSIONS_CLR_RESET_(stm)
                << std::endl
                ;

            stm
                << "\t"
                << VERSIONS_CLR_MACRO_(stm)
                << "STLSOFT_COMPILER_VERSION_STRING"
                << VERSIONS_CLR_RESET_(stm)
                << " = "
                << VERSIONS_CLR_VERSION_(stm)
                << STLSOFT_COMPILER_VERSION_STRING
                << VERSIONS_CLR_RESET_(stm)
                << std::endl
                ;
        }
    }


    {
        stm
            << std::endl
            << VERSIONS_CLR_HEADING_(stm)
            << "Subprojects"
            << VERSIONS_CLR_RESET_(stm)
            << ":"
            << std::endl
            ;
        stm << std::endl;


        // _STLSOFT_VER
        print_version(stm, "STLSoft", "_STLSOFT_VER", _STLSOFT_VER);
#ifdef STLSOFT_HAS_ACE

        /* _ACESTL_VER */
        print_version(stm, "ACESTL", "_ACESTL_VER", _ACESTL_VER);
#endif
#ifdef STLSOFT_HAS_ATL

        /* _ATLSTL_VER */
        print_version(stm, "ATLSTL", "_ATLSTL_VER", _ATLSTL_VER);
#endif
#ifdef STLSOFT_HAS_COM

        /* _COMSTL_VER */
        print_version(stm, "COMSTL", "_COMSTL_VER", _COMSTL_VER);
#endif
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX) ||\
      defined(PLATFORMSTL_OS_IS_WINDOWS)

        /* _INETSTL_VER */
        print_version(stm, "InetSTL", "_INETSTL_VER", _INETSTL_VER);
#endif

        /* _PLATFORMSTL_VER */
        print_version(stm, "PlatformSTL", "_PLATFORMSTL_VER", _PLATFORMSTL_VER);
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

        /* _UNIXSTL_VER */
        print_version(stm, "UNIXSTL", "_UNIXSTL_VER", _UNIXSTL_VER);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

        /* _WINSTL_VER */
        print_version(stm, "WinSTL", "_WINSTL_VER", _WINSTL_VER);
#endif

        stm << std::endl;
    }


    {
        stm
            << VERSIONS_CLR_HEADING_(stm)
            << "Efferent dependencies"
            << VERSIONS_CLR_RESET_(stm)
            << ":"
            << std::endl
        ;
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

        print_version(stm, "xTests", "XTESTS_VER", _XTESTS_VER);
#endif

        stm << std::endl;
    }


    return 0;
}

/* ///////////////////////////// end of file //////////////////////////// */

