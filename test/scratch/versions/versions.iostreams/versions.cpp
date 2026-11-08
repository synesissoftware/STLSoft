
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

#include <iomanip>
#include <iostream>

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
    ,   (int)((libver >> 24) & 0xff)
    ,   (int)((libver >> 16) & 0xff)
    ,   (int)((libver >> 8) & 0xff)
    ,   (int)((libver >> 0) & 0xff)
    ,   &n
    );

    if (0 == r)
    {
        buffer[n] = '\0';

        std::ios::fmtflags const    flags   =   stm.flags();
        char const                  fill    =   stm.fill();

        stm
            << "\t"
            << VERSIONS_CLR_NAME_
            << name
            << VERSIONS_CLR_RESET_
            << ": "
            << VERSIONS_CLR_VERSION_
            << buffer
            << VERSIONS_CLR_RESET_
            << " ("
            << VERSIONS_CLR_MACRO_
            << macroname
            << VERSIONS_CLR_RESET_
            << " = "
            << VERSIONS_CLR_VERSION_
            << "0x"
            << std::hex
            << std::setfill('0')
            << std::setw(8)
            << libver
            << VERSIONS_CLR_RESET_
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
        << VERSIONS_CLR_NAME_
        << name
        << VERSIONS_CLR_RESET_
        << ": "
        << VERSIONS_CLR_VERSION_
        << 'v'
        << ((libver >> 24) & 0xff)
        << '.'
        << ((libver >> 16) & 0xff)
        << '.'
        << ((libver >> 8) & 0xff)
        << '.'
        << ((libver >> 0) & 0xff)
        << VERSIONS_CLR_RESET_
        << " ("
        << VERSIONS_CLR_MACRO_
        << macroname
        << VERSIONS_CLR_RESET_
        << " = "
        << VERSIONS_CLR_VERSION_
        << "0x"
        << std::hex
        << std::setfill('0')
        << std::setw(8)
        << libver
        << VERSIONS_CLR_RESET_
        << ")"
        << std::endl
        ;

    stm.flags(flags);
    stm.fill(fill);
}

void
print_subproject_(
    std::ostream&   stm
,   char const*     name
,   char const*     macroName
,   unsigned long   libver
)
{
    stm
        << "\t"
        << VERSIONS_CLR_NAME_
        << name
        << VERSIONS_CLR_RESET_
        << " = "
        << VERSIONS_CLR_VERSION_
        << ((libver >> 24) & 0xff)
        << "."
        << ((libver >> 16) & 0xff)
        << "."
        << ((libver >> 8) & 0xff)
        << "."
        << ((libver >> 0) & 0xff)
        << VERSIONS_CLR_RESET_
        << std::endl
        ;
    stm
        << "\t"
        << VERSIONS_CLR_MACRO_
        << macroName
        << VERSIONS_CLR_RESET_
        << " = "
        << VERSIONS_CLR_VERSION_
        << "0x"
        << std::hex << std::setfill('0') << std::setw(8) << libver
        << std::dec
        << VERSIONS_CLR_RESET_
        << std::endl
        ;

    stm << std::endl;
}


int main(int /* argc */, char* /* argv */[])
{
    std::cout << std::endl;
    std::cout << VERSIONS_CLR_HEADING_ << "STLSoft libraries" << VERSIONS_CLR_RESET_ << ":" << std::endl;


    // __cplusplus

    {
        std::cout
            << "\t"
            << VERSIONS_CLR_MACRO_
            << "__cplusplus"
            << VERSIONS_CLR_RESET_
            << " = "
            << VERSIONS_CLR_VERSION_
            << __cplusplus
            << VERSIONS_CLR_RESET_
            << std::endl
            ;

        std::cout << std::endl;
    }

    {
        std::cout
            << "\t"
            << VERSIONS_CLR_MACRO_
            << "STLSOFT_COMPILER_LABEL_STRING"
            << VERSIONS_CLR_RESET_
            << " = "
            << VERSIONS_CLR_VERSION_
            << STLSOFT_COMPILER_LABEL_STRING
            << VERSIONS_CLR_RESET_
            << std::endl
            ;

        std::cout
            << "\t"
            << VERSIONS_CLR_MACRO_
            << "STLSOFT_COMPILER_VERSION_STRING"
            << VERSIONS_CLR_RESET_
            << " = "
            << VERSIONS_CLR_VERSION_
            << STLSOFT_COMPILER_VERSION_STRING
            << VERSIONS_CLR_RESET_
            << std::endl
            ;
    }


    {
        std::cout << std::endl;
        std::cout << VERSIONS_CLR_HEADING_ << "Subprojects" << VERSIONS_CLR_RESET_ << ":" << std::endl;
        std::cout << std::endl;


        // _STLSOFT_VER
        print_subproject_(std::cout, "STLSoft", "_STLSOFT_VER", _STLSOFT_VER);


#ifdef STLSOFT_HAS_ACE

        /* _ACESTL_VER */
        print_subproject_(std::cout, "ACESTL", "_ACESTL_VER", _ACESTL_VER);
#endif


#ifdef STLSOFT_HAS_ATL

        /* _ATLSTL_VER */
        print_subproject_(std::cout, "ATLSTL", "_ATLSTL_VER", _ATLSTL_VER);
#endif


#ifdef STLSOFT_HAS_COM

        /* _COMSTL_VER */
        print_subproject_(std::cout, "COMSTL", "_COMSTL_VER", _COMSTL_VER);
#endif


        /* _PLATFORMSTL_VER */
        print_subproject_(std::cout, "PlatformSTL", "_PLATFORMSTL_VER", _PLATFORMSTL_VER);


#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX) || \
      defined(PLATFORMSTL_OS_IS_WINDOWS)

        /* _INETSTL_VER */
        print_subproject_(std::cout, "InetSTL", "_INETSTL_VER", _INETSTL_VER);
#endif


#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

        /* _UNIXSTL_VER */
        print_subproject_(std::cout, "UNIXSTL", "_UNIXSTL_VER", _UNIXSTL_VER);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

        /* _WINSTL_VER */
        print_subproject_(std::cout, "WinSTL", "_WINSTL_VER", _WINSTL_VER);
#endif
    }


    {
        std::cout << std::endl;
        std::cout << VERSIONS_CLR_HEADING_ << "Efferent dependencies" << VERSIONS_CLR_RESET_ << ":" << std::endl;
        std::cout << std::endl;


#ifdef HAS_cstring

        print_efferent_dependency_(std::cout, "cstring", "CSTRING_VER", CSTRING_VER);
#endif

#ifdef HAS_Diagnosticism

        print_efferent_dependency_(std::cout, "Diagnosticism", "DIAGNOSTICISM_VER", DIAGNOSTICISM_VER);
#endif


#ifdef HAS_shwild

        print_efferent_dependency_(std::cout, "shwild", "SHWILD_VER", SHWILD_VER);
#endif

#ifdef HAS_UNIXem

        print_efferent_dependency_(std::cout, "UNIXem", "UNIXEM_VER", UNIXEM_VER);
#endif

#ifdef HAS_woad

        print_efferent_dependency_(std::cout, "woad", "WOAD_VER", WOAD_VER);
#endif

#ifdef HAS_xTests

        print_efferent_dependency_(std::cout, "xTests", "XTESTS_VER", _XTESTS_VER);
#endif
    }

    return 0;
}

