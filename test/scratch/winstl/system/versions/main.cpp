
#include <stdio.h>

#include <winstl/dl/dl_call.hpp>
#include <winstl/system/os_version.h>
#include <winstl/system/system_version.hpp>

#include <iostream>

int main(int /* argc */, char* /* argv */[])
{
    // ::GetVersion()
    {
#include <stlsoft/internal/warnings/push/suppress_deprecation_.h>

        std::cout << "::GetVersion() : ";

        DWORD const v = ::GetVersion();

        std::cout
            << "\t"
            << (DWORD)(LOBYTE(LOWORD(v)))
            << "."
            << (DWORD)(HIBYTE(LOWORD(v)))
            << "."
            << (DWORD)(HIWORD(v))
            << std::endl;

#include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
    }

    // ::GetVersionEx()
    {
#include <stlsoft/internal/warnings/push/suppress_deprecation_.h>

        std::cout << "::GetVersionEx() : ";

        OSVERSIONINFO osvi;

        osvi.dwOSVersionInfoSize = sizeof(osvi);

        ::GetVersionEx(&osvi);

        std::cout
            << "\t"
            << osvi.dwMajorVersion
            << "."
            << osvi.dwMinorVersion
            << "."
            << osvi.dwBuildNumber
            << std::endl;

#include <stlsoft/internal/warnings/pop/suppress_deprecation_.h>
    }

    // ::RtlGetVersion()
    {
        std::cout << "::RtlGetVersion() : ";

        OSVERSIONINFOW osvi;

        osvi.dwOSVersionInfoSize = sizeof(osvi);

        try
        {
            LONG const r = winstl::dl_call<LONG>("NtosKrnl.exe", winstl::fn_desc(3, "RtlGetVersion"), &osvi);

            if (0 == r)
            {
                std::cout
                    << "\t"
                    << osvi.dwMajorVersion
                    << "."
                    << osvi.dwMinorVersion
                    << "."
                    << osvi.dwBuildNumber
                    << std::endl;
            }
        }
        catch (std::bad_alloc&)
        {
            std::cerr << "out of memory" << std::endl;
        }
        catch (std::exception& x)
        {
            std::cerr << "exception: " << x.what() << std::endl;
        }
    }

    // ::RtlGetNtVersionNumbers()
    {
        std::cout << "::RtlGetNtVersionNumbers() : ";

        ULONG ntMajorVersion;
        ULONG ntMinorVersion;
        ULONG ntBuildNumber;

        try
        {
            winstl::dl_call<void>("ntdll.dll", winstl::fn_desc(3, "RtlGetNtVersionNumbers"), &ntMajorVersion, &ntMinorVersion, &ntBuildNumber);

            std::cout
                << "\t"
                << ntMajorVersion
                << "."
                << ntMinorVersion
                << "."
                << LOWORD(ntBuildNumber)
                << std::endl;
        }
        catch (std::bad_alloc&)
        {
            std::cerr << "out of memory" << std::endl;
        }
        catch (std::exception& x)
        {
            std::cerr << "exception: " << x.what() << std::endl;
        }
    }

    // winstl::system_version
    {
        std::cout << "winstl::system_version : ";

        std::cout
            << "\t"
            << winstl::system_version::major()
            << "."
            << winstl::system_version::minor()
            << "."
            << winstl::system_version::build_number()
            << std::endl;
    }

    // winstl_C_internal_GetVersionEx
    {
        using namespace winstl;

        std::cout << "winstl_C_internal_GetVersionEx() : ";

        OSVERSIONINFO osvi;

        osvi.dwOSVersionInfoSize = sizeof(osvi);

        winstl_C_internal_GetVersionEx(&osvi);

        std::cout
            << "\t"
            << osvi.dwMajorVersion
            << "."
            << osvi.dwMinorVersion
            << "."
            << osvi.dwBuildNumber
            << std::endl;
    }

    // winstl_C_identify_operating_system
    {
        using namespace winstl;

        std::cout << "winstl_C_identify_operating_system() : ";

        auto const ios = winstl_C_identify_operating_system(NULL);

        std::cout
            << "\t"
            << c_str_data_a(ios)
            << std::endl;
    }

    return 0;
}
