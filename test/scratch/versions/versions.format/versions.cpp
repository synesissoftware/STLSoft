
#include <stlsoft/stlsoft.h>
#include <platformstl/platformstl.h>
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)
# include <inetstl/inetstl.h>
# include <unixstl/unixstl.h>
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)
# include <inetstl/inetstl.h>
# include <winstl/winstl.h>
#endif
#ifdef STLSOFT_HAS_ACE
# include <acestl/acestl.hpp>
#endif

#include <cstdint>
#include <iostream>
#include <string>
#include <version>

#if defined(__cpp_lib_format) && \
    __cpp_lib_format >= 201907L
# include <format>
# define VERSIONS_FORMAT_HAS_STD_FORMAT_
#endif


#ifdef VERSIONS_FORMAT_HAS_STD_FORMAT_

namespace {

void
print_version(
    char const*     name
,   char const*     macro_name
,   std::uint32_t   ver
)
{
    std::cout
        << std::format(
            "{} = {}.{}.{}.{}\n"
            "{} = 0x{:08x}\n"
            "\n"
        ,   name
        ,   (ver >> 24) & 0xff
        ,   (ver >> 16) & 0xff
        ,   (ver >> 8) & 0xff
        ,   (ver >> 0) & 0xff
        ,   macro_name
        ,   ver
        )
        ;
}
} // anonymous namespace


int main(int /* argc */, char* /* argv */[])
{
    // __cplusplus

    std::cout << std::format("__cplusplus = {}\n\n", __cplusplus);


    // _STLSOFT_VER

    print_version("STLSoft", "_STLSOFT_VER", _STLSOFT_VER);
    std::cout
        << std::format(
            "STLSOFT_COMPILER_VERSION_STRING = {}\n\n"
        ,   STLSOFT_COMPILER_VERSION_STRING
        )
        ;
#ifdef STLSOFT_HAS_ACE

    // _ACESTL_VER

    print_version("ACESTL", "_ACESTL_VER", _ACESTL_VER);
#endif /* STLSOFT_HAS_ACE */

    // _PLATFORMSTL_VER

    print_version("PlatformSTL", "_PLATFORMSTL_VER", _PLATFORMSTL_VER);

#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX)

    // _UNIXSTL_VER

    print_version("UNIXSTL", "_UNIXSTL_VER", _UNIXSTL_VER);
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)

    // _WINSTL_VER

    print_version("WinSTL", "_WINSTL_VER", _WINSTL_VER);
#endif
#if 0
#elif defined(PLATFORMSTL_OS_IS_UNIX) || \
      defined(PLATFORMSTL_OS_IS_WINDOWS)

    // _INETSTL_VER

    print_version("InetSTL", "_INETSTL_VER", _INETSTL_VER);
#endif

    return EXIT_SUCCESS;
}
#else /* ? VERSIONS_FORMAT_HAS_STD_FORMAT_ */

int main(int /* argc */, char* /* argv */[])
{
    std::cerr << "std::format is not available with this toolchain" << std::endl;

    return EXIT_FAILURE;
}
#endif /* VERSIONS_FORMAT_HAS_STD_FORMAT_ */

